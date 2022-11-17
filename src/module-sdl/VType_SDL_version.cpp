//==============================================================================
// VType_SDL_version.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_version, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_version, `en)}

${help.ComposeMethodHelp(sdl.SDL_version, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_version#major
Gurax_DeclareProperty_R(SDL_version, major)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_version, major)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().major);
}

// sdl.SDL_version#minor
Gurax_DeclareProperty_R(SDL_version, minor)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_version, minor)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().minor);
}

// sdl.SDL_version#patch
Gurax_DeclareProperty_R(SDL_version, patch)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_version, patch)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().patch);
}

//------------------------------------------------------------------------------
// VType_SDL_version
//------------------------------------------------------------------------------
VType_SDL_version VTYPE_SDL_version("SDL_version");

void VType_SDL_version::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_version, major));
	Assign(Gurax_CreateProperty(SDL_version, minor));
	Assign(Gurax_CreateProperty(SDL_version, patch));
}

//------------------------------------------------------------------------------
// Value_SDL_version
//------------------------------------------------------------------------------
VType& Value_SDL_version::vtype = VTYPE_SDL_version;

String Value_SDL_version::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_version");
}

Gurax_EndModuleScope(sdl)
