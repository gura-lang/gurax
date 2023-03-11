﻿//==============================================================================
// VType_wxFontProperty.cpp
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

${help.ComposePropertyHelp(wx.FontProperty, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.FontProperty, `en)}

${help.ComposeMethodHelp(wx.FontProperty, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.FontProperty, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.FontProperty, `ja)}

${help.ComposeMethodHelp(wx.FontProperty, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.FontProperty(label? as String, name? as String, value? as wx.Font) {block?}
Gurax_DeclareConstructorAlias(FontProperty_gurax, "FontProperty")
{
	Declare(VTYPE_wxFontProperty, Flag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("value", VTYPE_wxFont, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(FontProperty_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* label = args_gurax.IsValid()? args_gurax.PickString() : wxPG_LABEL;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxPG_LABEL;
	const wxFont& value = args_gurax.IsValid()? args_gurax.Pick<Value_wxFont>().GetEntity() : wxFont();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFontProperty(
		wxFontProperty(label, name, value)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.FontProperty#OnSetValue()
Gurax_DeclareMethodAlias(wxFontProperty, OnSetValue_gurax, "OnSetValue")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxFontProperty, OnSetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->OnSetValue();
	return Gurax::Value::nil();
}

// wx.FontProperty#ValueToString(value as wx.Variant, argFlags? as Number)
Gurax_DeclareMethodAlias(wxFontProperty, ValueToString_gurax, "ValueToString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("value", VTYPE_wxVariant, ArgOccur::Once, ArgFlag::None);
	DeclareArg("argFlags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFontProperty, ValueToString_gurax, processor_gurax, argument_gurax)
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
	//return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.FontProperty#OnEvent(propgrid as wx.PropertyGrid, primary as wx.Window, event as wx.Event)
Gurax_DeclareMethodAlias(wxFontProperty, OnEvent_gurax, "OnEvent")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("propgrid", VTYPE_wxPropertyGrid, ArgOccur::Once, ArgFlag::None);
	DeclareArg("primary", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("event", VTYPE_wxEvent, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFontProperty, OnEvent_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPropertyGrid& value_propgrid = args_gurax.Pick<Value_wxPropertyGrid>();
	wxPropertyGrid* propgrid = value_propgrid.GetEntityPtr();
	Value_wxWindow& value_primary = args_gurax.Pick<Value_wxWindow>();
	wxWindow* primary = value_primary.GetEntityPtr();
	Value_wxEvent& value_event = args_gurax.Pick<Value_wxEvent>();
	wxEvent& event = value_event.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->OnEvent(propgrid, primary, event);
	return new Gurax::Value_Bool(rtn);
}

// wx.FontProperty#ChildChanged(thisValue as wx.Variant, childIndex as Number, childValue as wx.Variant) {block?}
Gurax_DeclareMethodAlias(wxFontProperty, ChildChanged_gurax, "ChildChanged")
{
	Declare(VTYPE_wxVariant, Flag::None);
	DeclareArg("thisValue", VTYPE_wxVariant, ArgOccur::Once, ArgFlag::None);
	DeclareArg("childIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("childValue", VTYPE_wxVariant, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFontProperty, ChildChanged_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxVariant& value_thisValue = args_gurax.Pick<Value_wxVariant>();
	wxVariant& thisValue = value_thisValue.GetEntity();
	int childIndex = args_gurax.PickNumber<int>();
	Value_wxVariant& value_childValue = args_gurax.Pick<Value_wxVariant>();
	wxVariant& childValue = value_childValue.GetEntity();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxVariant(
		pEntity_gurax->ChildChanged(thisValue, childIndex, childValue)));
}

// wx.FontProperty#RefreshChildren()
Gurax_DeclareMethodAlias(wxFontProperty, RefreshChildren_gurax, "RefreshChildren")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxFontProperty, RefreshChildren_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->RefreshChildren();
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFontProperty
//------------------------------------------------------------------------------
VType_wxFontProperty VTYPE_wxFontProperty("FontProperty");

void VType_wxFontProperty::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxPGProperty, Flag::Mutable, Gurax_CreateConstructor(FontProperty_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFontProperty, OnSetValue_gurax));
	Assign(Gurax_CreateMethod(wxFontProperty, ValueToString_gurax));
	Assign(Gurax_CreateMethod(wxFontProperty, OnEvent_gurax));
	Assign(Gurax_CreateMethod(wxFontProperty, ChildChanged_gurax));
	Assign(Gurax_CreateMethod(wxFontProperty, RefreshChildren_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFontProperty
//------------------------------------------------------------------------------
VType& Value_wxFontProperty::vtype = VTYPE_wxFontProperty;

String Value_wxFontProperty::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FontProperty");
}

Gurax_EndModuleScope(wx)
