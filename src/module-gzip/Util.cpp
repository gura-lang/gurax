//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gzip)

Value_Stream* GenerateReader(Stream* pStreamSrc, int windowBits)
{
	RefPtr<ZLib::Stream_Inflater> pStream(new ZLib::Stream_Inflater(pStreamSrc, -1));
	if (!pStream->Initialize(windowBits)) return nullptr;
	return new Value_Stream(pStream.release());
}

Value_Stream* GenerateWriter(Stream* pStreamDst, int level, int windowBits)
{
	RefPtr<ZLib::Stream_Deflater> pStream(new ZLib::Stream_Deflater(pStreamDst));
	if (!pStream->Initialize(level, windowBits, 8, Z_DEFAULT_STRATEGY)) return nullptr;
	return new Value_Stream(pStream.release());
}

Gurax_EndModuleScope(gzip)
