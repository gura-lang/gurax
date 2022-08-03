//==============================================================================
// Storage.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mtp)

//------------------------------------------------------------------------------
// Storage
//------------------------------------------------------------------------------
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
	str.Format("Storage:begin=%zu:end=%zu", _idxBegin, _idxEnd);
	return str;
}

Gurax_EndModuleScope(mtp)
