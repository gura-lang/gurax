//==============================================================================
// VType_TrainOptimizer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(TrainOptimizer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(TrainOptimizer, `en)}

${help.ComposeMethodHelp(TrainOptimizer, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// TrainOptimizer() {block?}
Gurax_DeclareConstructor(TrainOptimizer)
{
	Declare(VTYPE_TrainOptimizer, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `TrainOptimizer` instance.
)""");
}

Gurax_ImplementConstructor(TrainOptimizer)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<TrainOptimizer> pTrainOptimizer(new TrainOptimizer());
	return argument.ReturnValue(processor, new Value_TrainOptimizer(pTrainOptimizer.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// TrainOptimizer#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(TrainOptimizer, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(TrainOptimizer, MethodSkeleton)
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
// TrainOptimizer#propSkeleton
Gurax_DeclareProperty_R(TrainOptimizer, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(TrainOptimizer, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_TrainOptimizer
//------------------------------------------------------------------------------
VType_TrainOptimizer VTYPE_TrainOptimizer("TrainOptimizer");

void VType_TrainOptimizer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(TrainOptimizer));
	// Assignment of method
	Assign(Gurax_CreateMethod(TrainOptimizer, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(TrainOptimizer, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_TrainOptimizer
//------------------------------------------------------------------------------
VType& Value_TrainOptimizer::vtype = VTYPE_TrainOptimizer;

String Value_TrainOptimizer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetTrainOptimizer().ToString(ss));
}

}
