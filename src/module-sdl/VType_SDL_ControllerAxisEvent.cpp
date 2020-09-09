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
// sdl.SDL_ControllerAxisEvent#data1
Gurax_DeclareProperty_R(SDL_ControllerAxisEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_ControllerAxisEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().data1);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_SDL_ControllerAxisEvent
//------------------------------------------------------------------------------
VType_SDL_ControllerAxisEvent VTYPE_SDL_ControllerAxisEvent("SDL_ControllerAxisEvent");

void VType_SDL_ControllerAxisEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_ControllerAxisEvent, data1));
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
