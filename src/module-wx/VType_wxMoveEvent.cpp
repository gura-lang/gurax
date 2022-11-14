﻿//==============================================================================
// VType_wxMoveEvent.cpp
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

${help.ComposePropertyHelp(wx.MoveEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.MoveEvent, `en)}

${help.ComposeMethodHelp(wx.MoveEvent, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.MoveEvent#GetPosition() {block?}
Gurax_DeclareMethodAlias(wxMoveEvent, GetPosition_gurax, "GetPosition")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxMoveEvent, GetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetPosition()));
}

// wx.MoveEvent#GetRect() {block?}
Gurax_DeclareMethodAlias(wxMoveEvent, GetRect_gurax, "GetRect")
{
	Declare(VTYPE_wxRect, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxMoveEvent, GetRect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRect(
		pEntity_gurax->GetRect()));
}

// wx.MoveEvent#SetRect(rect as wx.Rect)
Gurax_DeclareMethodAlias(wxMoveEvent, SetRect_gurax, "SetRect")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxMoveEvent, SetRect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRect& value_rect = args_gurax.Pick<Value_wxRect>();
	const wxRect& rect = value_rect.GetEntity();
	// Function body
	pEntity_gurax->SetRect(rect);
	return Gurax::Value::nil();
}

// wx.MoveEvent#SetPosition(pos as wx.Point)
Gurax_DeclareMethodAlias(wxMoveEvent, SetPosition_gurax, "SetPosition")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxMoveEvent, SetPosition_gurax, processor_gurax, argument_gurax)
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

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxMoveEvent
//------------------------------------------------------------------------------
VType_wxMoveEvent VTYPE_wxMoveEvent("MoveEvent");

void VType_wxMoveEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxMoveEvent, GetPosition_gurax));
	Assign(Gurax_CreateMethod(wxMoveEvent, GetRect_gurax));
	Assign(Gurax_CreateMethod(wxMoveEvent, SetRect_gurax));
	Assign(Gurax_CreateMethod(wxMoveEvent, SetPosition_gurax));
}

//------------------------------------------------------------------------------
// Value_wxMoveEvent
//------------------------------------------------------------------------------
VType& Value_wxMoveEvent::vtype = VTYPE_wxMoveEvent;
EventValueFactoryDeriv<Value_wxMoveEvent> Value_wxMoveEvent::eventValueFactory;

String Value_wxMoveEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MoveEvent");
}

Gurax_EndModuleScope(wx)
