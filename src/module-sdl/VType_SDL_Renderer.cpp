//==============================================================================
// VType_SDL_Renderer.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_Renderer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_Renderer, `en)}

${help.ComposeMethodHelp(sdl.SDL_Renderer, `en)}
)**";

//------------------------------------------------------------------------------
// VType_SDL_Renderer
//------------------------------------------------------------------------------
VType_SDL_Renderer VTYPE_SDL_Renderer("SDL_Renderer");

void VType_SDL_Renderer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
}

//------------------------------------------------------------------------------
// Value_SDL_Renderer
//------------------------------------------------------------------------------
VType& Value_SDL_Renderer::vtype = VTYPE_SDL_Renderer;

String Value_SDL_Renderer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_Renderer");
}

Gurax_EndModuleScope(sdl)
