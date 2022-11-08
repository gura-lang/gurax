//==============================================================================
// VType_wxKeyEvent.cpp
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

${help.ComposePropertyHelp(wx.KeyEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.KeyEvent, `en)}

${help.ComposeMethodHelp(wx.KeyEvent, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.KeyEvent#GetKeyCode()
Gurax_DeclareMethodAlias(wxKeyEvent, GetKeyCode_gurax, "GetKeyCode")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, GetKeyCode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetKeyCode();
	return new Gurax::Value_Number(rtn);
}

// wx.KeyEvent#IsKeyInCategory(category as Number)
Gurax_DeclareMethodAlias(wxKeyEvent, IsKeyInCategory_gurax, "IsKeyInCategory")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("category", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, IsKeyInCategory_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int category = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->IsKeyInCategory(category);
	return new Gurax::Value_Bool(rtn);
}

// wx.KeyEvent#GetRawKeyFlags()
Gurax_DeclareMethodAlias(wxKeyEvent, GetRawKeyFlags_gurax, "GetRawKeyFlags")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, GetRawKeyFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	UInt32 rtn = pEntity_gurax->GetRawKeyFlags();
	return new Gurax::Value_Number(rtn);
}

// wx.KeyEvent#GetUnicodeKey()
Gurax_DeclareMethodAlias(wxKeyEvent, GetUnicodeKey_gurax, "GetUnicodeKey")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, GetUnicodeKey_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	char rtn = pEntity_gurax->GetUnicodeKey();
	return new Gurax::Value_Number(rtn);
}

// wx.KeyEvent#GetX()
Gurax_DeclareMethodAlias(wxKeyEvent, GetX_gurax, "GetX")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, GetX_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxCoord rtn = pEntity_gurax->GetX();
	return new Gurax::Value_Number(rtn);
}

// wx.KeyEvent#GetY()
Gurax_DeclareMethodAlias(wxKeyEvent, GetY_gurax, "GetY")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, GetY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxCoord rtn = pEntity_gurax->GetY();
	return new Gurax::Value_Number(rtn);
}

// wx.KeyEvent#DoAllowNextEvent()
Gurax_DeclareMethodAlias(wxKeyEvent, DoAllowNextEvent_gurax, "DoAllowNextEvent")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, DoAllowNextEvent_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->DoAllowNextEvent();
	return Gurax::Value::nil();
}

// wx.KeyEvent#IsNextEventAllowed()
Gurax_DeclareMethodAlias(wxKeyEvent, IsNextEventAllowed_gurax, "IsNextEventAllowed")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, IsNextEventAllowed_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsNextEventAllowed();
	return new Gurax::Value_Bool(rtn);
}

// wx.KeyEvent#GetPosition() {block?}
Gurax_DeclareMethodAlias(wxKeyEvent, GetPosition_gurax, "GetPosition")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, GetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetPosition()));
}

// wx.KeyEvent#GetPositionXY()
Gurax_DeclareMethodAlias(wxKeyEvent, GetPositionXY_gurax, "GetPositionXY")
{
	Declare(VTYPE_Tuple, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, GetPositionXY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxCoord x, y;
	pEntity_gurax->GetPosition(&x, &y);
	return Value_Tuple::Create(new Value_Number(x), new Value_Number(y));
}

// wx.KeyEvent#GetModifiers()
Gurax_DeclareMethodAlias(wxKeyEvent, GetModifiers_gurax, "GetModifiers")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, GetModifiers_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetModifiers();
	return new Gurax::Value_Number(rtn);
}

// wx.KeyEvent#HasAnyModifiers()
Gurax_DeclareMethodAlias(wxKeyEvent, HasAnyModifiers_gurax, "HasAnyModifiers")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, HasAnyModifiers_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasAnyModifiers();
	return new Gurax::Value_Bool(rtn);
}

// wx.KeyEvent#HasModifiers()
Gurax_DeclareMethodAlias(wxKeyEvent, HasModifiers_gurax, "HasModifiers")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, HasModifiers_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasModifiers();
	return new Gurax::Value_Bool(rtn);
}

// wx.KeyEvent#ControlDown()
Gurax_DeclareMethodAlias(wxKeyEvent, ControlDown_gurax, "ControlDown")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, ControlDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->ControlDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.KeyEvent#RawControlDown()
Gurax_DeclareMethodAlias(wxKeyEvent, RawControlDown_gurax, "RawControlDown")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, RawControlDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->RawControlDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.KeyEvent#ShiftDown()
Gurax_DeclareMethodAlias(wxKeyEvent, ShiftDown_gurax, "ShiftDown")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, ShiftDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->ShiftDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.KeyEvent#MetaDown()
Gurax_DeclareMethodAlias(wxKeyEvent, MetaDown_gurax, "MetaDown")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, MetaDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->MetaDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.KeyEvent#AltDown()
Gurax_DeclareMethodAlias(wxKeyEvent, AltDown_gurax, "AltDown")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, AltDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->AltDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.KeyEvent#CmdDown()
Gurax_DeclareMethodAlias(wxKeyEvent, CmdDown_gurax, "CmdDown")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, CmdDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->CmdDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.KeyEvent#SetControlDown(down as Bool)
Gurax_DeclareMethodAlias(wxKeyEvent, SetControlDown_gurax, "SetControlDown")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("down", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, SetControlDown_gurax, processor_gurax, argument_gurax)
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

// wx.KeyEvent#SetRawControlDown(down as Bool)
Gurax_DeclareMethodAlias(wxKeyEvent, SetRawControlDown_gurax, "SetRawControlDown")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("down", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, SetRawControlDown_gurax, processor_gurax, argument_gurax)
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

// wx.KeyEvent#SetShiftDown(down as Bool)
Gurax_DeclareMethodAlias(wxKeyEvent, SetShiftDown_gurax, "SetShiftDown")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("down", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, SetShiftDown_gurax, processor_gurax, argument_gurax)
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

// wx.KeyEvent#SetAltDown(down as Bool)
Gurax_DeclareMethodAlias(wxKeyEvent, SetAltDown_gurax, "SetAltDown")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("down", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, SetAltDown_gurax, processor_gurax, argument_gurax)
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

// wx.KeyEvent#SetMetaDown(down as Bool)
Gurax_DeclareMethodAlias(wxKeyEvent, SetMetaDown_gurax, "SetMetaDown")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("down", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxKeyEvent, SetMetaDown_gurax, processor_gurax, argument_gurax)
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
// VType_wxKeyEvent
//------------------------------------------------------------------------------
VType_wxKeyEvent VTYPE_wxKeyEvent("KeyEvent");

void VType_wxKeyEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxKeyEvent, GetKeyCode_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, IsKeyInCategory_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, GetRawKeyFlags_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, GetUnicodeKey_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, GetX_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, GetY_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, DoAllowNextEvent_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, IsNextEventAllowed_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, GetPosition_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, GetPositionXY_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, GetModifiers_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, HasAnyModifiers_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, HasModifiers_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, ControlDown_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, RawControlDown_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, ShiftDown_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, MetaDown_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, AltDown_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, CmdDown_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, SetControlDown_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, SetRawControlDown_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, SetShiftDown_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, SetAltDown_gurax));
	Assign(Gurax_CreateMethod(wxKeyEvent, SetMetaDown_gurax));
}

//------------------------------------------------------------------------------
// Value_wxKeyEvent
//------------------------------------------------------------------------------
VType& Value_wxKeyEvent::vtype = VTYPE_wxKeyEvent;
EventValueFactoryDeriv<Value_wxKeyEvent> Value_wxKeyEvent::eventValueFactory;

String Value_wxKeyEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.KeyEvent");
}

Gurax_EndModuleScope(wx)
