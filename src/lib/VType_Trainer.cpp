//==============================================================================
// VType_Trainer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Trainer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Trainer, `en)}

${help.ComposeMethodHelp(Trainer, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Trainer(model as Expr, optimizer:nil as TrainOptimizer, inputs* as Symbol) {block?}
Gurax_DeclareConstructor(Trainer)
{
	Declare(VTYPE_Trainer, Flag::None);
	DeclareArg("model", VTYPE_Expr, ArgOccur::Once, ArgFlag::None);
	DeclareArg("optimizer", VTYPE_TrainOptimizer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("inputs", VTYPE_Symbol, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Trainer` instance.
)""");
}

Gurax_ImplementConstructor(Trainer)
{
	// Arguments
	ArgPicker args(argument);
	const Expr& exprModel = args.PickExpr();
	RefPtr<TrainOptimizer> pTrainOptimizer(args.IsValid()?
		args.Pick<Value_TrainOptimizer>().GetTrainOptimizer().Reference() : new TrainOptimizer_None());
	const ValueList& inputs = args.PickList();
	// Function body
	RefPtr<Trainer> pTrainer(new Trainer(pTrainOptimizer.release()));
	SymbolSet symbolsInput;
	for (const Value* pValue : inputs) symbolsInput.Set(Value_Symbol::GetSymbol(*pValue));
	if (!pTrainer->CreateFromExpr(exprModel, symbolsInput)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Trainer(pTrainer.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Trainer#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Trainer, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Trainer, MethodSkeleton)
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
// Trainer#propSkeleton
Gurax_DeclareProperty_R(Trainer, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Trainer, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Trainer
//------------------------------------------------------------------------------
VType_Trainer VTYPE_Trainer("Trainer");

void VType_Trainer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Trainer));
	// Assignment of method
	Assign(Gurax_CreateMethod(Trainer, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Trainer, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Trainer
//------------------------------------------------------------------------------
VType& Value_Trainer::vtype = VTYPE_Trainer;

String Value_Trainer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetTrainer().ToString(ss));
}

}
