//==============================================================================
// VType_SDL_AudioCVT.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_AudioCVT, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_AudioCVT, `en)}

${help.ComposeMethodHelp(sdl.SDL_AudioCVT, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_AudioCVT#propSkeleton
Gurax_DeclareProperty_R(SDL_AudioCVT, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_AudioCVT, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_AudioCVT
//------------------------------------------------------------------------------
VType_SDL_AudioCVT VTYPE_SDL_AudioCVT("SDL_AudioCVT");

void VType_SDL_AudioCVT::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_AudioCVT, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_SDL_AudioCVT
//------------------------------------------------------------------------------
VType& Value_SDL_AudioCVT::vtype = VTYPE_SDL_AudioCVT;

String Value_SDL_AudioCVT::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_AudioCVT");
}

Gurax_EndModuleScope(sdl)
