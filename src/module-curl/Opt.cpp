﻿//==============================================================================
// Opt.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// Opt
//------------------------------------------------------------------------------
Opt::Map Opt::_map;

Opt::Opt(CURL* curl) : _curl(curl),
		pValue_WRITE(Value::nil()),
		pValue_READ(Value::nil()),
		pValue_PROGRESS(Value::nil()),
		pValue_HEADER(Value::nil()),
		pValue_DEBUG(Value::nil()),
		pValue_SSL_CTX(Value::nil()),
		pValue_IOCTL(Value::nil()),
		pValue_CONV_FROM_NETWORK(Value::nil()),
		pValue_CONV_TO_NETWORK(Value::nil()),
		pValue_CONV_FROM_UTF8(Value::nil()),
		pValue_SOCKOPT(Value::nil()),
		pValue_OPENSOCKET(Value::nil()),
		pValue_SEEK(Value::nil()),
		pValue_SSH_KEY(Value::nil()),
		pValue_INTERLEAVE(Value::nil()),
		pValue_CHUNK_BGN(Value::nil()),
		pValue_CHUNK_END(Value::nil()),
		pValue_FNMATCH(Value::nil()),
		pValue_CLOSESOCKET(Value::nil()),
		pValue_XFERINFO(Value::nil()),
		pValue_RESOLVER_START(Value::nil()),
		pValue_TRAILER(Value::nil()) {}

bool Opt::SetProperty(const Symbol* pSymbol, const Value& value)
{
	auto iter = _map.find(pSymbol);
	if (iter == _map.end()) {
		Error::Issue(ErrorType::PropertyError,
			"option '%s' can not be found", pSymbol->GetName());
		return false;
	}
	CURLcode code;
	if (!SetItem(iter->second, value, &code)) return false;
	if (code != CURLE_OK) {
		Error::Issue(ErrorType::GuestError, "%s", curl_easy_strerror(code));
		return false;
	} 
	return true;
}

