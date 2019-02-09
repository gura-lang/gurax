//==============================================================================
// Value_Expr.h
//==============================================================================
#ifndef GURAX_OBJECT_EXPR_H
#define GURAX_OBJECT_EXPR_H
#include "Value_Object.h"
#include "Expr.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Expr
//------------------------------------------------------------------------------
class VType_Expr : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
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
private:
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
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetExpr().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pValue) const override {
		return IsSameType(pValue) &&
			GetExpr().IsEqualTo(dynamic_cast<const Value_Expr*>(pValue)->GetExpr());
	}
	virtual bool IsLessThan(const Object* pValue) const override {
		return IsSameType(pValue)?
			GetExpr().IsLessThan(dynamic_cast<const Value_Expr*>(pValue)->GetExpr()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetExpr().ToString(ss);
	}
};

}

#endif
