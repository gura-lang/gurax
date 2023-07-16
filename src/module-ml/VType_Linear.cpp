//==============================================================================
// VType_Linear.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.Linear, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.Linear, `en)}

${help.ComposeMethodHelp(ml.Linear, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.Linear(nColsOut as Number, elemType? as Symbol) {block?}
Gurax_DeclareConstructor(Linear)
{
	Declare(VTYPE_Linear, Flag::None);
	DeclareArg("nColsOut", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
}

Gurax_ImplementConstructor(Linear)
{
	// Arguments
	ArgPicker args(argument);
	size_t nColsOut = args.PickNumberPos<size_t>();
	if (Error::IsIssued()) return Value::nil();
	const Array::ElemTypeT& elemType = args.IsValid()? Array::SymbolToElemType(args.PickSymbol()) : Array::ElemType::Float;
	if (elemType.IsNone()) {
		Error::Issue(ErrorType::SymbolError, "invalid symbol for elemType");
		return Value::nil();
	}
	// Function body
	RefPtr<Linear> pLinear(new Linear(nColsOut, elemType));
	return argument.ReturnValue(processor, new Value_Linear(pLinear.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
#if 0
// ml.Linear#nColsIn
Gurax_DeclareProperty_R(Linear, nColsIn)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(Linear, nColsIn)
{
	auto& linear = GetValueThis(valueTarget).GetLinear();
	return new Value_Number(linear.GetNColsIn());
}
#endif

// ml.Linear#nColsOut
Gurax_DeclareProperty_R(Linear, nColsOut)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(Linear, nColsOut)
{
	auto& linear = GetValueThis(valueTarget).GetLinear();
	return new Value_Number(linear.GetNColsOut());
}

// ml.Linear#weight
Gurax_DeclareProperty_R(Linear, weight)
{
	Declare(VTYPE_Array, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Linear, weight)
{
	auto& linear = GetValueThis(valueTarget).GetLinear();
	return linear.HasArrayWeight()? new Value_Array(linear.GetArrayWeight().Reference()) : Value::nil();
}

// ml.Linear#weightGrad
Gurax_DeclareProperty_R(Linear, weightGrad)
{
	Declare(VTYPE_Array, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Linear, weightGrad)
{
	auto& linear = GetValueThis(valueTarget).GetLinear();
	return linear.HasArrayWeightGrad()? new Value_Array(linear.GetArrayWeightGrad().Reference()) : Value::nil();
}

// ml.Linear#bias
Gurax_DeclareProperty_R(Linear, bias)
{
	Declare(VTYPE_Array, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Linear, bias)
{
	auto& linear = GetValueThis(valueTarget).GetLinear();
	return linear.HasArrayBias()? new Value_Array(linear.GetArrayBias().Reference()) : Value::nil();
}

// ml.Linear#biasGrad
Gurax_DeclareProperty_R(Linear, biasGrad)
{
	Declare(VTYPE_Array, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Linear, biasGrad)
{
	auto& linear = GetValueThis(valueTarget).GetLinear();
	return linear.HasArrayBiasGrad()? new Value_Array(linear.GetArrayBiasGrad().Reference()) : Value::nil();
}

//------------------------------------------------------------------------------
// VType_Linear
//------------------------------------------------------------------------------
VType_Linear VTYPE_Linear("Linear");

void VType_Linear::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(Linear));
	// Assignment of method
	// Assignment of property
	//Assign(Gurax_CreateProperty(Linear, nColsIn));
	Assign(Gurax_CreateProperty(Linear, nColsOut));
	Assign(Gurax_CreateProperty(Linear, weight));
	Assign(Gurax_CreateProperty(Linear, weightGrad));
	Assign(Gurax_CreateProperty(Linear, bias));
	Assign(Gurax_CreateProperty(Linear, biasGrad));
}

//------------------------------------------------------------------------------c
// Value_Linear
//------------------------------------------------------------------------------
VType& Value_Linear::vtype = VTYPE_Linear;

String Value_Linear::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetLinear().ToString(ss));
}

bool Value_Linear::DoSerialize(Stream& stream) const
{
	return GetLinear().Serialize(stream);
}

Value* VType_Linear::DoDeserialize(Stream& stream) const
{
	RefPtr<Linear> pLinear(Linear::Deserialize(stream));
	return pLinear? new Value_Linear(pLinear.release()) : nullptr;
}

Gurax_EndModuleScope(ml)