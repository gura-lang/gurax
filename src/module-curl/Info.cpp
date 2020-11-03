//==============================================================================
// Info.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// Info
//------------------------------------------------------------------------------
Value* Info::GetEntry(CURLINFO info)
{
	CURLcode code = CURLE_OK;
	RefPtr<Value> pValueRtn(Value::nil());
	long infoType = info & CURLINFO_TYPEMASK;
	if (infoType == CURLINFO_STRING) {
		const char* value;
		code = curl_easy_getinfo(_curl, info, &value);
		pValueRtn.reset(new Value_String(value));
	} else if (infoType == CURLINFO_LONG) {
		long value;
		code = curl_easy_getinfo(_curl, info, &value);
		pValueRtn.reset(new Value_Number(value));
	} else if (infoType == CURLINFO_DOUBLE) {
		double value;
		code = curl_easy_getinfo(_curl, info, &value);
		pValueRtn.reset(new Value_Number(value));
	} else if (infoType == CURLINFO_SLIST) {
		curl_slist* slist = nullptr;
		code = curl_easy_getinfo(_curl, info, &slist);
		RefPtr<ValueOwner> pValues(CreateValueOwnerFromSList(slist));
		curl_free(slist);
		pValueRtn.reset(new Value_List(VTYPE_String, pValues.release()));
	} else if (infoType == CURLINFO_PTR) {
	} else if (infoType == CURLINFO_SOCKET) {
	} else if (infoType == CURLINFO_OFF_T) {
		curl_off_t value;
		code = curl_easy_getinfo(_curl, info, &value);
		pValueRtn.reset(new Value_Number(value));
	}
	if (code != CURLE_OK) {
		Error::Issue(ErrorType::GuestError, "%s", curl_easy_strerror(code));		
		return Value::nil();
	}
	return pValueRtn.release();
}

String Info::ToString(const StringStyle& ss) const
{
	return String().Format("curl.Info");
}

Gurax_EndModuleScope(curl)
