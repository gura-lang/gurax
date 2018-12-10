//==============================================================================
// Operator.h
//==============================================================================
#ifndef GURAX_OPERATOR_H
#define GURAX_OPERATOR_H

namespace Gurax {

enum class OpType {
	None,
	// unary operators
	unary,
	Pos				= unary,
	Neg,
	Inv,
	Not,
	// suffixed unary operators
	suffixed_unary,
	SeqInf			= suffixed_unary,
	Question,
	Each,
	PostPos,
	PostMod,
	// binary operators
	binary,
	Add				= binary,
	Sub,
	Mul,
	Div,
	Mod,
	ModMod,
	Dot,
	Cross,
	Gear,
	Concat,
	Difference,
	Intersection,
	Union,
	Pow,
	Eq,
	Ne,
	Gt,
	Lt,
	Ge,
	Le,
	Cmp,
	Contains,
	And,
	Or,
	Xor,
	Shl,
	Shr,
	OrOr,
	AndAnd,
	Seq,
	Pair,
	// mathematical functions
	math,
	Math_abs 		= math,
	Math_acos,
	Math_arg,
	Math_asin,
	Math_atan,
	Math_atan2,
	Math_ceil,
	Math_conj,
	Math_cos,
	Math_cosh,
	Math_covariance,
	Math_cross,
	Math_delta,
	Math_dot,
	Math_exp,
	Math_floor,
	Math_hypot,
	Math_imag,
	Math_log,
	Math_log10,
	Math_norm,
	Math_real,
	Math_relu,
	Math_sigmoid,
	Math_sin,
	Math_sinh,
	Math_sqrt,
	Math_tan,
	Math_tanh,
	Math_unitstep,
	max,
};

};

#endif
