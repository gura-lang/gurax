//==============================================================================
// VType_wxTaskBarIconEvent.cpp
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

${help.ComposePropertyHelp(wxTaskBarIconEvent)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxTaskBarIconEvent)}

${help.ComposeMethodHelp(wxTaskBarIconEvent)}
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
// VType_wxTaskBarIconEvent
//------------------------------------------------------------------------------
VType_wxTaskBarIconEvent VTYPE_wxTaskBarIconEvent("TaskBarIconEvent");

void VType_wxTaskBarIconEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxTaskBarIconEvent
//------------------------------------------------------------------------------
VType& Value_wxTaskBarIconEvent::vtype = VTYPE_wxTaskBarIconEvent;
EventValueFactoryDeriv<Value_wxTaskBarIconEvent> Value_wxTaskBarIconEvent::eventValueFactory;

String Value_wxTaskBarIconEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.TaskBarIconEvent");
}

Gurax_EndModuleScope(wx)
