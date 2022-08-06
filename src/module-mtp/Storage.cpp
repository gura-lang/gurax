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
bool StorageOwner::Enumerate()
{
#if 0
	CComPtr<IPortableStorageManager> pPortableStorageManager;
	if (FAILED(::CoCreateInstance(CLSID_PortableStorageManager, nullptr,
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pPortableStorageManager)))) return false;
	DWORD nStorageIDs = 0;
	if (FAILED(pPortableStorageManager->GetStorages(nullptr, &nStorageIDs))) return false;
	std::unique_ptr<LPWSTR[]> StorageIDs(new LPWSTR[nStorageIDs]);
	if (FAILED(pPortableStorageManager->GetStorages(StorageIDs.get(), &nStorageIDs))) return false;
	for (DWORD i = 0; i < nStorageIDs; i++) {
		RefPtr<Storage> pStorage(new Storage(StorageIDs[i]));
		::CoTaskMemFree(StorageIDs[i]);
		if (!pStorage->Open(pPortableStorageManager.p)) return false;
		push_back(pStorage.release());
	}
#endif
	return true;
}

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
	str.Format("Storage:begin=%zu:end=%zu", _idxBegin, _idxEnd);
	return str;
}

Gurax_EndModuleScope(mtp)
