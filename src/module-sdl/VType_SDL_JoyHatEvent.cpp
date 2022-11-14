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

${help.ComposePropertyHelp(sdl.SDL_JoyHatEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_JoyHatEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_JoyHatEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_JoyHatEvent#type
Gurax_DeclareProperty_R(SDL_JoyHatEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyHatEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_JoyHatEvent#which
Gurax_DeclareProperty_R(SDL_JoyHatEvent, which)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyHatEvent, which)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().which);
}

// sdl.SDL_JoyHatEvent#hat
Gurax_DeclareProperty_R(SDL_JoyHatEvent, hat)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyHatEvent, hat)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().hat);
}

// sdl.SDL_JoyHatEvent#value
Gurax_DeclareProperty_R(SDL_JoyHatEvent, value)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyHatEvent, value)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().value);
}

//------------------------------------------------------------------------------
// VType_SDL_JoyHatEvent
//------------------------------------------------------------------------------
VType_SDL_JoyHatEvent VTYPE_SDL_JoyHatEvent("SDL_JoyHatEvent");

void VType_SDL_JoyHatEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_JoyHatEvent, type));
	Assign(Gurax_CreateProperty(SDL_JoyHatEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_JoyHatEvent, which));
	Assign(Gurax_CreateProperty(SDL_JoyHatEvent, hat));
	Assign(Gurax_CreateProperty(SDL_JoyHatEvent, value));
}

//------------------------------------------------------------------------------
// Value_SDL_JoyHatEvent
//------------------------------------------------------------------------------
VType& Value_SDL_JoyHatEvent::vtype = VTYPE_SDL_JoyHatEvent;

String Value_SDL_JoyHatEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_JoyHatEvent");
}

Gurax_EndModuleScope(sdl)
