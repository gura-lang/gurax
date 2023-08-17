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
// ml.cifar.Sample#hasSuperClass
Gurax_DeclareProperty_R(Sample, hasSuperClass)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, hasSuperClass)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetSample().HasSuperClass());
}

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

// ml.cifar.Sample#labelSuper:nil
Gurax_DeclareProperty_R(Sample, labelSuper)
{
	Declare(VTYPE_Number, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, labelSuper)
{
	auto& valueThis = GetValueThis(valueTarget);
	if (!valueThis.GetSample().HasSuperClass()) return Value::nil();
	return new Value_Number(valueThis.GetSample().GetLabelSuper());
}

// ml.cifar.Sample#labelName
Gurax_DeclareProperty_R(Sample, labelName)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, labelName)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetSample().GetLabelName());
}

// ml.cifar.Sample#labelNameSuper:nil
Gurax_DeclareProperty_R(Sample, labelNameSuper)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, labelNameSuper)
{
	auto& valueThis = GetValueThis(valueTarget);
	if (!valueThis.GetSample().HasSuperClass()) return Value::nil();
	return new Value_String(valueThis.GetSample().GetLabelNameSuper());
}

// ml.cifar.Sample#labels
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

// ml.cifar.Sample#labelsSuper:nil
Gurax_DeclareProperty_R(Sample, labelsSuper)
{
	Declare(VTYPE_List, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, labelsSuper)
{
	auto& valueThis = GetValueThis(valueTarget);
	if (!valueThis.GetSample().HasSuperClass()) return Value::nil();
	return new Value_List(VTYPE_Number, valueThis.GetSample().GetValuesLabelSuper().Reference());
}

// ml.cifar.Sample#labelNames
Gurax_DeclareProperty_R(Sample, labelNames)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, labelNames)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_List(VTYPE_Number, valueThis.GetSample().GetValuesLabelName().Reference());
}

// ml.cifar.Sample#labelNamesSuper:nil
Gurax_DeclareProperty_R(Sample, labelNamesSuper)
{
	Declare(VTYPE_List, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, labelNamesSuper)
{
	auto& valueThis = GetValueThis(valueTarget);
	if (!valueThis.GetSample().HasSuperClass()) return Value::nil();
	return new Value_List(VTYPE_Number, valueThis.GetSample().GetValuesLabelNameSuper().Reference());
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
	Assign(Gurax_CreateProperty(Sample, hasSuperClass));
	Assign(Gurax_CreateProperty(Sample, input));
	Assign(Gurax_CreateProperty(Sample, result));
	Assign(Gurax_CreateProperty(Sample, image));
	Assign(Gurax_CreateProperty(Sample, label));
	Assign(Gurax_CreateProperty(Sample, labelSuper));
	Assign(Gurax_CreateProperty(Sample, labelName));
	Assign(Gurax_CreateProperty(Sample, labelNameSuper));
	Assign(Gurax_CreateProperty(Sample, labels));
	Assign(Gurax_CreateProperty(Sample, labelsSuper));
	Assign(Gurax_CreateProperty(Sample, labelNames));
	Assign(Gurax_CreateProperty(Sample, labelNamesSuper));
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
