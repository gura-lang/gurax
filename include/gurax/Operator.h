//==============================================================================
// Operator.h
//==============================================================================
#ifndef GURAX_OPERATOR_H
#define GURAX_OPERATOR_H
#include "Value.h"

//------------------------------------------------------------------------------
// Macros to implement unary operators
//------------------------------------------------------------------------------
#define Gurax_ImplementOpUnary(opType, typeName) \
class OpEntry_##opType##_##typeName : public OpEntry { \
public: \
	virtual Value* EvalUnary(Processor& processor, Value& value) const; \
}; \
Value* OpEntry_##opType##_##typeName::EvalUnary(Processor& processor, Value& value) const

#define Gurax_AssignOpUnary(opType, typeName) \
Operator::opType->AssignEntry(VTYPE_##typeName, new OpEntry_##opType##_##typeName())

//------------------------------------------------------------------------------
// Macros to implement binary operators
//------------------------------------------------------------------------------
#define Gurax_ImplementBinary(opType, typeNameL, typeNameR) \
class OpEntry_##opType##_##typeNameL##_##typeNameR : public OpEntry { \
public: \
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const; \
}; \
Value* OpEntry_##opType##_##typeNameL##_##typeNameR::EvalBinary(Processor& processor, Value& valueL, Value& valueR) const

