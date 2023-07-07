//==============================================================================
// VType_Dropout.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.Dropout, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.Dropout, `en)}

${help.ComposeMethodHelp(ml.Dropout, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.Dropout(rate as Number) {block?}
Gurax_DeclareConstructor(Dropout)
{
	Declare(VTYPE_Dropout, Flag::None);
	DeclareArg("rate", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.Dropout` instance.
)""");
}

Gurax_ImplementConstructor(Dropout)
{
	// Arguments
	ArgPicker args(argument);
	Double rate = args.PickNumber<Double>();
	// Function body
	RefPtr<Dropout> pDropout(new Dropout(rate));
	return argument.ReturnValue(processor, new Value_Dropout(pDropout.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.Dropout#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Dropout, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Dropout, MethodSkeleton)
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
// ml.Dropout#propSkeleton
Gurax_DeclareProperty_R(Dropout, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Dropout, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Dropout
//------------------------------------------------------------------------------
VType_Dropout VTYPE_Dropout("Dropout");

void VType_Dropout::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(Dropout));
	// Assignment of method
	Assign(Gurax_CreateMethod(Dropout, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Dropout, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Dropout
//------------------------------------------------------------------------------
VType& Value_Dropout::vtype = VTYPE_Dropout;

String Value_Dropout::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetDropout().ToString(ss));
}

bool Value_Dropout::DoSerialize(Stream& stream) const
{
	return GetDropout().Serialize(stream);
}

Value* VType_Dropout::DoDeserialize(Stream& stream) const
{
	RefPtr<Dropout> pDropout(Dropout::Deserialize(stream));
	return pDropout? new Value_Dropout(pDropout.release()) : nullptr;
}

Gurax_EndModuleScope(ml)
