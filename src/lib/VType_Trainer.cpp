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
	DeclareArg("optimizer", VTYPE_TrainOptimizer, ArgOccur::Once, ArgFlag::Nil);
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
	RefPtr<Trainer> pTrainer(new Trainer(exprModel.Reference(), pTrainOptimizer.release()));
	SymbolSet symbolsInput;
	for (const Value* pValue : inputs) symbolsInput.Set(Value_Symbol::GetSymbol(*pValue));
	if (!pTrainer->CreateFromExpr(symbolsInput)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Trainer(pTrainer.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Trainer#Eval() {block?}
Gurax_DeclareMethod(Trainer, Eval)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Runs the forward pass of a neural network model associated with a Trainer object and returns the result.
)""");
}

Gurax_ImplementMethod(Trainer, Eval)
{
	// Target
	Trainer& trainer = GetValueThis(argument).GetTrainer();
	// Function body
	if (!trainer.EvalForward(processor)) return Value::nil();
	return argument.ReturnValue(processor, trainer.GetResult().ToValue());
}

// Trainer#EvalBackward(correct as Array):void
Gurax_DeclareMethod(Trainer, EvalBackward)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("correct", VTYPE_Array, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Given the `correct` data, it updates the weights of the neural network by computing the gradients of the loss function with respect to the weights using backpropagation.
Therefore, the EvalBackward method updates the weights of the neural network associated with the Trainer object by performing the backward pass.
)""");
}

Gurax_ImplementMethod(Trainer, EvalBackward)
{
	// Target
	Trainer& trainer = GetValueThis(argument).GetTrainer();
	// Arguments
	ArgPicker args(argument);
	const Array& arrayCorrect = args.Pick<Value_Array>().GetArray();
	// Function body
	trainer.EvalBackward(processor, arrayCorrect);
	return Value::nil();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
}

// Trainer#GetNode(symbol as Symbol):map:[nil] {block?}
Gurax_DeclareMethod(Trainer, GetNode)
{
	Declare(VTYPE_TrainNode, Flag::Map);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(nil));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Trainer, GetNode)
{
	// Target
	Trainer& trainer = GetValueThis(argument).GetTrainer();
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	bool nilFlag = argument.IsSet(Gurax_Symbol(nil));
	// Function body
	TrainNode* pNode = trainer.FindNode(pSymbol);
	RefPtr<Value> pValueRtn(Value::nil());
	if (pNode) {
		pValueRtn.reset(new Value_TrainNode(pNode->Reference()));
	} else if(!nilFlag) {
		Error::Issue(ErrorType::KeyError, "can't find a node named %s", pSymbol->GetName());
		return Value::nil();
	}
	return argument.ReturnValue(processor, pValueRtn.release());
}

// Trainer#Print(stream? as Stream):void
Gurax_DeclareMethod(Trainer, Print)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Trainer, Print)
{
	// Target
	Trainer& trainer = GetValueThis(argument).GetTrainer();
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.IsValid()? args.PickStream() : *Stream::COut;
	// Function body
	trainer.Print(stream);
	return Value::nil();
}

// Trainer#Train(correct as Array)
Gurax_DeclareMethod(Trainer, Train)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("correct", VTYPE_Array, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Trainer, Train)
{
	// Target
	Trainer& trainer = GetValueThis(argument).GetTrainer();
	// Arguments
	ArgPicker args(argument);
	const Array& arrayCorrect = args.Pick<Value_Array>().GetArray();
	// Function body
	if (!trainer.EvalForward(processor)) return Value::nil();
	trainer.EvalBackward(processor, arrayCorrect);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Trainer#model
Gurax_DeclareProperty_R(Trainer, model)
{
	Declare(VTYPE_Expr, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Trainer, model)
{
	Trainer& trainer = GetValueThis(valueTarget).GetTrainer();
	return new Value_Expr(trainer.GetExprModel().Reference());
}

// Trainer#nodeBottom
Gurax_DeclareProperty_R(Trainer, nodeBottom)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Trainer, nodeBottom)
{
	Trainer& trainer = GetValueThis(valueTarget).GetTrainer();
	return new Value_TrainNode(trainer.GetNodeBottom().Reference());
}

// Trainer#optimizer
Gurax_DeclareProperty_R(Trainer, optimizer)
{
	Declare(VTYPE_TrainOptimizer, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Trainer, optimizer)
{
	Trainer& trainer = GetValueThis(valueTarget).GetTrainer();
	return new Value_TrainOptimizer(trainer.GetOptimizer().Reference());
}

// Trainer#result
Gurax_DeclareProperty_R(Trainer, result)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Trainer, result)
{
	Trainer& trainer = GetValueThis(valueTarget).GetTrainer();
	return trainer.GetResult().ToValue();
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
	Assign(Gurax_CreateMethod(Trainer, Eval));
	Assign(Gurax_CreateMethod(Trainer, EvalBackward));
	Assign(Gurax_CreateMethod(Trainer, GetNode));
	Assign(Gurax_CreateMethod(Trainer, Print));
	Assign(Gurax_CreateMethod(Trainer, Train));
	// Assignment of property
	Assign(Gurax_CreateProperty(Trainer, model));
	Assign(Gurax_CreateProperty(Trainer, nodeBottom));
	Assign(Gurax_CreateProperty(Trainer, optimizer));
	Assign(Gurax_CreateProperty(Trainer, result));
}

//------------------------------------------------------------------------------
// Value_Trainer
//------------------------------------------------------------------------------
VType& Value_Trainer::vtype = VTYPE_Trainer;

String Value_Trainer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetTrainer().ToString(ss));
}

bool Value_Trainer::DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const
{
	const Symbol* pSymbol = Value::GetSymbol(valueIndex);
	if (!pSymbol) {
		Error::Issue(ErrorType::KeyError, "the key must be a symbol");
		return false;
	}
	TrainNode* pNode = GetTrainer().FindNode(pSymbol);
	if (!pNode) {
		Error::Issue(ErrorType::KeyError, "can't find a node named %s", pSymbol->GetName());
		return false;
	}	
	*ppValue = new Value_TrainNode(pNode->Reference());
	return true;
}

}
