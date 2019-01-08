//==============================================================================
// Expr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Expr
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ExprList
//------------------------------------------------------------------------------
void ExprList::Exec() const
{
	for (const Expr* pExpr : *this) {
		pExpr->Exec();
		if (Error::IsIssued()) return;
	}
}

//------------------------------------------------------------------------------
// ExprOwner
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Expr_Unary
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Expr_UnaryOp
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_UnaryOp::typeInfo;

void Expr_UnaryOp::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Binary
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Expr_BinaryOp
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_BinaryOp::typeInfo;

void Expr_BinaryOp::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Assign
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Assign::typeInfo;

void Expr_Assign::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Container
//------------------------------------------------------------------------------
void Expr_Container::AddChild(Expr* pExpr)
{
	pExpr->SetParent(this);
	_pExprChildren->push_back(pExpr);
}

//------------------------------------------------------------------------------
// Expr_Block
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Block::typeInfo;

void Expr_Block::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Lister
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Lister::typeInfo;

void Expr_Lister::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Composite
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Composite::typeInfo;

void Expr_Composite::AddCdr(Expr* pExpr)
{
	pExpr->SetParent(this);
	_pExprCdrs->push_back(pExpr);
}

void Expr_Composite::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Object
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Object::typeInfo;

void Expr_Object::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Identifier
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Identifier::typeInfo;

void Expr_Identifier::Exec() const
{
}

}
