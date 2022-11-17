//==============================================================================
// VType_SDL_MouseMotionEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_MouseMotionEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_MouseMotionEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_MouseMotionEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_MouseMotionEvent#type
Gurax_DeclareProperty_R(SDL_MouseMotionEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseMotionEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_MouseMotionEvent#timestamp
Gurax_DeclareProperty_R(SDL_MouseMotionEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseMotionEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_MouseMotionEvent#windowID
Gurax_DeclareProperty_R(SDL_MouseMotionEvent, windowID)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseMotionEvent, windowID)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().windowID);
}

// sdl.SDL_MouseMotionEvent#which
Gurax_DeclareProperty_R(SDL_MouseMotionEvent, which)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseMotionEvent, which)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().which);
}

// sdl.SDL_MouseMotionEvent#state
Gurax_DeclareProperty_R(SDL_MouseMotionEvent, state)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseMotionEvent, state)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().state);
}

// sdl.SDL_MouseMotionEvent#x
Gurax_DeclareProperty_R(SDL_MouseMotionEvent, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseMotionEvent, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().x);
}

// sdl.SDL_MouseMotionEvent#y
Gurax_DeclareProperty_R(SDL_MouseMotionEvent, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseMotionEvent, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().y);
}

// sdl.SDL_MouseMotionEvent#xrel
Gurax_DeclareProperty_R(SDL_MouseMotionEvent, xrel)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseMotionEvent, xrel)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().xrel);
}

// sdl.SDL_MouseMotionEvent#yrel
Gurax_DeclareProperty_R(SDL_MouseMotionEvent, yrel)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MouseMotionEvent, yrel)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().yrel);
}

//------------------------------------------------------------------------------
// VType_SDL_MouseMotionEvent
//------------------------------------------------------------------------------
VType_SDL_MouseMotionEvent VTYPE_SDL_MouseMotionEvent("SDL_MouseMotionEvent");

void VType_SDL_MouseMotionEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_MouseMotionEvent, type));
	Assign(Gurax_CreateProperty(SDL_MouseMotionEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_MouseMotionEvent, windowID));
	Assign(Gurax_CreateProperty(SDL_MouseMotionEvent, which));
	Assign(Gurax_CreateProperty(SDL_MouseMotionEvent, state));
	Assign(Gurax_CreateProperty(SDL_MouseMotionEvent, x));
	Assign(Gurax_CreateProperty(SDL_MouseMotionEvent, y));
	Assign(Gurax_CreateProperty(SDL_MouseMotionEvent, xrel));
	Assign(Gurax_CreateProperty(SDL_MouseMotionEvent, yrel));
}

//------------------------------------------------------------------------------
// Value_SDL_MouseMotionEvent
//------------------------------------------------------------------------------
VType& Value_SDL_MouseMotionEvent::vtype = VTYPE_SDL_MouseMotionEvent;

String Value_SDL_MouseMotionEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_MouseMotionEvent");
}

Gurax_EndModuleScope(sdl)
