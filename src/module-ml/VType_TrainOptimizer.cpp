//==============================================================================
// VType_TrainOptimizer.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

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

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// TrainOptimizer.AdaGrad(learningRate as Number, epsilon as Number)
Gurax_DeclareClassMethod(TrainOptimizer, AdaGrad)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("learningRate", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("epsilon", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementClassMethod(TrainOptimizer, AdaGrad)
{
	// Arguments
	ArgPicker args(argument);
	Double learningRate = args.PickNumber<Double>();
	Double epsilon = args.PickNumber<Double>();
	// Function body
	return new Value_TrainOptimizer(new TrainOptimizer_AdaGrad(learningRate, epsilon));
}

// TrainOptimizer.Adam()
Gurax_DeclareClassMethod(TrainOptimizer, Adam)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementClassMethod(TrainOptimizer, Adam)
{
	// Arguments
	//ArgPicker args(argument);
	//Double learningRate = args.PickNumber<Double>();
	//Double epsilon = args.PickNumber<Double>();
	// Function body
	return new Value_TrainOptimizer(new TrainOptimizer_Adam());
}

// TrainOptimizer.GradientDescent(learningRate as Number, epsilon as Number)
Gurax_DeclareClassMethod(TrainOptimizer, GradientDescent)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("learningRate", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("epsilon", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementClassMethod(TrainOptimizer, GradientDescent)
{
	// Arguments
	ArgPicker args(argument);
	Double learningRate = args.PickNumber<Double>();
	// Function body
	return new Value_TrainOptimizer(new TrainOptimizer_GradientDescent(learningRate));
}

// TrainOptimizer.Momentum(learningRate as Number, epsilon as Number)
Gurax_DeclareClassMethod(TrainOptimizer, Momentum)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("learningRate", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("epsilon", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementClassMethod(TrainOptimizer, Momentum)
{
	// Arguments
	ArgPicker args(argument);
	Double learningRate = args.PickNumber<Double>();
	Double epsilon = args.PickNumber<Double>();
	// Function body
	return new Value_TrainOptimizer(new TrainOptimizer_Momentum(learningRate, epsilon));
}

// TrainOptimizer.Nesterov()
Gurax_DeclareClassMethod(TrainOptimizer, Nesterov)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementClassMethod(TrainOptimizer, Nesterov)
{
	// Arguments
	// ArgPicker args(argument);
	// Function body
	return new Value_TrainOptimizer(new TrainOptimizer_Nesterov());
}

// TrainOptimizer.RMSProp()
Gurax_DeclareClassMethod(TrainOptimizer, RMSprop)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementClassMethod(TrainOptimizer, RMSprop)
{
	// Arguments
	//ArgPicker args(argument);
	//Double learningRate = args.PickNumber<Double>();
	//Double epsilon = args.PickNumber<Double>();
	// Function body
	return new Value_TrainOptimizer(new TrainOptimizer_RMSprop());
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
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(TrainOptimizer, AdaGrad));
	Assign(Gurax_CreateMethod(TrainOptimizer, Adam));
	Assign(Gurax_CreateMethod(TrainOptimizer, GradientDescent));
	Assign(Gurax_CreateMethod(TrainOptimizer, Momentum));
	Assign(Gurax_CreateMethod(TrainOptimizer, Nesterov));
	Assign(Gurax_CreateMethod(TrainOptimizer, RMSprop));
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

Gurax_EndModuleScope(ml)
