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
	StatOwner& statOwner = _pReader->GetStatOwner();
	while (_idx < statOwner.size()) {
		Stat* pStat = statOwner[_idx++];
		if (pStat->IsFolder()) continue;
		RefPtr<Stream> pStream(CreateStream(_pReader->GetStreamSrc(), *pStat));
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
