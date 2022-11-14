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

${help.ComposePropertyHelp(sdl.SDL_SysWMEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_SysWMEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_SysWMEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_SysWMEvent#type
Gurax_DeclareProperty_R(SDL_SysWMEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_SysWMEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_SysWMEvent#timestamp
Gurax_DeclareProperty_R(SDL_SysWMEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_SysWMEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

//------------------------------------------------------------------------------
// VType_SDL_SysWMEvent
//------------------------------------------------------------------------------
VType_SDL_SysWMEvent VTYPE_SDL_SysWMEvent("SDL_SysWMEvent");

void VType_SDL_SysWMEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_SysWMEvent, type));
	Assign(Gurax_CreateProperty(SDL_SysWMEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_SysWMEvent
//------------------------------------------------------------------------------
VType& Value_SDL_SysWMEvent::vtype = VTYPE_SDL_SysWMEvent;

String Value_SDL_SysWMEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_SysWMEvent");
}

Gurax_EndModuleScope(sdl)
