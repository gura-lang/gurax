//==============================================================================
// Expr.h
//==============================================================================
#ifndef GURAX_EXPR_H
#define GURAX_EXPR_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Expr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Expr : public Referable {
public:
	// Constructor
	Expr() {}
	// Copy constructor/operator
	Expr(const Expr& src) = delete;
	Expr& operator=(const Expr& src) = delete;
	// Move constructor/operator
	Expr(Expr&& src) = delete;
	Expr& operator=(Expr&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Expr() = default;
public:
	// Referable accessor
	Gurax_DeclareReferable(Expr);
};

//------------------------------------------------------------------------------
// ExprList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ExprList : public std::vector<Expr*> {
};

//------------------------------------------------------------------------------
// ExprOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ExprOwner : public ExprList, public Referable {
protected:
	~ExprOwner() { Clear(); }
public:
	// Referable accessor
	Gurax_DeclareReferable(ExprOwner);
public:
	void Clear() {
		for (auto pExpr : *this) Expr::Delete(pExpr);
		clear();
	}
};

}

#endif
