//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_TAR_UTIL_H
#define GURAX_MODULE_TAR_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(tar)

enum class Compress { Invalid, None, Gzip, Bzip2 };

Compress DetermineCompress(const char* fileName, const Symbol* pSymbol);
Stream* CreateUncompressingStream(Stream& stream);

Gurax_EndModuleScope(tar)

#endif
