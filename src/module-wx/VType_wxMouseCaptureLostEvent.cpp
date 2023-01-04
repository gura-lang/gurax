﻿//==============================================================================
// VType_wxMouseCaptureLostEvent.cpp
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

${help.ComposePropertyHelp(wx.MouseCaptureLostEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.MouseCaptureLostEvent, `en)}

${help.ComposeMethodHelp(wx.MouseCaptureLostEvent, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.MouseCaptureLostEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.MouseCaptureLostEvent, `ja)}

${help.ComposeMethodHelp(wx.MouseCaptureLostEvent, `ja)}
)**";

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
// VType_wxMouseCaptureLostEvent
//------------------------------------------------------------------------------
VType_wxMouseCaptureLostEvent VTYPE_wxMouseCaptureLostEvent("MouseCaptureLostEvent");

void VType_wxMouseCaptureLostEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxMouseCaptureLostEvent
//------------------------------------------------------------------------------
VType& Value_wxMouseCaptureLostEvent::vtype = VTYPE_wxMouseCaptureLostEvent;
EventValueFactoryDeriv<Value_wxMouseCaptureLostEvent> Value_wxMouseCaptureLostEvent::eventValueFactory;

String Value_wxMouseCaptureLostEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MouseCaptureLostEvent");
}

Gurax_EndModuleScope(wx)
