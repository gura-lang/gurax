//==============================================================================
// VType_TTF_Font.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.TTF_Font, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.TTF_Font, `en)}

${help.ComposeMethodHelp(sdl.TTF_Font, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// sdl.TTF_Font#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(TTF_Font, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(TTF_Font, MethodSkeleton)
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
// sdl.TTF_Font#propSkeleton
Gurax_DeclareProperty_R(TTF_Font, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(TTF_Font, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_TTF_Font
//------------------------------------------------------------------------------
VType_TTF_Font VTYPE_TTF_Font("TTF_Font");

void VType_TTF_Font::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(TTF_Font, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(TTF_Font, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_TTF_Font
//------------------------------------------------------------------------------
VType& Value_TTF_Font::vtype = VTYPE_TTF_Font;

String Value_TTF_Font::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.TTF_Font");
}

Gurax_EndModuleScope(sdl)
