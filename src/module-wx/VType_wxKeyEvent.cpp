//==============================================================================
// VType_wxKeyEvent.cpp
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

# Property

# Operator

# Cast Operation

# Constructor

# Method
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
// VType_wxKeyEvent
//------------------------------------------------------------------------------
VType_wxKeyEvent VTYPE_wxKeyEvent("KeyEvent");

void VType_wxKeyEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxKeyEvent
//------------------------------------------------------------------------------
VType& Value_wxKeyEvent::vtype = VTYPE_wxKeyEvent;
EventValueFactoryDeriv<Value_wxKeyEvent> Value_wxKeyEvent::eventValueFactory;

String Value_wxKeyEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.KeyEvent");
}

Gurax_EndModuleScope(wx)
