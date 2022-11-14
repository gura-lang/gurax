//==============================================================================
// VType_SDL_Palette.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_Palette, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_Palette, `en)}

${help.ComposeMethodHelp(sdl.SDL_Palette, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_Palette#ncolors
Gurax_DeclareProperty_R(SDL_Palette, ncolors)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Palette, ncolors)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().ncolors);
}

// sdl.SDL_Palette#colors
Gurax_DeclareProperty_R(SDL_Palette, colors)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Palette, colors)
{
	auto& valueThis = GetValueThis(valueTarget);
	int ncolors = valueThis.GetEntity().ncolors;
	SDL_Color* colors = valueThis.GetEntity().colors;
	RefPtr<ValueOwner> pValues(new ValueOwner());
	pValues->reserve(ncolors);
	for (int i = 0; i < ncolors; i++) {
		pValues->push_back(new Value_SDL_Color(colors[i]));
	}
	return new Value_List(pValues.release());
}

//------------------------------------------------------------------------------
// VType_SDL_Palette
//------------------------------------------------------------------------------
VType_SDL_Palette VTYPE_SDL_Palette("SDL_Palette");

void VType_SDL_Palette::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_Palette, ncolors));
	Assign(Gurax_CreateProperty(SDL_Palette, colors));
}

//------------------------------------------------------------------------------
// Value_SDL_Palette
//------------------------------------------------------------------------------
VType& Value_SDL_Palette::vtype = VTYPE_SDL_Palette;

String Value_SDL_Palette::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_Palette");
}

Gurax_EndModuleScope(sdl)
