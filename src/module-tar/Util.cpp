//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(tar)

Stream* CreateUncompressingStream(Stream& stream)
{
	RefPtr<Stream> pStream(stream.Reference());
	if (String::EndsWith<CharICase>(stream.GetIdentifier(), ".gz") ||
		String::EndsWith<CharICase>(stream.GetIdentifier(), ".tgz")) {
		ZLib::GZHeader hdr;
		if (!hdr.Read(stream)) return nullptr;
		RefPtr<ZLib::Stream_Reader> pStreamGZ(new ZLib::Stream_Reader(stream.Reference()));
		if (!pStreamGZ->Initialize(-MAX_WBITS)) return nullptr;
		pStream.reset(pStreamGZ.release());
	} else if (String::EndsWith<CharICase>(stream.GetIdentifier(), ".bz2")) {
		int verbosity = 0, small = 0;
		RefPtr<BZLib::Stream_Reader> pStreamBZ2(new BZLib::Stream_Reader(stream.Reference()));
		if (!pStreamBZ2->Initialize(verbosity, small)) return nullptr;
		pStream.reset(pStreamBZ2.release());
	}
	return pStream.release();
}

Gurax_EndModuleScope(tar)
