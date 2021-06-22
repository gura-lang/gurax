//==============================================================================
// Events.cpp
//==============================================================================
#include "stdafx.h"

#define AssignEvent(eventName, eventType) \
frame.Assign(#eventName, new Value_wxEventType(wx##eventName, Value_##eventType::eventValueFactory))

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Assignment
//------------------------------------------------------------------------------
void AssignEvents(Frame& frame)
{
	AssignEvent(EVT_MENU,						wxCommandEvent);
	AssignEvent(EVT_COMMAND_BUTTON_CLICKED,		wxCommandEvent);
	AssignEvent(EVT_BUTTON,						wxCommandEvent);
	AssignEvent(EVT_ACTIVATE,					wxActivateEvent);
	AssignEvent(EVT_CHILD_FOCUS,				wxChildFocusEvent);
	AssignEvent(EVT_CONTEXT_MENU,				wxContextMenuEvent);
	AssignEvent(EVT_HELP,						wxHelpEvent);

}

Gurax_EndModuleScope(wx)
