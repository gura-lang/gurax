﻿//==============================================================================
// VType_wxListItemAttr.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wx.ListItemAttr, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.ListItemAttr, `en)}

${help.ComposeMethodHelp(wx.ListItemAttr, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.ListItemAttr, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.ListItemAttr, `ja)}

${help.ComposeMethodHelp(wx.ListItemAttr, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.ListItemAttr(args* as Any) {block?}
Gurax_DeclareConstructorAlias(ListItemAttr_gurax, "ListItemAttr")
{
	Declare(VTYPE_wxListItemAttr, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(ListItemAttr_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// wx.ListItemAttr()
	if (args.empty()) {
		return new Value_wxListItemAttr(wxListItemAttr());
	}
	// wx.ListItemAttr(colText as wx.Colour, colBack as wx.Colour, font as wxFont)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("colText", VTYPE_wxColour);
			pDeclCallable->DeclareArg("colBack", VTYPE_wxColour);
			pDeclCallable->DeclareArg("font", VTYPE_wxFont);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxColour& colText = args.Pick<Value_wxColour>().GetEntity();
		const wxColour& colBack = args.Pick<Value_wxColour>().GetEntity();
		const wxFont& font = args.Pick<Value_wxFont>().GetEntity();
		return new Value_wxListItemAttr(wxListItemAttr(colText, colBack, font));
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ListItemAttr#GetBackgroundColour() {block?}
Gurax_DeclareMethodAlias(wxListItemAttr, GetBackgroundColour_gurax, "GetBackgroundColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxListItemAttr, GetBackgroundColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(pEntity_gurax->GetBackgroundColour()));
}

// wx.ListItemAttr#GetFont() {block?}
Gurax_DeclareMethodAlias(wxListItemAttr, GetFont_gurax, "GetFont")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxListItemAttr, GetFont_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFont(pEntity_gurax->GetFont()));
}

// wx.ListItemAttr#GetTextColour() {block?}
Gurax_DeclareMethodAlias(wxListItemAttr, GetTextColour_gurax, "GetTextColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxListItemAttr, GetTextColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(pEntity_gurax->GetTextColour()));
}

// wx.ListItemAttr#HasBackgroundColour()
Gurax_DeclareMethodAlias(wxListItemAttr, HasBackgroundColour_gurax, "HasBackgroundColour")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxListItemAttr, HasBackgroundColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasBackgroundColour();
	return new Gurax::Value_Bool(rtn);
}

// wx.ListItemAttr#HasFont()
Gurax_DeclareMethodAlias(wxListItemAttr, HasFont_gurax, "HasFont")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxListItemAttr, HasFont_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasFont();
	return new Gurax::Value_Bool(rtn);
}

// wx.ListItemAttr#HasTextColour()
Gurax_DeclareMethodAlias(wxListItemAttr, HasTextColour_gurax, "HasTextColour")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxListItemAttr, HasTextColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasTextColour();
	return new Gurax::Value_Bool(rtn);
}

// wx.ListItemAttr#SetBackgroundColour(colour as wx.Colour)
Gurax_DeclareMethodAlias(wxListItemAttr, SetBackgroundColour_gurax, "SetBackgroundColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colour", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxListItemAttr, SetBackgroundColour_gurax, processor_gurax, argument_gurax)
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
	pEntity_gurax->SetBackgroundColour(colour);
	return Gurax::Value::nil();
}

// wx.ListItemAttr#SetFont(font as wx.Font)
Gurax_DeclareMethodAlias(wxListItemAttr, SetFont_gurax, "SetFont")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("font", VTYPE_wxFont, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxListItemAttr, SetFont_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxFont& value_font = args_gurax.Pick<Value_wxFont>();
	const wxFont& font = value_font.GetEntity();
	// Function body
	pEntity_gurax->SetFont(font);
	return Gurax::Value::nil();
}

// wx.ListItemAttr#SetTextColour(colour as wx.Colour)
Gurax_DeclareMethodAlias(wxListItemAttr, SetTextColour_gurax, "SetTextColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colour", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxListItemAttr, SetTextColour_gurax, processor_gurax, argument_gurax)
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
	pEntity_gurax->SetTextColour(colour);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxListItemAttr
//------------------------------------------------------------------------------
VType_wxListItemAttr VTYPE_wxListItemAttr("ListItemAttr");

void VType_wxListItemAttr::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(ListItemAttr_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxListItemAttr, GetBackgroundColour_gurax));
	Assign(Gurax_CreateMethod(wxListItemAttr, GetFont_gurax));
	Assign(Gurax_CreateMethod(wxListItemAttr, GetTextColour_gurax));
	Assign(Gurax_CreateMethod(wxListItemAttr, HasBackgroundColour_gurax));
	Assign(Gurax_CreateMethod(wxListItemAttr, HasFont_gurax));
	Assign(Gurax_CreateMethod(wxListItemAttr, HasTextColour_gurax));
	Assign(Gurax_CreateMethod(wxListItemAttr, SetBackgroundColour_gurax));
	Assign(Gurax_CreateMethod(wxListItemAttr, SetFont_gurax));
	Assign(Gurax_CreateMethod(wxListItemAttr, SetTextColour_gurax));
}

//------------------------------------------------------------------------------
// Value_wxListItemAttr
//------------------------------------------------------------------------------
VType& Value_wxListItemAttr::vtype = VTYPE_wxListItemAttr;

String Value_wxListItemAttr::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ListItemAttr");
}

Gurax_EndModuleScope(wx)
