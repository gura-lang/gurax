//==============================================================================
// VType_SDL_TouchFingerEvent.cpp
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
// sdl.SDL_TouchFingerEvent#type
Gurax_DeclareProperty_R(SDL_TouchFingerEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_TouchFingerEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_TouchFingerEvent#timestamp
Gurax_DeclareProperty_R(SDL_TouchFingerEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_TouchFingerEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

//------------------------------------------------------------------------------
// VType_SDL_TouchFingerEvent
//------------------------------------------------------------------------------
VType_SDL_TouchFingerEvent VTYPE_SDL_TouchFingerEvent("SDL_TouchFingerEvent");

void VType_SDL_TouchFingerEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_TouchFingerEvent, type));
	Assign(Gurax_CreateProperty(SDL_TouchFingerEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_TouchFingerEvent
//------------------------------------------------------------------------------
VType& Value_SDL_TouchFingerEvent::vtype = VTYPE_SDL_TouchFingerEvent;

String Value_SDL_TouchFingerEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_TouchFingerEvent";
}

Gurax_EndModuleScope(sdl)
