//==============================================================================
// VType_Function.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

${help.ComposePropertyHelp(Function, `en)}

${help.ComposeConstructorHelp(Function, `en)}

${help.ComposeMethodHelp(Function, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// &{block}
Gurax_DeclareFunctionAlias(_function_, "&")
{
	Declare(VTYPE_Function, Flag::None);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `Function` instance.
)**");
}

Gurax_ImplementFunction(_function_)
{
	// Arguments
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	// Function body
	SymbolList symbolList(pExprOfBlock->GatherArgSymbols());
	RefPtr<DeclCallable> pDeclCallable(pExprOfBlock->GetDeclCallable().Reference());
	if (!pExprOfBlock->HasExprParam()) {
		pDeclCallable.reset(new DeclCallable());
		for (const Symbol* pSymbol : symbolList) {
			RefPtr<DeclArg> pDeclArg(
				new DeclArg(pSymbol, VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr));
			pDeclCallable->GetDeclArgOwner().push_back(pDeclArg.release());
		}
	} else if (!symbolList.empty()) {
		Error::Issue(ErrorType::SyntaxError,
				"block parameters and dollar-style arguments can not be used together.");
		return Value::nil();
	}
	RefPtr<FunctionCustom> pFunction(
		new FunctionCustom(
			Type::Function, Symbol::Empty, pDeclCallable.release(), pExprOfBlock->Reference()));
	pFunction->Declare(VTYPE_Any, Flag::None);
	pFunction->SetFrameOuter(processor.GetFrameCur());
	return new Value_Function(pFunction.release());
}

// Function(`exprs*) {block}
Gurax_DeclareConstructor(Function)
{
	Declare(VTYPE_Random, Flag::None);
	DeclareArg("argDecls", VTYPE_Quote, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::Once);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementConstructor(Function)
{
	// Arguments
	ArgPicker args(argument);
	const ValueList& valuesExpr = args.PickList();
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	// Function body
	RefPtr<Function> pFunction(Function::CreateDynamicFunction(Symbol::Empty, valuesExpr, *pExprOfBlock));
	if (!pFunction) return Value::nil();
	pFunction->SetFrameOuter(processor.GetFrameCur());
	return new Value_Function(pFunction.release());
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Function#expr
Gurax_DeclareProperty_R(Function, expr)
{
	Declare(VTYPE_Expr, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
An `expr` instance that represents the function body.
Set to `nil` if the function has not been declared in a script.
)**");
}

Gurax_ImplementPropertyGetter(Function, expr)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Expr& expr = valueThis.GetFunction().GetExprBody();
	return expr.IsEmpty()? Value::nil() : new Value_Expr(expr.Reference());
}

// Function#name
Gurax_DeclareProperty_R(Function, name)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The name of the function.
)**");
}

Gurax_ImplementPropertyGetter(Function, name)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetFunction().GetName());
}

// Function#symbol
Gurax_DeclareProperty_R(Function, symbol)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The symbol of the function.
)**");
}

Gurax_ImplementPropertyGetter(Function, symbol)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetFunction().GetSymbol());
}

