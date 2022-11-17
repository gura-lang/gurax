//==============================================================================
// VType_SDL_CommonEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_CommonEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_CommonEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_CommonEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_CommonEvent#type
Gurax_DeclareProperty_R(SDL_CommonEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_CommonEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_CommonEvent#timestamp
Gurax_DeclareProperty_R(SDL_CommonEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_CommonEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

//------------------------------------------------------------------------------
// VType_SDL_CommonEvent
//------------------------------------------------------------------------------
VType_SDL_CommonEvent VTYPE_SDL_CommonEvent("SDL_CommonEvent");

void VType_SDL_CommonEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_CommonEvent, type));
	Assign(Gurax_CreateProperty(SDL_CommonEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_CommonEvent
//------------------------------------------------------------------------------
VType& Value_SDL_CommonEvent::vtype = VTYPE_SDL_CommonEvent;

String Value_SDL_CommonEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_CommonEvent");
}

Gurax_EndModuleScope(sdl)
