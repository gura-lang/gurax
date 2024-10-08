﻿//==============================================================================
// VType_wxMouseState.cpp
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

${help.ComposePropertyHelp(wx.MouseState, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.MouseState, `en)}

${help.ComposeMethodHelp(wx.MouseState, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.MouseState, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.MouseState, `ja)}

${help.ComposeMethodHelp(wx.MouseState, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.MouseState#GetX()
Gurax_DeclareMethodAlias(wxMouseState, GetX_gurax, "GetX")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxMouseState, GetX_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxCoord rtn = pEntity_gurax->GetX();
	return new Gurax::Value_Number(rtn);
}

// wx.MouseState#GetY()
Gurax_DeclareMethodAlias(wxMouseState, GetY_gurax, "GetY")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxMouseState, GetY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxCoord rtn = pEntity_gurax->GetY();
	return new Gurax::Value_Number(rtn);
}

// wx.MouseState#LeftIsDown()
Gurax_DeclareMethodAlias(wxMouseState, LeftIsDown_gurax, "LeftIsDown")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMouseState, LeftIsDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->LeftIsDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.MouseState#MiddleIsDown()
Gurax_DeclareMethodAlias(wxMouseState, MiddleIsDown_gurax, "MiddleIsDown")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMouseState, MiddleIsDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->MiddleIsDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.MouseState#RightIsDown()
Gurax_DeclareMethodAlias(wxMouseState, RightIsDown_gurax, "RightIsDown")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMouseState, RightIsDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->RightIsDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.MouseState#Aux1IsDown()
Gurax_DeclareMethodAlias(wxMouseState, Aux1IsDown_gurax, "Aux1IsDown")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMouseState, Aux1IsDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Aux1IsDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.MouseState#Aux2IsDown()
Gurax_DeclareMethodAlias(wxMouseState, Aux2IsDown_gurax, "Aux2IsDown")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMouseState, Aux2IsDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Aux2IsDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.MouseState#SetX(x as Number)
Gurax_DeclareMethodAlias(wxMouseState, SetX_gurax, "SetX")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMouseState, SetX_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxCoord x = args_gurax.PickNumber<wxCoord>();
	// Function body
	pEntity_gurax->SetX(x);
	return Gurax::Value::nil();
}

// wx.MouseState#SetY(y as Number)
Gurax_DeclareMethodAlias(wxMouseState, SetY_gurax, "SetY")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMouseState, SetY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxCoord y = args_gurax.PickNumber<wxCoord>();
	// Function body
	pEntity_gurax->SetY(y);
	return Gurax::Value::nil();
}

// wx.MouseState#SetPosition(pos as wx.Point)
Gurax_DeclareMethodAlias(wxMouseState, SetPosition_gurax, "SetPosition")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMouseState, SetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPoint& value_pos = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& pos = value_pos.GetEntity();
	// Function body
	pEntity_gurax->SetPosition(pos);
	return Gurax::Value::nil();
}

// wx.MouseState#SetLeftDown(down as Bool)
Gurax_DeclareMethodAlias(wxMouseState, SetLeftDown_gurax, "SetLeftDown")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("down", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMouseState, SetLeftDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool down = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetLeftDown(down);
	return Gurax::Value::nil();
}

// wx.MouseState#SetMiddleDown(down as Bool)
Gurax_DeclareMethodAlias(wxMouseState, SetMiddleDown_gurax, "SetMiddleDown")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("down", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMouseState, SetMiddleDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool down = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetMiddleDown(down);
	return Gurax::Value::nil();
}

// wx.MouseState#SetRightDown(down as Bool)
Gurax_DeclareMethodAlias(wxMouseState, SetRightDown_gurax, "SetRightDown")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("down", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMouseState, SetRightDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool down = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetRightDown(down);
	return Gurax::Value::nil();
}

// wx.MouseState#SetAux1Down(down as Bool)
Gurax_DeclareMethodAlias(wxMouseState, SetAux1Down_gurax, "SetAux1Down")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("down", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMouseState, SetAux1Down_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool down = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetAux1Down(down);
	return Gurax::Value::nil();
}

// wx.MouseState#SetAux2Down(down as Bool)
Gurax_DeclareMethodAlias(wxMouseState, SetAux2Down_gurax, "SetAux2Down")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("down", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMouseState, SetAux2Down_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool down = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetAux2Down(down);
	return Gurax::Value::nil();
}

// wx.MouseState#GetPosition() {block?}
Gurax_DeclareMethodAlias(wxMouseState, GetPosition_gurax, "GetPosition")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxMouseState, GetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(pEntity_gurax->GetPosition()));
}

