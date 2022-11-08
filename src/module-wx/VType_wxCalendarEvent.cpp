//==============================================================================
// VType_wxCalendarEvent.cpp
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

${help.ComposePropertyHelp(wx.CalendarEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.CalendarEvent, `en)}

${help.ComposeMethodHelp(wx.CalendarEvent, `en)}
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
// VType_wxCalendarEvent
//------------------------------------------------------------------------------
VType_wxCalendarEvent VTYPE_wxCalendarEvent("CalendarEvent");

void VType_wxCalendarEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDateEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxCalendarEvent
//------------------------------------------------------------------------------
VType& Value_wxCalendarEvent::vtype = VTYPE_wxCalendarEvent;
EventValueFactoryDeriv<Value_wxCalendarEvent> Value_wxCalendarEvent::eventValueFactory;

String Value_wxCalendarEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.CalendarEvent");
}

Gurax_EndModuleScope(wx)
