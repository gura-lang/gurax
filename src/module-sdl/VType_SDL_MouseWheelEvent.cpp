//==============================================================================
// VType_SDL_MouseWheelEvent.cpp
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
// sdl.SDL_MouseWheelEvent#data1
Gurax_DeclareProperty_R(SDL_MouseWheelEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_MouseWheelEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().data1);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_SDL_MouseWheelEvent
//------------------------------------------------------------------------------
VType_SDL_MouseWheelEvent VTYPE_SDL_MouseWheelEvent("SDL_MouseWheelEvent");

void VType_SDL_MouseWheelEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_MouseWheelEvent, data1));
}

//------------------------------------------------------------------------------
// Value_SDL_MouseWheelEvent
//------------------------------------------------------------------------------
VType& Value_SDL_MouseWheelEvent::vtype = VTYPE_SDL_MouseWheelEvent;

String Value_SDL_MouseWheelEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_MouseWheelEvent";
}

Gurax_EndModuleScope(sdl)
