//==============================================================================
// VType_SDL_ControllerButtonEvent.cpp
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
// sdl.SDL_ControllerButtonEvent#type
Gurax_DeclareProperty_R(SDL_ControllerButtonEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
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
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_ControllerButtonEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

#if 0
SDL_JoystickID which; /**< The joystick instance id */
Uint8 button;       /**< The controller button (SDL_GameControllerButton) */
Uint8 state;        /**< ::SDL_PRESSED or ::SDL_RELEASED */
Uint8 padding1;
Uint8 padding2;
#endif

//------------------------------------------------------------------------------
// VType_SDL_ControllerButtonEvent
//------------------------------------------------------------------------------
VType_SDL_ControllerButtonEvent VTYPE_SDL_ControllerButtonEvent("SDL_ControllerButtonEvent");

void VType_SDL_ControllerButtonEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_ControllerButtonEvent, type));
	Assign(Gurax_CreateProperty(SDL_ControllerButtonEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_ControllerButtonEvent
//------------------------------------------------------------------------------
VType& Value_SDL_ControllerButtonEvent::vtype = VTYPE_SDL_ControllerButtonEvent;

String Value_SDL_ControllerButtonEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_ControllerButtonEvent";
}

Gurax_EndModuleScope(sdl)
