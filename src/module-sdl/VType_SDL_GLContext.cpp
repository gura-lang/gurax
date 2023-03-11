//==============================================================================
// VType_SDL_GLContext.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_GLContext, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_GLContext, `en)}

${help.ComposeMethodHelp(sdl.SDL_GLContext, `en)}
)""";

//------------------------------------------------------------------------------
// VType_SDL_GLContext
//------------------------------------------------------------------------------
VType_SDL_GLContext VTYPE_SDL_GLContext("SDL_GLContext");

void VType_SDL_GLContext::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
}

//------------------------------------------------------------------------------
// Value_SDL_GLContext
//------------------------------------------------------------------------------
VType& Value_SDL_GLContext::vtype = VTYPE_SDL_GLContext;

String Value_SDL_GLContext::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_GLContext");
}

Gurax_EndModuleScope(sdl)
