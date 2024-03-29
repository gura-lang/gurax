﻿//==============================================================================
// VType_wxGauge.cpp
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

${help.ComposePropertyHelp(wx.Gauge, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Gauge, `en)}

${help.ComposeMethodHelp(wx.Gauge, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.Gauge, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.Gauge, `ja)}

${help.ComposeMethodHelp(wx.Gauge, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Gauge(parent as wx.Window, id as Number, range as Number, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(Gauge_gurax, "Gauge")
{
	Declare(VTYPE_wxGauge, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("range", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(Gauge_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	int range = args_gurax.PickNumber<int>();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxGA_HORIZONTAL;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	bool name_validFlag = args_gurax.IsValid();
	wxString name = name_validFlag? wxString(args_gurax.PickString()) : wxGaugeNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxGauge::EntityT(parent, id, range, pos, size, style, validator, name);
	RefPtr<Value_wxGauge> pValue_gurax(new Value_wxGauge(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Gauge#GetBezelFace()
Gurax_DeclareMethodAlias(wxGauge, GetBezelFace_gurax, "GetBezelFace")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxGauge, GetBezelFace_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetBezelFace();
	return new Gurax::Value_Number(rtn);
}

// wx.Gauge#GetRange()
Gurax_DeclareMethodAlias(wxGauge, GetRange_gurax, "GetRange")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxGauge, GetRange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetRange();
	return new Gurax::Value_Number(rtn);
}

// wx.Gauge#GetShadowWidth()
Gurax_DeclareMethodAlias(wxGauge, GetShadowWidth_gurax, "GetShadowWidth")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxGauge, GetShadowWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetShadowWidth();
	return new Gurax::Value_Number(rtn);
}

// wx.Gauge#GetValue()
Gurax_DeclareMethodAlias(wxGauge, GetValue_gurax, "GetValue")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxGauge, GetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetValue();
	return new Gurax::Value_Number(rtn);
}

// wx.Gauge#IsVertical()
Gurax_DeclareMethodAlias(wxGauge, IsVertical_gurax, "IsVertical")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGauge, IsVertical_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsVertical();
	return new Gurax::Value_Bool(rtn);
}

// wx.Gauge#Pulse()
Gurax_DeclareMethodAlias(wxGauge, Pulse_gurax, "Pulse")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxGauge, Pulse_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Pulse();
	return Gurax::Value::nil();
}

// wx.Gauge#SetBezelFace(width as Number)
Gurax_DeclareMethodAlias(wxGauge, SetBezelFace_gurax, "SetBezelFace")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGauge, SetBezelFace_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetBezelFace(width);
	return Gurax::Value::nil();
}

// wx.Gauge#SetRange(range as Number)
Gurax_DeclareMethodAlias(wxGauge, SetRange_gurax, "SetRange")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("range", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGauge, SetRange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int range = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetRange(range);
	return Gurax::Value::nil();
}

// wx.Gauge#SetShadowWidth(width as Number)
Gurax_DeclareMethodAlias(wxGauge, SetShadowWidth_gurax, "SetShadowWidth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGauge, SetShadowWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetShadowWidth(width);
	return Gurax::Value::nil();
}

// wx.Gauge#SetValue(pos as Number)
Gurax_DeclareMethodAlias(wxGauge, SetValue_gurax, "SetValue")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGauge, SetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int pos = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetValue(pos);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGauge
//------------------------------------------------------------------------------
VType_wxGauge VTYPE_wxGauge("Gauge");

void VType_wxGauge::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(Gauge_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGauge, GetBezelFace_gurax));
	Assign(Gurax_CreateMethod(wxGauge, GetRange_gurax));
	Assign(Gurax_CreateMethod(wxGauge, GetShadowWidth_gurax));
	Assign(Gurax_CreateMethod(wxGauge, GetValue_gurax));
	Assign(Gurax_CreateMethod(wxGauge, IsVertical_gurax));
	Assign(Gurax_CreateMethod(wxGauge, Pulse_gurax));
	Assign(Gurax_CreateMethod(wxGauge, SetBezelFace_gurax));
	Assign(Gurax_CreateMethod(wxGauge, SetRange_gurax));
	Assign(Gurax_CreateMethod(wxGauge, SetShadowWidth_gurax));
	Assign(Gurax_CreateMethod(wxGauge, SetValue_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGauge
//------------------------------------------------------------------------------
VType& Value_wxGauge::vtype = VTYPE_wxGauge;

String Value_wxGauge::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Gauge");
}

//------------------------------------------------------------------------------
// Value_wxGauge::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
