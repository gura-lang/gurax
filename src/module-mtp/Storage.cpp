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

Directory* Storage::OpenDir(const char* pathName)
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
		if (FAILED(pPortableDeviceContent->EnumObjects(0, GetObjectID(), nullptr, &pEnumPortableDeviceObjectIDs))) return nullptr;
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
		if (objectIDFound.empty()) break;
		pDirectory.reset(DirectoryEx::Create(pDirectory.release(), objectIDFound.c_str()));
	}
	return pDirectory.release();
}

bool Storage::RecvFile(const char* pathName, Stream& stream, const Function* pFuncBlock) const
{
#if 0
	AutoPtr<Directory_MTP> pDirectory(GenerateDirectory(sig, pathName));
	if (pDirectory.IsNull()) return false;
	if (pDirectory->GetStat()->IsFolder()) {
		sig.SetError(ERR_FileError, "can't transfer a folder");
		return false;
	}
	IPortableDeviceContent *pPortableDeviceContent = _pDevice->GetPortableDeviceContent();
	ComPtr<IPortableDeviceResources> pPortableDeviceResources;
 	if (CatchErr(sig, pPortableDeviceContent->Transfer(&pPortableDeviceResources))) return false;
	ComPtr<IStream> pStreamOnDevice;
	DWORD bytesBuff;
	if (CatchErr(sig, pPortableDeviceResources->GetStream(pDirectory->GetObjectID(),
			WPD_RESOURCE_DEFAULT, STGM_READ, &bytesBuff, &pStreamOnDevice))) return false;
	AutoPtr<Memory> pMemory(new MemoryHeap(bytesBuff));
	char *buff = pMemory->GetPointer();
	size_t bytesTotal = pDirectory->GetStat()->GetFileSize();
	size_t bytesSent = 0;
	for (;;) {
		DWORD bytesRead;
		if (CatchErr(sig, pStreamOnDevice->Read(buff, bytesBuff, &bytesRead))) return false;
		if (bytesRead == 0) break;
		pStream->Write(sig, buff, bytesRead);
		if (sig.IsSignalled()) return false;
		bytesSent += bytesRead;
		if (pFuncBlock != nullptr) {
			Environment &env = pFuncBlock->GetEnvScope();
			AutoPtr<Argument> pArg(new Argument(pFuncBlock));
			pArg->StoreValue(env, Value(bytesSent), Value(bytesTotal));
			pFuncBlock->Eval(env, *pArg);
			if (sig.IsSignalled()) return false;
		}
	}
#endif
	return true;
}

