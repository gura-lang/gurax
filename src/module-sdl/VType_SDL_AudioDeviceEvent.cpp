//==============================================================================
// VType_SDL_AudioDeviceEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_AudioDeviceEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_AudioDeviceEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_AudioDeviceEvent, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_AudioDeviceEvent#type
Gurax_DeclareProperty_R(SDL_AudioDeviceEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_AudioDeviceEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_AudioDeviceEvent#timestamp
Gurax_DeclareProperty_R(SDL_AudioDeviceEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_AudioDeviceEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_AudioDeviceEvent#which
Gurax_DeclareProperty_R(SDL_AudioDeviceEvent, which)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_AudioDeviceEvent, which)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().which);
}

// sdl.SDL_AudioDeviceEvent#iscapture
Gurax_DeclareProperty_R(SDL_AudioDeviceEvent, iscapture)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_AudioDeviceEvent, iscapture)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().iscapture);
}

//------------------------------------------------------------------------------
// VType_SDL_AudioDeviceEvent
//------------------------------------------------------------------------------
VType_SDL_AudioDeviceEvent VTYPE_SDL_AudioDeviceEvent("SDL_AudioDeviceEvent");

void VType_SDL_AudioDeviceEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_AudioDeviceEvent, type));
	Assign(Gurax_CreateProperty(SDL_AudioDeviceEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_AudioDeviceEvent, which));
	Assign(Gurax_CreateProperty(SDL_AudioDeviceEvent, iscapture));
}

//------------------------------------------------------------------------------
// Value_SDL_AudioDeviceEvent
//------------------------------------------------------------------------------
VType& Value_SDL_AudioDeviceEvent::vtype = VTYPE_SDL_AudioDeviceEvent;

String Value_SDL_AudioDeviceEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_AudioDeviceEvent");
}

Gurax_EndModuleScope(sdl)
