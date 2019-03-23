//==============================================================================
// VType_Dict.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

// %{block}
Gurax_DeclareStatementAlias(_dict_, "%")
{
	Declare(VTYPE_Dict, Flag::None);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::None);
}

Gurax_ImplementStatement(_dict_)
{
	Expr* pExpr = exprCaller.GetExprOfBlock()->GetExprElemFirst();
	composer.Add_CreateDict(exprCaller);						// [ValueDict]
	for ( ; pExpr; pExpr = pExpr->GetExprNext()) {
		if (pExpr->IsType<Expr_BinaryOp>() &&
			dynamic_cast<Expr_BinaryOp*>(pExpr)->GetOperator()->IsType(OpType::Pair)) {
			// %{ .. key => value .. }
			Expr_BinaryOp* pExprEx = dynamic_cast<Expr_BinaryOp*>(pExpr);
			pExprEx->GetExprLeft()->Compose(composer);			// [ValueDict ValueKey]
			pExprEx->GetExprRight()->Compose(composer);			// [ValueDict ValueKey ValueElem]
		} else if (pExpr->IsType<Expr_Block>()) {
			// %{ .. {key, value} .. }
			Expr_Block* pExprEx = dynamic_cast<Expr_Block*>(pExpr);
			if (pExprEx->CountExprElem() != 2) {
				Error::IssueWith(ErrorType::SyntaxError, exprCaller,
								 "block is expected to have a format of {key, value}");
				return;
			}
			Expr* pExprElem = pExprEx->GetExprElemFirst();
			pExprElem->Compose(composer);						// [ValueDict ValueKey]
			pExprElem = pExprElem->GetExprNext();
			pExprElem->Compose(composer);						// [ValueDict ValueKey ValueElem]
		} else {
			// %{ .. key, value .. }
			pExpr->Compose(composer);							// [ValueDict ValueKey]
			pExpr = pExpr->GetExprNext();
			if (!pExpr) {
				Error::IssueWith(ErrorType::SyntaxError, exprCaller,
								 "value is missing in the initialization list for dictionary");
				return;
			}
			pExpr->Compose(composer);							// [ValueDict ValueKey ValueElem]
		}
		composer.Add_AddDict(exprCaller);						// [ValueDict]
	}
}

//------------------------------------------------------------------------------
// VType_Dict
//------------------------------------------------------------------------------
VType_Dict VTYPE_Dict("Dict");

void VType_Dict::DoPrepare(Frame& frame)
{
	SetAttrs(VTYPE_Object, Flag::Mutable);
	frame.Assign(*this);
	frame.Assign(Gurax_CreateStatement(_dict_));
}

//------------------------------------------------------------------------------
// Value_Dict
//------------------------------------------------------------------------------

}
