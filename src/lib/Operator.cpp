//==============================================================================
// Operator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Operator
//------------------------------------------------------------------------------
Operator* Operator::_operatorTbl[static_cast<size_t>(OpType::max)] = {};
OperatorMap Operator::_operatorMap_Unary;
OperatorMap Operator::_operatorMap_UnaryPost;
OperatorMap Operator::_operatorMap_Binary;
OperatorMap Operator::_operatorMap_Math;

// Unary operators
Operator* Operator::Inv				= new Operator(OpStyle::Unary,			"Inv",			"~",			OpType::Inv, Operator::Flag::Map | Operator::Flag::BitOp);
Operator* Operator::Neg				= new Operator(OpStyle::Unary,			"Neg",			"-",			OpType::Neg);
Operator* Operator::Not				= new Operator(OpStyle::Unary,			"Not",			"!",			OpType::Not, Operator::Flag::Map | Operator::Flag::LogicOp);
Operator* Operator::Pos				= new Operator(OpStyle::Unary,			"Pos",			"+",			OpType::Pos);
Operator* Operator::Question		= new Operator(OpStyle::Unary,			"Question",		"?",			OpType::Question);
Operator* Operator::PreAnd			= new Operator_PreAnd();
Operator* Operator::PreMod			= new Operator(OpStyle::Unary,			"PreMod",		"%",			OpType::PreMod);
Operator* Operator::PreModMod		= new Operator(OpStyle::Unary,			"PreModMod",	"%%",			OpType::PreModMod);
Operator* Operator::PreMul			= new Operator(OpStyle::Unary,			"PreMul",		"*",			OpType::PreMul);
Operator* Operator::Quote			= new Operator_Quote();
// Post-unary operators
Operator* Operator::PostMod			= new Operator(OpStyle::UnaryPost,		"PostMod",		"%",			OpType::PostMod);
Operator* Operator::PostModMod		= new Operator(OpStyle::UnaryPost,		"PostModMod",	"%%",			OpType::PostModMod);
Operator* Operator::PostMul			= new Operator(OpStyle::UnaryPost,		"PostMul",		"*",			OpType::PostMul);
Operator* Operator::PostPos			= new Operator(OpStyle::UnaryPost,		"PostPos",		"+",			OpType::PostPos);
Operator* Operator::PostQuestion	= new Operator(OpStyle::UnaryPost,		"PostQuestion",	"?",			OpType::PostQuestion);
Operator* Operator::PostSeq			= new Operator(OpStyle::UnaryPost,		"PostSeq",		"..",			OpType::PostSeq);
// Binary operators
Operator* Operator::Add				= new Operator(OpStyle::Binary,			"Add",			"+",			OpType::Add);
Operator* Operator::And				= new Operator(OpStyle::Binary,			"And",			"&",			OpType::And, Operator::Flag::Map | Operator::Flag::BitOp);
Operator* Operator::AndAnd			= new Operator_AndAnd();
Operator* Operator::As				= new Operator(OpStyle::Binary,			"As",			"as",			OpType::As);
Operator* Operator::Cmp				= new Operator(OpStyle::Binary,			"Cmp",			"<=>",			OpType::Cmp);
Operator* Operator::Concat			= new Operator(OpStyle::Binary,			"Concat",		"|+|",			OpType::Concat, Operator::Flag::NoMap);
Operator* Operator::Contains		= new Operator(OpStyle::Binary,			"Contains",		"in",			OpType::Contains, Operator::Flag::NoMap);
Operator* Operator::Cross			= new Operator(OpStyle::Binary,			"Cross",		"|^|",			OpType::Cross, Operator::Flag::NoMap);
Operator* Operator::Difference		= new Operator(OpStyle::Binary,			"Difference",	"|-|",			OpType::Difference, Operator::Flag::NoMap);
Operator* Operator::Div				= new Operator(OpStyle::Binary,			"Div",			"/",			OpType::Div);
Operator* Operator::Dot				= new Operator(OpStyle::Binary,			"Dot",			"|.|",			OpType::Dot, Operator::Flag::NoMap);
Operator* Operator::Eq				= new Operator(OpStyle::Binary,			"Eq",			"==",			OpType::Eq);
Operator* Operator::Gear			= new Operator(OpStyle::Binary,			"Gear",			"|*|",			OpType::Gear, Operator::Flag::NoMap);
Operator* Operator::Ge				= new Operator(OpStyle::Binary,			"Ge",			">=",			OpType::Ge);
Operator* Operator::Gt				= new Operator(OpStyle::Binary,			"Gt",			">",			OpType::Gt);
Operator* Operator::Intersection	= new Operator(OpStyle::Binary,			"Intersection",	"|&|",			OpType::Intersection, Operator::Flag::NoMap);
Operator* Operator::Le				= new Operator(OpStyle::Binary,			"Le",			"<=",			OpType::Le);
Operator* Operator::Lt				= new Operator(OpStyle::Binary,			"Lt",			"<",			OpType::Lt);
Operator* Operator::Mod				= new Operator(OpStyle::Binary,			"Mod",			"%",			OpType::Mod);
Operator* Operator::ModMod			= new Operator(OpStyle::Binary,			"ModMod",		"%%",			OpType::ModMod);
Operator* Operator::Mul				= new Operator(OpStyle::Binary,			"Mul",			"*",			OpType::Mul);
Operator* Operator::Ne				= new Operator(OpStyle::Binary,			"Ne",			"!=",			OpType::Ne);
Operator* Operator::Or				= new Operator(OpStyle::Binary,			"Or",			"|",			OpType::Or, Operator::Flag::Map | Operator::Flag::BitOp);
Operator* Operator::OrOr			= new Operator_OrOr();
Operator* Operator::Pair			= new Operator(OpStyle::Binary,			"Pair",			"=>",			OpType::Pair, Operator::Flag::NoMap);
Operator* Operator::Pow				= new Operator(OpStyle::Binary,			"Pow",			"**",			OpType::Pow);
Operator* Operator::Seq				= new Operator(OpStyle::Binary,			"Seq",			"..",			OpType::Seq);
Operator* Operator::Shl				= new Operator(OpStyle::Binary,			"Shl",			"<<",			OpType::Shl, Operator::Flag::Map | Operator::Flag::BitOp);
Operator* Operator::Shr				= new Operator(OpStyle::Binary,			"Shr",			">>",			OpType::Shr, Operator::Flag::Map | Operator::Flag::BitOp);
Operator* Operator::Sub				= new Operator(OpStyle::Binary,			"Sub",			"-",			OpType::Sub);
Operator* Operator::Union			= new Operator(OpStyle::Binary,			"Union",		"|||",			OpType::Union, Operator::Flag::NoMap);
Operator* Operator::Xor				= new Operator(OpStyle::Binary,			"Xor",			"^",			OpType::Xor, Operator::Flag::Map | Operator::Flag::BitOp);
// Mathematical functions
Operator* Operator::math_Abs		= new Operator(OpStyle::MathUnary,		"math.Abs",		"Abs",			OpType::math_Abs);
Operator* Operator::math_Acos		= new Operator(OpStyle::MathUnary,		"math.Acos",	"Acos",			OpType::math_Acos);
Operator* Operator::math_Arg		= new Operator(OpStyle::MathUnary,		"math.Arg",		"Arg",			OpType::math_Arg);
Operator* Operator::math_Asin		= new Operator(OpStyle::MathUnary,		"math.Asin",	"Asin",			OpType::math_Asin);
Operator* Operator::math_Atan		= new Operator(OpStyle::MathUnary,		"math.Atan",	"Atan",			OpType::math_Atan);
Operator* Operator::math_Atan2		= new Operator(OpStyle::MathBinary,		"math.Atan2",	"Atan2",		OpType::math_Atan2);
Operator* Operator::math_Ceil		= new Operator(OpStyle::MathUnary,		"math.Ceil",	"Ceil",			OpType::math_Ceil);
Operator* Operator::math_Conj		= new Operator(OpStyle::MathUnary,		"math.Conj",	"Conj",			OpType::math_Conj);
Operator* Operator::math_Cos		= new Operator(OpStyle::MathUnary,		"math.Cos",		"Cos",			OpType::math_Cos);
Operator* Operator::math_Cosh		= new Operator(OpStyle::MathUnary,		"math.Cosh",	"Cosh",			OpType::math_Cosh);
Operator* Operator::math_Covariance = new Operator(OpStyle::MathUnary,		"math.Covariance", "Covariance",OpType::math_Covariance);
Operator* Operator::math_Cross		= new Operator(OpStyle::MathUnary,		"math.Cross",	"Cross",		OpType::math_Cross);
Operator* Operator::math_Delta		= new Operator(OpStyle::MathUnary,		"math.Delta",	"Delta",		OpType::math_Delta);
Operator* Operator::math_Dot		= new Operator(OpStyle::MathUnary,		"math.Dot",		"Dot",			OpType::math_Dot);
Operator* Operator::math_Exp		= new Operator(OpStyle::MathUnary,		"math.Exp",		"Exp",			OpType::math_Exp);
Operator* Operator::math_Floor		= new Operator(OpStyle::MathUnary,		"math.Floor",	"Floor",		OpType::math_Floor);
Operator* Operator::math_Hypot		= new Operator(OpStyle::MathBinary,		"math.Hypot",	"Hypot",		OpType::math_Hypot);
Operator* Operator::math_Imag		= new Operator(OpStyle::MathUnary,		"math.Imag",	"Imag",			OpType::math_Imag);
Operator* Operator::math_Log		= new Operator(OpStyle::MathUnary,		"math.Log",		"Log",			OpType::math_Log);
Operator* Operator::math_Log10		= new Operator(OpStyle::MathUnary,		"math.Log10",	"Log10",		OpType::math_Log10);
Operator* Operator::math_Norm		= new Operator(OpStyle::MathUnary,		"math.Norm",	"Norm",			OpType::math_Norm);
Operator* Operator::math_Real		= new Operator(OpStyle::MathUnary,		"math.Real",	"Real",			OpType::math_Real);
Operator* Operator::math_Relu		= new Operator(OpStyle::MathUnary,		"math.Relu",	"Relu",			OpType::math_Relu);
Operator* Operator::math_Sigmoid	= new Operator(OpStyle::MathUnary,		"math.Sigmoid",	"Sigmoid",		OpType::math_Sigmoid);
Operator* Operator::math_Sin		= new Operator(OpStyle::MathUnary,		"math.Sin",		"Sin",			OpType::math_Sin);
Operator* Operator::math_Sinh		= new Operator(OpStyle::MathUnary,		"math.Sinh",	"Sinh",			OpType::math_Sinh);
Operator* Operator::math_Sqrt		= new Operator(OpStyle::MathUnary,		"math.Sqrt",	"Sqrt",			OpType::math_Sqrt);
Operator* Operator::math_Tan		= new Operator(OpStyle::MathUnary,		"math.Tan",		"Tan",			OpType::math_Tan);
Operator* Operator::math_Tanh		= new Operator(OpStyle::MathUnary,		"math.Tanh",	"Tanh",			OpType::math_Tanh);
Operator* Operator::math_Unitstep	= new Operator(OpStyle::MathUnary,		"math.Unitstep","Unitstep",		OpType::math_Unitstep);

