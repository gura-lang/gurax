﻿//==============================================================================
// VType_wxSlider.cpp
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

${help.ComposePropertyHelp(wx.Slider, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Slider, `en)}

${help.ComposeMethodHelp(wx.Slider, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.Slider, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.Slider, `ja)}

${help.ComposeMethodHelp(wx.Slider, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Slider(parent as wx.Window, id as Number, value as Number, minValue as Number, maxValue as Number, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(Slider_gurax, "Slider")
{
	Declare(VTYPE_wxSlider, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("minValue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxValue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(Slider_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	int value = args_gurax.PickNumber<int>();
	int minValue = args_gurax.PickNumber<int>();
	int maxValue = args_gurax.PickNumber<int>();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxSL_HORIZONTAL;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxSliderNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxSlider::EntityT(parent, id, value, minValue, maxValue, pos, size, style, validator, name);
	RefPtr<Value_wxSlider> pValue_gurax(new Value_wxSlider(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Slider#ClearSel()
Gurax_DeclareMethodAlias(wxSlider, ClearSel_gurax, "ClearSel")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxSlider, ClearSel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->ClearSel();
	return Gurax::Value::nil();
}

// wx.Slider#ClearTicks()
Gurax_DeclareMethodAlias(wxSlider, ClearTicks_gurax, "ClearTicks")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxSlider, ClearTicks_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->ClearTicks();
	return Gurax::Value::nil();
}

// wx.Slider#Create(parent as wx.Window, id as Number, value as Number, minValue as Number, maxValue as Number, point? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String)
Gurax_DeclareMethodAlias(wxSlider, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("minValue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxValue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("point", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSlider, Create_gurax, processor_gurax, argument_gurax)
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
	int value = args_gurax.PickNumber<int>();
	int minValue = args_gurax.PickNumber<int>();
	int maxValue = args_gurax.PickNumber<int>();
	const wxPoint& point = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxSL_HORIZONTAL;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxSliderNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, value, minValue, maxValue, point, size, style, validator, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.Slider#GetLineSize()
Gurax_DeclareMethodAlias(wxSlider, GetLineSize_gurax, "GetLineSize")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSlider, GetLineSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetLineSize();
	return new Gurax::Value_Number(rtn);
}

// wx.Slider#GetMax()
Gurax_DeclareMethodAlias(wxSlider, GetMax_gurax, "GetMax")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSlider, GetMax_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetMax();
	return new Gurax::Value_Number(rtn);
}

// wx.Slider#GetMin()
Gurax_DeclareMethodAlias(wxSlider, GetMin_gurax, "GetMin")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSlider, GetMin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetMin();
	return new Gurax::Value_Number(rtn);
}

// wx.Slider#GetPageSize()
Gurax_DeclareMethodAlias(wxSlider, GetPageSize_gurax, "GetPageSize")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSlider, GetPageSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetPageSize();
	return new Gurax::Value_Number(rtn);
}

// wx.Slider#GetSelEnd()
Gurax_DeclareMethodAlias(wxSlider, GetSelEnd_gurax, "GetSelEnd")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSlider, GetSelEnd_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSelEnd();
	return new Gurax::Value_Number(rtn);
}

// wx.Slider#GetSelStart()
Gurax_DeclareMethodAlias(wxSlider, GetSelStart_gurax, "GetSelStart")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSlider, GetSelStart_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSelStart();
	return new Gurax::Value_Number(rtn);
}

// wx.Slider#GetThumbLength()
Gurax_DeclareMethodAlias(wxSlider, GetThumbLength_gurax, "GetThumbLength")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSlider, GetThumbLength_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetThumbLength();
	return new Gurax::Value_Number(rtn);
}

// wx.Slider#GetTickFreq()
Gurax_DeclareMethodAlias(wxSlider, GetTickFreq_gurax, "GetTickFreq")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSlider, GetTickFreq_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetTickFreq();
	return new Gurax::Value_Number(rtn);
}

// wx.Slider#GetValue()
Gurax_DeclareMethodAlias(wxSlider, GetValue_gurax, "GetValue")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSlider, GetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetValue();
	return new Gurax::Value_Number(rtn);
}

// wx.Slider#SetLineSize(lineSize as Number)
Gurax_DeclareMethodAlias(wxSlider, SetLineSize_gurax, "SetLineSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("lineSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSlider, SetLineSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int lineSize = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetLineSize(lineSize);
	return Gurax::Value::nil();
}

// wx.Slider#SetMin(minValue as Number)
Gurax_DeclareMethodAlias(wxSlider, SetMin_gurax, "SetMin")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("minValue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSlider, SetMin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int minValue = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetMin(minValue);
	return Gurax::Value::nil();
}

