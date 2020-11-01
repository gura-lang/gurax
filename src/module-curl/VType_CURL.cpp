//==============================================================================
// VType_CURL.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// curl.CURL() {block?}
Gurax_DeclareConstructor(CURL)
{
	Declare(VTYPE_CURL, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `curl.CURL` instance.");
}

Gurax_ImplementConstructor(CURL)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	//RefPtr<CURL> pCURL(new CURL());
	//return argument.ReturnValue(processor, new Value_CURL(pCURL.release()));
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// curl.CURL#streamSrc
Gurax_DeclareProperty_RW(CURL, streamSrc)
{
	Declare(VTYPE_Stream, Flag::StreamR);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(CURL, streamSrc)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Stream(valueThis.GetStreamRead().Reference());
}

Gurax_ImplementPropertySetter(CURL, streamSrc)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.SetStreamRead(Value_Stream::GetStream(value).Reference());
}

// curl.CURL#streamDst
Gurax_DeclareProperty_RW(CURL, streamDst)
{
	Declare(VTYPE_Stream, Flag::StreamW);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(CURL, streamDst)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Stream(valueThis.GetStreamWrite().Reference());
}

Gurax_ImplementPropertySetter(CURL, streamDst)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.SetStreamWrite(Value_Stream::GetStream(value).Reference());
}

//------------------------------------------------------------------------------
// VType_CURL
//------------------------------------------------------------------------------
VType_CURL VTYPE_CURL("CURL");

void VType_CURL::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(CURL));
	// Assignment of property
	Assign(Gurax_CreateProperty(CURL, streamSrc));
	Assign(Gurax_CreateProperty(CURL, streamDst));
}

//------------------------------------------------------------------------------
// Value_CURL
//------------------------------------------------------------------------------
VType& Value_CURL::vtype = VTYPE_CURL;

Value_CURL::Value_CURL(Processor* pProcessor, CURL* pCURL, VType& vtype) :
		Value_Object(vtype), _pProcessor(pProcessor), _pCURL(pCURL),
		_pStreamWrite(Stream::COut->Reference()),
		_pStreamRead(Stream::CIn->Reference()),
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
		pValue_TRAILER(Value::nil()) {
	SetupCallback();
}

void Value_CURL::SetupCallback()
{
	curl_easy_setopt(_pCURL, CURLOPT_WRITEFUNCTION, Callback_WRITE);
	curl_easy_setopt(_pCURL, CURLOPT_READFUNCTION, Callback_READ);
	curl_easy_setopt(_pCURL, CURLOPT_WRITEDATA, this);
	curl_easy_setopt(_pCURL, CURLOPT_READDATA, this);
}

