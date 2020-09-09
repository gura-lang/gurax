//==============================================================================
// VType_SDL_JoyHatEvent.cpp
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
// sdl.SDL_JoyHatEvent#type
Gurax_DeclareProperty_R(SDL_JoyHatEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_JoyHatEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_JoyHatEvent#timestamp
Gurax_DeclareProperty_R(SDL_JoyHatEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_JoyHatEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

//------------------------------------------------------------------------------
// VType_SDL_JoyHatEvent
//------------------------------------------------------------------------------
VType_SDL_JoyHatEvent VTYPE_SDL_JoyHatEvent("SDL_JoyHatEvent");

void VType_SDL_JoyHatEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_JoyHatEvent, type));
	Assign(Gurax_CreateProperty(SDL_JoyHatEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_JoyHatEvent
//------------------------------------------------------------------------------
VType& Value_SDL_JoyHatEvent::vtype = VTYPE_SDL_JoyHatEvent;

String Value_SDL_JoyHatEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_JoyHatEvent";
}

Gurax_EndModuleScope(sdl)
