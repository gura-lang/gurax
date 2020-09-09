//==============================================================================
// VType_SDL_MouseMotionEvent.cpp
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
// sdl.SDL_MouseMotionEvent#type
Gurax_DeclareProperty_R(SDL_MouseMotionEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_MouseMotionEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_MouseMotionEvent#timestamp
Gurax_DeclareProperty_R(SDL_MouseMotionEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_MouseMotionEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

//------------------------------------------------------------------------------
// VType_SDL_MouseMotionEvent
//------------------------------------------------------------------------------
VType_SDL_MouseMotionEvent VTYPE_SDL_MouseMotionEvent("SDL_MouseMotionEvent");

void VType_SDL_MouseMotionEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_MouseMotionEvent, type));
	Assign(Gurax_CreateProperty(SDL_MouseMotionEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_MouseMotionEvent
//------------------------------------------------------------------------------
VType& Value_SDL_MouseMotionEvent::vtype = VTYPE_SDL_MouseMotionEvent;

String Value_SDL_MouseMotionEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_MouseMotionEvent";
}

Gurax_EndModuleScope(sdl)
