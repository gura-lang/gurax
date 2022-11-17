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

${help.ComposePropertyHelp(gif.ImageDescriptor, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(gif.ImageDescriptor, `en)}

${help.ComposeMethodHelp(gif.ImageDescriptor, `en)}
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(ImageDescriptor, ImageLeftPosition)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& imageDescriptor = valueThis.GetGraphicBlock().GetImageDescriptor();
	return new Value_Number(Gurax_UnpackUInt16(imageDescriptor.ImageLeftPosition));
}

// gif.ImageDescriptor#ImageTopPosition
Gurax_DeclareProperty_R(ImageDescriptor, ImageTopPosition)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(ImageDescriptor, ImageTopPosition)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& imageDescriptor = valueThis.GetGraphicBlock().GetImageDescriptor();
	return new Value_Number(Gurax_UnpackUInt16(imageDescriptor.ImageTopPosition));
}

// gif.ImageDescriptor#ImageWidth
Gurax_DeclareProperty_R(ImageDescriptor, ImageWidth)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(ImageDescriptor, ImageWidth)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& imageDescriptor = valueThis.GetGraphicBlock().GetImageDescriptor();
	return new Value_Number(Gurax_UnpackUInt16(imageDescriptor.ImageWidth));
}

// gif.ImageDescriptor#ImageHeight
Gurax_DeclareProperty_R(ImageDescriptor, ImageHeight)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(ImageDescriptor, ImageHeight)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& imageDescriptor = valueThis.GetGraphicBlock().GetImageDescriptor();
	return new Value_Number(Gurax_UnpackUInt16(imageDescriptor.ImageHeight));
}

// gif.ImageDescriptor#LocalColorTableFlag
Gurax_DeclareProperty_R(ImageDescriptor, LocalColorTableFlag)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(ImageDescriptor, LocalColorTableFlag)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& imageDescriptor = valueThis.GetGraphicBlock().GetImageDescriptor();
	return new Value_Bool(imageDescriptor.GetLocalColorTableFlag());
}

// gif.ImageDescriptor#InterlaceFlag
Gurax_DeclareProperty_R(ImageDescriptor, InterlaceFlag)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(ImageDescriptor, InterlaceFlag)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& imageDescriptor = valueThis.GetGraphicBlock().GetImageDescriptor();
	return new Value_Bool(imageDescriptor.GetInterlaceFlag());
}

// gif.ImageDescriptor#SortFlag
Gurax_DeclareProperty_R(ImageDescriptor, SortFlag)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(ImageDescriptor, SortFlag)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& imageDescriptor = valueThis.GetGraphicBlock().GetImageDescriptor();
	return new Value_Bool(imageDescriptor.GetSortFlag());
}

// gif.ImageDescriptor#SizeOfLocalColorTable
Gurax_DeclareProperty_R(ImageDescriptor, SizeOfLocalColorTable)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(ImageDescriptor, SizeOfLocalColorTable)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& imageDescriptor = valueThis.GetGraphicBlock().GetImageDescriptor();
	return new Value_Number(imageDescriptor.GetSizeOfLocalColorTable());
}

//------------------------------------------------------------------------------
// VType_ImageDescriptor
//------------------------------------------------------------------------------
VType_ImageDescriptor VTYPE_ImageDescriptor("ImageDescriptor");

void VType_ImageDescriptor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(ImageDescriptor, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(ImageDescriptor, ImageLeftPosition));
	Assign(Gurax_CreateProperty(ImageDescriptor, ImageTopPosition));
	Assign(Gurax_CreateProperty(ImageDescriptor, ImageWidth));
	Assign(Gurax_CreateProperty(ImageDescriptor, ImageHeight));
	Assign(Gurax_CreateProperty(ImageDescriptor, LocalColorTableFlag));
	Assign(Gurax_CreateProperty(ImageDescriptor, InterlaceFlag));
	Assign(Gurax_CreateProperty(ImageDescriptor, SortFlag));
	Assign(Gurax_CreateProperty(ImageDescriptor, SizeOfLocalColorTable));
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