Operator::Operator(OpStyle opStyle, const char* name, const char* symbol, OpType opType, Flags flags) :
	_opStyle(opStyle), _name(name), _pSymbol(Symbol::Add(symbol)), _opType(opType), _flags(flags)
{
	_operatorTbl[static_cast<size_t>(opType)] = this;
}

void Operator::Bootup()
{
	for (size_t i = 0; i < static_cast<int>(OpType::max); i++) {
		Operator* pOp = _operatorTbl[i];
		const Symbol* pSymbol = pOp->GetSymbol();
		if (pOp->IsUnary()) {
			_operatorMap_Unary.GetMap()[pSymbol] = pOp;
		} else if (pOp->IsUnaryPost()) {
			_operatorMap_UnaryPost.GetMap()[pSymbol] = pOp;
		} else if (pOp->IsBinary()) {
			_operatorMap_Binary.GetMap()[pSymbol] = pOp;
		} else if (pOp->IsMathUnary() || pOp->IsMathBinary()) {
			_operatorMap_Math.GetMap()[pSymbol] = pOp;
		}
	}
}

const Symbol* Operator::GetStyleAsSymbol() const
{
	return
		IsUnary()? Gurax_Symbol(unary) :
		IsUnaryPost()? Gurax_Symbol(unaryPost) :
		IsBinary()? Gurax_Symbol(binary) :
		IsMathUnary()? Gurax_Symbol(mathUnary) :
		IsMathBinary()? Gurax_Symbol(mathBinary) : Symbol::Empty;
}

