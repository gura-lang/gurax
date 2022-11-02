//==============================================================================
// VType_wxStyledTextEvent.cpp
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

${help.ComposePropertyHelp(wxStyledTextEvent)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxStyledTextEvent)}

${help.ComposeMethodHelp(wxStyledTextEvent)}
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
// VType_wxStyledTextEvent
//------------------------------------------------------------------------------
VType_wxStyledTextEvent VTYPE_wxStyledTextEvent("StyledTextEvent");

void VType_wxStyledTextEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxStyledTextEvent
//------------------------------------------------------------------------------
VType& Value_wxStyledTextEvent::vtype = VTYPE_wxStyledTextEvent;
EventValueFactoryDeriv<Value_wxStyledTextEvent> Value_wxStyledTextEvent::eventValueFactory;

String Value_wxStyledTextEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.StyledTextEvent");
}

Gurax_EndModuleScope(wx)
