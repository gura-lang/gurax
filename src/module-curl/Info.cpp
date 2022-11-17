//==============================================================================
// Info.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// Info
//------------------------------------------------------------------------------
Info::Map Info::_map;

Value* Info::GetProperty(const Symbol* pSymbol)
{
	auto iter = _map.find(pSymbol);
	if (iter == _map.end()) {
		Error::Issue(ErrorType::PropertyError,
			"information '%s' can not be found", pSymbol->GetName());
		return false;
	}
	return GetItem(iter->second);
}

Value* Info::GetItem(CURLINFO info)
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

const Info::Pair Info::_pairTbl[] = {
	{ "EFFECTIVE_URL",				CURLINFO_EFFECTIVE_URL },
	{ "RESPONSE_CODE",				CURLINFO_RESPONSE_CODE },
	{ "TOTAL_TIME",					CURLINFO_TOTAL_TIME },
	{ "NAMELOOKUP_TIME",			CURLINFO_NAMELOOKUP_TIME },
	{ "CONNECT_TIME",				CURLINFO_CONNECT_TIME },
	{ "PRETRANSFER_TIME",			CURLINFO_PRETRANSFER_TIME },
	{ "SIZE_UPLOAD",				CURLINFO_SIZE_UPLOAD },
	{ "SIZE_UPLOAD_T",				CURLINFO_SIZE_UPLOAD_T },
	{ "SIZE_DOWNLOAD",				CURLINFO_SIZE_DOWNLOAD },
	{ "SIZE_DOWNLOAD_T",			CURLINFO_SIZE_DOWNLOAD_T },
	{ "SPEED_DOWNLOAD",				CURLINFO_SPEED_DOWNLOAD },
	{ "SPEED_DOWNLOAD_T",			CURLINFO_SPEED_DOWNLOAD_T },
	{ "SPEED_UPLOAD",				CURLINFO_SPEED_UPLOAD },
	{ "SPEED_UPLOAD_T",				CURLINFO_SPEED_UPLOAD_T },
	{ "HEADER_SIZE",				CURLINFO_HEADER_SIZE },
	{ "REQUEST_SIZE",				CURLINFO_REQUEST_SIZE },
	{ "SSL_VERIFYRESULT",			CURLINFO_SSL_VERIFYRESULT },
	{ "FILETIME",					CURLINFO_FILETIME },
	{ "FILETIME_T",					CURLINFO_FILETIME_T },
	{ "CONTENT_LENGTH_DOWNLOAD",	CURLINFO_CONTENT_LENGTH_DOWNLOAD },
	{ "CONTENT_LENGTH_DOWNLOAD_T",	CURLINFO_CONTENT_LENGTH_DOWNLOAD_T },
	{ "CONTENT_LENGTH_UPLOAD",		CURLINFO_CONTENT_LENGTH_UPLOAD },
	{ "CONTENT_LENGTH_UPLOAD_T",	CURLINFO_CONTENT_LENGTH_UPLOAD_T },
	{ "STARTTRANSFER_TIME",			CURLINFO_STARTTRANSFER_TIME },
	{ "CONTENT_TYPE",				CURLINFO_CONTENT_TYPE },
	{ "REDIRECT_TIME",				CURLINFO_REDIRECT_TIME },
	{ "REDIRECT_COUNT",				CURLINFO_REDIRECT_COUNT },
	{ "PRIVATE",					CURLINFO_PRIVATE },
	{ "HTTP_CONNECTCODE",			CURLINFO_HTTP_CONNECTCODE },
	{ "HTTPAUTH_AVAIL",				CURLINFO_HTTPAUTH_AVAIL },
	{ "PROXYAUTH_AVAIL",			CURLINFO_PROXYAUTH_AVAIL },
	{ "OS_ERRNO",					CURLINFO_OS_ERRNO },
	{ "NUM_CONNECTS",				CURLINFO_NUM_CONNECTS },
	{ "SSL_ENGINES",				CURLINFO_SSL_ENGINES },
	{ "COOKIELIST",					CURLINFO_COOKIELIST },
	{ "LASTSOCKET",					CURLINFO_LASTSOCKET },
	{ "FTP_ENTRY_PATH",				CURLINFO_FTP_ENTRY_PATH },
	{ "REDIRECT_URL",				CURLINFO_REDIRECT_URL },
	{ "PRIMARY_IP",					CURLINFO_PRIMARY_IP },
	{ "APPCONNECT_TIME",			CURLINFO_APPCONNECT_TIME },
	{ "CERTINFO",					CURLINFO_CERTINFO },
	{ "CONDITION_UNMET",			CURLINFO_CONDITION_UNMET },
	{ "RTSP_SESSION_ID",			CURLINFO_RTSP_SESSION_ID },
	{ "RTSP_CLIENT_CSEQ",			CURLINFO_RTSP_CLIENT_CSEQ },
	{ "RTSP_SERVER_CSEQ",			CURLINFO_RTSP_SERVER_CSEQ },
	{ "RTSP_CSEQ_RECV",				CURLINFO_RTSP_CSEQ_RECV },
	{ "PRIMARY_PORT",				CURLINFO_PRIMARY_PORT },
	{ "LOCAL_IP",					CURLINFO_LOCAL_IP },
	{ "LOCAL_PORT",					CURLINFO_LOCAL_PORT },
	{ "TLS_SESSION",				CURLINFO_TLS_SESSION },
	{ "ACTIVESOCKET",				CURLINFO_ACTIVESOCKET },
	{ "TLS_SSL_PTR",				CURLINFO_TLS_SSL_PTR },
	{ "HTTP_VERSION",				CURLINFO_HTTP_VERSION },
	{ "PROXY_SSL_VERIFYRESULT",		CURLINFO_PROXY_SSL_VERIFYRESULT },
	{ "PROTOCOL",					CURLINFO_PROTOCOL },
	{ "SCHEME",						CURLINFO_SCHEME },
	{ "TOTAL_TIME_T",				CURLINFO_TOTAL_TIME_T },
	{ "NAMELOOKUP_TIME_T",			CURLINFO_NAMELOOKUP_TIME_T },
	{ "CONNECT_TIME_T",				CURLINFO_CONNECT_TIME_T },
	{ "PRETRANSFER_TIME_T",			CURLINFO_PRETRANSFER_TIME_T },
	{ "STARTTRANSFER_TIME_T",		CURLINFO_STARTTRANSFER_TIME_T },
	{ "REDIRECT_TIME_T",			CURLINFO_REDIRECT_TIME_T },
	{ "APPCONNECT_TIME_T",			CURLINFO_APPCONNECT_TIME_T },
	{ "RETRY_AFTER",				CURLINFO_RETRY_AFTER },
	{ "EFFECTIVE_METHOD",			CURLINFO_EFFECTIVE_METHOD },
	{ "PROXY_ERROR",				CURLINFO_PROXY_ERROR },
	{ "LASTONE",					CURLINFO_LASTONE },
	{ "HTTP_CODE",					CURLINFO_HTTP_CODE },
};

void Info::Bootup()
{
	for (size_t i = 0; i < Gurax_ArraySizeOf(_pairTbl); i++) {
		_map[Symbol::Add(_pairTbl[i].name)] = _pairTbl[i].info;
	}
}

Gurax_EndModuleScope(curl)
