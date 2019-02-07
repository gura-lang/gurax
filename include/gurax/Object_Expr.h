//==============================================================================
// Object_Expr.h
//==============================================================================
#ifndef GURAX_OBJECT_EXPR_H
#define GURAX_OBJECT_EXPR_H
#include "Object.h"
#include "Expr.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_Expr
//------------------------------------------------------------------------------
class KlassT_Expr : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_Expr Klass_Expr;

//------------------------------------------------------------------------------
// Object_Expr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Expr : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Expr);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Expr");
private:
	RefPtr<Expr> _pExpr;
public:
	// Constructor
	Object_Expr() = delete;
	explicit Object_Expr(Expr *pExpr) : Object(Klass_Expr), _pExpr(pExpr) {}
	// Copy constructor/operator
	Object_Expr(const Object_Expr& src) : Object(Klass_Expr), _pExpr(src._pExpr->Reference()) {}
	Object_Expr& operator=(const Object_Expr& src) { _pExpr.reset(src._pExpr->Reference()); return *this; }
	// Move constructor/operator
	Object_Expr(Object_Expr&& src) : Object(Klass_Expr), _pExpr(src._pExpr.release()) {}
	Object_Expr& operator=(Object_Expr&& src) noexcept { _pExpr.reset(src._pExpr.release()); return *this; }
protected:
	// Destructor
	~Object_Expr() = default;
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
			GetExpr().IsEqualTo(dynamic_cast<const Object_Expr*>(pObject)->GetExpr());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetExpr().IsLessThan(dynamic_cast<const Object_Expr*>(pObject)->GetExpr()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetExpr().ToString(ss);
	}
};

}

#endif