bool Value_CURL::SetOpt(CURLoption option, const Value& value, CURLcode* pCode)
{
	CURL* curl = GetEntityPtr();
	long optType = static_cast<long>(option) / 10000 * 10000;
	CURLcode& code = *pCode;
	code = CURLE_OK;
	if (optType == CURLOPTTYPE_LONG) {
		if (!value.IsInstanceOf(VTYPE_Number)) {
			Error::Issue(ErrorType::TypeError, "the option accepts Number value");
			return false;
		}
		code = curl_easy_setopt(curl, option, Value_Number::GetNumber<long>(value));
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
			code = curl_easy_setopt(curl, option, slist);
			curl_slist_free_all(slist);
			break;
		}
		default: {
			if (!value.IsInstanceOf(VTYPE_String)) {
				Error::Issue(ErrorType::TypeError, "the option accepts String value");
				return false;
			}
			code = curl_easy_setopt(curl, option, Value_String::GetString(value));
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
			curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, Value_CURL::Callback_PROGRESS);
			curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, this);
			pFunc_PROGRESS.reset(func.Reference());
			break;
		}
		case CURLOPT_HEADERFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, Value_CURL::Callback_HEADER);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);
			pFunc_HEADER.reset(func.Reference());
			break;
		}
		case CURLOPT_DEBUGFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, Value_CURL::Callback_DEBUG);
			curl_easy_setopt(curl, CURLOPT_DEBUGDATA, this);
			pFunc_DEBUG.reset(func.Reference());
			break;
		}
		case CURLOPT_SSL_CTX_FUNCTION: {
			curl_easy_setopt(curl, CURLOPT_SSL_CTX_FUNCTION, Value_CURL::Callback_SSL_CTX);
			curl_easy_setopt(curl, CURLOPT_SSL_CTX_DATA, this);
			pFunc_SSL_CTX.reset(func.Reference());
			break;
		}
		case CURLOPT_IOCTLFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_IOCTLFUNCTION, Value_CURL::Callback_IOCTL);
			curl_easy_setopt(curl, CURLOPT_IOCTLDATA, this);
			pFunc_IOCTL.reset(func.Reference());
			break;
		}
		case CURLOPT_CONV_FROM_NETWORK_FUNCTION: {
			curl_easy_setopt(curl, CURLOPT_CONV_FROM_NETWORK_FUNCTION, Value_CURL::Callback_CONV_FROM_NETWORK);
			//curl_easy_setopt(curl, CURLOPT_CONV_FROM_NETWORK_DATA, this);
			pFunc_CONV_FROM_NETWORK.reset(func.Reference());
			break;
		}
		case CURLOPT_CONV_TO_NETWORK_FUNCTION: {
			curl_easy_setopt(curl, CURLOPT_CONV_TO_NETWORK_FUNCTION, Value_CURL::Callback_CONV_TO_NETWORK);
			//curl_easy_setopt(curl, CURLOPT_CONV_TO_NETWORK_DATA, this);
			pFunc_CONV_TO_NETWORK.reset(func.Reference());
			break;
		}
		case CURLOPT_CONV_FROM_UTF8_FUNCTION: {
			curl_easy_setopt(curl, CURLOPT_CONV_FROM_UTF8_FUNCTION, Value_CURL::Callback_CONV_FROM_UTF8);
			//curl_easy_setopt(curl, CURLOPT_CONV_FROM_UTF8_DATA, this);
			pFunc_CONV_FROM_UTF8.reset(func.Reference());
			break;
		}
		case CURLOPT_SOCKOPTFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_SOCKOPTFUNCTION, Value_CURL::Callback_SOCKOPT);
			curl_easy_setopt(curl, CURLOPT_SOCKOPTDATA, this);
			pFunc_SOCKOPT.reset(func.Reference());
			break;
		}
		case CURLOPT_OPENSOCKETFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_OPENSOCKETFUNCTION, Value_CURL::Callback_OPENSOCKET);
			curl_easy_setopt(curl, CURLOPT_OPENSOCKETDATA, this);
			pFunc_OPENSOCKET.reset(func.Reference());
			break;
		}
		case CURLOPT_SEEKFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_SEEKFUNCTION, Value_CURL::Callback_SEEK);
			curl_easy_setopt(curl, CURLOPT_SEEKDATA, this);
			pFunc_SEEK.reset(func.Reference());
			break;
		}
		case CURLOPT_SSH_KEYFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_SSH_KEYFUNCTION, Value_CURL::Callback_SSH_KEY);
			curl_easy_setopt(curl, CURLOPT_SSH_KEYDATA, this);
			pFunc_SSH_KEY.reset(func.Reference());
			break;
		}
		case CURLOPT_INTERLEAVEFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_INTERLEAVEFUNCTION, Value_CURL::Callback_INTERLEAVE);
			curl_easy_setopt(curl, CURLOPT_INTERLEAVEDATA, this);
			pFunc_INTERLEAVE.reset(func.Reference());
			break;
		}
		case CURLOPT_CHUNK_BGN_FUNCTION: {
			curl_easy_setopt(curl, CURLOPT_CHUNK_BGN_FUNCTION, Value_CURL::Callback_CHUNK_BGN);
			//curl_easy_setopt(curl, CURLOPT_CHUNK_BGN_DATA, this);
			pFunc_CHUNK_BGN.reset(func.Reference());
			break;
		}
		case CURLOPT_CHUNK_END_FUNCTION: {
			curl_easy_setopt(curl, CURLOPT_CHUNK_END_FUNCTION, Value_CURL::Callback_CHUNK_END);
			//curl_easy_setopt(curl, CURLOPT_CHUNK_END_DATA, this);
			pFunc_CHUNK_END.reset(func.Reference());
			break;
		}
		case CURLOPT_FNMATCH_FUNCTION: {
			curl_easy_setopt(curl, CURLOPT_FNMATCH_FUNCTION, Value_CURL::Callback_FNMATCH);
			curl_easy_setopt(curl, CURLOPT_FNMATCH_DATA, this);
			pFunc_FNMATCH.reset(func.Reference());
			break;
		}
		case CURLOPT_CLOSESOCKETFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_CLOSESOCKETFUNCTION, Value_CURL::Callback_CLOSESOCKET);
			curl_easy_setopt(curl, CURLOPT_CLOSESOCKETDATA, this);
			pFunc_CLOSESOCKET.reset(func.Reference());
			break;
		}
		case CURLOPT_XFERINFOFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, Value_CURL::Callback_XFERINFO);
			curl_easy_setopt(curl, CURLOPT_XFERINFODATA, this);
			pFunc_XFERINFO.reset(func.Reference());
			break;
		}
		case CURLOPT_RESOLVER_START_FUNCTION: {
			curl_easy_setopt(curl, CURLOPT_RESOLVER_START_FUNCTION, Value_CURL::Callback_RESOLVER_START);
			curl_easy_setopt(curl, CURLOPT_RESOLVER_START_DATA, this);
			pFunc_RESOLVER_START.reset(func.Reference());
			break;
		}
		case CURLOPT_TRAILERFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_TRAILERFUNCTION, Value_CURL::Callback_TRAILER);
			curl_easy_setopt(curl, CURLOPT_TRAILERDATA, this);
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
		code = curl_easy_setopt(curl, option, Value_Number::GetNumber<size_t>(value));
	} else if (optType == CURLOPTTYPE_BLOB) {

	}
	return true;
}

