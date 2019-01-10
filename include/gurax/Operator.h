//==============================================================================
// Operator.h
//==============================================================================
#ifndef GURAX_OPERATOR_H
#define GURAX_OPERATOR_H
#include "Object.h"

#define Gurax_ImplementOpUnary(opType, typeName) \
class OpEntry_##opType##_##typeName : public OpEntry { \
public: \
	virtual Object* EvalUnary(const Object* pObject) const; \
}; \
Object* OpEntry_##opType##_##typeName::EvalUnary(const Object* pObject) const

#define Gurax_AssignOpUnary(opType, typeName) \
Operator::opType->AssignEntry(Object_##typeName::klass, new OpEntry_##opType##_##typeName())

#define Gurax_ImplementOpBinary(opType, typeNameL, typeNameR) \
class OpEntry_##opType##_##typeNameL##_##typeNameR : public OpEntry { \
public: \
	virtual Object* EvalBinary(const Object* pObjectL, const Object* pObjectR) const; \
}; \
Object* OpEntry_##opType##_##typeNameL##_##typeNameR::EvalBinary(const Object* pObjectL, const Object* pObjectR) const

#define Gurax_AssignOpBinary(opType, typeNameL, typeNameR) \
Operator::opType->AssignEntry(Object_##typeNameL::klass, Object_##typeNameR::klass, new OpEntry_##opType##_##typeNameL##_##typeNameR())

namespace Gurax {

//------------------------------------------------------------------------------
// OpStyle
//------------------------------------------------------------------------------
enum class OpStyle {
	OpUnary,
	OpPostUnary,
	OpBinary,
	MathUnary,
	MathBinary,
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
// OpEntry
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE OpEntry {
public:
	// Constructor
	OpEntry() = default;
	// Copy constructor/operator
	OpEntry(const OpEntry& src) = delete;
	OpEntry& operator=(const OpEntry& src) = delete;
	// Move constructor/operator
	OpEntry(OpEntry&& src) = delete;
	OpEntry& operator=(OpEntry&& src) noexcept = delete;
	// Destructor
	virtual ~OpEntry() = default;
public:
	virtual Object* EvalUnary(const Object* pObject) const ;
	virtual Object* EvalBinary(const Object* pObjectL, const Object* pObjectR) const;
};

//------------------------------------------------------------------------------
// OpEntryMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE OpEntryMap : public std::unordered_map<UInt64, OpEntry*> {
public:
	~OpEntryMap() {
		for (auto pair : *this) delete pair.second;
	}
public:
	void Assign(UInt64 key, OpEntry *pOpEntry);
	void Assign(const Klass& klass, OpEntry* pOpEntry) {
		Assign(GenKey(klass), pOpEntry);
	}
	void Assign(const Klass& klassL, const Klass& klassR, OpEntry* pOpEntry) {
		Assign(GenKey(klassL, klassR), pOpEntry);
	}
	OpEntry* Lookup(UInt64 key) const {
		auto pPair = find(key);
		return (pPair == end())? nullptr : pPair->second;
	}
	OpEntry* Lookup(const Klass& klass) const {
		return Lookup(GenKey(klass));
	}
	OpEntry* Lookup(const Klass& klassL, const Klass& klassR) const { 
		return Lookup(GenKey(klassL, klassR));
	}
public:
	static UInt64 GenKey(const Klass& klass) { return klass.GetSeqId(); }
	static UInt64 GenKey(const Klass& klassL, const Klass& klassR) {
		return (static_cast<UInt64>(klassL.GetSeqId()) << 32) + klassR.GetSeqId();
	}
};

//------------------------------------------------------------------------------
// Operator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Operator {
private:
	OpStyle _opStyle;
	OpType _opType;
	bool _binaryFlag;
	OpEntryMap _opEntryMap;
private:
	static Operator* _operatorTbl[static_cast<size_t>(OpType::max)];
public:
	// Unary operators
	static Operator* Inv;
	static Operator* Neg;
	static Operator* Not;
	static Operator* Pos;
	// Post-unary operators
	static Operator* PostMod;
	static Operator* PostMul;
	static Operator* PostPos;
	static Operator* PostQuestion;
	static Operator* PostSeq;
	// Binary operators
	static Operator* Add;
	static Operator* And;
	static Operator* AndAnd;
	static Operator* Cmp;
	static Operator* Concat;
	static Operator* Contains;
	static Operator* Cross;
	static Operator* Difference;
	static Operator* Div;
	static Operator* Dot;
	static Operator* Eq;
	static Operator* Gear;
	static Operator* Ge;
	static Operator* Gt;
	static Operator* Intersection;
	static Operator* Le;
	static Operator* Lt;
	static Operator* Mod;
	static Operator* ModMod;
	static Operator* Mul;
	static Operator* Ne;
	static Operator* Or;
	static Operator* OrOr;
	static Operator* Pair;
	static Operator* Pow;
	static Operator* Seq;
	static Operator* Shl;
	static Operator* Shr;
	static Operator* Sub;
	static Operator* Union;
	static Operator* Xor;
	// Mathematical functions
	static Operator* math_abs;
	static Operator* math_acos;
	static Operator* math_arg;
	static Operator* math_asin;
	static Operator* math_atan;
	static Operator* math_atan2;
	static Operator* math_ceil;
	static Operator* math_conj;
	static Operator* math_cos;
	static Operator* math_cosh;
	static Operator* math_covariance;
	static Operator* math_cross;
	static Operator* math_delta;
	static Operator* math_dot;
	static Operator* math_exp;
	static Operator* math_floor;
	static Operator* math_hypot;
	static Operator* math_imag;
	static Operator* math_log;
	static Operator* math_log10;
	static Operator* math_norm;
	static Operator* math_real;
	static Operator* math_relu;
	static Operator* math_sigmoid;
	static Operator* math_sin;
	static Operator* math_sinh;
	static Operator* math_sqrt;
	static Operator* math_tan;
	static Operator* math_tanh;
	static Operator* math_unitstep;
public:
	// Constructor
	Operator(OpStyle opStyle, OpType opType);
	// Copy constructor/operator
	Operator(const Operator& src) = delete;
	Operator& operator=(const Operator& src) = delete;
	// Move constructor/operator
	Operator(Operator&& src) = delete;
	Operator& operator=(Operator&& src) noexcept = delete;
	// Destructor
	virtual ~Operator() = default;
public:
	OpStyle GetStyle() const			{ return _opStyle; }
	OpType GetType() const				{ return _opType; }
	bool IsType(OpType opType) const	{ return _opType == opType; }
	bool IsUnary() const				{ return !_binaryFlag; }
	bool IsBinary() const				{ return _binaryFlag; }
	bool IsOpUnary() const				{ return _opStyle == OpStyle::OpUnary; }
	bool IsOpPostUnary() const			{ return _opStyle == OpStyle::OpPostUnary; }
	bool IsOpBinary() const				{ return _opStyle == OpStyle::OpBinary; }
	bool IsMathUnary() const			{ return _opStyle == OpStyle::MathUnary; }
	bool IsMathBinary() const			{ return _opStyle == OpStyle::MathBinary; }
public:
	void AssignEntry(const Klass& klass, OpEntry* pOpEntry) {
		_opEntryMap.Assign(klass, pOpEntry);
	}
	void AssignEntry(const Klass& klassL, const Klass& klassR, OpEntry* pOpEntry) {
		_opEntryMap.Assign(klassL, klassR, pOpEntry);
	}
	OpEntry* LookupEntry(const Klass& klass) {
		return _opEntryMap.Lookup(klass);
	}
	OpEntry* LookupEntry(const Klass& klassL, const Klass& klassR) {
		return _opEntryMap.Lookup(klassL, klassR);
	}
public:
	Object* EvalUnary(const Object* pObject) {
		if (!pObject) return nullptr;
		const OpEntry* pOpEntry = LookupEntry(pObject->GetKlass());
		return pOpEntry? pOpEntry->EvalUnary(pObject) : nullptr;
	}
	Object* EvalBinary(const Object* pObjectL, const Object* pObjectR) {
		if (!pObjectL || !pObjectR) return nullptr;
		const OpEntry* pOpEntry = LookupEntry(pObjectL->GetKlass(), pObjectR->GetKlass());
		return pOpEntry? pOpEntry->EvalBinary(pObjectL, pObjectR) : nullptr;
	}
public:
	static Operator* Lookup(OpType opType) { return _operatorTbl[static_cast<size_t>(opType)]; }
};

};

#endif
