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
// Expr(stream:Stream):map {block?}
Gurax_DeclareConstructor(Expr)
{
	Declare(VTYPE_Expr, Flag::Map);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an `Expr` instance by parsing the scripts from the given stream.");
}

Gurax_ImplementConstructor(Expr)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
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
// Expr#EachElem() {block?}
Gurax_DeclareMethod(Expr, EachElem)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Returns an iterator that returns `Expr` instance of the contained elements.\n");
}

Gurax_ImplementMethod(Expr, EachElem)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Expr& expr = valueThis.GetExpr();
	//Function body
	return argument.ReturnIterator(processor, expr.EachElem());
}

// Expr#EachParam() {block?}
Gurax_DeclareMethod(Expr, EachParam)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An iterator that returns `Expr` instance of the parameter elements.\n");
}

Gurax_ImplementMethod(Expr, EachParam)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Expr& expr = valueThis.GetExpr();
	//Function body
	return argument.ReturnIterator(processor, expr.EachParam());
}

// Expr#EachPUnit() {block?}
Gurax_DeclareMethod(Expr, EachPUnit)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
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
	return argument.ReturnIterator(processor, pIterator.release());
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

// Expr#IsAssign()
Gurax_DeclareMethod(Expr, IsAssign)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Assign");
}

Gurax_ImplementMethod(Expr, IsAssign)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Assign>());
}

// Expr#IsBinaryOp(symbol?:Symbol)
Gurax_DeclareMethod(Expr, IsBinaryOp)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is BinaryOp");
}

Gurax_ImplementMethod(Expr, IsBinaryOp)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Expr& expr = valueThis.GetExpr();
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.IsValid()? args.PickSymbol() : nullptr;
	// Function body
	bool rtn = expr.IsType<Expr_BinaryOp>() &&
		(!pSymbol || expr.InspectOperator()->GetSymbol()->IsIdentical(pSymbol));
	return new Value_Bool(rtn);
}

// Expr#IsBlock()
Gurax_DeclareMethod(Expr, IsBlock)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Block");
}

Gurax_ImplementMethod(Expr, IsBlock)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Block>());
}

// Expr#IsCaller()
Gurax_DeclareMethod(Expr, IsCaller)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Caller");
}

Gurax_ImplementMethod(Expr, IsCaller)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Caller>());
}

// Expr#IsIdentifier(symbol?:Symbol)
Gurax_DeclareMethod(Expr, IsIdentifier)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Identifier.\n"
		"If the argument `symbol` is specifieid,\n"
		"it also checks if the identifier's symbol matches with that.\n");
}

Gurax_ImplementMethod(Expr, IsIdentifier)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Expr& expr = valueThis.GetExpr();
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.IsValid()? args.PickSymbol() : nullptr;
	// Function body
	bool rtn = expr.IsType<Expr_Identifier>() && (!pSymbol || expr.HasSymbol(pSymbol));
	return new Value_Bool(rtn);
}

// Expr#IsIndexer()
Gurax_DeclareMethod(Expr, IsIndexer)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Indexer");
}

Gurax_ImplementMethod(Expr, IsIndexer)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Indexer>());
}

// Expr#IsIterer()
Gurax_DeclareMethod(Expr, IsIterer)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Iterer");
}

Gurax_ImplementMethod(Expr, IsIterer)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Iterer>());
}

// Expr#IsLister()
Gurax_DeclareMethod(Expr, IsLister)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Lister");
}

Gurax_ImplementMethod(Expr, IsLister)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Lister>());
}

// Expr#IsMember()
Gurax_DeclareMethod(Expr, IsMember)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Member");
}

Gurax_ImplementMethod(Expr, IsMember)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Member>());
}

// Expr#IsPureAssign()
Gurax_DeclareMethod(Expr, IsPureAssign)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Assign without any operation.");
}

Gurax_ImplementMethod(Expr, IsPureAssign)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetExpr().IsPureAssign());
}

// Expr#IsRoot()
Gurax_DeclareMethod(Expr, IsRoot)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Root");
}

Gurax_ImplementMethod(Expr, IsRoot)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Root>());
}

// Expr#IsSuffixed()
Gurax_DeclareMethod(Expr, IsSuffixed)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Suffixed");
}

Gurax_ImplementMethod(Expr, IsSuffixed)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Suffixed>());
}

// Expr#IsUnaryOp()
Gurax_DeclareMethod(Expr, IsUnaryOp)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is UnaryOp");
}

Gurax_ImplementMethod(Expr, IsUnaryOp)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Expr& expr = valueThis.GetExpr();
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.IsValid()? args.PickSymbol() : nullptr;
	// Function body
	bool rtn = expr.IsType<Expr_UnaryOp>() &&
		(!pSymbol || expr.InspectOperator()->GetSymbol()->IsIdentical(pSymbol));
	return new Value_Bool(rtn);
}

// Expr#IsValue()
Gurax_DeclareMethod(Expr, IsValue)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the expression is Value");
}

