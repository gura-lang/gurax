//==============================================================================
// VType_SDL_JoyBallEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_JoyBallEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_JoyBallEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_JoyBallEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_JoyBallEvent#type
Gurax_DeclareProperty_R(SDL_JoyBallEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyBallEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_JoyBallEvent#timestamp
Gurax_DeclareProperty_R(SDL_JoyBallEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyBallEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_JoyBallEvent#which
Gurax_DeclareProperty_R(SDL_JoyBallEvent, which)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyBallEvent, which)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().which);
}

// sdl.SDL_JoyBallEvent#ball
Gurax_DeclareProperty_R(SDL_JoyBallEvent, ball)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyBallEvent, ball)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().ball);
}

// sdl.SDL_JoyBallEvent#xrel
Gurax_DeclareProperty_R(SDL_JoyBallEvent, xrel)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyBallEvent, xrel)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().xrel);
}

// sdl.SDL_JoyBallEvent#yrel
Gurax_DeclareProperty_R(SDL_JoyBallEvent, yrel)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyBallEvent, yrel)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().yrel);
}

//------------------------------------------------------------------------------
// VType_SDL_JoyBallEvent
//------------------------------------------------------------------------------
VType_SDL_JoyBallEvent VTYPE_SDL_JoyBallEvent("SDL_JoyBallEvent");

void VType_SDL_JoyBallEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_JoyBallEvent, type));
	Assign(Gurax_CreateProperty(SDL_JoyBallEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_JoyBallEvent, which));
	Assign(Gurax_CreateProperty(SDL_JoyBallEvent, ball));
	Assign(Gurax_CreateProperty(SDL_JoyBallEvent, xrel));
	Assign(Gurax_CreateProperty(SDL_JoyBallEvent, yrel));
}

//------------------------------------------------------------------------------
// Value_SDL_JoyBallEvent
//------------------------------------------------------------------------------
VType& Value_SDL_JoyBallEvent::vtype = VTYPE_SDL_JoyBallEvent;

String Value_SDL_JoyBallEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_JoyBallEvent");
}

Gurax_EndModuleScope(sdl)
