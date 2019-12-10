//==============================================================================
// VType_Expr.cpp
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
// Expr(stream:Stream):map
Gurax_DeclareConstructor(Expr)
{
	Declare(VTYPE_Expr, Flag::Map);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an `Expr` instance by pasring the given stream.");
}

Gurax_ImplementConstructor(Expr)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.Pick<Value_Stream>().GetStream();
	// Function body
	RefPtr<Expr_Collector> pExprRoot(Parser::ParseStream(stream));
	if (!pExprRoot) return Value::nil();
	Composer composer;
	pExprRoot->Compose(composer);
	if (Error::IsIssued()) return Value::nil();
	return argument.ReturnValue(processor, new Value_Expr(pExprRoot.release()));
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
	return expr.Eval(processor);
}

// Expr.Parse(str:String):map {block?}
Gurax_DeclareClassMethod(Expr, Parse)
{
	Declare(VTYPE_Expr, Flag::Map);
	DeclareArg("script", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an `Expr` instance by parsing the given script.");
}

Gurax_ImplementClassMethod(Expr, Parse)
{
	// Argument
	ArgPicker args(argument);
	const char* str = args.PickString();
	// Function body
	RefPtr<Expr_Collector> pExprRoot(Parser::ParseString(str));
	if (!pExprRoot) return Value::nil();
	Composer composer;
	pExprRoot->Compose(composer);
	if (Error::IsIssued()) return Value::nil();
	return argument.ReturnValue(processor, new Value_Expr(pExprRoot.release()));
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Expr#child
Gurax_DeclareProperty_R(Expr, child)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An `Expr` instance of the child element.\n");
}

Gurax_ImplementPropertyGetter(Expr, child)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Expr* pExpr = valueThis.GetExpr().InspectChild();
	if (!pExpr) return Value::nil();
	return new Value_Expr(pExpr->Reference());
}

// Expr#left
Gurax_DeclareProperty_R(Expr, left)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An `Expr` instance of the left element.\n");
}

Gurax_ImplementPropertyGetter(Expr, left)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Expr* pExpr = valueThis.GetExpr().InspectLeft();
	if (!pExpr) return Value::nil();
	return new Value_Expr(pExpr->Reference());
}

// Expr#right
Gurax_DeclareProperty_R(Expr, right)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An `Expr` instance of the right element.\n");
}

Gurax_ImplementPropertyGetter(Expr, right)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Expr* pExpr = valueThis.GetExpr().InspectRight();
	if (!pExpr) return Value::nil();
	return new Value_Expr(pExpr->Reference());
}

// Expr#car
Gurax_DeclareProperty_R(Expr, car)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An `Expr` instance of the car element.\n");
}

Gurax_ImplementPropertyGetter(Expr, car)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Expr* pExpr = valueThis.GetExpr().InspectCar();
	if (!pExpr) return Value::nil();
	return new Value_Expr(pExpr->Reference());
}

// Expr#target
Gurax_DeclareProperty_R(Expr, target)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An `Expr` instance of the target element.\n");
}

Gurax_ImplementPropertyGetter(Expr, target)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Expr* pExpr = valueThis.GetExpr().InspectTarget();
	if (!pExpr) return Value::nil();
	return new Value_Expr(pExpr->Reference());
}

// Expr#block
Gurax_DeclareProperty_R(Expr, block)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An `Expr` instance of the block element.\n");
}

Gurax_ImplementPropertyGetter(Expr, block)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Expr* pExpr = valueThis.GetExpr().InspectBlock();
	if (!pExpr) return Value::nil();
	return new Value_Expr(pExpr->Reference());
}

// Expr#trailer
Gurax_DeclareProperty_R(Expr, trailer)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An `Expr` instance of the trailer element.\n");
}

Gurax_ImplementPropertyGetter(Expr, trailer)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Expr* pExpr = valueThis.GetExpr().InspectTrailer();
	if (!pExpr) return Value::nil();
	return new Value_Expr(pExpr->Reference());
}

// Expr#cdrs
Gurax_DeclareProperty_R(Expr, cdrs)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An iterator that returns `Expr` instance of the cdr elements.\n");
}

Gurax_ImplementPropertyGetter(Expr, cdrs)
{
	auto& valueThis = GetValueThis(valueTarget);
	RefPtr<Iterator> pIterator(valueThis.GetExpr().EachCdr());
	if (!pIterator) return Value::nil();
	return new Value_Iterator(pIterator.release());
}

// Expr#children
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

// Expr#params
Gurax_DeclareProperty_R(Expr, params)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An iterator that returns `Expr` instance of the parameter elements.\n");
}

Gurax_ImplementPropertyGetter(Expr, params)
{
	auto& valueThis = GetValueThis(valueTarget);
	RefPtr<Iterator> pIterator(valueThis.GetExpr().EachParam());
	if (!pIterator) return Value::nil();
	return new Value_Iterator(pIterator.release());
}

