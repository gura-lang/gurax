﻿//==============================================================================
// VType_wxColourProperty.cpp
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

${help.ComposePropertyHelp(wx.ColourProperty, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.ColourProperty, `en)}

${help.ComposeMethodHelp(wx.ColourProperty, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.ColourProperty(label? as String, name? as String, value? as wx.Colour) {block?}
Gurax_DeclareConstructorAlias(ColourProperty_gurax, "ColourProperty")
{
	Declare(VTYPE_wxColourProperty, Flag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("value", VTYPE_wxColour, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.ColourProperty.
)**");
}

Gurax_ImplementConstructorEx(ColourProperty_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* label = args_gurax.IsValid()? args_gurax.PickString() : wxPG_LABEL;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxPG_LABEL;
	const wxColour& value = args_gurax.IsValid()? args_gurax.Pick<Value_wxColour>().GetEntity() : *wxWHITE;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColourProperty(
		wxColourProperty(label, name, value)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ColourProperty#ValueToString(value as wx.Variant, argFlags? as Number)
Gurax_DeclareMethodAlias(wxColourProperty, ValueToString_gurax, "ValueToString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("value", VTYPE_wxVariant, ArgOccur::Once, ArgFlag::None);
	DeclareArg("argFlags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxColourProperty, ValueToString_gurax, processor_gurax, argument_gurax)
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
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.ColourProperty#GetColour(index as Number) {block?}
Gurax_DeclareMethodAlias(wxColourProperty, GetColour_gurax, "GetColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxColourProperty, GetColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetColour(index)));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxColourProperty
//------------------------------------------------------------------------------
VType_wxColourProperty VTYPE_wxColourProperty("ColourProperty");

void VType_wxColourProperty::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxSystemColourProperty, Flag::Mutable, Gurax_CreateConstructor(ColourProperty_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxColourProperty, ValueToString_gurax));
	Assign(Gurax_CreateMethod(wxColourProperty, GetColour_gurax));
}

//------------------------------------------------------------------------------
// Value_wxColourProperty
//------------------------------------------------------------------------------
VType& Value_wxColourProperty::vtype = VTYPE_wxColourProperty;

String Value_wxColourProperty::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ColourProperty");
}

Gurax_EndModuleScope(wx)
