﻿//==============================================================================
// VType_wxAuiToolBarEvent.cpp
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

${help.ComposePropertyHelp(wx.AuiToolBarEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.AuiToolBarEvent, `en)}

${help.ComposeMethodHelp(wx.AuiToolBarEvent, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.AuiToolBarEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.AuiToolBarEvent, `ja)}

${help.ComposeMethodHelp(wx.AuiToolBarEvent, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxAuiToolBarEvent
//------------------------------------------------------------------------------
VType_wxAuiToolBarEvent VTYPE_wxAuiToolBarEvent("AuiToolBarEvent");

void VType_wxAuiToolBarEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxNotifyEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxAuiToolBarEvent
//------------------------------------------------------------------------------
VType& Value_wxAuiToolBarEvent::vtype = VTYPE_wxAuiToolBarEvent;
EventValueFactoryDeriv<Value_wxAuiToolBarEvent> Value_wxAuiToolBarEvent::eventValueFactory;

String Value_wxAuiToolBarEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AuiToolBarEvent");
}

Gurax_EndModuleScope(wx)
