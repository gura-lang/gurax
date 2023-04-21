//==============================================================================
// VType_Softmax.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.Softmax, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.Softmax, `en)}

${help.ComposeMethodHelp(ml.Softmax, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.Softmax() {block?}
Gurax_DeclareConstructor(Softmax)
{
	Declare(VTYPE_Softmax, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.Softmax` instance.
)""");
}

Gurax_ImplementConstructor(Softmax)
{
	// Function body
	RefPtr<Softmax> pSoftmax(new Softmax());
	return argument.ReturnValue(processor, new Value_Softmax(pSoftmax.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.Softmax#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Softmax, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Softmax, MethodSkeleton)
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
// ml.Softmax#propSkeleton
Gurax_DeclareProperty_R(Softmax, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Softmax, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Softmax
//------------------------------------------------------------------------------
VType_Softmax VTYPE_Softmax("Softmax");

void VType_Softmax::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(Softmax));
	// Assignment of method
	Assign(Gurax_CreateMethod(Softmax, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Softmax, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Softmax
//------------------------------------------------------------------------------
VType& Value_Softmax::vtype = VTYPE_Softmax;

String Value_Softmax::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetSoftmax().ToString(ss));
}

Gurax_EndModuleScope(ml)
