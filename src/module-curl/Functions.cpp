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
	return new Value_CURL(processor_gurax.Reference(), rtn);
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
	CURLcode code = CURLE_OK;
	if (!value_curl.SetOpt(option, value, &code)) return Value::nil();
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
	return value_curl.GetInfo(info);
}

// curl.curl_easy_duphandle(curl:CURL)
Gurax_DeclareFunctionAlias(curl_easy_duphandle_gurax, "curl_easy_duphandle")
{
	Declare(VTYPE_CURL, Flag::None);
	DeclareArg("curl", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_easy_duphandle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_curl = args_gurax.Pick<Value_CURL>();
	CURL* curl = value_curl.GetEntityPtr();
	// Function body
	CURL* rtn = curl_easy_duphandle(curl);
	if (!rtn) return Value::nil();
	return new Value_CURL(processor_gurax.Reference(), rtn);
}

// curl.curl_easy_reset(curl:CURL)
Gurax_DeclareFunctionAlias(curl_easy_reset_gurax, "curl_easy_reset")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("curl", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_easy_reset_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_curl = args_gurax.Pick<Value_CURL>();
	CURL* curl = value_curl.GetEntityPtr();
	// Function body
	curl_easy_reset(curl);
	return Gurax::Value::nil();
}

// curl.curl_easy_upkeep(curl:CURL)
Gurax_DeclareFunctionAlias(curl_easy_upkeep_gurax, "curl_easy_upkeep")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("curl", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_easy_upkeep_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_curl = args_gurax.Pick<Value_CURL>();
	CURL* curl = value_curl.GetEntityPtr();
	// Function body
	CURLcode rtn = curl_easy_upkeep(curl);
	return new Gurax::Value_Number(rtn);
}

// curl.curl_mime_init(easy:CURL)
Gurax_DeclareFunctionAlias(curl_mime_init_gurax, "curl_mime_init")
{
	Declare(VTYPE_curl_mime, Flag::None);
	DeclareArg("easy", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_mime_init_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_easy = args_gurax.Pick<Value_CURL>();
	CURL* easy = value_easy.GetEntityPtr();
	// Function body
	curl_mime* rtn = curl_mime_init(easy);
	if (!rtn) return Value::nil();
	return new Value_curl_mime(rtn);
}

// curl.curl_mime_free(mime:curl_mime)
Gurax_DeclareFunctionAlias(curl_mime_free_gurax, "curl_mime_free")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mime", VTYPE_curl_mime, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_mime_free_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_mime = args_gurax.Pick<Value_curl_mime>();
	curl_mime* mime = value_mime.GetEntityPtr();
	// Function body
	curl_mime_free(mime);
	return Gurax::Value::nil();
}

// curl.curl_mime_addpart(mime:curl_mime)
Gurax_DeclareFunctionAlias(curl_mime_addpart_gurax, "curl_mime_addpart")
{
	Declare(VTYPE_curl_mimepart, Flag::None);
	DeclareArg("mime", VTYPE_curl_mime, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_mime_addpart_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_mime = args_gurax.Pick<Value_curl_mime>();
	curl_mime* mime = value_mime.GetEntityPtr();
	// Function body
	curl_mimepart* rtn = curl_mime_addpart(mime);
	if (!rtn) return Value::nil();
	return new Value_curl_mimepart(rtn);
}

// curl.curl_mime_name(part:curl_mimepart, name:String)
Gurax_DeclareFunctionAlias(curl_mime_name_gurax, "curl_mime_name")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("part", VTYPE_curl_mimepart, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_mime_name_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_part = args_gurax.Pick<Value_curl_mimepart>();
	curl_mimepart* part = value_part.GetEntityPtr();
	const char* name = args_gurax.PickString();
	// Function body
	CURLcode rtn = curl_mime_name(part, name);
	return new Gurax::Value_Number(rtn);
}

// curl.curl_mime_filename(part:curl_mimepart, filename:String)
Gurax_DeclareFunctionAlias(curl_mime_filename_gurax, "curl_mime_filename")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("part", VTYPE_curl_mimepart, ArgOccur::Once, ArgFlag::None);
	DeclareArg("filename", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_mime_filename_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_part = args_gurax.Pick<Value_curl_mimepart>();
	curl_mimepart* part = value_part.GetEntityPtr();
	const char* filename = args_gurax.PickString();
	// Function body
	CURLcode rtn = curl_mime_filename(part, filename);
	return new Gurax::Value_Number(rtn);
}

// curl.curl_mime_type(part:curl_mimepart, mimetype:String)
Gurax_DeclareFunctionAlias(curl_mime_type_gurax, "curl_mime_type")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("part", VTYPE_curl_mimepart, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mimetype", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_mime_type_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_part = args_gurax.Pick<Value_curl_mimepart>();
	curl_mimepart* part = value_part.GetEntityPtr();
	const char* mimetype = args_gurax.PickString();
	// Function body
	CURLcode rtn = curl_mime_type(part, mimetype);
	return new Gurax::Value_Number(rtn);
}

// curl.curl_mime_encoder(part:curl_mimepart, encoding:String)
Gurax_DeclareFunctionAlias(curl_mime_encoder_gurax, "curl_mime_encoder")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("part", VTYPE_curl_mimepart, ArgOccur::Once, ArgFlag::None);
	DeclareArg("encoding", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_mime_encoder_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_part = args_gurax.Pick<Value_curl_mimepart>();
	curl_mimepart* part = value_part.GetEntityPtr();
	const char* encoding = args_gurax.PickString();
	// Function body
	CURLcode rtn = curl_mime_encoder(part, encoding);
	return new Gurax::Value_Number(rtn);
}

// curl.curl_mime_filedata(part:curl_mimepart, filename:String)
Gurax_DeclareFunctionAlias(curl_mime_filedata_gurax, "curl_mime_filedata")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("part", VTYPE_curl_mimepart, ArgOccur::Once, ArgFlag::None);
	DeclareArg("filename", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_mime_filedata_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_part = args_gurax.Pick<Value_curl_mimepart>();
	curl_mimepart* part = value_part.GetEntityPtr();
	const char* filename = args_gurax.PickString();
	// Function body
	CURLcode rtn = curl_mime_filedata(part, filename);
	return new Gurax::Value_Number(rtn);
}

// curl.curl_mime_subparts(part:curl_mimepart, subparts:curl_mime)
Gurax_DeclareFunctionAlias(curl_mime_subparts_gurax, "curl_mime_subparts")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("part", VTYPE_curl_mimepart, ArgOccur::Once, ArgFlag::None);
	DeclareArg("subparts", VTYPE_curl_mime, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_mime_subparts_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_part = args_gurax.Pick<Value_curl_mimepart>();
	curl_mimepart* part = value_part.GetEntityPtr();
	auto& value_subparts = args_gurax.Pick<Value_curl_mime>();
	curl_mime* subparts = value_subparts.GetEntityPtr();
	// Function body
	CURLcode rtn = curl_mime_subparts(part, subparts);
	return new Gurax::Value_Number(rtn);
}

// curl.curl_free(value:Any)
Gurax_DeclareFunctionAlias(curl_free_gurax, "curl_free")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_free_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Gurax::Value& value = args_gurax.PickValue();
	// Function body
	return Value::nil();
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

// curl.curl_share_strerror(code:Number)
Gurax_DeclareFunctionAlias(curl_share_strerror_gurax, "curl_share_strerror")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("code", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_share_strerror_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	CURLSHcode code = args_gurax.PickNumber<CURLSHcode>();
	// Function body
	const char* rtn = curl_share_strerror(code);
	return new Gurax::Value_String(rtn);
}

// curl.curl_easy_pause(handle:CURL, bitmask:Number)
Gurax_DeclareFunctionAlias(curl_easy_pause_gurax, "curl_easy_pause")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("handle", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bitmask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(curl_easy_pause_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_handle = args_gurax.Pick<Value_CURL>();
	CURL* handle = value_handle.GetEntityPtr();
	int bitmask = args_gurax.PickNumber<int>();
	// Function body
	CURLcode rtn = curl_easy_pause(handle, bitmask);
	return new Gurax::Value_Number(rtn);
}

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(curl_easy_init_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_setopt_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_perform_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_cleanup_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_getinfo_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_duphandle_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_reset_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_upkeep_gurax));
	frame.Assign(Gurax_CreateFunction(curl_mime_init_gurax));
	frame.Assign(Gurax_CreateFunction(curl_mime_free_gurax));
	frame.Assign(Gurax_CreateFunction(curl_mime_addpart_gurax));
	frame.Assign(Gurax_CreateFunction(curl_mime_name_gurax));
	frame.Assign(Gurax_CreateFunction(curl_mime_filename_gurax));
	frame.Assign(Gurax_CreateFunction(curl_mime_type_gurax));
	frame.Assign(Gurax_CreateFunction(curl_mime_encoder_gurax));
	frame.Assign(Gurax_CreateFunction(curl_mime_filedata_gurax));
	frame.Assign(Gurax_CreateFunction(curl_mime_subparts_gurax));
	frame.Assign(Gurax_CreateFunction(curl_free_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_strerror_gurax));
	frame.Assign(Gurax_CreateFunction(curl_share_strerror_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_pause_gurax));
}

Gurax_EndModuleScope(curl)
