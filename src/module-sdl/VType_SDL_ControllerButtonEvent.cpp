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
// sdl.SDL_ControllerButtonEvent#data1
Gurax_DeclareProperty_R(SDL_ControllerButtonEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_ControllerButtonEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().data1);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_SDL_ControllerButtonEvent
//------------------------------------------------------------------------------
VType_SDL_ControllerButtonEvent VTYPE_SDL_ControllerButtonEvent("SDL_ControllerButtonEvent");

void VType_SDL_ControllerButtonEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_ControllerButtonEvent, data1));
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
