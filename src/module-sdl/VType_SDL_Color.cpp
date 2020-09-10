//==============================================================================
// VType_SDL_Color.cpp
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
// Implementation of method
//-----------------------------------------------------------------------------
// sdl.SDL_Color#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(SDL_Color, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(SDL_Color, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_Color#r
Gurax_DeclareProperty_RW(SDL_Color, r)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Color, r)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().r);
}

Gurax_ImplementPropertySetter(SDL_Color, r)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().r = Value_Number::GetNumberRanged<Uint8>(value, 0, 255);
}

// sdl.SDL_Color#g
Gurax_DeclareProperty_RW(SDL_Color, g)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Color, g)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().g);
}

Gurax_ImplementPropertySetter(SDL_Color, g)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().g = Value_Number::GetNumberRanged<Uint8>(value, 0, 255);
}

// sdl.SDL_Color#b
Gurax_DeclareProperty_RW(SDL_Color, b)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Color, b)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().b);
}

Gurax_ImplementPropertySetter(SDL_Color, b)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().b = Value_Number::GetNumberRanged<Uint8>(value, 0, 255);
}

// sdl.SDL_Color#a
Gurax_DeclareProperty_RW(SDL_Color, a)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Color, a)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().a);
}

Gurax_ImplementPropertySetter(SDL_Color, a)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().a = Value_Number::GetNumberRanged<Uint8>(value, 0, 255);
}

//------------------------------------------------------------------------------
// VType_SDL_Color
//------------------------------------------------------------------------------
VType_SDL_Color VTYPE_SDL_Color("SDL_Color");

void VType_SDL_Color::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(SDL_Color, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_Color, r));
	Assign(Gurax_CreateProperty(SDL_Color, g));
	Assign(Gurax_CreateProperty(SDL_Color, b));
	Assign(Gurax_CreateProperty(SDL_Color, a));
}

//------------------------------------------------------------------------------
// Value_SDL_Color
//------------------------------------------------------------------------------
VType& Value_SDL_Color::vtype = VTYPE_SDL_Color;

String Value_SDL_Color::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_Color";
}

Gurax_EndModuleScope(sdl)
