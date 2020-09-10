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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_DollarGestureEvent#type
Gurax_DeclareProperty_R(SDL_DollarGestureEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
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
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_DollarGestureEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

#if 0
SDL_TouchID touchId; /**< The touch device id */
SDL_GestureID gestureId;
Uint32 numFingers;
float error;
float x;            /**< Normalized center of gesture */
float y;            /**< Normalized center of gesture */
#endif

//------------------------------------------------------------------------------
// VType_SDL_DollarGestureEvent
//------------------------------------------------------------------------------
VType_SDL_DollarGestureEvent VTYPE_SDL_DollarGestureEvent("SDL_DollarGestureEvent");

void VType_SDL_DollarGestureEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_DollarGestureEvent, type));
	Assign(Gurax_CreateProperty(SDL_DollarGestureEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_DollarGestureEvent
//------------------------------------------------------------------------------
VType& Value_SDL_DollarGestureEvent::vtype = VTYPE_SDL_DollarGestureEvent;

String Value_SDL_DollarGestureEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_DollarGestureEvent";
}

Gurax_EndModuleScope(sdl)
