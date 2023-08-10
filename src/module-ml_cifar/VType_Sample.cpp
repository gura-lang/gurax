//==============================================================================
// VType_Sample.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.cifar.Sample, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.cifar.Sample, `en)}

${help.ComposeMethodHelp(ml.cifar.Sample, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.cifar.Sample#MethodSkeleton(num1 as Number, num2 as Number)
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
// ml.cifar.Sample#input
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

// ml.cifar.Sample#result
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

// ml.cifar.Sample#image
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

// ml.cifar.Sample#label
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
}

//------------------------------------------------------------------------------
// Value_Sample
//------------------------------------------------------------------------------
VType& Value_Sample::vtype = VTYPE_Sample;

String Value_Sample::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetSample().ToString(ss));
}

Gurax_EndModuleScope(ml_cifar)
