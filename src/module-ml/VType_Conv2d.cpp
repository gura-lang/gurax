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
// ml.Conv2d(nChannelsIn as Number, nRowsIn as Number, nColsIn as Number,
//           nFilters as Number, nRowsFilter as Number, nColsFilter as Number, stride? as Number, padding? as Number,
//           elemType? as Symbol) {block?}
Gurax_DeclareConstructor(Conv2d)
{
	Declare(VTYPE_Conv2d, Flag::None);
	DeclareArg("nChannelsIn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nRowsIn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nColsIn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nFilters", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nRowsFilter", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nColsFilter", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("padding", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.Conv2d` instance.
)""");
}

Gurax_ImplementConstructor(Conv2d)
{
	// Arguments
	ArgPicker args(argument);
	size_t nChannelsIn = args.PickNumberPos<size_t>();
	size_t nRowsIn = args.PickNumberPos<size_t>();
	size_t nColsIn = args.PickNumberPos<size_t>();
	size_t nFilters = args.PickNumberPos<size_t>();
	size_t nRowsFilter = args.PickNumberPos<size_t>();
	size_t nColsFilter = args.PickNumberPos<size_t>();
	size_t stride = args.IsValid()? args.PickNumberPos<size_t>() : 1;
	size_t padding = args.IsValid()? args.PickNumberNonNeg<size_t>() : 0;
	if (Error::IsIssued()) return Value::nil();
	const Array::ElemTypeT& elemType = args.IsValid()? Array::SymbolToElemType(args.PickSymbol()) : Array::ElemType::Float;
	if (elemType.IsNone()) {
		Error::Issue(ErrorType::SymbolError, "invalid symbol for elemType");
		return Value::nil();
	}
	// Function body
	//if (!Conv2d::ValidateArrayFilter(arrayFilter)) return Value::nil();
	RefPtr<Conv2d> pConv2d(new Conv2d(nChannelsIn, nRowsIn, nColsIn, nFilters, nRowsFilter, nColsFilter, stride, padding, elemType));
	return argument.ReturnValue(processor, new Value_Conv2d(pConv2d.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
#if 0
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
#endif

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

// ml.Conv2d#nChannelsIn
Gurax_DeclareProperty_R(Conv2d, nChannelsIn)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(Conv2d, nChannelsIn)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetConv2d().GetNChannelsIn());
}

// ml.Conv2d#nRowsIn
Gurax_DeclareProperty_R(Conv2d, nRowsIn)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(Conv2d, nRowsIn)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetConv2d().GetNRowsIn());
}

// ml.Conv2d#nColsIn
Gurax_DeclareProperty_R(Conv2d, nColsIn)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(Conv2d, nColsIn)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetConv2d().GetNColsIn());
}

// ml.Conv2d#nFilters
Gurax_DeclareProperty_R(Conv2d, nFilters)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(Conv2d, nFilters)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetConv2d().GetNFilters());
}

// ml.Conv2d#nRowsFilter
Gurax_DeclareProperty_R(Conv2d, nRowsFilter)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(Conv2d, nRowsFilter)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetConv2d().GetNRowsFilter());
}

// ml.Conv2d#nColsFilter
Gurax_DeclareProperty_R(Conv2d, nColsFilter)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(Conv2d, nColsFilter)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetConv2d().GetNColsFilter());
}

// ml.Conv2d#stride
Gurax_DeclareProperty_R(Conv2d, stride)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(Conv2d, stride)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetConv2d().GetStride());
}

// ml.Conv2d#
Gurax_DeclareProperty_R(Conv2d, padding)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(Conv2d, padding)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetConv2d().GetPadding());
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
	//Assign(Gurax_CreateMethod(Conv2d, CalcSizeOut));
	// Assignment of property
	Assign(Gurax_CreateProperty(Conv2d, filter));
	Assign(Gurax_CreateProperty(Conv2d, filterGrad));
}

//------------------------------------------------------------------------------c
// Value_Conv2d
//------------------------------------------------------------------------------
VType& Value_Conv2d::vtype = VTYPE_Conv2d;

String Value_Conv2d::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetConv2d().ToString(ss));
}

bool Value_Conv2d::DoSerialize(Stream& stream) const
{
	return GetConv2d().Serialize(stream);
}

Value* VType_Conv2d::DoDeserialize(Stream& stream) const
{
	RefPtr<Conv2d> pConv2d(Conv2d::Deserialize(stream));
	return pConv2d? new Value_Conv2d(pConv2d.release()) : nullptr;
}

Gurax_EndModuleScope(ml)
