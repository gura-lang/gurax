//==============================================================================
// VType_SDL_JoyAxisEvent.cpp
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
// sdl.SDL_JoyAxisEvent#type
Gurax_DeclareProperty_R(SDL_JoyAxisEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_JoyAxisEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_JoyAxisEvent#timestamp
Gurax_DeclareProperty_R(SDL_JoyAxisEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_JoyAxisEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

#if 0
SDL_JoystickID which; /**< The joystick instance id */
Uint8 axis;         /**< The joystick axis index */
Uint8 padding1;
Uint8 padding2;
Uint8 padding3;
Sint16 value;       /**< The axis value (range: -32768 to 32767) */
Uint16 padding4;
#endif

//------------------------------------------------------------------------------
// VType_SDL_JoyAxisEvent
//------------------------------------------------------------------------------
VType_SDL_JoyAxisEvent VTYPE_SDL_JoyAxisEvent("SDL_JoyAxisEvent");

void VType_SDL_JoyAxisEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_JoyAxisEvent, type));
	Assign(Gurax_CreateProperty(SDL_JoyAxisEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_JoyAxisEvent
//------------------------------------------------------------------------------
VType& Value_SDL_JoyAxisEvent::vtype = VTYPE_SDL_JoyAxisEvent;

String Value_SDL_JoyAxisEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_JoyAxisEvent";
}

Gurax_EndModuleScope(sdl)
