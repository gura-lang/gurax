//==============================================================================
// VType_SDL_MouseButtonEvent.cpp
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
// sdl.SDL_MouseButtonEvent#data1
Gurax_DeclareProperty_R(SDL_MouseButtonEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_MouseButtonEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().data1);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_SDL_MouseButtonEvent
//------------------------------------------------------------------------------
VType_SDL_MouseButtonEvent VTYPE_SDL_MouseButtonEvent("SDL_MouseButtonEvent");

void VType_SDL_MouseButtonEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_MouseButtonEvent, data1));
}

//------------------------------------------------------------------------------
// Value_SDL_MouseButtonEvent
//------------------------------------------------------------------------------
VType& Value_SDL_MouseButtonEvent::vtype = VTYPE_SDL_MouseButtonEvent;

String Value_SDL_MouseButtonEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_MouseButtonEvent";
}

Gurax_EndModuleScope(sdl)
