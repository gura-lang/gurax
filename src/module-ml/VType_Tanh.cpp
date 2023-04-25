//==============================================================================
// VType_Tanh.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.Tanh, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.Tanh, `en)}

${help.ComposeMethodHelp(ml.Tanh, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.Tanh() {block?}
Gurax_DeclareConstructor(Tanh)
{
	Declare(VTYPE_Tanh, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.Tanh` instance.
)""");
}

Gurax_ImplementConstructor(Tanh)
{
	// Function body
	RefPtr<Tanh> pTanh(new Tanh());
	return argument.ReturnValue(processor, new Value_Tanh(pTanh.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.Tanh#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Tanh, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Tanh, MethodSkeleton)
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
// ml.Tanh#propSkeleton
Gurax_DeclareProperty_R(Tanh, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Tanh, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Tanh
//------------------------------------------------------------------------------
VType_Tanh VTYPE_Tanh("Tanh");

void VType_Tanh::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(Tanh));
	// Assignment of method
	Assign(Gurax_CreateMethod(Tanh, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Tanh, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Tanh
//------------------------------------------------------------------------------
VType& Value_Tanh::vtype = VTYPE_Tanh;

String Value_Tanh::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetTanh().ToString(ss));
}

Gurax_EndModuleScope(ml)
