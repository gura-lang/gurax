//==============================================================================
// Expr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Expr
//------------------------------------------------------------------------------
const char* Expr::_indentUnitDefault = "  ";

int Expr::CalcIndentLevel() const
{
	int indentLevel = 0;
	for (RefPtr<Expr> pExpr = Reference(); pExpr; pExpr.reset(pExpr->LockExprParent()), indentLevel++) ;
	return indentLevel;
}

String Expr::ComposeIndent(const char* indentUnit) const
{
	String rtn;
	for (RefPtr<Expr> pExpr = Reference(); pExpr; pExpr.reset(pExpr->LockExprParent()), rtn += indentUnit) ;
	return rtn;
}

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

void ExprList::SetExprParent(const Expr* pExprParent)
{
	for (Expr* pExpr : *this) pExpr->SetExprParent(pExprParent);
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
void Expr_Collector::AddExprElem(Expr* pExprElem)
{
	pExprElem->SetExprParent(this);
	_pExprOwnerElem->push_back(pExprElem);
}

//------------------------------------------------------------------------------
// Expr_Composite
//------------------------------------------------------------------------------
void Expr_Composite::AddExprCdr(Expr* pExprCdr)
{
	pExprCdr->SetExprParent(this);
	_pExprOwnerCdr->push_back(pExprCdr);
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

String Expr_Object::ToString(const StringStyle& ss) const
{
	return _pObject->ToString();
}

//------------------------------------------------------------------------------
// Expr_Identifier : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Identifier::typeInfo;

void Expr_Identifier::Exec() const
{
}

String Expr_Identifier::ToString(const StringStyle& ss) const
{
	return _pSymbol->ToString();
}

//------------------------------------------------------------------------------
// Expr_Suffixed : Expr_Node
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Suffixed::typeInfo;

void Expr_Suffixed::Exec() const
{
}

String Expr_Suffixed::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += IsNumber()? GetValueSTL() : GetValueSTL().MakeQuoted(true);
	rtn += GetSuffix()->GetName();
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_UnaryOp : Expr_Unary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_UnaryOp::typeInfo;

void Expr_UnaryOp::Exec() const
{
}

String Expr_UnaryOp::ToString(const StringStyle& ss) const
{
	String rtn;
	switch (GetOperator()->GetStyle()) {
	case OpStyle::OpUnary: {
		rtn += GetOperator()->GetSymbol();
		rtn += '(';
		rtn += GetExprChild()->ToString(ss);
		rtn += ')';
		break;
	}
	case OpStyle::OpPostUnary: {
		rtn += '(';
		rtn += GetExprChild()->ToString(ss);
		rtn += ')';
		rtn += GetOperator()->GetSymbol();
		break;
	}
	case OpStyle::MathUnary: {
		rtn += GetOperator()->GetSymbol();
		rtn += '(';
		rtn += GetExprChild()->ToString(ss);
		rtn += ')';
		break;
	}
	default:
		break;
	}
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_BinaryOp : Expr_Binary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_BinaryOp::typeInfo;

void Expr_BinaryOp::Exec() const
{
}

String Expr_BinaryOp::ToString(const StringStyle& ss) const
{
	String rtn;
	switch (GetOperator()->GetStyle()) {
	case OpStyle::OpBinary: {
		rtn += '(';
		rtn += GetExprLeft()->ToString(ss);
		rtn += ')';
		rtn += GetOperator()->GetSymbol();
		rtn += '(';
		rtn += GetExprRight()->ToString(ss);
		rtn += ')';
		break;
	}
	case OpStyle::MathBinary: {
		rtn += GetOperator()->GetSymbol();
		rtn += '(';
		rtn += GetExprLeft()->ToString(ss);
		rtn += ss.GetComma();
		rtn += GetExprRight()->ToString(ss);
		rtn += ')';
		break;
	}
	default:
		break;
	}
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_Assign : Expr_Binary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Assign::typeInfo;

void Expr_Assign::Exec() const
{
}

String Expr_Assign::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += GetExprLeft()->ToString(ss);
	if (!ss.IsCram()) rtn += ' ';
	if (_pOperator) rtn += _pOperator->GetSymbol();
	rtn += '=';
	if (!ss.IsCram()) rtn += ' ';
	rtn += GetExprRight()->ToString(ss);
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_Member : Expr_Binary
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Member::typeInfo;

void Expr_Member::Exec() const
{
}

String Expr_Member::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += GetExprLeft()->ToString(ss);
	rtn += '.';
	rtn += GetExprRight()->ToString(ss);
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_Root : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Root::typeInfo;

void Expr_Root::Exec() const
{
}

String Expr_Root::ToString(const StringStyle& ss) const
{
	String indent = ComposeIndent();
	String rtn;
	if (ss.IsMultiLine()) {
		for (const Expr* pExpr : GetExprsElem()) {
			rtn += indent;
			rtn += pExpr->ToString(ss);
			rtn += '\n';
		}
	} else {
		bool firstFlag = true;
		for (const Expr* pExpr : GetExprsElem()) {
			if (firstFlag) {
				firstFlag = false;
			} else if (!ss.IsCram()) {
				rtn += ' ';
			}
			rtn += pExpr->ToString(ss);
			rtn += ';';
		}
	}
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_Block : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Block::typeInfo;

void Expr_Block::Exec() const
{
}

String Expr_Block::ToString(const StringStyle& ss) const
{
	String rtn;
	return rtn;
}

//------------------------------------------------------------------------------
// Expr_Iterer : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Iterer::typeInfo;

void Expr_Iterer::Exec() const
{
}

String Expr_Iterer::ToString(const StringStyle& ss) const
{
	return "";
}

//------------------------------------------------------------------------------
// Expr_Lister : Expr_Collector
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Lister::typeInfo;

void Expr_Lister::Exec() const
{
}

String Expr_Lister::ToString(const StringStyle& ss) const
{
	return "";
}

//------------------------------------------------------------------------------
// Expr_Indexer : Expr_Compound
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Indexer::typeInfo;

void Expr_Indexer::Exec() const
{
}

String Expr_Indexer::ToString(const StringStyle& ss) const
{
	return "";
}

//------------------------------------------------------------------------------
// Expr_Caller : Expr_Compound
//------------------------------------------------------------------------------
const Expr::TypeInfo Expr_Caller::typeInfo;

void Expr_Caller::Exec() const
{
}

String Expr_Caller::ToString(const StringStyle& ss) const
{
	return "";
}

void Expr_Caller::AddExprElemBlock(Expr* pExprElem)
{
	pExprElem->SetExprParent(this);
	_pExprOwnerElemBlock->push_back(pExprElem);
}

void Expr_Caller::SetExprTrailer(Expr_Caller* pExprTrailer)
{
	_pExprTrailer.reset(pExprTrailer);
	if (_pExprTrailer) _pExprTrailer->SetExprParent(this);
}

void Expr_Caller::AppendExprTrailer(Expr_Caller* pExprTrailer)
{
#if 0
	if (_pExprBlock.IsNull()) {
		SetBlock(new Expr_Block());
		_implicitBlockFlag = true;
	}
	if (_implicitBlockFlag) {
		_pExprBlock->AddExpr(pExprCaller);
	} else {
		GetLastTrailer()->SetTrailer(pExprCaller);
	}
#endif
	GetExprTrailerLast()->SetExprTrailer(pExprTrailer);
}

Expr_Caller* Expr_Caller::GetExprTrailerLast()
{
	Expr_Caller* pExpr = this;
	for ( ; pExpr->GetExprTrailer() != nullptr; pExpr = pExpr->GetExprTrailer()) ;
	return pExpr;
}

}
