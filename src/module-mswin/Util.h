//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_MSWIN_UTIL_H
#define GURAX_MODULE_MSWIN_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(mswin)

void SetErrorFromErrCode(DWORD dwErrCode);
void SetErrorFromHRESULT(HRESULT hr);
OLECHAR* StringToBSTR(const char* psz);
String BSTRToString(const OLECHAR* bstr);
Value* VariantToValue(const VARIANT& var);
bool ValueToVariant(VARIANT& var, Value& value);
Value* RegDataToValue(DWORD dwType, LPCBYTE lpData, DWORD cbData);
bool ValueToRegData(const Value& value, DWORD* pdwType, LPBYTE* lppData, DWORD* pcbData);

Gurax_EndModuleScope(mswin)

#endif
