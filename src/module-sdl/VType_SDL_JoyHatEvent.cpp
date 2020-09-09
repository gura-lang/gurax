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
// sdl.SDL_JoyHatEvent#data1
Gurax_DeclareProperty_R(SDL_JoyHatEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_JoyHatEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().data1);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_SDL_JoyHatEvent
//------------------------------------------------------------------------------
VType_SDL_JoyHatEvent VTYPE_SDL_JoyHatEvent("SDL_JoyHatEvent");

void VType_SDL_JoyHatEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_JoyHatEvent, data1));
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
