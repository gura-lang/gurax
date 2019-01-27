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
Operator* Operator::Inv				= new Operator(OpStyle::OpUnary,		"~",			OpType::Inv);
Operator* Operator::Neg				= new Operator(OpStyle::OpUnary,		"-",			OpType::Neg);
Operator* Operator::Not				= new Operator(OpStyle::OpUnary,		"!",			OpType::Not);
Operator* Operator::Pos				= new Operator(OpStyle::OpUnary,		"+",			OpType::Pos);
Operator* Operator::Quote			= new Operator(OpStyle::OpUnary,		"`",			OpType::Quote);
// Post-unary operators
Operator* Operator::PostMod			= new Operator(OpStyle::OpPostUnary,	"%",			OpType::PostMod);
Operator* Operator::PostMul			= new Operator(OpStyle::OpPostUnary,	"*",			OpType::PostMul);
Operator* Operator::PostPos			= new Operator(OpStyle::OpPostUnary,	"+",			OpType::PostPos);
Operator* Operator::PostQuestion	= new Operator(OpStyle::OpPostUnary,	"?",			OpType::PostQuestion);
Operator* Operator::PostSeq			= new Operator(OpStyle::OpPostUnary,	"..",			OpType::PostSeq);
// Binary operators
Operator* Operator::Add				= new Operator(OpStyle::OpUnary,		"+",			OpType::Add);
Operator* Operator::And				= new Operator(OpStyle::OpUnary,		"&",			OpType::And);
Operator* Operator::AndAnd			= new Operator(OpStyle::OpUnary,		"&&",			OpType::AndAnd);
Operator* Operator::Cmp				= new Operator(OpStyle::OpUnary,		"<=>",			OpType::Cmp);
Operator* Operator::Concat			= new Operator(OpStyle::OpUnary,		"|+|",			OpType::Concat);
Operator* Operator::Contains		= new Operator(OpStyle::OpUnary,		"in",			OpType::Contains);
Operator* Operator::Cross			= new Operator(OpStyle::OpUnary,		"|^|",			OpType::Cross);
Operator* Operator::Difference		= new Operator(OpStyle::OpUnary,		"|-|",			OpType::Difference);
Operator* Operator::Div				= new Operator(OpStyle::OpUnary,		"/",			OpType::Div);
Operator* Operator::Dot				= new Operator(OpStyle::OpUnary,		"|.|",			OpType::Dot);
Operator* Operator::Eq				= new Operator(OpStyle::OpUnary,		"==",			OpType::Eq);
Operator* Operator::Gear			= new Operator(OpStyle::OpUnary,		"|*|",			OpType::Gear);
Operator* Operator::Ge				= new Operator(OpStyle::OpUnary,		">=",			OpType::Ge);
Operator* Operator::Gt				= new Operator(OpStyle::OpUnary,		">",			OpType::Gt);
Operator* Operator::Intersection	= new Operator(OpStyle::OpUnary,		"|&|",			OpType::Intersection);
Operator* Operator::Le				= new Operator(OpStyle::OpUnary,		"<=",			OpType::Le);
Operator* Operator::Lt				= new Operator(OpStyle::OpUnary,		"<",			OpType::Lt);
Operator* Operator::Mod				= new Operator(OpStyle::OpUnary,		"%",			OpType::Mod);
Operator* Operator::ModMod			= new Operator(OpStyle::OpUnary,		"%%",			OpType::ModMod);
Operator* Operator::Mul				= new Operator(OpStyle::OpUnary,		"*",			OpType::Mul);
Operator* Operator::Ne				= new Operator(OpStyle::OpUnary,		"!=",			OpType::Ne);
Operator* Operator::Or				= new Operator(OpStyle::OpUnary,		"|",			OpType::Or);
Operator* Operator::OrOr			= new Operator(OpStyle::OpUnary,		"||",			OpType::OrOr);
Operator* Operator::Pair			= new Operator(OpStyle::OpUnary,		"=>",			OpType::Pair);
Operator* Operator::Pow				= new Operator(OpStyle::OpUnary,		"**",			OpType::Pow);
Operator* Operator::Seq				= new Operator(OpStyle::OpUnary,		"..",			OpType::Seq);
Operator* Operator::Shl				= new Operator(OpStyle::OpUnary,		"<<",			OpType::Shl);
Operator* Operator::Shr				= new Operator(OpStyle::OpUnary,		">>",			OpType::Shr);
Operator* Operator::Sub				= new Operator(OpStyle::OpUnary,		"-",			OpType::Sub);
Operator* Operator::Union			= new Operator(OpStyle::OpUnary,		"|||",			OpType::Union);
Operator* Operator::Xor				= new Operator(OpStyle::OpUnary,		"^",			OpType::Xor);
// Mathematical functions
Operator* Operator::math_abs		= new Operator(OpStyle::OpUnary,		"abs",			OpType::math_abs);
Operator* Operator::math_acos		= new Operator(OpStyle::OpUnary,		"acos",			OpType::math_acos);
Operator* Operator::math_arg		= new Operator(OpStyle::OpUnary,		"arg",			OpType::math_arg);
Operator* Operator::math_asin		= new Operator(OpStyle::OpUnary,		"asin",			OpType::math_asin);
Operator* Operator::math_atan		= new Operator(OpStyle::OpUnary,		"atan",			OpType::math_atan);
Operator* Operator::math_atan2		= new Operator(OpStyle::OpBinary,		"atan2",		OpType::math_atan2);
Operator* Operator::math_ceil		= new Operator(OpStyle::OpUnary,		"ceil",			OpType::math_ceil);
Operator* Operator::math_conj		= new Operator(OpStyle::OpUnary,		"conj",			OpType::math_conj);
Operator* Operator::math_cos		= new Operator(OpStyle::OpUnary,		"cos",			OpType::math_cos);
Operator* Operator::math_cosh		= new Operator(OpStyle::OpUnary,		"cosh",			OpType::math_cosh);
Operator* Operator::math_covariance = new Operator(OpStyle::OpUnary,		"covariance",	OpType::math_covariance);
Operator* Operator::math_cross		= new Operator(OpStyle::OpUnary,		"cross",		OpType::math_cross);
Operator* Operator::math_delta		= new Operator(OpStyle::OpUnary,		"delta",		OpType::math_delta);
Operator* Operator::math_dot		= new Operator(OpStyle::OpUnary,		"dot",			OpType::math_dot);
Operator* Operator::math_exp		= new Operator(OpStyle::OpUnary,		"exp",			OpType::math_exp);
Operator* Operator::math_floor		= new Operator(OpStyle::OpUnary,		"floor",		OpType::math_floor);
Operator* Operator::math_hypot		= new Operator(OpStyle::OpBinary,		"hypot",		OpType::math_hypot);
Operator* Operator::math_imag		= new Operator(OpStyle::OpUnary,		"imag",			OpType::math_imag);
Operator* Operator::math_log		= new Operator(OpStyle::OpUnary,		"log",			OpType::math_log);
Operator* Operator::math_log10		= new Operator(OpStyle::OpUnary,		"log10",		OpType::math_log10);
Operator* Operator::math_norm		= new Operator(OpStyle::OpUnary,		"norm",			OpType::math_norm);
Operator* Operator::math_real		= new Operator(OpStyle::OpUnary,		"real",			OpType::math_real);
Operator* Operator::math_relu		= new Operator(OpStyle::OpUnary,		"relu",			OpType::math_relu);
Operator* Operator::math_sigmoid	= new Operator(OpStyle::OpUnary,		"sigmoid",		OpType::math_sigmoid);
Operator* Operator::math_sin		= new Operator(OpStyle::OpUnary,		"sin",			OpType::math_sin);
Operator* Operator::math_sinh		= new Operator(OpStyle::OpUnary,		"sinh",			OpType::math_sinh);
Operator* Operator::math_sqrt		= new Operator(OpStyle::OpUnary,		"sqrt",			OpType::math_sqrt);
Operator* Operator::math_tan		= new Operator(OpStyle::OpUnary,		"tan",			OpType::math_tan);
Operator* Operator::math_tanh		= new Operator(OpStyle::OpUnary,		"tanh",			OpType::math_tanh);
Operator* Operator::math_unitstep	= new Operator(OpStyle::OpUnary,		"unitstep",		OpType::math_unitstep);

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

//------------------------------------------------------------------------------
// OpEntry
//------------------------------------------------------------------------------
Object* OpEntry::EvalUnary(const Object* pObject) const
{
	return Object::nil();
}

Object* OpEntry::EvalBinary(const Object* pObjectL, const Object* pObjectR) const
{
	return Object::nil();
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
