//==============================================================================
// VType_Function.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// &{block}
Gurax_DeclareFunctionAlias(_function_, "&")
{
	Declare(VTYPE_Dict, Flag::None);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Function` instance.\n");
}

Gurax_ImplementFunction(_function_)
{
#if 0
	Expr* pExpr = exprCaller.GetExprOfBlock()->GetExprElemFirst();
	composer.Add_CreateDict(&exprCaller);						// [Dict]
	for ( ; pExpr; pExpr = pExpr->GetExprNext()) {
		if (pExpr->IsType<Expr_BinaryOp>() &&
			dynamic_cast<Expr_BinaryOp*>(pExpr)->GetOperator()->IsType(OpType::Pair)) {
			// %{ .. key => value .. }
			Expr_BinaryOp* pExprEx = dynamic_cast<Expr_BinaryOp*>(pExpr);
			pExprEx->GetExprLeft().ComposeOrNil(composer);		// [Dict Key]
			pExprEx->GetExprRight().ComposeOrNil(composer);		// [Dict Key Elem]
		} else if (pExpr->IsType<Expr_Block>()) {
			// %{ .. {key, value} .. }
			Expr_Block* pExprEx = dynamic_cast<Expr_Block*>(pExpr);
			if (pExprEx->CountExprElem() != 2) {
				Error::IssueWith(ErrorType::SyntaxError, exprCaller,
								 "block is expected to have a format of {key, value}");
				return;
			}
			Expr* pExprElem = pExprEx->GetExprElemFirst();
			pExprElem->ComposeOrNil(composer);					// [Dict Key]
			pExprElem = pExprElem->GetExprNext();
			pExprElem->ComposeOrNil(composer);					// [Dict Key Elem]
		} else {
			// %{ .. key, value .. }
			pExpr->ComposeOrNil(composer);						// [Dict Key]
			pExpr = pExpr->GetExprNext();
			if (!pExpr) {
				Error::IssueWith(ErrorType::SyntaxError, exprCaller,
								 "value is missing in the initialization list for dictionary");
				return;
			}
			pExpr->ComposeOrNil(composer);						// [Dict Key Elem]
		}
		composer.Add_DictElem(0, &exprCaller);					// [Dict]
	}
#endif
	return Value::nil();
}

// Function(`exprs*) {block}
Gurax_DeclareFunction(Function)
{
	Declare(VTYPE_Random, Flag::Map);
	DeclareArg("argDecls", VTYPE_Quote, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::Once);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(Function)
{
	// Arguments
	ArgPicker args(argument);
	const ValueList& argDecls = args.PickList();
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	// Function body
	RefPtr<ExprLink> pExprLink(new ExprLink());
	for (const Value* pExpr : argDecls) {
		pExprLink->AddExpr(Value_Expr::GetExpr(*pExpr).Reference());
	}
	RefPtr<DeclCallable> pDeclCallable(new DeclCallable());
	if (!pDeclCallable->Prepare(*pExprLink, *Attribute::Empty, nullptr)) return Value::nil();
	RefPtr<FunctionCustom> pFunction(
		new FunctionCustom(
			Type::Function, Symbol::Empty, pDeclCallable.release(), pExprOfBlock->Reference()));
	pFunction->Declare(VTYPE_Any, Flag::None);
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
		"The type of the function. One of `` `statement``, `` `function``, `` `method`` and `` `classMethod``.");
}

Gurax_ImplementPropertyGetter(Function, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Function& func = valueThis.GetFunction();
	return new Value_Symbol(
		func.IsTypeStatement()? Gurax_Symbol(statement) :
		func.IsTypeFunction()? Gurax_Symbol(function) :
		func.IsTypeMethod()? Gurax_Symbol(method) :
		func.IsTypeClassMethod()? Gurax_Symbol(classMethod) : Symbol::Empty);
}

//------------------------------------------------------------------------------
// VType_Function
//------------------------------------------------------------------------------
VType_Function VTYPE_Function("Function");

void VType_Function::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	SetConstructor(Gurax_CreateFunction(Function));
	// Assignment of function
	Assign(Gurax_CreateFunction(_function_));
	// Assignment of property
	Assign(Gurax_CreateProperty(Function, expr));
	Assign(Gurax_CreateProperty(Function, name));
	Assign(Gurax_CreateProperty(Function, type));
}

//------------------------------------------------------------------------------
// Value_Function
//------------------------------------------------------------------------------
VType& Value_Function::vtype = VTYPE_Function;

String Value_Function::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Printf(":%s>", GetFunction().MakeFullName().c_str());
	return str;
}

String Value_Function::ToStringDetail(const StringStyle& ss) const
{
	return GetFunction().ToString(ss);
}

const DeclCallable* Value_Function::GetDeclCallable()
{
	return &GetFunction().GetDeclCallable();
}

void Value_Function::DoCall(Processor& processor, Argument& argument)
{
	GetFunction().DoCall(processor, argument);
}

Value* Value_Function::DoEval(Processor& processor, Argument& argument) const
{
	return GetFunction().DoEval(processor, argument);
}

}
