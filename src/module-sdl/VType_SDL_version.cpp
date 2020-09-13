//==============================================================================
// VType_SDL_version.cpp
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
// sdl.SDL_version#propSkeleton
Gurax_DeclareProperty_R(SDL_version, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_version, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_version
//------------------------------------------------------------------------------
VType_SDL_version VTYPE_SDL_version("SDL_version");

void VType_SDL_version::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_version, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_SDL_version
//------------------------------------------------------------------------------
VType& Value_SDL_version::vtype = VTYPE_SDL_version;

String Value_SDL_version::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_version";
}

Gurax_EndModuleScope(sdl)
