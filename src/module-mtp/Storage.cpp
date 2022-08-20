//==============================================================================
// Storage.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mtp)

//------------------------------------------------------------------------------
// Storage
//------------------------------------------------------------------------------
Storage::Storage(Device* pDevice, LPCWSTR objectID) :
	_pDevice(pDevice), _objectID(objectID),
	_pStorageType(Symbol::Empty), _pFilesystemType(Symbol::Empty), _pAccessCapability(Symbol::Empty),
	_maxCapacity(0), _freeSpaceInBytes(0), _freeSpaceInObjects(0)
{
}

Storage* Storage::OpenStorage(size_t iDevice, size_t iStorage)
{
	RefPtr<Device> pDevice(Device::OpenDevice(iDevice));
	if (!pDevice) return nullptr;
	RefPtr<StorageOwner> pStorageOwner(pDevice->EnumStorage());
	if (!pStorageOwner) {
		Error::Issue(ErrorType::GuestError, "failed to open portable device's storage");
		return nullptr;
	}
	if (iStorage >= pStorageOwner->size()) {
		Error::Issue(ErrorType::IndexError, "storage index is out of range");
		return nullptr;
	}
	return pStorageOwner->at(iStorage)->Reference();
}

DirectoryEx* Storage::OpenDir(const char* pathName)
{
	IPortableDeviceContent* pPortableDeviceContent = _pDevice->GetPortableDeviceContent();
	IPortableDeviceProperties* pPortableDeviceProperties = _pDevice->GetPortableDeviceProperties();
	IPortableDeviceKeyCollection* pPortableDeviceKeyCollection = _pDevice->GetPortableDeviceKeyCollection();
	RefPtr<StatEx> pStat(new StatEx(new DateTime(), new DateTime(), new DateTime(), "", Stat::Flag::Dir, 0));
	RefPtr<DirectoryEx::CoreEx> pCore(new DirectoryEx::CoreEx(GetDevice().Reference(), Directory::Type::Folder, GetObjectID(), pStat.release()));
	RefPtr<DirectoryEx> pDirectory(new DirectoryEx(pCore.release(), nullptr));
	const char* p = pathName;
	if (IsFileSeparator(*p)) p++;
	while (*p != '\0') {
		if (!pDirectory->IsFolder()) {
			Error::Issue(ErrorType::PathError, "can't browse inside an item");
			return nullptr;
		}
		String field;
		for ( ; ; p++) {
			if (*p == '\0') {
				break;
			} else if (IsFileSeparator(*p)) {
				p++;
				break;
			}
			field += *p;
		}
		if (field.empty()) {
			Error::Issue(ErrorType::PathError, "wrong format of path name");
			return nullptr;
		}
		//::printf("[%s]\n", field.c_str());
		CComPtr<IEnumPortableDeviceObjectIDs> pEnumPortableDeviceObjectIDs;
		if (FAILED(pPortableDeviceContent->EnumObjects(0, pDirectory->GetCoreEx().GetObjectID(), nullptr, &pEnumPortableDeviceObjectIDs))) return nullptr;
		HRESULT hr;
		LPWSTR objectIDs[32];
		StringW objectIDFound;
		do {
			DWORD nObjectIDs = 0;
			hr = pEnumPortableDeviceObjectIDs->Next(Gurax_ArraySizeOf(objectIDs), objectIDs, &nObjectIDs);
			if (FAILED(hr)) return nullptr;
			for (DWORD i = 0; i < nObjectIDs; i++) {
				LPCWSTR objectID = objectIDs[i];
				CComPtr<IPortableDeviceValues> pPortableDeviceValues;
				if (FAILED(pPortableDeviceProperties->GetValues(
					objectID, pPortableDeviceKeyCollection, &pPortableDeviceValues))) break;
				// WPD_OBJECT_ORIGINAL_FILE_NAME: VT_LPWSTR
				LPWSTR value = nullptr;
				if (FAILED(pPortableDeviceValues->GetStringValue(
									WPD_OBJECT_ORIGINAL_FILE_NAME, &value))) break;
				String fileName = WSTRToString(value);
				//::printf("%s\n", fileName.c_str());
				::CoTaskMemFree(value);
				if (field == fileName) {
					objectIDFound = objectID;
					break;
				}
			}
			for (DWORD i = 0; i < nObjectIDs; i++) {
				::CoTaskMemFree(objectIDs[i]);
			}
			if (Error::IsIssued()) return nullptr;
		} while (hr == S_OK && objectIDFound.empty());
		if (objectIDFound.empty()) return nullptr;
		pDirectory.reset(DirectoryEx::Create(pDirectory.release(), objectIDFound.c_str()));
	}
	return pDirectory.release();
}

