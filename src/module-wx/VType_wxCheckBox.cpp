﻿//==============================================================================
// VType_wxCheckBox.cpp
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

${help.ComposePropertyHelp(wx.CheckBox, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.CheckBox, `en)}

${help.ComposeMethodHelp(wx.CheckBox, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.CheckBox, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.CheckBox, `ja)}

${help.ComposeMethodHelp(wx.CheckBox, `ja)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.CheckBox(parent as wx.Window, id as Number, label as String, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(CheckBox_gurax, "CheckBox")
{
	Declare(VTYPE_wxCheckBox, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(CheckBox_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const char* label = args_gurax.PickString();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxCheckBoxNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxCheckBox::EntityT(parent, id, label, pos, size, style, validator, name);
	RefPtr<Value_wxCheckBox> pValue_gurax(new Value_wxCheckBox(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.CheckBox#GetValue()
Gurax_DeclareMethodAlias(wxCheckBox, GetValue_gurax, "GetValue")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxCheckBox, GetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetValue();
	return new Gurax::Value_Bool(rtn);
}

// wx.CheckBox#Get3StateValue()
Gurax_DeclareMethodAlias(wxCheckBox, Get3StateValue_gurax, "Get3StateValue")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxCheckBox, Get3StateValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxCheckBoxState rtn = pEntity_gurax->Get3StateValue();
	return new Gurax::Value_Number(rtn);
}

// wx.CheckBox#Is3State()
Gurax_DeclareMethodAlias(wxCheckBox, Is3State_gurax, "Is3State")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxCheckBox, Is3State_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Is3State();
	return new Gurax::Value_Bool(rtn);
}

// wx.CheckBox#Is3rdStateAllowedForUser()
Gurax_DeclareMethodAlias(wxCheckBox, Is3rdStateAllowedForUser_gurax, "Is3rdStateAllowedForUser")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxCheckBox, Is3rdStateAllowedForUser_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Is3rdStateAllowedForUser();
	return new Gurax::Value_Bool(rtn);
}

// wx.CheckBox#IsChecked()
Gurax_DeclareMethodAlias(wxCheckBox, IsChecked_gurax, "IsChecked")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxCheckBox, IsChecked_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsChecked();
	return new Gurax::Value_Bool(rtn);
}

// wx.CheckBox#SetValue(state as Bool)
Gurax_DeclareMethodAlias(wxCheckBox, SetValue_gurax, "SetValue")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("state", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxCheckBox, SetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool state = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetValue(state);
	return Gurax::Value::nil();
}

// wx.CheckBox#Set3StateValue(state as Number)
Gurax_DeclareMethodAlias(wxCheckBox, Set3StateValue_gurax, "Set3StateValue")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("state", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxCheckBox, Set3StateValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxCheckBoxState state = args_gurax.PickNumber<wxCheckBoxState>();
	// Function body
	pEntity_gurax->Set3StateValue(state);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxCheckBox
//------------------------------------------------------------------------------
VType_wxCheckBox VTYPE_wxCheckBox("CheckBox");

void VType_wxCheckBox::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(CheckBox_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxCheckBox, GetValue_gurax));
	Assign(Gurax_CreateMethod(wxCheckBox, Get3StateValue_gurax));
	Assign(Gurax_CreateMethod(wxCheckBox, Is3State_gurax));
	Assign(Gurax_CreateMethod(wxCheckBox, Is3rdStateAllowedForUser_gurax));
	Assign(Gurax_CreateMethod(wxCheckBox, IsChecked_gurax));
	Assign(Gurax_CreateMethod(wxCheckBox, SetValue_gurax));
	Assign(Gurax_CreateMethod(wxCheckBox, Set3StateValue_gurax));
}

//------------------------------------------------------------------------------
// Value_wxCheckBox
//------------------------------------------------------------------------------
VType& Value_wxCheckBox::vtype = VTYPE_wxCheckBox;

String Value_wxCheckBox::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.CheckBox");
}

//------------------------------------------------------------------------------
// Value_wxCheckBox::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
