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
const ExprList ExprList::Empty;

void ExprList::Exec() const
{
	for (const Expr* pExpr : *this) {
		pExpr->Exec();
		if (Error::IsIssued()) return;
	}
}

void ExprList::SetParent(const Expr* pExprParent)
{
	for (Expr* pExpr : *this) pExpr->SetParent(pExprParent);
}

//------------------------------------------------------------------------------
// ExprOwner
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Expr_Node
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Expr_Unary
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Expr_Binary
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Expr_Collector
//------------------------------------------------------------------------------
void Expr_Collector::AddChild(Expr* pExpr)
{
	pExpr->SetParent(this);
	_pExprChildren->push_back(pExpr);
}

//------------------------------------------------------------------------------
// Expr_Composite
//------------------------------------------------------------------------------
void Expr_Composite::AddCdr(Expr* pExpr)
{
	pExpr->SetParent(this);
	_pExprsCdr->push_back(pExpr);
}

void Expr_Composite::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Object : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Object::typeInfo;

void Expr_Object::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Identifier : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Identifier::typeInfo;

void Expr_Identifier::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Suffixed : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Suffixed::typeInfo;

void Expr_Suffixed::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_UnaryOp : Expr_Unary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_UnaryOp::typeInfo;

void Expr_UnaryOp::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_BinaryOp : Expr_Binary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_BinaryOp::typeInfo;

void Expr_BinaryOp::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Assign : Expr_Binary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Assign::typeInfo;

void Expr_Assign::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Member : Expr_Binary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Member::typeInfo;

void Expr_Member::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Block : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Block::typeInfo;

void Expr_Block::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Iterer : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Iterer::typeInfo;

void Expr_Iterer::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Lister : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Lister::typeInfo;

void Expr_Lister::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Indexer : Expr_Compound
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Indexer::typeInfo;

void Expr_Indexer::Exec() const
{
}

//------------------------------------------------------------------------------
// Expr_Caller : Expr_Compound
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Caller::typeInfo;

void Expr_Caller::Exec() const
{
}

}
