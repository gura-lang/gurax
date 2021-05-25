//==============================================================================
// Events.cpp
//==============================================================================
#include "stdafx.h"

#define AssignEvent(eventName, eventType) \
frame.Assign(#eventName, new Value_EventType(wx##eventName, Value_##eventType::eventValueFactory))

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Assignment
//------------------------------------------------------------------------------
void AssignEvents(Frame& frame)
{
	AssignEvent(EVT_MENU, CommandEvent);
	AssignEvent(EVT_COMMAND_BUTTON_CLICKED, CommandEvent);
}

Gurax_EndModuleScope(wx)
