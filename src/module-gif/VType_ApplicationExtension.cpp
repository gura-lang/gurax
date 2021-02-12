//==============================================================================
// VType_ApplicationExtension.cpp
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
// gif.ApplicationExtension#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(ApplicationExtension, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(ApplicationExtension, MethodSkeleton)
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
// Implementation of class property
//-----------------------------------------------------------------------------
// gif.ApplicationExtension#default
Gurax_DeclareClassPropertyAlias_R(ApplicationExtension, default_, "default")
{
	Declare(VTYPE_ApplicationExtension, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassPropertyGetter(ApplicationExtension, default_)
{
	return new Value_ApplicationExtension(Content::extensionsCommon.applicationExtension, nullptr);
}

//------------------------------------------------------------------------------
// VType_ApplicationExtension
//------------------------------------------------------------------------------
VType_ApplicationExtension VTYPE_ApplicationExtension("ApplicationExtension");

void VType_ApplicationExtension::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(ApplicationExtension, MethodSkeleton));
	// Assignment of class property
	Assign(Gurax_CreateClassProperty(ApplicationExtension, default_));
}

//------------------------------------------------------------------------------
// Value_ApplicationExtension
//------------------------------------------------------------------------------
VType& Value_ApplicationExtension::vtype = VTYPE_ApplicationExtension;

String Value_ApplicationExtension::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "gif.ApplicationExtension");
}

Gurax_EndModuleScope(gif)
