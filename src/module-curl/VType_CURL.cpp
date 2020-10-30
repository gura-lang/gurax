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
// curl.CURL#streamR
Gurax_DeclareProperty_RW(CURL, streamR)
{
	Declare(VTYPE_Stream, Flag::StreamR);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(CURL, streamR)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Stream(valueThis.GetStreamRead().Reference());
}

Gurax_ImplementPropertySetter(CURL, streamR)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.SetStreamRead(Value_Stream::GetStream(value).Reference());
}

// curl.CURL#streamW
Gurax_DeclareProperty_RW(CURL, streamW)
{
	Declare(VTYPE_Stream, Flag::StreamW);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(CURL, streamW)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Stream(valueThis.GetStreamWrite().Reference());
}

Gurax_ImplementPropertySetter(CURL, streamW)
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
	Assign(Gurax_CreateProperty(CURL, streamR));
	Assign(Gurax_CreateProperty(CURL, streamW));
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
