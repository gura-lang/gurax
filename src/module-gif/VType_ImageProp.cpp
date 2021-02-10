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
// gif.ImageProp#GraphicControlExtension
Gurax_DeclareProperty_R(ImageProp, GraphicControlExtension)
{
	Declare(VTYPE_GraphicControlExtension, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(ImageProp, GraphicControlExtension)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_GraphicControlExtension(valueThis.GetImageProp().Reference());
}

// gif.ImageProp#ImageDescriptor
Gurax_DeclareProperty_R(ImageProp, ImageDescriptor)
{
	Declare(VTYPE_ImageDescriptor, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(ImageProp, ImageDescriptor)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_ImageDescriptor(valueThis.GetImageProp().Reference());
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
	Assign(Gurax_CreateProperty(ImageProp, GraphicControlExtension));
	Assign(Gurax_CreateProperty(ImageProp, ImageDescriptor));
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