//==============================================================================
// VType_SDL_MouseWheelEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_MouseWheelEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_MouseWheelEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_MouseWheelEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_MouseWheelEvent#type
Gurax_DeclareProperty_R(SDL_MouseWheelEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseWheelEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_MouseWheelEvent#timestamp
Gurax_DeclareProperty_R(SDL_MouseWheelEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseWheelEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_MouseWheelEvent#windowID
Gurax_DeclareProperty_R(SDL_MouseWheelEvent, windowID)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseWheelEvent, windowID)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().windowID);
}

// sdl.SDL_MouseWheelEvent#which
Gurax_DeclareProperty_R(SDL_MouseWheelEvent, which)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseWheelEvent, which)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().which);
}

// sdl.SDL_MouseWheelEvent#x
Gurax_DeclareProperty_R(SDL_MouseWheelEvent, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseWheelEvent, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().x);
}

// sdl.SDL_MouseWheelEvent#y
Gurax_DeclareProperty_R(SDL_MouseWheelEvent, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseWheelEvent, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().y);
}

// sdl.SDL_MouseWheelEvent#direction
Gurax_DeclareProperty_R(SDL_MouseWheelEvent, direction)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseWheelEvent, direction)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().direction);
}

//------------------------------------------------------------------------------
// VType_SDL_MouseWheelEvent
//------------------------------------------------------------------------------
VType_SDL_MouseWheelEvent VTYPE_SDL_MouseWheelEvent("SDL_MouseWheelEvent");

void VType_SDL_MouseWheelEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_MouseWheelEvent, type));
	Assign(Gurax_CreateProperty(SDL_MouseWheelEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_MouseWheelEvent, windowID));
	Assign(Gurax_CreateProperty(SDL_MouseWheelEvent, which));
	Assign(Gurax_CreateProperty(SDL_MouseWheelEvent, x));
	Assign(Gurax_CreateProperty(SDL_MouseWheelEvent, y));
	Assign(Gurax_CreateProperty(SDL_MouseWheelEvent, direction));
}

//------------------------------------------------------------------------------
// Value_SDL_MouseWheelEvent
//------------------------------------------------------------------------------
VType& Value_SDL_MouseWheelEvent::vtype = VTYPE_SDL_MouseWheelEvent;

String Value_SDL_MouseWheelEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_MouseWheelEvent");
}

Gurax_EndModuleScope(sdl)
