//==============================================================================
// VType_wxGridEvent.cpp
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
// VType_wxGridEvent
//------------------------------------------------------------------------------
VType_wxGridEvent VTYPE_wxGridEvent("GridEvent");

void VType_wxGridEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxNotifyEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridEvent
//------------------------------------------------------------------------------
VType& Value_wxGridEvent::vtype = VTYPE_wxGridEvent;
EventValueFactoryDeriv<Value_wxGridEvent> Value_wxGridEvent::eventValueFactory;

String Value_wxGridEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridEvent");
}

Gurax_EndModuleScope(wx)
