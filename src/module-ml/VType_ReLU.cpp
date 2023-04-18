//==============================================================================
// VType_ReLU.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.ReLU, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.ReLU, `en)}

${help.ComposeMethodHelp(ml.ReLU, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.ReLU() {block?}
Gurax_DeclareConstructor(ReLU)
{
	Declare(VTYPE_ReLU, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.ReLU` instance.
)""");
}

Gurax_ImplementConstructor(ReLU)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<ReLU> pReLU(new ReLU());
	return argument.ReturnValue(processor, new Value_ReLU(pReLU.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.ReLU#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(ReLU, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(ReLU, MethodSkeleton)
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
// ml.ReLU#propSkeleton
Gurax_DeclareProperty_R(ReLU, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(ReLU, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_ReLU
//------------------------------------------------------------------------------
VType_ReLU VTYPE_ReLU("ReLU");

void VType_ReLU::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(ReLU));
	// Assignment of method
	Assign(Gurax_CreateMethod(ReLU, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(ReLU, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_ReLU
//------------------------------------------------------------------------------
VType& Value_ReLU::vtype = VTYPE_ReLU;

String Value_ReLU::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetReLU().ToString(ss));
}

Gurax_EndModuleScope(ml)
