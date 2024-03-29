//==============================================================================
// VType_SampleSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.cifar.SampleSet, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.cifar.SampleSet, `en)}

${help.ComposeMethodHelp(ml.cifar.SampleSet, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.cifar.SampleSet(hasSuperClassFlag as Bool) {block?}
Gurax_DeclareConstructor(SampleSet)
{
	Declare(VTYPE_SampleSet, Flag::None);
	DeclareArg("hasSuperClassFlag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.cifar.SampleSet` instance.
)""");
}

Gurax_ImplementConstructor(SampleSet)
{
	// Arguments
	ArgPicker args(argument);
	Bool hasSuperClassFlag = args.PickBool();
	// Function body
	RefPtr<SampleSet> pSampleSet(new SampleSet(hasSuperClassFlag));
	return argument.ReturnValue(processor, new Value_SampleSet(pSampleSet.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.cifar.SampleSet#Each(elemType? as Symbol, numCeil? as Number):[fine,super] as Iterator {block?}
Gurax_DeclareMethod(SampleSet, Each)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("numCeil", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(fine));
	DeclareAttrOpt(Gurax_Symbol(super));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(SampleSet, Each)
{
	// Target
	auto& sampleSet = GetValueThis(argument).GetSampleSet();
	// Arguments
	ArgPicker args(argument);
	const Array::ElemTypeT& elemType = args.IsValid()? Array::SymbolToElemType(args.PickSymbol()) : Array::ElemType::Float;
	if (elemType.IsNone()) {
		Error::Issue(ErrorType::ValueError, "invalid symbol for element type");
		return Value::nil();
	}
	Double numCeil = args.IsValid()? args.PickNumberPos<Double>() : 1.;
	bool defaultSuperClassFlag = argument.IsSet(Gurax_Symbol(super));
	if (Error::IsIssued()) return Value::nil();
	if (defaultSuperClassFlag && !sampleSet.HasSuperClass()) {
		Error::Issue(ErrorType::ValueError, "there is no super class data");
		return Value::nil();
	}
	const Image::Format& format = Image::Format::RGBA;
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Each(sampleSet.Reference(), elemType, format, 0, numCeil, defaultSuperClassFlag));
	return argument.ReturnIterator(processor, pIterator.release());
}

// ml.cifar.SampleSet#EachBatch(elemType as Symbol, batchSize as Number, numCeil? as Number):[fine,super] as Iterator {block?}
Gurax_DeclareMethod(SampleSet, EachBatch)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("batchSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("numCeil", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(fine));
	DeclareAttrOpt(Gurax_Symbol(super));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(SampleSet, EachBatch)
{
	// Target
	auto& sampleSet = GetValueThis(argument).GetSampleSet();
	// Arguments
	ArgPicker args(argument);
	size_t batchSize = args.PickNumberPos<size_t>();
	const Array::ElemTypeT& elemType = args.IsValid()? Array::SymbolToElemType(args.PickSymbol()) : Array::ElemType::Float;
	if (elemType.IsNone()) {
		Error::Issue(ErrorType::ValueError, "invalid symbol for element type");
		return Value::nil();
	}
	Double numCeil = args.IsValid()? args.PickNumberPos<Double>() : 1.;
	bool defaultSuperClassFlag = argument.IsSet(Gurax_Symbol(super));
	if (Error::IsIssued()) return Value::nil();
	if (defaultSuperClassFlag && !sampleSet.HasSuperClass()) {
		Error::Issue(ErrorType::ValueError, "there is no super class data");
		return Value::nil();
	}
	const Image::Format& format = Image::Format::RGBA;
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Each(sampleSet.Reference(), elemType, format, batchSize, numCeil, defaultSuperClassFlag));
	return argument.ReturnIterator(processor, pIterator.release());
}

// ml.cifar.SampleSet#Get(idx as Number, elemType? as Symbol, numCeil? as Number):[fine,super] as ml.cifar.Sample {block?}
Gurax_DeclareMethod(SampleSet, Get)
{
	Declare(VTYPE_Sample, Flag::None);
	DeclareArg("idx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("numCeil", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(fine));
	DeclareAttrOpt(Gurax_Symbol(super));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(SampleSet, Get)
{
	// Target
	auto& sampleSet = GetValueThis(argument).GetSampleSet();
	// Arguments
	ArgPicker args(argument);
	size_t idx = args.PickNumberNonNeg<size_t>();
	const Array::ElemTypeT& elemType = args.IsValid()? Array::SymbolToElemType(args.PickSymbol()) : Array::ElemType::Float;
	if (elemType.IsNone()) {
		Error::Issue(ErrorType::ValueError, "invalid symbol for element type");
		return Value::nil();
	}
	Double numCeil = args.IsValid()? args.PickNumberPos<Double>() : 1.;
	bool defaultSuperClassFlag = argument.IsSet(Gurax_Symbol(super));
	if (Error::IsIssued()) return Value::nil();
	if (defaultSuperClassFlag && !sampleSet.HasSuperClass()) {
		Error::Issue(ErrorType::ValueError, "there is no super class data");
		return Value::nil();
	}
	const Image::Format& format = Image::Format::RGBA;
	// Function body
	if (idx >= sampleSet.GetNSamples()) {
		Error::Issue(ErrorType::IndexError, "index is out of range");
		return Value::nil();
	}
	RefPtr<Sample> pSample(new Sample(sampleSet.Reference(), elemType, format, 0, numCeil, idx, defaultSuperClassFlag));
	return argument.ReturnValue(processor, new Value_Sample(pSample.release()));
}

// ml.cifar.SampleSet#Read(stream as Stream):reduce
Gurax_DeclareMethod(SampleSet, Read)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(SampleSet, Read)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	if (!valueThis.GetSampleSet().Read(stream)) {
		Error::Issue(ErrorType::FormatError, "invalid format of CIFAR-10/100 file");
		return Value::nil();
	}
	return valueThis.Reference();
}

// ml.cifar.SampleSet#SetLabelNames(labelNames[] as String):reduce
Gurax_DeclareMethod(SampleSet, SetLabelNames)
{
	Declare(VTYPE_LabelSet, Flag::None);
	DeclareArg("labelNames", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(SampleSet, SetLabelNames)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	StringList labelNames = args.PickStringList();
	// Function body
	valueThis.GetSampleSet().GetLabelSet().SetLabelNames(std::move(labelNames));
	return valueThis.Reference();
}

// ml.cifar.SampleSet#SetLabelNamesSuper(labelNamesSuper[] as String):reduce
Gurax_DeclareMethod(SampleSet, SetLabelNamesSuper)
{
	Declare(VTYPE_LabelSet, Flag::None);
	DeclareArg("labelNamesSuper", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(SampleSet, SetLabelNamesSuper)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	StringList labelNamesSuper = args.PickStringList();
	// Function body
	valueThis.GetSampleSet().GetLabelSet().SetLabelNamesSuper(std::move(labelNamesSuper));
	return valueThis.Reference();
}

// ml.cifar.SampleSet#Shuffle(random? as Random):reduce
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
// ml.cifar.SampleSet#nSamples
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
	return new Value_Number(valueThis.GetSampleSet().GetNSamples());
}

// ml.cifar.SampleSet#nChannels
Gurax_DeclareProperty_R(SampleSet, nChannels)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(SampleSet, nChannels)
{
	return new Value_Number(ImageSet::nChannels);
}

// ml.cifar.SampleSet#nRows
Gurax_DeclareProperty_R(SampleSet, nRows)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(SampleSet, nRows)
{
	return new Value_Number(ImageSet::nRows);
}

// ml.cifar.SampleSet#nCols
Gurax_DeclareProperty_R(SampleSet, nCols)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(SampleSet, nCols)
{
	return new Value_Number(ImageSet::nCols);
}

// ml.cifar.SampleSet#nClasses
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

// ml.cifar.SampleSet#nClassesSuper
Gurax_DeclareProperty_R(SampleSet, nClassesSuper)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(SampleSet, nClassesSuper)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetSampleSet().GetLabelSet().GetNClassesSuper());
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
	Assign(Gurax_CreateMethod(SampleSet, Get));
	Assign(Gurax_CreateMethod(SampleSet, Read));
	Assign(Gurax_CreateMethod(SampleSet, SetLabelNames));
	Assign(Gurax_CreateMethod(SampleSet, SetLabelNamesSuper));
	Assign(Gurax_CreateMethod(SampleSet, Shuffle));
	// Assignment of property
	Assign(Gurax_CreateProperty(SampleSet, nSamples));
	Assign(Gurax_CreateProperty(SampleSet, nChannels));
	Assign(Gurax_CreateProperty(SampleSet, nRows));
	Assign(Gurax_CreateProperty(SampleSet, nCols));
	Assign(Gurax_CreateProperty(SampleSet, nClasses));
	Assign(Gurax_CreateProperty(SampleSet, nClassesSuper));
}

//------------------------------------------------------------------------------
// Value_SampleSet
//------------------------------------------------------------------------------
VType& Value_SampleSet::vtype = VTYPE_SampleSet;

String Value_SampleSet::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetSampleSet().ToString(ss));
}

Gurax_EndModuleScope(ml_cifar)
