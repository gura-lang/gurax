//==============================================================================
// VType_SDL_SysWMEvent.cpp
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
// sdl.SDL_SysWMEvent#data1
Gurax_DeclareProperty_R(SDL_SysWMEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_SysWMEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().data1);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_SDL_SysWMEvent
//------------------------------------------------------------------------------
VType_SDL_SysWMEvent VTYPE_SDL_SysWMEvent("SDL_SysWMEvent");

void VType_SDL_SysWMEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_SDL_Event, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_SysWMEvent, data1));
}

//------------------------------------------------------------------------------
// Value_SDL_SysWMEvent
//------------------------------------------------------------------------------
VType& Value_SDL_SysWMEvent::vtype = VTYPE_SDL_SysWMEvent;

String Value_SDL_SysWMEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_SysWMEvent";
}

Gurax_EndModuleScope(sdl)
