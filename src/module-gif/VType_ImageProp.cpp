//==============================================================================
// VType_ImageProp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gif)

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
// gif.ImageProp#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(ImageProp, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(ImageProp, MethodSkeleton)
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
// gif.ImageProp#propSkeleton
Gurax_DeclareProperty_R(ImageProp, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(ImageProp, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_ImageProp
//------------------------------------------------------------------------------
VType_ImageProp VTYPE_ImageProp("ImageProp");

void VType_ImageProp::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(ImageProp, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(ImageProp, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_ImageProp
//------------------------------------------------------------------------------
VType& Value_ImageProp::vtype = VTYPE_ImageProp;

String Value_ImageProp::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "gif.ImageProp");
}

Gurax_EndModuleScope(gif)
