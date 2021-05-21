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
    frame.Assign("EVT_COMMAND_BUTTON_CLICKED", new Value_EventType(wxEVT_COMMAND_BUTTON_CLICKED));
}

Gurax_EndModuleScope(wx)
