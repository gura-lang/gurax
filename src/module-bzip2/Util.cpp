//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(bzip2)

Value_Stream* GenerateReader(Stream* pStreamSrc)
{
	size_t bytesSrc = -1;
	size_t bytesBuff = 32768;
	int verbosity = 0;
	int small = 0;
	RefPtr<BZLib::Stream_Reader> pStream(new BZLib::Stream_Reader(pStreamSrc, bytesSrc, bytesBuff));
	if (!pStream->Initialize(verbosity, small)) return nullptr;
	return new Value_Stream(pStream.release());
}

Value_Stream* GenerateWriter(Stream* pStreamDst, int blockSize100k)
{
	int verbosity = 0;
	int workFactor = 0;
	RefPtr<BZLib::Stream_Writer> pStream(new BZLib::Stream_Writer(pStreamDst));
	if (!pStream->Initialize(blockSize100k, verbosity, workFactor)) return nullptr;
	return new Value_Stream(pStream.release());
}

Gurax_EndModuleScope(bzip2)
