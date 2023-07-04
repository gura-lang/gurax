//==============================================================================
// VType_Trainer.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

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
// Trainer(model as Expr, optimizer:nil as Optimizer, symbolsInput* as Symbol) {block?}
Gurax_DeclareConstructor(Trainer)
{
	Declare(VTYPE_Trainer, Flag::None);
	DeclareArg("model", VTYPE_Expr, ArgOccur::Once, ArgFlag::None);
	DeclareArg("optimizer", VTYPE_Optimizer, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("symbolsInput", VTYPE_Symbol, ArgOccur::ZeroOrMore, ArgFlag::None);
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
	RefPtr<Optimizer> pOptimizer(args.IsValid()?
		args.Pick<Value_Optimizer>().GetOptimizer().Reference() : new Optimizer_None());
	const ValueList& symbolsInput = args.PickList();
	// Function body
	SymbolList symbolListInput;
	for (const Value* pValue : symbolsInput) symbolListInput.push_back(Value_Symbol::GetSymbol(*pValue));
	RefPtr<Trainer> pTrainer(new Trainer(exprModel.Reference(), symbolListInput, pOptimizer.release()));
	if (!pTrainer->CreateFromExpr()) return Value::nil();
	return argument.ReturnValue(processor, new Value_Trainer(pTrainer.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Trainer#EachNode(type* as Symbol) {block?}
Gurax_DeclareMethod(Trainer, EachNode)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareArg("type", VTYPE_Symbol, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Trainer, EachNode)
{
	// Target
	Trainer& trainer = GetValueThis(argument).GetTrainer();
	// Arguments
	ArgPicker args(argument);
	const ValueList& values = args.PickList();
	// Function body
	SymbolSet symbolsType;
	for (const Value* pValue : values) symbolsType.Set(Value_Symbol::GetSymbol(*pValue));
	RefPtr<Iterator> pIterator(new Iterator_Node(trainer.GetNodeOwner().Reference(), std::move(symbolsType)));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Trainer#Eval(inputs* as Array) {block?}
Gurax_DeclareMethod(Trainer, Eval)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("inputs", VTYPE_Array, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Runs the forward pass of a neural network model associated with a Trainer object and returns the result.
)""");
}

Gurax_ImplementMethod(Trainer, Eval)
{
	// Target
	Trainer& trainer = GetValueThis(argument).GetTrainer();
	// Arguments
	ArgPicker args(argument);
	const ValueList& valuesInput = args.PickList();
	// Function body
	if (!trainer.EvalForward(processor, valuesInput)) return Value::nil();
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
	Declare(VTYPE_Node, Flag::Map);
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
	Node* pNode = trainer.FindNode(pSymbol);
	RefPtr<Value> pValueRtn(Value::nil());
	if (pNode) {
		pValueRtn.reset(new Value_Node(pNode->Reference()));
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

// Trainer#Train(correct as Array, inputs* as Array)
Gurax_DeclareMethod(Trainer, Train)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("correct", VTYPE_Array, ArgOccur::Once, ArgFlag::None);
	DeclareArg("inputs", VTYPE_Array, ArgOccur::ZeroOrMore, ArgFlag::None);
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
	const ValueList& valuesInput = args.PickList();
	// Function body
	if (!trainer.EvalForward(processor, valuesInput)) return Value::nil();
	trainer.EvalBackward(processor, arrayCorrect);
	return Value::nil();
}

// Trainer#CalcCrossEntropyError(correct as Array)
Gurax_DeclareMethod(Trainer, CalcCrossEntropyError)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("correct", VTYPE_Array, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Trainer, CalcCrossEntropyError)
{
	// Target
	Trainer& trainer = GetValueThis(argument).GetTrainer();
	// Arguments
	ArgPicker args(argument);
	const Array& arrayCorrect = args.Pick<Value_Array>().GetArray();
	Double epsilon = 1.e-6;
	// Function body
	Double entropyError = trainer.CalcCrossEntropyError(arrayCorrect, epsilon);
	if (Error::IsIssued()) return Value::nil();
	return new Value_Number(entropyError);
}

// Trainer#CalcMeanSquaredError(correct as Array)
Gurax_DeclareMethod(Trainer, CalcMeanSquaredError)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("correct", VTYPE_Array, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Trainer, CalcMeanSquaredError)
{
	// Target
	Trainer& trainer = GetValueThis(argument).GetTrainer();
	// Arguments
	ArgPicker args(argument);
	const Array& arrayCorrect = args.Pick<Value_Array>().GetArray();
	// Function body
	Double meanSquareError = trainer.CalcMeanSquareError(arrayCorrect);
	if (Error::IsIssued()) return Value::nil();
	return new Value_Number(meanSquareError);
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

// Trainer#node
Gurax_DeclareProperty_R(Trainer, node)
{
	Declare(VTYPE_NodeMap, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Trainer, node)
{
	Trainer& trainer = GetValueThis(valueTarget).GetTrainer();
	return new Value_NodeMap(trainer.GetNodeMap().Reference());
}

// Trainer#nodeBottom
Gurax_DeclareProperty_R(Trainer, nodeBottom)
{
	Declare(VTYPE_Node, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Trainer, nodeBottom)
{
	Trainer& trainer = GetValueThis(valueTarget).GetTrainer();
	return new Value_Node(trainer.GetNodeBottom().Reference());
}

// Trainer#optimizer
Gurax_DeclareProperty_R(Trainer, optimizer)
{
	Declare(VTYPE_Optimizer, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Trainer, optimizer)
{
	Trainer& trainer = GetValueThis(valueTarget).GetTrainer();
	return new Value_Optimizer(trainer.GetOptimizer().Reference());
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
	Assign(Gurax_CreateMethod(Trainer, EachNode));
	Assign(Gurax_CreateMethod(Trainer, Eval));
	Assign(Gurax_CreateMethod(Trainer, EvalBackward));
	Assign(Gurax_CreateMethod(Trainer, GetNode));
	Assign(Gurax_CreateMethod(Trainer, Print));
	Assign(Gurax_CreateMethod(Trainer, Train));
	Assign(Gurax_CreateMethod(Trainer, CalcMeanSquaredError));
	Assign(Gurax_CreateMethod(Trainer, CalcCrossEntropyError));
	// Assignment of property
	Assign(Gurax_CreateProperty(Trainer, model));
	Assign(Gurax_CreateProperty(Trainer, node));
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

Gurax_EndModuleScope(ml)
