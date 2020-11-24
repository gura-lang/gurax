//==============================================================================
// Reader.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(tar)

//------------------------------------------------------------------------------
// Reader
//------------------------------------------------------------------------------
String Reader::ToString(const StringStyle& ss) const
{
	return String().Format("tar.Reader");
}

//------------------------------------------------------------------------------
// Iterator_Entry
//------------------------------------------------------------------------------
Value* Iterator_Entry::DoNextValue()
{
#if 0
	while (_idx < statExOwner.size()) {
		StatEx* pStatEx = statExOwner[_idx++];
		if (_skipDirFlag && pStatEx->IsDir()) continue;
		RefPtr<Stream> pStream(Stream_Reader::Create(_pReader->GetStreamSrc(), *pStatEx));
		if (!pStream) return nullptr;
		return new Value_Stream(pStream.release());
	}
#endif
	return nullptr;
}

String Iterator_Entry::ToString(const StringStyle& ss) const
{
	return "tar.Entry";
}

Gurax_EndModuleScope(tar)
