//==============================================================================
// VType_SDL_Texture.cpp
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
// sdl.SDL_Texture#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(SDL_Texture, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(SDL_Texture, MethodSkeleton)
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
// sdl.SDL_Texture#propSkeleton
Gurax_DeclareProperty_R(SDL_Texture, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Texture, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_Texture
//------------------------------------------------------------------------------
VType_SDL_Texture VTYPE_SDL_Texture("SDL_Texture");

void VType_SDL_Texture::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(SDL_Texture, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_Texture, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_SDL_Texture
//------------------------------------------------------------------------------
VType& Value_SDL_Texture::vtype = VTYPE_SDL_Texture;

String Value_SDL_Texture::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_Texture";
}

Gurax_EndModuleScope(sdl)
