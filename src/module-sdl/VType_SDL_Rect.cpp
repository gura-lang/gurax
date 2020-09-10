//==============================================================================
// VType_SDL_Rect.cpp
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
// sdl.SDL_Rect#x
Gurax_DeclareProperty_RW(SDL_Rect, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Rect, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().x);
}

Gurax_ImplementPropertySetter(SDL_Rect, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().x = Value_Number::GetNumber<int>(value);
}

// sdl.SDL_Rect#y
Gurax_DeclareProperty_RW(SDL_Rect, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Rect, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().y);
}

Gurax_ImplementPropertySetter(SDL_Rect, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().y = Value_Number::GetNumber<int>(value);
}

// sdl.SDL_Rect#w
Gurax_DeclareProperty_RW(SDL_Rect, w)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Rect, w)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().w);
}

Gurax_ImplementPropertySetter(SDL_Rect, w)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().w = Value_Number::GetNumber<int>(value);
}

// sdl.SDL_Rect#h
Gurax_DeclareProperty_RW(SDL_Rect, h)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Rect, h)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().h);
}

Gurax_ImplementPropertySetter(SDL_Rect, h)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().h = Value_Number::GetNumber<int>(value);
}

//------------------------------------------------------------------------------
// VType_SDL_Rect
//------------------------------------------------------------------------------
VType_SDL_Rect VTYPE_SDL_Rect("SDL_Rect");

void VType_SDL_Rect::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_Rect, x));
	Assign(Gurax_CreateProperty(SDL_Rect, y));
	Assign(Gurax_CreateProperty(SDL_Rect, w));
	Assign(Gurax_CreateProperty(SDL_Rect, h));
}

//------------------------------------------------------------------------------
// Value_SDL_Rect
//------------------------------------------------------------------------------
VType& Value_SDL_Rect::vtype = VTYPE_SDL_Rect;

String Value_SDL_Rect::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_Rect";
}

Gurax_EndModuleScope(sdl)
