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
Operator* Operator::Quote			= new Operator(OpStyle::OpPreUnary,		"`",			OpType::Quote);
// Post-unary operators
Operator* Operator::PostMod			= new Operator(OpStyle::OpPostUnary,	"%",			OpType::PostMod);
Operator* Operator::PostMul			= new Operator(OpStyle::OpPostUnary,	"*",			OpType::PostMul);
Operator* Operator::PostPos			= new Operator(OpStyle::OpPostUnary,	"+",			OpType::PostPos);
Operator* Operator::PostQuestion	= new Operator(OpStyle::OpPostUnary,	"?",			OpType::PostQuestion);
Operator* Operator::PostSeq			= new Operator(OpStyle::OpPostUnary,	"..",			OpType::PostSeq);
// Binary operators
Operator* Operator::Add				= new Operator(OpStyle::OpBinary,		"+",			OpType::Add);
Operator* Operator::And				= new Operator(OpStyle::OpBinary,		"&",			OpType::And);
Operator* Operator::AndAnd			= new Operator(OpStyle::OpBinary,		"&&",			OpType::AndAnd);
Operator* Operator::Cmp				= new Operator(OpStyle::OpBinary,		"<=>",			OpType::Cmp);
Operator* Operator::Concat			= new Operator(OpStyle::OpBinary,		"|+|",			OpType::Concat);
Operator* Operator::Contains		= new Operator(OpStyle::OpBinary,		"in",			OpType::Contains);
Operator* Operator::Cross			= new Operator(OpStyle::OpBinary,		"|^|",			OpType::Cross);
Operator* Operator::Difference		= new Operator(OpStyle::OpBinary,		"|-|",			OpType::Difference);
Operator* Operator::Div				= new Operator(OpStyle::OpBinary,		"/",			OpType::Div);
Operator* Operator::Dot				= new Operator(OpStyle::OpBinary,		"|.|",			OpType::Dot);
Operator* Operator::Eq				= new Operator(OpStyle::OpBinary,		"==",			OpType::Eq);
Operator* Operator::Gear			= new Operator(OpStyle::OpBinary,		"|*|",			OpType::Gear);
Operator* Operator::Ge				= new Operator(OpStyle::OpBinary,		">=",			OpType::Ge);
Operator* Operator::Gt				= new Operator(OpStyle::OpBinary,		">",			OpType::Gt);
Operator* Operator::Intersection	= new Operator(OpStyle::OpBinary,		"|&|",			OpType::Intersection);
Operator* Operator::Le				= new Operator(OpStyle::OpBinary,		"<=",			OpType::Le);
Operator* Operator::Lt				= new Operator(OpStyle::OpBinary,		"<",			OpType::Lt);
Operator* Operator::Mod				= new Operator(OpStyle::OpBinary,		"%",			OpType::Mod);
Operator* Operator::ModMod			= new Operator(OpStyle::OpBinary,		"%%",			OpType::ModMod);
Operator* Operator::Mul				= new Operator(OpStyle::OpBinary,		"*",			OpType::Mul);
Operator* Operator::Ne				= new Operator(OpStyle::OpBinary,		"!=",			OpType::Ne);
Operator* Operator::Or				= new Operator(OpStyle::OpBinary,		"|",			OpType::Or);
Operator* Operator::OrOr			= new Operator(OpStyle::OpBinary,		"||",			OpType::OrOr);
Operator* Operator::Pair			= new Operator(OpStyle::OpBinary,		"=>",			OpType::Pair);
Operator* Operator::Pow				= new Operator(OpStyle::OpBinary,		"**",			OpType::Pow);
Operator* Operator::Seq				= new Operator(OpStyle::OpBinary,		"..",			OpType::Seq);
Operator* Operator::Shl				= new Operator(OpStyle::OpBinary,		"<<",			OpType::Shl);
Operator* Operator::Shr				= new Operator(OpStyle::OpBinary,		">>",			OpType::Shr);
Operator* Operator::Sub				= new Operator(OpStyle::OpBinary,		"-",			OpType::Sub);
Operator* Operator::Union			= new Operator(OpStyle::OpBinary,		"|||",			OpType::Union);
Operator* Operator::Xor				= new Operator(OpStyle::OpBinary,		"^",			OpType::Xor);
// Mathematical functions
Operator* Operator::math_abs		= new Operator(OpStyle::MathUnary,		"abs",			OpType::math_abs);
Operator* Operator::math_acos		= new Operator(OpStyle::MathUnary,		"acos",			OpType::math_acos);
Operator* Operator::math_arg		= new Operator(OpStyle::MathUnary,		"arg",			OpType::math_arg);
Operator* Operator::math_asin		= new Operator(OpStyle::MathUnary,		"asin",			OpType::math_asin);
Operator* Operator::math_atan		= new Operator(OpStyle::MathUnary,		"atan",			OpType::math_atan);
Operator* Operator::math_atan2		= new Operator(OpStyle::MathBinary,		"atan2",		OpType::math_atan2);
Operator* Operator::math_ceil		= new Operator(OpStyle::MathUnary,		"ceil",			OpType::math_ceil);
Operator* Operator::math_conj		= new Operator(OpStyle::MathUnary,		"conj",			OpType::math_conj);
Operator* Operator::math_cos		= new Operator(OpStyle::MathUnary,		"cos",			OpType::math_cos);
Operator* Operator::math_cosh		= new Operator(OpStyle::MathUnary,		"cosh",			OpType::math_cosh);
Operator* Operator::math_covariance = new Operator(OpStyle::MathUnary,		"covariance",	OpType::math_covariance);
Operator* Operator::math_cross		= new Operator(OpStyle::MathUnary,		"cross",		OpType::math_cross);
Operator* Operator::math_delta		= new Operator(OpStyle::MathUnary,		"delta",		OpType::math_delta);
Operator* Operator::math_dot		= new Operator(OpStyle::MathUnary,		"dot",			OpType::math_dot);
Operator* Operator::math_exp		= new Operator(OpStyle::MathUnary,		"exp",			OpType::math_exp);
Operator* Operator::math_floor		= new Operator(OpStyle::MathUnary,		"floor",		OpType::math_floor);
Operator* Operator::math_hypot		= new Operator(OpStyle::MathBinary,		"hypot",		OpType::math_hypot);
Operator* Operator::math_imag		= new Operator(OpStyle::MathUnary,		"imag",			OpType::math_imag);
Operator* Operator::math_log		= new Operator(OpStyle::MathUnary,		"log",			OpType::math_log);
Operator* Operator::math_log10		= new Operator(OpStyle::MathUnary,		"log10",		OpType::math_log10);
Operator* Operator::math_norm		= new Operator(OpStyle::MathUnary,		"norm",			OpType::math_norm);
Operator* Operator::math_real		= new Operator(OpStyle::MathUnary,		"real",			OpType::math_real);
Operator* Operator::math_relu		= new Operator(OpStyle::MathUnary,		"relu",			OpType::math_relu);
Operator* Operator::math_sigmoid	= new Operator(OpStyle::MathUnary,		"sigmoid",		OpType::math_sigmoid);
Operator* Operator::math_sin		= new Operator(OpStyle::MathUnary,		"sin",			OpType::math_sin);
Operator* Operator::math_sinh		= new Operator(OpStyle::MathUnary,		"sinh",			OpType::math_sinh);
Operator* Operator::math_sqrt		= new Operator(OpStyle::MathUnary,		"sqrt",			OpType::math_sqrt);
Operator* Operator::math_tan		= new Operator(OpStyle::MathUnary,		"tan",			OpType::math_tan);
Operator* Operator::math_tanh		= new Operator(OpStyle::MathUnary,		"tanh",			OpType::math_tanh);
Operator* Operator::math_unitstep	= new Operator(OpStyle::MathUnary,		"unitstep",		OpType::math_unitstep);

