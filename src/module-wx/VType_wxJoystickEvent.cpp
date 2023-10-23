﻿//==============================================================================
// VType_wxJoystickEvent.cpp
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

${help.ComposePropertyHelp(wx.JoystickEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.JoystickEvent, `en)}

${help.ComposeMethodHelp(wx.JoystickEvent, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.JoystickEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.JoystickEvent, `ja)}

${help.ComposeMethodHelp(wx.JoystickEvent, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.JoystickEvent#ButtonDown(button? as Number)
Gurax_DeclareMethodAlias(wxJoystickEvent, ButtonDown_gurax, "ButtonDown")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("button", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxJoystickEvent, ButtonDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool button_validFlag = args_gurax.IsValid();
	int button = button_validFlag? args_gurax.PickNumber<int>() : wxJOY_BUTTON_ANY;
	// Function body
	bool rtn = pEntity_gurax->ButtonDown(button);
	return new Gurax::Value_Bool(rtn);
}

// wx.JoystickEvent#ButtonIsDown(button? as Number)
Gurax_DeclareMethodAlias(wxJoystickEvent, ButtonIsDown_gurax, "ButtonIsDown")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("button", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxJoystickEvent, ButtonIsDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool button_validFlag = args_gurax.IsValid();
	int button = button_validFlag? args_gurax.PickNumber<int>() : wxJOY_BUTTON_ANY;
	// Function body
	bool rtn = pEntity_gurax->ButtonIsDown(button);
	return new Gurax::Value_Bool(rtn);
}

// wx.JoystickEvent#ButtonUp(button? as Number)
Gurax_DeclareMethodAlias(wxJoystickEvent, ButtonUp_gurax, "ButtonUp")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("button", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxJoystickEvent, ButtonUp_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool button_validFlag = args_gurax.IsValid();
	int button = button_validFlag? args_gurax.PickNumber<int>() : wxJOY_BUTTON_ANY;
	// Function body
	bool rtn = pEntity_gurax->ButtonUp(button);
	return new Gurax::Value_Bool(rtn);
}

// wx.JoystickEvent#GetButtonChange()
Gurax_DeclareMethodAlias(wxJoystickEvent, GetButtonChange_gurax, "GetButtonChange")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxJoystickEvent, GetButtonChange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetButtonChange();
	return new Gurax::Value_Number(rtn);
}

// wx.JoystickEvent#GetButtonState()
Gurax_DeclareMethodAlias(wxJoystickEvent, GetButtonState_gurax, "GetButtonState")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxJoystickEvent, GetButtonState_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetButtonState();
	return new Gurax::Value_Number(rtn);
}

// wx.JoystickEvent#GetJoystick()
Gurax_DeclareMethodAlias(wxJoystickEvent, GetJoystick_gurax, "GetJoystick")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxJoystickEvent, GetJoystick_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetJoystick();
	return new Gurax::Value_Number(rtn);
}

// wx.JoystickEvent#GetPosition() {block?}
Gurax_DeclareMethodAlias(wxJoystickEvent, GetPosition_gurax, "GetPosition")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxJoystickEvent, GetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(pEntity_gurax->GetPosition()));
}

// wx.JoystickEvent#GetZPosition()
Gurax_DeclareMethodAlias(wxJoystickEvent, GetZPosition_gurax, "GetZPosition")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxJoystickEvent, GetZPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetZPosition();
	return new Gurax::Value_Number(rtn);
}

// wx.JoystickEvent#IsButton()
Gurax_DeclareMethodAlias(wxJoystickEvent, IsButton_gurax, "IsButton")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxJoystickEvent, IsButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsButton();
	return new Gurax::Value_Bool(rtn);
}

// wx.JoystickEvent#IsMove()
Gurax_DeclareMethodAlias(wxJoystickEvent, IsMove_gurax, "IsMove")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxJoystickEvent, IsMove_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsMove();
	return new Gurax::Value_Bool(rtn);
}

// wx.JoystickEvent#IsZMove()
Gurax_DeclareMethodAlias(wxJoystickEvent, IsZMove_gurax, "IsZMove")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxJoystickEvent, IsZMove_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsZMove();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxJoystickEvent
//------------------------------------------------------------------------------
VType_wxJoystickEvent VTYPE_wxJoystickEvent("JoystickEvent");

void VType_wxJoystickEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxJoystickEvent, ButtonDown_gurax));
	Assign(Gurax_CreateMethod(wxJoystickEvent, ButtonIsDown_gurax));
	Assign(Gurax_CreateMethod(wxJoystickEvent, ButtonUp_gurax));
	Assign(Gurax_CreateMethod(wxJoystickEvent, GetButtonChange_gurax));
	Assign(Gurax_CreateMethod(wxJoystickEvent, GetButtonState_gurax));
	Assign(Gurax_CreateMethod(wxJoystickEvent, GetJoystick_gurax));
	Assign(Gurax_CreateMethod(wxJoystickEvent, GetPosition_gurax));
	Assign(Gurax_CreateMethod(wxJoystickEvent, GetZPosition_gurax));
	Assign(Gurax_CreateMethod(wxJoystickEvent, IsButton_gurax));
	Assign(Gurax_CreateMethod(wxJoystickEvent, IsMove_gurax));
	Assign(Gurax_CreateMethod(wxJoystickEvent, IsZMove_gurax));
}

//------------------------------------------------------------------------------
// Value_wxJoystickEvent
//------------------------------------------------------------------------------
VType& Value_wxJoystickEvent::vtype = VTYPE_wxJoystickEvent;
EventValueFactoryDeriv<Value_wxJoystickEvent> Value_wxJoystickEvent::eventValueFactory;

String Value_wxJoystickEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.JoystickEvent");
}

Gurax_EndModuleScope(wx)
