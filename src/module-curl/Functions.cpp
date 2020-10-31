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
	long optType = static_cast<long>(option) / 10000 * 10000;
	CURLcode code = CURLE_OK;
	if (optType == CURLOPTTYPE_LONG) {
		if (!value.IsInstanceOf(VTYPE_Number)) {
			Error::Issue(ErrorType::TypeError, "the option accepts Number value");
			return Value::nil();
		}
		code = curl_easy_setopt(curl, option, Value_Number::GetNumber<long>(value));
	} else if (optType == CURLOPTTYPE_OBJECTPOINT) {
		switch (option) {
		case CURLOPT_WRITEDATA: {
			value_curl.pValue_WRITE.reset(value.Reference());
			break;
		}
		case CURLOPT_READDATA: {
			value_curl.pValue_READ.reset(value.Reference());
			break;
		}
		case CURLOPT_PROGRESSDATA: {
			value_curl.pValue_PROGRESS.reset(value.Reference());
			break;
		}
		case CURLOPT_HEADERDATA: {
			value_curl.pValue_HEADER.reset(value.Reference());
			break;
		}
		case CURLOPT_DEBUGDATA: {
			value_curl.pValue_DEBUG.reset(value.Reference());
			break;
		}
		case CURLOPT_SSL_CTX_DATA: {
			value_curl.pValue_SSL_CTX.reset(value.Reference());
			break;
		}
		case CURLOPT_IOCTLDATA: {
			value_curl.pValue_IOCTL.reset(value.Reference());
			break;
		}
		//case CURLOPT_CONV_FROM_NETWORK_DATA: {
		//	value_curl.pValue_CONV_FROM_NETWORK.reset(value.Reference());
		//	break;
		//}
		//case CURLOPT_CONV_TO_NETWORK_DATA: {
		//	value_curl.pValue_CONV_TO_NETWORK.reset(value.Reference());
		//	break;
		//}
		//case CURLOPT_CONV_FROM_UTF8_DATA: {
		//	value_curl.pValue_CONV_FROM_UTF8.reset(value.Reference());
		//	break;
		//}
		case CURLOPT_SOCKOPTDATA: {
			value_curl.pValue_SOCKOPT.reset(value.Reference());
			break;
		}
		case CURLOPT_OPENSOCKETDATA: {
			value_curl.pValue_OPENSOCKET.reset(value.Reference());
			break;
		}
		case CURLOPT_SEEKDATA: {
			value_curl.pValue_SEEK.reset(value.Reference());
			break;
		}
		case CURLOPT_SSH_KEYDATA: {
			value_curl.pValue_SSH_KEY.reset(value.Reference());
			break;
		}
		case CURLOPT_INTERLEAVEDATA: {
			value_curl.pValue_INTERLEAVE.reset(value.Reference());
			break;
		}
		//case CURLOPT_CHUNK_BGN_DATA: {
		//	value_curl.pValue_CHUNK_BGN.reset(value.Reference());
		//	break;
		//}
		//case CURLOPT_CHUNK_END_DATA: {
		//	value_curl.pValue_CHUNK_END.reset(value.Reference());
		//	break;
		//}
		case CURLOPT_FNMATCH_DATA: {
			value_curl.pValue_FNMATCH.reset(value.Reference());
			break;
		}
		case CURLOPT_CLOSESOCKETDATA: {
			value_curl.pValue_CLOSESOCKET.reset(value.Reference());
			break;
		}
		//case CURLOPT_XFERINFODATA: {
		//	value_curl.pValue_XFERINFO.reset(value.Reference());
		//	break;
		//}
		case CURLOPT_RESOLVER_START_DATA: {
			value_curl.pValue_RESOLVER_START.reset(value.Reference());
			break;
		}
		case CURLOPT_TRAILERDATA: {
			value_curl.pValue_TRAILER.reset(value.Reference());
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
				return Value::nil();
			}
			curl_slist* slist = nullptr;
			for (const Value* pValue : Value_List::GetValueOwner(value)) {
				if (!pValue->IsInstanceOf(VTYPE_String)) {
					Error::Issue(ErrorType::TypeError, "the option accepts String value");
					return Value::nil();
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
				return Value::nil();
			}
			code = curl_easy_setopt(curl, option, Value_String::GetString(value));
			break;
		}
		}
	} else if (optType == CURLOPTTYPE_FUNCTIONPOINT) {
		if (!value.IsInstanceOf(VTYPE_Function)) {
			Error::Issue(ErrorType::TypeError, "the option accepts Function value");
			return Value::nil();
		}
		const Function& func = Value_Function::GetFunction(value);
		switch (option) {
		case CURLOPT_WRITEFUNCTION: {
			value_curl.pFunc_WRITE.reset(func.Reference());
			break;
		}
		case CURLOPT_READFUNCTION: {
			value_curl.pFunc_READ.reset(func.Reference());
			break;
		}
		case CURLOPT_PROGRESSFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, Value_CURL::Callback_PROGRESS);
			curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, this);
			value_curl.pFunc_PROGRESS.reset(func.Reference());
			break;
		}
		case CURLOPT_HEADERFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, Value_CURL::Callback_HEADER);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);
			value_curl.pFunc_HEADER.reset(func.Reference());
			break;
		}
		case CURLOPT_DEBUGFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, Value_CURL::Callback_DEBUG);
			curl_easy_setopt(curl, CURLOPT_DEBUGDATA, this);
			value_curl.pFunc_DEBUG.reset(func.Reference());
			break;
		}
		case CURLOPT_SSL_CTX_FUNCTION: {
			curl_easy_setopt(curl, CURLOPT_SSL_CTX_FUNCTION, Value_CURL::Callback_SSL_CTX);
			curl_easy_setopt(curl, CURLOPT_SSL_CTX_DATA, this);
			value_curl.pFunc_SSL_CTX.reset(func.Reference());
			break;
		}
		case CURLOPT_IOCTLFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_IOCTLFUNCTION, Value_CURL::Callback_IOCTL);
			curl_easy_setopt(curl, CURLOPT_IOCTLDATA, this);
			value_curl.pFunc_IOCTL.reset(func.Reference());
			break;
		}
		case CURLOPT_CONV_FROM_NETWORK_FUNCTION: {
			curl_easy_setopt(curl, CURLOPT_CONV_FROM_NETWORK_FUNCTION, Value_CURL::Callback_CONV_FROM_NETWORK);
			//curl_easy_setopt(curl, CURLOPT_CONV_FROM_NETWORK_DATA, this);
			value_curl.pFunc_CONV_FROM_NETWORK.reset(func.Reference());
			break;
		}
		case CURLOPT_CONV_TO_NETWORK_FUNCTION: {
			curl_easy_setopt(curl, CURLOPT_CONV_TO_NETWORK_FUNCTION, Value_CURL::Callback_CONV_TO_NETWORK);
			//curl_easy_setopt(curl, CURLOPT_CONV_TO_NETWORK_DATA, this);
			value_curl.pFunc_CONV_TO_NETWORK.reset(func.Reference());
			break;
		}
		case CURLOPT_CONV_FROM_UTF8_FUNCTION: {
			curl_easy_setopt(curl, CURLOPT_CONV_FROM_UTF8_FUNCTION, Value_CURL::Callback_CONV_FROM_UTF8);
			//curl_easy_setopt(curl, CURLOPT_CONV_FROM_UTF8_DATA, this);
			value_curl.pFunc_CONV_FROM_UTF8.reset(func.Reference());
			break;
		}
		case CURLOPT_SOCKOPTFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_SOCKOPTFUNCTION, Value_CURL::Callback_SOCKOPT);
			curl_easy_setopt(curl, CURLOPT_SOCKOPTDATA, this);
			value_curl.pFunc_SOCKOPT.reset(func.Reference());
			break;
		}
		case CURLOPT_OPENSOCKETFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_OPENSOCKETFUNCTION, Value_CURL::Callback_OPENSOCKET);
			curl_easy_setopt(curl, CURLOPT_OPENSOCKETDATA, this);
			value_curl.pFunc_OPENSOCKET.reset(func.Reference());
			break;
		}
		case CURLOPT_SEEKFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_SEEKFUNCTION, Value_CURL::Callback_SEEK);
			curl_easy_setopt(curl, CURLOPT_SEEKDATA, this);
			value_curl.pFunc_SEEK.reset(func.Reference());
			break;
		}
		case CURLOPT_SSH_KEYFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_SSH_KEYFUNCTION, Value_CURL::Callback_SSH_KEY);
			curl_easy_setopt(curl, CURLOPT_SSH_KEYDATA, this);
			value_curl.pFunc_SSH_KEY.reset(func.Reference());
			break;
		}
		case CURLOPT_INTERLEAVEFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_INTERLEAVEFUNCTION, Value_CURL::Callback_INTERLEAVE);
			curl_easy_setopt(curl, CURLOPT_INTERLEAVEDATA, this);
			value_curl.pFunc_INTERLEAVE.reset(func.Reference());
			break;
		}
		case CURLOPT_CHUNK_BGN_FUNCTION: {
			curl_easy_setopt(curl, CURLOPT_CHUNK_BGN_FUNCTION, Value_CURL::Callback_CHUNK_BGN);
			//curl_easy_setopt(curl, CURLOPT_CHUNK_BGN_DATA, this);
			value_curl.pFunc_CHUNK_BGN.reset(func.Reference());
			break;
		}
		case CURLOPT_CHUNK_END_FUNCTION: {
			curl_easy_setopt(curl, CURLOPT_CHUNK_END_FUNCTION, Value_CURL::Callback_CHUNK_END);
			//curl_easy_setopt(curl, CURLOPT_CHUNK_END_DATA, this);
			value_curl.pFunc_CHUNK_END.reset(func.Reference());
			break;
		}
		case CURLOPT_FNMATCH_FUNCTION: {
			curl_easy_setopt(curl, CURLOPT_FNMATCH_FUNCTION, Value_CURL::Callback_FNMATCH);
			curl_easy_setopt(curl, CURLOPT_FNMATCH_DATA, this);
			value_curl.pFunc_FNMATCH.reset(func.Reference());
			break;
		}
		case CURLOPT_CLOSESOCKETFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_CLOSESOCKETFUNCTION, Value_CURL::Callback_CLOSESOCKET);
			curl_easy_setopt(curl, CURLOPT_CLOSESOCKETDATA, this);
			value_curl.pFunc_CLOSESOCKET.reset(func.Reference());
			break;
		}
		case CURLOPT_XFERINFOFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, Value_CURL::Callback_XFERINFO);
			curl_easy_setopt(curl, CURLOPT_XFERINFODATA, this);
			value_curl.pFunc_XFERINFO.reset(func.Reference());
			break;
		}
		case CURLOPT_RESOLVER_START_FUNCTION: {
			curl_easy_setopt(curl, CURLOPT_RESOLVER_START_FUNCTION, Value_CURL::Callback_RESOLVER_START);
			curl_easy_setopt(curl, CURLOPT_RESOLVER_START_DATA, this);
			value_curl.pFunc_RESOLVER_START.reset(func.Reference());
			break;
		}
		case CURLOPT_TRAILERFUNCTION: {
			curl_easy_setopt(curl, CURLOPT_TRAILERFUNCTION, Value_CURL::Callback_TRAILER);
			curl_easy_setopt(curl, CURLOPT_TRAILERDATA, this);
			value_curl.pFunc_TRAILER.reset(func.Reference());
			break;
		}
		default: {
			break;
		}
		}
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
	frame.Assign(Gurax_CreateFunction(curl_easy_strerror_gurax));
	frame.Assign(Gurax_CreateFunction(curl_share_strerror_gurax));
	frame.Assign(Gurax_CreateFunction(curl_easy_pause_gurax));
}

Gurax_EndModuleScope(curl)
