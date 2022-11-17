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
	return _statExOwner.ReadCentralDirectory(*_pStreamSrc);
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
	StatExOwner& statExOwner = _pReader->GetStatExOwner();
	while (_idx < statExOwner.size()) {
		StatEx* pStatEx = statExOwner[_idx++];
		if (_skipDirFlag && pStatEx->IsDir()) continue;
		RefPtr<Stream> pStream(Stream_Reader::Create(_pReader->GetStreamSrc(), *pStatEx));
		if (!pStream) return nullptr;
		return new Value_Stream(pStream.release());
	}
	return nullptr;
}

String Iterator_Entry::ToString(const StringStyle& ss) const
{
	return "zip.Entry";
}

Gurax_EndModuleScope(zip)
