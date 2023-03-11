﻿//==============================================================================
// VType_wxGridEvent.cpp
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

${help.ComposePropertyHelp(wx.GridEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridEvent, `en)}

${help.ComposeMethodHelp(wx.GridEvent, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.GridEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.GridEvent, `ja)}

${help.ComposeMethodHelp(wx.GridEvent, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GridEvent#AltDown()
Gurax_DeclareMethodAlias(wxGridEvent, AltDown_gurax, "AltDown")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGridEvent, AltDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->AltDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.GridEvent#ControlDown()
Gurax_DeclareMethodAlias(wxGridEvent, ControlDown_gurax, "ControlDown")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGridEvent, ControlDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->ControlDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.GridEvent#GetCol()
Gurax_DeclareMethodAlias(wxGridEvent, GetCol_gurax, "GetCol")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxGridEvent, GetCol_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetCol();
	return new Gurax::Value_Number(rtn);
}

// wx.GridEvent#GetPosition() {block?}
Gurax_DeclareMethodAlias(wxGridEvent, GetPosition_gurax, "GetPosition")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridEvent, GetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetPosition()));
}

// wx.GridEvent#GetRow()
Gurax_DeclareMethodAlias(wxGridEvent, GetRow_gurax, "GetRow")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxGridEvent, GetRow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetRow();
	return new Gurax::Value_Number(rtn);
}

// wx.GridEvent#MetaDown()
Gurax_DeclareMethodAlias(wxGridEvent, MetaDown_gurax, "MetaDown")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGridEvent, MetaDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->MetaDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.GridEvent#Selecting()
Gurax_DeclareMethodAlias(wxGridEvent, Selecting_gurax, "Selecting")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGridEvent, Selecting_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Selecting();
	return new Gurax::Value_Bool(rtn);
}

// wx.GridEvent#ShiftDown()
Gurax_DeclareMethodAlias(wxGridEvent, ShiftDown_gurax, "ShiftDown")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGridEvent, ShiftDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->ShiftDown();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGridEvent
//------------------------------------------------------------------------------
VType_wxGridEvent VTYPE_wxGridEvent("GridEvent");

void VType_wxGridEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxNotifyEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGridEvent, AltDown_gurax));
	Assign(Gurax_CreateMethod(wxGridEvent, ControlDown_gurax));
	Assign(Gurax_CreateMethod(wxGridEvent, GetCol_gurax));
	Assign(Gurax_CreateMethod(wxGridEvent, GetPosition_gurax));
	Assign(Gurax_CreateMethod(wxGridEvent, GetRow_gurax));
	Assign(Gurax_CreateMethod(wxGridEvent, MetaDown_gurax));
	Assign(Gurax_CreateMethod(wxGridEvent, Selecting_gurax));
	Assign(Gurax_CreateMethod(wxGridEvent, ShiftDown_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGridEvent
//------------------------------------------------------------------------------
VType& Value_wxGridEvent::vtype = VTYPE_wxGridEvent;
EventValueFactoryDeriv<Value_wxGridEvent> Value_wxGridEvent::eventValueFactory;

String Value_wxGridEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridEvent");
}

Gurax_EndModuleScope(wx)
