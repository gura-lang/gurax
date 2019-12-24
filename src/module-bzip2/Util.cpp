//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"
#include "BZLibHelper.h"

Gurax_BeginModuleScope(bzip2)

Value_Stream* GenerateReader(Stream* pStreamSrc, int windowBits)
{
	RefPtr<BZLib::Stream_Reader> pStream(new BZLib::Stream_Reader(pStreamSrc, -1));
	if (!pStream->Initialize(windowBits)) return nullptr;
	return new Value_Stream(pStream.release());
}

Value_Stream* GenerateWriter(Stream* pStreamDst, int level, int windowBits)
{
	RefPtr<BZLib::Stream_Writer> pStream(new BZLib::Stream_Writer(pStreamDst));
	if (!pStream->Initialize(level, windowBits, 8, Z_DEFAULT_STRATEGY)) return nullptr;
	return new Value_Stream(pStream.release());
}

Gurax_EndModuleScope(bzip2)
