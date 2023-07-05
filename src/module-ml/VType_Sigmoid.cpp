//==============================================================================
// VType_Sigmoid.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.Sigmoid, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.Sigmoid, `en)}

${help.ComposeMethodHelp(ml.Sigmoid, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.Sigmoid() {block?}
Gurax_DeclareConstructor(Sigmoid)
{
	Declare(VTYPE_Sigmoid, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.Sigmoid` instance.
)""");
}

Gurax_ImplementConstructor(Sigmoid)
{
	// Function body
	RefPtr<Sigmoid> pSigmoid(new Sigmoid());
	return argument.ReturnValue(processor, new Value_Sigmoid(pSigmoid.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.Sigmoid#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Sigmoid, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Sigmoid, MethodSkeleton)
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
// ml.Sigmoid#propSkeleton
Gurax_DeclareProperty_R(Sigmoid, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Sigmoid, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Sigmoid
//------------------------------------------------------------------------------
VType_Sigmoid VTYPE_Sigmoid("Sigmoid");

void VType_Sigmoid::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(Sigmoid));
	// Assignment of method
	Assign(Gurax_CreateMethod(Sigmoid, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Sigmoid, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Sigmoid
//------------------------------------------------------------------------------
VType& Value_Sigmoid::vtype = VTYPE_Sigmoid;

String Value_Sigmoid::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetSigmoid().ToString(ss));
}

bool Value_Sigmoid::DoSerialize(Stream& stream) const
{
	return GetSigmoid().Serialize(stream);
}

Value* VType_Sigmoid::DoDeserialize(Stream& stream) const
{
	RefPtr<Sigmoid> pSigmoid(Sigmoid::Deserialize(stream));
	return pSigmoid? new Value_Sigmoid(pSigmoid.release()) : nullptr;
}

Gurax_EndModuleScope(ml)
