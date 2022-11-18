﻿//==============================================================================
// VType_wxFocusEvent.cpp
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

${help.ComposePropertyHelp(wx.FocusEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.FocusEvent, `en)}

${help.ComposeMethodHelp(wx.FocusEvent, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.FocusEvent#GetWindow() {block?}
Gurax_DeclareMethodAlias(wxFocusEvent, GetWindow_gurax, "GetWindow")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFocusEvent, GetWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetWindow()));
}

// wx.FocusEvent#SetWindow(win as wx.Window)
Gurax_DeclareMethodAlias(wxFocusEvent, SetWindow_gurax, "SetWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("win", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFocusEvent, SetWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_win = args_gurax.Pick<Value_wxWindow>();
	wxWindow* win = value_win.GetEntityPtr();
	// Function body
	pEntity_gurax->SetWindow(win);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFocusEvent
//------------------------------------------------------------------------------
VType_wxFocusEvent VTYPE_wxFocusEvent("FocusEvent");

void VType_wxFocusEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFocusEvent, GetWindow_gurax));
	Assign(Gurax_CreateMethod(wxFocusEvent, SetWindow_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFocusEvent
//------------------------------------------------------------------------------
VType& Value_wxFocusEvent::vtype = VTYPE_wxFocusEvent;
EventValueFactoryDeriv<Value_wxFocusEvent> Value_wxFocusEvent::eventValueFactory;

String Value_wxFocusEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FocusEvent");
}

Gurax_EndModuleScope(wx)
