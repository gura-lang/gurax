//==============================================================================
// VType_Expr.h
//==============================================================================
#ifndef GURAX_VTYPE_EXPR_H
#define GURAX_VTYPE_EXPR_H
#include "VType_Object.h"
#include "Expr.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Expr
//------------------------------------------------------------------------------
class VType_Expr : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frame) override;
};

extern VType_Expr VTYPE_Expr;

//------------------------------------------------------------------------------
// Value_Expr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Expr : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Expr);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Expr");
protected:
	RefPtr<Expr> _pExpr;
public:
	// Constructor
	Value_Expr() = delete;
	explicit Value_Expr(Expr *pExpr, VType& vtype = VTYPE_Expr) :
		Value_Object(vtype), _pExpr(pExpr) {}
	// Copy constructor/operator
	Value_Expr(const Value_Expr& src) :
		Value_Object(src), _pExpr(src._pExpr->Reference()) {}
	Value_Expr& operator=(const Value_Expr& src) = delete;
	// Move constructor/operator
	Value_Expr(Value_Expr&& src) = delete;
	Value_Expr& operator=(Value_Expr&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Expr() = default;
public:
	Expr& GetExpr() { return *_pExpr; }
	const Expr& GetExpr() const { return *_pExpr; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetExpr().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetExpr().IsEqualTo(dynamic_cast<const Value_Expr*>(pValue)->GetExpr());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetExpr().IsLessThan(dynamic_cast<const Value_Expr*>(pValue)->GetExpr()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetExpr().ToString(ss);
	}
};

}

#endif
