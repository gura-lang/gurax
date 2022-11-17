//==============================================================================
// VType_SDL_DollarGestureEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_DollarGestureEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_DollarGestureEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_DollarGestureEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_DollarGestureEvent#type
Gurax_DeclareProperty_R(SDL_DollarGestureEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_DollarGestureEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_DollarGestureEvent#timestamp
Gurax_DeclareProperty_R(SDL_DollarGestureEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_DollarGestureEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_DollarGestureEvent#touchId
Gurax_DeclareProperty_R(SDL_DollarGestureEvent, touchId)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_DollarGestureEvent, touchId)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().touchId);
}

// sdl.SDL_DollarGestureEvent#gestureId
Gurax_DeclareProperty_R(SDL_DollarGestureEvent, gestureId)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_DollarGestureEvent, gestureId)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().gestureId);
}

// sdl.SDL_DollarGestureEvent#numFingers
Gurax_DeclareProperty_R(SDL_DollarGestureEvent, numFingers)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_DollarGestureEvent, numFingers)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().numFingers);
}

// sdl.SDL_DollarGestureEvent#error
Gurax_DeclareProperty_R(SDL_DollarGestureEvent, error)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_DollarGestureEvent, error)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().error);
}

// sdl.SDL_DollarGestureEvent#x
Gurax_DeclareProperty_R(SDL_DollarGestureEvent, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_DollarGestureEvent, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().x);
}

// sdl.SDL_DollarGestureEvent#y
Gurax_DeclareProperty_R(SDL_DollarGestureEvent, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_DollarGestureEvent, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().y);
}

//------------------------------------------------------------------------------
// VType_SDL_DollarGestureEvent
//------------------------------------------------------------------------------
VType_SDL_DollarGestureEvent VTYPE_SDL_DollarGestureEvent("SDL_DollarGestureEvent");

void VType_SDL_DollarGestureEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_DollarGestureEvent, type));
	Assign(Gurax_CreateProperty(SDL_DollarGestureEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_DollarGestureEvent, touchId));
	Assign(Gurax_CreateProperty(SDL_DollarGestureEvent, gestureId));
	Assign(Gurax_CreateProperty(SDL_DollarGestureEvent, numFingers));
	Assign(Gurax_CreateProperty(SDL_DollarGestureEvent, error));
	Assign(Gurax_CreateProperty(SDL_DollarGestureEvent, x));
	Assign(Gurax_CreateProperty(SDL_DollarGestureEvent, y));
}

//------------------------------------------------------------------------------
// Value_SDL_DollarGestureEvent
//------------------------------------------------------------------------------
VType& Value_SDL_DollarGestureEvent::vtype = VTYPE_SDL_DollarGestureEvent;

String Value_SDL_DollarGestureEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_DollarGestureEvent");
}

Gurax_EndModuleScope(sdl)