bool Storage::RecvFile(Processor& processor, const char* pathName, Stream& stream, const Function* pFuncBlock)
{
	IPortableDeviceContent* pPortableDeviceContent = _pDevice->GetPortableDeviceContent();
	RefPtr<DirectoryEx> pDirectory(OpenDir(pathName));
	if (!pDirectory) return false;
	if (pDirectory->GetCoreEx().GetStat().IsDir()) {
		Error::Issue(ErrorType::PathError, "can't transfer a folder");
		return false;
	}
	CComPtr<IPortableDeviceResources> pPortableDeviceResources;
 	if (FAILED(pPortableDeviceContent->Transfer(&pPortableDeviceResources))) return false;
	CComPtr<IStream> pStreamOnDevice;
	DWORD bytesBuff;
	if (FAILED(pPortableDeviceResources->GetStream(pDirectory->GetCoreEx().GetObjectID(),
			WPD_RESOURCE_DEFAULT, STGM_READ, &bytesBuff, &pStreamOnDevice))) return false;
	RefPtr<Memory> pMemory(new MemoryHeap(bytesBuff));
	char* buff = pMemory->GetPointerC<char>();
	size_t bytesTotal = pDirectory->GetCoreEx().GetStat().GetBytes();
	size_t bytesSent = 0;
	for (;;) {
		DWORD bytesRead;
		if (FAILED(pStreamOnDevice->Read(buff, bytesBuff, &bytesRead))) return false;
		if (bytesRead == 0) break;
		if (!stream.Write(buff, bytesRead)) return false;
		bytesSent += bytesRead;
		if (pFuncBlock) {
			Value::Delete(pFuncBlock->EvalEasy(processor, new Value_Number(bytesSent), new Value_Number(bytesTotal)));
			if (Error::IsIssued()) return false;
		}
	}
	return true;
}

bool Storage::SendFile(Processor& processor, const char* pathName, Stream& stream, const Function* pFuncBlock)
{
	IPortableDeviceContent* pPortableDeviceContent = _pDevice->GetPortableDeviceContent();
	String dirName, fileName, baseName;
	PathName(pathName).SplitFileName(&dirName, &fileName);
	PathName(fileName).SplitExtName(&baseName, nullptr);
	RefPtr<DirectoryEx> pDirectoryParent(OpenDir(dirName.c_str()));
	if (!pDirectoryParent) return false;
	CComPtr<IPortableDeviceValues> pPortableDeviceValues;
	if (FAILED(::CoCreateInstance(CLSID_PortableDeviceValues, nullptr, CLSCTX_INPROC_SERVER,
					IID_PPV_ARGS(&pPortableDeviceValues)))) return false;
	if (FAILED(pPortableDeviceValues->SetStringValue(
		WPD_OBJECT_PARENT_ID, pDirectoryParent->GetCoreEx().GetObjectID()))) return false;
	if (FAILED(pPortableDeviceValues->SetUnsignedLargeIntegerValue(
		WPD_OBJECT_SIZE, stream.GetBytes()))) return false;
	if (FAILED(pPortableDeviceValues->SetStringValue(
		WPD_OBJECT_ORIGINAL_FILE_NAME, STRToStringW(fileName.c_str()).c_str()))) return false;
	if (FAILED(pPortableDeviceValues->SetStringValue(
		WPD_OBJECT_NAME, STRToStringW(baseName.c_str()).c_str()))) return false;
#if 0
	if (FAILED(pPortableDeviceValues->SetGuidValue(WPD_OBJECT_CONTENT_TYPE, WPD_CONTENT_TYPE_IMAGE))) return false;
	if (FAILED(pPortableDeviceValues->SetGuidValue(WPD_OBJECT_FORMAT, WPD_OBJECT_FORMAT_EXIF))) return false;
#endif
	CComPtr<IStream> pStreamTmp;
	DWORD bytesBuff;
	if (FAILED(pPortableDeviceContent->CreateObjectWithPropertiesAndData(
		pPortableDeviceValues.p, &pStreamTmp, &bytesBuff, nullptr))) return false;
	CComPtr<IPortableDeviceDataStream> pPortableDeviceDataStream;
	if (FAILED(pStreamTmp.QueryInterface(&pPortableDeviceDataStream))) return false;
	RefPtr<Memory> pMemory(new MemoryHeap(bytesBuff));
	char* buff = pMemory->GetPointerC<char>();
	size_t bytesTotal = static_cast<DWORD>(stream.GetBytes());
	size_t bytesSent = 0;
	for (;;) {
		DWORD bytesRead = static_cast<DWORD>(stream.Read(buff, bytesBuff));
		if (Error::IsIssued()) return false;
		if (bytesRead == 0) break;
		DWORD bytesWritten;
		if (FAILED(pPortableDeviceDataStream->Write(buff, bytesRead, &bytesWritten))) return false;
		bytesSent += bytesRead;
		if (pFuncBlock) {
			Value::Delete(pFuncBlock->EvalEasy(processor, new Value_Number(bytesSent), new Value_Number(bytesTotal)));
			if (Error::IsIssued()) return false;
		}
	}
	if (FAILED(pPortableDeviceDataStream->Commit(STGC_DEFAULT))) return false;
	return true;
}

