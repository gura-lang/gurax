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