bool Opt::SetItem(CURLoption option, const Value& value, CURLcode* pCode)
{
	long optType = static_cast<long>(option) / 10000 * 10000;
	CURLcode& code = *pCode;
	code = CURLE_OK;
	if (optType == CURLOPTTYPE_LONG) {
		if (!value.IsInstanceOf(VTYPE_Number)) {
			Error::Issue(ErrorType::TypeError, "the option accepts Number value");
			return false;
		}
		code = curl_easy_setopt(_curl, option, Value_Number::GetNumber<long>(value));
	} else if (optType == CURLOPTTYPE_OBJECTPOINT) {
		switch (option) {
		case CURLOPT_WRITEDATA: {
			pValue_WRITE.reset(value.Reference());
			break;
		}
		case CURLOPT_READDATA: {
			pValue_READ.reset(value.Reference());
			break;
		}
		case CURLOPT_PROGRESSDATA: {
			pValue_PROGRESS.reset(value.Reference());
			break;
		}
		case CURLOPT_HEADERDATA: {
			pValue_HEADER.reset(value.Reference());
			break;
		}
		case CURLOPT_DEBUGDATA: {
			pValue_DEBUG.reset(value.Reference());
			break;
		}
		case CURLOPT_SSL_CTX_DATA: {
			pValue_SSL_CTX.reset(value.Reference());
			break;
		}
		case CURLOPT_IOCTLDATA: {
			pValue_IOCTL.reset(value.Reference());
			break;
		}
		//case CURLOPT_CONV_FROM_NETWORK_DATA: {
		//	pValue_CONV_FROM_NETWORK.reset(value.Reference());
		//	break;
		//}
		//case CURLOPT_CONV_TO_NETWORK_DATA: {
		//	pValue_CONV_TO_NETWORK.reset(value.Reference());
		//	break;
		//}
		//case CURLOPT_CONV_FROM_UTF8_DATA: {
		//	pValue_CONV_FROM_UTF8.reset(value.Reference());
		//	break;
		//}
		case CURLOPT_SOCKOPTDATA: {
			pValue_SOCKOPT.reset(value.Reference());
			break;
		}
		case CURLOPT_OPENSOCKETDATA: {
			pValue_OPENSOCKET.reset(value.Reference());
			break;
		}
		case CURLOPT_SEEKDATA: {
			pValue_SEEK.reset(value.Reference());
			break;
		}
		case CURLOPT_SSH_KEYDATA: {
			pValue_SSH_KEY.reset(value.Reference());
			break;
		}
		case CURLOPT_INTERLEAVEDATA: {
			pValue_INTERLEAVE.reset(value.Reference());
			break;
		}
		//case CURLOPT_CHUNK_BGN_DATA: {
		//	pValue_CHUNK_BGN.reset(value.Reference());
		//	break;
		//}
		//case CURLOPT_CHUNK_END_DATA: {
		//	pValue_CHUNK_END.reset(value.Reference());
		//	break;
		//}
		case CURLOPT_FNMATCH_DATA: {
			pValue_FNMATCH.reset(value.Reference());
			break;
		}
		case CURLOPT_CLOSESOCKETDATA: {
			pValue_CLOSESOCKET.reset(value.Reference());
			break;
		}
		//case CURLOPT_XFERINFODATA: {
		//	pValue_XFERINFO.reset(value.Reference());
		//	break;
		//}
		case CURLOPT_RESOLVER_START_DATA: {
			pValue_RESOLVER_START.reset(value.Reference());
			break;
		}
		case CURLOPT_TRAILERDATA: {
			pValue_TRAILER.reset(value.Reference());
			break;
		}
		case CURLOPT_HTTPHEADER:
		case CURLOPT_QUOTE:
		case CURLOPT_POSTQUOTE:
		case CURLOPT_TELNETOPTIONS:
		case CURLOPT_PREQUOTE:
		case CURLOPT_HTTP200ALIASES:
		case CURLOPT_MAIL_RCPT:
		case CURLOPT_RESOLVE:
		case CURLOPT_PROXYHEADER:
		case CURLOPT_CONNECT_TO: {
			if (!value.IsInstanceOf(VTYPE_curl_slist)) {
				Error::Issue(ErrorType::TypeError, "the option accepts curl_slist value");
				return false;
			}
			code = curl_easy_setopt(_curl, option, Value_curl_slist::GetEntityPtr(value));
			break;
		}
		default: {
			if (!value.IsInstanceOf(VTYPE_String)) {
				Error::Issue(ErrorType::TypeError, "the option accepts String value");
				return false;
			}
			code = curl_easy_setopt(_curl, option, Value_String::GetString(value));
			break;
		}
		}
	} else if (optType == CURLOPTTYPE_FUNCTIONPOINT) {
		if (!value.IsInstanceOf(VTYPE_Function)) {
			Error::Issue(ErrorType::TypeError, "the option accepts Function value");
			return false;
		}
		const Function& func = Value_Function::GetFunction(value);
		switch (option) {
		case CURLOPT_WRITEFUNCTION: {
			pFunc_WRITE.reset(func.Reference());
			break;
		}
		case CURLOPT_READFUNCTION: {
			pFunc_READ.reset(func.Reference());
			break;
		}
		case CURLOPT_PROGRESSFUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION, Value_CURL::Callback_PROGRESS);
			curl_easy_setopt(_curl, CURLOPT_PROGRESSDATA, this);
			pFunc_PROGRESS.reset(func.Reference());
			break;
		}
		case CURLOPT_HEADERFUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_HEADERFUNCTION, Value_CURL::Callback_HEADER);
			curl_easy_setopt(_curl, CURLOPT_HEADERDATA, this);
			pFunc_HEADER.reset(func.Reference());
			break;
		}
		case CURLOPT_DEBUGFUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_DEBUGFUNCTION, Value_CURL::Callback_DEBUG);
			curl_easy_setopt(_curl, CURLOPT_DEBUGDATA, this);
			pFunc_DEBUG.reset(func.Reference());
			break;
		}
		case CURLOPT_SSL_CTX_FUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_SSL_CTX_FUNCTION, Value_CURL::Callback_SSL_CTX);
			curl_easy_setopt(_curl, CURLOPT_SSL_CTX_DATA, this);
			pFunc_SSL_CTX.reset(func.Reference());
			break;
		}
		case CURLOPT_IOCTLFUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_IOCTLFUNCTION, Value_CURL::Callback_IOCTL);
			curl_easy_setopt(_curl, CURLOPT_IOCTLDATA, this);
			pFunc_IOCTL.reset(func.Reference());
			break;
		}
		case CURLOPT_CONV_FROM_NETWORK_FUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_CONV_FROM_NETWORK_FUNCTION, Value_CURL::Callback_CONV_FROM_NETWORK);
			//curl_easy_setopt(_curl, CURLOPT_CONV_FROM_NETWORK_DATA, this);
			pFunc_CONV_FROM_NETWORK.reset(func.Reference());
			break;
		}
		case CURLOPT_CONV_TO_NETWORK_FUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_CONV_TO_NETWORK_FUNCTION, Value_CURL::Callback_CONV_TO_NETWORK);
			//curl_easy_setopt(_curl, CURLOPT_CONV_TO_NETWORK_DATA, this);
			pFunc_CONV_TO_NETWORK.reset(func.Reference());
			break;
		}
		case CURLOPT_CONV_FROM_UTF8_FUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_CONV_FROM_UTF8_FUNCTION, Value_CURL::Callback_CONV_FROM_UTF8);
			//curl_easy_setopt(_curl, CURLOPT_CONV_FROM_UTF8_DATA, this);
			pFunc_CONV_FROM_UTF8.reset(func.Reference());
			break;
		}
		case CURLOPT_SOCKOPTFUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_SOCKOPTFUNCTION, Value_CURL::Callback_SOCKOPT);
			curl_easy_setopt(_curl, CURLOPT_SOCKOPTDATA, this);
			pFunc_SOCKOPT.reset(func.Reference());
			break;
		}
		case CURLOPT_OPENSOCKETFUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_OPENSOCKETFUNCTION, Value_CURL::Callback_OPENSOCKET);
			curl_easy_setopt(_curl, CURLOPT_OPENSOCKETDATA, this);
			pFunc_OPENSOCKET.reset(func.Reference());
			break;
		}
		case CURLOPT_SEEKFUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_SEEKFUNCTION, Value_CURL::Callback_SEEK);
			curl_easy_setopt(_curl, CURLOPT_SEEKDATA, this);
			pFunc_SEEK.reset(func.Reference());
			break;
		}
		case CURLOPT_SSH_KEYFUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_SSH_KEYFUNCTION, Value_CURL::Callback_SSH_KEY);
			curl_easy_setopt(_curl, CURLOPT_SSH_KEYDATA, this);
			pFunc_SSH_KEY.reset(func.Reference());
			break;
		}
		case CURLOPT_INTERLEAVEFUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_INTERLEAVEFUNCTION, Value_CURL::Callback_INTERLEAVE);
			curl_easy_setopt(_curl, CURLOPT_INTERLEAVEDATA, this);
			pFunc_INTERLEAVE.reset(func.Reference());
			break;
		}
		case CURLOPT_CHUNK_BGN_FUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_CHUNK_BGN_FUNCTION, Value_CURL::Callback_CHUNK_BGN);
			//curl_easy_setopt(_curl, CURLOPT_CHUNK_BGN_DATA, this);
			pFunc_CHUNK_BGN.reset(func.Reference());
			break;
		}
		case CURLOPT_CHUNK_END_FUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_CHUNK_END_FUNCTION, Value_CURL::Callback_CHUNK_END);
			//curl_easy_setopt(_curl, CURLOPT_CHUNK_END_DATA, this);
			pFunc_CHUNK_END.reset(func.Reference());
			break;
		}
		case CURLOPT_FNMATCH_FUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_FNMATCH_FUNCTION, Value_CURL::Callback_FNMATCH);
			curl_easy_setopt(_curl, CURLOPT_FNMATCH_DATA, this);
			pFunc_FNMATCH.reset(func.Reference());
			break;
		}
		case CURLOPT_CLOSESOCKETFUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_CLOSESOCKETFUNCTION, Value_CURL::Callback_CLOSESOCKET);
			curl_easy_setopt(_curl, CURLOPT_CLOSESOCKETDATA, this);
			pFunc_CLOSESOCKET.reset(func.Reference());
			break;
		}
		case CURLOPT_XFERINFOFUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_XFERINFOFUNCTION, Value_CURL::Callback_XFERINFO);
			curl_easy_setopt(_curl, CURLOPT_XFERINFODATA, this);
			pFunc_XFERINFO.reset(func.Reference());
			break;
		}
		case CURLOPT_RESOLVER_START_FUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_RESOLVER_START_FUNCTION, Value_CURL::Callback_RESOLVER_START);
			curl_easy_setopt(_curl, CURLOPT_RESOLVER_START_DATA, this);
			pFunc_RESOLVER_START.reset(func.Reference());
			break;
		}
		case CURLOPT_TRAILERFUNCTION: {
			curl_easy_setopt(_curl, CURLOPT_TRAILERFUNCTION, Value_CURL::Callback_TRAILER);
			curl_easy_setopt(_curl, CURLOPT_TRAILERDATA, this);
			pFunc_TRAILER.reset(func.Reference());
			break;
		}
		default: {
			break;
		}
		}
	} else if (optType == CURLOPTTYPE_OFF_T) {
		if (!value.IsInstanceOf(VTYPE_Number)) {
			Error::Issue(ErrorType::TypeError, "the option accepts Number value");
			return false;
		}
		code = curl_easy_setopt(_curl, option, Value_Number::GetNumber<size_t>(value));
	} else if (optType == CURLOPTTYPE_BLOB) {

	}
	return true;
}

