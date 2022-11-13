﻿//==============================================================================
// VType_wxCursorProperty.cpp
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

${help.ComposePropertyHelp(wx.CursorProperty, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.CursorProperty, `en)}

${help.ComposeMethodHelp(wx.CursorProperty, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.CursorProperty(label? as String, name? as String, value? as Number) {block?}
Gurax_DeclareConstructorAlias(CursorProperty_gurax, "CursorProperty")
{
	Declare(VTYPE_wxCursorProperty, Flag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates an instance of wx.CursorProperty.
)**");
}

Gurax_ImplementConstructorEx(CursorProperty_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* label = args_gurax.IsValid()? args_gurax.PickString() : wxPG_LABEL;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxPG_LABEL;
	bool value_validFlag = args_gurax.IsValid();
	int value = value_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxCursorProperty(
		wxCursorProperty(label, name, value)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.CursorProperty#OnMeasureImage(item as Number) {block?}
Gurax_DeclareMethodAlias(wxCursorProperty, OnMeasureImage_gurax, "OnMeasureImage")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxCursorProperty, OnMeasureImage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int item = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->OnMeasureImage(item)));
}

// wx.CursorProperty#OnCustomPaint(dc as wx.DC, rect as wx.Rect, paintdata as wx.PGPaintData)
Gurax_DeclareMethodAlias(wxCursorProperty, OnCustomPaint_gurax, "OnCustomPaint")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dc", VTYPE_wxDC, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("paintdata", VTYPE_wxPGPaintData, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxCursorProperty, OnCustomPaint_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDC& value_dc = args_gurax.Pick<Value_wxDC>();
	wxDC& dc = value_dc.GetEntity();
	Value_wxRect& value_rect = args_gurax.Pick<Value_wxRect>();
	const wxRect& rect = value_rect.GetEntity();
	Value_wxPGPaintData& value_paintdata = args_gurax.Pick<Value_wxPGPaintData>();
	wxPGPaintData& paintdata = value_paintdata.GetEntity();
	// Function body
	pEntity_gurax->OnCustomPaint(dc, rect, paintdata);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxCursorProperty
//------------------------------------------------------------------------------
VType_wxCursorProperty VTYPE_wxCursorProperty("CursorProperty");

void VType_wxCursorProperty::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEnumProperty, Flag::Mutable, Gurax_CreateConstructor(CursorProperty_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxCursorProperty, OnMeasureImage_gurax));
	Assign(Gurax_CreateMethod(wxCursorProperty, OnCustomPaint_gurax));
}

//------------------------------------------------------------------------------
// Value_wxCursorProperty
//------------------------------------------------------------------------------
VType& Value_wxCursorProperty::vtype = VTYPE_wxCursorProperty;

String Value_wxCursorProperty::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.CursorProperty");
}

Gurax_EndModuleScope(wx)