bool Storage::SendFile(const char* pathName, Stream& stream, const Function* pFuncBlock) const
{
#if 0
	String dirName, fileName, baseName;
	PathMgr::SplitFileName(pathName, &dirName, &fileName);
	PathMgr::SplitExtName(fileName.c_str(), &baseName, nullptr);
	AutoPtr<Directory_MTP> pDirectoryParent(GenerateDirectory(sig, dirName.c_str()));
	if (pDirectoryParent.IsNull()) return false;
	IPortableDeviceContent *pPortableDeviceContent = _pDevice->GetPortableDeviceContent();
	ComPtr<IPortableDeviceValues> pPortableDeviceValues;
	if (CatchErr(sig, ::CoCreateInstance(CLSID_PortableDeviceValues, nullptr, CLSCTX_INPROC_SERVER,
					IID_PPV_ARGS(&pPortableDeviceValues)))) return false;
	if (CatchErr(sig, pPortableDeviceValues->SetStringValue(
		WPD_OBJECT_PARENT_ID, pDirectoryParent->GetObjectID()))) return false;
	if (CatchErr(sig, pPortableDeviceValues->SetUnsignedLargeIntegerValue(
		WPD_OBJECT_SIZE, pStream->GetSize()))) return false;
	if (CatchErr(sig, pPortableDeviceValues->SetStringValue(
		WPD_OBJECT_ORIGINAL_FILE_NAME, STRToStringW(fileName.c_str()).c_str()))) return false;
	if (CatchErr(sig, pPortableDeviceValues->SetStringValue(
		WPD_OBJECT_NAME, STRToStringW(baseName.c_str()).c_str()))) return false;
#if 0
	if (CatchErr(sig, pPortableDeviceValues->SetGuidValue(
		WPD_OBJECT_CONTENT_TYPE, WPD_CONTENT_TYPE_IMAGE))) return false;
	if (CatchErr(sig, pPortableDeviceValues->SetGuidValue(
		WPD_OBJECT_FORMAT, WPD_OBJECT_FORMAT_EXIF))) return false;
#endif
	ComPtr<IStream> pStreamTmp;
	DWORD bytesBuff;
	if (CatchErr(sig, pPortableDeviceContent->CreateObjectWithPropertiesAndData(
		pPortableDeviceValues.Get(), &pStreamTmp, &bytesBuff, nullptr))) return false;
	ComPtr<IPortableDeviceDataStream> pPortableDeviceDataStream;
	if (CatchErr(sig, pStreamTmp.As(&pPortableDeviceDataStream))) return false;
	AutoPtr<Memory> pMemory(new MemoryHeap(bytesBuff));
	char *buff = pMemory->GetPointer();
	size_t bytesTotal = static_cast<DWORD>(pStream->GetSize());
	size_t bytesSent = 0;
	for (;;) {
		DWORD bytesRead = static_cast<DWORD>(pStream->Read(sig, buff, bytesBuff));
		if (sig.IsSignalled()) return false;
		if (bytesRead == 0) break;
		DWORD bytesWritten;
		if (CatchErr(sig, pPortableDeviceDataStream->Write(buff, bytesRead, &bytesWritten))) return false;
		bytesSent += bytesRead;
		if (pFuncBlock != nullptr) {
			Environment &env = pFuncBlock->GetEnvScope();
			AutoPtr<Argument> pArg(new Argument(pFuncBlock));
			pArg->StoreValue(env, Value(bytesSent), Value(bytesTotal));
			pFuncBlock->Eval(env, *pArg);
			if (sig.IsSignalled()) return false;
		}
	}
	if (CatchErr(sig, pPortableDeviceDataStream->Commit(STGC_DEFAULT))) return false;
#endif
	return true;
}

bool Storage::DeleteFile(const char* pathName) const
{
#if 0
	IPortableDeviceContent *pPortableDeviceContent = _pDevice->GetPortableDeviceContent();
	AutoPtr<Directory_MTP> pDirectory(GenerateDirectory(sig, pathName));
	if (pDirectory.IsNull()) return false;
	if (pDirectory->GetStat()->IsFolder()) {
		sig.SetError(ERR_FileError, "can't delete a folder");
		return false;
	}
	ComPtr<IPortableDevicePropVariantCollection> pPortableDevicePropVariantCollection;
	if (CatchErr(sig, ::CoCreateInstance(CLSID_PortableDevicePropVariantCollection,
		nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pPortableDevicePropVariantCollection)))) return false;
	PROPVARIANT propVar;
	if (CatchErr(sig, ::InitPropVariantFromString(pDirectory->GetObjectID(), &propVar))) return false;
	if (CatchErr(sig, pPortableDevicePropVariantCollection->Add(&propVar))) goto error_done;
	if (CatchErr(sig, pPortableDeviceContent->Delete(PORTABLE_DEVICE_DELETE_NO_RECURSION,
		pPortableDevicePropVariantCollection.Get(), nullptr))) goto error_done;
	PropVariantClear(&propVar);
	return true;
error_done:
	PropVariantClear(&propVar);
#endif
	return false;
}

bool Storage::MoveFile(const char* pathNameOld, const char* pathNameNew, bool overwriteFlag) const
{
	return false;
}

bool Storage::CopyFile(const char* pathNameSrc, const char* pathNameDst, bool overwriteFlag) const
{
	return false;
}


String Storage::ToString(const StringStyle& ss) const
{
	return String().Format("mtp.Storage");
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

Gurax_EndModuleScope(mtp)
