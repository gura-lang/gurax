﻿//==============================================================================
// VType_wxRibbonBarEvent.cpp
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

${help.ComposePropertyHelp(wx.RibbonBarEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RibbonBarEvent, `en)}

${help.ComposeMethodHelp(wx.RibbonBarEvent, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.RibbonBarEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.RibbonBarEvent, `ja)}

${help.ComposeMethodHelp(wx.RibbonBarEvent, `ja)}
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
// VType_wxRibbonBarEvent
//------------------------------------------------------------------------------
VType_wxRibbonBarEvent VTYPE_wxRibbonBarEvent("RibbonBarEvent");

void VType_wxRibbonBarEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxNotifyEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRibbonBarEvent
//------------------------------------------------------------------------------
VType& Value_wxRibbonBarEvent::vtype = VTYPE_wxRibbonBarEvent;
EventValueFactoryDeriv<Value_wxRibbonBarEvent> Value_wxRibbonBarEvent::eventValueFactory;

String Value_wxRibbonBarEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RibbonBarEvent");
}

Gurax_EndModuleScope(wx)
