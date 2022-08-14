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
	RefPtr<DirectoryEx> pDirectory(new DirectoryEx(nullptr, "/", Directory::Type::Folder, _pDevice->Reference(), GetObjectID()));
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

	}
	return pDirectory.release();
}

bool Storage::RecvFile(const char* pathName, Stream& stream, const Function* pFuncBlock) const
{
	return false;
}

bool Storage::SendFile(const char* pathName, Stream& stream, const Function* pFuncBlock) const
{
	return false;
}

bool Storage::DeleteFile(const char* pathName) const
{
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
