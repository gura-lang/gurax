//==============================================================================
// VType_LogicalScreenDescriptor.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(gif.LogicalScreenDescriptor, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(gif.LogicalScreenDescriptor, `en)}

${help.ComposeMethodHelp(gif.LogicalScreenDescriptor, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// gif.LogicalScreenDescriptor#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(LogicalScreenDescriptor, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(LogicalScreenDescriptor, MethodSkeleton)
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
// gif.LogicalScreenDescriptor#LogicalScreenWidth
Gurax_DeclareProperty_R(LogicalScreenDescriptor, LogicalScreenWidth)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(LogicalScreenDescriptor, LogicalScreenWidth)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& logicalScreenDescriptor = valueThis.GetContent().GetLogicalScreenDescriptor();
	return new Value_Number(Gurax_UnpackUInt16(logicalScreenDescriptor.LogicalScreenWidth));
}

// gif.LogicalScreenDescriptor#LogicalScreenHeight
Gurax_DeclareProperty_R(LogicalScreenDescriptor, LogicalScreenHeight)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(LogicalScreenDescriptor, LogicalScreenHeight)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& logicalScreenDescriptor = valueThis.GetContent().GetLogicalScreenDescriptor();
	return new Value_Number(Gurax_UnpackUInt16(logicalScreenDescriptor.LogicalScreenHeight));
}

// gif.LogicalScreenDescriptor#BackgroundColorIndex
Gurax_DeclareProperty_R(LogicalScreenDescriptor, BackgroundColorIndex)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(LogicalScreenDescriptor, BackgroundColorIndex)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& logicalScreenDescriptor = valueThis.GetContent().GetLogicalScreenDescriptor();
	return new Value_Number(logicalScreenDescriptor.BackgroundColorIndex);
}

// gif.LogicalScreenDescriptor#PixelAspectRatio
Gurax_DeclareProperty_R(LogicalScreenDescriptor, PixelAspectRatio)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(LogicalScreenDescriptor, PixelAspectRatio)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& logicalScreenDescriptor = valueThis.GetContent().GetLogicalScreenDescriptor();
	return new Value_Number(logicalScreenDescriptor.PixelAspectRatio);
}

// gif.LogicalScreenDescriptor#GlobalColorTableFlag
Gurax_DeclareProperty_R(LogicalScreenDescriptor, GlobalColorTableFlag)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(LogicalScreenDescriptor, GlobalColorTableFlag)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& logicalScreenDescriptor = valueThis.GetContent().GetLogicalScreenDescriptor();
	return new Value_Bool(logicalScreenDescriptor.GetGlobalColorTableFlag());
}

// gif.LogicalScreenDescriptor#ColorResolution
Gurax_DeclareProperty_R(LogicalScreenDescriptor, ColorResolution)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(LogicalScreenDescriptor, ColorResolution)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& logicalScreenDescriptor = valueThis.GetContent().GetLogicalScreenDescriptor();
	return new Value_Number(logicalScreenDescriptor.GetColorResolution());
}

// gif.LogicalScreenDescriptor#SortFlag
Gurax_DeclareProperty_R(LogicalScreenDescriptor, SortFlag)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(LogicalScreenDescriptor, SortFlag)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& logicalScreenDescriptor = valueThis.GetContent().GetLogicalScreenDescriptor();
	return new Value_Bool(logicalScreenDescriptor.GetSortFlag());
}

// gif.LogicalScreenDescriptor#SizeOfGlobalColorTable
Gurax_DeclareProperty_R(LogicalScreenDescriptor, SizeOfGlobalColorTable)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(LogicalScreenDescriptor, SizeOfGlobalColorTable)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& logicalScreenDescriptor = valueThis.GetContent().GetLogicalScreenDescriptor();
	return new Value_Number(logicalScreenDescriptor.GetSizeOfGlobalColorTable());
}

//------------------------------------------------------------------------------
// VType_LogicalScreenDescriptor
//------------------------------------------------------------------------------
VType_LogicalScreenDescriptor VTYPE_LogicalScreenDescriptor("LogicalScreenDescriptor");

void VType_LogicalScreenDescriptor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(LogicalScreenDescriptor, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(LogicalScreenDescriptor, LogicalScreenWidth));
	Assign(Gurax_CreateProperty(LogicalScreenDescriptor, LogicalScreenHeight));
	Assign(Gurax_CreateProperty(LogicalScreenDescriptor, BackgroundColorIndex));
	Assign(Gurax_CreateProperty(LogicalScreenDescriptor, PixelAspectRatio));
	Assign(Gurax_CreateProperty(LogicalScreenDescriptor, GlobalColorTableFlag));
	Assign(Gurax_CreateProperty(LogicalScreenDescriptor, ColorResolution));
	Assign(Gurax_CreateProperty(LogicalScreenDescriptor, SortFlag));
	Assign(Gurax_CreateProperty(LogicalScreenDescriptor, SizeOfGlobalColorTable));
}

//------------------------------------------------------------------------------
// Value_LogicalScreenDescriptor
//------------------------------------------------------------------------------
VType& Value_LogicalScreenDescriptor::vtype = VTYPE_LogicalScreenDescriptor;

String Value_LogicalScreenDescriptor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetContent().ToString(ss));
}

Gurax_EndModuleScope(gif)
