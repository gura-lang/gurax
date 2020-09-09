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
// sdl.SDL_JoyBallEvent#data1
Gurax_DeclareProperty_R(SDL_JoyBallEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_JoyBallEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().data1);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_SDL_JoyBallEvent
//------------------------------------------------------------------------------
VType_SDL_JoyBallEvent VTYPE_SDL_JoyBallEvent("SDL_JoyBallEvent");

void VType_SDL_JoyBallEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_JoyBallEvent, data1));
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
