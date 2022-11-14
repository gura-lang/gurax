//==============================================================================
// MultiEvents.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

// wx.EVT_JOYSTICK_EVENTS(handler as wx.EvtHandler, funct as Any, id? as Number)
Gurax_DeclareFunction(EVT_JOYSTICK_EVENTS)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("handler", VTYPE_wxEvtHandler, ArgOccur::Once, ArgFlag::None);
	DeclareArg("funct", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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

// wx.EVT_MOUSE_EVENTS(handler as wx.EvtHandler, funct as Any, id? as Number)
Gurax_DeclareFunction(EVT_MOUSE_EVENTS)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("handler", VTYPE_wxEvtHandler, ArgOccur::Once, ArgFlag::None);
	DeclareArg("funct", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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

// wx.EVT_SCROLL(handler as wx.EvtHandler, funct as Any, id? as Number)
Gurax_DeclareFunction(EVT_SCROLL)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("handler", VTYPE_wxEvtHandler, ArgOccur::Once, ArgFlag::None);
	DeclareArg("funct", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementFunction(EVT_SCROLL)
{
	static const wxEventType eventTypes[] = {
		wxEVT_SCROLL_TOP,
		wxEVT_SCROLL_BOTTOM,
		wxEVT_SCROLL_LINEUP,
		wxEVT_SCROLL_LINEDOWN,
		wxEVT_SCROLL_PAGEUP,
		wxEVT_SCROLL_PAGEDOWN,
		wxEVT_SCROLL_THUMBTRACK,
		wxEVT_SCROLL_THUMBRELEASE,
		wxEVT_SCROLL_CHANGED,
	};
	Util::BindMultiEvents(processor, argument, eventTypes, Gurax_ArraySizeOf(eventTypes), Value_wxScrollEvent::eventValueFactory);
	return Value::nil();
}

// wx.EVT_SCROLLWIN(handler as wx.EvtHandler, funct as Any, id? as Number)
Gurax_DeclareFunction(EVT_SCROLLWIN)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("handler", VTYPE_wxEvtHandler, ArgOccur::Once, ArgFlag::None);
	DeclareArg("funct", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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

void AssignMultiEvents(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(EVT_JOYSTICK_EVENTS));
	frame.Assign(Gurax_CreateFunction(EVT_MOUSE_EVENTS));
	frame.Assign(Gurax_CreateFunction(EVT_SCROLL));
	frame.Assign(Gurax_CreateFunction(EVT_SCROLLWIN));
}

Gurax_EndModuleScope(wx)
