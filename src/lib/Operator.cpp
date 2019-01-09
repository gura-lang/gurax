//==============================================================================
// Operator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Operator
//------------------------------------------------------------------------------
// Unary operators
const Operator* Operator::Inv			= new Operator_Inv();
const Operator* Operator::Neg			= new Operator_Neg();
const Operator* Operator::Not			= new Operator_Not();
const Operator* Operator::Pos			= new Operator_Pos();
// Post-unary operators
const Operator* Operator::PostMod		= new Operator_PostMod();
const Operator* Operator::PostMul		= new Operator_PostMul();
const Operator* Operator::PostPos		= new Operator_PostPos();
const Operator* Operator::PostQuestion	= new Operator_PostQuestion();
const Operator* Operator::PostSeq		= new Operator_PostSeq();
// Binary operators
const Operator* Operator::Add			= new Operator_Add();
const Operator* Operator::And			= new Operator_And();
const Operator* Operator::AndAnd		= new Operator_AndAnd();
const Operator* Operator::Cmp			= new Operator_Cmp();
const Operator* Operator::Concat		= new Operator_Concat();
const Operator* Operator::Contains		= new Operator_Contains();
const Operator* Operator::Cross			= new Operator_Cross();
const Operator* Operator::Difference	= new Operator_Difference();
const Operator* Operator::Div			= new Operator_Div();
const Operator* Operator::Dot			= new Operator_Dot();
const Operator* Operator::Eq			= new Operator_Eq();
const Operator* Operator::Gear			= new Operator_Gear();
const Operator* Operator::Ge			= new Operator_Ge();
const Operator* Operator::Gt			= new Operator_Gt();
const Operator* Operator::Intersection	= new Operator_Intersection();
const Operator* Operator::Le			= new Operator_Le();
const Operator* Operator::Lt			= new Operator_Lt();
const Operator* Operator::Mod			= new Operator_Mod();
const Operator* Operator::ModMod		= new Operator_ModMod();
const Operator* Operator::Mul			= new Operator_Mul();
const Operator* Operator::Ne			= new Operator_Ne();
const Operator* Operator::Or			= new Operator_Or();
const Operator* Operator::OrOr			= new Operator_OrOr();
const Operator* Operator::Pair			= new Operator_Pair();
const Operator* Operator::Pow			= new Operator_Pow();
const Operator* Operator::Seq			= new Operator_Seq();
const Operator* Operator::Shl			= new Operator_Shl();
const Operator* Operator::Shr			= new Operator_Shr();
const Operator* Operator::Sub			= new Operator_Sub();
const Operator* Operator::Union			= new Operator_Union();
const Operator* Operator::Xor			= new Operator_Xor();
// Mathematical functions
const Operator* Operator::math_abs		= new Operator_math_abs();
const Operator* Operator::math_acos		= new Operator_math_acos();
const Operator* Operator::math_arg		= new Operator_math_arg();
const Operator* Operator::math_asin		= new Operator_math_asin();
const Operator* Operator::math_atan		= new Operator_math_atan();
const Operator* Operator::math_atan2	= new Operator_math_atan2();
const Operator* Operator::math_ceil		= new Operator_math_ceil();
const Operator* Operator::math_conj		= new Operator_math_conj();
const Operator* Operator::math_cos		= new Operator_math_cos();
const Operator* Operator::math_cosh		= new Operator_math_cosh();
const Operator* Operator::math_covariance = new Operator_math_covariance();
const Operator* Operator::math_cross	= new Operator_math_cross();
const Operator* Operator::math_delta	= new Operator_math_delta();
const Operator* Operator::math_dot		= new Operator_math_dot();
const Operator* Operator::math_exp		= new Operator_math_exp();
const Operator* Operator::math_floor	= new Operator_math_floor();
const Operator* Operator::math_hypot	= new Operator_math_hypot();
const Operator* Operator::math_imag		= new Operator_math_imag();
const Operator* Operator::math_log		= new Operator_math_log();
const Operator* Operator::math_log10	= new Operator_math_log10();
const Operator* Operator::math_norm		= new Operator_math_norm();
const Operator* Operator::math_real		= new Operator_math_real();
const Operator* Operator::math_relu		= new Operator_math_relu();
const Operator* Operator::math_sigmoid	= new Operator_math_sigmoid();
const Operator* Operator::math_sin		= new Operator_math_sin();
const Operator* Operator::math_sinh		= new Operator_math_sinh();
const Operator* Operator::math_sqrt		= new Operator_math_sqrt();
const Operator* Operator::math_tan		= new Operator_math_tan();
const Operator* Operator::math_tanh		= new Operator_math_tanh();
const Operator* Operator::math_unitstep	= new Operator_math_unitstep();

Object* Operator::EvalUnary(const Object* pObject)
{
	return Object::nil();
}

Object* Operator::EvalBinary(const Object* pObjectL, const Object* pObjectR)
{
	return Object::nil();
}

}
