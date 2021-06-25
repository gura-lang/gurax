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
	AssignEvent(EVT_DROP_FILES,					wxDropFilesEvent);
	AssignEvent(EVT_ERASE_BACKGROUND,			wxEraseEvent);
	AssignEvent(EVT_SET_FOCUS,					wxFocusEvent);
	AssignEvent(EVT_KILL_FOCUS,					wxFocusEvent);
	AssignEvent(EVT_IDLE,						wxIdleEvent);
	//AssignEvent(EVT_JOY,						wxJoystickEvent);
	AssignEvent(EVT_KEY_DOWN,					wxKeyEvent);
	AssignEvent(EVT_KEY_UP,						wxKeyEvent);
	AssignEvent(EVT_CHAR,						wxKeyEvent);
	AssignEvent(EVT_CHAR_HOOK,					wxKeyEvent);
	AssignEvent(EVT_MOUSE_CAPTURE_LOST,			wxMouseCaptureLostEvent);
	AssignEvent(EVT_MOUSE_CAPTURE_CHANGED,		wxMouseCaptureChangedEvent);
	//AssignEvent(EVT_MOUSE_,					wxMouseEvent);
	AssignEvent(EVT_LEFT_DOWN,					wxMouseEvent);
	AssignEvent(EVT_LEFT_UP,					wxMouseEvent);
	AssignEvent(EVT_LEFT_DCLICK,				wxMouseEvent);
	AssignEvent(EVT_MIDDLE_DOWN,				wxMouseEvent);
	AssignEvent(EVT_MIDDLE_UP,					wxMouseEvent);
	AssignEvent(EVT_MIDDLE_DCLICK,				wxMouseEvent);
	AssignEvent(EVT_RIGHT_DOWN,					wxMouseEvent);
	AssignEvent(EVT_RIGHT_UP,					wxMouseEvent);
	AssignEvent(EVT_RIGHT_DCLICK,				wxMouseEvent);
	//AssignEvent(EVT_MOUSE_AUX1_DOWN,			wxMouseEvent);
	//AssignEvent(EVT_MOUSE_AUX1_UP,				wxMouseEvent);
	//AssignEvent(EVT_MOUSE_AUX1_DCLICK,			wxMouseEvent);
	//AssignEvent(EVT_MOUSE_AUX2_DOWN,			wxMouseEvent);
	//AssignEvent(EVT_MOUSE_AUX2_UP,				wxMouseEvent);
	//AssignEvent(EVT_MOUSE_AUX2_DCLICK,			wxMouseEvent);
	AssignEvent(EVT_MOTION,						wxMouseEvent);
	AssignEvent(EVT_ENTER_WINDOW,				wxMouseEvent);
	AssignEvent(EVT_LEAVE_WINDOW,				wxMouseEvent);
	AssignEvent(EVT_MOUSEWHEEL,					wxMouseEvent);
	//AssignEvent(EVT_MOUSE_EVENTS,				wxMouseEvent);
	AssignEvent(EVT_PAINT,						wxPaintEvent);
	//AssignEvent(EVT_POWER_,					wxPowerEvent);
	//AssignEvent(EVT_SCROLLWIN_,					wxScrollWinEvent);
	//AssignEvent(EVT_SET_CURSOR,					wxSetCursorEvent);
	AssignEvent(EVT_SIZE,						wxSizeEvent);
	//AssignEvent(EVT_SYSCOLOUR_CHANGED,			wxSysColourChangedEvent);

}

Gurax_EndModuleScope(wx)
