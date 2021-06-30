//==============================================================================
// Events.cpp
//==============================================================================
#include "stdafx.h"

#define AssignEvent(eventName, eventType) do { \
RefPtr<Value> pValue(new Value_wxEventType(wx##eventName, #eventName, Value_##eventType::eventValueFactory)); \
g_eventTypeMap[wx##eventName] = pValue.Reference(); \
frame.Assign(#eventName, pValue.release()); \
} while (0)

Gurax_BeginModuleScope(wx)

using EventTypeMap = std::unordered_map<wxEventType, Value*>;

static EventTypeMap g_eventTypeMap;

//------------------------------------------------------------------------------
// Function
//------------------------------------------------------------------------------
// wx.EVT_JOYSTICK_EVENTS(handler.wxEvtHandler, id:Number, funct:Any)
Gurax_DeclareFunction(EVT_JOYSTICK_EVENTS)
{
	Declare(VTYPE_Number, Flag::None);
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("handler", VTYPE_wxEvtHandler, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("funct", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(EVT_JOYSTICK_EVENTS)
{
	static const wxEventType eventTypes[] = {
		wxEVT_JOY_BUTTON_DOWN,
		wxEVT_JOY_BUTTON_UP,
		wxEVT_JOY_MOVE,
		wxEVT_JOY_ZMOVE,
	};
	Util::BindMultiEvents(processor, argument, eventTypes, Gurax_ArraySizeOf(eventTypes), Value_wxMouseEvent::eventValueFactory);
	return Value::nil();
}

// wx.EVT_MOUSE_EVENTS(handler.wxEvtHandler, id:Number, funct:Any)
Gurax_DeclareFunction(EVT_MOUSE_EVENTS)
{
	Declare(VTYPE_Number, Flag::None);
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("handler", VTYPE_wxEvtHandler, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("funct", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(EVT_MOUSE_EVENTS)
{
	static const wxEventType eventTypes[] = {
		wxEVT_LEFT_DOWN,
		wxEVT_LEFT_UP,
		wxEVT_LEFT_DCLICK,
		wxEVT_MIDDLE_DOWN,
		wxEVT_MIDDLE_UP,
		wxEVT_MIDDLE_DCLICK,
		wxEVT_RIGHT_DOWN,
		wxEVT_RIGHT_UP,
		wxEVT_RIGHT_DCLICK,
		wxEVT_AUX1_DOWN,
		wxEVT_AUX1_UP,
		wxEVT_AUX1_DCLICK,
		wxEVT_AUX2_DOWN,
		wxEVT_AUX2_UP,
		wxEVT_AUX2_DCLICK,
		wxEVT_MOTION,
		wxEVT_ENTER_WINDOW,
		wxEVT_LEAVE_WINDOW,
		wxEVT_MOUSEWHEEL,
	};
	Util::BindMultiEvents(processor, argument, eventTypes, Gurax_ArraySizeOf(eventTypes), Value_wxMouseEvent::eventValueFactory);
	return Value::nil();
}

// wx.EVT_SCROLLWIN(handler.wxEvtHandler, id:Number, funct:Any)
Gurax_DeclareFunction(EVT_SCROLLWIN)
{
	Declare(VTYPE_Number, Flag::None);
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("handler", VTYPE_wxEvtHandler, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("funct", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(EVT_SCROLLWIN)
{
	static const wxEventType eventTypes[] = {
		wxEVT_SCROLLWIN_TOP,
		wxEVT_SCROLLWIN_BOTTOM,
		wxEVT_SCROLLWIN_LINEUP,
		wxEVT_SCROLLWIN_LINEDOWN,
		wxEVT_SCROLLWIN_PAGEUP,
		wxEVT_SCROLLWIN_PAGEDOWN,
		wxEVT_SCROLLWIN_THUMBTRACK,
		wxEVT_SCROLLWIN_THUMBRELEASE,
	};
	Util::BindMultiEvents(processor, argument, eventTypes, Gurax_ArraySizeOf(eventTypes), Value_wxMouseEvent::eventValueFactory);
	return Value::nil();
}

//------------------------------------------------------------------------------
// Assignment
//------------------------------------------------------------------------------
void AssignEvents(Frame& frame)
{
	AssignEvent(EVT_MENU,						wxCommandEvent);
	AssignEvent(EVT_COMMAND_BUTTON_CLICKED,		wxCommandEvent);
	AssignEvent(EVT_BUTTON,						wxCommandEvent);
	AssignEvent(EVT_CHECKBOX,					wxCommandEvent);
	AssignEvent(EVT_CHOICE,						wxCommandEvent);
	AssignEvent(EVT_COMBOBOX,					wxCommandEvent);
	AssignEvent(EVT_LISTBOX,					wxCommandEvent);
	AssignEvent(EVT_LISTBOX_DCLICK,				wxCommandEvent);
	AssignEvent(EVT_CHECKLISTBOX,				wxCommandEvent);
	AssignEvent(EVT_MENU,						wxCommandEvent);
	AssignEvent(EVT_CONTEXT_MENU,				wxCommandEvent);
	AssignEvent(EVT_RADIOBOX,					wxCommandEvent);
	AssignEvent(EVT_RADIOBUTTON,				wxCommandEvent);
	AssignEvent(EVT_SCROLLBAR,					wxCommandEvent);
	AssignEvent(EVT_SLIDER,						wxCommandEvent);
	AssignEvent(EVT_TEXT,						wxCommandEvent);
	AssignEvent(EVT_TEXT_ENTER,					wxCommandEvent);
	AssignEvent(EVT_TEXT_MAXLEN,				wxCommandEvent);
	//AssignEvent(EVT_TOGGLEBUTTON,				wxCommandEvent);
	AssignEvent(EVT_TOOL,						wxCommandEvent);
	AssignEvent(EVT_TOOL_RCLICKED,				wxCommandEvent);
	AssignEvent(EVT_TOOL_ENTER,					wxCommandEvent);
	AssignEvent(EVT_COMMAND_LEFT_CLICK,			wxCommandEvent);
	AssignEvent(EVT_COMMAND_LEFT_DCLICK,		wxCommandEvent);
	AssignEvent(EVT_COMMAND_RIGHT_CLICK,		wxCommandEvent);
	AssignEvent(EVT_COMMAND_RIGHT_DCLICK,		wxCommandEvent);
	AssignEvent(EVT_COMMAND_SET_FOCUS,			wxCommandEvent);
	AssignEvent(EVT_COMMAND_KILL_FOCUS,			wxCommandEvent);
	AssignEvent(EVT_COMMAND_ENTER,				wxCommandEvent);
	AssignEvent(EVT_ACTIVATE,					wxActivateEvent);
	AssignEvent(EVT_CHILD_FOCUS,				wxChildFocusEvent);
	AssignEvent(EVT_CONTEXT_MENU,				wxContextMenuEvent);
	AssignEvent(EVT_HELP,						wxHelpEvent);
	AssignEvent(EVT_DROP_FILES,					wxDropFilesEvent);
	AssignEvent(EVT_ERASE_BACKGROUND,			wxEraseEvent);
	AssignEvent(EVT_SET_FOCUS,					wxFocusEvent);
	AssignEvent(EVT_KILL_FOCUS,					wxFocusEvent);
	AssignEvent(EVT_IDLE,						wxIdleEvent);
	frame.Assign(Gurax_CreateFunction(EVT_JOYSTICK_EVENTS));
	AssignEvent(EVT_JOY_BUTTON_DOWN,			wxJoystickEvent);
	AssignEvent(EVT_JOY_BUTTON_UP,				wxJoystickEvent);
	AssignEvent(EVT_JOY_MOVE,					wxJoystickEvent);
	AssignEvent(EVT_JOY_ZMOVE,					wxJoystickEvent);
	AssignEvent(EVT_KEY_DOWN,					wxKeyEvent);
	AssignEvent(EVT_KEY_UP,						wxKeyEvent);
	AssignEvent(EVT_CHAR,						wxKeyEvent);
	AssignEvent(EVT_CHAR_HOOK,					wxKeyEvent);
	AssignEvent(EVT_MOUSE_CAPTURE_LOST,			wxMouseCaptureLostEvent);
	AssignEvent(EVT_MOUSE_CAPTURE_CHANGED,		wxMouseCaptureChangedEvent);
	AssignEvent(EVT_LEFT_DOWN,					wxMouseEvent);
	AssignEvent(EVT_LEFT_UP,					wxMouseEvent);
	AssignEvent(EVT_LEFT_DCLICK,				wxMouseEvent);
	AssignEvent(EVT_MIDDLE_DOWN,				wxMouseEvent);
	AssignEvent(EVT_MIDDLE_UP,					wxMouseEvent);
	AssignEvent(EVT_MIDDLE_DCLICK,				wxMouseEvent);
	AssignEvent(EVT_RIGHT_DOWN,					wxMouseEvent);
	AssignEvent(EVT_RIGHT_UP,					wxMouseEvent);
	AssignEvent(EVT_RIGHT_DCLICK,				wxMouseEvent);
	AssignEvent(EVT_AUX1_DOWN,					wxMouseEvent);
	AssignEvent(EVT_AUX1_UP,					wxMouseEvent);
	AssignEvent(EVT_AUX1_DCLICK,				wxMouseEvent);
	AssignEvent(EVT_AUX2_DOWN,					wxMouseEvent);
	AssignEvent(EVT_AUX2_UP,					wxMouseEvent);
	AssignEvent(EVT_AUX2_DCLICK,				wxMouseEvent);
	AssignEvent(EVT_MOTION,						wxMouseEvent);
	AssignEvent(EVT_ENTER_WINDOW,				wxMouseEvent);
	AssignEvent(EVT_LEAVE_WINDOW,				wxMouseEvent);
	AssignEvent(EVT_MOUSEWHEEL,					wxMouseEvent);
	frame.Assign(Gurax_CreateFunction(EVT_MOUSE_EVENTS));
	AssignEvent(EVT_PAINT,						wxPaintEvent);
	AssignEvent(EVT_POWER_SUSPENDING,			wxPowerEvent);
	AssignEvent(EVT_POWER_SUSPENDED,			wxPowerEvent);
	AssignEvent(EVT_POWER_SUSPEND_CANCEL,		wxPowerEvent);
	AssignEvent(EVT_POWER_RESUME,				wxPowerEvent);
	frame.Assign(Gurax_CreateFunction(EVT_SCROLLWIN));
	AssignEvent(EVT_SCROLLWIN_TOP,				wxScrollWinEvent);
	AssignEvent(EVT_SCROLLWIN_BOTTOM,			wxScrollWinEvent);
	AssignEvent(EVT_SCROLLWIN_LINEUP,			wxScrollWinEvent);
	AssignEvent(EVT_SCROLLWIN_LINEDOWN,			wxScrollWinEvent);
	AssignEvent(EVT_SCROLLWIN_PAGEUP,			wxScrollWinEvent);
	AssignEvent(EVT_SCROLLWIN_PAGEDOWN,			wxScrollWinEvent);
	AssignEvent(EVT_SCROLLWIN_THUMBTRACK,		wxScrollWinEvent);
	AssignEvent(EVT_SCROLLWIN_THUMBRELEASE,		wxScrollWinEvent);
	AssignEvent(EVT_SET_CURSOR,					wxSetCursorEvent);
	AssignEvent(EVT_SIZE,						wxSizeEvent);
	AssignEvent(EVT_SYS_COLOUR_CHANGED,			wxSysColourChangedEvent);
}

const Value& LookupEventType(wxEventType eventType)
{
	auto iter = g_eventTypeMap.find(eventType);
	if (iter == g_eventTypeMap.end()) return Value::C_nil();
	return *iter->second;
}

Gurax_EndModuleScope(wx)
