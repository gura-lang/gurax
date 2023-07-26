//==============================================================================
// VType_PairSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.mnist.PairSet, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.mnist.PairSet, `en)}

${help.ComposeMethodHelp(ml.mnist.PairSet, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.mnist.PairSet(imageSet as ml.ImageSet, labelSet as ml.LabelSet) {block?}
Gurax_DeclareConstructor(PairSet)
{
	Declare(VTYPE_PairSet, Flag::None);
	DeclareArg("imageSet", VTYPE_ImageSet, ArgOccur::Once, ArgFlag::None);
	DeclareArg("labelSet", VTYPE_LabelSet, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.mnist.PairSet` instance.
)""");
}

Gurax_ImplementConstructor(PairSet)
{
	// Arguments
	ArgPicker args(argument);
	const ImageSet& imageSet = args.Pick<Value_ImageSet>().GetImageSet();
	const LabelSet& labelSet = args.Pick<Value_LabelSet>().GetLabelSet();
	// Function body
	RefPtr<PairSet> pPairSet(new PairSet(imageSet.Reference(), labelSet.Reference()));
	return argument.ReturnValue(processor, new Value_PairSet(pPairSet.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.mnist.PairSet#Each(elemType as Symbol, batchSize as Number, numCeil? as Number) as Iterator {block?}
Gurax_DeclareMethod(PairSet, Each)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("batchSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("numCeil", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(PairSet, Each)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Array::ElemTypeT& elemType = Array::SymbolToElemType(args.PickSymbol());
	if (elemType.IsNone()) {
		Error::Issue(ErrorType::ValueError, "invalid symbol for element type");
		return Value::nil();
	}
	size_t batchSize = args.PickNumberPos<size_t>();
	Double numCeil = args.IsValid()? args.PickNumberPos<Double>() : 1.;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_EachBatch(valueThis.GetPairSet().Reference(), elemType, batchSize, numCeil));
	return argument.ReturnIterator(processor, pIterator.release());
}

// ml.mnist.PairSet#Shuffle(random? as Random):reduce
Gurax_DeclareMethod(PairSet, Shuffle)
{
	Declare(VTYPE_PairSet, Flag::Reduce);
	DeclareArg("random", VTYPE_Random, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(PairSet, Shuffle)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Random& random = args.IsValid()? args.Pick<Value_Random>().GetRandom() : Random::Global();
	// Function body
	valueThis.GetPairSet().Shuffle(random);
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// ml.mnist.PairSet#imageSet
Gurax_DeclareProperty_R(PairSet, imageSet)
{
	Declare(VTYPE_ImageSet, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(PairSet, imageSet)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_ImageSet(valueThis.GetPairSet().GetImageSet().Reference());
}

// ml.mnist.PairSet#labelSet
Gurax_DeclareProperty_R(PairSet, labelSet)
{
	Declare(VTYPE_ImageSet, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(PairSet, labelSet)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_LabelSet(valueThis.GetPairSet().GetLabelSet().Reference());
}

// ml.mnist.PairSet#nClasses
Gurax_DeclareProperty_R(PairSet, nClasses)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(PairSet, nClasses)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetPairSet().GetLabelSet().GetNClasses());
}

// ml.mnist.PairSet#nSamples
Gurax_DeclareProperty_R(PairSet, nSamples)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(PairSet, nSamples)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetPairSet().GetImageSet().GetNSamples());
}

// ml.mnist.PairSet#nRows
Gurax_DeclareProperty_R(PairSet, nRows)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(PairSet, nRows)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetPairSet().GetImageSet().GetNRows());
}

// ml.mnist.PairSet#nCols
Gurax_DeclareProperty_R(PairSet, nCols)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(PairSet, nCols)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetPairSet().GetImageSet().GetNCols());
}

//------------------------------------------------------------------------------
// VType_PairSet
//------------------------------------------------------------------------------
VType_PairSet VTYPE_PairSet("PairSet");

void VType_PairSet::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(PairSet));
	// Assignment of method
	Assign(Gurax_CreateMethod(PairSet, Shuffle));
	// Assignment of property
	Assign(Gurax_CreateProperty(PairSet, imageSet));
	Assign(Gurax_CreateProperty(PairSet, labelSet));
	Assign(Gurax_CreateProperty(PairSet, nClasses));
	Assign(Gurax_CreateProperty(PairSet, nSamples));
	Assign(Gurax_CreateProperty(PairSet, nRows));
	Assign(Gurax_CreateProperty(PairSet, nCols));
}

//------------------------------------------------------------------------------
// Value_PairSet
//------------------------------------------------------------------------------
VType& Value_PairSet::vtype = VTYPE_PairSet;

String Value_PairSet::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetPairSet().ToString(ss));
}

Gurax_EndModuleScope(ml_mnist)
