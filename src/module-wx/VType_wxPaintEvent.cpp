﻿//==============================================================================
// VType_wxPaintEvent.cpp
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

${help.ComposePropertyHelp(wx.PaintEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.PaintEvent, `en)}

${help.ComposeMethodHelp(wx.PaintEvent, `en)}
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
// VType_wxPaintEvent
//------------------------------------------------------------------------------
VType_wxPaintEvent VTYPE_wxPaintEvent("PaintEvent");

void VType_wxPaintEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPaintEvent
//------------------------------------------------------------------------------
VType& Value_wxPaintEvent::vtype = VTYPE_wxPaintEvent;
EventValueFactoryDeriv<Value_wxPaintEvent> Value_wxPaintEvent::eventValueFactory;

String Value_wxPaintEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PaintEvent");
}

Gurax_EndModuleScope(wx)
