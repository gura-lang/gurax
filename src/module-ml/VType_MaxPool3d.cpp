//==============================================================================
// VType_MaxPool3d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.MaxPool3d, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.MaxPool3d, `en)}

${help.ComposeMethodHelp(ml.MaxPool3d, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.MaxPool3d(nColsKernel as Number, nRowsKernel as Number, stride? as Number) {block?}
Gurax_DeclareConstructor(MaxPool3d)
{
	Declare(VTYPE_MaxPool3d, Flag::None);
	DeclareArg("nRowsKernel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nColsKernel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.MaxPool3d` instance.
)""");
}

Gurax_ImplementConstructor(MaxPool3d)
{
	// Arguments
	ArgPicker args(argument);
	size_t nRowsKernel = args.PickNumberPos<size_t>();
	size_t nColsKernel = args.PickNumberPos<size_t>();
	size_t stride = args.IsValid()? args.PickNumberPos<size_t>() : 1;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<MaxPool3d> pMaxPool3d(new MaxPool3d(nRowsKernel, nColsKernel, stride, stride));
	return argument.ReturnValue(processor, new Value_MaxPool3d(pMaxPool3d.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// MaxPool3d#CalcSizeOut(nRowsIn as Number, nColsIn as Number) as Tuple
Gurax_DeclareMethod(MaxPool3d, CalcSizeOut)
{
	Declare(VTYPE_Tuple, Flag::None);
	DeclareArg("nRowsIn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nColsIn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(MaxPool3d, CalcSizeOut)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	size_t nRowsIn = args.PickNumberPos<size_t>();
	size_t nColsIn = args.PickNumberPos<size_t>();
	// Function body
	size_t nRowsOut, nColsOut;
	valueThis.GetMaxPool3d().CalcSizeOut(nRowsIn, nColsIn, &nRowsOut, &nColsOut);
	return Value_Tuple::Create(new Value_Number(nRowsOut), new Value_Number(nColsOut));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// ml.MaxPool3d#propSkeleton
Gurax_DeclareProperty_R(MaxPool3d, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(MaxPool3d, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_MaxPool3d
//------------------------------------------------------------------------------
VType_MaxPool3d VTYPE_MaxPool3d("MaxPool3d");

void VType_MaxPool3d::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(MaxPool3d));
	// Assignment of method
	Assign(Gurax_CreateMethod(MaxPool3d, CalcSizeOut));
	// Assignment of property
	Assign(Gurax_CreateProperty(MaxPool3d, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_MaxPool3d
//------------------------------------------------------------------------------
VType& Value_MaxPool3d::vtype = VTYPE_MaxPool3d;

String Value_MaxPool3d::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetMaxPool3d().ToString(ss));
}

Gurax_EndModuleScope(ml)
