//==============================================================================
// VType_PlainTextExtension.cpp
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
// gif.PlainTextExtension#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(PlainTextExtension, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(PlainTextExtension, MethodSkeleton)
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
// gif.PlainTextExtension#propSkeleton
Gurax_DeclareProperty_R(PlainTextExtension, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(PlainTextExtension, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_PlainTextExtension
//------------------------------------------------------------------------------
VType_PlainTextExtension VTYPE_PlainTextExtension("PlainTextExtension");

void VType_PlainTextExtension::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(PlainTextExtension, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(PlainTextExtension, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_PlainTextExtension
//------------------------------------------------------------------------------
VType& Value_PlainTextExtension::vtype = VTYPE_PlainTextExtension;

String Value_PlainTextExtension::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetContent().ToString(ss));
}

Gurax_EndModuleScope(gif)
