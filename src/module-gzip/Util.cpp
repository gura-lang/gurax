//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gzip)

Value_Stream* GenerateReader(Stream* pStreamSrc, int windowBits)
{
	const size_t bytesSrc = -1;
	const size_t bytesBuff = 32768;
	RefPtr<ZLib::Stream_Reader> pStream(new ZLib::Stream_Reader(pStreamSrc, bytesSrc, bytesBuff));
	if (!pStream->Initialize(windowBits)) return nullptr;
	return new Value_Stream(pStream.release());
}

Value_Stream* GenerateWriter(Stream* pStreamDst, int level, int windowBits)
{
	const size_t bytesBuff = 32768;
	const int memLevel = 8;
	RefPtr<ZLib::Stream_Writer> pStream(new ZLib::Stream_Writer(pStreamDst, bytesBuff));
	if (!pStream->Initialize(level, windowBits, memLevel, Z_DEFAULT_STRATEGY)) return nullptr;
	return new Value_Stream(pStream.release());
}

Gurax_EndModuleScope(gzip)
