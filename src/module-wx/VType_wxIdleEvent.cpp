﻿//==============================================================================
// VType_wxIdleEvent.cpp
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

${help.ComposePropertyHelp(wx.IdleEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.IdleEvent, `en)}

${help.ComposeMethodHelp(wx.IdleEvent, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.IdleEvent#MoreRequested()
Gurax_DeclareMethodAlias(wxIdleEvent, MoreRequested_gurax, "MoreRequested")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxIdleEvent, MoreRequested_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->MoreRequested();
	return new Gurax::Value_Bool(rtn);
}

// wx.IdleEvent#RequestMore(needMore? as Bool)
Gurax_DeclareMethodAlias(wxIdleEvent, RequestMore_gurax, "RequestMore")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("needMore", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxIdleEvent, RequestMore_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool needMore = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->RequestMore(needMore);
	return Gurax::Value::nil();
}

// wx.IdleEvent.GetMode()
Gurax_DeclareClassMethodAlias(wxIdleEvent, GetMode_gurax, "GetMode")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxIdleEvent, GetMode_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxIdleMode rtn = wxIdleEvent::GetMode();
	return new Gurax::Value_Number(rtn);
}

// wx.IdleEvent.SetMode(mode as Number)
Gurax_DeclareClassMethodAlias(wxIdleEvent, SetMode_gurax, "SetMode")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxIdleEvent, SetMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxIdleMode mode = args_gurax.PickNumber<wxIdleMode>();
	// Function body
	wxIdleEvent::SetMode(mode);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxIdleEvent
//------------------------------------------------------------------------------
VType_wxIdleEvent VTYPE_wxIdleEvent("IdleEvent");

void VType_wxIdleEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxIdleEvent, MoreRequested_gurax));
	Assign(Gurax_CreateMethod(wxIdleEvent, RequestMore_gurax));
	Assign(Gurax_CreateMethod(wxIdleEvent, GetMode_gurax));
	Assign(Gurax_CreateMethod(wxIdleEvent, SetMode_gurax));
}

//------------------------------------------------------------------------------
// Value_wxIdleEvent
//------------------------------------------------------------------------------
VType& Value_wxIdleEvent::vtype = VTYPE_wxIdleEvent;
EventValueFactoryDeriv<Value_wxIdleEvent> Value_wxIdleEvent::eventValueFactory;

String Value_wxIdleEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.IdleEvent");
}

Gurax_EndModuleScope(wx)
