//==============================================================================
// VType_wxSysColourChangedEvent.cpp
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

${help.ComposePropertyHelp(wx.SysColourChangedEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SysColourChangedEvent, `en)}

${help.ComposeMethodHelp(wx.SysColourChangedEvent, `en)}
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
// VType_wxSysColourChangedEvent
//------------------------------------------------------------------------------
VType_wxSysColourChangedEvent VTYPE_wxSysColourChangedEvent("SysColourChangedEvent");

void VType_wxSysColourChangedEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxSysColourChangedEvent
//------------------------------------------------------------------------------
VType& Value_wxSysColourChangedEvent::vtype = VTYPE_wxSysColourChangedEvent;
EventValueFactoryDeriv<Value_wxSysColourChangedEvent> Value_wxSysColourChangedEvent::eventValueFactory;

String Value_wxSysColourChangedEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SysColourChangedEvent");
}

Gurax_EndModuleScope(wx)
