//==============================================================================
// Operator.h
//==============================================================================
#ifndef GURAX_OPERATOR_H
#define GURAX_OPERATOR_H
#include "Common.h"

namespace Gurax {

class Object;
	
//------------------------------------------------------------------------------
// OpStyle
//------------------------------------------------------------------------------
enum class OpStyle {
	Unary,
	PostUnary,
	Binary,
	Math,
};

//------------------------------------------------------------------------------
// OpType
//------------------------------------------------------------------------------
enum class OpType {
	None,
	// Unary operators
	Inv,
	Neg,
	Not,
	Pos,
	// Post-unary operators
	PostMul,
	PostMod,
	PostPos,
	PostQuestion,
	PostSeq,
	// Binary operators
	Add,
	And,
	AndAnd,
	Cmp,
	Concat,
	Contains,
	Cross,
	Difference,
	Div,
	Dot,
	Eq,
	Gear,
	Ge,
	Gt,
	Intersection,
	Le,
	Lt,
	Mod,
	ModMod,
	Mul,
	Ne,
	Or,
	OrOr,
	Pair,
	Pow,
	Seq,
	Shl,
	Shr,
	Sub,
	Union,
	Xor,
	// Mathematical functions
	math_abs,
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
	OpStyle _opStyle;
	OpType _opType;
public:
	// Unary operators
	static const Operator* Inv;
	static const Operator* Neg;
	static const Operator* Not;
	static const Operator* Pos;
	// Post-unary operators
	static const Operator* PostMod;
	static const Operator* PostMul;
	static const Operator* PostPos;
	static const Operator* PostQuestion;
	static const Operator* PostSeq;
	// Binary operators
	static const Operator* Add;
	static const Operator* And;
	static const Operator* AndAnd;
	static const Operator* Cmp;
	static const Operator* Concat;
	static const Operator* Contains;
	static const Operator* Cross;
	static const Operator* Difference;
	static const Operator* Div;
	static const Operator* Dot;
	static const Operator* Eq;
	static const Operator* Gear;
	static const Operator* Ge;
	static const Operator* Gt;
	static const Operator* Intersection;
	static const Operator* Le;
	static const Operator* Lt;
	static const Operator* Mod;
	static const Operator* ModMod;
	static const Operator* Mul;
	static const Operator* Ne;
	static const Operator* Or;
	static const Operator* OrOr;
	static const Operator* Pair;
	static const Operator* Pow;
	static const Operator* Seq;
	static const Operator* Shl;
	static const Operator* Shr;
	static const Operator* Sub;
	static const Operator* Union;
	static const Operator* Xor;
	// Mathematical functions
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
	Operator(OpStyle opStyle, OpType opType) : _opStyle(opStyle), _opType(opType) {}
	// Copy constructor/operator
	Operator(const Operator& src) = delete;
	Operator& operator=(const Operator& src) = delete;
	// Move constructor/operator
	Operator(Operator&& src) = delete;
	Operator& operator=(Operator&& src) noexcept = delete;
	// Destructor
	virtual ~Operator() = default;
public:
	OpStyle GetStyle() const { return _opStyle; }
	OpType GetType() const { return _opType; }
	bool IsType(OpType opType) const { return _opType == opType; }
	bool IsUnary() const { return _opStyle == OpStyle::Unary; }
	bool IsPostUnary() const { return _opStyle == OpStyle::PostUnary; }
	bool IsBinary() const { return _opStyle == OpStyle::Binary; }
	bool IsMath() const { return _opStyle == OpStyle::Math; }
public:
	virtual Object* EvalUnary(const Object* pObject);
	virtual Object* EvalBinary(const Object* pObjectL, const Object* pObjectR);
};

#define Gurax_DeclareOperator(opStyle, opType) \
class GURAX_DLLDECLARE Operator_##opType : public Operator {	\
public: \
	Operator_##opType() : Operator(OpStyle::opStyle, OpType::opType) {}	\
};

