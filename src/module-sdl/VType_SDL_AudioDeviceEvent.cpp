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
// sdl.SDL_AudioDeviceEvent#data1
Gurax_DeclareProperty_R(SDL_AudioDeviceEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_AudioDeviceEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().data1);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_SDL_AudioDeviceEvent
//------------------------------------------------------------------------------
VType_SDL_AudioDeviceEvent VTYPE_SDL_AudioDeviceEvent("SDL_AudioDeviceEvent");

void VType_SDL_AudioDeviceEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_AudioDeviceEvent, data1));
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
