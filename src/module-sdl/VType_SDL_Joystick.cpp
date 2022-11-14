//==============================================================================
// VType_SDL_Joystick.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_Joystick, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_Joystick, `en)}

${help.ComposeMethodHelp(sdl.SDL_Joystick, `en)}
)**";

//------------------------------------------------------------------------------
// VType_SDL_Joystick
//------------------------------------------------------------------------------
VType_SDL_Joystick VTYPE_SDL_Joystick("SDL_Joystick");

void VType_SDL_Joystick::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
}

//------------------------------------------------------------------------------
// Value_SDL_Joystick
//------------------------------------------------------------------------------
VType& Value_SDL_Joystick::vtype = VTYPE_SDL_Joystick;

String Value_SDL_Joystick::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_Joystick");
}

Gurax_EndModuleScope(sdl)
