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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_JoyHatEvent#type
Gurax_DeclareProperty_R(SDL_JoyHatEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
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
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_JoyHatEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

#if 0
SDL_JoystickID which; /**< The joystick instance id */
Uint8 hat;          /**< The joystick hat index */
Uint8 value;        /**< The hat position value.
						*   \sa ::SDL_HAT_LEFTUP ::SDL_HAT_UP ::SDL_HAT_RIGHTUP
						*   \sa ::SDL_HAT_LEFT ::SDL_HAT_CENTERED ::SDL_HAT_RIGHT
						*   \sa ::SDL_HAT_LEFTDOWN ::SDL_HAT_DOWN ::SDL_HAT_RIGHTDOWN
						*
						*   Note that zero means the POV is centered.
						*/
Uint8 padding1;
Uint8 padding2;
#endif

//------------------------------------------------------------------------------
// VType_SDL_JoyHatEvent
//------------------------------------------------------------------------------
VType_SDL_JoyHatEvent VTYPE_SDL_JoyHatEvent("SDL_JoyHatEvent");

void VType_SDL_JoyHatEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_JoyHatEvent, type));
	Assign(Gurax_CreateProperty(SDL_JoyHatEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_JoyHatEvent
//------------------------------------------------------------------------------
VType& Value_SDL_JoyHatEvent::vtype = VTYPE_SDL_JoyHatEvent;

String Value_SDL_JoyHatEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_JoyHatEvent";
}

Gurax_EndModuleScope(sdl)
