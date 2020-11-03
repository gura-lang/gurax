//==============================================================================
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
			if (!value.IsInstanceOf(VTYPE_List)) {
				Error::Issue(ErrorType::TypeError, "the option accepts List value");
				return false;
			}
			curl_slist* slist = nullptr;
			for (const Value* pValue : Value_List::GetValueOwner(value)) {
				if (!pValue->IsInstanceOf(VTYPE_String)) {
					Error::Issue(ErrorType::TypeError, "the option accepts String value");
					return false;
				}
				slist = curl_slist_append(slist, Value_String::GetString(*pValue));
			}
			code = curl_easy_setopt(_curl, option, slist);
			curl_slist_free_all(slist);
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
	{ "WRITEDATA", CURLOPT_WRITEDATA },
};

void Opt::Bootup()
{
}

Gurax_EndModuleScope(curl)
