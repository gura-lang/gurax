﻿//==============================================================================
// VType_wxFontData.cpp
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

${help.ComposePropertyHelp(wx.FontData, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.FontData, `en)}

${help.ComposeMethodHelp(wx.FontData, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.FontData, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.FontData, `ja)}

${help.ComposeMethodHelp(wx.FontData, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.FontData() {block?}
Gurax_DeclareConstructorAlias(FontData_gurax, "FontData")
{
	Declare(VTYPE_wxFontData, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(FontData_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFontData(
		wxFontData()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.FontData#EnableEffects(enable as Bool)
Gurax_DeclareMethodAlias(wxFontData, EnableEffects_gurax, "EnableEffects")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("enable", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFontData, EnableEffects_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool enable = args_gurax.PickBool();
	// Function body
	pEntity_gurax->EnableEffects(enable);
	return Gurax::Value::nil();
}

// wx.FontData#GetAllowSymbols()
Gurax_DeclareMethodAlias(wxFontData, GetAllowSymbols_gurax, "GetAllowSymbols")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxFontData, GetAllowSymbols_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetAllowSymbols();
	return new Gurax::Value_Bool(rtn);
}

// wx.FontData#GetChosenFont() {block?}
Gurax_DeclareMethodAlias(wxFontData, GetChosenFont_gurax, "GetChosenFont")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFontData, GetChosenFont_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFont(pEntity_gurax->GetChosenFont()));
}

// wx.FontData#GetColour() {block?}
Gurax_DeclareMethodAlias(wxFontData, GetColour_gurax, "GetColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFontData, GetColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(pEntity_gurax->GetColour()));
}

// wx.FontData#GetEnableEffects()
Gurax_DeclareMethodAlias(wxFontData, GetEnableEffects_gurax, "GetEnableEffects")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxFontData, GetEnableEffects_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetEnableEffects();
	return new Gurax::Value_Bool(rtn);
}

// wx.FontData#GetInitialFont() {block?}
Gurax_DeclareMethodAlias(wxFontData, GetInitialFont_gurax, "GetInitialFont")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFontData, GetInitialFont_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFont(pEntity_gurax->GetInitialFont()));
}

// wx.FontData#GetShowHelp()
Gurax_DeclareMethodAlias(wxFontData, GetShowHelp_gurax, "GetShowHelp")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxFontData, GetShowHelp_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetShowHelp();
	return new Gurax::Value_Bool(rtn);
}

// wx.FontData#SetAllowSymbols(allowSymbols as Bool)
Gurax_DeclareMethodAlias(wxFontData, SetAllowSymbols_gurax, "SetAllowSymbols")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("allowSymbols", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFontData, SetAllowSymbols_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool allowSymbols = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetAllowSymbols(allowSymbols);
	return Gurax::Value::nil();
}

// wx.FontData#SetChosenFont(font as wx.Font)
Gurax_DeclareMethodAlias(wxFontData, SetChosenFont_gurax, "SetChosenFont")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("font", VTYPE_wxFont, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFontData, SetChosenFont_gurax, processor_gurax, argument_gurax)
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
	pEntity_gurax->SetChosenFont(font);
	return Gurax::Value::nil();
}

// wx.FontData#SetColour(colour as wx.Colour)
Gurax_DeclareMethodAlias(wxFontData, SetColour_gurax, "SetColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colour", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFontData, SetColour_gurax, processor_gurax, argument_gurax)
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
	pEntity_gurax->SetColour(colour);
	return Gurax::Value::nil();
}

// wx.FontData#SetInitialFont(font as wx.Font)
Gurax_DeclareMethodAlias(wxFontData, SetInitialFont_gurax, "SetInitialFont")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("font", VTYPE_wxFont, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFontData, SetInitialFont_gurax, processor_gurax, argument_gurax)
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
	pEntity_gurax->SetInitialFont(font);
	return Gurax::Value::nil();
}

// wx.FontData#SetRange(min as Number, max as Number)
Gurax_DeclareMethodAlias(wxFontData, SetRange_gurax, "SetRange")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("min", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("max", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFontData, SetRange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int min = args_gurax.PickNumber<int>();
	int max = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetRange(min, max);
	return Gurax::Value::nil();
}

// wx.FontData#SetShowHelp(showHelp as Bool)
Gurax_DeclareMethodAlias(wxFontData, SetShowHelp_gurax, "SetShowHelp")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("showHelp", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFontData, SetShowHelp_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool showHelp = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetShowHelp(showHelp);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFontData
//------------------------------------------------------------------------------
VType_wxFontData VTYPE_wxFontData("FontData");

void VType_wxFontData::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(FontData_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFontData, EnableEffects_gurax));
	Assign(Gurax_CreateMethod(wxFontData, GetAllowSymbols_gurax));
	Assign(Gurax_CreateMethod(wxFontData, GetChosenFont_gurax));
	Assign(Gurax_CreateMethod(wxFontData, GetColour_gurax));
	Assign(Gurax_CreateMethod(wxFontData, GetEnableEffects_gurax));
	Assign(Gurax_CreateMethod(wxFontData, GetInitialFont_gurax));
	Assign(Gurax_CreateMethod(wxFontData, GetShowHelp_gurax));
	Assign(Gurax_CreateMethod(wxFontData, SetAllowSymbols_gurax));
	Assign(Gurax_CreateMethod(wxFontData, SetChosenFont_gurax));
	Assign(Gurax_CreateMethod(wxFontData, SetColour_gurax));
	Assign(Gurax_CreateMethod(wxFontData, SetInitialFont_gurax));
	Assign(Gurax_CreateMethod(wxFontData, SetRange_gurax));
	Assign(Gurax_CreateMethod(wxFontData, SetShowHelp_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFontData
//------------------------------------------------------------------------------
VType& Value_wxFontData::vtype = VTYPE_wxFontData;

String Value_wxFontData::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FontData");
}

Gurax_EndModuleScope(wx)
