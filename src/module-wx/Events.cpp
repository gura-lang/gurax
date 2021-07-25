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
	Gurax_AssignEvent(EVT_MENU,						wxCommandEvent);
	Gurax_AssignEvent(EVT_COMMAND_BUTTON_CLICKED,		wxCommandEvent);
	Gurax_AssignEvent(EVT_BUTTON,						wxCommandEvent);
	Gurax_AssignEvent(EVT_CHECKBOX,					wxCommandEvent);
	Gurax_AssignEvent(EVT_CHOICE,						wxCommandEvent);
	Gurax_AssignEvent(EVT_COMBOBOX,					wxCommandEvent);
	Gurax_AssignEvent(EVT_LISTBOX,					wxCommandEvent);
	Gurax_AssignEvent(EVT_LISTBOX_DCLICK,				wxCommandEvent);
	Gurax_AssignEvent(EVT_CHECKLISTBOX,				wxCommandEvent);
	Gurax_AssignEvent(EVT_MENU,						wxCommandEvent);
	Gurax_AssignEvent(EVT_CONTEXT_MENU,				wxCommandEvent);
	Gurax_AssignEvent(EVT_RADIOBOX,					wxCommandEvent);
	Gurax_AssignEvent(EVT_RADIOBUTTON,				wxCommandEvent);
	Gurax_AssignEvent(EVT_SCROLLBAR,					wxCommandEvent);
	Gurax_AssignEvent(EVT_SLIDER,						wxCommandEvent);
	Gurax_AssignEvent(EVT_TEXT,						wxCommandEvent);
	Gurax_AssignEvent(EVT_TEXT_ENTER,					wxCommandEvent);
	Gurax_AssignEvent(EVT_TEXT_MAXLEN,				wxCommandEvent);
	//Gurax_AssignEvent(EVT_TOGGLEBUTTON,				wxCommandEvent);
	Gurax_AssignEvent(EVT_TOOL,						wxCommandEvent);
	Gurax_AssignEvent(EVT_TOOL_RCLICKED,				wxCommandEvent);
	Gurax_AssignEvent(EVT_TOOL_ENTER,					wxCommandEvent);
	Gurax_AssignEvent(EVT_COMMAND_LEFT_CLICK,			wxCommandEvent);
	Gurax_AssignEvent(EVT_COMMAND_LEFT_DCLICK,		wxCommandEvent);
	Gurax_AssignEvent(EVT_COMMAND_RIGHT_CLICK,		wxCommandEvent);
	Gurax_AssignEvent(EVT_COMMAND_RIGHT_DCLICK,		wxCommandEvent);
	Gurax_AssignEvent(EVT_COMMAND_SET_FOCUS,			wxCommandEvent);
	Gurax_AssignEvent(EVT_COMMAND_KILL_FOCUS,			wxCommandEvent);
	Gurax_AssignEvent(EVT_COMMAND_ENTER,				wxCommandEvent);
	Gurax_AssignEvent(EVT_ACTIVATE,					wxActivateEvent);
	Gurax_AssignEvent(EVT_CHILD_FOCUS,				wxChildFocusEvent);
	Gurax_AssignEvent(EVT_CONTEXT_MENU,				wxContextMenuEvent);
	Gurax_AssignEvent(EVT_HELP,						wxHelpEvent);
	Gurax_AssignEvent(EVT_DROP_FILES,					wxDropFilesEvent);
	Gurax_AssignEvent(EVT_ERASE_BACKGROUND,			wxEraseEvent);
	Gurax_AssignEvent(EVT_SET_FOCUS,					wxFocusEvent);
	Gurax_AssignEvent(EVT_KILL_FOCUS,					wxFocusEvent);
	Gurax_AssignEvent(EVT_IDLE,						wxIdleEvent);
	Gurax_AssignEvent(EVT_JOY_BUTTON_DOWN,			wxJoystickEvent);
	Gurax_AssignEvent(EVT_JOY_BUTTON_UP,				wxJoystickEvent);
	Gurax_AssignEvent(EVT_JOY_MOVE,					wxJoystickEvent);
	Gurax_AssignEvent(EVT_JOY_ZMOVE,					wxJoystickEvent);
	Gurax_AssignEvent(EVT_KEY_DOWN,					wxKeyEvent);
	Gurax_AssignEvent(EVT_KEY_UP,						wxKeyEvent);
	Gurax_AssignEvent(EVT_CHAR,						wxKeyEvent);
	Gurax_AssignEvent(EVT_CHAR_HOOK,					wxKeyEvent);
	Gurax_AssignEvent(EVT_MOUSE_CAPTURE_LOST,			wxMouseCaptureLostEvent);
	Gurax_AssignEvent(EVT_MOUSE_CAPTURE_CHANGED,		wxMouseCaptureChangedEvent);
	Gurax_AssignEvent(EVT_LEFT_DOWN,					wxMouseEvent);
	Gurax_AssignEvent(EVT_LEFT_UP,					wxMouseEvent);
	Gurax_AssignEvent(EVT_LEFT_DCLICK,				wxMouseEvent);
	Gurax_AssignEvent(EVT_MIDDLE_DOWN,				wxMouseEvent);
	Gurax_AssignEvent(EVT_MIDDLE_UP,					wxMouseEvent);
	Gurax_AssignEvent(EVT_MIDDLE_DCLICK,				wxMouseEvent);
	Gurax_AssignEvent(EVT_RIGHT_DOWN,					wxMouseEvent);
	Gurax_AssignEvent(EVT_RIGHT_UP,					wxMouseEvent);
	Gurax_AssignEvent(EVT_RIGHT_DCLICK,				wxMouseEvent);
	Gurax_AssignEvent(EVT_AUX1_DOWN,					wxMouseEvent);
	Gurax_AssignEvent(EVT_AUX1_UP,					wxMouseEvent);
	Gurax_AssignEvent(EVT_AUX1_DCLICK,				wxMouseEvent);
	Gurax_AssignEvent(EVT_AUX2_DOWN,					wxMouseEvent);
	Gurax_AssignEvent(EVT_AUX2_UP,					wxMouseEvent);
	Gurax_AssignEvent(EVT_AUX2_DCLICK,				wxMouseEvent);
	Gurax_AssignEvent(EVT_MOTION,						wxMouseEvent);
	Gurax_AssignEvent(EVT_ENTER_WINDOW,				wxMouseEvent);
	Gurax_AssignEvent(EVT_LEAVE_WINDOW,				wxMouseEvent);
	Gurax_AssignEvent(EVT_MOUSEWHEEL,					wxMouseEvent);
	Gurax_AssignEvent(EVT_PAINT,						wxPaintEvent);
	Gurax_AssignEvent(EVT_POWER_SUSPENDING,			wxPowerEvent);
	Gurax_AssignEvent(EVT_POWER_SUSPENDED,			wxPowerEvent);
	Gurax_AssignEvent(EVT_POWER_SUSPEND_CANCEL,		wxPowerEvent);
	Gurax_AssignEvent(EVT_POWER_RESUME,				wxPowerEvent);
	Gurax_AssignEvent(EVT_SCROLLWIN_TOP,				wxScrollWinEvent);
	Gurax_AssignEvent(EVT_SCROLLWIN_BOTTOM,			wxScrollWinEvent);
	Gurax_AssignEvent(EVT_SCROLLWIN_LINEUP,			wxScrollWinEvent);
	Gurax_AssignEvent(EVT_SCROLLWIN_LINEDOWN,			wxScrollWinEvent);
	Gurax_AssignEvent(EVT_SCROLLWIN_PAGEUP,			wxScrollWinEvent);
	Gurax_AssignEvent(EVT_SCROLLWIN_PAGEDOWN,			wxScrollWinEvent);
	Gurax_AssignEvent(EVT_SCROLLWIN_THUMBTRACK,		wxScrollWinEvent);
	Gurax_AssignEvent(EVT_SCROLLWIN_THUMBRELEASE,		wxScrollWinEvent);
	Gurax_AssignEvent(EVT_SET_CURSOR,					wxSetCursorEvent);
	Gurax_AssignEvent(EVT_SIZE,						wxSizeEvent);
	Gurax_AssignEvent(EVT_SYS_COLOUR_CHANGED,			wxSysColourChangedEvent);
}

Gurax_EndModuleScope(wx)
