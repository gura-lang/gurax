//==============================================================================
// VType_Quote.h
//==============================================================================
#ifndef GURAX_VTYPE_QUOTE_H
#define GURAX_VTYPE_QUOTE_H
#include "Value.h"
#include "Expr.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Quote
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Quote : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_Quote VTYPE_Quote;

//------------------------------------------------------------------------------
// Value_Quote
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Quote : public Value {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Quote);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Quote");
protected:
	RefPtr<Expr> _pExpr;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Quote() = delete;
	explicit Value_Quote(Expr* pExpr) : Value(VTYPE_Quote), _pExpr(pExpr) {}
	// Copy constructor/operator
	Value_Quote(const Value_Quote& src) : Value(src), _pExpr(src._pExpr->Reference()) {}
	Value_Quote& operator=(const Value_Quote& src) = delete;
	// Move constructor/operator
	Value_Quote(Value_Quote&& src) = delete;
	Value_Quote& operator=(Value_Quote&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Quote() = default;
public:
	Expr& GetExpr() { return *_pExpr; }
	const Expr& GetExpr() const { return *_pExpr; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetExpr().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetExpr().IsEqualTo(dynamic_cast<const Value_Quote&>(value).GetExpr());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetExpr().IsLessThan(dynamic_cast<const Value_Quote&>(value).GetExpr()) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
