//==============================================================================
// VType_GraphicControlExtension.cpp
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
// gif.GraphicControlExtension#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(GraphicControlExtension, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(GraphicControlExtension, MethodSkeleton)
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
// gif.GraphicControlExtension#propSkeleton
Gurax_DeclareProperty_R(GraphicControlExtension, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(GraphicControlExtension, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_GraphicControlExtension
//------------------------------------------------------------------------------
VType_GraphicControlExtension VTYPE_GraphicControlExtension("GraphicControlExtension");

void VType_GraphicControlExtension::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(GraphicControlExtension, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(GraphicControlExtension, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_GraphicControlExtension
//------------------------------------------------------------------------------
VType& Value_GraphicControlExtension::vtype = VTYPE_GraphicControlExtension;

String Value_GraphicControlExtension::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "gif.GraphicControlExtension");
}

Gurax_EndModuleScope(gif)
