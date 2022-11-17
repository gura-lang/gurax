//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_MTP_UTIL_H
#define GURAX_MODULE_MTP_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(mtp)

using StringW = std::basic_string<WCHAR>;

StringW STRToStringW(LPCSTR str);
String WSTRToString(LPCWSTR wstr);
void IssueErrorFromHRESULT(HRESULT hr);
String HRESULTToString(HRESULT hr);

Gurax_EndModuleScope(mtp)

#endif
