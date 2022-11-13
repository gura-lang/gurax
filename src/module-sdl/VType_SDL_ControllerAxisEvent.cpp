//==============================================================================
// VType_SDL_ControllerAxisEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_ControllerAxisEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_ControllerAxisEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_ControllerAxisEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_ControllerAxisEvent#type
Gurax_DeclareProperty_R(SDL_ControllerAxisEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_ControllerAxisEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_ControllerAxisEvent#timestamp
Gurax_DeclareProperty_R(SDL_ControllerAxisEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_ControllerAxisEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_ControllerAxisEvent#which
Gurax_DeclareProperty_R(SDL_ControllerAxisEvent, which)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_ControllerAxisEvent, which)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().which);
}

// sdl.SDL_ControllerAxisEvent#axis
Gurax_DeclareProperty_R(SDL_ControllerAxisEvent, axis)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_ControllerAxisEvent, axis)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().axis);
}

// sdl.SDL_ControllerAxisEvent#value
Gurax_DeclareProperty_R(SDL_ControllerAxisEvent, value)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_ControllerAxisEvent, value)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().value);
}

//------------------------------------------------------------------------------
// VType_SDL_ControllerAxisEvent
//------------------------------------------------------------------------------
VType_SDL_ControllerAxisEvent VTYPE_SDL_ControllerAxisEvent("SDL_ControllerAxisEvent");

void VType_SDL_ControllerAxisEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_ControllerAxisEvent, type));
	Assign(Gurax_CreateProperty(SDL_ControllerAxisEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_ControllerAxisEvent, which));
	Assign(Gurax_CreateProperty(SDL_ControllerAxisEvent, axis));
	Assign(Gurax_CreateProperty(SDL_ControllerAxisEvent, value));
}

//------------------------------------------------------------------------------
// Value_SDL_ControllerAxisEvent
//------------------------------------------------------------------------------
VType& Value_SDL_ControllerAxisEvent::vtype = VTYPE_SDL_ControllerAxisEvent;

String Value_SDL_ControllerAxisEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_ControllerAxisEvent");
}

Gurax_EndModuleScope(sdl)
