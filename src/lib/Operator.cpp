//==============================================================================
// Operator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Operator
//------------------------------------------------------------------------------
Operator* Operator::_operatorTbl[static_cast<size_t>(OpType::max)] = {};

// Unary operators
Operator* Operator::Inv				= new Operator(OpStyle::OpPreUnary,		"~",			OpType::Inv);
Operator* Operator::Neg				= new Operator(OpStyle::OpPreUnary,		"-",			OpType::Neg);
Operator* Operator::Not				= new Operator(OpStyle::OpPreUnary,		"!",			OpType::Not);
Operator* Operator::Pos				= new Operator(OpStyle::OpPreUnary,		"+",			OpType::Pos);
Operator* Operator::Question		= new Operator(OpStyle::OpPreUnary,		"?",			OpType::Question);
Operator* Operator::Quote			= new Operator_Quote();
// Post-unary operators
Operator* Operator::PostMod			= new Operator(OpStyle::OpPostUnary,	"%",			OpType::PostMod);
Operator* Operator::PostModMod		= new Operator(OpStyle::OpPostUnary,	"%%",			OpType::PostModMod);
Operator* Operator::PostMul			= new Operator(OpStyle::OpPostUnary,	"*",			OpType::PostMul);
Operator* Operator::PostPos			= new Operator(OpStyle::OpPostUnary,	"+",			OpType::PostPos);
Operator* Operator::PostQuestion	= new Operator(OpStyle::OpPostUnary,	"?",			OpType::PostQuestion);
Operator* Operator::PostSeq			= new Operator(OpStyle::OpPostUnary,	"..",			OpType::PostSeq);
// Binary operators
Operator* Operator::Add				= new Operator(OpStyle::OpBinary,		"+",			OpType::Add);
Operator* Operator::And				= new Operator(OpStyle::OpBinary,		"&",			OpType::And);
Operator* Operator::AndAnd			= new Operator_AndAnd();
Operator* Operator::Cmp				= new Operator(OpStyle::OpBinary,		"<=>",			OpType::Cmp);
Operator* Operator::Concat			= new Operator(OpStyle::OpBinary,		"|+|",			OpType::Concat, Operator::Flag::NoMap);
Operator* Operator::Contains		= new Operator(OpStyle::OpBinary,		"in",			OpType::Contains, Operator::Flag::NoMap);
Operator* Operator::Cross			= new Operator(OpStyle::OpBinary,		"|^|",			OpType::Cross, Operator::Flag::NoMap);
Operator* Operator::Difference		= new Operator(OpStyle::OpBinary,		"|-|",			OpType::Difference, Operator::Flag::NoMap);
Operator* Operator::Div				= new Operator(OpStyle::OpBinary,		"/",			OpType::Div);
Operator* Operator::Dot				= new Operator(OpStyle::OpBinary,		"|.|",			OpType::Dot, Operator::Flag::NoMap);
Operator* Operator::Eq				= new Operator(OpStyle::OpBinary,		"==",			OpType::Eq);
Operator* Operator::Gear			= new Operator(OpStyle::OpBinary,		"|*|",			OpType::Gear, Operator::Flag::NoMap);
Operator* Operator::Ge				= new Operator(OpStyle::OpBinary,		">=",			OpType::Ge);
Operator* Operator::Gt				= new Operator(OpStyle::OpBinary,		">",			OpType::Gt);
Operator* Operator::Intersection	= new Operator(OpStyle::OpBinary,		"|&|",			OpType::Intersection, Operator::Flag::NoMap);
Operator* Operator::Le				= new Operator(OpStyle::OpBinary,		"<=",			OpType::Le);
Operator* Operator::Lt				= new Operator(OpStyle::OpBinary,		"<",			OpType::Lt);
Operator* Operator::Mod				= new Operator(OpStyle::OpBinary,		"%",			OpType::Mod);
Operator* Operator::ModMod			= new Operator(OpStyle::OpBinary,		"%%",			OpType::ModMod);
Operator* Operator::Mul				= new Operator(OpStyle::OpBinary,		"*",			OpType::Mul);
Operator* Operator::Ne				= new Operator(OpStyle::OpBinary,		"!=",			OpType::Ne);
Operator* Operator::Or				= new Operator(OpStyle::OpBinary,		"|",			OpType::Or);
Operator* Operator::OrOr			= new Operator_OrOr();
Operator* Operator::Pair			= new Operator(OpStyle::OpBinary,		"=>",			OpType::Pair, Operator::Flag::NoMap);
Operator* Operator::Pow				= new Operator(OpStyle::OpBinary,		"**",			OpType::Pow);
Operator* Operator::Seq				= new Operator(OpStyle::OpBinary,		"..",			OpType::Seq);
Operator* Operator::Shl				= new Operator(OpStyle::OpBinary,		"<<",			OpType::Shl);
Operator* Operator::Shr				= new Operator(OpStyle::OpBinary,		">>",			OpType::Shr);
Operator* Operator::Sub				= new Operator(OpStyle::OpBinary,		"-",			OpType::Sub);
Operator* Operator::Union			= new Operator(OpStyle::OpBinary,		"|||",			OpType::Union, Operator::Flag::NoMap);
Operator* Operator::Xor				= new Operator(OpStyle::OpBinary,		"^",			OpType::Xor);
// Mathematical functions
Operator* Operator::math_Abs		= new Operator(OpStyle::MathUnary,		"Abs",			OpType::math_Abs);
Operator* Operator::math_Acos		= new Operator(OpStyle::MathUnary,		"Acos",			OpType::math_Acos);
Operator* Operator::math_Arg		= new Operator(OpStyle::MathUnary,		"Arg",			OpType::math_Arg);
Operator* Operator::math_Asin		= new Operator(OpStyle::MathUnary,		"Asin",			OpType::math_Asin);
Operator* Operator::math_Atan		= new Operator(OpStyle::MathUnary,		"Atan",			OpType::math_Atan);
Operator* Operator::math_Atan2		= new Operator(OpStyle::MathBinary,		"Atan2",		OpType::math_Atan2);
Operator* Operator::math_Ceil		= new Operator(OpStyle::MathUnary,		"Ceil",			OpType::math_Ceil);
Operator* Operator::math_Conj		= new Operator(OpStyle::MathUnary,		"Conj",			OpType::math_Conj);
Operator* Operator::math_Cos		= new Operator(OpStyle::MathUnary,		"Cos",			OpType::math_Cos);
Operator* Operator::math_Cosh		= new Operator(OpStyle::MathUnary,		"Cosh",			OpType::math_Cosh);
Operator* Operator::math_Covariance = new Operator(OpStyle::MathUnary,		"Covariance",	OpType::math_Covariance);
Operator* Operator::math_Cross		= new Operator(OpStyle::MathUnary,		"Cross",		OpType::math_Cross);
Operator* Operator::math_Delta		= new Operator(OpStyle::MathUnary,		"Delta",		OpType::math_Delta);
Operator* Operator::math_Dot		= new Operator(OpStyle::MathUnary,		"Dot",			OpType::math_Dot);
Operator* Operator::math_Exp		= new Operator(OpStyle::MathUnary,		"Exp",			OpType::math_Exp);
Operator* Operator::math_Floor		= new Operator(OpStyle::MathUnary,		"Floor",		OpType::math_Floor);
Operator* Operator::math_Hypot		= new Operator(OpStyle::MathBinary,		"Hypot",		OpType::math_Hypot);
Operator* Operator::math_Imag		= new Operator(OpStyle::MathUnary,		"Imag",			OpType::math_Imag);
Operator* Operator::math_Log		= new Operator(OpStyle::MathUnary,		"Log",			OpType::math_Log);
Operator* Operator::math_Log10		= new Operator(OpStyle::MathUnary,		"Log10",		OpType::math_Log10);
Operator* Operator::math_Norm		= new Operator(OpStyle::MathUnary,		"Norm",			OpType::math_Norm);
Operator* Operator::math_Real		= new Operator(OpStyle::MathUnary,		"Real",			OpType::math_Real);
Operator* Operator::math_Relu		= new Operator(OpStyle::MathUnary,		"Relu",			OpType::math_Relu);
Operator* Operator::math_Sigmoid	= new Operator(OpStyle::MathUnary,		"Sigmoid",		OpType::math_Sigmoid);
Operator* Operator::math_Sin		= new Operator(OpStyle::MathUnary,		"Sin",			OpType::math_Sin);
Operator* Operator::math_Sinh		= new Operator(OpStyle::MathUnary,		"Sinh",			OpType::math_Sinh);
Operator* Operator::math_Sqrt		= new Operator(OpStyle::MathUnary,		"Sqrt",			OpType::math_Sqrt);
Operator* Operator::math_Tan		= new Operator(OpStyle::MathUnary,		"Tan",			OpType::math_Tan);
Operator* Operator::math_Tanh		= new Operator(OpStyle::MathUnary,		"Tanh",			OpType::math_Tanh);
Operator* Operator::math_Unitstep	= new Operator(OpStyle::MathUnary,		"Unitstep",		OpType::math_Unitstep);

