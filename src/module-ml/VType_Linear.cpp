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
// ml.Linear(nColsOut as Number, elemType? as Symbol):[noBias] {block?}
Gurax_DeclareConstructor(Linear)
{
	Declare(VTYPE_Linear, Flag::None);
	DeclareArg("nColsOut", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(noBias));
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
	bool enableBiasFlag = !argument.IsSet(Gurax_Symbol(noBias));
	// Function body
	RefPtr<Linear> pLinear(new Linear(nColsOut, elemType, enableBiasFlag));
	//if (noBiasFlag) pLinear->SetArrayBias(Array::CreateNone());
	return argument.ReturnValue(processor, new Value_Linear(pLinear.release()));
}

//-----------------------------------------------------------------------------
// Implementation of class method
//-----------------------------------------------------------------------------
// Linear.Preset(weight as Array, bias? as Array):[noBias] {block?}
Gurax_DeclareClassMethod(Linear, Preset)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("weight", VTYPE_Array, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bias", VTYPE_Array, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(noBias));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
}

Gurax_ImplementClassMethod(Linear, Preset)
{
	// Arguments
	ArgPicker args(argument);
	const Array& arrayWeight = args.Pick<Value_Array>().GetArray();
	RefPtr<Array> pArrayBias(args.IsValid()? args.Pick<Value_Array>().GetArray().Reference() : Array::none());
	bool enableBiasFlag = !argument.IsSet(Gurax_Symbol(noBias));
	// Function body
	RefPtr<Linear> pLinear(new Linear(arrayWeight.Reference(), pArrayBias.release(), enableBiasFlag));
	return argument.ReturnValue(processor, new Value_Linear(pLinear.release()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
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
	return linear.HasArrayWeight()? linear.GetArrayWeight().ToValue() : Value::nil();
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
	return linear.HasArrayWeightGrad()? linear.GetArrayWeightGrad().ToValue() : Value::nil();
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
	return linear.HasArrayBias()? linear.GetArrayBias().ToValue() : Value::nil();
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
	return linear.HasArrayBiasGrad()? linear.GetArrayBiasGrad().ToValue() : Value::nil();
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
	// Assignment of class method
	Assign(Gurax_CreateClassMethod(Linear, Preset));
	// Assignment of property
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
