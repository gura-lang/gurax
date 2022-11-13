//==============================================================================
// VType_SDL_Haptic.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_Haptic, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_Haptic, `en)}

${help.ComposeMethodHelp(sdl.SDL_Haptic, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_Haptic#propSkeleton
Gurax_DeclareProperty_R(SDL_Haptic, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Haptic, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_Haptic
//------------------------------------------------------------------------------
VType_SDL_Haptic VTYPE_SDL_Haptic("SDL_Haptic");

void VType_SDL_Haptic::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_Haptic, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_SDL_Haptic
//------------------------------------------------------------------------------
VType& Value_SDL_Haptic::vtype = VTYPE_SDL_Haptic;

String Value_SDL_Haptic::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_Haptic");
}

Gurax_EndModuleScope(sdl)
