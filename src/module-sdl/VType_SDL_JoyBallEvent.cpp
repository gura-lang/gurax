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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_JoyBallEvent#type
Gurax_DeclareProperty_R(SDL_JoyBallEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
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
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_JoyBallEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

#if 0
SDL_JoystickID which; /**< The joystick instance id */
Uint8 ball;         /**< The joystick trackball index */
Uint8 padding1;
Uint8 padding2;
Uint8 padding3;
Sint16 xrel;        /**< The relative motion in the X direction */
Sint16 yrel;        /**< The relative motion in the Y direction */
#endif

//------------------------------------------------------------------------------
// VType_SDL_JoyBallEvent
//------------------------------------------------------------------------------
VType_SDL_JoyBallEvent VTYPE_SDL_JoyBallEvent("SDL_JoyBallEvent");

void VType_SDL_JoyBallEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_JoyBallEvent, type));
	Assign(Gurax_CreateProperty(SDL_JoyBallEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_JoyBallEvent
//------------------------------------------------------------------------------
VType& Value_SDL_JoyBallEvent::vtype = VTYPE_SDL_JoyBallEvent;

String Value_SDL_JoyBallEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_JoyBallEvent";
}

Gurax_EndModuleScope(sdl)
