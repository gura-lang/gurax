//==============================================================================
// VType_wxPropertyGridEvent.cpp
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

${help.ComposePropertyHelp(wx.PropertyGridEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.PropertyGridEvent, `en)}

${help.ComposeMethodHelp(wx.PropertyGridEvent, `en)}
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
// VType_wxPropertyGridEvent
//------------------------------------------------------------------------------
VType_wxPropertyGridEvent VTYPE_wxPropertyGridEvent("PropertyGridEvent");

void VType_wxPropertyGridEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPropertyGridEvent
//------------------------------------------------------------------------------
VType& Value_wxPropertyGridEvent::vtype = VTYPE_wxPropertyGridEvent;
EventValueFactoryDeriv<Value_wxPropertyGridEvent> Value_wxPropertyGridEvent::eventValueFactory;

String Value_wxPropertyGridEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PropertyGridEvent");
}

Gurax_EndModuleScope(wx)
