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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// VType_SDL_Renderer
//------------------------------------------------------------------------------
VType_SDL_Renderer VTYPE_SDL_Renderer("SDL_Renderer");

void VType_SDL_Renderer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
}

//------------------------------------------------------------------------------
// Value_SDL_Renderer
//------------------------------------------------------------------------------
VType& Value_SDL_Renderer::vtype = VTYPE_SDL_Renderer;

String Value_SDL_Renderer::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_Renderer";
}

Gurax_EndModuleScope(sdl)
