//==============================================================================
// VType_SDL_WindowEvent.cpp
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
// sdl.SDL_WindowEvent#data1
Gurax_DeclareProperty_R(SDL_WindowEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_WindowEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().data1);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_SDL_WindowEvent
//------------------------------------------------------------------------------
VType_SDL_WindowEvent VTYPE_SDL_WindowEvent("SDL_WindowEvent");

void VType_SDL_WindowEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_WindowEvent, data1));
}

//------------------------------------------------------------------------------
// Value_SDL_WindowEvent
//------------------------------------------------------------------------------
VType& Value_SDL_WindowEvent::vtype = VTYPE_SDL_WindowEvent;

String Value_SDL_WindowEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_WindowEvent";
}

Gurax_EndModuleScope(sdl)
