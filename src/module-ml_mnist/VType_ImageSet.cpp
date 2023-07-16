//==============================================================================
// VType_ImageSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.mnist.ImageSet, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.mnist.ImageSet, `en)}

${help.ComposeMethodHelp(ml.mnist.ImageSet, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.mnist.ImageSet(stream as Stream):map {block?}
Gurax_DeclareConstructor(ImageSet)
{
	Declare(VTYPE_ImageSet, Flag::Map);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.mnist.ImageSet` instance.
)""");
}

Gurax_ImplementConstructor(ImageSet)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<ImageSet> pImageSet(new ImageSet());
	if (!pImageSet->Read(stream)) return Value::nil();
	return argument.ReturnValue(processor, new Value_ImageSet(pImageSet.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//   flatten = false ... (nSamples, nRows, nCols)
//   flatten = true  ... (nSamples, nRows * nCols)
//-----------------------------------------------------------------------------
// ml.mnist.ImageSet#ToArray(elemType? as Symbol, flatten? as Bool, numCeil? as Number):map {block?}
Gurax_DeclareMethod(ImageSet, ToArray)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("flatten", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("numCeil", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(ImageSet, ToArray)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Array::ElemTypeT& elemType = args.IsValid()? Array::SymbolToElemType(args.PickSymbol()) : Array::ElemType::UInt8;
	Bool flattenFlag = args.IsValid()? args.PickBool() : false;
	Float numCeil = args.IsValid()? args.PickNumber<Float>() : 0;
	if (elemType.IsNone()) {
		Error::Issue(ErrorType::ValueError, "invalid symbol for element type");
		return Value::nil();
	}
	// Function body
	RefPtr<Array> pArray(valueThis.GetImageSet().Extract(elemType, 0, 0, flattenFlag, numCeil));
	return argument.ReturnValue(processor, new Value_Array(pArray.release()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// ml.mnist.ImageSet#nSamples
Gurax_DeclareProperty_R(ImageSet, nSamples)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(ImageSet, nSamples)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetImageSet().GetNSamples());
}

// ml.mnist.ImageSet#nRows
Gurax_DeclareProperty_R(ImageSet, nRows)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(ImageSet, nRows)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetImageSet().GetNRows());
}

// ml.mnist.ImageSet#nCols
Gurax_DeclareProperty_R(ImageSet, nCols)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(ImageSet, nCols)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetImageSet().GetNCols());
}

//------------------------------------------------------------------------------
// VType_ImageSet
//------------------------------------------------------------------------------
VType_ImageSet VTYPE_ImageSet("ImageSet");

void VType_ImageSet::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(ImageSet));
	// Assignment of method
	Assign(Gurax_CreateMethod(ImageSet, ToArray));
	// Assignment of property
	Assign(Gurax_CreateProperty(ImageSet, nSamples));
	Assign(Gurax_CreateProperty(ImageSet, nRows));
	Assign(Gurax_CreateProperty(ImageSet, nCols));
}

//------------------------------------------------------------------------------
// Value_ImageSet
//------------------------------------------------------------------------------
VType& Value_ImageSet::vtype = VTYPE_ImageSet;

String Value_ImageSet::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetImageSet().ToString(ss));
}

Gurax_EndModuleScope(ml_mnist)