const TokenType& Operator::GetTokenType() const
{
	return TokenType::OpTypeToTokenType(_opType);
}

Precedence Operator::LookupPrec(const Operator& opLeft, const Operator& opRight)
{
	return Token::LookupPrec(opLeft.GetTokenType(), opRight.GetTokenType());
}

void Operator::AssignEntry(VType& vtype, OpEntry* pOpEntry)
{
	pOpEntry->SetOperatorInfo(this, vtype);
	_opEntryMap.Assign(vtype, pOpEntry);
	vtype.AddOpEntry(pOpEntry);
}

void Operator::AssignEntry(VType& vtypeL, VType& vtypeR, OpEntry* pOpEntry)
{
	pOpEntry->SetOperatorInfo(this, vtypeL, vtypeR);
	_opEntryMap.Assign(vtypeL, vtypeR, pOpEntry);
	vtypeL.AddOpEntry(pOpEntry);
	vtypeR.AddOpEntry(pOpEntry);
}

const OpEntry* Operator::FindMatchedEntry(const VType& vtype) const
{
	const OpEntry* pOpEntry = nullptr;
	if ((pOpEntry = LookupEntry(vtype))) return pOpEntry;
	if ((pOpEntry = LookupEntry(VTYPE_Any))) return pOpEntry;
	if (vtype.IsIdentical(VTYPE_Undefined)) return &OpEntry::Empty;
	Error::Issue(ErrorType::TypeError, "unsupported %s operation: %s",
		IsMathUnary()? "math" : "unary", ToString(StringStyle::Empty, vtype).c_str());
	return nullptr;
}

