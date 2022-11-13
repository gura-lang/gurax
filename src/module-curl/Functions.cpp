//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

// curl.curl_easy_init()
Gurax_DeclareFunctionAlias(curl_easy_init_gurax, "curl_easy_init")
{
	Declare(VTYPE_CURL, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(curl_easy_init_gurax, processor_gurax, argument_gurax)
{
	// Function body
	CURL* rtn = curl_easy_init();
	if (!rtn) return Value::nil();
	return new Value_CURL(processor_gurax.Reference(), rtn);
}

// curl.curl_easy_setopt(curl as CURL, option as Number, value as Any)
Gurax_DeclareFunctionAlias(curl_easy_setopt_gurax, "curl_easy_setopt")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("curl", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	DeclareArg("option", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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
	if (!value_curl.GetOpt().SetItem(option, value, &code)) return Value::nil();
	return new Value_Number(code);
}

// curl.curl_easy_perform(curl as CURL)
Gurax_DeclareFunctionAlias(curl_easy_perform_gurax, "curl_easy_perform")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("curl", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_easy_cleanup(curl as CURL)
Gurax_DeclareFunctionAlias(curl_easy_cleanup_gurax, "curl_easy_cleanup")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("curl", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_easy_getinfo(curl as CURL, info as Number)
Gurax_DeclareFunctionAlias(curl_easy_getinfo_gurax, "curl_easy_getinfo")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("curl", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	DeclareArg("info", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(curl_easy_getinfo_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_curl = args_gurax.Pick<Value_CURL>();
	CURL* curl = value_curl.GetEntityPtr();
	CURLINFO info = args_gurax.PickNumber<CURLINFO>();
	// Function body
	return value_curl.GetInfo().GetItem(info);
}

// curl.curl_easy_duphandle(curl as CURL)
Gurax_DeclareFunctionAlias(curl_easy_duphandle_gurax, "curl_easy_duphandle")
{
	Declare(VTYPE_CURL, Flag::None);
	DeclareArg("curl", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_easy_reset(curl as CURL)
Gurax_DeclareFunctionAlias(curl_easy_reset_gurax, "curl_easy_reset")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("curl", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_easy_upkeep(curl as CURL)
Gurax_DeclareFunctionAlias(curl_easy_upkeep_gurax, "curl_easy_upkeep")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("curl", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_mime_init(easy as CURL)
Gurax_DeclareFunctionAlias(curl_mime_init_gurax, "curl_mime_init")
{
	Declare(VTYPE_curl_mime, Flag::None);
	DeclareArg("easy", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_mime_free(mime as curl_mime)
Gurax_DeclareFunctionAlias(curl_mime_free_gurax, "curl_mime_free")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mime", VTYPE_curl_mime, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_mime_addpart(mime as curl_mime)
Gurax_DeclareFunctionAlias(curl_mime_addpart_gurax, "curl_mime_addpart")
{
	Declare(VTYPE_curl_mimepart, Flag::None);
	DeclareArg("mime", VTYPE_curl_mime, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_mime_name(part as curl_mimepart, name as String)
Gurax_DeclareFunctionAlias(curl_mime_name_gurax, "curl_mime_name")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("part", VTYPE_curl_mimepart, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_mime_filename(part as curl_mimepart, filename as String)
Gurax_DeclareFunctionAlias(curl_mime_filename_gurax, "curl_mime_filename")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("part", VTYPE_curl_mimepart, ArgOccur::Once, ArgFlag::None);
	DeclareArg("filename", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_mime_type(part as curl_mimepart, mimetype as String)
Gurax_DeclareFunctionAlias(curl_mime_type_gurax, "curl_mime_type")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("part", VTYPE_curl_mimepart, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mimetype", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_mime_encoder(part as curl_mimepart, encoding as String)
Gurax_DeclareFunctionAlias(curl_mime_encoder_gurax, "curl_mime_encoder")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("part", VTYPE_curl_mimepart, ArgOccur::Once, ArgFlag::None);
	DeclareArg("encoding", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_mime_data(part as curl_mimepart, data as Pointer, datasize as Number)
Gurax_DeclareFunctionAlias(curl_mime_data_gurax, "curl_mime_data")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("part", VTYPE_curl_mimepart, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("datasize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(curl_mime_data_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_part = args_gurax.Pick<Value_curl_mimepart>();
	curl_mimepart* part = value_part.GetEntityPtr();
	const char* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<char>();
	size_t datasize = args_gurax.PickNumber<size_t>();
	// Function body
	CURLcode rtn = curl_mime_data(part, data, datasize);
	return new Gurax::Value_Number(rtn);
}

// curl.curl_mime_filedata(part as curl_mimepart, filename as String)
Gurax_DeclareFunctionAlias(curl_mime_filedata_gurax, "curl_mime_filedata")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("part", VTYPE_curl_mimepart, ArgOccur::Once, ArgFlag::None);
	DeclareArg("filename", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_mime_subparts(part as curl_mimepart, subparts as curl_mime)
Gurax_DeclareFunctionAlias(curl_mime_subparts_gurax, "curl_mime_subparts")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("part", VTYPE_curl_mimepart, ArgOccur::Once, ArgFlag::None);
	DeclareArg("subparts", VTYPE_curl_mime, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_mime_headers(part as curl_mimepart, headers as curl_slist, take_ownership as Number)
Gurax_DeclareFunctionAlias(curl_mime_headers_gurax, "curl_mime_headers")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("part", VTYPE_curl_mimepart, ArgOccur::Once, ArgFlag::None);
	DeclareArg("headers", VTYPE_curl_slist, ArgOccur::Once, ArgFlag::None);
	DeclareArg("take_ownership", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(curl_mime_headers_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_part = args_gurax.Pick<Value_curl_mimepart>();
	curl_mimepart* part = value_part.GetEntityPtr();
	auto& value_headers = args_gurax.Pick<Value_curl_slist>();
	curl_slist* headers = value_headers.GetEntityPtr();
	int take_ownership = args_gurax.PickNumber<int>();
	// Function body
	CURLcode rtn = curl_mime_headers(part, headers, take_ownership);
	return new Gurax::Value_Number(rtn);
}

// curl.curl_free(value as Any)
Gurax_DeclareFunctionAlias(curl_free_gurax, "curl_free")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(curl_free_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Gurax::Value& value = args_gurax.PickValue();
	// Function body
	return Value::nil();
}

// curl.curl_global_init(flags as Number)
Gurax_DeclareFunctionAlias(curl_global_init_gurax, "curl_global_init")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(curl_global_init_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long flags = args_gurax.PickNumber<long>();
	// Function body
	CURLcode rtn = curl_global_init(flags);
	return new Gurax::Value_Number(rtn);
}

// curl.curl_global_cleanup()
Gurax_DeclareFunctionAlias(curl_global_cleanup_gurax, "curl_global_cleanup")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(curl_global_cleanup_gurax, processor_gurax, argument_gurax)
{
	// Function body
	curl_global_cleanup();
	return Gurax::Value::nil();
}

// curl.curl_slist_append(slist:nil as curl_slist, str as String)
Gurax_DeclareFunctionAlias(curl_slist_append_gurax, "curl_slist_append")
{
	Declare(VTYPE_curl_slist, Flag::None);
	DeclareArg("slist", VTYPE_curl_slist, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(curl_slist_append_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	curl_slist* slist = args_gurax.IsValid()? args_gurax.Pick<Value_curl_slist>().GetEntityPtr() : nullptr;
	const char* str = args_gurax.PickString();
	// Function body
	curl_slist* rtn = curl_slist_append(slist, str);
	if (!rtn) return Value::nil();
	return new Value_curl_slist(rtn);
}

// curl.curl_slist_free_all(slist as curl_slist)
Gurax_DeclareFunctionAlias(curl_slist_free_all_gurax, "curl_slist_free_all")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("slist", VTYPE_curl_slist, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(curl_slist_free_all_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_slist = args_gurax.Pick<Value_curl_slist>();
	curl_slist* slist = value_slist.GetEntityPtr();
	// Function body
	curl_slist_free_all(slist);
	return Gurax::Value::nil();
}

// curl.curl_easy_strerror(code as Number)
Gurax_DeclareFunctionAlias(curl_easy_strerror_gurax, "curl_easy_strerror")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("code", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_share_strerror(code as Number)
Gurax_DeclareFunctionAlias(curl_share_strerror_gurax, "curl_share_strerror")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("code", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_easy_pause(handle as CURL, bitmask as Number)
Gurax_DeclareFunctionAlias(curl_easy_pause_gurax, "curl_easy_pause")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("handle", VTYPE_CURL, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bitmask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// curl.curl_url()
Gurax_DeclareFunctionAlias(curl_url_gurax, "curl_url")
{
	Declare(VTYPE_CURLU, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(curl_url_gurax, processor_gurax, argument_gurax)
{
	// Function body
	CURLU* rtn = curl_url();
	if (!rtn) return Value::nil();
	return new Value_CURLU(rtn);
}

// curl.curl_url_cleanup(handle as CURLU)
Gurax_DeclareFunctionAlias(curl_url_cleanup_gurax, "curl_url_cleanup")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("handle", VTYPE_CURLU, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(curl_url_cleanup_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_handle = args_gurax.Pick<Value_CURLU>();
	CURLU* handle = value_handle.GetEntityPtr();
	// Function body
	curl_url_cleanup(handle);
	return Gurax::Value::nil();
}

// curl.curl_url_dup(inhandle as CURLU)
Gurax_DeclareFunctionAlias(curl_url_dup_gurax, "curl_url_dup")
{
	Declare(VTYPE_CURLU, Flag::None);
	DeclareArg("inhandle", VTYPE_CURLU, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(curl_url_dup_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_inhandle = args_gurax.Pick<Value_CURLU>();
	CURLU* inhandle = value_inhandle.GetEntityPtr();
	// Function body
	CURLU* rtn = curl_url_dup(inhandle);
	if (!rtn) return Value::nil();
	return new Value_CURLU(rtn);
}

// curl.curl_url_get(url as CURLU, what as Number, flags as Number)
Gurax_DeclareFunctionAlias(curl_url_get_gurax, "curl_url_get")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("url", VTYPE_CURLU, ArgOccur::Once, ArgFlag::None);
	DeclareArg("what", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(curl_url_get_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_url = args_gurax.Pick<Value_CURLU>();
	CURLU* url = value_url.GetEntityPtr();
	CURLUPart what = args_gurax.PickNumber<CURLUPart>();
	unsigned int flags = args_gurax.PickNumber<unsigned int>();
	// Function body
	char* part;
	CURLUcode code = curl_url_get(url, what, &part, flags);
	if (code != CURLE_OK) {
		Error::Issue(ErrorType::GuestError, "error in handling URL");
		return Value::nil();
	}
	RefPtr<Value> pValueRtn(new Value_String(part));
	curl_free(part);
	return pValueRtn.release();
}

// curl.curl_url_set(url as CURLU, part as Number, content as String, flags as Number)
Gurax_DeclareFunctionAlias(curl_url_set_gurax, "curl_url_set")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("url", VTYPE_CURLU, ArgOccur::Once, ArgFlag::None);
	DeclareArg("part", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("content", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(curl_url_set_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_url = args_gurax.Pick<Value_CURLU>();
	CURLU* url = value_url.GetEntityPtr();
	CURLUPart part = args_gurax.PickNumber<CURLUPart>();
	const char* content = args_gurax.PickString();
	unsigned int flags = args_gurax.PickNumber<unsigned int>();
	// Function body
	CURLUcode rtn = curl_url_set(url, part, content, flags);
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
	frame.Assign(Gurax_CreateFunction(curl_mime_data_gurax));
	frame.Assign(Gurax_CreateFunction(curl_mime_filedata_gurax));
	frame.Assign(Gurax_CreateFunction(curl_mime_subparts_gurax));
	frame.Assign(Gurax_CreateFunction(curl_mime_headers_gurax));
	frame.Assign(Gurax_CreateFunction(curl_free_gurax));
	frame.Assign(Gurax_CreateFunction(curl_global_init_gurax));
	frame.Assign(Gurax_CreateFunction(curl_global_cleanup_gurax));
	frame.Assign(Gurax_CreateFunction(curl_slist_append_gurax));
	frame.Assign(Gurax_CreateFunction(curl_slist_free_all_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_strerror_gurax));
	frame.Assign(Gurax_CreateFunction(curl_share_strerror_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_pause_gurax));
	frame.Assign(Gurax_CreateFunction(curl_url_gurax));
	frame.Assign(Gurax_CreateFunction(curl_url_cleanup_gurax));
	frame.Assign(Gurax_CreateFunction(curl_url_dup_gurax));
	frame.Assign(Gurax_CreateFunction(curl_url_get_gurax));
	frame.Assign(Gurax_CreateFunction(curl_url_set_gurax));
}

Gurax_EndModuleScope(curl)
