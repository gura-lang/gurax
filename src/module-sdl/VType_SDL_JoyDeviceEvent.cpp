//==============================================================================
// VType_SDL_JoyDeviceEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_JoyDeviceEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_JoyDeviceEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_JoyDeviceEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_JoyDeviceEvent#type
Gurax_DeclareProperty_R(SDL_JoyDeviceEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyDeviceEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_JoyDeviceEvent#timestamp
Gurax_DeclareProperty_R(SDL_JoyDeviceEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyDeviceEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_JoyDeviceEvent#which
Gurax_DeclareProperty_R(SDL_JoyDeviceEvent, which)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoyDeviceEvent, which)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().which);
}

//------------------------------------------------------------------------------
// VType_SDL_JoyDeviceEvent
//------------------------------------------------------------------------------
VType_SDL_JoyDeviceEvent VTYPE_SDL_JoyDeviceEvent("SDL_JoyDeviceEvent");

void VType_SDL_JoyDeviceEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_JoyDeviceEvent, type));
	Assign(Gurax_CreateProperty(SDL_JoyDeviceEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_JoyDeviceEvent, which));
}

//------------------------------------------------------------------------------
// Value_SDL_JoyDeviceEvent
//------------------------------------------------------------------------------
VType& Value_SDL_JoyDeviceEvent::vtype = VTYPE_SDL_JoyDeviceEvent;

String Value_SDL_JoyDeviceEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_JoyDeviceEvent");
}

Gurax_EndModuleScope(sdl)
