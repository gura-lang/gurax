//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mtp)

StringW STRToStringW(LPCSTR str)
{
	// cnt includes null-terminater
	int cnt = ::MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
	std::unique_ptr<WCHAR[]> wstr(new WCHAR [cnt + 1]);
	::MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr.get(), cnt);
	wstr[cnt] = '\0';
	return StringW(wstr.get());
}

String WSTRToString(LPCWSTR wstr)
{
	// cnt includes null-terminater
	int cnt = ::WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
	std::unique_ptr<char []> str(new char [cnt + 1]);
	::WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str.get(), cnt, nullptr, nullptr);
	str[cnt] = '\0';
	return String(str.get());
}

//********************
String HRESULTToString(HRESULT hr)
{
	String rtn;
	PVOID wstr;
	::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				reinterpret_cast<LPTSTR>(&wstr), 0, nullptr);
	//::wprintf(L"[%S]\n", reinterpret_cast<LPWSTR>(wstr));
	if (wstr != nullptr) rtn = WSTRToString(reinterpret_cast<LPWSTR>(wstr));
	::LocalFree(wstr);
	return rtn;
}

void IssueErrorFromHRESULT(HRESULT hr)
{
	Error::Issue(ErrorType::GuestError, "%s", HRESULTToString(hr).c_str());
}

Gurax_EndModuleScope(mtp)