Operator::Operator(OpStyle opStyle, const char* symbol, OpType opType) :
	_opStyle(opStyle), _symbol(symbol), _opType(opType),
	_binaryFlag(opStyle == OpStyle::OpBinary || opStyle == OpStyle::MathBinary)
{
	_operatorTbl[static_cast<size_t>(opType)] = this;
}

const TokenType& Operator::GetTokenType() const
{
	return TokenType::OpTypeToTokenType(_opType);
}

Value* Operator::EvalUnary(const Value* pValue) const
{
	if (!pValue) return nullptr;
	const OpEntry* pOpEntry = LookupEntry(pValue->GetVType());
	if (pOpEntry) return pOpEntry->EvalUnary(pValue);
	Error::Issue(ErrorType::TypeError, "");
	return nullptr;
}

Value* Operator::EvalBinary(const Value* pValueL, const Value* pValueR) const
{
	if (!pValueL || !pValueR) return nullptr;
	const OpEntry* pOpEntry = LookupEntry(pValueL->GetVType(), pValueR->GetVType());
	if (pOpEntry) pOpEntry->EvalBinary(pValueL, pValueR);
	Error::Issue(ErrorType::TypeError, "");
	return nullptr;
}

//------------------------------------------------------------------------------
// OpEntry
//------------------------------------------------------------------------------
Value* OpEntry::EvalUnary(const Value* pValue) const
{
	return Value::nil();
}

Value* OpEntry::EvalBinary(const Value* pValueL, const Value* pValueR) const
{
	return Value::nil();
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
