//==============================================================================
// Value_Quote.h
//==============================================================================
#ifndef GURAX_OBJECT_QUOTE_H
#define GURAX_OBJECT_QUOTE_H
#include "Object.h"
#include "Expr.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Quote
//------------------------------------------------------------------------------
class VType_Quote : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VType_Quote VTYPE_Quote;

//------------------------------------------------------------------------------
// Value_Quote
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Quote : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Quote);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Quote");
private:
	RefPtr<Expr> _pExpr;
public:
	// Constructor
	Value_Quote() = delete;
	explicit Value_Quote(Expr* pExpr) : Object(VTYPE_Quote), _pExpr(pExpr) {}
	// Copy constructor/operator
	Value_Quote(const Value_Quote& src) : Object(src), _pExpr(src._pExpr->Reference()) {}
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
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetExpr().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pValue) const override {
		return IsSameType(pValue) &&
			GetExpr().IsEqualTo(dynamic_cast<const Value_Quote*>(pValue)->GetExpr());
	}
	virtual bool IsLessThan(const Object* pValue) const override {
		return IsSameType(pValue)?
			GetExpr().IsLessThan(dynamic_cast<const Value_Quote*>(pValue)->GetExpr()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetExpr().ToString(ss);
	}
};

}

#endif
