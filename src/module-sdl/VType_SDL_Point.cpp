//==============================================================================
// VType_SDL_Point.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_Point, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_Point, `en)}

${help.ComposeMethodHelp(sdl.SDL_Point, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// SDL_Point(x?:Number, y?:Number) {block?}
Gurax_DeclareConstructor(SDL_Point)
{
	Declare(VTYPE_Color, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `SDL_Point` instance.
)**");
}

Gurax_ImplementConstructor(SDL_Point)
{
	// Arguments
	ArgPicker args(argument);
	SDL_Point point;
	point.x = args.IsValid()? args.PickNumber<int>() : 0;
	point.y = args.IsValid()? args.PickNumber<int>() : 0;
	// Function body
	return argument.ReturnValue(processor, new Value_SDL_Point(point));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_Point#x
Gurax_DeclareProperty_RW(SDL_Point, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Point, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().x);
}

Gurax_ImplementPropertySetter(SDL_Point, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().x = Value_Number::GetNumber<int>(value);
}

// sdl.SDL_Point#y
Gurax_DeclareProperty_RW(SDL_Point, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Point, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().y);
}

Gurax_ImplementPropertySetter(SDL_Point, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().y = Value_Number::GetNumber<int>(value);
}

//------------------------------------------------------------------------------
// VType_SDL_Point
//------------------------------------------------------------------------------
VType_SDL_Point VTYPE_SDL_Point("SDL_Point");

void VType_SDL_Point::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(SDL_Point));
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_Point, x));
	Assign(Gurax_CreateProperty(SDL_Point, y));
}

//------------------------------------------------------------------------------
// Value_SDL_Point
//------------------------------------------------------------------------------
VType& Value_SDL_Point::vtype = VTYPE_SDL_Point;

String Value_SDL_Point::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_Point");
}

Gurax_EndModuleScope(sdl)
