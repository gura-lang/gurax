//==============================================================================
// VType_SDL_JoyButtonEvent.cpp
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
// sdl.SDL_JoyButtonEvent#type
Gurax_DeclareProperty_R(SDL_JoyButtonEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_JoyButtonEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_JoyButtonEvent#timestamp
Gurax_DeclareProperty_R(SDL_JoyButtonEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_JoyButtonEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

//------------------------------------------------------------------------------
// VType_SDL_JoyButtonEvent
//------------------------------------------------------------------------------
VType_SDL_JoyButtonEvent VTYPE_SDL_JoyButtonEvent("SDL_JoyButtonEvent");

void VType_SDL_JoyButtonEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_JoyButtonEvent, type));
	Assign(Gurax_CreateProperty(SDL_JoyButtonEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_JoyButtonEvent
//------------------------------------------------------------------------------
VType& Value_SDL_JoyButtonEvent::vtype = VTYPE_SDL_JoyButtonEvent;

String Value_SDL_JoyButtonEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_JoyButtonEvent";
}

Gurax_EndModuleScope(sdl)
