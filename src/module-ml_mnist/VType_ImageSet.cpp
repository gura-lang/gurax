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
//-----------------------------------------------------------------------------
// ml.mnist.ImageSet#ToArray(shape? as Symbol, elemType? as Symbol, normalize? as Bool):map {block?}
Gurax_DeclareMethod(ImageSet, ToArray)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("shape", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("normalize", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
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
	const Symbol* pSymbolShape = args.IsValid()? args.PickSymbol() : Gurax_Symbol(flat);
	const Symbol* pSymbolElemType = args.IsValid()? args.PickSymbol() : Gurax_Symbol(float_);
	bool normalizeFlag = args.IsValid()? args.PickBool() : true;
	bool flattenFlag = true;
	if (pSymbolShape->IsIdentical(Gurax_Symbol(flat))) {
		flattenFlag = true;
	} else if (pSymbolShape->IsIdentical(Gurax_Symbol(matrix))) {
		flattenFlag = false;
	} else {
		Error::Issue(ErrorType::ValueError, "argument shape takes `` `flat` or `` `matrix``");
		return Value::nil();
	}
	const Array::ElemTypeT& elemType = Array::SymbolToElemType(pSymbolElemType);
	if (elemType.IsNone()) {
		
	}
	// Function body
	valueThis.GetImageSet().ToArray(flattenFlag, elemType, normalizeFlag);
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// ml.mnist.ImageSet#nImages
Gurax_DeclareProperty_R(ImageSet, nImages)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(ImageSet, nImages)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetImageSet().CountImages());
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
	Assign(Gurax_CreateProperty(ImageSet, nImages));
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
