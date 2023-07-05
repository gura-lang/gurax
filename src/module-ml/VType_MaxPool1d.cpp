//==============================================================================
// VType_MaxPool1d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.MaxPool1d, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.MaxPool1d, `en)}

${help.ComposeMethodHelp(ml.MaxPool1d, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.MaxPool1d(nColsKernel as Number, nRowsKernel as Number, stride? as Number) {block?}
Gurax_DeclareConstructor(MaxPool1d)
{
	Declare(VTYPE_MaxPool1d, Flag::None);
	DeclareArg("nRowsKernel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nColsKernel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.MaxPool1d` instance.
)""");
}

Gurax_ImplementConstructor(MaxPool1d)
{
	// Arguments
	ArgPicker args(argument);
	size_t nRowsKernel = args.PickNumberPos<size_t>();
	size_t nColsKernel = args.PickNumberPos<size_t>();
	size_t stride = args.IsValid()? args.PickNumberPos<size_t>() : 1;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<MaxPool1d> pMaxPool1d(new MaxPool1d(nRowsKernel, nColsKernel, stride, stride));
	return argument.ReturnValue(processor, new Value_MaxPool1d(pMaxPool1d.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// MaxPool1d#CalcSizeOut(nRowsIn as Number, nColsIn as Number) as Tuple
Gurax_DeclareMethod(MaxPool1d, CalcSizeOut)
{
	Declare(VTYPE_Tuple, Flag::None);
	DeclareArg("nRowsIn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nColsIn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(MaxPool1d, CalcSizeOut)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	size_t nRowsIn = args.PickNumberPos<size_t>();
	size_t nColsIn = args.PickNumberPos<size_t>();
	// Function body
	size_t nRowsOut, nColsOut;
	valueThis.GetMaxPool1d().CalcSizeOut(nRowsIn, nColsIn, &nRowsOut, &nColsOut);
	return Value_Tuple::Create(new Value_Number(nRowsOut), new Value_Number(nColsOut));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// ml.MaxPool1d#propSkeleton
Gurax_DeclareProperty_R(MaxPool1d, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(MaxPool1d, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_MaxPool1d
//------------------------------------------------------------------------------
VType_MaxPool1d VTYPE_MaxPool1d("MaxPool1d");

void VType_MaxPool1d::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(MaxPool1d));
	// Assignment of method
	Assign(Gurax_CreateMethod(MaxPool1d, CalcSizeOut));
	// Assignment of property
	Assign(Gurax_CreateProperty(MaxPool1d, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_MaxPool1d
//------------------------------------------------------------------------------
VType& Value_MaxPool1d::vtype = VTYPE_MaxPool1d;

String Value_MaxPool1d::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetMaxPool1d().ToString(ss));
}

Gurax_EndModuleScope(ml)
