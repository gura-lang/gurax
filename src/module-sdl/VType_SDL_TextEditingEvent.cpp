//==============================================================================
// VType_SDL_TextEditingEvent.cpp
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
// sdl.SDL_TextEditingEvent#data1
Gurax_DeclareProperty_R(SDL_TextEditingEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_TextEditingEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().data1);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_SDL_TextEditingEvent
//------------------------------------------------------------------------------
VType_SDL_TextEditingEvent VTYPE_SDL_TextEditingEvent("SDL_TextEditingEvent");

void VType_SDL_TextEditingEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_TextEditingEvent, data1));
}

//------------------------------------------------------------------------------
// Value_SDL_TextEditingEvent
//------------------------------------------------------------------------------
VType& Value_SDL_TextEditingEvent::vtype = VTYPE_SDL_TextEditingEvent;

String Value_SDL_TextEditingEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_TextEditingEvent";
}

Gurax_EndModuleScope(sdl)
