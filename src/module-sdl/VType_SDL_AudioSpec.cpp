//==============================================================================
// VType_SDL_AudioSpec.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_AudioSpec#propSkeleton
Gurax_DeclareProperty_R(SDL_AudioSpec, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_AudioSpec, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_AudioSpec
//------------------------------------------------------------------------------
VType_SDL_AudioSpec VTYPE_SDL_AudioSpec("SDL_AudioSpec");

void VType_SDL_AudioSpec::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_AudioSpec, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_SDL_AudioSpec
//------------------------------------------------------------------------------
VType& Value_SDL_AudioSpec::vtype = VTYPE_SDL_AudioSpec;

String Value_SDL_AudioSpec::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_AudioSpec";
}

Gurax_EndModuleScope(sdl)
