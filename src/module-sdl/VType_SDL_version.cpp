//==============================================================================
// VType_SDL_version.cpp
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
// sdl.SDL_version#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(SDL_version, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(SDL_version, MethodSkeleton)
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
// sdl.SDL_version#propSkeleton
Gurax_DeclareProperty_R(SDL_version, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_version, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_version
//------------------------------------------------------------------------------
VType_SDL_version VTYPE_SDL_version("SDL_version");

void VType_SDL_version::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(SDL_version, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_version, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_SDL_version
//------------------------------------------------------------------------------
VType& Value_SDL_version::vtype = VTYPE_SDL_version;

String Value_SDL_version::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_version";
}

Gurax_EndModuleScope(sdl)
