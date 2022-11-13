//==============================================================================
// VType_SDL_PixelFormat.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_PixelFormat, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_PixelFormat, `en)}

${help.ComposeMethodHelp(sdl.SDL_PixelFormat, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_PixelFormat#format
Gurax_DeclareProperty_R(SDL_PixelFormat, format)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_PixelFormat, format)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().format);
}

// sdl.SDL_PixelFormat#palette
Gurax_DeclareProperty_R(SDL_PixelFormat, palette)
{
	Declare(VTYPE_SDL_Palette, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_PixelFormat, palette)
{
	auto& valueThis = GetValueThis(valueTarget);
	SDL_Palette* palette = valueThis.GetEntity().palette;
	if (!palette) return Value::nil();
	return new Value_SDL_Palette(palette);
}

// sdl.SDL_PixelFormat#BitsPerPixel
Gurax_DeclareProperty_R(SDL_PixelFormat, BitsPerPixel)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_PixelFormat, BitsPerPixel)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().BitsPerPixel);
}

// sdl.SDL_PixelFormat#BytesPerPixel
Gurax_DeclareProperty_R(SDL_PixelFormat, BytesPerPixel)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_PixelFormat, BytesPerPixel)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().BytesPerPixel);
}

// sdl.SDL_PixelFormat#Rmask
Gurax_DeclareProperty_R(SDL_PixelFormat, Rmask)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_PixelFormat, Rmask)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().Rmask);
}

// sdl.SDL_PixelFormat#Gmask
Gurax_DeclareProperty_R(SDL_PixelFormat, Gmask)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_PixelFormat, Gmask)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().Gmask);
}

// sdl.SDL_PixelFormat#Bmask
Gurax_DeclareProperty_R(SDL_PixelFormat, Bmask)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_PixelFormat, Bmask)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().Bmask);
}

// sdl.SDL_PixelFormat#Amask
Gurax_DeclareProperty_R(SDL_PixelFormat, Amask)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_PixelFormat, Amask)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().Amask);
}

//------------------------------------------------------------------------------
// VType_SDL_PixelFormat
//------------------------------------------------------------------------------
VType_SDL_PixelFormat VTYPE_SDL_PixelFormat("SDL_PixelFormat");

void VType_SDL_PixelFormat::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_PixelFormat, format));
	Assign(Gurax_CreateProperty(SDL_PixelFormat, palette));
	Assign(Gurax_CreateProperty(SDL_PixelFormat, BitsPerPixel));
	Assign(Gurax_CreateProperty(SDL_PixelFormat, BytesPerPixel));
	Assign(Gurax_CreateProperty(SDL_PixelFormat, Rmask));
	Assign(Gurax_CreateProperty(SDL_PixelFormat, Gmask));
	Assign(Gurax_CreateProperty(SDL_PixelFormat, Bmask));
	Assign(Gurax_CreateProperty(SDL_PixelFormat, Amask));
}

//------------------------------------------------------------------------------
// Value_SDL_PixelFormat
//------------------------------------------------------------------------------
VType& Value_SDL_PixelFormat::vtype = VTYPE_SDL_PixelFormat;

String Value_SDL_PixelFormat::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_PixelFormat");
}

Gurax_EndModuleScope(sdl)
