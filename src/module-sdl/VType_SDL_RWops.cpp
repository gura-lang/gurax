//==============================================================================
// VType_SDL_RWops.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(SDL_RWops)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(SDL_RWops)}

${help.ComposeMethodHelp(SDL_RWops)}
)**";

//------------------------------------------------------------------------------
// VType_SDL_RWops
//------------------------------------------------------------------------------
VType_SDL_RWops VTYPE_SDL_RWops("SDL_RWops");

void VType_SDL_RWops::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
}

//------------------------------------------------------------------------------
// Value_SDL_RWops
//------------------------------------------------------------------------------
VType& Value_SDL_RWops::vtype = VTYPE_SDL_RWops;

String Value_SDL_RWops::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_RWops");
}

Gurax_EndModuleScope(sdl)
