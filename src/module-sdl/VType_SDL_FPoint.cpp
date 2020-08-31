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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// sdl.SDL_FPoint#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(SDL_FPoint, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(SDL_FPoint, MethodSkeleton)
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
// sdl.SDL_FPoint#propSkeleton
Gurax_DeclareProperty_R(SDL_FPoint, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_FPoint, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
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
	// Assignment of method
	Assign(Gurax_CreateMethod(SDL_FPoint, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_FPoint, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_SDL_FPoint
//------------------------------------------------------------------------------
VType& Value_SDL_FPoint::vtype = VTYPE_SDL_FPoint;

String Value_SDL_FPoint::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_FPoint";
}

Gurax_EndModuleScope(sdl)