Gurax_ImplementMethod(Expr, IsValue)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetExpr().IsType<Expr_Value>());
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
// Expr#attr
Gurax_DeclareProperty_R(Expr, attr)
{
	Declare(VTYPE_Attribute, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The attribute.\n");
}

Gurax_ImplementPropertyGetter(Expr, attr)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Attribute* pAttr = valueThis.GetExpr().InspectAttr();
	if (!pAttr) return Value::nil();
	return new Value_Attribute(pAttr->Reference());
}

// Expr#block
Gurax_DeclareProperty_R(Expr, block)
{
	Declare(VTYPE_Expr, Flag::None);
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

// Expr#car
Gurax_DeclareProperty_R(Expr, car)
{
	Declare(VTYPE_Expr, Flag::None);
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

// Expr#child
Gurax_DeclareProperty_R(Expr, child)
{
	Declare(VTYPE_Expr, Flag::None);
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
	Declare(VTYPE_Expr, Flag::None);
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

// Expr#lineNoBtm
Gurax_DeclareProperty_R(Expr, lineNoBtm)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Line number of the bottom of the Expr's source code.\n");
}

Gurax_ImplementPropertyGetter(Expr, lineNoBtm)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetExpr().GetLineNoBtm());
}

// Expr#lineNoTop
Gurax_DeclareProperty_R(Expr, lineNoTop)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Line number of the top of the Expr's source code.\n");
}

Gurax_ImplementPropertyGetter(Expr, lineNoTop)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetExpr().GetLineNoTop());
}

// Expr#mode
Gurax_DeclareProperty_R(Expr, mode)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The member accessor's mode in symbol.\n");
}

Gurax_ImplementPropertyGetter(Expr, mode)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Symbol* pSymbol = valueThis.GetExpr().InspectModeAsSymbol();
	if (!pSymbol) return Value::nil();
	return new Value_Symbol(pSymbol);
}

// Expr#operator
Gurax_DeclarePropertyAlias_R(Expr, operator_, "operator")
{
	Declare(VTYPE_Operator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The operator that is associated with the expr.\n");
}

Gurax_ImplementPropertyGetter(Expr, operator_)
{
	auto& valueThis = GetValueThis(valueTarget);
	Operator* pOp = valueThis.GetExpr().InspectOperator();
	if (!pOp) return Value::nil();
	return new Value_Operator(pOp);
}

// Expr#right
Gurax_DeclareProperty_R(Expr, right)
{
	Declare(VTYPE_Expr, Flag::None);
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

// Expr#string
Gurax_DeclareProperty_R(Expr, string)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The string that is associated with the expr.");
}

Gurax_ImplementPropertyGetter(Expr, string)
{
	auto& valueThis = GetValueThis(valueTarget);
	RefPtr<StringReferable> pStr(valueThis.GetExpr().InspectStringReferable());
	if (!pStr) return Value::nil();
	return new Value_String(pStr.release());
}

// Expr#symbol
Gurax_DeclareProperty_R(Expr, symbol)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The symbol that is associated with identifier or member.\n");
}

Gurax_ImplementPropertyGetter(Expr, symbol)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Symbol* pSymbol = valueThis.GetExpr().InspectSymbol();
	if (!pSymbol) return Value::nil();
	return new Value_Symbol(pSymbol);
}

// Expr#symbolName
Gurax_DeclareProperty_R(Expr, symbolName)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The name of the symbol that is associated with identifier or member.\n");
}

Gurax_ImplementPropertyGetter(Expr, symbolName)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Symbol* pSymbol = valueThis.GetExpr().InspectSymbol();
	if (!pSymbol) return Value::nil();
	return new Value_String(pSymbol->GetName());
}

