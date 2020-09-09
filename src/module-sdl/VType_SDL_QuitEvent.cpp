//==============================================================================
// VType_SDL_QuitEvent.cpp
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
// sdl.SDL_QuitEvent#type
Gurax_DeclareProperty_R(SDL_QuitEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_QuitEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_QuitEvent#timestamp
Gurax_DeclareProperty_R(SDL_QuitEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_QuitEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

//------------------------------------------------------------------------------
// VType_SDL_QuitEvent
//------------------------------------------------------------------------------
VType_SDL_QuitEvent VTYPE_SDL_QuitEvent("SDL_QuitEvent");

void VType_SDL_QuitEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_QuitEvent, type));
	Assign(Gurax_CreateProperty(SDL_QuitEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_QuitEvent
//------------------------------------------------------------------------------
VType& Value_SDL_QuitEvent::vtype = VTYPE_SDL_QuitEvent;

String Value_SDL_QuitEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_QuitEvent";
}

Gurax_EndModuleScope(sdl)
