//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(tar)

Compress DetermineCompress(const char* fileName, const Symbol* pSymbol)
{
	Compress compress = Compress::None;
	if (!pSymbol || pSymbol->IsIdentical(Gurax_Symbol(auto_))) {
		if (String::EndsWith<CharICase>(fileName, ".tar.gz") ||
			String::EndsWith<CharICase>(fileName, ".tgz")) {
			compress = Compress::Gzip;
		} else if (String::EndsWith<CharICase>(fileName, ".tar.bz2") ||
			String::EndsWith<CharICase>(fileName, ".tb2") ||
			String::EndsWith<CharICase>(fileName, ".tbz2")) {
			compress = Compress::Bzip2;
		}
	} else if (pSymbol->IsIdentical(Gurax_Symbol(gz)) || pSymbol->IsIdentical(Gurax_Symbol(gzip))) {
		compress = Compress::Gzip;
	} else if (pSymbol->IsIdentical(Gurax_Symbol(bz2)) || pSymbol->IsIdentical(Gurax_Symbol(bzip2))) {
		compress = Compress::Bzip2;
	} else if (pSymbol->IsIdentical(Gurax_Symbol(none))) {
		compress = Compress::None;
	} else {
		Error::Issue(ErrorType::SymbolError, "invalid symbol to specify compression method: %s", pSymbol->GetName());
		return Compress::Invalid;
	}
	return compress;
}

Stream* CreateUncompressingStream(Stream& stream)
{
	RefPtr<Stream> pStream(stream.Reference());
	const char* identifier = stream.GetIdentifier();
	if (String::EndsWith<CharICase>(identifier, ".tar.gz") ||
		String::EndsWith<CharICase>(identifier, ".tgz")) {
		ZLib::GZHeader hdr;
		if (!hdr.Read(stream)) return nullptr;
		RefPtr<ZLib::Stream_Reader> pStreamGZ(new ZLib::Stream_Reader(stream.Reference()));
		if (!pStreamGZ->Initialize(-MAX_WBITS)) return nullptr;
		pStream.reset(pStreamGZ.release());
	} else if (String::EndsWith<CharICase>(identifier, ".tar.bz2") ||
			String::EndsWith<CharICase>(identifier, ".tb2") ||
			String::EndsWith<CharICase>(identifier, ".tbz2")) {
		int verbosity = 0, small = 0;
		RefPtr<BZLib::Stream_Reader> pStreamBZ2(new BZLib::Stream_Reader(stream.Reference()));
		if (!pStreamBZ2->Initialize(verbosity, small)) return nullptr;
		pStream.reset(pStreamBZ2.release());
	}
	return pStream.release();
}

Gurax_EndModuleScope(tar)
