//==============================================================================
// VType_wxEraseEvent.cpp
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
// VType_wxEraseEvent
//------------------------------------------------------------------------------
VType_wxEraseEvent VTYPE_wxEraseEvent("EraseEvent");

void VType_wxEraseEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxEraseEvent
//------------------------------------------------------------------------------
VType& Value_wxEraseEvent::vtype = VTYPE_wxEraseEvent;
EventValueFactoryDeriv<Value_wxEraseEvent> Value_wxEraseEvent::eventValueFactory;

String Value_wxEraseEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.EraseEvent");
}

Gurax_EndModuleScope(wx)