// wx.Slider#SetMax(maxValue as Number)
Gurax_DeclareMethodAlias(wxSlider, SetMax_gurax, "SetMax")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("maxValue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSlider, SetMax_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int maxValue = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetMax(maxValue);
	return Gurax::Value::nil();
}

// wx.Slider#SetPageSize(pageSize as Number)
Gurax_DeclareMethodAlias(wxSlider, SetPageSize_gurax, "SetPageSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pageSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSlider, SetPageSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int pageSize = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetPageSize(pageSize);
	return Gurax::Value::nil();
}

// wx.Slider#SetRange(minValue as Number, maxValue as Number)
Gurax_DeclareMethodAlias(wxSlider, SetRange_gurax, "SetRange")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("minValue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxValue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSlider, SetRange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int minValue = args_gurax.PickNumber<int>();
	int maxValue = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetRange(minValue, maxValue);
	return Gurax::Value::nil();
}

// wx.Slider#SetSelection(startPos as Number, endPos as Number)
Gurax_DeclareMethodAlias(wxSlider, SetSelection_gurax, "SetSelection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("startPos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("endPos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSlider, SetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int startPos = args_gurax.PickNumber<int>();
	int endPos = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetSelection(startPos, endPos);
	return Gurax::Value::nil();
}

// wx.Slider#SetThumbLength(len as Number)
Gurax_DeclareMethodAlias(wxSlider, SetThumbLength_gurax, "SetThumbLength")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("len", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSlider, SetThumbLength_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int len = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetThumbLength(len);
	return Gurax::Value::nil();
}

// wx.Slider#SetTick(tickPos as Number)
Gurax_DeclareMethodAlias(wxSlider, SetTick_gurax, "SetTick")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("tickPos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSlider, SetTick_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int tickPos = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetTick(tickPos);
	return Gurax::Value::nil();
}

// wx.Slider#SetTickFreq(n as Number)
Gurax_DeclareMethodAlias(wxSlider, SetTickFreq_gurax, "SetTickFreq")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSlider, SetTickFreq_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int n = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetTickFreq(n);
	return Gurax::Value::nil();
}

// wx.Slider#SetValue(value as Number)
Gurax_DeclareMethodAlias(wxSlider, SetValue_gurax, "SetValue")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSlider, SetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int value = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetValue(value);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSlider
//------------------------------------------------------------------------------
VType_wxSlider VTYPE_wxSlider("Slider");

void VType_wxSlider::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(Slider_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSlider, ClearSel_gurax));
	Assign(Gurax_CreateMethod(wxSlider, ClearTicks_gurax));
	Assign(Gurax_CreateMethod(wxSlider, Create_gurax));
	Assign(Gurax_CreateMethod(wxSlider, GetLineSize_gurax));
	Assign(Gurax_CreateMethod(wxSlider, GetMax_gurax));
	Assign(Gurax_CreateMethod(wxSlider, GetMin_gurax));
	Assign(Gurax_CreateMethod(wxSlider, GetPageSize_gurax));
	Assign(Gurax_CreateMethod(wxSlider, GetSelEnd_gurax));
	Assign(Gurax_CreateMethod(wxSlider, GetSelStart_gurax));
	Assign(Gurax_CreateMethod(wxSlider, GetThumbLength_gurax));
	Assign(Gurax_CreateMethod(wxSlider, GetTickFreq_gurax));
	Assign(Gurax_CreateMethod(wxSlider, GetValue_gurax));
	Assign(Gurax_CreateMethod(wxSlider, SetLineSize_gurax));
	Assign(Gurax_CreateMethod(wxSlider, SetMin_gurax));
	Assign(Gurax_CreateMethod(wxSlider, SetMax_gurax));
	Assign(Gurax_CreateMethod(wxSlider, SetPageSize_gurax));
	Assign(Gurax_CreateMethod(wxSlider, SetRange_gurax));
	Assign(Gurax_CreateMethod(wxSlider, SetSelection_gurax));
	Assign(Gurax_CreateMethod(wxSlider, SetThumbLength_gurax));
	Assign(Gurax_CreateMethod(wxSlider, SetTick_gurax));
	Assign(Gurax_CreateMethod(wxSlider, SetTickFreq_gurax));
	Assign(Gurax_CreateMethod(wxSlider, SetValue_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSlider
//------------------------------------------------------------------------------
VType& Value_wxSlider::vtype = VTYPE_wxSlider;

String Value_wxSlider::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Slider");
}

//------------------------------------------------------------------------------
// Value_wxSlider::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
