//==============================================================================
// VType_SDL_Texture.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_Texture, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_Texture, `en)}

${help.ComposeMethodHelp(sdl.SDL_Texture, `en)}
)""";

//------------------------------------------------------------------------------
// VType_SDL_Texture
//------------------------------------------------------------------------------
VType_SDL_Texture VTYPE_SDL_Texture("SDL_Texture");

void VType_SDL_Texture::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
}

//------------------------------------------------------------------------------
// Value_SDL_Texture
//------------------------------------------------------------------------------
VType& Value_SDL_Texture::vtype = VTYPE_SDL_Texture;

String Value_SDL_Texture::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_Texture");
}

Gurax_EndModuleScope(sdl)
