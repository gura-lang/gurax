//==============================================================================
// VType_wxMouseEvent.cpp
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
// VType_wxMouseEvent
//------------------------------------------------------------------------------
VType_wxMouseEvent VTYPE_wxMouseEvent("MouseEvent");

void VType_wxMouseEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxMouseEvent
//------------------------------------------------------------------------------
VType& Value_wxMouseEvent::vtype = VTYPE_wxMouseEvent;
EventValueFactoryDeriv<Value_wxMouseEvent> Value_wxMouseEvent::eventValueFactory;

String Value_wxMouseEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MouseEvent");
}

Gurax_EndModuleScope(wx)
