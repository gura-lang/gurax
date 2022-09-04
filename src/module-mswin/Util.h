//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_MSWIN_UTIL_H
#define GURAX_MODULE_MSWIN_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(mswin)

void SetErrorFromErrCode(DWORD dwErrCode);
OLECHAR* StringToBSTR(const char* psz);
String BSTRToString(const OLECHAR* bstr);
Value* VariantToValue(const VARIANT& var);
Value* RegDataToValue(DWORD dwType, LPCBYTE lpData, DWORD cbData);
bool ValueToRegData(const Value& value, DWORD* pdwType, LPBYTE* lppData, DWORD* pcbData);

Gurax_EndModuleScope(mswin)

#endif