const OpEntry* Operator::FindMatchedEntry(const VType& vtypeL, const VType& vtypeR) const
{
	const OpEntry* pOpEntry = nullptr;
	if ((pOpEntry = LookupEntry(vtypeL, vtypeR))) return pOpEntry;
	if ((pOpEntry = LookupEntry(vtypeL, VTYPE_Any))) return pOpEntry;
	if ((pOpEntry = LookupEntry(VTYPE_Any, vtypeR))) return pOpEntry;
	if ((pOpEntry = LookupEntry(VTYPE_Any, VTYPE_Any))) return pOpEntry;
	if (vtypeL.IsIdentical(VTYPE_Undefined) || vtypeR.IsIdentical(VTYPE_Undefined)) return &OpEntry::Empty;
	Error::Issue(ErrorType::TypeError, "unsuppported %s operation: %s",
		IsMathBinary()? "math" : "binary", ToString(StringStyle::Empty, vtypeL, vtypeR).c_str());
	return nullptr;
}

const DeclCallable& Operator::GetDeclCallable() const
{
	return
		IsUnary()? *DeclCallable::Unary :
		IsUnaryPost()? *DeclCallable::Unary :
		IsBinary()? (GetMapFlag()? *DeclCallable::Binary : *DeclCallable::Binary_NoMap) :
		IsMathUnary()? *DeclCallable::Unary :
		IsMathBinary()? *DeclCallable::Binary :
		*DeclCallable::Empty;
}

Value* Operator::EvalUnary(Processor& processor, Value& value)
{
	if (GetMapFlag()) {
		if (value.IsList()) {
			RefPtr<Iterator> pIterator(
				new Iterator_UnaryOpImpMap(
					processor.Reference(), this,
					new Value_ArgMapper(value.GenIterator())));
			RefPtr<Value_List> pValueRtn(new Value_List());
			ValueTypedOwner& valueTypedOwner = pValueRtn->GetValueTypedOwner();
			for (;;) {
				RefPtr<Value> pValue(pIterator->NextValue());
				if (!pValue) break;
				valueTypedOwner.Add(pValue.release());
			}
			if (Error::IsIssued()) return Value::nil();
			return pValueRtn.release();
		} else if (value.IsIterator()) {
			RefPtr<Iterator> pIterator(
				new Iterator_UnaryOpImpMap(
					processor.Reference(), this,
					new Value_ArgMapper(value.GenIterator())));
			return new Value_Iterator(pIterator.release());
		}
	}
	const OpEntry* pOpEntry = FindMatchedEntry(value.GetVTypeCustom());
	return pOpEntry? pOpEntry->EvalUnary(processor, value) : Value::undefined();
}