// wx.MouseState#GetPositionXY(&x:nilRef as Number, &y:nilRef as Number)
Gurax_DeclareMethodAlias(wxMouseState, GetPositionXY_gurax, "GetPositionXY")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementMethodEx(wxMouseState, GetPositionXY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Referencer> x(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> y(args_gurax.PickReferencer().Reference());
	// Function body
	int x_, y_;
	pEntity_gurax->GetPosition(&x_, &y_);
	x->SetValue(processor_gurax, new Value_Number(x_));
	y->SetValue(processor_gurax, new Value_Number(y_));
	return Value::nil();
}

// wx.MouseState#GetModifiers()
Gurax_DeclareMethodAlias(wxMouseState, GetModifiers_gurax, "GetModifiers")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxMouseState, GetModifiers_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetModifiers();
	return new Gurax::Value_Number(rtn);
}

// wx.MouseState#HasAnyModifiers()
Gurax_DeclareMethodAlias(wxMouseState, HasAnyModifiers_gurax, "HasAnyModifiers")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMouseState, HasAnyModifiers_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasAnyModifiers();
	return new Gurax::Value_Bool(rtn);
}

// wx.MouseState#HasModifiers()
Gurax_DeclareMethodAlias(wxMouseState, HasModifiers_gurax, "HasModifiers")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMouseState, HasModifiers_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasModifiers();
	return new Gurax::Value_Bool(rtn);
}

// wx.MouseState#ControlDown()
Gurax_DeclareMethodAlias(wxMouseState, ControlDown_gurax, "ControlDown")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMouseState, ControlDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->ControlDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.MouseState#RawControlDown()
Gurax_DeclareMethodAlias(wxMouseState, RawControlDown_gurax, "RawControlDown")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMouseState, RawControlDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->RawControlDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.MouseState#ShiftDown()
Gurax_DeclareMethodAlias(wxMouseState, ShiftDown_gurax, "ShiftDown")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMouseState, ShiftDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->ShiftDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.MouseState#MetaDown()
Gurax_DeclareMethodAlias(wxMouseState, MetaDown_gurax, "MetaDown")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMouseState, MetaDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->MetaDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.MouseState#AltDown()
Gurax_DeclareMethodAlias(wxMouseState, AltDown_gurax, "AltDown")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMouseState, AltDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->AltDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.MouseState#CmdDown()
Gurax_DeclareMethodAlias(wxMouseState, CmdDown_gurax, "CmdDown")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMouseState, CmdDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->CmdDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.MouseState#SetControlDown(down as Bool)
Gurax_DeclareMethodAlias(wxMouseState, SetControlDown_gurax, "SetControlDown")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("down", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMouseState, SetControlDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool down = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetControlDown(down);
	return Gurax::Value::nil();
}

// wx.MouseState#SetRawControlDown(down as Bool)
Gurax_DeclareMethodAlias(wxMouseState, SetRawControlDown_gurax, "SetRawControlDown")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("down", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMouseState, SetRawControlDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool down = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetRawControlDown(down);
	return Gurax::Value::nil();
}

// wx.MouseState#SetShiftDown(down as Bool)
Gurax_DeclareMethodAlias(wxMouseState, SetShiftDown_gurax, "SetShiftDown")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("down", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMouseState, SetShiftDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool down = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetShiftDown(down);
	return Gurax::Value::nil();
}

// wx.MouseState#SetAltDown(down as Bool)
Gurax_DeclareMethodAlias(wxMouseState, SetAltDown_gurax, "SetAltDown")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("down", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMouseState, SetAltDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool down = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetAltDown(down);
	return Gurax::Value::nil();
}

// wx.MouseState#SetMetaDown(down as Bool)
Gurax_DeclareMethodAlias(wxMouseState, SetMetaDown_gurax, "SetMetaDown")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("down", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMouseState, SetMetaDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool down = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetMetaDown(down);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxMouseState
//------------------------------------------------------------------------------
VType_wxMouseState VTYPE_wxMouseState("MouseState");

void VType_wxMouseState::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxMouseState, GetX_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, GetY_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, LeftIsDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, MiddleIsDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, RightIsDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, Aux1IsDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, Aux2IsDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, SetX_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, SetY_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, SetPosition_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, SetLeftDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, SetMiddleDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, SetRightDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, SetAux1Down_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, SetAux2Down_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, GetPosition_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, GetPositionXY_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, GetModifiers_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, HasAnyModifiers_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, HasModifiers_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, ControlDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, RawControlDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, ShiftDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, MetaDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, AltDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, CmdDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, SetControlDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, SetRawControlDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, SetShiftDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, SetAltDown_gurax));
	Assign(Gurax_CreateMethod(wxMouseState, SetMetaDown_gurax));
}

//------------------------------------------------------------------------------
// Value_wxMouseState
//------------------------------------------------------------------------------
VType& Value_wxMouseState::vtype = VTYPE_wxMouseState;

String Value_wxMouseState::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MouseState");
}

Gurax_EndModuleScope(wx)
