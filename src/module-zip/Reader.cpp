//==============================================================================
// Reader.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// Reader
//------------------------------------------------------------------------------
bool Reader::ReadCentralDirectory()
{
	return _statOwner.ReadCentralDirectory(*_pStreamSrc);
}

String Reader::ToString(const StringStyle& ss) const
{
	return "Reader";
}

//------------------------------------------------------------------------------
// Iterator_Entry
//------------------------------------------------------------------------------
Value* Iterator_Entry::DoNextValue()
{
	return nullptr;
}

String Iterator_Entry::ToString(const StringStyle& ss) const
{
	return "zip.Entry";
}

Gurax_EndModuleScope(zip)
