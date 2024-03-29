﻿//==============================================================================
// VType_wxHelpEvent.cpp
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

${help.ComposePropertyHelp(wx.HelpEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.HelpEvent, `en)}

${help.ComposeMethodHelp(wx.HelpEvent, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.HelpEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.HelpEvent, `ja)}

${help.ComposeMethodHelp(wx.HelpEvent, `ja)}
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
// VType_wxHelpEvent
//------------------------------------------------------------------------------
VType_wxHelpEvent VTYPE_wxHelpEvent("HelpEvent");

void VType_wxHelpEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxHelpEvent
//------------------------------------------------------------------------------
VType& Value_wxHelpEvent::vtype = VTYPE_wxHelpEvent;
EventValueFactoryDeriv<Value_wxHelpEvent> Value_wxHelpEvent::eventValueFactory;

String Value_wxHelpEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HelpEvent");
}

Gurax_EndModuleScope(wx)
