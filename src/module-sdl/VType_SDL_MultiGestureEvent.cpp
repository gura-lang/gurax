//==============================================================================
// VType_SDL_MultiGestureEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_MultiGestureEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_MultiGestureEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_MultiGestureEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_MultiGestureEvent#type
Gurax_DeclareProperty_R(SDL_MultiGestureEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MultiGestureEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_MultiGestureEvent#timestamp
Gurax_DeclareProperty_R(SDL_MultiGestureEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MultiGestureEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_MultiGestureEvent#touchId
Gurax_DeclareProperty_R(SDL_MultiGestureEvent, touchId)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MultiGestureEvent, touchId)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().touchId);
}

// sdl.SDL_MultiGestureEvent#dTheta
Gurax_DeclareProperty_R(SDL_MultiGestureEvent, dTheta)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MultiGestureEvent, dTheta)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().dTheta);
}

// sdl.SDL_MultiGestureEvent#dDist
Gurax_DeclareProperty_R(SDL_MultiGestureEvent, dDist)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MultiGestureEvent, dDist)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().dDist);
}

// sdl.SDL_MultiGestureEvent#x
Gurax_DeclareProperty_R(SDL_MultiGestureEvent, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MultiGestureEvent, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().x);
}

// sdl.SDL_MultiGestureEvent#y
Gurax_DeclareProperty_R(SDL_MultiGestureEvent, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MultiGestureEvent, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().y);
}

// sdl.SDL_MultiGestureEvent#numFingers
Gurax_DeclareProperty_R(SDL_MultiGestureEvent, numFingers)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_MultiGestureEvent, numFingers)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().numFingers);
}

//------------------------------------------------------------------------------
// VType_SDL_MultiGestureEvent
//------------------------------------------------------------------------------
VType_SDL_MultiGestureEvent VTYPE_SDL_MultiGestureEvent("SDL_MultiGestureEvent");

void VType_SDL_MultiGestureEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_MultiGestureEvent, type));
	Assign(Gurax_CreateProperty(SDL_MultiGestureEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_MultiGestureEvent, touchId));
	Assign(Gurax_CreateProperty(SDL_MultiGestureEvent, dTheta));
	Assign(Gurax_CreateProperty(SDL_MultiGestureEvent, dDist));
	Assign(Gurax_CreateProperty(SDL_MultiGestureEvent, x));
	Assign(Gurax_CreateProperty(SDL_MultiGestureEvent, y));
	Assign(Gurax_CreateProperty(SDL_MultiGestureEvent, numFingers));
}

//------------------------------------------------------------------------------
// Value_SDL_MultiGestureEvent
//------------------------------------------------------------------------------
VType& Value_SDL_MultiGestureEvent::vtype = VTYPE_SDL_MultiGestureEvent;

String Value_SDL_MultiGestureEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_MultiGestureEvent");
}

Gurax_EndModuleScope(sdl)
