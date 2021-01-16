//==============================================================================
// VType_SDL_HapticEffect.cpp
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
// sdl.SDL_HapticEffect#propSkeleton
Gurax_DeclareProperty_R(SDL_HapticEffect, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_HapticEffect, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_HapticEffect
//------------------------------------------------------------------------------
VType_SDL_HapticEffect VTYPE_SDL_HapticEffect("SDL_HapticEffect");

void VType_SDL_HapticEffect::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_HapticEffect, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_SDL_HapticEffect
//------------------------------------------------------------------------------
VType& Value_SDL_HapticEffect::vtype = VTYPE_SDL_HapticEffect;

String Value_SDL_HapticEffect::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_HapticEffect");
}

Gurax_EndModuleScope(sdl)
