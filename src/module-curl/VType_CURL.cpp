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
// Implementation of method
//-----------------------------------------------------------------------------
// curl.CURL#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(CURL, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(CURL, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// curl.CURL#streamR
Gurax_DeclareProperty_RW(CURL, streamR)
{
	Declare(VTYPE_Stream, Flag::None);
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
	Declare(VTYPE_Stream, Flag::None);
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
	// Assignment of method
	Assign(Gurax_CreateMethod(CURL, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(CURL, streamR));
	Assign(Gurax_CreateProperty(CURL, streamW));
}

//------------------------------------------------------------------------------
// Value_CURL
//------------------------------------------------------------------------------
VType& Value_CURL::vtype = VTYPE_CURL;

Value_CURL::Value_CURL(CURL* pCURL, VType& vtype) :
		Value_Object(vtype), _pCURL(pCURL),
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

size_t Value_CURL::Callback_WRITE(char* ptr, size_t size, size_t nmemb, void* userdata)
{
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_WRITE) {
		//RefPtr<Memory> pMemory(new Memory_Sloth(ptr, nmemb));
		//pThis->pFunc_WRITE->EvalEasy(pThis->GetProcesor(), new Value_Pointer(pMemory.release()));
		return 0;
	} else {
		return pThis->GetStreamWrite().Write(ptr, size * nmemb)? size * nmemb : 0;
	}
}

size_t Value_CURL::Callback_READ(char* ptr, size_t size, size_t nmemb, void* userdata)
{
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_READ) {
		return 0;
	} else {
		return pThis->GetStreamRead().Read(ptr, size * nmemb);
	}
}

void Value_CURL::Callback_PROGRESS()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_PROGRESS) {
	} else {
	}
#endif
}

void Value_CURL::Callback_HEADER()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_HEADER) {
	} else {
	}
#endif
}

void Value_CURL::Callback_DEBUG()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_DEBUG) {
	} else {
	}
#endif
}

void Value_CURL::Callback_SSL_CTX()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_SSL_CTX) {
	} else {
	}
#endif
}

void Value_CURL::Callback_IOCTL()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_IOCTL) {
	} else {
	}
#endif
}

void Value_CURL::Callback_CONV_FROM_NETWORK()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_CONV_FROM_NETWORK) {
	} else {
	}
#endif
}

void Value_CURL::Callback_CONV_TO_NETWORK()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_CONV_TO_NETWORK) {
	} else {
	}
#endif
}

void Value_CURL::Callback_CONV_FROM_UTF8()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_CONV_FROM_UTF8) {
	} else {
	}
#endif
}

void Value_CURL::Callback_SOCKOPT()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_SOCKOPT) {
	} else {
	}
#endif
}

void Value_CURL::Callback_OPENSOCKET()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_OPENSOCKET) {
	} else {
	}
#endif
}

void Value_CURL::Callback_SEEK()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_SEEK) {
	} else {
	}
#endif
}

void Value_CURL::Callback_SSH_KEY()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_SSH_KEY) {
	} else {
	}
#endif
}

void Value_CURL::Callback_INTERLEAVE()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_INTERLEAVE) {
	} else {
	}
#endif
}

void Value_CURL::Callback_CHUNK_BGN()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_CHUNK_BGN) {
	} else {
	}
#endif
}

void Value_CURL::Callback_CHUNK_END()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_CHUNK_END) {
	} else {
	}
#endif
}

void Value_CURL::Callback_FNMATCH()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_FNMATCH) {
	} else {
	}
#endif
}

void Value_CURL::Callback_CLOSESOCKET()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_CLOSESOCKET) {
	} else {
	}
#endif
}

void Value_CURL::Callback_XFERINFO()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_XFERINFO) {
	} else {
	}
#endif
}

void Value_CURL::Callback_RESOLVER_START()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_RESOLVER_START) {
	} else {
	}
#endif
}

void Value_CURL::Callback_TRAILER()
{
#if 0
	Value_CURL* pThis = reinterpret_cast<Value_CURL*>(userdata);
	if (pThis->pFunc_TRAILER) {
	} else {
	}
#endif
}

Gurax_EndModuleScope(curl)
