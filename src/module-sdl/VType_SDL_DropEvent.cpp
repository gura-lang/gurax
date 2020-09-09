//==============================================================================
// VType_SDL_DropEvent.cpp
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
// sdl.SDL_DropEvent#data1
Gurax_DeclareProperty_R(SDL_DropEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_DropEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().data1);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_SDL_DropEvent
//------------------------------------------------------------------------------
VType_SDL_DropEvent VTYPE_SDL_DropEvent("SDL_DropEvent");

void VType_SDL_DropEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_DropEvent, data1));
}

//------------------------------------------------------------------------------
// Value_SDL_DropEvent
//------------------------------------------------------------------------------
VType& Value_SDL_DropEvent::vtype = VTYPE_SDL_DropEvent;

String Value_SDL_DropEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_DropEvent";
}

Gurax_EndModuleScope(sdl)
