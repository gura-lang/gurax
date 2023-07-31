//==============================================================================
// VType_Flatten.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.Flatten, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.Flatten, `en)}

${help.ComposeMethodHelp(ml.Flatten, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.Flatten(nDims* as Number) {block?}
Gurax_DeclareConstructor(Flatten)
{
	Declare(VTYPE_Flatten, Flag::None);
	DeclareArg("nDims", VTYPE_Number, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.Flatten` instance.
)""");
}

Gurax_ImplementConstructor(Flatten)
{
	// Arguments
	ArgPicker args(argument);
	const ValueList& valuesDimSize = args.PickList();
	// Function body
	RefPtr<ValueOwner> pValuesNDim(new ValueOwner());
	pValuesNDim->reserve(valuesDimSize.size());
	for (Value* pValue : valuesDimSize) pValuesNDim->push_back(pValue->Reference());
	RefPtr<Flatten> pFlatten(new Flatten(pValuesNDim.release()));
	return argument.ReturnValue(processor, new Value_Flatten(pFlatten.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.Flatten#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Flatten, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Flatten, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// ml.Flatten#propSkeleton
Gurax_DeclareProperty_R(Flatten, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Flatten, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Flatten
//------------------------------------------------------------------------------
VType_Flatten VTYPE_Flatten("Flatten");

void VType_Flatten::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(Flatten));
	// Assignment of method
	Assign(Gurax_CreateMethod(Flatten, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Flatten, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Flatten
//------------------------------------------------------------------------------
VType& Value_Flatten::vtype = VTYPE_Flatten;

String Value_Flatten::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetFlatten().ToString(ss));
}

bool Value_Flatten::DoSerialize(Stream& stream) const
{
	return GetFlatten().Serialize(stream);
}

Value* VType_Flatten::DoDeserialize(Stream& stream) const
{
	RefPtr<Flatten> pFlatten(Flatten::Deserialize(stream));
	return pFlatten? new Value_Flatten(pFlatten.release()) : nullptr;
}

Gurax_EndModuleScope(ml)
