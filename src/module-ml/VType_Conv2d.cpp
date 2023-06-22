//==============================================================================
// VType_Conv2d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.Conv2d, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.Conv2d, `en)}

${help.ComposeMethodHelp(ml.Conv2d, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.Conv2d(filter as Array, stride? as Number, padding? as Number) {block?}
Gurax_DeclareConstructor(Conv2d)
{
	Declare(VTYPE_Conv2d, Flag::None);
	DeclareArg("filter", VTYPE_Array, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("padding", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.Conv2d` instance.
)""");
}

Gurax_ImplementConstructor(Conv2d)
{
	// Arguments
	ArgPicker args(argument);
	const Array& arrayFilter = args.Pick<Value_Array>().GetArray();
	size_t stride = args.IsValid()? args.PickNumberPos<size_t>() : 1;
	size_t padding = args.IsValid()? args.PickNumberNonNeg<size_t>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	if (!Conv2d::ValidateArrayFilter(arrayFilter)) return Value::nil();
	RefPtr<Conv2d> pConv2d(new Conv2d(arrayFilter.Reference(), stride, padding));
	return argument.ReturnValue(processor, new Value_Conv2d(pConv2d.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Conv2d#CalcSizeOut(nRowsIn as Number, nColsIn as Number) as Tuple
Gurax_DeclareMethod(Conv2d, CalcSizeOut)
{
	Declare(VTYPE_Tuple, Flag::None);
	DeclareArg("nRowsIn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nColsIn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Conv2d, CalcSizeOut)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	size_t nRowsIn = args.PickNumberPos<size_t>();
	size_t nColsIn = args.PickNumberPos<size_t>();
	// Function body
	size_t nRowsOut, nColsOut;
	valueThis.GetConv2d().CalcSizeOut(nRowsIn, nColsIn, &nRowsOut, &nColsOut);
	return Value_Tuple::Create(new Value_Number(nRowsOut), new Value_Number(nColsOut));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// ml.Conv2d#filter
Gurax_DeclareProperty_R(Conv2d, filter)
{
	Declare(VTYPE_Array, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Conv2d, filter)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Array(valueThis.GetConv2d().GetArrayFilter().Reference());
}

// ml.Conv2d#filterGrad
Gurax_DeclareProperty_R(Conv2d, filterGrad)
{
	Declare(VTYPE_Array, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Conv2d, filterGrad)
{
	auto& valueThis = GetValueThis(valueTarget);
	return valueThis.GetConv2d().IsValidArrayFilterGrad()?
		new Value_Array(valueThis.GetConv2d().GetArrayFilterGrad().Reference()) : Value::nil();
}

//------------------------------------------------------------------------------
// VType_Conv2d
//------------------------------------------------------------------------------
VType_Conv2d VTYPE_Conv2d("Conv2d");

void VType_Conv2d::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(Conv2d));
	// Assignment of method
	Assign(Gurax_CreateMethod(Conv2d, CalcSizeOut));
	// Assignment of property
	Assign(Gurax_CreateProperty(Conv2d, filter));
	Assign(Gurax_CreateProperty(Conv2d, filterGrad));
}

//------------------------------------------------------------------------------
// Value_Conv2d
//------------------------------------------------------------------------------
VType& Value_Conv2d::vtype = VTYPE_Conv2d;

String Value_Conv2d::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetConv2d().ToString(ss));
}

Gurax_EndModuleScope(ml)
