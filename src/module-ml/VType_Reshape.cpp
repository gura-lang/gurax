//==============================================================================
// VType_Reshape.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.Reshape, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.Reshape, `en)}

${help.ComposeMethodHelp(ml.Reshape, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.Reshape(dimSizes:nil+ as Number) {block?}
Gurax_DeclareConstructor(Reshape)
{
	Declare(VTYPE_Reshape, Flag::None);
	DeclareArg("dimSizes", VTYPE_Number, ArgOccur::OnceOrMore, ArgFlag::Nil);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.Reshape` instance.
)""");
}

Gurax_ImplementConstructor(Reshape)
{
	// Arguments
	ArgPicker args(argument);
	const ValueList& valuesDimSize = args.PickList();
	// Function body
	RefPtr<ValueOwner> pValuesDimSize(new ValueOwner());
	pValuesDimSize->reserve(valuesDimSize.size());
	for (Value* pValue : valuesDimSize) pValuesDimSize->push_back(pValue->Reference());
	RefPtr<Reshape> pReshape(new Reshape(pValuesDimSize.release()));
	return argument.ReturnValue(processor, new Value_Reshape(pReshape.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.Reshape#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Reshape, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Reshape, MethodSkeleton)
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
// ml.Reshape#propSkeleton
Gurax_DeclareProperty_R(Reshape, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Reshape, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Reshape
//------------------------------------------------------------------------------
VType_Reshape VTYPE_Reshape("Reshape");

void VType_Reshape::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(Reshape));
	// Assignment of method
	Assign(Gurax_CreateMethod(Reshape, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Reshape, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Reshape
//------------------------------------------------------------------------------
VType& Value_Reshape::vtype = VTYPE_Reshape;

String Value_Reshape::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetReshape().ToString(ss));
}

bool Value_Reshape::DoSerialize(Stream& stream) const
{
	return GetReshape().Serialize(stream);
}

Value* VType_Reshape::DoDeserialize(Stream& stream) const
{
	RefPtr<Reshape> pReshape(Reshape::Deserialize(stream));
	return pReshape? new Value_Reshape(pReshape.release()) : nullptr;
}

Gurax_EndModuleScope(ml)
