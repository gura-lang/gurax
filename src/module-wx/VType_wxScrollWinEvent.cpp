﻿//==============================================================================
// VType_wxScrollWinEvent.cpp
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

${help.ComposePropertyHelp(wx.ScrollWinEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.ScrollWinEvent, `en)}

${help.ComposeMethodHelp(wx.ScrollWinEvent, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.ScrollWinEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.ScrollWinEvent, `ja)}

${help.ComposeMethodHelp(wx.ScrollWinEvent, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ScrollWinEvent#GetOrientation()
Gurax_DeclareMethodAlias(wxScrollWinEvent, GetOrientation_gurax, "GetOrientation")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxScrollWinEvent, GetOrientation_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetOrientation();
	return new Gurax::Value_Number(rtn);
}

// wx.ScrollWinEvent#GetPosition()
Gurax_DeclareMethodAlias(wxScrollWinEvent, GetPosition_gurax, "GetPosition")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxScrollWinEvent, GetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetPosition();
	return new Gurax::Value_Number(rtn);
}

// wx.ScrollWinEvent#SetOrientation(orient as Number)
Gurax_DeclareMethodAlias(wxScrollWinEvent, SetOrientation_gurax, "SetOrientation")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("orient", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrollWinEvent, SetOrientation_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int orient = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetOrientation(orient);
	return Gurax::Value::nil();
}

// wx.ScrollWinEvent#SetPosition(pos as Number)
Gurax_DeclareMethodAlias(wxScrollWinEvent, SetPosition_gurax, "SetPosition")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrollWinEvent, SetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int pos = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetPosition(pos);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxScrollWinEvent
//------------------------------------------------------------------------------
VType_wxScrollWinEvent VTYPE_wxScrollWinEvent("ScrollWinEvent");

void VType_wxScrollWinEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxScrollWinEvent, GetOrientation_gurax));
	Assign(Gurax_CreateMethod(wxScrollWinEvent, GetPosition_gurax));
	Assign(Gurax_CreateMethod(wxScrollWinEvent, SetOrientation_gurax));
	Assign(Gurax_CreateMethod(wxScrollWinEvent, SetPosition_gurax));
}

//------------------------------------------------------------------------------
// Value_wxScrollWinEvent
//------------------------------------------------------------------------------
VType& Value_wxScrollWinEvent::vtype = VTYPE_wxScrollWinEvent;
EventValueFactoryDeriv<Value_wxScrollWinEvent> Value_wxScrollWinEvent::eventValueFactory;

String Value_wxScrollWinEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ScrollWinEvent");
}

Gurax_EndModuleScope(wx)
