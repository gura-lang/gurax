//==============================================================================
// VType_SDL_JoystickGUID.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_JoystickGUID, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_JoystickGUID, `en)}

${help.ComposeMethodHelp(sdl.SDL_JoystickGUID, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_JoystickGUID#propSkeleton
Gurax_DeclareProperty_R(SDL_JoystickGUID, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_JoystickGUID, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_JoystickGUID
//------------------------------------------------------------------------------
VType_SDL_JoystickGUID VTYPE_SDL_JoystickGUID("SDL_JoystickGUID");

void VType_SDL_JoystickGUID::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_JoystickGUID, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_SDL_JoystickGUID
//------------------------------------------------------------------------------
VType& Value_SDL_JoystickGUID::vtype = VTYPE_SDL_JoystickGUID;

String Value_SDL_JoystickGUID::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_JoystickGUID");
}

Gurax_EndModuleScope(sdl)
