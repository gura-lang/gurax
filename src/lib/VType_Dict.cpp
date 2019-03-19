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
	for (Expr* pExpr = pExprCaller->GetExprOfBlock()->GetExprElemFirst();
		 pExpr; pExpr = pExpr->GetExprNext()) {
		pExpr->Compose(composer);
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
