//==============================================================================
// VType_SDL_KeyboardEvent.cpp
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
// sdl.SDL_KeyboardEvent#type
Gurax_DeclareProperty_R(SDL_KeyboardEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_KeyboardEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_KeyboardEvent#timestamp
Gurax_DeclareProperty_R(SDL_KeyboardEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_KeyboardEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

//------------------------------------------------------------------------------
// VType_SDL_KeyboardEvent
//------------------------------------------------------------------------------
VType_SDL_KeyboardEvent VTYPE_SDL_KeyboardEvent("SDL_KeyboardEvent");

void VType_SDL_KeyboardEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_KeyboardEvent, type));
	Assign(Gurax_CreateProperty(SDL_KeyboardEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_KeyboardEvent
//------------------------------------------------------------------------------
VType& Value_SDL_KeyboardEvent::vtype = VTYPE_SDL_KeyboardEvent;

String Value_SDL_KeyboardEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_KeyboardEvent";
}

Gurax_EndModuleScope(sdl)
