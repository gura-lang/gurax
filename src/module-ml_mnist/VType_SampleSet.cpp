//==============================================================================
// VType_SampleSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.mnist.SampleSet, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.mnist.SampleSet, `en)}

${help.ComposeMethodHelp(ml.mnist.SampleSet, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.mnist.SampleSet(imageSet as ml.ImageSet, labelSet as ml.LabelSet) {block?}
Gurax_DeclareConstructor(SampleSet)
{
	Declare(VTYPE_SampleSet, Flag::None);
	DeclareArg("imageSet", VTYPE_ImageSet, ArgOccur::Once, ArgFlag::None);
	DeclareArg("labelSet", VTYPE_LabelSet, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.mnist.SampleSet` instance.
)""");
}

Gurax_ImplementConstructor(SampleSet)
{
	// Arguments
	ArgPicker args(argument);
	const ImageSet& imageSet = args.Pick<Value_ImageSet>().GetImageSet();
	const LabelSet& labelSet = args.Pick<Value_LabelSet>().GetLabelSet();
	// Function body
	RefPtr<SampleSet> pSampleSet(new SampleSet(imageSet.Reference(), labelSet.Reference()));
	return argument.ReturnValue(processor, new Value_SampleSet(pSampleSet.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.mnist.SampleSet#Each(elemType as Symbol, numCeil? as Number) as Iterator {block?}
Gurax_DeclareMethod(SampleSet, Each)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("numCeil", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(SampleSet, Each)
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
	Double numCeil = args.IsValid()? args.PickNumberPos<Double>() : 1.;
	if (Error::IsIssued()) return Value::nil();
	const Image::Format& format = Image::Format::RGBA;
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Each(valueThis.GetSampleSet().Reference(), elemType, format, 0, numCeil));
	return argument.ReturnIterator(processor, pIterator.release());
}

// ml.mnist.SampleSet#EachBatch(elemType as Symbol, batchSize as Number, numCeil? as Number) as Iterator {block?}
Gurax_DeclareMethod(SampleSet, EachBatch)
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

Gurax_ImplementMethod(SampleSet, EachBatch)
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
	const Image::Format& format = Image::Format::RGBA;
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Each(valueThis.GetSampleSet().Reference(), elemType, format, batchSize, numCeil));
	return argument.ReturnIterator(processor, pIterator.release());
}

// ml.mnist.SampleSet#Shuffle(random? as Random):reduce
Gurax_DeclareMethod(SampleSet, Shuffle)
{
	Declare(VTYPE_SampleSet, Flag::Reduce);
	DeclareArg("random", VTYPE_Random, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(SampleSet, Shuffle)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Random& random = args.IsValid()? args.Pick<Value_Random>().GetRandom() : Random::Global();
	// Function body
	valueThis.GetSampleSet().Shuffle(random);
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// ml.mnist.SampleSet#imageSet
Gurax_DeclareProperty_R(SampleSet, imageSet)
{
	Declare(VTYPE_ImageSet, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(SampleSet, imageSet)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_ImageSet(valueThis.GetSampleSet().GetImageSet().Reference());
}

// ml.mnist.SampleSet#labelSet
Gurax_DeclareProperty_R(SampleSet, labelSet)
{
	Declare(VTYPE_ImageSet, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(SampleSet, labelSet)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_LabelSet(valueThis.GetSampleSet().GetLabelSet().Reference());
}

// ml.mnist.SampleSet#nClasses
Gurax_DeclareProperty_R(SampleSet, nClasses)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(SampleSet, nClasses)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetSampleSet().GetLabelSet().GetNClasses());
}

// ml.mnist.SampleSet#nSamples
Gurax_DeclareProperty_R(SampleSet, nSamples)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(SampleSet, nSamples)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetSampleSet().GetImageSet().GetNSamples());
}

// ml.mnist.SampleSet#nRows
Gurax_DeclareProperty_R(SampleSet, nRows)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(SampleSet, nRows)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetSampleSet().GetImageSet().GetNRows());
}

// ml.mnist.SampleSet#nCols
Gurax_DeclareProperty_R(SampleSet, nCols)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(SampleSet, nCols)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetSampleSet().GetImageSet().GetNCols());
}

//------------------------------------------------------------------------------
// VType_SampleSet
//------------------------------------------------------------------------------
VType_SampleSet VTYPE_SampleSet("SampleSet");

void VType_SampleSet::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(SampleSet));
	// Assignment of method
	Assign(Gurax_CreateMethod(SampleSet, Each));
	Assign(Gurax_CreateMethod(SampleSet, EachBatch));
	Assign(Gurax_CreateMethod(SampleSet, Shuffle));
	// Assignment of property
	Assign(Gurax_CreateProperty(SampleSet, imageSet));
	Assign(Gurax_CreateProperty(SampleSet, labelSet));
	Assign(Gurax_CreateProperty(SampleSet, nClasses));
	Assign(Gurax_CreateProperty(SampleSet, nSamples));
	Assign(Gurax_CreateProperty(SampleSet, nRows));
	Assign(Gurax_CreateProperty(SampleSet, nCols));
}

//------------------------------------------------------------------------------
// Value_SampleSet
//------------------------------------------------------------------------------
VType& Value_SampleSet::vtype = VTYPE_SampleSet;

String Value_SampleSet::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetSampleSet().ToString(ss));
}

Gurax_EndModuleScope(ml_mnist)
