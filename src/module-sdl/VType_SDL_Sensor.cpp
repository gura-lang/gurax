//==============================================================================
// VType_SDL_Sensor.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(SDL_Sensor)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(SDL_Sensor)}

${help.ComposeMethodHelp(SDL_Sensor)}
)**";

//------------------------------------------------------------------------------
// VType_SDL_Sensor
//------------------------------------------------------------------------------
VType_SDL_Sensor VTYPE_SDL_Sensor("SDL_Sensor");

void VType_SDL_Sensor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
}

//------------------------------------------------------------------------------
// Value_SDL_Sensor
//------------------------------------------------------------------------------
VType& Value_SDL_Sensor::vtype = VTYPE_SDL_Sensor;

String Value_SDL_Sensor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_Sensor");
}

Gurax_EndModuleScope(sdl)
