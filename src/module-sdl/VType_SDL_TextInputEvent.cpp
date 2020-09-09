//==============================================================================
// VType_SDL_TextInputEvent.cpp
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
// sdl.SDL_TextInputEvent#data1
Gurax_DeclareProperty_R(SDL_TextInputEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_TextInputEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().data1);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_SDL_TextInputEvent
//------------------------------------------------------------------------------
VType_SDL_TextInputEvent VTYPE_SDL_TextInputEvent("SDL_TextInputEvent");

void VType_SDL_TextInputEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_TextInputEvent, data1));
}

//------------------------------------------------------------------------------
// Value_SDL_TextInputEvent
//------------------------------------------------------------------------------
VType& Value_SDL_TextInputEvent::vtype = VTYPE_SDL_TextInputEvent;

String Value_SDL_TextInputEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_TextInputEvent";
}

Gurax_EndModuleScope(sdl)
