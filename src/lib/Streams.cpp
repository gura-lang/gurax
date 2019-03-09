//==============================================================================
// Streams.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stream_File
//------------------------------------------------------------------------------
Stream* Stream_File::Open(const char* fileName, const char* mode)
{
	FILE* fp = ::fopen(fileName, mode);
	return fp? new Stream_File(fp, true, fileName, fileName) : nullptr;
}

}
