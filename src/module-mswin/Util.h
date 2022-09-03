//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_MSWIN_UTIL_H
#define GURAX_MODULE_MSWIN_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(mswin)

void SetError(DWORD dwErrCode);
OLECHAR* StringToBSTR(const char* psz);
String BSTRToString(const OLECHAR* bstr);

Gurax_EndModuleScope(mswin)

#endif
