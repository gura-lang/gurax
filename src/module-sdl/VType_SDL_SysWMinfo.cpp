//==============================================================================
// VType_SDL_SysWMinfo.cpp
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

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_SysWMinfo#propSkeleton
Gurax_DeclareProperty_R(SDL_SysWMinfo, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_SysWMinfo, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_SysWMinfo
//------------------------------------------------------------------------------
VType_SDL_SysWMinfo VTYPE_SDL_SysWMinfo("SDL_SysWMinfo");

void VType_SDL_SysWMinfo::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_SysWMinfo, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_SDL_SysWMinfo
//------------------------------------------------------------------------------
VType& Value_SDL_SysWMinfo::vtype = VTYPE_SDL_SysWMinfo;

String Value_SDL_SysWMinfo::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_SysWMinfo");
}

Gurax_EndModuleScope(sdl)
