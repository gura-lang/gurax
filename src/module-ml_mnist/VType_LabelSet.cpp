//==============================================================================
// VType_LabelSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.mnist.LabelSet, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.mnist.LabelSet, `en)}

${help.ComposeMethodHelp(ml.mnist.LabelSet, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.mnist.LabelSet(stream as Stream):map {block?}
Gurax_DeclareConstructor(LabelSet)
{
	Declare(VTYPE_LabelSet, Flag::Map);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.mnist.LabelSet` instance.
)""");
}

Gurax_ImplementConstructor(LabelSet)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<LabelSet> pLabelSet(new LabelSet());
	if (!pLabelSet->Read(stream)) return Value::nil();
	return argument.ReturnValue(processor, new Value_LabelSet(pLabelSet.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//   oneHot = true  ... (nSamples, nLabels)
//   oneHot = false ... (nSamples)
//-----------------------------------------------------------------------------
// ml.mnist.LabelSet#ToArray(elemType? as Symbol, oneHot? as Bool):map {block?}
Gurax_DeclareMethod(LabelSet, ToArray)
{
	Declare(VTYPE_Number, Flag::Map);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("oneHot", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(LabelSet, ToArray)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Array::ElemTypeT& elemType = args.IsValid()? Array::SymbolToElemType(args.PickSymbol()) : Array::ElemType::UInt8;
	Bool oneHotFlag = args.IsValid()? args.PickBool() : false;
	if (elemType.IsNone()) {
		Error::Issue(ErrorType::ValueError, "invalid symbol for element type");
		return Value::nil();
	}
	// Function body
	RefPtr<Array> pArray(valueThis.GetLabelSet().ToArray(elemType, oneHotFlag));
	return argument.ReturnValue(processor, new Value_Array(pArray.release()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// ml.mnist.LabelSet#nSamples
Gurax_DeclareProperty_R(LabelSet, nSamples)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(LabelSet, nSamples)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetLabelSet().CountSamples());
}

// ml.mnist.LabelSet#nLabels
Gurax_DeclareProperty_R(LabelSet, nLabels)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(LabelSet, nLabels)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetLabelSet().CountLabels());
}

//------------------------------------------------------------------------------
// VType_LabelSet
//------------------------------------------------------------------------------
VType_LabelSet VTYPE_LabelSet("LabelSet");

void VType_LabelSet::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(LabelSet));
	// Assignment of method
	Assign(Gurax_CreateMethod(LabelSet, ToArray));
	// Assignment of property
	Assign(Gurax_CreateProperty(LabelSet, nSamples));
	Assign(Gurax_CreateProperty(LabelSet, nLabels));
}

//------------------------------------------------------------------------------
// Value_LabelSet
//------------------------------------------------------------------------------
VType& Value_LabelSet::vtype = VTYPE_LabelSet;

String Value_LabelSet::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetLabelSet().ToString(ss));
}

Gurax_EndModuleScope(ml_mnist)