// Expr#isValue
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

// Expr#isIdentifier
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

// Expr#isSuffixed
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

// Expr#isMember
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

// Expr#isUnaryOp
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

// Expr#isBinaryOp
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

// Expr#isAssign
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

// Expr#isRoot
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

// Expr#isBlock
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

// Expr#isLister
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

// Expr#isIterer
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

// Expr#isIndexer
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

// Expr#isCaller
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

// Expr#type
Gurax_DeclareProperty_R(Expr, type)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A `symbol` that represents the expression's type");
}

Gurax_ImplementPropertyGetter(Expr, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(Symbol::Add(valueThis.GetExpr().GetTypeInfo().GetName()));
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
	return new Value_Bool(exprR.IsSymbol(pSymbolL));
}

// Expr == Symbol
Gurax_ImplementOpBinary(Eq, Expr, Symbol)
{
	const Expr& exprL = Value_Expr::GetExpr(valueL);
	const Symbol* pSymbolR = Value_Symbol::GetSymbol(valueR);
	return new Value_Bool(exprL.IsSymbol(pSymbolR));
}

// Expr != Expr
Gurax_ImplementOpBinary(Ne, Expr, Expr)
{
	const Expr& exprL = Value_Expr::GetExpr(valueL);
	const Expr& exprR = Value_Expr::GetExpr(valueR);
	return new Value_Bool(!exprL.IsEqualTo(exprR));
}

// Symbol != Expr
Gurax_ImplementOpBinary(Ne, Symbol, Expr)
{
	const Symbol* pSymbolL = Value_Symbol::GetSymbol(valueL);
	const Expr& exprR = Value_Expr::GetExpr(valueR);
	return new Value_Bool(!exprR.IsSymbol(pSymbolL));
}

// Expr != Symbol
Gurax_ImplementOpBinary(Ne, Expr, Symbol)
{
	const Expr& exprL = Value_Expr::GetExpr(valueL);
	const Symbol* pSymbolR = Value_Symbol::GetSymbol(valueR);
	return new Value_Bool(!exprL.IsSymbol(pSymbolR));
}

//------------------------------------------------------------------------------
// VType_Expr
//------------------------------------------------------------------------------
VType_Expr VTYPE_Expr("Expr");

void VType_Expr::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Expr));
	// Assignment of method
	Assign(Gurax_CreateMethod(Expr, EachPUnit));
	Assign(Gurax_CreateMethod(Expr, Eval));
	Assign(Gurax_CreateMethod(Expr, Parse));
	// Assignment of property
	Assign(Gurax_CreateProperty(Expr, child));
	Assign(Gurax_CreateProperty(Expr, left));
	Assign(Gurax_CreateProperty(Expr, right));
	Assign(Gurax_CreateProperty(Expr, car));
	Assign(Gurax_CreateProperty(Expr, target));
	Assign(Gurax_CreateProperty(Expr, block));
	Assign(Gurax_CreateProperty(Expr, trailer));
	Assign(Gurax_CreateProperty(Expr, cdrs));
	Assign(Gurax_CreateProperty(Expr, children));
	Assign(Gurax_CreateProperty(Expr, params));
	Assign(Gurax_CreateProperty(Expr, isValue));
	Assign(Gurax_CreateProperty(Expr, isIdentifier));
	Assign(Gurax_CreateProperty(Expr, isSuffixed));
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
	Assign(Gurax_CreateProperty(Expr, type));
	// Assignment of operator
	Gurax_AssignOpBinary(Eq, Expr, Expr);
	Gurax_AssignOpBinary(Eq, Symbol, Expr);
	Gurax_AssignOpBinary(Eq, Expr, Symbol);
	Gurax_AssignOpBinary(Ne, Expr, Expr);
	Gurax_AssignOpBinary(Ne, Symbol, Expr);
	Gurax_AssignOpBinary(Ne, Expr, Symbol);
}

//------------------------------------------------------------------------------
// Value_Expr
//------------------------------------------------------------------------------
VType& Value_Expr::vtype = VTYPE_Expr;

bool Value_Expr::IsEqualTo(const Value* pValue) const
{
	if (IsSameType(pValue)) {
		return GetExpr().IsEqualTo(dynamic_cast<const Value_Expr*>(pValue)->GetExpr());
	} else if (pValue->IsType(VTYPE_Symbol)) {
		return GetExpr().IsPureSymbol(dynamic_cast<const Value_Symbol*>(pValue)->GetSymbol());
	}
	return false;
}

bool Value_Expr::IsLessThan(const Value* pValue) const
{
	return IsSameType(pValue)?
		GetExpr().IsLessThan(dynamic_cast<const Value_Expr*>(pValue)->GetExpr()) :
		GetVType().IsLessThan(pValue->GetVType());
}

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
