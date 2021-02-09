//==============================================================================
// VType_ImageDescriptor.cpp
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
// gif.ImageDescriptor#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(ImageDescriptor, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(ImageDescriptor, MethodSkeleton)
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
// gif.ImageDescriptor#ImageLeftPosition
Gurax_DeclareProperty_R(ImageDescriptor, ImageLeftPosition)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(ImageDescriptor, ImageLeftPosition)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& imageDescriptor = valueThis.GetImageProp().GetImageDescriptor();
	return new Value_Number(Gurax_UnpackUInt16(imageDescriptor.ImageLeftPosition));
}

// gif.ImageDescriptor#ImageTopPosition
Gurax_DeclareProperty_R(ImageDescriptor, ImageTopPosition)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(ImageDescriptor, ImageTopPosition)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& imageDescriptor = valueThis.GetImageProp().GetImageDescriptor();
	return new Value_Number(Gurax_UnpackUInt16(imageDescriptor.ImageTopPosition));
}

// gif.ImageDescriptor#ImageWidth
Gurax_DeclareProperty_R(ImageDescriptor, ImageWidth)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(ImageDescriptor, ImageWidth)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& imageDescriptor = valueThis.GetImageProp().GetImageDescriptor();
	return new Value_Number(Gurax_UnpackUInt16(imageDescriptor.ImageWidth));
}

// gif.ImageDescriptor#ImageHeight
Gurax_DeclareProperty_R(ImageDescriptor, ImageHeight)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(ImageDescriptor, ImageHeight)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& imageDescriptor = valueThis.GetImageProp().GetImageDescriptor();
	return new Value_Number(Gurax_UnpackUInt16(imageDescriptor.ImageHeight));
}

//------------------------------------------------------------------------------
// VType_ImageDescriptor
//------------------------------------------------------------------------------
VType_ImageDescriptor VTYPE_ImageDescriptor("ImageDescriptor");

void VType_ImageDescriptor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(ImageDescriptor, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(ImageDescriptor, ImageLeftPosition));
	Assign(Gurax_CreateProperty(ImageDescriptor, ImageTopPosition));
	Assign(Gurax_CreateProperty(ImageDescriptor, ImageWidth));
	Assign(Gurax_CreateProperty(ImageDescriptor, ImageHeight));
}

//------------------------------------------------------------------------------
// Value_ImageDescriptor
//------------------------------------------------------------------------------
VType& Value_ImageDescriptor::vtype = VTYPE_ImageDescriptor;

String Value_ImageDescriptor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "gif.ImageDescriptor");
}

Gurax_EndModuleScope(gif)
