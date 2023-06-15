//==============================================================================
// VType_MaxPool2d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.MaxPool2d, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.MaxPool2d, `en)}

${help.ComposeMethodHelp(ml.MaxPool2d, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.MaxPool2d(arrayFilter as Array, strides? as Number, padding? as Number) {block?}
Gurax_DeclareConstructor(MaxPool2d)
{
	Declare(VTYPE_MaxPool2d, Flag::None);
	DeclareArg("arrayFilter", VTYPE_Array, ArgOccur::Once, ArgFlag::None);
	DeclareArg("strides", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("padding", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.MaxPool2d` instance.
)""");
}

Gurax_ImplementConstructor(MaxPool2d)
{
	// Arguments
	ArgPicker args(argument);
	const Array& arrayFilter = args.Pick<Value_Array>().GetArray();
	size_t strides = args.IsValid()? args.PickNumberPos<size_t>() : 1;
	size_t padding = args.IsValid()? args.PickNumberNonNeg<size_t>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	if (!MaxPool2d::ValidateArrayFilter(arrayFilter)) return Value::nil();
	RefPtr<MaxPool2d> pMaxPool2d(new MaxPool2d(arrayFilter.Reference(), strides, padding));
	return argument.ReturnValue(processor, new Value_MaxPool2d(pMaxPool2d.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.MaxPool2d#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(MaxPool2d, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(MaxPool2d, MethodSkeleton)
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
// ml.MaxPool2d#propSkeleton
Gurax_DeclareProperty_R(MaxPool2d, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(MaxPool2d, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_MaxPool2d
//------------------------------------------------------------------------------
VType_MaxPool2d VTYPE_MaxPool2d("MaxPool2d");

void VType_MaxPool2d::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(MaxPool2d));
	// Assignment of method
	Assign(Gurax_CreateMethod(MaxPool2d, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(MaxPool2d, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_MaxPool2d
//------------------------------------------------------------------------------
VType& Value_MaxPool2d::vtype = VTYPE_MaxPool2d;

String Value_MaxPool2d::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetMaxPool2d().ToString(ss));
}

Gurax_EndModuleScope(ml)