//------------------------------------------------------------------------------
// Operator
//------------------------------------------------------------------------------
// Unary operators
Gurax_DeclareOperator(Unary, Pos);
Gurax_DeclareOperator(Unary, Neg);
Gurax_DeclareOperator(Unary, Inv);
Gurax_DeclareOperator(Unary, Not);
// Post-unary operators
Gurax_DeclareOperator(PostUnary, PostSeq);
Gurax_DeclareOperator(PostUnary, PostQuestion);
Gurax_DeclareOperator(PostUnary, PostMul);
Gurax_DeclareOperator(PostUnary, PostPos);
Gurax_DeclareOperator(PostUnary, PostMod);
// Binary operators
Gurax_DeclareOperator(Binary, Add);
Gurax_DeclareOperator(Binary, Sub);
Gurax_DeclareOperator(Binary, Mul);
Gurax_DeclareOperator(Binary, Div);
Gurax_DeclareOperator(Binary, Mod);
Gurax_DeclareOperator(Binary, ModMod);
Gurax_DeclareOperator(Binary, Dot);
Gurax_DeclareOperator(Binary, Cross);
Gurax_DeclareOperator(Binary, Gear);
Gurax_DeclareOperator(Binary, Concat);
Gurax_DeclareOperator(Binary, Difference);
Gurax_DeclareOperator(Binary, Intersection);
Gurax_DeclareOperator(Binary, Union);
Gurax_DeclareOperator(Binary, Pow);
Gurax_DeclareOperator(Binary, Eq);
Gurax_DeclareOperator(Binary, Ne);
Gurax_DeclareOperator(Binary, Gt);
Gurax_DeclareOperator(Binary, Lt);
Gurax_DeclareOperator(Binary, Ge);
Gurax_DeclareOperator(Binary, Le);
Gurax_DeclareOperator(Binary, Cmp);
Gurax_DeclareOperator(Binary, Contains);
Gurax_DeclareOperator(Binary, And);
Gurax_DeclareOperator(Binary, Or);
Gurax_DeclareOperator(Binary, Xor);
Gurax_DeclareOperator(Binary, Shl);
Gurax_DeclareOperator(Binary, Shr);
Gurax_DeclareOperator(Binary, OrOr);
Gurax_DeclareOperator(Binary, AndAnd);
Gurax_DeclareOperator(Binary, Seq);
Gurax_DeclareOperator(Binary, Pair);
// Mathematical functions
Gurax_DeclareOperator(Math, math_abs);
Gurax_DeclareOperator(Math, math_acos);
Gurax_DeclareOperator(Math, math_arg);
Gurax_DeclareOperator(Math, math_asin);
Gurax_DeclareOperator(Math, math_atan);
Gurax_DeclareOperator(Math, math_atan2);
Gurax_DeclareOperator(Math, math_ceil);
Gurax_DeclareOperator(Math, math_conj);
Gurax_DeclareOperator(Math, math_cos);
Gurax_DeclareOperator(Math, math_cosh);
Gurax_DeclareOperator(Math, math_covariance);
Gurax_DeclareOperator(Math, math_cross);
Gurax_DeclareOperator(Math, math_delta);
Gurax_DeclareOperator(Math, math_dot);
Gurax_DeclareOperator(Math, math_exp);
Gurax_DeclareOperator(Math, math_floor);
Gurax_DeclareOperator(Math, math_hypot);
Gurax_DeclareOperator(Math, math_imag);
Gurax_DeclareOperator(Math, math_log);
Gurax_DeclareOperator(Math, math_log10);
Gurax_DeclareOperator(Math, math_norm);
Gurax_DeclareOperator(Math, math_real);
Gurax_DeclareOperator(Math, math_relu);
Gurax_DeclareOperator(Math, math_sigmoid);
Gurax_DeclareOperator(Math, math_sin);
Gurax_DeclareOperator(Math, math_sinh);
Gurax_DeclareOperator(Math, math_sqrt);
Gurax_DeclareOperator(Math, math_tan);
Gurax_DeclareOperator(Math, math_tanh);
Gurax_DeclareOperator(Math, math_unitstep);

};

#endif
