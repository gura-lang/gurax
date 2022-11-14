//==============================================================================
// VType_Mix_Music.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.Mix_Music, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.Mix_Music, `en)}

${help.ComposeMethodHelp(sdl.Mix_Music, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// sdl.Mix_Music#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Mix_Music, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Mix_Music, MethodSkeleton)
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
// sdl.Mix_Music#propSkeleton
Gurax_DeclareProperty_R(Mix_Music, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Mix_Music, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Mix_Music
//------------------------------------------------------------------------------
VType_Mix_Music VTYPE_Mix_Music("Mix_Music");

void VType_Mix_Music::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Mix_Music, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Mix_Music, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Mix_Music
//------------------------------------------------------------------------------
VType& Value_Mix_Music::vtype = VTYPE_Mix_Music;

String Value_Mix_Music::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.Mix_Music");
}

Gurax_EndModuleScope(sdl)
