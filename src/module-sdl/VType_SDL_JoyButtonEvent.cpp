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

${help.ComposePropertyHelp(sdl.SDL_JoyButtonEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_JoyButtonEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_JoyButtonEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_JoyButtonEvent#type
Gurax_DeclareProperty_R(SDL_JoyButtonEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
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
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyButtonEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_JoyButtonEvent#which
Gurax_DeclareProperty_R(SDL_JoyButtonEvent, which)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyButtonEvent, which)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().which);
}

// sdl.SDL_JoyButtonEvent#button
Gurax_DeclareProperty_R(SDL_JoyButtonEvent, button)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyButtonEvent, button)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().button);
}

// sdl.SDL_JoyButtonEvent#state
Gurax_DeclareProperty_R(SDL_JoyButtonEvent, state)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyButtonEvent, state)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().state);
}

//------------------------------------------------------------------------------
// VType_SDL_JoyButtonEvent
//------------------------------------------------------------------------------
VType_SDL_JoyButtonEvent VTYPE_SDL_JoyButtonEvent("SDL_JoyButtonEvent");

void VType_SDL_JoyButtonEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_JoyButtonEvent, type));
	Assign(Gurax_CreateProperty(SDL_JoyButtonEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_JoyButtonEvent, which));
	Assign(Gurax_CreateProperty(SDL_JoyButtonEvent, button));
	Assign(Gurax_CreateProperty(SDL_JoyButtonEvent, state));
}

//------------------------------------------------------------------------------
// Value_SDL_JoyButtonEvent
//------------------------------------------------------------------------------
VType& Value_SDL_JoyButtonEvent::vtype = VTYPE_SDL_JoyButtonEvent;

String Value_SDL_JoyButtonEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_JoyButtonEvent");
}

Gurax_EndModuleScope(sdl)
