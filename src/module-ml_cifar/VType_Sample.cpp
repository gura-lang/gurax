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

// ml.cifar.Sample#result:nil:[fine,super]
Gurax_DeclareProperty_R(Sample, result)
{
	Declare(VTYPE_Array, Flag::Nil);
	DeclareAttrOpt(Gurax_Symbol(fine));
	DeclareAttrOpt(Gurax_Symbol(super));
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, result)
{
	auto& sample = GetValueThis(valueTarget).GetSample();
	return !sample.GetSuperClassFlag(attr)? new Value_Array(sample.GetArrayResult().Reference()) :
		sample.HasSuperClass()? new Value_Array(sample.GetArrayResultSuper().Reference()) :
		Value::nil();
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

// ml.cifar.Sample#label:nil:[fine,super]
Gurax_DeclareProperty_R(Sample, label)
{
	Declare(VTYPE_Number, Flag::Nil);
	DeclareAttrOpt(Gurax_Symbol(fine));
	DeclareAttrOpt(Gurax_Symbol(super));
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, label)
{
	auto& sample = GetValueThis(valueTarget).GetSample();
	return !sample.GetSuperClassFlag(attr)? new Value_Number(sample.GetLabel()) :
		sample.HasSuperClass()? new Value_Number(sample.GetLabelSuper()) :
		Value::nil();
}

// ml.cifar.Sample#labelName:nil:[fine,super]
Gurax_DeclareProperty_R(Sample, labelName)
{
	Declare(VTYPE_String, Flag::Nil);
	DeclareAttrOpt(Gurax_Symbol(fine));
	DeclareAttrOpt(Gurax_Symbol(super));
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, labelName)
{
	auto& sample = GetValueThis(valueTarget).GetSample();
	return !sample.GetSuperClassFlag(attr)? new Value_String(sample.GetLabelName()) :
		sample.HasSuperClass()? new Value_String(sample.GetLabelNameSuper()) :
		Value::nil();
}

// ml.cifar.Sample#labels:nil:[fine,super]
Gurax_DeclareProperty_R(Sample, labels)
{
	Declare(VTYPE_List, Flag::Nil);
	DeclareAttrOpt(Gurax_Symbol(fine));
	DeclareAttrOpt(Gurax_Symbol(super));
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, labels)
{
	auto& sample = GetValueThis(valueTarget).GetSample();
	return !sample.GetSuperClassFlag(attr)? new Value_List(VTYPE_Number, sample.GetValuesLabel().Reference()) :
		sample.HasSuperClass()? new Value_List(VTYPE_Number, sample.GetValuesLabelSuper().Reference()) :
		Value::nil();
}

// ml.cifar.Sample#labelNames:nil:[fine,super]
Gurax_DeclareProperty_R(Sample, labelNames)
{
	Declare(VTYPE_List, Flag::Nil);
	DeclareAttrOpt(Gurax_Symbol(fine));
	DeclareAttrOpt(Gurax_Symbol(super));
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sample, labelNames)
{
	auto& sample = GetValueThis(valueTarget).GetSample();
	return !sample.GetSuperClassFlag(attr)? new Value_List(VTYPE_String, sample.GetValuesLabelName().Reference()) :
		sample.HasSuperClass()? new Value_List(VTYPE_String, sample.GetValuesLabelNameSuper().Reference()) :
		Value::nil();
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
	Assign(Gurax_CreateProperty(Sample, labelName));
	Assign(Gurax_CreateProperty(Sample, labels));
	Assign(Gurax_CreateProperty(Sample, labelNames));
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
