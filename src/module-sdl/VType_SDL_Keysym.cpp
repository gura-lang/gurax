//==============================================================================
// VType_SDL_Keysym.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_Keysym, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_Keysym, `en)}

${help.ComposeMethodHelp(sdl.SDL_Keysym, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_Keysym#scancode
Gurax_DeclareProperty_R(SDL_Keysym, scancode)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Keysym, scancode)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().scancode);
}

// sdl.SDL_Keysym#sym
Gurax_DeclareProperty_R(SDL_Keysym, sym)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Keysym, sym)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().sym);
}

// sdl.SDL_Keysym#mod
Gurax_DeclareProperty_R(SDL_Keysym, mod)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Keysym, mod)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().mod);
}

//------------------------------------------------------------------------------
// VType_SDL_Keysym
//------------------------------------------------------------------------------
VType_SDL_Keysym VTYPE_SDL_Keysym("SDL_Keysym");

void VType_SDL_Keysym::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_Keysym, scancode));
	Assign(Gurax_CreateProperty(SDL_Keysym, sym));
	Assign(Gurax_CreateProperty(SDL_Keysym, mod));
}

//------------------------------------------------------------------------------
// Value_SDL_Keysym
//------------------------------------------------------------------------------
VType& Value_SDL_Keysym::vtype = VTYPE_SDL_Keysym;

String Value_SDL_Keysym::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_Keysym");
}

Gurax_EndModuleScope(sdl)
