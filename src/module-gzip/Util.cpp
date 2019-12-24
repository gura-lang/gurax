//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gzip)

Value_Stream* GenerateReader(Stream* pStreamSrc, int windowBits)
{
	RefPtr<ZLib::Stream_Reader> pStream(new ZLib::Stream_Reader(pStreamSrc, -1));
	if (!pStream->Initialize(windowBits)) return nullptr;
	return new Value_Stream(pStream.release());
}

Value_Stream* GenerateWriter(Stream* pStreamDst, int level, int windowBits)
{
	RefPtr<ZLib::Stream_Writer> pStream(new ZLib::Stream_Writer(pStreamDst));
	if (!pStream->Initialize(level, windowBits, 8, Z_DEFAULT_STRATEGY)) return nullptr;
	return new Value_Stream(pStream.release());
}

Gurax_EndModuleScope(gzip)
