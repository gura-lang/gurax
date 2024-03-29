﻿//==============================================================================
// VType_wxRibbonButtonBarEvent.cpp
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

${help.ComposePropertyHelp(wx.RibbonButtonBarEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RibbonButtonBarEvent, `en)}

${help.ComposeMethodHelp(wx.RibbonButtonBarEvent, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.RibbonButtonBarEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.RibbonButtonBarEvent, `ja)}

${help.ComposeMethodHelp(wx.RibbonButtonBarEvent, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.RibbonButtonBarEvent#GetBar() {block?}
Gurax_DeclareMethodAlias(wxRibbonButtonBarEvent, GetBar_gurax, "GetBar")
{
	Declare(VTYPE_wxRibbonButtonBar, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonButtonBarEvent, GetBar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonButtonBar(pEntity_gurax->GetBar()));
}

// wx.RibbonButtonBarEvent#SetBar(bar as wx.RibbonButtonBar)
Gurax_DeclareMethodAlias(wxRibbonButtonBarEvent, SetBar_gurax, "SetBar")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("bar", VTYPE_wxRibbonButtonBar, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonButtonBarEvent, SetBar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonButtonBar& value_bar = args_gurax.Pick<Value_wxRibbonButtonBar>();
	wxRibbonButtonBar* bar = value_bar.GetEntityPtr();
	// Function body
	pEntity_gurax->SetBar(bar);
	return Gurax::Value::nil();
}

// wx.RibbonButtonBarEvent#GetButton() {block?}
Gurax_DeclareMethodAlias(wxRibbonButtonBarEvent, GetButton_gurax, "GetButton")
{
	Declare(VTYPE_wxRibbonButtonBarButtonBase, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonButtonBarEvent, GetButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonButtonBarButtonBase(pEntity_gurax->GetButton()));
}

// wx.RibbonButtonBarEvent#SetButton(bar as wx.RibbonButtonBarButtonBase)
Gurax_DeclareMethodAlias(wxRibbonButtonBarEvent, SetButton_gurax, "SetButton")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("bar", VTYPE_wxRibbonButtonBarButtonBase, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonButtonBarEvent, SetButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonButtonBarButtonBase& value_bar = args_gurax.Pick<Value_wxRibbonButtonBarButtonBase>();
	wxRibbonButtonBarButtonBase* bar = value_bar.GetEntityPtr();
	// Function body
	pEntity_gurax->SetButton(bar);
	return Gurax::Value::nil();
}

// wx.RibbonButtonBarEvent#PopupMenu(menu as wx.Menu)
Gurax_DeclareMethodAlias(wxRibbonButtonBarEvent, PopupMenu_gurax, "PopupMenu")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("menu", VTYPE_wxMenu, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonButtonBarEvent, PopupMenu_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxMenu& value_menu = args_gurax.Pick<Value_wxMenu>();
	wxMenu* menu = value_menu.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->PopupMenu(menu);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxRibbonButtonBarEvent
//------------------------------------------------------------------------------
VType_wxRibbonButtonBarEvent VTYPE_wxRibbonButtonBarEvent("RibbonButtonBarEvent");

void VType_wxRibbonButtonBarEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxNotifyEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxRibbonButtonBarEvent, GetBar_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBarEvent, SetBar_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBarEvent, GetButton_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBarEvent, SetButton_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBarEvent, PopupMenu_gurax));
}

//------------------------------------------------------------------------------
// Value_wxRibbonButtonBarEvent
//------------------------------------------------------------------------------
VType& Value_wxRibbonButtonBarEvent::vtype = VTYPE_wxRibbonButtonBarEvent;
EventValueFactoryDeriv<Value_wxRibbonButtonBarEvent> Value_wxRibbonButtonBarEvent::eventValueFactory;

String Value_wxRibbonButtonBarEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RibbonButtonBarEvent");
}

Gurax_EndModuleScope(wx)
