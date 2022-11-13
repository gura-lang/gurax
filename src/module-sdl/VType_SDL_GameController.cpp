//==============================================================================
// VType_SDL_GameController.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_GameController, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_GameController, `en)}

${help.ComposeMethodHelp(sdl.SDL_GameController, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_GameController#propSkeleton
Gurax_DeclareProperty_R(SDL_GameController, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_GameController, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_GameController
//------------------------------------------------------------------------------
VType_SDL_GameController VTYPE_SDL_GameController("SDL_GameController");

void VType_SDL_GameController::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_GameController, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_SDL_GameController
//------------------------------------------------------------------------------
VType& Value_SDL_GameController::vtype = VTYPE_SDL_GameController;

String Value_SDL_GameController::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_GameController");
}

Gurax_EndModuleScope(sdl)
