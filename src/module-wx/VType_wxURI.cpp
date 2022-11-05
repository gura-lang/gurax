//==============================================================================
// VType_wxURI.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wxURI, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxURI, `en)}

${help.ComposeMethodHelp(wxURI, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.URI(uri? as String) {block?}
Gurax_DeclareConstructorAlias(URI_gurax, "URI")
{
	Declare(VTYPE_wxURI, Flag::None);
	DeclareArg("uri", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.URI.");
}

Gurax_ImplementConstructorEx(URI_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* uri = args_gurax.IsValid()? args_gurax.PickString() : "";
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxURI(
		wxURI(uri)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.URI#BuildURI()
Gurax_DeclareMethodAlias(wxURI, BuildURI_gurax, "BuildURI")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, BuildURI_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->BuildURI();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.URI#BuildUnescapedURI()
Gurax_DeclareMethodAlias(wxURI, BuildUnescapedURI_gurax, "BuildUnescapedURI")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, BuildUnescapedURI_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->BuildUnescapedURI();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.URI#Create(uri as String)
Gurax_DeclareMethodAlias(wxURI, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("uri", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* uri = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->Create(uri);
	return new Gurax::Value_Bool(rtn);
}

// wx.URI#GetFragment()
Gurax_DeclareMethodAlias(wxURI, GetFragment_gurax, "GetFragment")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, GetFragment_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetFragment();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.URI#GetHostType()
Gurax_DeclareMethodAlias(wxURI, GetHostType_gurax, "GetHostType")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, GetHostType_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxURIHostType rtn = pEntity_gurax->GetHostType();
	return new Gurax::Value_Number(rtn);
}

// wx.URI#GetPassword()
Gurax_DeclareMethodAlias(wxURI, GetPassword_gurax, "GetPassword")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, GetPassword_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetPassword();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.URI#GetPath()
Gurax_DeclareMethodAlias(wxURI, GetPath_gurax, "GetPath")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, GetPath_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetPath();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.URI#GetPort()
Gurax_DeclareMethodAlias(wxURI, GetPort_gurax, "GetPort")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, GetPort_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetPort();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.URI#GetQuery()
Gurax_DeclareMethodAlias(wxURI, GetQuery_gurax, "GetQuery")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, GetQuery_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetQuery();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.URI#GetScheme()
Gurax_DeclareMethodAlias(wxURI, GetScheme_gurax, "GetScheme")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, GetScheme_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetScheme();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.URI#GetServer()
Gurax_DeclareMethodAlias(wxURI, GetServer_gurax, "GetServer")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, GetServer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetServer();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.URI#GetUser()
Gurax_DeclareMethodAlias(wxURI, GetUser_gurax, "GetUser")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, GetUser_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetUser();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.URI#GetUserInfo()
Gurax_DeclareMethodAlias(wxURI, GetUserInfo_gurax, "GetUserInfo")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, GetUserInfo_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetUserInfo();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.URI#HasFragment()
Gurax_DeclareMethodAlias(wxURI, HasFragment_gurax, "HasFragment")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, HasFragment_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasFragment();
	return new Gurax::Value_Bool(rtn);
}

// wx.URI#HasPath()
Gurax_DeclareMethodAlias(wxURI, HasPath_gurax, "HasPath")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, HasPath_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasPath();
	return new Gurax::Value_Bool(rtn);
}

// wx.URI#HasPort()
Gurax_DeclareMethodAlias(wxURI, HasPort_gurax, "HasPort")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, HasPort_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasPort();
	return new Gurax::Value_Bool(rtn);
}

// wx.URI#HasQuery()
Gurax_DeclareMethodAlias(wxURI, HasQuery_gurax, "HasQuery")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, HasQuery_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasQuery();
	return new Gurax::Value_Bool(rtn);
}

// wx.URI#HasScheme()
Gurax_DeclareMethodAlias(wxURI, HasScheme_gurax, "HasScheme")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, HasScheme_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasScheme();
	return new Gurax::Value_Bool(rtn);
}

// wx.URI#HasServer()
Gurax_DeclareMethodAlias(wxURI, HasServer_gurax, "HasServer")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, HasServer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasServer();
	return new Gurax::Value_Bool(rtn);
}

// wx.URI#HasUserInfo()
Gurax_DeclareMethodAlias(wxURI, HasUserInfo_gurax, "HasUserInfo")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, HasUserInfo_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasUserInfo();
	return new Gurax::Value_Bool(rtn);
}

// wx.URI#IsReference()
Gurax_DeclareMethodAlias(wxURI, IsReference_gurax, "IsReference")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, IsReference_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsReference();
	return new Gurax::Value_Bool(rtn);
}

// wx.URI#Resolve(base as wx.URI, flags? as Number)
Gurax_DeclareMethodAlias(wxURI, Resolve_gurax, "Resolve")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("base", VTYPE_wxURI, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURI, Resolve_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxURI& value_base = args_gurax.Pick<Value_wxURI>();
	const wxURI& base = value_base.GetEntity();
	bool flags_validFlag = args_gurax.IsValid();
	int flags = flags_validFlag? args_gurax.PickNumber<int>() : wxURI_STRICT;
	// Function body
	pEntity_gurax->Resolve(base, flags);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxURI
//------------------------------------------------------------------------------
VType_wxURI VTYPE_wxURI("URI");

void VType_wxURI::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(URI_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxURI, BuildURI_gurax));
	Assign(Gurax_CreateMethod(wxURI, BuildUnescapedURI_gurax));
	Assign(Gurax_CreateMethod(wxURI, Create_gurax));
	Assign(Gurax_CreateMethod(wxURI, GetFragment_gurax));
	Assign(Gurax_CreateMethod(wxURI, GetHostType_gurax));
	Assign(Gurax_CreateMethod(wxURI, GetPassword_gurax));
	Assign(Gurax_CreateMethod(wxURI, GetPath_gurax));
	Assign(Gurax_CreateMethod(wxURI, GetPort_gurax));
	Assign(Gurax_CreateMethod(wxURI, GetQuery_gurax));
	Assign(Gurax_CreateMethod(wxURI, GetScheme_gurax));
	Assign(Gurax_CreateMethod(wxURI, GetServer_gurax));
	Assign(Gurax_CreateMethod(wxURI, GetUser_gurax));
	Assign(Gurax_CreateMethod(wxURI, GetUserInfo_gurax));
	Assign(Gurax_CreateMethod(wxURI, HasFragment_gurax));
	Assign(Gurax_CreateMethod(wxURI, HasPath_gurax));
	Assign(Gurax_CreateMethod(wxURI, HasPort_gurax));
	Assign(Gurax_CreateMethod(wxURI, HasQuery_gurax));
	Assign(Gurax_CreateMethod(wxURI, HasScheme_gurax));
	Assign(Gurax_CreateMethod(wxURI, HasServer_gurax));
	Assign(Gurax_CreateMethod(wxURI, HasUserInfo_gurax));
	Assign(Gurax_CreateMethod(wxURI, IsReference_gurax));
	Assign(Gurax_CreateMethod(wxURI, Resolve_gurax));
}

//------------------------------------------------------------------------------
// Value_wxURI
//------------------------------------------------------------------------------
VType& Value_wxURI::vtype = VTYPE_wxURI;

String Value_wxURI::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.URI");
}

Gurax_EndModuleScope(wx)
