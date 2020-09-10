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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_ControllerAxisEvent#type
Gurax_DeclareProperty_R(SDL_ControllerAxisEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
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
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_ControllerAxisEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

#if 0
SDL_JoystickID which; /**< The joystick instance id */
Uint8 axis;         /**< The controller axis (SDL_GameControllerAxis) */
Uint8 padding1;
Uint8 padding2;
Uint8 padding3;
Sint16 value;       /**< The axis value (range: -32768 to 32767) */
Uint16 padding4;
#endif

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
}

//------------------------------------------------------------------------------
// Value_SDL_ControllerAxisEvent
//------------------------------------------------------------------------------
VType& Value_SDL_ControllerAxisEvent::vtype = VTYPE_SDL_ControllerAxisEvent;

String Value_SDL_ControllerAxisEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_ControllerAxisEvent";
}

Gurax_EndModuleScope(sdl)
