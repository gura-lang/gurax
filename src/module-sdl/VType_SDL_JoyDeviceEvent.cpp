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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_JoyDeviceEvent#data1
Gurax_DeclareProperty_R(SDL_JoyDeviceEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_JoyDeviceEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().data1);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_SDL_JoyDeviceEvent
//------------------------------------------------------------------------------
VType_SDL_JoyDeviceEvent VTYPE_SDL_JoyDeviceEvent("SDL_JoyDeviceEvent");

void VType_SDL_JoyDeviceEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_JoyDeviceEvent, data1));
}

//------------------------------------------------------------------------------
// Value_SDL_JoyDeviceEvent
//------------------------------------------------------------------------------
VType& Value_SDL_JoyDeviceEvent::vtype = VTYPE_SDL_JoyDeviceEvent;

String Value_SDL_JoyDeviceEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_JoyDeviceEvent";
}

Gurax_EndModuleScope(sdl)
