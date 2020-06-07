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

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// &{block}
Gurax_DeclareFunctionAlias(_function_, "&")
{
	Declare(VTYPE_Function, Flag::None);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Function` instance.\n");
}

Gurax_ImplementFunction(_function_)
{
	// Arguments
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	// Function body
	SymbolList symbolList(pExprOfBlock->GatherArgSymbols());
	RefPtr<DeclCallable> pDeclCallable(new DeclCallable());
	for (const Symbol* pSymbol : symbolList) {
		RefPtr<DeclArg> pDeclArg(
			new DeclArg(pSymbol, VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr));
		pDeclCallable->GetDeclArgOwner().push_back(pDeclArg.release());
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
	AddHelp(
		Gurax_Symbol(en),
		"");
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
// Implementation of property
//------------------------------------------------------------------------------
// Function#expr
Gurax_DeclareProperty_R(Function, expr)
{
	Declare(VTYPE_Expr, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An `expr` instance that represents the function body.\n"
		"Set to `nil` if the function has not been declared in a script.");
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
	AddHelp(
		Gurax_Symbol(en),
		"The name of the function.");
}

Gurax_ImplementPropertyGetter(Function, name)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetFunction().GetName());
}

// Function#type
Gurax_DeclareProperty_R(Function, type)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The type of the function. One of `` `statement``, `` `function`` and `` `method``.");
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

//------------------------------------------------------------------------------
// VType_Function
//------------------------------------------------------------------------------
VType_Function VTYPE_Function("Function");

void VType_Function::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Function));
	// Assignment of function
	frameOuter.Assign(Gurax_CreateFunction(_function_));
	// Assignment of property
	Assign(Gurax_CreateProperty(Function, expr));
	Assign(Gurax_CreateProperty(Function, name));
	Assign(Gurax_CreateProperty(Function, type));
}

//------------------------------------------------------------------------------
// Value_Function
//------------------------------------------------------------------------------
VType& Value_Function::vtype = VTYPE_Function;

String Value_Function::ToStringFormatter(const StringStyle& ss) const
{
	String str;
	_ToStringFormatter(str, ss);
	str.Format(":%s>", GetFunction().MakeFullName().c_str());
	return str;
}

String Value_Function::ToStringDetail(const StringStyle& ss) const
{
	return GetFunction().ToString(ss);
}

void Value_Function::PresentHelp(Processor& processor, const Symbol* pLangCode) const
{
	GetFunction().PresentHelp(processor, pLangCode);
}

const DeclCallable* Value_Function::GetDeclCallable()
{
	return &GetFunction().GetDeclCallable();
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
