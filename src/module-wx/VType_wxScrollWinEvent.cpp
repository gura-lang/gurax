//==============================================================================
// VType_wxScrollWinEvent.cpp
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
// VType_wxScrollWinEvent
//------------------------------------------------------------------------------
VType_wxScrollWinEvent VTYPE_wxScrollWinEvent("ScrollWinEvent");

void VType_wxScrollWinEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
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
