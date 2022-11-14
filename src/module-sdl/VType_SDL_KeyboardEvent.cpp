//==============================================================================
// VType_SDL_KeyboardEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_KeyboardEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_KeyboardEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_KeyboardEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_KeyboardEvent#type
Gurax_DeclareProperty_R(SDL_KeyboardEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_KeyboardEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_KeyboardEvent#timestamp
Gurax_DeclareProperty_R(SDL_KeyboardEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_KeyboardEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_KeyboardEvent#windowID
Gurax_DeclareProperty_R(SDL_KeyboardEvent, windowID)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_KeyboardEvent, windowID)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().windowID);
}

// sdl.SDL_KeyboardEvent#state
Gurax_DeclareProperty_R(SDL_KeyboardEvent, state)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_KeyboardEvent, state)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().state);
}

// sdl.SDL_KeyboardEvent#repeat
Gurax_DeclareProperty_R(SDL_KeyboardEvent, repeat)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_KeyboardEvent, repeat)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().repeat);
}

// sdl.SDL_KeyboardEvent#keysym
Gurax_DeclareProperty_R(SDL_KeyboardEvent, keysym)
{
	Declare(VTYPE_SDL_Keysym, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_KeyboardEvent, keysym)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_Keysym(valueThis.GetEntity().keysym);
}

//------------------------------------------------------------------------------
// VType_SDL_KeyboardEvent
//------------------------------------------------------------------------------
VType_SDL_KeyboardEvent VTYPE_SDL_KeyboardEvent("SDL_KeyboardEvent");

void VType_SDL_KeyboardEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_KeyboardEvent, type));
	Assign(Gurax_CreateProperty(SDL_KeyboardEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_KeyboardEvent, windowID));
	Assign(Gurax_CreateProperty(SDL_KeyboardEvent, state));
	Assign(Gurax_CreateProperty(SDL_KeyboardEvent, repeat));
	Assign(Gurax_CreateProperty(SDL_KeyboardEvent, keysym));
}

//------------------------------------------------------------------------------
// Value_SDL_KeyboardEvent
//------------------------------------------------------------------------------
VType& Value_SDL_KeyboardEvent::vtype = VTYPE_SDL_KeyboardEvent;

String Value_SDL_KeyboardEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_KeyboardEvent");
}

Gurax_EndModuleScope(sdl)
