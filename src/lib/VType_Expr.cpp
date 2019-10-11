//==============================================================================
// VType_Expr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
Gurax_DeclareProperty_R(Expr, children)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An iterator that returns `Expr` instance of the child elements.\n");
}

Gurax_ImplementPropertyGetter(Expr, children)
{
	auto& valueThis = GetValueThis(valueTarget);
	RefPtr<Iterator> pIterator(valueThis.GetExpr().EachChild());
	if (!pIterator) return Value::nil();
	return new Value_Iterator(pIterator.release());
}

Gurax_DeclareProperty_R(Expr, isValue)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Value");
}

Gurax_ImplementPropertyGetter(Expr, isValue)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Value>());
}

Gurax_DeclareProperty_R(Expr, isIdentifier)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Identifier");
}

Gurax_ImplementPropertyGetter(Expr, isIdentifier)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Identifier>());
}

Gurax_DeclareProperty_R(Expr, isSuffixed)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Suffixed");
}

Gurax_ImplementPropertyGetter(Expr, isSuffixed)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Suffixed>());
}

Gurax_DeclareProperty_R(Expr, isEmbedded)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Embedded");
}

Gurax_ImplementPropertyGetter(Expr, isEmbedded)
{
	auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Bool(valueThis.GetExpr().IsType<Expr_Embedded>());
	return Value::nil();
}

Gurax_DeclareProperty_R(Expr, isMember)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Member");
}

Gurax_ImplementPropertyGetter(Expr, isMember)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Member>());
}

Gurax_DeclareProperty_R(Expr, isUnaryOp)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is UnaryOp");
}

Gurax_ImplementPropertyGetter(Expr, isUnaryOp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_UnaryOp>());
}

Gurax_DeclareProperty_R(Expr, isBinaryOp)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is BinaryOp");
}

Gurax_ImplementPropertyGetter(Expr, isBinaryOp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_BinaryOp>());
}

Gurax_DeclareProperty_R(Expr, isAssign)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Assign");
}

Gurax_ImplementPropertyGetter(Expr, isAssign)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Assign>());
}

Gurax_DeclareProperty_R(Expr, isRoot)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Root");
}

Gurax_ImplementPropertyGetter(Expr, isRoot)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Root>());
}

Gurax_DeclareProperty_R(Expr, isBlock)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Block");
}

Gurax_ImplementPropertyGetter(Expr, isBlock)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Block>());
}

Gurax_DeclareProperty_R(Expr, isLister)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Lister");
}

Gurax_ImplementPropertyGetter(Expr, isLister)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Lister>());
}

Gurax_DeclareProperty_R(Expr, isIterer)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Iterer");
}

Gurax_ImplementPropertyGetter(Expr, isIterer)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Iterer>());
}

Gurax_DeclareProperty_R(Expr, isIndexer)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Indexer");
}

Gurax_ImplementPropertyGetter(Expr, isIndexer)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Indexer>());
}

Gurax_DeclareProperty_R(Expr, isCaller)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Caller");
}

Gurax_ImplementPropertyGetter(Expr, isCaller)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Caller>());
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Expr#EachPUnit()
Gurax_DeclareMethod(Expr, EachPUnit)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns an iterator that enumerates `PUnit` instances stored in the target `Expr`.\n");
}

Gurax_ImplementMethod(Expr, EachPUnit)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Expr& expr = valueThis.GetExpr();
	// Function body
	RefPtr<Iterator> pIterator(expr.EachPUnit());
	return new Value_Iterator(pIterator.release());
}

// Expr#Eval()
Gurax_DeclareMethod(Expr, Eval)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Evaluates the target `Expr` and returns its result value.");
}

Gurax_ImplementMethod(Expr, Eval)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Expr& expr = valueThis.GetExpr();
	// Function body
	RefPtr<Value> pValueRtn(processor.ProcessExpr(expr));
	processor.ClearEvent();
	return pValueRtn.release();
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// Expr == Expr
Gurax_ImplementOpBinary(Eq, Expr, Expr)
{
	const Expr& exprL = Value_Expr::GetExpr(valueL);
	const Expr& exprR = Value_Expr::GetExpr(valueR);
	return new Value_Bool(exprL.IsEqualTo(exprR));
}

// Symbol == Expr
Gurax_ImplementOpBinary(Eq, Symbol, Expr)
{
	const Symbol* pSymbolL = Value_Symbol::GetSymbol(valueL);
	const Expr& exprR = Value_Expr::GetExpr(valueR);
	return new Value_Bool(pSymbolL->IsIdentical(exprR));
}

// Expr == Symbol
Gurax_ImplementOpBinary(Eq, Expr, Symbol)
{
	const Expr& exprL = Value_Expr::GetExpr(valueL);
	const Symbol* pSymbolR = Value_Symbol::GetSymbol(valueR);
	return new Value_Bool(pSymbolR->IsIdentical(exprL));
}

//------------------------------------------------------------------------------
// VType_Expr
//------------------------------------------------------------------------------
VType_Expr VTYPE_Expr("Expr");

void VType_Expr::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(Expr, children));
	Assign(Gurax_CreateProperty(Expr, isValue));
	Assign(Gurax_CreateProperty(Expr, isIdentifier));
	Assign(Gurax_CreateProperty(Expr, isSuffixed));
	Assign(Gurax_CreateProperty(Expr, isEmbedded));
	Assign(Gurax_CreateProperty(Expr, isMember));
	Assign(Gurax_CreateProperty(Expr, isUnaryOp));
	Assign(Gurax_CreateProperty(Expr, isBinaryOp));
	Assign(Gurax_CreateProperty(Expr, isAssign));
	Assign(Gurax_CreateProperty(Expr, isRoot));
	Assign(Gurax_CreateProperty(Expr, isBlock));
	Assign(Gurax_CreateProperty(Expr, isLister));
	Assign(Gurax_CreateProperty(Expr, isIterer));
	Assign(Gurax_CreateProperty(Expr, isIndexer));
	Assign(Gurax_CreateProperty(Expr, isCaller));
	// Assignment of method
	Assign(Gurax_CreateMethod(Expr, EachPUnit));
	Assign(Gurax_CreateMethod(Expr, Eval));
	// Assignment of operator
	Gurax_AssignOpBinary(Eq, Expr, Expr);
	Gurax_AssignOpBinary(Eq, Symbol, Expr);
	Gurax_AssignOpBinary(Eq, Expr, Symbol);
}

//------------------------------------------------------------------------------
// Value_Expr
//------------------------------------------------------------------------------
VType& Value_Expr::vtype = VTYPE_Expr;

String Value_Expr::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":`(";
	str += GetExpr().ToString(StringStyle().Cram());
	str += ")";
	if (GetExpr().GetPUnitFirst()) {
		str.Printf(":PUnit#%zu", GetExpr().GetPUnitFirst()->GetSeqId());
	}
	str += ">";
	return str;
}

String Value_Expr::ToStringDetail(const StringStyle& ss) const
{
	return GetExpr().ToString(ss);
}

}
