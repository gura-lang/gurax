//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

// curl.curl_easy_init()
Gurax_DeclareFunctionAlias(curl_easy_init_gurax, "curl_easy_init")
{
	Declare(VTYPE_CURL, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_easy_init_gurax, processor_gurax, argument_gurax)
{
	// Function body
	CURL* rtn = curl_easy_init();
	if (!rtn) return Value::nil();
	return new Value_CURL(rtn);
}

// curl.curl_easy_setopt(curl:CURL, option:Number, value:Any)
Gurax_DeclareFunctionAlias(curl_easy_setopt_gurax, "curl_easy_setopt")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("curl", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	DeclareArg("option", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_easy_setopt_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_curl = args_gurax.Pick<Value_CURL>();
	CURL* curl = value_curl.GetEntityPtr();
	CURLoption option = args_gurax.PickNumber<CURLoption>();
	Gurax::Value& value = args_gurax.PickValue();
	// Function body
	long optType = static_cast<long>(option) / 10000 * 10000;
	CURLcode code = CURLE_OK;
	if (optType == CURLOPTTYPE_LONG) {
		if (!value.IsInstanceOf(VTYPE_Number)) {
			Error::Issue(ErrorType::TypeError, "the option accepts Number value");
			return Value::nil();
		}
		code = curl_easy_setopt(curl, option, Value_Number::GetNumber<long>(value));
	} else if (optType == CURLOPTTYPE_OBJECTPOINT) {
		if (!value.IsInstanceOf(VTYPE_String)) {
			Error::Issue(ErrorType::TypeError, "the option accepts String value");
			return Value::nil();
		}
		code = curl_easy_setopt(curl, option, Value_String::GetString(value));
	} else if (optType == CURLOPTTYPE_FUNCTIONPOINT) {
	
	} else if (optType == CURLOPTTYPE_OFF_T) {
		if (!value.IsInstanceOf(VTYPE_Number)) {
			Error::Issue(ErrorType::TypeError, "the option accepts Number value");
			return Value::nil();
		}
		code = curl_easy_setopt(curl, option, Value_Number::GetNumber<size_t>(value));
	} else if (optType == CURLOPTTYPE_BLOB) {
	}
	return new Value_Number(code);
}

// curl.curl_easy_perform(curl:CURL)
Gurax_DeclareFunctionAlias(curl_easy_perform_gurax, "curl_easy_perform")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("curl", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_easy_perform_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_curl = args_gurax.Pick<Value_CURL>();
	CURL* curl = value_curl.GetEntityPtr();
	// Function body
	CURLcode rtn = curl_easy_perform(curl);
	return new Gurax::Value_Number(rtn);
}

// curl.curl_easy_cleanup(curl:CURL)
Gurax_DeclareFunctionAlias(curl_easy_cleanup_gurax, "curl_easy_cleanup")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("curl", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_easy_cleanup_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_curl = args_gurax.Pick<Value_CURL>();
	CURL* curl = value_curl.GetEntityPtr();
	// Function body
	curl_easy_cleanup(curl);
	return Gurax::Value::nil();
}

// curl.curl_easy_getinfo(curl:CURL, info:Number)
Gurax_DeclareFunctionAlias(curl_easy_getinfo_gurax, "curl_easy_getinfo")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("curl", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	DeclareArg("info", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_easy_getinfo_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_curl = args_gurax.Pick<Value_CURL>();
	CURL* curl = value_curl.GetEntityPtr();
	CURLINFO info = args_gurax.PickNumber<CURLINFO>();
	// Function body
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
	} else if (infoType == CURLINFO_PTR) {
	} else if (infoType == CURLINFO_SOCKET) {
	} else if (infoType == CURLINFO_OFF_T) {
	}
	return pValueRtn.release();
}

// curl.curl_easy_strerror(code:Number)
Gurax_DeclareFunctionAlias(curl_easy_strerror_gurax, "curl_easy_strerror")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("code", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_easy_strerror_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	CURLcode code = args_gurax.PickNumber<CURLcode>();
	// Function body
	const char* rtn = curl_easy_strerror(code);
	return new Gurax::Value_String(rtn);
}

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(curl_easy_init_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_setopt_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_perform_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_cleanup_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_getinfo_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_strerror_gurax));
}

Gurax_EndModuleScope(curl)
