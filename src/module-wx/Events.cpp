//==============================================================================
// Events.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Assignment
//------------------------------------------------------------------------------
void AssignEvents(Frame& frame)
{
	frame.Assign("EVT_MENU", new Value_EventType(wxEVT_MENU, Value_CommandEvent::eventValueFactory));
	frame.Assign("EVT_COMMAND_BUTTON_CLICKED", new Value_EventType(wxEVT_COMMAND_BUTTON_CLICKED, Value_CommandEvent::eventValueFactory));
}

Gurax_EndModuleScope(wx)
