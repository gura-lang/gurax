//==============================================================================
// Object_expr.h
//==============================================================================
#ifndef GURAX_OBJECT_EXPR_H
#define GURAX_OBJECT_EXPR_H
#include "Object.h"
#include "Expr.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_expr
//------------------------------------------------------------------------------
class KlassT_expr : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_expr Klass_expr;

//------------------------------------------------------------------------------
// Object_expr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_expr : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_expr);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_expr");
private:
	RefPtr<Expr> _pExpr;
public:
	// Constructor
	Object_expr() = delete;
	explicit Object_expr(Expr *pExpr) : Object(Klass_expr), _pExpr(pExpr) {}
	// Copy constructor/operator
	Object_expr(const Object_expr& src) : Object(Klass_expr), _pExpr(src._pExpr->Reference()) {}
	Object_expr& operator=(const Object_expr& src) { _pExpr.reset(src._pExpr->Reference()); return *this; }
	// Move constructor/operator
	Object_expr(Object_expr&& src) : Object(Klass_expr), _pExpr(src._pExpr.release()) {}
	Object_expr& operator=(Object_expr&& src) noexcept { _pExpr.reset(src._pExpr.release()); return *this; }
protected:
	// Destructor
	~Object_expr() = default;
public:
	Expr& GetExpr() { return *_pExpr; }
	const Expr& GetExpr() const { return *_pExpr; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetExpr().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetExpr().IsEqualTo(dynamic_cast<const Object_expr*>(pObject)->GetExpr());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetExpr().IsLessThan(dynamic_cast<const Object_expr*>(pObject)->GetExpr()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetExpr().ToString(ss);
	}
};

}

#endif
