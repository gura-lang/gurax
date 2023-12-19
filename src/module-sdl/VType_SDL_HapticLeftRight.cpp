//==============================================================================
// VType_SDL_HapticLeftRight.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_HapticLeftRight, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_HapticLeftRight, `en)}

${help.ComposeMethodHelp(sdl.SDL_HapticLeftRight, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_HapticLeftRight#type
Gurax_DeclareProperty_R(SDL_HapticLeftRight, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticLeftRight, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_HapticLeftRight#direction
Gurax_DeclareProperty_R(SDL_HapticLeftRight, direction)
{
	Declare(VTYPE_SDL_HapticDirection, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticLeftRight, direction)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_HapticDirection(valueThis.GetValue_HapticEffect().Reference());
}

// sdl.SDL_HapticLeftRight#length
Gurax_DeclareProperty_R(SDL_HapticLeftRight, length)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticLeftRight, length)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().length);
}

// sdl.SDL_HapticLeftRight#large_magnitude
Gurax_DeclareProperty_R(SDL_HapticLeftRight, large_magnitude)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticLeftRight, large_magnitude)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().large_magnitude);
}

// sdl.SDL_HapticLeftRight#small_magnitude
Gurax_DeclareProperty_R(SDL_HapticLeftRight, small_magnitude)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticLeftRight, small_magnitude)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().small_magnitude);
}

//------------------------------------------------------------------------------
// VType_SDL_HapticLeftRight
//------------------------------------------------------------------------------
VType_SDL_HapticLeftRight VTYPE_SDL_HapticLeftRight("SDL_HapticLeftRight");

void VType_SDL_HapticLeftRight::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_HapticLeftRight, type));
	Assign(Gurax_CreateProperty(SDL_HapticLeftRight, direction));
	Assign(Gurax_CreateProperty(SDL_HapticLeftRight, length));
	Assign(Gurax_CreateProperty(SDL_HapticLeftRight, large_magnitude));
	Assign(Gurax_CreateProperty(SDL_HapticLeftRight, small_magnitude));
}

//------------------------------------------------------------------------------
// Value_SDL_HapticLeftRight
//------------------------------------------------------------------------------
VType& Value_SDL_HapticLeftRight::vtype = VTYPE_SDL_HapticLeftRight;

String Value_SDL_HapticLeftRight::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_HapticLeftRight");
}

Gurax_EndModuleScope(sdl)
