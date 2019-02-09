//==============================================================================
// Object_Expr.h
//==============================================================================
#ifndef GURAX_OBJECT_EXPR_H
#define GURAX_OBJECT_EXPR_H
#include "Object_Object.h"
#include "Expr.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Expr
//------------------------------------------------------------------------------
class VTypeT_Expr : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VTypeT_Expr VType_Expr;

//------------------------------------------------------------------------------
// Object_Expr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Expr : public Object_Object {
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
	explicit Object_Expr(Expr *pExpr, VType& vtype = VType_Expr) :
		Object_Object(vtype), _pExpr(pExpr) {}
	// Copy constructor/operator
	Object_Expr(const Object_Expr& src) :
		Object_Object(src), _pExpr(src._pExpr->Reference()) {}
	Object_Expr& operator=(const Object_Expr& src) = delete;
	// Move constructor/operator
	Object_Expr(Object_Expr&& src) = delete;
	Object_Expr& operator=(Object_Expr&& src) noexcept = delete;
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
			GetVType().IsLessThan(pObject->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetExpr().ToString(ss);
	}
};

}

#endif