Operator::Operator(OpStyle opStyle, const char* symbol, OpType opType, Flags flags) :
	_opStyle(opStyle), _symbol(symbol), _opType(opType), _flags(flags),
	_binaryFlag(opStyle == OpStyle::OpBinary || opStyle == OpStyle::MathBinary)
{
	_operatorTbl[static_cast<size_t>(opType)] = this;
}

const TokenType& Operator::GetTokenType() const
{
	return TokenType::OpTypeToTokenType(_opType);
}

const OpEntry* Operator::FindMatchedEntry(const VType& vtype) const
{
	const OpEntry* pOpEntry = nullptr;
	if ((pOpEntry = LookupEntry(vtype))) return pOpEntry;
	if ((pOpEntry = LookupEntry(VTYPE_Any))) return pOpEntry;
	if (vtype.IsIdentical(VTYPE_Undefined)) return &OpEntry::Empty;
	Error::Issue(ErrorType::TypeError, "unsupported %s operation: %s",
				 IsMathUnary()? "math" : "unary", ToString(vtype).c_str());
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
				 IsMathBinary()? "math" : "binary", ToString(vtypeL, vtypeR).c_str());
	return nullptr;
}

Value* Operator::EvalUnary(Processor& processor, Value& value) const
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
	const OpEntry* pOpEntry = FindMatchedEntry(value.GetVType());
	return pOpEntry? pOpEntry->EvalUnary(processor, value) : Value::undefined();
}

