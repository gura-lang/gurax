//==============================================================================
// Object_Quote.h
//==============================================================================
#ifndef GURAX_OBJECT_QUOTE_H
#define GURAX_OBJECT_QUOTE_H
#include "Object.h"
#include "Expr.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Quote
//------------------------------------------------------------------------------
class VTypeT_Quote : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VTypeT_Quote VType_Quote;

//------------------------------------------------------------------------------
// Object_Quote
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Quote : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Quote);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Quote");
private:
	RefPtr<Expr> _pExpr;
public:
	// Constructor
	Object_Quote() = delete;
	explicit Object_Quote(Expr* pExpr) : Object(VType_Quote), _pExpr(pExpr) {}
	// Copy constructor/operator
	Object_Quote(const Object_Quote& src) : Object(src), _pExpr(src._pExpr->Reference()) {}
	Object_Quote& operator=(const Object_Quote& src) = delete;
	// Move constructor/operator
	Object_Quote(Object_Quote&& src) = delete;
	Object_Quote& operator=(Object_Quote&& src) noexcept = delete;
protected:
	// Destructor
	~Object_Quote() = default;
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
			GetExpr().IsEqualTo(dynamic_cast<const Object_Quote*>(pObject)->GetExpr());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetExpr().IsLessThan(dynamic_cast<const Object_Quote*>(pObject)->GetExpr()) :
			GetVType().IsLessThan(pObject->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetExpr().ToString(ss);
	}
};

}

#endif