Value* Value_CURL::GetInfo(CURLINFO info)
{
	CURL* curl = GetEntityPtr();
	RefPtr<Value> pValueRtn(Value::nil());
	long infoType = info & CURLINFO_TYPEMASK;
	if (infoType == CURLINFO_STRING) {
		const char* value;
		curl_easy_getinfo(curl, info, &value);
		pValueRtn.reset(new Value_String(value));
	} else if (infoType == CURLINFO_LONG) {
		long value;
		curl_easy_getinfo(curl, info, &value);
		pValueRtn.reset(new Value_Number(value));
	} else if (infoType == CURLINFO_DOUBLE) {
		double value;
		curl_easy_getinfo(curl, info, &value);
		pValueRtn.reset(new Value_Number(value));
	} else if (infoType == CURLINFO_SLIST) {
		curl_slist* slist = nullptr;
		curl_easy_getinfo(curl, info, &slist);
		RefPtr<ValueOwner> pValues(CreateValueOwnerFromSList(slist));
		curl_free(slist);
		pValueRtn.reset(new Value_List(VTYPE_String, pValues.release()));
	} else if (infoType == CURLINFO_PTR) {
	} else if (infoType == CURLINFO_SOCKET) {
	} else if (infoType == CURLINFO_OFF_T) {
		curl_off_t value;
		curl_easy_getinfo(curl, info, &value);
		pValueRtn.reset(new Value_Number(value));
	}
	return pValueRtn.release();
}

String Value_CURL::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "curl.CURL");
}

size_t Value_CURL::Callback_WRITE(char* ptr, size_t size, size_t nitems, void* userdata)
{
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_WRITE) {
		//RefPtr<Memory> pMemory(new Memory_Sloth(buffer, nitems));
		//pThis->pFunc_WRITE->EvalEasy(pThis->GetProcesor(), new Value_Pointer(pMemory.release()));
		return 0;
	} else {
		return pThis->GetStreamWrite().Write(ptr, size * nitems)? size * nitems : 0;
	}
}

