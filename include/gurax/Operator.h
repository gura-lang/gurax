//==============================================================================
// Operator.h
//==============================================================================
#ifndef GURAX_OPERATOR_H
#define GURAX_OPERATOR_H
#include "Value.h"

#define Gurax_ImplementOpPreUnary(opType, typeName) \
class OpEntry_##opType##_##typeName : public OpEntry { \
public: \
	virtual Value* EvalUnary(const Value& value) const; \
}; \
Value* OpEntry_##opType##_##typeName::EvalUnary(const Value& value) const

#define Gurax_AssignOpPreUnary(opType, typeName) \
Operator::opType->AssignEntry(VTYPE_##typeName, new OpEntry_##opType##_##typeName())

#define Gurax_ImplementOpBinary(opType, typeNameL, typeNameR) \
class OpEntry_##opType##_##typeNameL##_##typeNameR : public OpEntry { \
public: \
	virtual Value* EvalBinary(const Value& valueL, const Value& valueR) const; \
}; \
Value* OpEntry_##opType##_##typeNameL##_##typeNameR::EvalBinary(const Value& valueL, const Value& valueR) const

#define Gurax_AssignOpBinary(opType, typeNameL, typeNameR) \
Operator::opType->AssignEntry(VTYPE_##typeNameL, VTYPE_##typeNameR, new OpEntry_##opType##_##typeNameL##_##typeNameR())

namespace Gurax {

struct TokenType;

//------------------------------------------------------------------------------
// OpStyle
//------------------------------------------------------------------------------
enum class OpStyle {
	OpPreUnary,
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
	// Pre-unary operators
	Inv,
	Neg,
	Not,
	Pos,
	Quote,
	// Post-unary operators
	PostMod,
	PostModMod,
	PostMul,
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
	virtual Value* EvalUnary(const Value& value) const ;
	virtual Value* EvalBinary(const Value& valueL, const Value& valueR) const;
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
	void Assign(const VType& vtype, OpEntry* pOpEntry) {
		Assign(GenKey(vtype), pOpEntry);
	}
	void Assign(const VType& vtypeL, const VType& vtypeR, OpEntry* pOpEntry) {
		Assign(GenKey(vtypeL, vtypeR), pOpEntry);
	}
	OpEntry* Lookup(UInt64 key) const {
		auto pPair = find(key);
		return (pPair == end())? nullptr : pPair->second;
	}
	OpEntry* Lookup(const VType& vtype) const {
		return Lookup(GenKey(vtype));
	}
	OpEntry* Lookup(const VType& vtypeL, const VType& vtypeR) const { 
		return Lookup(GenKey(vtypeL, vtypeR));
	}
public:
	static UInt64 GenKey(const VType& vtype) { return vtype.GetSeqId(); }
	static UInt64 GenKey(const VType& vtypeL, const VType& vtypeR) {
		return (static_cast<UInt64>(vtypeL.GetSeqId()) << 32) + vtypeR.GetSeqId();
	}
};

//------------------------------------------------------------------------------
// Operator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Operator {
private:
	OpStyle _opStyle;
	const char* _symbol;
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
	static Operator* Quote;
	// Post-unary operators
	static Operator* PostMod;
	static Operator* PostModMod;
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
	Operator(OpStyle opStyle, const char* symbol, OpType opType);
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
	const char* GetSymbol() const		{ return _symbol; }
	OpType GetType() const				{ return _opType; }
	bool IsType(OpType opType) const	{ return _opType == opType; }
	bool IsUnary() const				{ return !_binaryFlag; }
	bool IsBinary() const				{ return _binaryFlag; }
	bool IsOpPreUnary() const			{ return _opStyle == OpStyle::OpPreUnary; }
	bool IsOpPostUnary() const			{ return _opStyle == OpStyle::OpPostUnary; }
	bool IsOpBinary() const				{ return _opStyle == OpStyle::OpBinary; }
	bool IsMathUnary() const			{ return _opStyle == OpStyle::MathUnary; }
	bool IsMathBinary() const			{ return _opStyle == OpStyle::MathBinary; }
	const TokenType& GetTokenType() const;
public:
	void AssignEntry(const VType& vtype, OpEntry* pOpEntry) {
		_opEntryMap.Assign(vtype, pOpEntry);
	}
	void AssignEntry(const VType& vtypeL, const VType& vtypeR, OpEntry* pOpEntry) {
		_opEntryMap.Assign(vtypeL, vtypeR, pOpEntry);
	}
	OpEntry* LookupEntry(const VType& vtype) const {
		return _opEntryMap.Lookup(vtype);
	}
	OpEntry* LookupEntry(const VType& vtypeL, const VType& vtypeR) const {
		return _opEntryMap.Lookup(vtypeL, vtypeR);
	}
public:
	Value* EvalUnary(const Value& value) const;
	Value* EvalBinary(const Value& valueL, const Value& valueR) const;
public:
	static Operator* Lookup(OpType opType) { return _operatorTbl[static_cast<size_t>(opType)]; }
};

};

#endif