// Function#type
Gurax_DeclareProperty_R(Function, type)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The type of the function. One of `` `statement``, `` `function`` and `` `method``.
)**");
}

Gurax_ImplementPropertyGetter(Function, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Function& func = valueThis.GetFunction();
	return new Value_Symbol(
		func.IsTypeStatement()? Gurax_Symbol(statement) :
		func.IsTypeFunction()? Gurax_Symbol(function) :
		func.IsTypeMethod()? Gurax_Symbol(method) : Symbol::Empty);
}

// Function#vtypeResult:nil:[name]
Gurax_DeclareProperty_R(Function, vtypeResult)
{
	Declare(VTYPE_Any, Flag::Nil);
	DeclareAttrOpt(Gurax_Symbol(name));
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Function, vtypeResult)
{
	auto& valueThis = GetValueThis(valueTarget);
	DeclCallable& declCallable = valueThis.GetFunction().GetDeclCallable();
	if (attr.IsSet(Gurax_Symbol(name))) {
		const DottedSymbol& dottedSymbol = declCallable.GetDottedSymbol();
		if (dottedSymbol.IsEmpty()) return Value::nil();
		return new Value_String(dottedSymbol.ToString());
	} else {
		return new Value_VType(declCallable.GetVTypeResult());
	}
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// Function * Any
Gurax_ImplementOpBinary(Mul, Function, Any)
{
	Function& func = Value_Function::GetFunction(valueL);
	RefPtr<Argument> pArgument(new Argument(processor, func, DeclCallable::Flag::None));
	pArgument->FeedValue(processor.GetFrameCur(), valueR.Reference());
	return func.Eval(processor, *pArgument);
}

// Function * Tuple
Gurax_ImplementOpBinary(Mul, Function, Tuple)
{
	Function& func = Value_Function::GetFunction(valueL);
	ValueOwner& values = Value_Tuple::GetValueOwner(valueR);
	RefPtr<Argument> pArgument(new Argument(processor, func, DeclCallable::Flag::None));
	pArgument->FeedValues(processor.GetFrameCur(), values);
	return func.Eval(processor, *pArgument);
}

// CallableMember * Tuple
Gurax_ImplementOpBinary(Mul, CallableMember, Tuple)
{
	const DeclCallable* pDeclCallable = valueL.GetDeclCallableWithError();
	if (!pDeclCallable) return Value::nil();
	ValueOwner& values = Value_Tuple::GetValueOwner(valueR);
	RefPtr<Argument> pArgument(new Argument(processor, pDeclCallable->Reference(), DeclCallable::Flag::None));
	pArgument->FeedValues(processor.GetFrameCur(), values);
	return valueL.Eval(processor, *pArgument);
}

// CallableMember * Any
Gurax_ImplementOpBinary(Mul, CallableMember, Any)
{
	const DeclCallable* pDeclCallable = valueL.GetDeclCallableWithError();
	if (!pDeclCallable) return Value::nil();
	RefPtr<Argument> pArgument(new Argument(processor, pDeclCallable->Reference(), DeclCallable::Flag::None));
	pArgument->FeedValue(processor.GetFrameCur(), valueR.Reference());
	return valueL.Eval(processor, *pArgument);
}

// VType * Tuple
Gurax_ImplementOpBinary(Mul, VType, Tuple)
{
	const DeclCallable* pDeclCallable = valueL.GetDeclCallableWithError();
	if (!pDeclCallable) return Value::nil();
	ValueOwner& values = Value_Tuple::GetValueOwner(valueR);
	RefPtr<Argument> pArgument(new Argument(processor, pDeclCallable->Reference(), DeclCallable::Flag::None));
	pArgument->FeedValues(processor.GetFrameCur(), values);
	return valueL.Eval(processor, *pArgument);
}

// VType * Any
Gurax_ImplementOpBinary(Mul, VType, Any)
{
	const DeclCallable* pDeclCallable = valueL.GetDeclCallableWithError();
	if (!pDeclCallable) return Value::nil();
	RefPtr<Argument> pArgument(new Argument(processor, pDeclCallable->Reference(), DeclCallable::Flag::None));
	pArgument->FeedValue(processor.GetFrameCur(), valueR.Reference());
	return valueL.Eval(processor, *pArgument);
}

//------------------------------------------------------------------------------
// VType_Function
//------------------------------------------------------------------------------
VType_Function VTYPE_Function("Function");

void VType_Function::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Function));
	// Assignment of function
	frameOuter.Assign(Gurax_CreateFunction(_function_));
	// Assignment of property
	Assign(Gurax_CreateProperty(Function, expr));
	Assign(Gurax_CreateProperty(Function, name));
	Assign(Gurax_CreateProperty(Function, symbol));
	Assign(Gurax_CreateProperty(Function, type));
	Assign(Gurax_CreateProperty(Function, vtypeResult));
	// Assignment of operator
	Gurax_AssignOpBinary(Mul, Function, Tuple);
	Gurax_AssignOpBinary(Mul, Function, Any);
	Gurax_AssignOpBinary(Mul, CallableMember, Tuple);
	Gurax_AssignOpBinary(Mul, CallableMember, Any);
	Gurax_AssignOpBinary(Mul, VType, Tuple);
	Gurax_AssignOpBinary(Mul, VType, Any);
}

Value* VType_Function::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_VType)) {
		const VType& vtype = Value_VType::GetVTypeThis(value);
		const Constructor& constructor = vtype.GetConstructor();
		if (constructor.IsEmpty()) {
			Error::Issue(ErrorType::ValueError,
				 "value type %s does not have a constructor", vtype.MakeFullName().c_str());
			return nullptr;
		}
		return new Value_Function(constructor.Reference());
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Function
//------------------------------------------------------------------------------
VType& Value_Function::vtype = VTYPE_Function;

String Value_Function::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetFunction().ToString(ss.IsUnbracket()? ss : StringStyle::Cram));
}

void Value_Function::PresentHelp(Processor& processor, const Symbol* pLangCode) const
{
	GetFunction().PresentHelp(processor, pLangCode);
}

const DeclCallable* Value_Function::GetDeclCallable()
{
	return &GetFunction().GetDeclCallable();
}

Frame* Value_Function::GetFrameForVType(Processor& processor)
{
	Frame* pFrame = GetFunction().LockFrameOuter();
	if (pFrame) return pFrame;
	return processor.GetFrameCur().Reference();
}

void Value_Function::DoCall(Processor& processor, Argument& argument)
{
	GetFunction().Call(processor, argument);
}

Value* Value_Function::DoEval(Processor& processor, Argument& argument) const
{
	return GetFunction().Eval(processor, argument);
}

}
