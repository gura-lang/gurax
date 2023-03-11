﻿//==============================================================================
// VType_wxSocketEvent.cpp
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

${help.ComposePropertyHelp(wx.SocketEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SocketEvent, `en)}

${help.ComposeMethodHelp(wx.SocketEvent, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.SocketEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.SocketEvent, `ja)}

${help.ComposeMethodHelp(wx.SocketEvent, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.SocketEvent#GetSocket() {block?}
Gurax_DeclareMethodAlias(wxSocketEvent, GetSocket_gurax, "GetSocket")
{
	Declare(VTYPE_wxSocketBase, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxSocketEvent, GetSocket_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSocketBase(
		pEntity_gurax->GetSocket()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSocketEvent
//------------------------------------------------------------------------------
VType_wxSocketEvent VTYPE_wxSocketEvent("SocketEvent");

void VType_wxSocketEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSocketEvent, GetSocket_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSocketEvent
//------------------------------------------------------------------------------
VType& Value_wxSocketEvent::vtype = VTYPE_wxSocketEvent;
EventValueFactoryDeriv<Value_wxSocketEvent> Value_wxSocketEvent::eventValueFactory;

String Value_wxSocketEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SocketEvent");
}

Gurax_EndModuleScope(wx)
