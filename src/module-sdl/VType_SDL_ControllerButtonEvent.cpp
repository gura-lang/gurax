//==============================================================================
// VType_SDL_ControllerButtonEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_ControllerButtonEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_ControllerButtonEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_ControllerButtonEvent, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_ControllerButtonEvent#type
Gurax_DeclareProperty_R(SDL_ControllerButtonEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_ControllerButtonEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_ControllerButtonEvent#timestamp
Gurax_DeclareProperty_R(SDL_ControllerButtonEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_ControllerButtonEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_ControllerButtonEvent#which
Gurax_DeclareProperty_R(SDL_ControllerButtonEvent, which)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_ControllerButtonEvent, which)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().which);
}

// sdl.SDL_ControllerButtonEvent#button
Gurax_DeclareProperty_R(SDL_ControllerButtonEvent, button)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_ControllerButtonEvent, button)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().button);
}

// sdl.SDL_ControllerButtonEvent#state
Gurax_DeclareProperty_R(SDL_ControllerButtonEvent, state)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_ControllerButtonEvent, state)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().state);
}

//------------------------------------------------------------------------------
// VType_SDL_ControllerButtonEvent
//------------------------------------------------------------------------------
VType_SDL_ControllerButtonEvent VTYPE_SDL_ControllerButtonEvent("SDL_ControllerButtonEvent");

void VType_SDL_ControllerButtonEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_ControllerButtonEvent, type));
	Assign(Gurax_CreateProperty(SDL_ControllerButtonEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_ControllerButtonEvent, which));
	Assign(Gurax_CreateProperty(SDL_ControllerButtonEvent, button));
	Assign(Gurax_CreateProperty(SDL_ControllerButtonEvent, state));
}

//------------------------------------------------------------------------------
// Value_SDL_ControllerButtonEvent
//------------------------------------------------------------------------------
VType& Value_SDL_ControllerButtonEvent::vtype = VTYPE_SDL_ControllerButtonEvent;

String Value_SDL_ControllerButtonEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_ControllerButtonEvent");
}

Gurax_EndModuleScope(sdl)
