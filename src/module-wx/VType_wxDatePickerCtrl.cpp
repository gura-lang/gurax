﻿//==============================================================================
// VType_wxDatePickerCtrl.cpp
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

${help.ComposePropertyHelp(wx.DatePickerCtrl, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DatePickerCtrl, `en)}

${help.ComposeMethodHelp(wx.DatePickerCtrl, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.DatePickerCtrl(parent as wx.Window, id as Number, dt? as wx.DateTime, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(DatePickerCtrl_gurax, "DatePickerCtrl")
{
	Declare(VTYPE_wxDatePickerCtrl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dt", VTYPE_wxDateTime, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(DatePickerCtrl_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxDateTime& dt = args_gurax.IsValid()? args_gurax.Pick<Value_wxDateTime>().GetEntity() : wxDefaultDateTime;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : (wxDP_DEFAULT | wxDP_SHOWCENTURY);
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : "datectrl";
	// Function body
	auto pEntity_gurax = new Value_wxDatePickerCtrl::EntityT(parent, id, dt, pos, size, style, validator, name);
	RefPtr<Value_wxDatePickerCtrl> pValue_gurax(new Value_wxDatePickerCtrl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.DatePickerCtrl#Create(parent as wx.Window, id as Number, dt? as wx.DateTime, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String)
Gurax_DeclareMethodAlias(wxDatePickerCtrl, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dt", VTYPE_wxDateTime, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxDatePickerCtrl, Create_gurax, processor_gurax, argument_gurax)
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
	const wxDateTime& dt = args_gurax.IsValid()? args_gurax.Pick<Value_wxDateTime>().GetEntity() : wxDefaultDateTime;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : (wxDP_DEFAULT | wxDP_SHOWCENTURY);
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : "datectrl";
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, dt, pos, size, style, validator, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.DatePickerCtrl#GetRange(dt1 as wx.DateTime, dt2 as wx.DateTime)
Gurax_DeclareMethodAlias(wxDatePickerCtrl, GetRange_gurax, "GetRange")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("dt1", VTYPE_wxDateTime, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dt2", VTYPE_wxDateTime, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxDatePickerCtrl, GetRange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDateTime& value_dt1 = args_gurax.Pick<Value_wxDateTime>();
	wxDateTime* dt1 = value_dt1.GetEntityPtr();
	Value_wxDateTime& value_dt2 = args_gurax.Pick<Value_wxDateTime>();
	wxDateTime* dt2 = value_dt2.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->GetRange(dt1, dt2);
	return new Gurax::Value_Bool(rtn);
}

// wx.DatePickerCtrl#GetValue() {block?}
Gurax_DeclareMethodAlias(wxDatePickerCtrl, GetValue_gurax, "GetValue")
{
	Declare(VTYPE_wxDateTime, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxDatePickerCtrl, GetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateTime(
		pEntity_gurax->GetValue()));
}

// wx.DatePickerCtrl#SetRange(dt1 as wx.DateTime, dt2 as wx.DateTime)
Gurax_DeclareMethodAlias(wxDatePickerCtrl, SetRange_gurax, "SetRange")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dt1", VTYPE_wxDateTime, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dt2", VTYPE_wxDateTime, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxDatePickerCtrl, SetRange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDateTime& value_dt1 = args_gurax.Pick<Value_wxDateTime>();
	const wxDateTime& dt1 = value_dt1.GetEntity();
	Value_wxDateTime& value_dt2 = args_gurax.Pick<Value_wxDateTime>();
	const wxDateTime& dt2 = value_dt2.GetEntity();
	// Function body
	pEntity_gurax->SetRange(dt1, dt2);
	return Gurax::Value::nil();
}

// wx.DatePickerCtrl#SetValue(dt as wx.DateTime)
Gurax_DeclareMethodAlias(wxDatePickerCtrl, SetValue_gurax, "SetValue")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dt", VTYPE_wxDateTime, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxDatePickerCtrl, SetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDateTime& value_dt = args_gurax.Pick<Value_wxDateTime>();
	const wxDateTime& dt = value_dt.GetEntity();
	// Function body
	pEntity_gurax->SetValue(dt);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxDatePickerCtrl
//------------------------------------------------------------------------------
VType_wxDatePickerCtrl VTYPE_wxDatePickerCtrl("DatePickerCtrl");

void VType_wxDatePickerCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(DatePickerCtrl_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxDatePickerCtrl, Create_gurax));
	Assign(Gurax_CreateMethod(wxDatePickerCtrl, GetRange_gurax));
	Assign(Gurax_CreateMethod(wxDatePickerCtrl, GetValue_gurax));
	Assign(Gurax_CreateMethod(wxDatePickerCtrl, SetRange_gurax));
	Assign(Gurax_CreateMethod(wxDatePickerCtrl, SetValue_gurax));
}

//------------------------------------------------------------------------------
// Value_wxDatePickerCtrl
//------------------------------------------------------------------------------
VType& Value_wxDatePickerCtrl::vtype = VTYPE_wxDatePickerCtrl;

String Value_wxDatePickerCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DatePickerCtrl");
}

//------------------------------------------------------------------------------
// Value_wxDatePickerCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
