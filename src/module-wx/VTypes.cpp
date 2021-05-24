//==============================================================================
// VTypes.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Assignment
//------------------------------------------------------------------------------
void AssignVTypes(Frame& frame)
{
	frame.Assign(VTYPE_App);
	frame.Assign(VTYPE_AppConsole);
	frame.Assign(VTYPE_CommandEvent);
	frame.Assign(VTYPE_Control);
	frame.Assign(VTYPE_Event);
	frame.Assign(VTYPE_EventType);
	frame.Assign(VTYPE_EvtHandler);
	frame.Assign(VTYPE_Frame);
	frame.Assign(VTYPE_Menu);
	frame.Assign(VTYPE_MenuBar);
	frame.Assign(VTYPE_MenuItem);
	frame.Assign(VTYPE_Panel);
	frame.Assign(VTYPE_Point);
	frame.Assign(VTYPE_Size);
	frame.Assign(VTYPE_StatusBar);
	frame.Assign(VTYPE_Window);
}

Gurax_EndModuleScope(wx)
