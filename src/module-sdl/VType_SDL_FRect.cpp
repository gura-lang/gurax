//==============================================================================
// VType_SDL_FRect.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_FRect, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_FRect, `en)}

${help.ComposeMethodHelp(sdl.SDL_FRect, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_FRect#x
Gurax_DeclareProperty_RW(SDL_FRect, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_FRect, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().x);
}

Gurax_ImplementPropertySetter(SDL_FRect, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().x = Value_Number::GetNumber<int>(value);
}

// sdl.SDL_FRect#y
Gurax_DeclareProperty_RW(SDL_FRect, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_FRect, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().y);
}

Gurax_ImplementPropertySetter(SDL_FRect, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().y = Value_Number::GetNumber<int>(value);
}

// sdl.SDL_FRect#w
Gurax_DeclareProperty_RW(SDL_FRect, w)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_FRect, w)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().w);
}

Gurax_ImplementPropertySetter(SDL_FRect, w)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().w = Value_Number::GetNumber<int>(value);
}

// sdl.SDL_FRect#h
Gurax_DeclareProperty_RW(SDL_FRect, h)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_FRect, h)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().h);
}

Gurax_ImplementPropertySetter(SDL_FRect, h)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().h = Value_Number::GetNumber<int>(value);
}

//------------------------------------------------------------------------------
// VType_SDL_FRect
//------------------------------------------------------------------------------
VType_SDL_FRect VTYPE_SDL_FRect("SDL_FRect");

void VType_SDL_FRect::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_FRect, x));
	Assign(Gurax_CreateProperty(SDL_FRect, y));
	Assign(Gurax_CreateProperty(SDL_FRect, w));
	Assign(Gurax_CreateProperty(SDL_FRect, h));
}

//------------------------------------------------------------------------------
// Value_SDL_FRect
//------------------------------------------------------------------------------
VType& Value_SDL_FRect::vtype = VTYPE_SDL_FRect;

String Value_SDL_FRect::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_FRect");
}

Gurax_EndModuleScope(sdl)
