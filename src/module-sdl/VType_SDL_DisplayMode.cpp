//==============================================================================
// VType_SDL_DisplayMode.cpp
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
// sdl.SDL_DisplayMode#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(SDL_DisplayMode, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(SDL_DisplayMode, MethodSkeleton)
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
// sdl.SDL_DisplayMode#format
Gurax_DeclareProperty_R(SDL_DisplayMode, format)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_DisplayMode, format)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().format);
}

// sdl.SDL_DisplayMode#w
Gurax_DeclareProperty_R(SDL_DisplayMode, w)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_DisplayMode, w)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().w);
}

// sdl.SDL_DisplayMode#h
Gurax_DeclareProperty_R(SDL_DisplayMode, h)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_DisplayMode, h)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().h);
}

// sdl.SDL_DisplayMode#refresh_rate
Gurax_DeclareProperty_R(SDL_DisplayMode, refresh_rate)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_DisplayMode, refresh_rate)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().refresh_rate);
}

//------------------------------------------------------------------------------
// VType_SDL_DisplayMode
//------------------------------------------------------------------------------
VType_SDL_DisplayMode VTYPE_SDL_DisplayMode("SDL_DisplayMode");

void VType_SDL_DisplayMode::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(SDL_DisplayMode, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_DisplayMode, format));
	Assign(Gurax_CreateProperty(SDL_DisplayMode, w));
	Assign(Gurax_CreateProperty(SDL_DisplayMode, h));
	Assign(Gurax_CreateProperty(SDL_DisplayMode, refresh_rate));
}

//------------------------------------------------------------------------------
// Value_SDL_DisplayMode
//------------------------------------------------------------------------------
VType& Value_SDL_DisplayMode::vtype = VTYPE_SDL_DisplayMode;

String Value_SDL_DisplayMode::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_DisplayMode";
}

Gurax_EndModuleScope(sdl)
