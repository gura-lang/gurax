//==============================================================================
// Object_quote.h
//==============================================================================
#ifndef GURAX_OBJECT_QUOTE_H
#define GURAX_OBJECT_QUOTE_H
#include "Object.h"
#include "Expr.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_quote
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_quote : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_quote);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_quote");
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare(Frame* pFrame) override;
	};
	static KlassEx klass;
private:
	RefPtr<Expr> _pExpr;
public:
	// Constructor
	Object_quote() = delete;
	explicit Object_quote(Expr *pExpr) : Object(klass), _pExpr(pExpr) {}
	// Copy constructor/operator
	Object_quote(const Object_quote& src) : Object(klass), _pExpr(src._pExpr->Reference()) {}
	Object_quote& operator=(const Object_quote& src) { _pExpr.reset(src._pExpr->Reference()); return *this; }
	// Move constructor/operator
	Object_quote(Object_quote&& src) : Object(klass), _pExpr(src._pExpr.release()) {}
	Object_quote& operator=(Object_quote&& src) noexcept { _pExpr.reset(src._pExpr.release()); return *this; }
protected:
	// Destructor
	~Object_quote() = default;
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
			GetExpr().IsEqualTo(dynamic_cast<const Object_quote*>(pObject)->GetExpr());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetExpr().IsLessThan(dynamic_cast<const Object_quote*>(pObject)->GetExpr()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetExpr().ToString(ss);
	}
};

}

#endif
