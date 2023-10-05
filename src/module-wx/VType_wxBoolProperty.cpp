﻿//==============================================================================
// VType_wxBoolProperty.cpp
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

${help.ComposePropertyHelp(wx.BoolProperty, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.BoolProperty, `en)}

${help.ComposeMethodHelp(wx.BoolProperty, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.BoolProperty, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.BoolProperty, `ja)}

${help.ComposeMethodHelp(wx.BoolProperty, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.BoolProperty(label? as String, name? as String, value? as Bool) {block?}
Gurax_DeclareConstructorAlias(BoolProperty_gurax, "BoolProperty")
{
	Declare(VTYPE_wxBoolProperty, Flag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("value", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(BoolProperty_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* label = args_gurax.IsValid()? args_gurax.PickString() : wxPG_LABEL;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxPG_LABEL;
	bool value = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBoolProperty(
		wxBoolProperty(label, name, value)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.BoolProperty#ValueToString(value as wx.Variant, argFlags? as Number)
Gurax_DeclareMethodAlias(wxBoolProperty, ValueToString_gurax, "ValueToString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("value", VTYPE_wxVariant, ArgOccur::Once, ArgFlag::None);
	DeclareArg("argFlags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxBoolProperty, ValueToString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxVariant& value_value = args_gurax.Pick<Value_wxVariant>();
	wxVariant& value = value_value.GetEntity();
	bool argFlags_validFlag = args_gurax.IsValid();
	int argFlags = argFlags_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	wxString rtn = pEntity_gurax->ValueToString(value, argFlags);
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.BoolProperty#StringToValue(variant as wx.Variant, text as String, argFlags? as Number)
Gurax_DeclareMethodAlias(wxBoolProperty, StringToValue_gurax, "StringToValue")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("variant", VTYPE_wxVariant, ArgOccur::Once, ArgFlag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("argFlags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxBoolProperty, StringToValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxVariant& value_variant = args_gurax.Pick<Value_wxVariant>();
	wxVariant& variant = value_variant.GetEntity();
	const char* text = args_gurax.PickString();
	bool argFlags_validFlag = args_gurax.IsValid();
	int argFlags = argFlags_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	bool rtn = pEntity_gurax->StringToValue(variant, text, argFlags);
	return new Gurax::Value_Bool(rtn);
}

// wx.BoolProperty#IntToValue(variant as wx.Variant, number as Number, argFlags? as Number)
Gurax_DeclareMethodAlias(wxBoolProperty, IntToValue_gurax, "IntToValue")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("variant", VTYPE_wxVariant, ArgOccur::Once, ArgFlag::None);
	DeclareArg("number", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("argFlags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxBoolProperty, IntToValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxVariant& value_variant = args_gurax.Pick<Value_wxVariant>();
	wxVariant& variant = value_variant.GetEntity();
	int number = args_gurax.PickNumber<int>();
	bool argFlags_validFlag = args_gurax.IsValid();
	int argFlags = argFlags_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	bool rtn = pEntity_gurax->IntToValue(variant, number, argFlags);
	return new Gurax::Value_Bool(rtn);
}

// wx.BoolProperty#DoSetAttribute(name as String, value as wx.Variant)
Gurax_DeclareMethodAlias(wxBoolProperty, DoSetAttribute_gurax, "DoSetAttribute")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_wxVariant, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxBoolProperty, DoSetAttribute_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	Value_wxVariant& value_value = args_gurax.Pick<Value_wxVariant>();
	wxVariant& value = value_value.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->DoSetAttribute(name, value);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxBoolProperty
//------------------------------------------------------------------------------
VType_wxBoolProperty VTYPE_wxBoolProperty("BoolProperty");

void VType_wxBoolProperty::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxPGProperty, Flag::Mutable, Gurax_CreateConstructor(BoolProperty_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxBoolProperty, ValueToString_gurax));
	Assign(Gurax_CreateMethod(wxBoolProperty, StringToValue_gurax));
	Assign(Gurax_CreateMethod(wxBoolProperty, IntToValue_gurax));
	Assign(Gurax_CreateMethod(wxBoolProperty, DoSetAttribute_gurax));
}

//------------------------------------------------------------------------------
// Value_wxBoolProperty
//------------------------------------------------------------------------------
VType& Value_wxBoolProperty::vtype = VTYPE_wxBoolProperty;

String Value_wxBoolProperty::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.BoolProperty");
}

Gurax_EndModuleScope(wx)
