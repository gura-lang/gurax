//==============================================================================
// VType_SDL_HapticDirection.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_HapticDirection, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_HapticDirection, `en)}

${help.ComposeMethodHelp(sdl.SDL_HapticDirection, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_HapticDirection#type
Gurax_DeclareProperty_R(SDL_HapticDirection, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticDirection, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

//------------------------------------------------------------------------------
// VType_SDL_HapticDirection
//------------------------------------------------------------------------------
VType_SDL_HapticDirection VTYPE_SDL_HapticDirection("SDL_HapticDirection");

void VType_SDL_HapticDirection::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_HapticDirection, type));
}

//------------------------------------------------------------------------------
// Value_SDL_HapticDirection
//------------------------------------------------------------------------------
VType& Value_SDL_HapticDirection::vtype = VTYPE_SDL_HapticDirection;

String Value_SDL_HapticDirection::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_HapticDirection");
}

Gurax_EndModuleScope(sdl)
