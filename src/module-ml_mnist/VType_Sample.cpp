//==============================================================================
// VType_Sample.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.mnist.Sample, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.mnist.Sample, `en)}

${help.ComposeMethodHelp(ml.mnist.Sample, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.mnist.Sample#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Sample, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Sample, MethodSkeleton)
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
// ml.mnist.Sample#input
Gurax_DeclareProperty_R(Sample, input)
{
	Declare(VTYPE_Array, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, input)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Array(valueThis.GetSample().GetArrayInput().Reference());
}

// ml.mnist.Sample#result
Gurax_DeclareProperty_R(Sample, result)
{
	Declare(VTYPE_Array, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, result)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Array(valueThis.GetSample().GetArrayResult().Reference());
}

// ml.mnist.Sample#image
Gurax_DeclareProperty_R(Sample, image)
{
	Declare(VTYPE_Image, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, image)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Image(valueThis.GetSample().GetImage().Reference());
}

// ml.mnist.Sample#label
Gurax_DeclareProperty_R(Sample, label)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, label)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetSample().GetLabel());
}

// ml.mnist.Sample#labels
Gurax_DeclareProperty_R(Sample, labels)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, labels)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_List(VTYPE_Number, valueThis.GetSample().GetValuesLabel().Reference());
}

//------------------------------------------------------------------------------
// VType_Sample
//------------------------------------------------------------------------------
VType_Sample VTYPE_Sample("Sample");

void VType_Sample::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Sample, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Sample, input));
	Assign(Gurax_CreateProperty(Sample, result));
	Assign(Gurax_CreateProperty(Sample, image));
	Assign(Gurax_CreateProperty(Sample, label));
	Assign(Gurax_CreateProperty(Sample, labels));
}

//------------------------------------------------------------------------------
// Value_Sample
//------------------------------------------------------------------------------
VType& Value_Sample::vtype = VTYPE_Sample;

String Value_Sample::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetSample().ToString(ss));
}

Gurax_EndModuleScope(ml_mnist)
