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
	//RefPtr<CURL> curl(new CURL());
	//return argument.ReturnValue(processor, new Value_CURL(curl.release()));
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// curl.CURL#info
Gurax_DeclareProperty_R(CURL, info)
{
	Declare(VTYPE_Info, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(CURL, info)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Info(valueThis.GetInfo().Reference());
}

// curl.CURL#opt
Gurax_DeclareProperty_R(CURL, opt)
{
	Declare(VTYPE_Opt, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(CURL, opt)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Opt(valueThis.GetOpt().Reference());
}

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

// curl.CURL#streamHeader
Gurax_DeclareProperty_RW(CURL, streamHeader)
{
	Declare(VTYPE_Stream, Flag::StreamW);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(CURL, streamHeader)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Stream(valueThis.GetStreamHeader().Reference());
}

Gurax_ImplementPropertySetter(CURL, streamHeader)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.SetStreamHeader(Value_Stream::GetStream(value).Reference());
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
	Assign(Gurax_CreateProperty(CURL, info));
	Assign(Gurax_CreateProperty(CURL, opt));
	Assign(Gurax_CreateProperty(CURL, streamDst));
	Assign(Gurax_CreateProperty(CURL, streamSrc));
	Assign(Gurax_CreateProperty(CURL, streamHeader));
}

//------------------------------------------------------------------------------
// Value_CURL
//------------------------------------------------------------------------------
VType& Value_CURL::vtype = VTYPE_CURL;

Value_CURL::Value_CURL(Processor* pProcessor, CURL* curl, VType& vtype) :
		Value_Object(vtype), _pProcessor(pProcessor), _curl(curl),
		_pInfo(new Info(curl)), _pOpt(new Opt(curl)),
		_pStreamWrite(Stream::COut->Reference()),
		_pStreamRead(Stream::CIn->Reference())
{
	SetupCallback();
}

void Value_CURL::SetupCallback()
{
	curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, Callback_WRITE);
	curl_easy_setopt(_curl, CURLOPT_READFUNCTION, Callback_READ);
	curl_easy_setopt(_curl, CURLOPT_HEADERFUNCTION, Callback_HEADER);
	curl_easy_setopt(_curl, CURLOPT_WRITEDATA, this);
	curl_easy_setopt(_curl, CURLOPT_READDATA, this);
	curl_easy_setopt(_curl, CURLOPT_HEADERDATA, this);
}

String Value_CURL::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "curl.CURL");
}

size_t Value_CURL::Callback_WRITE(char* ptr, size_t size, size_t nitems, void* userdata)
{
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_WRITE) {
		//RefPtr<Memory> pMemory(new Memory_Sloth(buffer, nitems));
		//pThis->pFunc_WRITE->EvalEasy(pThis->GetProcesor(), new Value_Pointer(pMemory.release()));
		return 0;
	} else {
		return (!pThis->IsValidStreamWrite() ||
			pThis->GetStreamWrite().Write(ptr, size * nitems))? size * nitems : 0;
	}
}

size_t Value_CURL::Callback_READ(char* ptr, size_t size, size_t nitems, void* userdata)
{
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_READ) {
		return 0;
	} else {
		return pThis->IsValidStreamRead()?
			pThis->GetStreamRead().Read(ptr, size * nitems) : 0;
	}
}

curlioerr Value_CURL::Callback_PROGRESS(CURL* curl, int cmd, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_PROGRESS) {
	} else {
	}
#endif
	return CURLIOE_OK;
}

size_t Value_CURL::Callback_HEADER(char* ptr, size_t size,   size_t nitems, void* userdata)
{
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_HEADER) {
		//RefPtr<Memory> pMemory(new Memory_Sloth(buffer, nitems));
		//pThis->GetOpt().pFunc_WRITE->EvalEasy(pThis->GetProcesor(), new Value_Pointer(pMemory.release()));
		return 0;
	} else {
		return (!pThis->IsValidStreamHeader() ||
			pThis->GetStreamHeader().Write(ptr, size * nitems))? size * nitems : 0;
	}
}

int Value_CURL::Callback_DEBUG(CURL* curl, curl_infotype type, char* data, size_t size, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_DEBUG) {
	} else {
	}
#endif
	return 0;
}

CURLcode Value_CURL::Callback_SSL_CTX(CURL* curl, void* ssl_ctx, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_SSL_CTX) {
	} else {
	}
#endif
	return CURLE_OK;
}

curlioerr Value_CURL::Callback_IOCTL(CURL* curl, int cmd, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_IOCTL) {
	} else {
	}
#endif
	return CURLIOE_OK;
}

CURLcode Value_CURL::Callback_CONV_FROM_NETWORK(char* ptr, size_t length)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_CONV_FROM_NETWORK) {
	} else {
	}
#endif
	return CURLE_OK;
}

CURLcode Value_CURL::Callback_CONV_TO_NETWORK(char* ptr, size_t length)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_CONV_TO_NETWORK) {
	} else {
	}
#endif
	return CURLE_OK;
}

CURLcode Value_CURL::Callback_CONV_FROM_UTF8(char* ptr, size_t length)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_CONV_FROM_UTF8) {
	} else {
	}
#endif
	return CURLE_OK;
}

int Value_CURL::Callback_SOCKOPT(void* userdata, curl_socket_t curlfd, curlsocktype purpose)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_SOCKOPT) {
	} else {
	}
#endif
	return 0;
}

curl_socket_t Value_CURL::Callback_OPENSOCKET(void* userdata, curlsocktype purpose, curl_sockaddr* address)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_OPENSOCKET) {
	} else {
	}
#endif
	return 0;
}

int Value_CURL::Callback_SEEK(void* userdata, curl_off_t offset, int origin)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_SEEK) {
	} else {
	}
#endif
	return 0;
}

int Value_CURL::Callback_SSH_KEY(CURL* curl, const curl_khkey* knownkey, const curl_khkey* foundkey, curl_khmatch match, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_SSH_KEY) {
	} else {
	}
#endif
	return 0;
}

size_t Value_CURL::Callback_INTERLEAVE(void* ptr, size_t size, size_t nitems, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_INTERLEAVE) {
	} else {
	}
#endif
	return 0;
}

long Value_CURL::Callback_CHUNK_BGN(const void* transfer_info, void* userdata, int remains)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_CHUNK_BGN) {
	} else {
	}
#endif
	return 0;
}

long Value_CURL::Callback_CHUNK_END(void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_CHUNK_END) {
	} else {
	}
#endif
	return 0;
}

int Value_CURL::Callback_FNMATCH(void* userdata, const char* pattern, const char* string)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_FNMATCH) {
	} else {
	}
#endif
	return 0;
}

int Value_CURL::Callback_CLOSESOCKET(void* userdata, curl_socket_t item)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_CLOSESOCKET) {
	} else {
	}
#endif
	return 0;
}

int Value_CURL::Callback_XFERINFO(void* userdata, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_XFERINFO) {
	} else {
	}
#endif
	return 0;
}

int Value_CURL::Callback_RESOLVER_START(void* resover_state, void* reserved, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_RESOLVER_START) {
	} else {
	}
#endif
	return 0;
}

int Value_CURL::Callback_TRAILER(struct curl_slist** list, void* userdata)
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->GetOpt().pFunc_TRAILER) {
	} else {
	}
#endif
	return 0;
}

Gurax_EndModuleScope(curl)
