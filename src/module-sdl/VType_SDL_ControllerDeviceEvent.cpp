//==============================================================================
// VType_SDL_ControllerDeviceEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_ControllerDeviceEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_ControllerDeviceEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_ControllerDeviceEvent, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_ControllerDeviceEvent#type
Gurax_DeclareProperty_R(SDL_ControllerDeviceEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_ControllerDeviceEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_ControllerDeviceEvent#timestamp
Gurax_DeclareProperty_R(SDL_ControllerDeviceEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_ControllerDeviceEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_ControllerDeviceEvent#which
Gurax_DeclareProperty_R(SDL_ControllerDeviceEvent, which)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_ControllerDeviceEvent, which)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().which);
}

//------------------------------------------------------------------------------
// VType_SDL_ControllerDeviceEvent
//------------------------------------------------------------------------------
VType_SDL_ControllerDeviceEvent VTYPE_SDL_ControllerDeviceEvent("SDL_ControllerDeviceEvent");

void VType_SDL_ControllerDeviceEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_ControllerDeviceEvent, type));
	Assign(Gurax_CreateProperty(SDL_ControllerDeviceEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_ControllerDeviceEvent, which));
}

//------------------------------------------------------------------------------
// Value_SDL_ControllerDeviceEvent
//------------------------------------------------------------------------------
VType& Value_SDL_ControllerDeviceEvent::vtype = VTYPE_SDL_ControllerDeviceEvent;

String Value_SDL_ControllerDeviceEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_ControllerDeviceEvent");
}

Gurax_EndModuleScope(sdl)
