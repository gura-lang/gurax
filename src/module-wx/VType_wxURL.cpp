//==============================================================================
// VType_wxURL.cpp
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

${help.ComposePropertyHelp(wxURL)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxURL)}

${help.ComposeMethodHelp(wxURL)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.URL(url? as String) {block?}
Gurax_DeclareConstructorAlias(URL_gurax, "URL")
{
	Declare(VTYPE_wxURL, Flag::None);
	DeclareArg("url", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.URL.");
}

Gurax_ImplementConstructorEx(URL_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* url = args_gurax.IsValid()? args_gurax.PickString() : "";
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxURL(
		wxURL(url)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.URL#GetError()
Gurax_DeclareMethodAlias(wxURL, GetError_gurax, "GetError")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURL, GetError_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxURLError rtn = pEntity_gurax->GetError();
	return new Gurax::Value_Number(rtn);
}

// wx.URL#GetInputStream() {block?}
Gurax_DeclareMethodAlias(wxURL, GetInputStream_gurax, "GetInputStream")
{
	Declare(VTYPE_wxInputStream, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURL, GetInputStream_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxInputStream(
		pEntity_gurax->GetInputStream()));
}

// wx.URL#IsOk()
Gurax_DeclareMethodAlias(wxURL, IsOk_gurax, "IsOk")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURL, IsOk_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsOk();
	return new Gurax::Value_Bool(rtn);
}

// wx.URL#SetProxy(url_proxy as String)
Gurax_DeclareMethodAlias(wxURL, SetProxy_gurax, "SetProxy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("url_proxy", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURL, SetProxy_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* url_proxy = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetProxy(url_proxy);
	return Gurax::Value::nil();
}

// wx.URL#SetURL(url as String)
Gurax_DeclareMethodAlias(wxURL, SetURL_gurax, "SetURL")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("url", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxURL, SetURL_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* url = args_gurax.PickString();
	// Function body
	wxURLError rtn = pEntity_gurax->SetURL(url);
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxURL
//------------------------------------------------------------------------------
VType_wxURL VTYPE_wxURL("URL");

void VType_wxURL::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxURI, Flag::Mutable, Gurax_CreateConstructor(URL_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxURL, GetError_gurax));
	Assign(Gurax_CreateMethod(wxURL, GetInputStream_gurax));
	Assign(Gurax_CreateMethod(wxURL, IsOk_gurax));
	Assign(Gurax_CreateMethod(wxURL, SetProxy_gurax));
	Assign(Gurax_CreateMethod(wxURL, SetURL_gurax));
}

//------------------------------------------------------------------------------
// Value_wxURL
//------------------------------------------------------------------------------
VType& Value_wxURL::vtype = VTYPE_wxURL;

String Value_wxURL::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.URL");
}

Gurax_EndModuleScope(wx)
