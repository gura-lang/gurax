//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_GZIP_UTIL_H
#define GURAX_MODULE_GZIP_UTIL_H
#include <gurax.h>
#include <gurax/helper/ZLibHelper.h>

Gurax_BeginModuleScope(gzip)

Value_Stream* GenerateReader(Stream* pStreamSrc, int windowBits);
Value_Stream* GenerateWriter(Stream* pStreamDst, int level, int windowBits);

Gurax_EndModuleScope(gzip)

#endif
