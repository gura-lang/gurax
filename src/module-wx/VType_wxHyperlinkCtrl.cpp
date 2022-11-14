﻿//==============================================================================
// VType_wxHyperlinkCtrl.cpp
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

${help.ComposePropertyHelp(wx.HyperlinkCtrl, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.HyperlinkCtrl, `en)}

${help.ComposeMethodHelp(wx.HyperlinkCtrl, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.HyperlinkCtrl(parent as wx.Window, id as Number, label as String, url as String, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(HyperlinkCtrl_gurax, "HyperlinkCtrl")
{
	Declare(VTYPE_wxHyperlinkCtrl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("url", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.HyperlinkCtrl.
)**");
}

Gurax_ImplementConstructorEx(HyperlinkCtrl_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const char* label = args_gurax.PickString();
	const char* url = args_gurax.PickString();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxHL_DEFAULT_STYLE;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxHyperlinkCtrlNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxHyperlinkCtrl::EntityT(parent, id, label, url, pos, size, style, name);
	RefPtr<Value_wxHyperlinkCtrl> pValue_gurax(new Value_wxHyperlinkCtrl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.HyperlinkCtrl#Create(parent as wx.Window, id as Number, label as String, url as String, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String)
Gurax_DeclareMethodAlias(wxHyperlinkCtrl, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("url", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxHyperlinkCtrl, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const char* label = args_gurax.PickString();
	const char* url = args_gurax.PickString();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxHL_DEFAULT_STYLE;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxHyperlinkCtrlNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, label, url, pos, size, style, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.HyperlinkCtrl#GetHoverColour() {block?}
Gurax_DeclareMethodAlias(wxHyperlinkCtrl, GetHoverColour_gurax, "GetHoverColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxHyperlinkCtrl, GetHoverColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetHoverColour()));
}

// wx.HyperlinkCtrl#GetNormalColour() {block?}
Gurax_DeclareMethodAlias(wxHyperlinkCtrl, GetNormalColour_gurax, "GetNormalColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxHyperlinkCtrl, GetNormalColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetNormalColour()));
}

// wx.HyperlinkCtrl#GetURL()
Gurax_DeclareMethodAlias(wxHyperlinkCtrl, GetURL_gurax, "GetURL")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxHyperlinkCtrl, GetURL_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetURL();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.HyperlinkCtrl#GetVisited()
Gurax_DeclareMethodAlias(wxHyperlinkCtrl, GetVisited_gurax, "GetVisited")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxHyperlinkCtrl, GetVisited_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetVisited();
	return new Gurax::Value_Bool(rtn);
}

// wx.HyperlinkCtrl#GetVisitedColour() {block?}
Gurax_DeclareMethodAlias(wxHyperlinkCtrl, GetVisitedColour_gurax, "GetVisitedColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxHyperlinkCtrl, GetVisitedColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetVisitedColour()));
}

// wx.HyperlinkCtrl#SetHoverColour(colour as wx.Colour)
Gurax_DeclareMethodAlias(wxHyperlinkCtrl, SetHoverColour_gurax, "SetHoverColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colour", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxHyperlinkCtrl, SetHoverColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_colour = args_gurax.Pick<Value_wxColour>();
	const wxColour& colour = value_colour.GetEntity();
	// Function body
	pEntity_gurax->SetHoverColour(colour);
	return Gurax::Value::nil();
}

// wx.HyperlinkCtrl#SetNormalColour(colour as wx.Colour)
Gurax_DeclareMethodAlias(wxHyperlinkCtrl, SetNormalColour_gurax, "SetNormalColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colour", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxHyperlinkCtrl, SetNormalColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_colour = args_gurax.Pick<Value_wxColour>();
	const wxColour& colour = value_colour.GetEntity();
	// Function body
	pEntity_gurax->SetNormalColour(colour);
	return Gurax::Value::nil();
}

// wx.HyperlinkCtrl#SetURL(url as String)
Gurax_DeclareMethodAlias(wxHyperlinkCtrl, SetURL_gurax, "SetURL")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("url", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxHyperlinkCtrl, SetURL_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* url = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetURL(url);
	return Gurax::Value::nil();
}

// wx.HyperlinkCtrl#SetVisited(visited? as Bool)
Gurax_DeclareMethodAlias(wxHyperlinkCtrl, SetVisited_gurax, "SetVisited")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("visited", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxHyperlinkCtrl, SetVisited_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool visited = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->SetVisited(visited);
	return Gurax::Value::nil();
}

// wx.HyperlinkCtrl#SetVisitedColour(colour as wx.Colour)
Gurax_DeclareMethodAlias(wxHyperlinkCtrl, SetVisitedColour_gurax, "SetVisitedColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colour", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxHyperlinkCtrl, SetVisitedColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_colour = args_gurax.Pick<Value_wxColour>();
	const wxColour& colour = value_colour.GetEntity();
	// Function body
	pEntity_gurax->SetVisitedColour(colour);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxHyperlinkCtrl
//------------------------------------------------------------------------------
VType_wxHyperlinkCtrl VTYPE_wxHyperlinkCtrl("HyperlinkCtrl");

void VType_wxHyperlinkCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(HyperlinkCtrl_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxHyperlinkCtrl, Create_gurax));
	Assign(Gurax_CreateMethod(wxHyperlinkCtrl, GetHoverColour_gurax));
	Assign(Gurax_CreateMethod(wxHyperlinkCtrl, GetNormalColour_gurax));
	Assign(Gurax_CreateMethod(wxHyperlinkCtrl, GetURL_gurax));
	Assign(Gurax_CreateMethod(wxHyperlinkCtrl, GetVisited_gurax));
	Assign(Gurax_CreateMethod(wxHyperlinkCtrl, GetVisitedColour_gurax));
	Assign(Gurax_CreateMethod(wxHyperlinkCtrl, SetHoverColour_gurax));
	Assign(Gurax_CreateMethod(wxHyperlinkCtrl, SetNormalColour_gurax));
	Assign(Gurax_CreateMethod(wxHyperlinkCtrl, SetURL_gurax));
	Assign(Gurax_CreateMethod(wxHyperlinkCtrl, SetVisited_gurax));
	Assign(Gurax_CreateMethod(wxHyperlinkCtrl, SetVisitedColour_gurax));
}

//------------------------------------------------------------------------------
// Value_wxHyperlinkCtrl
//------------------------------------------------------------------------------
VType& Value_wxHyperlinkCtrl::vtype = VTYPE_wxHyperlinkCtrl;

String Value_wxHyperlinkCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HyperlinkCtrl");
}

//------------------------------------------------------------------------------
// Value_wxHyperlinkCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
