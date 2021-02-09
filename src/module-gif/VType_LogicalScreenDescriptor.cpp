//==============================================================================
// VType_LogicalScreenDescriptor.cpp
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
// gif.LogicalScreenDescriptor#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(LogicalScreenDescriptor, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
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
// gif.LogicalScreenDescriptor#propSkeleton
Gurax_DeclareProperty_R(LogicalScreenDescriptor, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(LogicalScreenDescriptor, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_LogicalScreenDescriptor
//------------------------------------------------------------------------------
VType_LogicalScreenDescriptor VTYPE_LogicalScreenDescriptor("LogicalScreenDescriptor");

void VType_LogicalScreenDescriptor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(LogicalScreenDescriptor, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(LogicalScreenDescriptor, propSkeleton));
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
