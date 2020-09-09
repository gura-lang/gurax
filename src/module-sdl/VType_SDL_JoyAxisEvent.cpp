//==============================================================================
// VType_SDL_JoyAxisEvent.cpp
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
// sdl.SDL_JoyAxisEvent#data1
Gurax_DeclareProperty_R(SDL_JoyAxisEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_JoyAxisEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().data1);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_SDL_JoyAxisEvent
//------------------------------------------------------------------------------
VType_SDL_JoyAxisEvent VTYPE_SDL_JoyAxisEvent("SDL_JoyAxisEvent");

void VType_SDL_JoyAxisEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_JoyAxisEvent, data1));
}

//------------------------------------------------------------------------------
// Value_SDL_JoyAxisEvent
//------------------------------------------------------------------------------
VType& Value_SDL_JoyAxisEvent::vtype = VTYPE_SDL_JoyAxisEvent;

String Value_SDL_JoyAxisEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_JoyAxisEvent";
}

Gurax_EndModuleScope(sdl)
