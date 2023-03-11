//==============================================================================
// VType_SDL_JoyAxisEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_JoyAxisEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_JoyAxisEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_JoyAxisEvent, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_JoyAxisEvent#type
Gurax_DeclareProperty_R(SDL_JoyAxisEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_JoyAxisEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_JoyAxisEvent#timestamp
Gurax_DeclareProperty_R(SDL_JoyAxisEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_JoyAxisEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_JoyAxisEvent#which
Gurax_DeclareProperty_R(SDL_JoyAxisEvent, which)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_JoyAxisEvent, which)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

// sdl.SDL_JoyAxisEvent#axis
Gurax_DeclareProperty_R(SDL_JoyAxisEvent, axis)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_JoyAxisEvent, axis)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

// sdl.SDL_JoyAxisEvent#value
Gurax_DeclareProperty_R(SDL_JoyAxisEvent, value)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_JoyAxisEvent, value)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_JoyAxisEvent
//------------------------------------------------------------------------------
VType_SDL_JoyAxisEvent VTYPE_SDL_JoyAxisEvent("SDL_JoyAxisEvent");

void VType_SDL_JoyAxisEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_JoyAxisEvent, type));
	Assign(Gurax_CreateProperty(SDL_JoyAxisEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_JoyAxisEvent, which));
	Assign(Gurax_CreateProperty(SDL_JoyAxisEvent, axis));
	Assign(Gurax_CreateProperty(SDL_JoyAxisEvent, value));
}

//------------------------------------------------------------------------------
// Value_SDL_JoyAxisEvent
//------------------------------------------------------------------------------
VType& Value_SDL_JoyAxisEvent::vtype = VTYPE_SDL_JoyAxisEvent;

String Value_SDL_JoyAxisEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_JoyAxisEvent");
}

Gurax_EndModuleScope(sdl)
