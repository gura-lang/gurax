//==============================================================================
// VType_SDL_AudioDeviceEvent.cpp
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
// sdl.SDL_AudioDeviceEvent#type
Gurax_DeclareProperty_R(SDL_AudioDeviceEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
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
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_AudioDeviceEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

#if 0
Uint32 which;       /**< The audio device index for the ADDED event (valid until next SDL_GetNumAudioDevices() call), SDL_AudioDeviceID for the REMOVED event */
Uint8 iscapture;    /**< zero if an output device, non-zero if a capture device. */
Uint8 padding1;
Uint8 padding2;
Uint8 padding3;
#endif

//------------------------------------------------------------------------------
// VType_SDL_AudioDeviceEvent
//------------------------------------------------------------------------------
VType_SDL_AudioDeviceEvent VTYPE_SDL_AudioDeviceEvent("SDL_AudioDeviceEvent");

void VType_SDL_AudioDeviceEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_AudioDeviceEvent, type));
	Assign(Gurax_CreateProperty(SDL_AudioDeviceEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_AudioDeviceEvent
//------------------------------------------------------------------------------
VType& Value_SDL_AudioDeviceEvent::vtype = VTYPE_SDL_AudioDeviceEvent;

String Value_SDL_AudioDeviceEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_AudioDeviceEvent";
}

Gurax_EndModuleScope(sdl)