// Expr#target
Gurax_DeclareProperty_R(Expr, target)
{
	Declare(VTYPE_Expr, Flag::None);
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

// Expr#trailer
Gurax_DeclareProperty_R(Expr, trailer)
{
	Declare(VTYPE_Expr, Flag::None);
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

// Expr#value
Gurax_DeclareProperty_R(Expr, value)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The value that is associated with the expr.");
}

Gurax_ImplementPropertyGetter(Expr, value)
{
	auto& valueThis = GetValueThis(valueTarget);
	RefPtr<Value> pValue(valueThis.GetExpr().InspectValue());
	if (!pValue) return Value::nil();
	return pValue.release();
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// Expr == Expr
Gurax_ImplementBinary(Eq, Expr, Expr)
{
	const Expr& exprL = Value_Expr::GetExpr(valueL);
	const Expr& exprR = Value_Expr::GetExpr(valueR);
	return new Value_Bool(exprL.IsEqualTo(exprR));
}

// Symbol == Expr
Gurax_ImplementBinary(Eq, Symbol, Expr)
{
	const Symbol* pSymbolL = Value_Symbol::GetSymbol(valueL);
	const Expr& exprR = Value_Expr::GetExpr(valueR);
	return new Value_Bool(exprR.HasSymbol(pSymbolL));
}

// Expr == Symbol
Gurax_ImplementBinary(Eq, Expr, Symbol)
{
	const Expr& exprL = Value_Expr::GetExpr(valueL);
	const Symbol* pSymbolR = Value_Symbol::GetSymbol(valueR);
	return new Value_Bool(exprL.HasSymbol(pSymbolR));
}

// Expr != Expr
Gurax_ImplementBinary(Ne, Expr, Expr)
{
	const Expr& exprL = Value_Expr::GetExpr(valueL);
	const Expr& exprR = Value_Expr::GetExpr(valueR);
	return new Value_Bool(!exprL.IsEqualTo(exprR));
}

// Symbol != Expr
Gurax_ImplementBinary(Ne, Symbol, Expr)
{
	const Symbol* pSymbolL = Value_Symbol::GetSymbol(valueL);
	const Expr& exprR = Value_Expr::GetExpr(valueR);
	return new Value_Bool(!exprR.HasSymbol(pSymbolL));
}

// Expr != Symbol
Gurax_ImplementBinary(Ne, Expr, Symbol)
{
	const Expr& exprL = Value_Expr::GetExpr(valueL);
	const Symbol* pSymbolR = Value_Symbol::GetSymbol(valueR);
	return new Value_Bool(!exprL.HasSymbol(pSymbolR));
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
	Assign(Gurax_CreateMethod(Expr, EachElem));
	Assign(Gurax_CreateMethod(Expr, EachParam));
	Assign(Gurax_CreateMethod(Expr, EachPUnit));
	Assign(Gurax_CreateMethod(Expr, Eval));
	Assign(Gurax_CreateMethod(Expr, IsAssign));
	Assign(Gurax_CreateMethod(Expr, IsBinaryOp));
	Assign(Gurax_CreateMethod(Expr, IsBlock));
	Assign(Gurax_CreateMethod(Expr, IsCaller));
	Assign(Gurax_CreateMethod(Expr, IsIdentifier));
	Assign(Gurax_CreateMethod(Expr, IsIndexer));
	Assign(Gurax_CreateMethod(Expr, IsIterer));
	Assign(Gurax_CreateMethod(Expr, IsLister));
	Assign(Gurax_CreateMethod(Expr, IsMember));
	Assign(Gurax_CreateMethod(Expr, IsPureAssign));
	Assign(Gurax_CreateMethod(Expr, IsRoot));
	Assign(Gurax_CreateMethod(Expr, IsSuffixed));
	Assign(Gurax_CreateMethod(Expr, IsUnaryOp));
	Assign(Gurax_CreateMethod(Expr, IsValue));
	Assign(Gurax_CreateMethod(Expr, Parse));
	// Assignment of property
	Assign(Gurax_CreateProperty(Expr, attr));
	Assign(Gurax_CreateProperty(Expr, block));
	Assign(Gurax_CreateProperty(Expr, car));
	Assign(Gurax_CreateProperty(Expr, child));
	Assign(Gurax_CreateProperty(Expr, left));
	Assign(Gurax_CreateProperty(Expr, lineNoBtm));
	Assign(Gurax_CreateProperty(Expr, lineNoTop));
	Assign(Gurax_CreateProperty(Expr, mode));
	Assign(Gurax_CreateProperty(Expr, operator_));
	Assign(Gurax_CreateProperty(Expr, right));
	Assign(Gurax_CreateProperty(Expr, string));
	Assign(Gurax_CreateProperty(Expr, symbol));
	Assign(Gurax_CreateProperty(Expr, symbolName));
	Assign(Gurax_CreateProperty(Expr, target));
	Assign(Gurax_CreateProperty(Expr, trailer));
	Assign(Gurax_CreateProperty(Expr, type));
	Assign(Gurax_CreateProperty(Expr, value));
	// Assignment of operator
	Gurax_AssignBinary(Eq, Expr, Expr);
	Gurax_AssignBinary(Eq, Symbol, Expr);
	Gurax_AssignBinary(Eq, Expr, Symbol);
	Gurax_AssignBinary(Ne, Expr, Expr);
	Gurax_AssignBinary(Ne, Symbol, Expr);
	Gurax_AssignBinary(Ne, Expr, Symbol);
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
		return GetExpr().HasPureSymbol(dynamic_cast<const Value_Symbol*>(pValue)->GetSymbol());
	}
	return false;
}

bool Value_Expr::IsLessThan(const Value* pValue) const
{
	return IsSameType(pValue)?
		GetExpr().IsLessThan(dynamic_cast<const Value_Expr*>(pValue)->GetExpr()) :
		GetVType().IsLessThan(pValue->GetVType());
}

String Value_Expr::ToString(const StringStyle& ss) const
{
	String strEntity;
	if (const Symbol* pSymbol = GetExpr().GetPureSymbol()) {
		strEntity = pSymbol->ToString(ss);
	} else {
		if (ss.IsQuoteSymbol()) strEntity += "`";
		strEntity += GetExpr().ToString(ss);
	}
	if (!ss.IsBracket()) {
		return strEntity;
	} else if (GetExpr().GetPUnitFirst()) {
		return ToStringGeneric(ss, String().Format("%s:PUnit#%zu",
					strEntity.c_str(), GetExpr().GetPUnitFirst()->GetSeqId()));
	} else {
		return ToStringGeneric(ss, strEntity);
	}
	return strEntity;
}

}