String Opt::ToString(const StringStyle& ss) const
{
	return String().Format("curl.Opt");
}

const Opt::Pair Opt::_pairTbl[] = {
	// Enums
	{ "WRITEDATA",					CURLOPT_WRITEDATA },
	{ "URL",						CURLOPT_URL },
	{ "PORT",						CURLOPT_PORT },
	{ "PROXY",						CURLOPT_PROXY },
	{ "USERPWD",					CURLOPT_USERPWD },
	{ "PROXYUSERPWD",				CURLOPT_PROXYUSERPWD },
	{ "RANGE",						CURLOPT_RANGE },
	{ "READDATA",					CURLOPT_READDATA },
	{ "ERRORBUFFER",				CURLOPT_ERRORBUFFER },
	{ "WRITEFUNCTION",				CURLOPT_WRITEFUNCTION },
	{ "READFUNCTION",				CURLOPT_READFUNCTION },
	{ "TIMEOUT",					CURLOPT_TIMEOUT },
	{ "INFILESIZE",					CURLOPT_INFILESIZE },
	{ "POSTFIELDS",					CURLOPT_POSTFIELDS },
	{ "REFERER",					CURLOPT_REFERER },
	{ "FTPPORT",					CURLOPT_FTPPORT },
	{ "USERAGENT",					CURLOPT_USERAGENT },
	{ "LOW_SPEED_LIMIT",			CURLOPT_LOW_SPEED_LIMIT },
	{ "LOW_SPEED_TIME",				CURLOPT_LOW_SPEED_TIME },
	{ "RESUME_FROM",				CURLOPT_RESUME_FROM },
	{ "COOKIE",						CURLOPT_COOKIE },
	{ "HTTPHEADER",					CURLOPT_HTTPHEADER },
	{ "HTTPPOST",					CURLOPT_HTTPPOST },
	{ "SSLCERT",					CURLOPT_SSLCERT },
	{ "KEYPASSWD",					CURLOPT_KEYPASSWD },
	{ "CRLF",						CURLOPT_CRLF },
	{ "QUOTE",						CURLOPT_QUOTE },
	{ "HEADERDATA",					CURLOPT_HEADERDATA },
	{ "COOKIEFILE",					CURLOPT_COOKIEFILE },
	{ "SSLVERSION",					CURLOPT_SSLVERSION },
	{ "TIMECONDITION",				CURLOPT_TIMECONDITION },
	{ "TIMEVALUE",					CURLOPT_TIMEVALUE },
	{ "CUSTOMREQUEST",				CURLOPT_CUSTOMREQUEST },
	{ "STDERR",						CURLOPT_STDERR },
	{ "POSTQUOTE",					CURLOPT_POSTQUOTE },
	{ "OBSOLETE40",					CURLOPT_OBSOLETE40 },
	{ "VERBOSE",					CURLOPT_VERBOSE },
	{ "HEADER",						CURLOPT_HEADER },
	{ "NOPROGRESS",					CURLOPT_NOPROGRESS },
	{ "NOBODY",						CURLOPT_NOBODY },
	{ "FAILONERROR",				CURLOPT_FAILONERROR },
	{ "UPLOAD",						CURLOPT_UPLOAD },
	{ "POST",						CURLOPT_POST },
	{ "DIRLISTONLY",				CURLOPT_DIRLISTONLY },
	{ "APPEND",						CURLOPT_APPEND },
	{ "NETRC",						CURLOPT_NETRC },
	{ "FOLLOWLOCATION",				CURLOPT_FOLLOWLOCATION },
	{ "TRANSFERTEXT",				CURLOPT_TRANSFERTEXT },
	{ "PUT",						CURLOPT_PUT },
	{ "PROGRESSFUNCTION",			CURLOPT_PROGRESSFUNCTION },
	{ "XFERINFODATA",				CURLOPT_XFERINFODATA },
	{ "AUTOREFERER",				CURLOPT_AUTOREFERER },
	{ "PROXYPORT",					CURLOPT_PROXYPORT },
	{ "POSTFIELDSIZE",				CURLOPT_POSTFIELDSIZE },
	{ "HTTPPROXYTUNNEL",			CURLOPT_HTTPPROXYTUNNEL },
	{ "INTERFACE",					CURLOPT_INTERFACE },
	{ "KRBLEVEL",					CURLOPT_KRBLEVEL },
	{ "SSL_VERIFYPEER",				CURLOPT_SSL_VERIFYPEER },
	{ "CAINFO",						CURLOPT_CAINFO },
	{ "MAXREDIRS",					CURLOPT_MAXREDIRS },
	{ "FILETIME",					CURLOPT_FILETIME },
	{ "TELNETOPTIONS",				CURLOPT_TELNETOPTIONS },
	{ "MAXCONNECTS",				CURLOPT_MAXCONNECTS },
	{ "OBSOLETE72",					CURLOPT_OBSOLETE72 },
	{ "FRESH_CONNECT",				CURLOPT_FRESH_CONNECT },
	{ "FORBID_REUSE",				CURLOPT_FORBID_REUSE },
	{ "RANDOM_FILE",				CURLOPT_RANDOM_FILE },
	{ "EGDSOCKET",					CURLOPT_EGDSOCKET },
	{ "CONNECTTIMEOUT",				CURLOPT_CONNECTTIMEOUT },
	{ "HEADERFUNCTION",				CURLOPT_HEADERFUNCTION },
	{ "HTTPGET",					CURLOPT_HTTPGET },
	{ "SSL_VERIFYHOST",				CURLOPT_SSL_VERIFYHOST },
	{ "COOKIEJAR",					CURLOPT_COOKIEJAR },
	{ "SSL_CIPHER_LIST",			CURLOPT_SSL_CIPHER_LIST },
	{ "HTTP_VERSION",				CURLOPT_HTTP_VERSION },
	{ "FTP_USE_EPSV",				CURLOPT_FTP_USE_EPSV },
	{ "SSLCERTTYPE",				CURLOPT_SSLCERTTYPE },
	{ "SSLKEY",						CURLOPT_SSLKEY },
	{ "SSLKEYTYPE",					CURLOPT_SSLKEYTYPE },
	{ "SSLENGINE",					CURLOPT_SSLENGINE },
	{ "SSLENGINE_DEFAULT",			CURLOPT_SSLENGINE_DEFAULT },
	{ "DNS_USE_GLOBAL_CACHE",		CURLOPT_DNS_USE_GLOBAL_CACHE },
	{ "DNS_CACHE_TIMEOUT",			CURLOPT_DNS_CACHE_TIMEOUT },
	{ "PREQUOTE",					CURLOPT_PREQUOTE },
	{ "DEBUGFUNCTION",				CURLOPT_DEBUGFUNCTION },
	{ "DEBUGDATA",					CURLOPT_DEBUGDATA },
	{ "COOKIESESSION",				CURLOPT_COOKIESESSION },
	{ "CAPATH",						CURLOPT_CAPATH },
	{ "BUFFERSIZE",					CURLOPT_BUFFERSIZE },
	{ "NOSIGNAL",					CURLOPT_NOSIGNAL },
	{ "SHARE",						CURLOPT_SHARE },
	{ "PROXYTYPE",					CURLOPT_PROXYTYPE },
	{ "ACCEPT_ENCODING",			CURLOPT_ACCEPT_ENCODING },
	{ "PRIVATE",					CURLOPT_PRIVATE },
	{ "HTTP200ALIASES",				CURLOPT_HTTP200ALIASES },
	{ "UNRESTRICTED_AUTH",			CURLOPT_UNRESTRICTED_AUTH },
	{ "FTP_USE_EPRT",				CURLOPT_FTP_USE_EPRT },
	{ "HTTPAUTH",					CURLOPT_HTTPAUTH },
	{ "SSL_CTX_FUNCTION",			CURLOPT_SSL_CTX_FUNCTION },
	{ "SSL_CTX_DATA",				CURLOPT_SSL_CTX_DATA },
	{ "FTP_CREATE_MISSING_DIRS",	CURLOPT_FTP_CREATE_MISSING_DIRS },
	{ "PROXYAUTH",					CURLOPT_PROXYAUTH },
	{ "FTP_RESPONSE_TIMEOUT",		CURLOPT_FTP_RESPONSE_TIMEOUT },
	{ "IPRESOLVE",					CURLOPT_IPRESOLVE },
	{ "MAXFILESIZE",				CURLOPT_MAXFILESIZE },
	{ "INFILESIZE_LARGE",			CURLOPT_INFILESIZE_LARGE },
	{ "RESUME_FROM_LARGE",			CURLOPT_RESUME_FROM_LARGE },
	{ "MAXFILESIZE_LARGE",			CURLOPT_MAXFILESIZE_LARGE },
	{ "NETRC_FILE",					CURLOPT_NETRC_FILE },
	{ "USE_SSL",					CURLOPT_USE_SSL },
	{ "POSTFIELDSIZE_LARGE",		CURLOPT_POSTFIELDSIZE_LARGE },
	{ "TCP_NODELAY",				CURLOPT_TCP_NODELAY },
	{ "FTPSSLAUTH",					CURLOPT_FTPSSLAUTH },
	{ "IOCTLFUNCTION",				CURLOPT_IOCTLFUNCTION },
	{ "IOCTLDATA",					CURLOPT_IOCTLDATA },
	{ "FTP_ACCOUNT",				CURLOPT_FTP_ACCOUNT },
	{ "COOKIELIST",					CURLOPT_COOKIELIST },
	{ "IGNORE_CONTENT_LENGTH",		CURLOPT_IGNORE_CONTENT_LENGTH },
	{ "FTP_SKIP_PASV_IP",			CURLOPT_FTP_SKIP_PASV_IP },
	{ "FTP_FILEMETHOD",				CURLOPT_FTP_FILEMETHOD },
	{ "LOCALPORT",					CURLOPT_LOCALPORT },
	{ "LOCALPORTRANGE",				CURLOPT_LOCALPORTRANGE },
	{ "CONNECT_ONLY",				CURLOPT_CONNECT_ONLY },
	{ "CONV_FROM_NETWORK_FUNCTION",	CURLOPT_CONV_FROM_NETWORK_FUNCTION },
	{ "CONV_TO_NETWORK_FUNCTION",	CURLOPT_CONV_TO_NETWORK_FUNCTION },
	{ "CONV_FROM_UTF8_FUNCTION",	CURLOPT_CONV_FROM_UTF8_FUNCTION },
	{ "MAX_SEND_SPEED_LARGE",		CURLOPT_MAX_SEND_SPEED_LARGE },
	{ "MAX_RECV_SPEED_LARGE",		CURLOPT_MAX_RECV_SPEED_LARGE },
	{ "FTP_ALTERNATIVE_TO_USER",	CURLOPT_FTP_ALTERNATIVE_TO_USER },
	{ "SOCKOPTFUNCTION",			CURLOPT_SOCKOPTFUNCTION },
	{ "SOCKOPTDATA",				CURLOPT_SOCKOPTDATA },
	{ "SSL_SESSIONID_CACHE",		CURLOPT_SSL_SESSIONID_CACHE },
	{ "SSH_AUTH_TYPES",				CURLOPT_SSH_AUTH_TYPES },
	{ "SSH_PUBLIC_KEYFILE",			CURLOPT_SSH_PUBLIC_KEYFILE },
	{ "SSH_PRIVATE_KEYFILE",		CURLOPT_SSH_PRIVATE_KEYFILE },
	{ "FTP_SSL_CCC",				CURLOPT_FTP_SSL_CCC },
	{ "TIMEOUT_MS",					CURLOPT_TIMEOUT_MS },
	{ "CONNECTTIMEOUT_MS",			CURLOPT_CONNECTTIMEOUT_MS },
	{ "HTTP_TRANSFER_DECODING",		CURLOPT_HTTP_TRANSFER_DECODING },
	{ "HTTP_CONTENT_DECODING",		CURLOPT_HTTP_CONTENT_DECODING },
	{ "NEW_FILE_PERMS",				CURLOPT_NEW_FILE_PERMS },
	{ "NEW_DIRECTORY_PERMS",		CURLOPT_NEW_DIRECTORY_PERMS },
	{ "POSTREDIR",					CURLOPT_POSTREDIR },
	{ "SSH_HOST_PUBLIC_KEY_MD5",	CURLOPT_SSH_HOST_PUBLIC_KEY_MD5 },
	{ "OPENSOCKETFUNCTION",			CURLOPT_OPENSOCKETFUNCTION },
	{ "OPENSOCKETDATA",				CURLOPT_OPENSOCKETDATA },
	{ "COPYPOSTFIELDS",				CURLOPT_COPYPOSTFIELDS },
	{ "PROXY_TRANSFER_MODE",		CURLOPT_PROXY_TRANSFER_MODE },
	{ "SEEKFUNCTION",				CURLOPT_SEEKFUNCTION },
	{ "SEEKDATA",					CURLOPT_SEEKDATA },
	{ "CRLFILE",					CURLOPT_CRLFILE },
	{ "ISSUERCERT",					CURLOPT_ISSUERCERT },
	{ "ADDRESS_SCOPE",				CURLOPT_ADDRESS_SCOPE },
	{ "CERTINFO",					CURLOPT_CERTINFO },
	{ "USERNAME",					CURLOPT_USERNAME },
	{ "PASSWORD",					CURLOPT_PASSWORD },
	{ "PROXYUSERNAME",				CURLOPT_PROXYUSERNAME },
	{ "PROXYPASSWORD",				CURLOPT_PROXYPASSWORD },
	{ "NOPROXY",					CURLOPT_NOPROXY },
	{ "TFTP_BLKSIZE",				CURLOPT_TFTP_BLKSIZE },
	{ "SOCKS5_GSSAPI_SERVICE",		CURLOPT_SOCKS5_GSSAPI_SERVICE },
	{ "SOCKS5_GSSAPI_NEC",			CURLOPT_SOCKS5_GSSAPI_NEC },
	{ "PROTOCOLS",					CURLOPT_PROTOCOLS },
	{ "REDIR_PROTOCOLS",			CURLOPT_REDIR_PROTOCOLS },
	{ "SSH_KNOWNHOSTS",				CURLOPT_SSH_KNOWNHOSTS },
	{ "SSH_KEYFUNCTION",			CURLOPT_SSH_KEYFUNCTION },
	{ "SSH_KEYDATA",				CURLOPT_SSH_KEYDATA },
	{ "MAIL_FROM",					CURLOPT_MAIL_FROM },
	{ "MAIL_RCPT",					CURLOPT_MAIL_RCPT },
	{ "FTP_USE_PRET",				CURLOPT_FTP_USE_PRET },
	{ "RTSP_REQUEST",				CURLOPT_RTSP_REQUEST },
	{ "RTSP_SESSION_ID",			CURLOPT_RTSP_SESSION_ID },
	{ "RTSP_STREAM_URI",			CURLOPT_RTSP_STREAM_URI },
	{ "RTSP_TRANSPORT",				CURLOPT_RTSP_TRANSPORT },
	{ "RTSP_CLIENT_CSEQ",			CURLOPT_RTSP_CLIENT_CSEQ },
	{ "RTSP_SERVER_CSEQ",			CURLOPT_RTSP_SERVER_CSEQ },
	{ "INTERLEAVEDATA",				CURLOPT_INTERLEAVEDATA },
	{ "INTERLEAVEFUNCTION",			CURLOPT_INTERLEAVEFUNCTION },
	{ "WILDCARDMATCH",				CURLOPT_WILDCARDMATCH },
	{ "CHUNK_BGN_FUNCTION",			CURLOPT_CHUNK_BGN_FUNCTION },
	{ "CHUNK_END_FUNCTION",			CURLOPT_CHUNK_END_FUNCTION },
	{ "FNMATCH_FUNCTION",			CURLOPT_FNMATCH_FUNCTION },
	{ "CHUNK_DATA",					CURLOPT_CHUNK_DATA },
	{ "FNMATCH_DATA",				CURLOPT_FNMATCH_DATA },
	{ "RESOLVE",					CURLOPT_RESOLVE },
	{ "TLSAUTH_USERNAME",			CURLOPT_TLSAUTH_USERNAME },
	{ "TLSAUTH_PASSWORD",			CURLOPT_TLSAUTH_PASSWORD },
	{ "TLSAUTH_TYPE",				CURLOPT_TLSAUTH_TYPE },
	{ "TRANSFER_ENCODING",			CURLOPT_TRANSFER_ENCODING },
	{ "CLOSESOCKETFUNCTION",		CURLOPT_CLOSESOCKETFUNCTION },
	{ "CLOSESOCKETDATA",			CURLOPT_CLOSESOCKETDATA },
	{ "GSSAPI_DELEGATION",			CURLOPT_GSSAPI_DELEGATION },
	{ "DNS_SERVERS",				CURLOPT_DNS_SERVERS },
	{ "ACCEPTTIMEOUT_MS",			CURLOPT_ACCEPTTIMEOUT_MS },
	{ "TCP_KEEPALIVE",				CURLOPT_TCP_KEEPALIVE },
	{ "TCP_KEEPIDLE",				CURLOPT_TCP_KEEPIDLE },
	{ "TCP_KEEPINTVL",				CURLOPT_TCP_KEEPINTVL },
	{ "SSL_OPTIONS",				CURLOPT_SSL_OPTIONS },
	{ "MAIL_AUTH",					CURLOPT_MAIL_AUTH },
	{ "SASL_IR",					CURLOPT_SASL_IR },
	{ "XFERINFOFUNCTION",			CURLOPT_XFERINFOFUNCTION },
	{ "XOAUTH2_BEARER",				CURLOPT_XOAUTH2_BEARER },
	{ "DNS_INTERFACE",				CURLOPT_DNS_INTERFACE },
	{ "DNS_LOCAL_IP4",				CURLOPT_DNS_LOCAL_IP4 },
	{ "DNS_LOCAL_IP6",				CURLOPT_DNS_LOCAL_IP6 },
	{ "LOGIN_OPTIONS",				CURLOPT_LOGIN_OPTIONS },
	{ "SSL_ENABLE_NPN",				CURLOPT_SSL_ENABLE_NPN },
	{ "SSL_ENABLE_ALPN",			CURLOPT_SSL_ENABLE_ALPN },
	{ "EXPECT_100_TIMEOUT_MS",		CURLOPT_EXPECT_100_TIMEOUT_MS },
	{ "PROXYHEADER",				CURLOPT_PROXYHEADER },
	{ "HEADEROPT",					CURLOPT_HEADEROPT },
	{ "PINNEDPUBLICKEY",			CURLOPT_PINNEDPUBLICKEY },
	{ "UNIX_SOCKET_PATH",			CURLOPT_UNIX_SOCKET_PATH },
	{ "SSL_VERIFYSTATUS",			CURLOPT_SSL_VERIFYSTATUS },
	{ "SSL_FALSESTART",				CURLOPT_SSL_FALSESTART },
	{ "PATH_AS_IS",					CURLOPT_PATH_AS_IS },
	{ "PROXY_SERVICE_NAME",			CURLOPT_PROXY_SERVICE_NAME },
	{ "SERVICE_NAME",				CURLOPT_SERVICE_NAME },
	{ "PIPEWAIT",					CURLOPT_PIPEWAIT },
	{ "DEFAULT_PROTOCOL",			CURLOPT_DEFAULT_PROTOCOL },
	{ "STREAM_WEIGHT",				CURLOPT_STREAM_WEIGHT },
	{ "STREAM_DEPENDS",				CURLOPT_STREAM_DEPENDS },
	{ "STREAM_DEPENDS_E",			CURLOPT_STREAM_DEPENDS_E },
	{ "TFTP_NO_OPTIONS",			CURLOPT_TFTP_NO_OPTIONS },
	{ "CONNECT_TO",					CURLOPT_CONNECT_TO },
	{ "TCP_FASTOPEN",				CURLOPT_TCP_FASTOPEN },
	{ "KEEP_SENDING_ON_ERROR",		CURLOPT_KEEP_SENDING_ON_ERROR },
	{ "PROXY_CAINFO",				CURLOPT_PROXY_CAINFO },
	{ "PROXY_CAPATH",				CURLOPT_PROXY_CAPATH },
	{ "PROXY_SSL_VERIFYPEER",		CURLOPT_PROXY_SSL_VERIFYPEER },
	{ "PROXY_SSL_VERIFYHOST",		CURLOPT_PROXY_SSL_VERIFYHOST },
	{ "PROXY_SSLVERSION",			CURLOPT_PROXY_SSLVERSION },
	{ "PROXY_TLSAUTH_USERNAME",		CURLOPT_PROXY_TLSAUTH_USERNAME },
	{ "PROXY_TLSAUTH_PASSWORD",		CURLOPT_PROXY_TLSAUTH_PASSWORD },
	{ "PROXY_TLSAUTH_TYPE",			CURLOPT_PROXY_TLSAUTH_TYPE },
	{ "PROXY_SSLCERT",				CURLOPT_PROXY_SSLCERT },
	{ "PROXY_SSLCERTTYPE",			CURLOPT_PROXY_SSLCERTTYPE },
	{ "PROXY_SSLKEY",				CURLOPT_PROXY_SSLKEY },
	{ "PROXY_SSLKEYTYPE",			CURLOPT_PROXY_SSLKEYTYPE },
	{ "PROXY_KEYPASSWD",			CURLOPT_PROXY_KEYPASSWD },
	{ "PROXY_SSL_CIPHER_LIST",		CURLOPT_PROXY_SSL_CIPHER_LIST },
	{ "PROXY_CRLFILE",				CURLOPT_PROXY_CRLFILE },
	{ "PROXY_SSL_OPTIONS",			CURLOPT_PROXY_SSL_OPTIONS },
	{ "PRE_PROXY",					CURLOPT_PRE_PROXY },
	{ "PROXY_PINNEDPUBLICKEY",		CURLOPT_PROXY_PINNEDPUBLICKEY },
	{ "ABSTRACT_UNIX_SOCKET",		CURLOPT_ABSTRACT_UNIX_SOCKET },
	{ "SUPPRESS_CONNECT_HEADERS",	CURLOPT_SUPPRESS_CONNECT_HEADERS },
	{ "REQUEST_TARGET",				CURLOPT_REQUEST_TARGET },
	{ "SOCKS5_AUTH",				CURLOPT_SOCKS5_AUTH },
	{ "SSH_COMPRESSION",			CURLOPT_SSH_COMPRESSION },
	{ "MIMEPOST",					CURLOPT_MIMEPOST },
	{ "TIMEVALUE_LARGE",			CURLOPT_TIMEVALUE_LARGE },
	{ "HAPPY_EYEBALLS_TIMEOUT_MS",	CURLOPT_HAPPY_EYEBALLS_TIMEOUT_MS },
	{ "RESOLVER_START_FUNCTION",	CURLOPT_RESOLVER_START_FUNCTION },
	{ "RESOLVER_START_DATA",		CURLOPT_RESOLVER_START_DATA },
	{ "HAPROXYPROTOCOL",			CURLOPT_HAPROXYPROTOCOL },
	{ "DNS_SHUFFLE_ADDRESSES",		CURLOPT_DNS_SHUFFLE_ADDRESSES },
	{ "TLS13_CIPHERS",				CURLOPT_TLS13_CIPHERS },
	{ "PROXY_TLS13_CIPHERS",		CURLOPT_PROXY_TLS13_CIPHERS },
	{ "DISALLOW_USERNAME_IN_URL",	CURLOPT_DISALLOW_USERNAME_IN_URL },
	{ "DOH_URL",					CURLOPT_DOH_URL },
	{ "UPLOAD_BUFFERSIZE",			CURLOPT_UPLOAD_BUFFERSIZE },
	{ "UPKEEP_INTERVAL_MS",			CURLOPT_UPKEEP_INTERVAL_MS },
	{ "CURLU",						CURLOPT_CURLU },
	{ "TRAILERFUNCTION",			CURLOPT_TRAILERFUNCTION },
	{ "TRAILERDATA",				CURLOPT_TRAILERDATA },
	{ "HTTP09_ALLOWED",				CURLOPT_HTTP09_ALLOWED },
	{ "ALTSVC_CTRL",				CURLOPT_ALTSVC_CTRL },
	{ "ALTSVC",						CURLOPT_ALTSVC },
	{ "MAXAGE_CONN",				CURLOPT_MAXAGE_CONN },
	{ "SASL_AUTHZID",				CURLOPT_SASL_AUTHZID },
	{ "MAIL_RCPT_ALLLOWFAILS",		CURLOPT_MAIL_RCPT_ALLLOWFAILS },
	{ "SSLCERT_BLOB",				CURLOPT_SSLCERT_BLOB },
	{ "SSLKEY_BLOB",				CURLOPT_SSLKEY_BLOB },
	{ "PROXY_SSLCERT_BLOB",			CURLOPT_PROXY_SSLCERT_BLOB },
	{ "PROXY_SSLKEY_BLOB",			CURLOPT_PROXY_SSLKEY_BLOB },
	{ "ISSUERCERT_BLOB",			CURLOPT_ISSUERCERT_BLOB },
	{ "PROXY_ISSUERCERT",			CURLOPT_PROXY_ISSUERCERT },
	{ "PROXY_ISSUERCERT_BLOB",		CURLOPT_PROXY_ISSUERCERT_BLOB },
	{ "SSL_EC_CURVES",				CURLOPT_SSL_EC_CURVES },
	// Macro
	{ "ENCODING",					CURLOPT_ENCODING },
	{ "FILE",						CURLOPT_FILE },
	{ "INFILE",						CURLOPT_INFILE },
	{ "WRITEHEADER",				CURLOPT_WRITEHEADER },
	{ "WRITEINFO",					CURLOPT_WRITEINFO },
	{ "CLOSEPOLICY",				CURLOPT_CLOSEPOLICY },
	{ "PROGRESSDATA",				CURLOPT_PROGRESSDATA },
	{ "SERVER_RESPONSE_TIMEOUT",	CURLOPT_SERVER_RESPONSE_TIMEOUT },
	{ "POST301",					CURLOPT_POST301 },
	{ "SSLKEYPASSWD",				CURLOPT_SSLKEYPASSWD },
	{ "FTPAPPEND",					CURLOPT_FTPAPPEND },
	{ "FTPLISTONLY",				CURLOPT_FTPLISTONLY },
	{ "FTP_SSL",					CURLOPT_FTP_SSL },
	{ "SSLCERTPASSWD",				CURLOPT_SSLCERTPASSWD },
	{ "KRB4LEVEL",					CURLOPT_KRB4LEVEL },
	{ "RTSPHEADER",					CURLOPT_RTSPHEADER },
};

void Opt::Bootup()
{
	for (size_t i = 0; i < Gurax_ArraySizeOf(_pairTbl); i++) {
		_map[Symbol::Add(_pairTbl[i].name)] = _pairTbl[i].option;
	}
}

Gurax_EndModuleScope(curl)
