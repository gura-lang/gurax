//==============================================================================
// VType_wxChildFocusEvent.cpp
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

${help.ComposePropertyHelp(wx.ChildFocusEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.ChildFocusEvent, `en)}

${help.ComposeMethodHelp(wx.ChildFocusEvent, `en)}
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
// VType_wxChildFocusEvent
//------------------------------------------------------------------------------
VType_wxChildFocusEvent VTYPE_wxChildFocusEvent("ChildFocusEvent");

void VType_wxChildFocusEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxChildFocusEvent
//------------------------------------------------------------------------------
VType& Value_wxChildFocusEvent::vtype = VTYPE_wxChildFocusEvent;
EventValueFactoryDeriv<Value_wxChildFocusEvent> Value_wxChildFocusEvent::eventValueFactory;

String Value_wxChildFocusEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ChildFocusEvent");
}

Gurax_EndModuleScope(wx)
