//==============================================================================
// VType_SDL_MultiGestureEvent.cpp
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
// sdl.SDL_MultiGestureEvent#type
Gurax_DeclareProperty_R(SDL_MultiGestureEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_MultiGestureEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_MultiGestureEvent#timestamp
Gurax_DeclareProperty_R(SDL_MultiGestureEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_MultiGestureEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

//------------------------------------------------------------------------------
// VType_SDL_MultiGestureEvent
//------------------------------------------------------------------------------
VType_SDL_MultiGestureEvent VTYPE_SDL_MultiGestureEvent("SDL_MultiGestureEvent");

void VType_SDL_MultiGestureEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_MultiGestureEvent, type));
	Assign(Gurax_CreateProperty(SDL_MultiGestureEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_MultiGestureEvent
//------------------------------------------------------------------------------
VType& Value_SDL_MultiGestureEvent::vtype = VTYPE_SDL_MultiGestureEvent;

String Value_SDL_MultiGestureEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_MultiGestureEvent";
}

Gurax_EndModuleScope(sdl)
