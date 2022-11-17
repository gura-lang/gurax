//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_BZIP2_UTIL_H
#define GURAX_MODULE_BZIP2_UTIL_H
#include <gurax.h>
#include <gurax/helper/BZLibHelper.h>

Gurax_BeginModuleScope(bzip2)

Value_Stream* GenerateReader(Stream* pStreamSrc);
Value_Stream* GenerateWriter(Stream* pStreamDst, int blockSize100k);

Gurax_EndModuleScope(bzip2)

#endif