Value* Operator::EvalBinary(Processor& processor, Value& valueL, Value& valueR)
{
	if (GetMapFlag()) {
		if (valueL.IsIterator() || valueR.IsIterator()) {
			RefPtr<Iterator> pIterator(
				new Iterator_BinaryOpImpMap(
					processor.Reference(), this,
					valueL.IsIterable()? new Value_ArgMapper(valueL.GenIterator()) : valueL.Reference(),
					valueR.IsIterable()? new Value_ArgMapper(valueR.GenIterator()) : valueR.Reference()));
			return new Value_Iterator(pIterator.release());
		} else if (valueL.IsList() || valueR.IsList()) {
			RefPtr<Iterator> pIterator(
				new Iterator_BinaryOpImpMap(
					processor.Reference(), this,
					valueL.IsIterable()? new Value_ArgMapper(valueL.GenIterator()) : valueL.Reference(),
					valueR.IsIterable()? new Value_ArgMapper(valueR.GenIterator()) : valueR.Reference()));
			RefPtr<Value_List> pValueRtn(new Value_List());
			ValueTypedOwner& valueTypedOwner = pValueRtn->GetValueTypedOwner();
			for (;;) {
				RefPtr<Value> pValue(pIterator->NextValue());
				if (!pValue) break;
				valueTypedOwner.Add(pValue.release());
			}
			if (Error::IsIssued()) return Value::nil();
			return pValueRtn.release();
		}
	}
	const OpEntry* pOpEntry = FindMatchedEntry(valueL.GetVTypeCustom(), valueR.GetVTypeCustom());
	return pOpEntry? pOpEntry->EvalBinary(processor, valueL, valueR) : Value::undefined();
}

void Operator::ComposeUnary(Composer& composer, Expr_UnaryOp& expr) const
{
	expr.GetExprChild().ComposeOrNil(composer);									// [Any]
	composer.Add_UnaryOp(expr.GetOperator(), expr);								// [Result]
}

void Operator::ComposeBinary(Composer& composer, Expr_BinaryOp& expr) const
{
	expr.GetExprLeft().ComposeOrNil(composer);									// [Left]
	expr.GetExprRight().ComposeOrNil(composer);									// [Left Right]
	composer.Add_BinaryOp(expr.GetOperator(), expr);							// [Result]
}

Operator* Operator::LookupUnary(const Symbol* pSymbol)
{
	return _operatorMap_Unary.Lookup(pSymbol);
}

Operator* Operator::LookupUnaryPost(const Symbol* pSymbol)
{
	return _operatorMap_UnaryPost.Lookup(pSymbol);
}

Operator* Operator::LookupBinary(const Symbol* pSymbol)
{
	return _operatorMap_Binary.Lookup(pSymbol);
}

Operator* Operator::LookupMath(const Symbol* pSymbol)
{
	return _operatorMap_Math.Lookup(pSymbol);
}

String Operator::ToString(const StringStyle& ss) const
{
	String str =
		IsUnary()? String().Format("Operator:Unary:%s:%s", GetName(), GetSymbol()->GetName()) :
		IsUnaryPost()? String().Format("Operator:UnaryPost:%s:%s", GetName(), GetSymbol()->GetName()) :
		IsBinary()? String().Format("Operator:Binary:%s:%s", GetName(), GetSymbol()->GetName()) :
		IsMathUnary()? String().Format("Operator:MathUnary:%s", GetSymbol()->GetName()) :
		IsMathBinary()? String().Format("Operator:MathBinary:%s", GetSymbol()->GetName()) :
		String::Empty;
	str += ":";
	str += GetDeclCallable().ToString(ss);
	return str;
}

String Operator::ToString(const StringStyle& ss, const VType& vtype) const
{
	return
		IsUnary()? String().Format("%s%s", GetSymbol()->GetName(), vtype.MakeFullName().c_str()) :
		IsUnaryPost()? String().Format("%s%s", vtype.MakeFullName().c_str(), GetSymbol()->GetName()) :
		IsMathUnary()? String().Format("math.%s(%s)", GetSymbol()->GetName(), vtype.MakeFullName().c_str()) :
		String::Empty;
}

String Operator::ToString(const StringStyle& ss, const VType& vtypeL, const VType& vtypeR) const
{
	return
		IsBinary()? String().Format(ss.IsCram()? "%s%s%s" : "%s %s %s",
			vtypeL.MakeFullName().c_str(), GetSymbol()->GetName(), vtypeR.MakeFullName().c_str()) :
		IsMathBinary()? String().Format(ss.IsCram()? "math.%s(%s,%s)" : "math.%s(%s, %s)",
			GetSymbol()->GetName(), vtypeL.MakeFullName().c_str(), vtypeR.MakeFullName().c_str()) :
		String::Empty;
}