Value* Operator::EvalBinary(Processor& processor, Value& valueL, Value& valueR) const
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
	const OpEntry* pOpEntry = FindMatchedEntry(valueL.GetVType(), valueR.GetVType());
	return pOpEntry? pOpEntry->EvalBinary(processor, valueL, valueR) : Value::undefined();
}

String Operator::ToString(const VType& vtype) const
{
	String str;
	if (IsOpPreUnary()) {
		str.Format("%s%s", GetSymbol(), vtype.MakeFullName().c_str());
	} else if (IsOpPostUnary()) {
		str.Format("%s%s", vtype.MakeFullName().c_str(), GetSymbol());
	} else if (IsMathUnary()) {
		str.Format("math.%s(%s)", GetSymbol(), vtype.MakeFullName().c_str());
	}
	return str;
}

String Operator::ToString(const VType& vtypeL, const VType& vtypeR) const
{
	String str;
	if (IsOpBinary()) {
		str.Format("%s %s %s", vtypeL.MakeFullName().c_str(), GetSymbol(), vtypeR.MakeFullName().c_str());
	} else if (IsMathBinary()) {
		str.Format("math.%s(%s, %s)", GetSymbol(), vtypeL.MakeFullName().c_str(), vtypeR.MakeFullName().c_str());
	}
	return str;
}

//------------------------------------------------------------------------------
// Operator_Quote
//------------------------------------------------------------------------------
void Operator_Quote::ComposeUnary(Composer& composer, Expr_Unary& expr) const
{
	Expr& exprChild = expr.GetExprChild();
	PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
	composer.Add_Jump(expr);
	composer.ComposeAsSequence(exprChild);
	composer.Add_Return(exprChild);
	pPUnitOfBranch->SetPUnitCont(composer.PeekPUnitCont());
	composer.Add_Value(new Value_Expr(exprChild.Reference()), expr);				// [Result]
}

//------------------------------------------------------------------------------
// Operator_AndAnd
//------------------------------------------------------------------------------
void Operator_AndAnd::ComposeBinary(Composer& composer, Expr_Binary& expr) const
{
	expr.GetExprLeft().ComposeOrNil(composer);						// [Bool]
	PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
	composer.Add_JumpIfNot(PUnit::BranchMode::Keep, expr);
	expr.GetExprRight().ComposeOrNil(composer);					// [Bool]
	pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
	composer.Add_NoOperation(expr);
}

//------------------------------------------------------------------------------
// Operator_OrOr
//------------------------------------------------------------------------------
void Operator_OrOr::ComposeBinary(Composer& composer, Expr_Binary& expr) const
{
	expr.GetExprLeft().ComposeOrNil(composer);						// [Bool]
	PUnit* pPUnitOfBranch = composer.PeekPUnitCont();
	composer.Add_JumpIf(PUnit::BranchMode::Keep, expr);
	expr.GetExprRight().ComposeOrNil(composer);					// [Bool]
	pPUnitOfBranch->SetPUnitBranchDest(composer.PeekPUnitCont());
	composer.Add_NoOperation(expr);
}

//------------------------------------------------------------------------------
// OpEntry
//------------------------------------------------------------------------------
const OpEntry OpEntry::Empty;

Value* OpEntry::EvalUnary(Processor& processor, Value& value) const
{
	return Value::undefined();
}

Value* OpEntry::EvalBinary(Processor& processor, Value& valueL, Value& valueR) const
{
	return Value::undefined();
}

//------------------------------------------------------------------------------
// OpEntryMap
//------------------------------------------------------------------------------
void OpEntryMap::Assign(UInt64 key, OpEntry* pOpEntry)
{
	auto pPair = find(key);
	if (pPair == end()) {
		(*this)[key] = pOpEntry;
	} else {
		delete pPair->second;
		pPair->second = pOpEntry;
	}
}

}
