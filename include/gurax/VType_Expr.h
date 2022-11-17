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
class GURAX_DLLDECLARE VType_Expr : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Expr VTYPE_Expr;

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
	static VType& vtype;
public:
	// Constructor
	Value_Expr() = delete;
	explicit Value_Expr(Expr* pExpr, VType& vtype = VTYPE_Expr) :
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
	static Expr& GetExpr(Value& value) { return dynamic_cast<Value_Expr&>(value).GetExpr(); }
	static const Expr& GetExpr(const Value& value) { return dynamic_cast<const Value_Expr&>(value).GetExpr(); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override;
	virtual bool IsEqualTo(const Value& value) const override;
	virtual bool IsLessThan(const Value& value) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