//------------------------------------------------------------------------------
// OperatorMap
//------------------------------------------------------------------------------
Operator* OperatorMap::Lookup(const Symbol* pSymbol) const
{
	auto iter = _map.find(pSymbol);
	return (iter == _map.end())? nullptr : iter->second;
}

//------------------------------------------------------------------------------
// Operator_PreAnd
//------------------------------------------------------------------------------
void Operator_PreAnd::ComposeUnary(Composer& composer, Expr_UnaryOp& expr) const
{
	Expr& exprChild = expr.GetExprChild();
	exprChild.ComposeReferencer(composer);										// [Result]
}

//------------------------------------------------------------------------------
// Operator_Quote
//------------------------------------------------------------------------------
void Operator_Quote::ComposeUnary(Composer& composer, Expr_UnaryOp& expr) const
{
	Expr& exprChild = expr.GetExprChild();
	PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
	composer.Add_Jump(expr);
	composer.ComposeAsSequence(exprChild);
	composer.Add_Return(exprChild);
	pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
	composer.Add_Value(new Value_Expr(exprChild.Reference()), expr);			// [Result]
}

//------------------------------------------------------------------------------
// Operator_AndAnd
//------------------------------------------------------------------------------
void Operator_AndAnd::ComposeBinary(Composer& composer, Expr_BinaryOp& expr) const
{
	expr.GetExprLeft().ComposeOrNil(composer);									// [Bool]
	PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
	composer.Add_JumpIfNot(PUnit::BranchMode::Keep, expr);
	expr.GetExprRight().ComposeOrNil(composer);									// [Bool]
	pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
	composer.Add_NoOperation(expr);
}

//------------------------------------------------------------------------------
// Operator_OrOr
//------------------------------------------------------------------------------
void Operator_OrOr::ComposeBinary(Composer& composer, Expr_BinaryOp& expr) const
{
	expr.GetExprLeft().ComposeOrNil(composer);									// [Bool]
	PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
	composer.Add_JumpIf(PUnit::BranchMode::Keep, expr);
	expr.GetExprRight().ComposeOrNil(composer);									// [Bool]
	pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
	composer.Add_NoOperation(expr);
}

//------------------------------------------------------------------------------
// OpEntry
//------------------------------------------------------------------------------
const OpEntry OpEntry::Empty;

OpEntry::OpEntry() : _pOperator(nullptr), _pVTypeL(&VTYPE_Undefined), _pVTypeR(&VTYPE_Undefined) {}

bool OpEntry::IsBinary() const
{
	return !_pVTypeL->IsIdentical(VTYPE_Undefined) && !_pVTypeR->IsIdentical(VTYPE_Undefined);
}

void OpEntry::ReassignEntry(VType& vtype)
{
	_pOperator->GetOpEntryMap().Assign(vtype, this);
}

void OpEntry::ReassignEntry(VType& vtypeL, VType& vtypeR)
{
	_pOperator->GetOpEntryMap().Assign(vtypeL, vtypeR, this);
}

Value* OpEntry::EvalUnary(Processor& processor, Value& value) const
{
	return Value::undefined();
}

Value* OpEntry::EvalBinary(Processor& processor, Value& valueL, Value& valueR) const
{
	return Value::undefined();
}

//------------------------------------------------------------------------------
// OpEntryCustom_Unary
//------------------------------------------------------------------------------
Value* OpEntryCustom_Unary::EvalUnary(Processor& processor, Value& value) const
{
	return _pValueFunct->EvalEasy(processor, value.Reference());
}

//------------------------------------------------------------------------------
// OpEntryCustom_Binary
//------------------------------------------------------------------------------
Value* OpEntryCustom_Binary::EvalBinary(Processor& processor, Value& valueL, Value& valueR) const
{
	return _pValueFunct->EvalEasy(processor, valueL.Reference(), valueR.Reference());
}

//------------------------------------------------------------------------------
// OpEntryMap
//------------------------------------------------------------------------------
void OpEntryMap::Assign(UInt64 key, OpEntry* pOpEntry)
{
	auto pPair = _map.find(key);
	if (pPair == _map.end()) {
		_map[key] = pOpEntry;
	} else {
		delete pPair->second;
		pPair->second = pOpEntry;
	}
}

}
