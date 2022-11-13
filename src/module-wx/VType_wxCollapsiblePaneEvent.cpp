﻿//==============================================================================
// VType_wxCollapsiblePaneEvent.cpp
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

${help.ComposePropertyHelp(wx.CollapsiblePaneEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.CollapsiblePaneEvent, `en)}

${help.ComposeMethodHelp(wx.CollapsiblePaneEvent, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.CollapsiblePaneEvent#GetCollapsed()
Gurax_DeclareMethodAlias(wxCollapsiblePaneEvent, GetCollapsed_gurax, "GetCollapsed")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxCollapsiblePaneEvent, GetCollapsed_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetCollapsed();
	return new Gurax::Value_Bool(rtn);
}

// wx.CollapsiblePaneEvent#SetCollapsed(collapsed as Bool)
Gurax_DeclareMethodAlias(wxCollapsiblePaneEvent, SetCollapsed_gurax, "SetCollapsed")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("collapsed", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxCollapsiblePaneEvent, SetCollapsed_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool collapsed = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetCollapsed(collapsed);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxCollapsiblePaneEvent
//------------------------------------------------------------------------------
VType_wxCollapsiblePaneEvent VTYPE_wxCollapsiblePaneEvent("CollapsiblePaneEvent");

void VType_wxCollapsiblePaneEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxCollapsiblePaneEvent, GetCollapsed_gurax));
	Assign(Gurax_CreateMethod(wxCollapsiblePaneEvent, SetCollapsed_gurax));
}

//------------------------------------------------------------------------------
// Value_wxCollapsiblePaneEvent
//------------------------------------------------------------------------------
VType& Value_wxCollapsiblePaneEvent::vtype = VTYPE_wxCollapsiblePaneEvent;
EventValueFactoryDeriv<Value_wxCollapsiblePaneEvent> Value_wxCollapsiblePaneEvent::eventValueFactory;

String Value_wxCollapsiblePaneEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.CollapsiblePaneEvent");
}

Gurax_EndModuleScope(wx)
