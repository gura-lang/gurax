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
// sdl.SDL_ControllerDeviceEvent#data1
Gurax_DeclareProperty_R(SDL_ControllerDeviceEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_ControllerDeviceEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().data1);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_SDL_ControllerDeviceEvent
//------------------------------------------------------------------------------
VType_SDL_ControllerDeviceEvent VTYPE_SDL_ControllerDeviceEvent("SDL_ControllerDeviceEvent");

void VType_SDL_ControllerDeviceEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_ControllerDeviceEvent, data1));
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
