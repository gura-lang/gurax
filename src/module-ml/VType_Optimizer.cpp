//==============================================================================
// VType_Optimizer.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Optimizer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Optimizer, `en)}

${help.ComposeMethodHelp(Optimizer, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Optimizer.AdaGrad(learningRate as Number, epsilon as Number)
Gurax_DeclareClassMethod(Optimizer, AdaGrad)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("learningRate", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("epsilon", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementClassMethod(Optimizer, AdaGrad)
{
	// Arguments
	ArgPicker args(argument);
	Double learningRate = args.PickNumber<Double>();
	Double epsilon = args.PickNumber<Double>();
	// Function body
	return new Value_Optimizer(new Optimizer_AdaGrad(learningRate, epsilon));
}

// Optimizer.Adam()
Gurax_DeclareClassMethod(Optimizer, Adam)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementClassMethod(Optimizer, Adam)
{
	// Arguments
	//ArgPicker args(argument);
	//Double learningRate = args.PickNumber<Double>();
	//Double epsilon = args.PickNumber<Double>();
	// Function body
	return new Value_Optimizer(new Optimizer_Adam());
}

// Optimizer.GradientDescent(learningRate as Number)
Gurax_DeclareClassMethod(Optimizer, GradientDescent)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("learningRate", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementClassMethod(Optimizer, GradientDescent)
{
	// Arguments
	ArgPicker args(argument);
	Double learningRate = args.PickNumber<Double>();
	// Function body
	return new Value_Optimizer(new Optimizer_GradientDescent(learningRate));
}

// Optimizer.Momentum(learningRate as Number, epsilon as Number)
Gurax_DeclareClassMethod(Optimizer, Momentum)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("learningRate", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("epsilon", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementClassMethod(Optimizer, Momentum)
{
	// Arguments
	ArgPicker args(argument);
	Double learningRate = args.PickNumber<Double>();
	Double epsilon = args.PickNumber<Double>();
	// Function body
	return new Value_Optimizer(new Optimizer_Momentum(learningRate, epsilon));
}

// Optimizer.Nesterov()
Gurax_DeclareClassMethod(Optimizer, Nesterov)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementClassMethod(Optimizer, Nesterov)
{
	// Arguments
	// ArgPicker args(argument);
	// Function body
	return new Value_Optimizer(new Optimizer_Nesterov());
}

// Optimizer.RMSProp()
Gurax_DeclareClassMethod(Optimizer, RMSprop)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementClassMethod(Optimizer, RMSprop)
{
	// Arguments
	//ArgPicker args(argument);
	//Double learningRate = args.PickNumber<Double>();
	//Double epsilon = args.PickNumber<Double>();
	// Function body
	return new Value_Optimizer(new Optimizer_RMSprop());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Optimizer#propSkeleton
Gurax_DeclareProperty_R(Optimizer, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Optimizer, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Optimizer
//------------------------------------------------------------------------------
VType_Optimizer VTYPE_Optimizer("Optimizer");

void VType_Optimizer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Optimizer, AdaGrad));
	Assign(Gurax_CreateMethod(Optimizer, Adam));
	Assign(Gurax_CreateMethod(Optimizer, GradientDescent));
	Assign(Gurax_CreateMethod(Optimizer, Momentum));
	Assign(Gurax_CreateMethod(Optimizer, Nesterov));
	Assign(Gurax_CreateMethod(Optimizer, RMSprop));
	// Assignment of property
	Assign(Gurax_CreateProperty(Optimizer, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Optimizer
//------------------------------------------------------------------------------
VType& Value_Optimizer::vtype = VTYPE_Optimizer;

String Value_Optimizer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetOptimizer().ToString(ss));
}

Value* Value_Optimizer::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	RefPtr<Value> pValueRtn(_pOptimizer->DoGetProperty(pSymbol, attr));
	if (pValueRtn) return pValueRtn.release();
	return DoGetProperty(pSymbol, attr, notFoundErrorFlag);
}

bool Value_Optimizer::DoSetProperty(Processor& processor, const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	if (_pOptimizer->DoSetProperty(pSymbol, pValue.Reference(), attr)) return true;
	return Value::DoSetProperty(processor, pSymbol, pValue.release(), attr);
}

Gurax_EndModuleScope(ml)
