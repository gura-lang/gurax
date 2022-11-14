//==============================================================================
// VType_Mix_Chunk.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.Mix_Chunk, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.Mix_Chunk, `en)}

${help.ComposeMethodHelp(sdl.Mix_Chunk, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// sdl.Mix_Chunk#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Mix_Chunk, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Mix_Chunk, MethodSkeleton)
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
// sdl.Mix_Chunk#propSkeleton
Gurax_DeclareProperty_R(Mix_Chunk, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Mix_Chunk, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Mix_Chunk
//------------------------------------------------------------------------------
VType_Mix_Chunk VTYPE_Mix_Chunk("Mix_Chunk");

void VType_Mix_Chunk::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Mix_Chunk, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Mix_Chunk, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Mix_Chunk
//------------------------------------------------------------------------------
VType& Value_Mix_Chunk::vtype = VTYPE_Mix_Chunk;

String Value_Mix_Chunk::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.Mix_Chunk");
}

Gurax_EndModuleScope(sdl)
