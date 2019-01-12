//==============================================================================
// Object_expr.h
//==============================================================================
#ifndef GURAX_OBJECT_EXPR_H
#define GURAX_OBJECT_EXPR_H
#include "Object.h"
#include "Expr.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_expr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_expr : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_expr);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_expr");
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare() override;
	};
	static KlassEx klass;
private:
	RefPtr<Expr> _pExpr;
public:
	// Constructor
	Object_expr() = delete;
	explicit Object_expr(Expr *pExpr) : Object(klass), _pExpr(pExpr) {}
	// Copy constructor/operator
	Object_expr(const Object_expr& src) : Object(klass), _pExpr(src._pExpr->Reference()) {}
	Object_expr& operator=(const Object_expr& src) { _pExpr.reset(src._pExpr->Reference()); return *this; }
	// Move constructor/operator
	Object_expr(Object_expr&& src) : Object(klass), _pExpr(src._pExpr.release()) {}
	Object_expr& operator=(Object_expr&& src) noexcept { _pExpr.reset(src._pExpr.release()); return *this; }
protected:
	// Destructor
	~Object_expr() = default;
public:
	const Expr* GetExpr() const { return _pExpr.get(); }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return reinterpret_cast<size_t>(this); }
	virtual bool IsEqualTo(const Object* pObject) const override { return IsIdentical(pObject); }
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetExpr()->IsLessThan(dynamic_cast<const Object_expr*>(pObject)->GetExpr()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle&) const override { return _pExpr->ToString(); }
};

}

#endif