#define Gurax_AssignBinary(opType, typeNameL, typeNameR) \
Operator::opType->AssignEntry(VTYPE_##typeNameL, VTYPE_##typeNameR, new OpEntry_##opType##_##typeNameL##_##typeNameR())

namespace Gurax {

class Expr;
class Expr_Unary;
class Expr_Binary;
class Composer;
class Operator;
struct TokenType;

//------------------------------------------------------------------------------
// OpStyle
//------------------------------------------------------------------------------
enum class OpStyle {
	Unary,
	UnaryPost,
	Binary,
	MathUnary,
	MathBinary,
};

//------------------------------------------------------------------------------
// OpType
//------------------------------------------------------------------------------
enum class OpType {
	None = -1,
	// Pre-unary operators
	Inv = 0,
	Neg,
	Not,
	Pos,
	Question,
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
	math_Abs,
	math_Acos,
	math_Arg,
	math_Asin,
	math_Atan,
	math_Atan2,
	math_Ceil,
	math_Conj,
	math_Cos,
	math_Cosh,
	math_Covariance,
	math_Cross,
	math_Delta,
	math_Dot,
	math_Exp,
	math_Floor,
	math_Hypot,
	math_Imag,
	math_Log,
	math_Log10,
	math_Norm,
	math_Real,
	math_Relu,
	math_Sigmoid,
	math_Sin,
	math_Sinh,
	math_Sqrt,
	math_Tan,
	math_Tanh,
	math_Unitstep,
	max,
};

//------------------------------------------------------------------------------
// OpEntry
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE OpEntry {
public:
	static const OpEntry Empty;
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
	virtual Value* EvalUnary(Processor& processor, Value& value) const;
	virtual Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR) const;
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
	static UInt64 GenKey(const VType& vtype) { return vtype.GetUniqId(); }
	static UInt64 GenKey(const VType& vtypeL, const VType& vtypeR) {
		return (static_cast<UInt64>(vtypeL.GetUniqId()) << 32) + vtypeR.GetUniqId();
	}
};

//------------------------------------------------------------------------------
// OperatorMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE OperatorMap :
		public std::unordered_map<const Symbol*, Operator*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId> {
public:
	Operator* Lookup(const Symbol* pSymbol) const;
};

//------------------------------------------------------------------------------
// Operator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Operator {
public:
	using Flags = UInt32;
	struct GURAX_DLLDECLARE Flag {
		static const Flags None		= 0;
		static const Flags Raw		= 1 << 0;
		static const Flags Map		= 1 << 1;
		static const Flags NoMap	= 0 << 1;
	};
private:
	OpStyle _opStyle;
	const char* _name;
	const Symbol* _pSymbol;
	OpType _opType;
	Flags _flags;
	OpEntryMap _opEntryMap;
private:
	static Operator* _operatorTbl[static_cast<size_t>(OpType::max)];
	static OperatorMap _operatorMap_Unary;
	static OperatorMap _operatorMap_UnaryPost;
	static OperatorMap _operatorMap_Binary;
	static OperatorMap _operatorMap_Math;
public:
	// Unary operators
	static Operator* Inv;
	static Operator* Neg;
	static Operator* Not;
	static Operator* Pos;
	static Operator* Question;
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
	static Operator* math_Abs;
	static Operator* math_Acos;
	static Operator* math_Arg;
	static Operator* math_Asin;
	static Operator* math_Atan;
	static Operator* math_Atan2;
	static Operator* math_Ceil;
	static Operator* math_Conj;
	static Operator* math_Cos;
	static Operator* math_Cosh;
	static Operator* math_Covariance;
	static Operator* math_Cross;
	static Operator* math_Delta;
	static Operator* math_Dot;
	static Operator* math_Exp;
	static Operator* math_Floor;
	static Operator* math_Hypot;
	static Operator* math_Imag;
	static Operator* math_Log;
	static Operator* math_Log10;
	static Operator* math_Norm;
	static Operator* math_Real;
	static Operator* math_Relu;
	static Operator* math_Sigmoid;
	static Operator* math_Sin;
	static Operator* math_Sinh;
	static Operator* math_Sqrt;
	static Operator* math_Tan;
	static Operator* math_Tanh;
	static Operator* math_Unitstep;
public:
	// Constructor
	Operator(OpStyle opStyle, const char* name, const char* symbol, OpType opType, Flags flags = Flag::Map);
	// Copy constructor/operator
	Operator(Operator& src) = delete;
	Operator& operator=(Operator& src) = delete;
	// Move constructor/operator
	Operator(Operator&& src) = delete;
	Operator& operator=(Operator&& src) noexcept = delete;
	// Destructor
	virtual ~Operator() = default;
public:
	static void Bootup();
public:
	OpStyle GetStyle() const			{ return _opStyle; }
	const char* GetName() const			{ return _name; }
	const Symbol* GetSymbol() const		{ return _pSymbol; }
	OpType GetType() const				{ return _opType; }
	bool GetRawFlag() const				{ return (_flags & Flag::Raw) != 0; }
	bool GetMapFlag() const				{ return (_flags & Flag::Map) != 0; }
	bool IsType(OpType opType) const	{ return _opType == opType; }
	bool IsUnary() const				{ return _opStyle == OpStyle::Unary; }
	bool IsUnaryPost() const			{ return _opStyle == OpStyle::UnaryPost; }
	bool IsBinary() const				{ return _opStyle == OpStyle::Binary; }
	bool IsMath() const					{ return IsMathUnary() || IsMathBinary(); }
	bool IsMathUnary() const			{ return _opStyle == OpStyle::MathUnary; }
	bool IsMathBinary() const			{ return _opStyle == OpStyle::MathBinary; }
	const Symbol* GetStyleAsSymbol() const;
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
	const OpEntry* FindMatchedEntry(const VType& vtype) const;
	const OpEntry* FindMatchedEntry(const VType& vtypeL, const VType& vtypeR) const;
public:
	const DeclCallable& GetDeclCallable() const;
	Value* EvalUnary(Processor& processor, Value& value);
	Value* EvalBinary(Processor& processor, Value& valueL, Value& valueR);
	String ToString(const StringStyle& ss) const;
	String ToString(const StringStyle& ss, const VType& vtype) const;
	String ToString(const StringStyle& ss, const VType& vtypeL, const VType& vtypeR) const;
	virtual void ComposeUnary(Composer& composer, Expr_Unary& expr) const {}
	virtual void ComposeBinary(Composer& composer, Expr_Binary& expr) const {}
public:
	static Operator* Lookup(OpType opType) { return _operatorTbl[static_cast<size_t>(opType)]; }
	static Operator* LookupUnary(const Symbol* pSymbol);
	static Operator* LookupUnaryPost(const Symbol* pSymbol);
	static Operator* LookupBinary(const Symbol* pSymbol);
	static Operator* LookupMath(const Symbol* pSymbol);
};

//------------------------------------------------------------------------------
// Operator_Quote
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Operator_Quote : public Operator {
public:
	Operator_Quote() : Operator(OpStyle::Unary, "Quote", "`", OpType::Quote, Flag::Raw) {}
public:
	virtual void ComposeUnary(Composer& composer, Expr_Unary& expr) const override;
};

//------------------------------------------------------------------------------
// Operator_AndAnd
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Operator_AndAnd : public Operator {
public:
	Operator_AndAnd() : Operator(OpStyle::Binary, "AndAnd", "&&", OpType::AndAnd, Flag::Raw) {}
public:
	virtual void ComposeBinary(Composer& composer, Expr_Binary& expr) const override;
};

//------------------------------------------------------------------------------
// Operator_OrOr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Operator_OrOr : public Operator {
public:
	Operator_OrOr() : Operator(OpStyle::Binary, "OrOr", "||", OpType::OrOr, Flag::Raw) {}
public:
	virtual void ComposeBinary(Composer& composer, Expr_Binary& expr) const override;
};

};

#endif