bool Storage::DeleteFile(const char* pathName)
{
	IPortableDeviceContent* pPortableDeviceContent = _pDevice->GetPortableDeviceContent();
	RefPtr<DirectoryEx> pDirectory(OpenDir(pathName));
	if (!pDirectory) return false;
	if (pDirectory->GetCoreEx().GetStat().IsDir()) {
		Error::Issue(ErrorType::PathError, "can't delete a folder");
		return false;
	}
	CComPtr<IPortableDevicePropVariantCollection> pPortableDevicePropVariantCollection;
	if (FAILED(::CoCreateInstance(CLSID_PortableDevicePropVariantCollection,
		nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pPortableDevicePropVariantCollection)))) return false;
	PROPVARIANT propVar;
	if (FAILED(::InitPropVariantFromString(pDirectory->GetCoreEx().GetObjectID(), &propVar))) return false;
	if (FAILED(pPortableDevicePropVariantCollection->Add(&propVar))) goto error_done;
	if (FAILED(pPortableDeviceContent->Delete(PORTABLE_DEVICE_DELETE_NO_RECURSION,
		pPortableDevicePropVariantCollection.p, nullptr))) goto error_done;
	PropVariantClear(&propVar);
	return true;
error_done:
	PropVariantClear(&propVar);
	return false;
}

bool Storage::MoveFile(const char* pathNameOld, const char* pathNameNew, bool overwriteFlag)
{
	return false;
}

bool Storage::CopyFile(const char* pathNameSrc, const char* pathNameDst, bool overwriteFlag)
{
	return false;
}

String Storage::ToString(const StringStyle& ss) const
{
	return String().Format("mtp.Storage:%s:%zubytes", GetStorageDescription(), GetMaxCapacity());
}

//------------------------------------------------------------------------------
// StorageList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// StorageOwner
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Iterator_Storage
//------------------------------------------------------------------------------
Value* Iterator_Storage::DoNextValue()
{
	const StorageOwner& storageOwner = GetStorageOwner();
	if (_idx >= _idxEnd) return nullptr;
	return new Value_Storage(storageOwner[_idx++]->Reference());
}

String Iterator_Storage::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("mtp.Storage:begin=%zu:end=%zu:current=%zu", _idxBegin, _idxEnd, _idx);
	return str;
}

//-----------------------------------------------------------------------------
// Iterator_DirectoryGlobEx
//-----------------------------------------------------------------------------
Directory* Iterator_DirectoryGlobEx::OpenDirectory(const char* pathName)
{
	return nullptr;
}

Gurax_EndModuleScope(mtp)
