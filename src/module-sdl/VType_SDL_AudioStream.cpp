//==============================================================================
// VType_SDL_AudioStream.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_AudioStream, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_AudioStream, `en)}

${help.ComposeMethodHelp(sdl.SDL_AudioStream, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_AudioStream#propSkeleton
Gurax_DeclareProperty_R(SDL_AudioStream, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_AudioStream, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_AudioStream
//------------------------------------------------------------------------------
VType_SDL_AudioStream VTYPE_SDL_AudioStream("SDL_AudioStream");

void VType_SDL_AudioStream::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_AudioStream, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_SDL_AudioStream
//------------------------------------------------------------------------------
VType& Value_SDL_AudioStream::vtype = VTYPE_SDL_AudioStream;

String Value_SDL_AudioStream::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_AudioStream");
}

Gurax_EndModuleScope(sdl)
