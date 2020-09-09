//==============================================================================
// VType_SDL_DollarGestureEvent.cpp
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
// sdl.SDL_DollarGestureEvent#data1
Gurax_DeclareProperty_R(SDL_DollarGestureEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_DollarGestureEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().data1);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_SDL_DollarGestureEvent
//------------------------------------------------------------------------------
VType_SDL_DollarGestureEvent VTYPE_SDL_DollarGestureEvent("SDL_DollarGestureEvent");

void VType_SDL_DollarGestureEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_DollarGestureEvent, data1));
}

//------------------------------------------------------------------------------
// Value_SDL_DollarGestureEvent
//------------------------------------------------------------------------------
VType& Value_SDL_DollarGestureEvent::vtype = VTYPE_SDL_DollarGestureEvent;

String Value_SDL_DollarGestureEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_DollarGestureEvent";
}

Gurax_EndModuleScope(sdl)
