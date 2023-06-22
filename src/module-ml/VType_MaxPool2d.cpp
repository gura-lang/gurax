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
// ml.MaxPool2d(nColsKernel as Number, nRowsKernel as Number, strides? as Number) {block?}
Gurax_DeclareConstructor(MaxPool2d)
{
	Declare(VTYPE_MaxPool2d, Flag::None);
	DeclareArg("nRowsKernel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nColsKernel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("strides", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.MaxPool2d` instance.
)""");
}

Gurax_ImplementConstructor(MaxPool2d)
{
	// Arguments
	ArgPicker args(argument);
	size_t nRowsKernel = args.PickNumberPos<size_t>();
	size_t nColsKernel = args.PickNumberPos<size_t>();
	size_t strides = args.IsValid()? args.PickNumberPos<size_t>() : 1;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<MaxPool2d> pMaxPool2d(new MaxPool2d(nRowsKernel, nColsKernel, strides, strides));
	return argument.ReturnValue(processor, new Value_MaxPool2d(pMaxPool2d.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// MaxPool2d#CalcSizeOut(nRowsIn as Number, nColsIn as Number) as Tuple
Gurax_DeclareMethod(MaxPool2d, CalcSizeOut)
{
	Declare(VTYPE_Tuple, Flag::None);
	DeclareArg("nRowsIn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nColsIn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(MaxPool2d, CalcSizeOut)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	size_t nRowsIn = args.PickNumberPos<size_t>();
	size_t nColsIn = args.PickNumberPos<size_t>();
	// Function body
	size_t nRowsOut, nColsOut;
	valueThis.GetMaxPool2d().CalcSizeOut(nRowsIn, nColsIn, &nRowsOut, &nColsOut);
	return Value_Tuple::Create(new Value_Number(nRowsOut), new Value_Number(nColsOut));
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
	Assign(Gurax_CreateMethod(MaxPool2d, CalcSizeOut));
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
