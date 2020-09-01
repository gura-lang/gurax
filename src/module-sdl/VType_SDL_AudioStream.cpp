//==============================================================================
// VType_SDL_AudioStream.cpp
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
// sdl.SDL_AudioStream#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(SDL_AudioStream, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(SDL_AudioStream, MethodSkeleton)
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
// sdl.SDL_AudioStream#propSkeleton
Gurax_DeclareProperty_R(SDL_AudioStream, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_AudioStream, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_AudioStream
//------------------------------------------------------------------------------
VType_SDL_AudioStream VTYPE_SDL_AudioStream("SDL_AudioStream");

void VType_SDL_AudioStream::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(SDL_AudioStream, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_AudioStream, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_SDL_AudioStream
//------------------------------------------------------------------------------
VType& Value_SDL_AudioStream::vtype = VTYPE_SDL_AudioStream;

String Value_SDL_AudioStream::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_AudioStream";
}

Gurax_EndModuleScope(sdl)
