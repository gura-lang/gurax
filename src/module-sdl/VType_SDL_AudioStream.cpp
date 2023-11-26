//==============================================================================
// VType_SDL_AudioStream.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_AudioStream, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_AudioStream, `en)}

${help.ComposeMethodHelp(sdl.SDL_AudioStream, `en)}
)""";

//------------------------------------------------------------------------------
// VType_SDL_AudioStream
//------------------------------------------------------------------------------
VType_SDL_AudioStream VTYPE_SDL_AudioStream("SDL_AudioStream");

void VType_SDL_AudioStream::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
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