size_t Value_CURL::Callback_READ(char* ptr, size_t size, size_t nitems, void* userdata)
{
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_READ) {
		return 0;
	} else {
		return pThis->GetStreamRead().Read(ptr, size * nitems);
	}
}

curlioerr Value_CURL::Callback_PROGRESS(CURL* curl, int cmd, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_PROGRESS) {
	} else {
	}
#endif
	return CURLIOE_OK;
}

size_t Value_CURL::Callback_HEADER(char* buffer, size_t size,   size_t nitems, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_HEADER) {
	} else {
	}
#endif
	return 0;
}

int Value_CURL::Callback_DEBUG(CURL* curl, curl_infotype type, char* data, size_t size, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_DEBUG) {
	} else {
	}
#endif
	return 0;
}

CURLcode Value_CURL::Callback_SSL_CTX(CURL* curl, void* ssl_ctx, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_SSL_CTX) {
	} else {
	}
#endif
	return CURLE_OK;
}

curlioerr Value_CURL::Callback_IOCTL(CURL* curl, int cmd, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_IOCTL) {
	} else {
	}
#endif
	return CURLIOE_OK;
}

CURLcode Value_CURL::Callback_CONV_FROM_NETWORK(char* ptr, size_t length)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_CONV_FROM_NETWORK) {
	} else {
	}
#endif
	return CURLE_OK;
}

CURLcode Value_CURL::Callback_CONV_TO_NETWORK(char* ptr, size_t length)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_CONV_TO_NETWORK) {
	} else {
	}
#endif
	return CURLE_OK;
}

CURLcode Value_CURL::Callback_CONV_FROM_UTF8(char* ptr, size_t length)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_CONV_FROM_UTF8) {
	} else {
	}
#endif
	return CURLE_OK;
}

int Value_CURL::Callback_SOCKOPT(void* userdata, curl_socket_t curlfd, curlsocktype purpose)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_SOCKOPT) {
	} else {
	}
#endif
	return 0;
}

curl_socket_t Value_CURL::Callback_OPENSOCKET(void* userdata, curlsocktype purpose, curl_sockaddr* address)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_OPENSOCKET) {
	} else {
	}
#endif
	return 0;
}

int Value_CURL::Callback_SEEK(void* userdata, curl_off_t offset, int origin)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_SEEK) {
	} else {
	}
#endif
	return 0;
}

int Value_CURL::Callback_SSH_KEY(CURL* curl, const curl_khkey* knownkey, const curl_khkey* foundkey, curl_khmatch match, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_SSH_KEY) {
	} else {
	}
#endif
	return 0;
}

size_t Value_CURL::Callback_INTERLEAVE(void* ptr, size_t size, size_t nitems, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_INTERLEAVE) {
	} else {
	}
#endif
	return 0;
}

long Value_CURL::Callback_CHUNK_BGN(const void* transfer_info, void* userdata, int remains)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_CHUNK_BGN) {
	} else {
	}
#endif
	return 0;
}

long Value_CURL::Callback_CHUNK_END(void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_CHUNK_END) {
	} else {
	}
#endif
	return 0;
}

int Value_CURL::Callback_FNMATCH(void* userdata, const char* pattern, const char* string)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_FNMATCH) {
	} else {
	}
#endif
	return 0;
}

int Value_CURL::Callback_CLOSESOCKET(void* userdata, curl_socket_t item)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_CLOSESOCKET) {
	} else {
	}
#endif
	return 0;
}

int Value_CURL::Callback_XFERINFO(void* userdata, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_XFERINFO) {
	} else {
	}
#endif
	return 0;
}

int Value_CURL::Callback_RESOLVER_START(void* resover_state, void* reserved, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_RESOLVER_START) {
	} else {
	}
#endif
	return 0;
}

int Value_CURL::Callback_TRAILER(struct curl_slist** list, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_TRAILER) {
	} else {
	}
#endif
	return 0;
}

Gurax_EndModuleScope(curl)
