//==============================================================================
// VType_SDL_TouchFingerEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_TouchFingerEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_TouchFingerEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_TouchFingerEvent, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_TouchFingerEvent#type
Gurax_DeclareProperty_R(SDL_TouchFingerEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_TouchFingerEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_TouchFingerEvent#timestamp
Gurax_DeclareProperty_R(SDL_TouchFingerEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_TouchFingerEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_TouchFingerEvent#touchId
Gurax_DeclareProperty_R(SDL_TouchFingerEvent, touchId)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_TouchFingerEvent, touchId)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().touchId);
}

// sdl.SDL_TouchFingerEvent#fingerId
Gurax_DeclareProperty_R(SDL_TouchFingerEvent, fingerId)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_TouchFingerEvent, fingerId)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().fingerId);
}

// sdl.SDL_TouchFingerEvent#x
Gurax_DeclareProperty_R(SDL_TouchFingerEvent, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_TouchFingerEvent, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().x);
}

// sdl.SDL_TouchFingerEvent#y
Gurax_DeclareProperty_R(SDL_TouchFingerEvent, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_TouchFingerEvent, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().y);
}

// sdl.SDL_TouchFingerEvent#dx
Gurax_DeclareProperty_R(SDL_TouchFingerEvent, dx)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_TouchFingerEvent, dx)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().dx);
}

// sdl.SDL_TouchFingerEvent#dy
Gurax_DeclareProperty_R(SDL_TouchFingerEvent, dy)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_TouchFingerEvent, dy)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().dy);
}

// sdl.SDL_TouchFingerEvent#pressure
Gurax_DeclareProperty_R(SDL_TouchFingerEvent, pressure)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_TouchFingerEvent, pressure)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().pressure);
}

// sdl.SDL_TouchFingerEvent#windowID
Gurax_DeclareProperty_R(SDL_TouchFingerEvent, windowID)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_TouchFingerEvent, windowID)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().windowID);
}

//------------------------------------------------------------------------------
// VType_SDL_TouchFingerEvent
//------------------------------------------------------------------------------
VType_SDL_TouchFingerEvent VTYPE_SDL_TouchFingerEvent("SDL_TouchFingerEvent");

void VType_SDL_TouchFingerEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_TouchFingerEvent, type));
	Assign(Gurax_CreateProperty(SDL_TouchFingerEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_TouchFingerEvent, touchId));
	Assign(Gurax_CreateProperty(SDL_TouchFingerEvent, fingerId));
	Assign(Gurax_CreateProperty(SDL_TouchFingerEvent, x));
	Assign(Gurax_CreateProperty(SDL_TouchFingerEvent, y));
	Assign(Gurax_CreateProperty(SDL_TouchFingerEvent, dx));
	Assign(Gurax_CreateProperty(SDL_TouchFingerEvent, dy));
	Assign(Gurax_CreateProperty(SDL_TouchFingerEvent, pressure));
	Assign(Gurax_CreateProperty(SDL_TouchFingerEvent, windowID));
}

//------------------------------------------------------------------------------
// Value_SDL_TouchFingerEvent
//------------------------------------------------------------------------------
VType& Value_SDL_TouchFingerEvent::vtype = VTYPE_SDL_TouchFingerEvent;

String Value_SDL_TouchFingerEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_TouchFingerEvent");
}

Gurax_EndModuleScope(sdl)
