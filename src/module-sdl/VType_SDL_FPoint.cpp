//==============================================================================
// VType_SDL_FPoint.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(SDL_FPoint)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(SDL_FPoint)}

${help.ComposeMethodHelp(SDL_FPoint)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_FPoint#x
Gurax_DeclareProperty_R(SDL_FPoint, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_FPoint, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().x);
}

// sdl.SDL_FPoint#y
Gurax_DeclareProperty_R(SDL_FPoint, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_FPoint, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().y);
}

//------------------------------------------------------------------------------
// VType_SDL_FPoint
//------------------------------------------------------------------------------
VType_SDL_FPoint VTYPE_SDL_FPoint("SDL_FPoint");

void VType_SDL_FPoint::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_FPoint, x));
	Assign(Gurax_CreateProperty(SDL_FPoint, y));
}

//------------------------------------------------------------------------------
// Value_SDL_FPoint
//------------------------------------------------------------------------------
VType& Value_SDL_FPoint::vtype = VTYPE_SDL_FPoint;

String Value_SDL_FPoint::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_FPoint");
}

Gurax_EndModuleScope(sdl)
