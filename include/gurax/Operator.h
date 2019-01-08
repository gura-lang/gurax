//==============================================================================
// Operator.h
//==============================================================================
#ifndef GURAX_OPERATOR_H
#define GURAX_OPERATOR_H
#include "Common.h"

namespace Gurax {

class Object;
	
//------------------------------------------------------------------------------
// OpType
//------------------------------------------------------------------------------
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
	math_abs 		= math,
	math_acos,
	math_arg,
	math_asin,
	math_atan,
	math_atan2,
	math_ceil,
	math_conj,
	math_cos,
	math_cosh,
	math_covariance,
	math_cross,
	math_delta,
	math_dot,
	math_exp,
	math_floor,
	math_hypot,
	math_imag,
	math_log,
	math_log10,
	math_norm,
	math_real,
	math_relu,
	math_sigmoid,
	math_sin,
	math_sinh,
	math_sqrt,
	math_tan,
	math_tanh,
	math_unitstep,
	max,
};

//------------------------------------------------------------------------------
// Operator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Operator {
private:
	OpType _opType;
public:
	// unary operators
	static const Operator* Pos;
	static const Operator* Neg;
	static const Operator* Inv;
	static const Operator* Not;
	// suffixed unary operators
	static const Operator* SeqInf;
	static const Operator* Question;
	static const Operator* Each;
	static const Operator* PostPos;
	static const Operator* PostMod;
	// binary operators
	static const Operator* Add;
	static const Operator* Sub;
	static const Operator* Mul;
	static const Operator* Div;
	static const Operator* Mod;
	static const Operator* ModMod;
	static const Operator* Dot;
	static const Operator* Cross;
	static const Operator* Gear;
	static const Operator* Concat;
	static const Operator* Difference;
	static const Operator* Intersection;
	static const Operator* Union;
	static const Operator* Pow;
	static const Operator* Eq;
	static const Operator* Ne;
	static const Operator* Gt;
	static const Operator* Lt;
	static const Operator* Ge;
	static const Operator* Le;
	static const Operator* Cmp;
	static const Operator* Contains;
	static const Operator* And;
	static const Operator* Or;
	static const Operator* Xor;
	static const Operator* Shl;
	static const Operator* Shr;
	static const Operator* OrOr;
	static const Operator* AndAnd;
	static const Operator* Seq;
	static const Operator* Pair;
	// mathematical functions
	static const Operator* math_abs;
	static const Operator* math_acos;
	static const Operator* math_arg;
	static const Operator* math_asin;
	static const Operator* math_atan;
	static const Operator* math_atan2;
	static const Operator* math_ceil;
	static const Operator* math_conj;
	static const Operator* math_cos;
	static const Operator* math_cosh;
	static const Operator* math_covariance;
	static const Operator* math_cross;
	static const Operator* math_delta;
	static const Operator* math_dot;
	static const Operator* math_exp;
	static const Operator* math_floor;
	static const Operator* math_hypot;
	static const Operator* math_imag;
	static const Operator* math_log;
	static const Operator* math_log10;
	static const Operator* math_norm;
	static const Operator* math_real;
	static const Operator* math_relu;
	static const Operator* math_sigmoid;
	static const Operator* math_sin;
	static const Operator* math_sinh;
	static const Operator* math_sqrt;
	static const Operator* math_tan;
	static const Operator* math_tanh;
	static const Operator* math_unitstep;
public:
	// Constructor
	Operator(OpType opType) : _opType(opType) {}
	// Copy constructor/operator
	Operator(const Operator& src) = delete;
	Operator& operator=(const Operator& src) = delete;
	// Move constructor/operator
	Operator(Operator&& src) = delete;
	Operator& operator=(Operator&& src) noexcept = delete;
	// Destructor
	virtual ~Operator() = default;
public:
	OpType GetOpType() const { return _opType; }
public:
	virtual Object* EvalUnary(const Object* pObject);
	virtual Object* EvalBinary(const Object* pObjectL, const Object* pObjectR);
};

#define Gurax_DeclareOperator(name) \
class GURAX_DLLDECLARE Operator_##name : public Operator {	\
public: \
	Operator_##name() : Operator(OpType::name) {} \
};

//------------------------------------------------------------------------------
// Operator
//------------------------------------------------------------------------------
// unary operators
Gurax_DeclareOperator(Pos);
Gurax_DeclareOperator(Neg);
Gurax_DeclareOperator(Inv);
Gurax_DeclareOperator(Not);
// suffixed unary operators
Gurax_DeclareOperator(SeqInf);
Gurax_DeclareOperator(Question);
Gurax_DeclareOperator(Each);
Gurax_DeclareOperator(PostPos);
Gurax_DeclareOperator(PostMod);
// binary operators
Gurax_DeclareOperator(Add);
Gurax_DeclareOperator(Sub);
Gurax_DeclareOperator(Mul);
Gurax_DeclareOperator(Div);
Gurax_DeclareOperator(Mod);
Gurax_DeclareOperator(ModMod);
Gurax_DeclareOperator(Dot);
Gurax_DeclareOperator(Cross);
Gurax_DeclareOperator(Gear);
Gurax_DeclareOperator(Concat);
Gurax_DeclareOperator(Difference);
Gurax_DeclareOperator(Intersection);
Gurax_DeclareOperator(Union);
Gurax_DeclareOperator(Pow);
Gurax_DeclareOperator(Eq);
Gurax_DeclareOperator(Ne);
Gurax_DeclareOperator(Gt);
Gurax_DeclareOperator(Lt);
Gurax_DeclareOperator(Ge);
Gurax_DeclareOperator(Le);
Gurax_DeclareOperator(Cmp);
Gurax_DeclareOperator(Contains);
Gurax_DeclareOperator(And);
Gurax_DeclareOperator(Or);
Gurax_DeclareOperator(Xor);
Gurax_DeclareOperator(Shl);
Gurax_DeclareOperator(Shr);
Gurax_DeclareOperator(OrOr);
Gurax_DeclareOperator(AndAnd);
Gurax_DeclareOperator(Seq);
Gurax_DeclareOperator(Pair);
// mathematical functions
Gurax_DeclareOperator(math_abs);
Gurax_DeclareOperator(math_acos);
Gurax_DeclareOperator(math_arg);
Gurax_DeclareOperator(math_asin);
Gurax_DeclareOperator(math_atan);
Gurax_DeclareOperator(math_atan2);
Gurax_DeclareOperator(math_ceil);
Gurax_DeclareOperator(math_conj);
Gurax_DeclareOperator(math_cos);
Gurax_DeclareOperator(math_cosh);
Gurax_DeclareOperator(math_covariance);
Gurax_DeclareOperator(math_cross);
Gurax_DeclareOperator(math_delta);
Gurax_DeclareOperator(math_dot);
Gurax_DeclareOperator(math_exp);
Gurax_DeclareOperator(math_floor);
Gurax_DeclareOperator(math_hypot);
Gurax_DeclareOperator(math_imag);
Gurax_DeclareOperator(math_log);
Gurax_DeclareOperator(math_log10);
Gurax_DeclareOperator(math_norm);
Gurax_DeclareOperator(math_real);
Gurax_DeclareOperator(math_relu);
Gurax_DeclareOperator(math_sigmoid);
Gurax_DeclareOperator(math_sin);
Gurax_DeclareOperator(math_sinh);
Gurax_DeclareOperator(math_sqrt);
Gurax_DeclareOperator(math_tan);
Gurax_DeclareOperator(math_tanh);
Gurax_DeclareOperator(math_unitstep);

};

#endif
