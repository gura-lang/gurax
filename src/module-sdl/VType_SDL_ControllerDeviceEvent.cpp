//==============================================================================
// VType_SDL_ControllerDeviceEvent.cpp
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
// sdl.SDL_ControllerDeviceEvent#type
Gurax_DeclareProperty_R(SDL_ControllerDeviceEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
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
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_ControllerDeviceEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

#if 0
Sint32 which;       /**< The joystick device index for the ADDED event, instance id for the REMOVED or REMAPPED event */
#endif

//------------------------------------------------------------------------------
// VType_SDL_ControllerDeviceEvent
//------------------------------------------------------------------------------
VType_SDL_ControllerDeviceEvent VTYPE_SDL_ControllerDeviceEvent("SDL_ControllerDeviceEvent");

void VType_SDL_ControllerDeviceEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_ControllerDeviceEvent, type));
	Assign(Gurax_CreateProperty(SDL_ControllerDeviceEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_ControllerDeviceEvent
//------------------------------------------------------------------------------
VType& Value_SDL_ControllerDeviceEvent::vtype = VTYPE_SDL_ControllerDeviceEvent;

String Value_SDL_ControllerDeviceEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_ControllerDeviceEvent";
}

Gurax_EndModuleScope(sdl)
