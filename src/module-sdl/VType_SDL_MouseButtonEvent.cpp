//==============================================================================
// VType_SDL_MouseButtonEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_MouseButtonEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_MouseButtonEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_MouseButtonEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_MouseButtonEvent#type
Gurax_DeclareProperty_R(SDL_MouseButtonEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseButtonEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_MouseButtonEvent#timestamp
Gurax_DeclareProperty_R(SDL_MouseButtonEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseButtonEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_MouseButtonEvent#windowID
Gurax_DeclareProperty_R(SDL_MouseButtonEvent, windowID)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseButtonEvent, windowID)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().windowID);
}

// sdl.SDL_MouseButtonEvent#which
Gurax_DeclareProperty_R(SDL_MouseButtonEvent, which)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseButtonEvent, which)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().which);
}

// sdl.SDL_MouseButtonEvent#button
Gurax_DeclareProperty_R(SDL_MouseButtonEvent, button)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseButtonEvent, button)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().button);
}

// sdl.SDL_MouseButtonEvent#state
Gurax_DeclareProperty_R(SDL_MouseButtonEvent, state)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseButtonEvent, state)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().state);
}

// sdl.SDL_MouseButtonEvent#clicks
Gurax_DeclareProperty_R(SDL_MouseButtonEvent, clicks)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseButtonEvent, clicks)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().clicks);
}

// sdl.SDL_MouseButtonEvent#padding1
Gurax_DeclareProperty_R(SDL_MouseButtonEvent, padding1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseButtonEvent, padding1)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().padding1);
}

// sdl.SDL_MouseButtonEvent#x
Gurax_DeclareProperty_R(SDL_MouseButtonEvent, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseButtonEvent, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().x);
}

// sdl.SDL_MouseButtonEvent#y
Gurax_DeclareProperty_R(SDL_MouseButtonEvent, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseButtonEvent, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().y);
}

//------------------------------------------------------------------------------
// VType_SDL_MouseButtonEvent
//------------------------------------------------------------------------------
VType_SDL_MouseButtonEvent VTYPE_SDL_MouseButtonEvent("SDL_MouseButtonEvent");

void VType_SDL_MouseButtonEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_MouseButtonEvent, type));
	Assign(Gurax_CreateProperty(SDL_MouseButtonEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_MouseButtonEvent, windowID));
	Assign(Gurax_CreateProperty(SDL_MouseButtonEvent, which));
	Assign(Gurax_CreateProperty(SDL_MouseButtonEvent, button));
	Assign(Gurax_CreateProperty(SDL_MouseButtonEvent, state));
	Assign(Gurax_CreateProperty(SDL_MouseButtonEvent, clicks));
	Assign(Gurax_CreateProperty(SDL_MouseButtonEvent, x));
	Assign(Gurax_CreateProperty(SDL_MouseButtonEvent, y));
}

//------------------------------------------------------------------------------
// Value_SDL_MouseButtonEvent
//------------------------------------------------------------------------------
VType& Value_SDL_MouseButtonEvent::vtype = VTYPE_SDL_MouseButtonEvent;

String Value_SDL_MouseButtonEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_MouseButtonEvent");
}

Gurax_EndModuleScope(sdl)
