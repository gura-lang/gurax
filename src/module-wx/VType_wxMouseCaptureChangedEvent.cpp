//==============================================================================
// VType_wxMouseCaptureChangedEvent.cpp
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
// VType_wxMouseCaptureChangedEvent
//------------------------------------------------------------------------------
VType_wxMouseCaptureChangedEvent VTYPE_wxMouseCaptureChangedEvent("MouseCaptureChangedEvent");

void VType_wxMouseCaptureChangedEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxMouseCaptureChangedEvent
//------------------------------------------------------------------------------
VType& Value_wxMouseCaptureChangedEvent::vtype = VTYPE_wxMouseCaptureChangedEvent;
EventValueFactoryDeriv<Value_wxMouseCaptureChangedEvent> Value_wxMouseCaptureChangedEvent::eventValueFactory;

String Value_wxMouseCaptureChangedEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MouseCaptureChangedEvent");
}

Gurax_EndModuleScope(wx)
