//==============================================================================
// VType_Cifar.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.cifar.Cifar, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.cifar.Cifar, `en)}

${help.ComposeMethodHelp(ml.cifar.Cifar, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.cifar.Cifar() {block?}
Gurax_DeclareConstructor(Cifar)
{
	Declare(VTYPE_Cifar, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.cifar.Cifar` instance.
)""");
}

Gurax_ImplementConstructor(Cifar)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Cifar> pCifar(new Cifar(false));
	return argument.ReturnValue(processor, new Value_Cifar(pCifar.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.cifar.Cifar#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Cifar, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Cifar, MethodSkeleton)
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
// ml.cifar.Cifar#propSkeleton
Gurax_DeclareProperty_R(Cifar, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Cifar, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Cifar
//------------------------------------------------------------------------------
VType_Cifar VTYPE_Cifar("Cifar");

void VType_Cifar::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Cifar));
	// Assignment of method
	Assign(Gurax_CreateMethod(Cifar, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Cifar, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Cifar
//------------------------------------------------------------------------------
VType& Value_Cifar::vtype = VTYPE_Cifar;

String Value_Cifar::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetCifar().ToString(ss));
}

Gurax_EndModuleScope(ml_cifar)
