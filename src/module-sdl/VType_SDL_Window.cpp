//==============================================================================
// VType_SDL_Window.cpp
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
// VType_SDL_Window
//------------------------------------------------------------------------------
VType_SDL_Window VTYPE_SDL_Window("SDL_Window");

void VType_SDL_Window::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
}

//------------------------------------------------------------------------------
// Value_SDL_Window
//------------------------------------------------------------------------------
VType& Value_SDL_Window::vtype = VTYPE_SDL_Window;

String Value_SDL_Window::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_Window";
}

Gurax_EndModuleScope(sdl)
