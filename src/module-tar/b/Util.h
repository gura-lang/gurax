//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_TAR_UTIL_H
#define GURAX_MODULE_TAR_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(tar)

Stream* CreateUncompressingStream(Stream& stream);

Gurax_EndModuleScope(tar)

#endif
