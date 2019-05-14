//==============================================================================
// VType_Dict.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of statement
//------------------------------------------------------------------------------
// %{block}
Gurax_DeclareStatementAlias(_dict_, "%")
{
	Declare(VTYPE_Dict, Flag::None);
	DeclareBlock(DeclBlock::Occur::Once, DeclBlock::Flag::None);
}

Gurax_ImplementStatement(_dict_)
{
	Expr* pExpr = exprCaller.GetExprOfBlock()->GetExprElemFirst();
	composer.Add_CreateDict(exprCaller);						// [Dict]
	for ( ; pExpr; pExpr = pExpr->GetExprNext()) {
		if (pExpr->IsType<Expr_BinaryOp>() &&
			dynamic_cast<Expr_BinaryOp*>(pExpr)->GetOperator()->IsType(OpType::Pair)) {
			// %{ .. key => value .. }
			Expr_BinaryOp* pExprEx = dynamic_cast<Expr_BinaryOp*>(pExpr);
			pExprEx->GetExprLeft()->ComposeOrNil(composer);		// [Dict Key]
			pExprEx->GetExprRight()->ComposeOrNil(composer);	// [Dict Key Elem]
		} else if (pExpr->IsType<Expr_Block>()) {
			// %{ .. {key, value} .. }
			Expr_Block* pExprEx = dynamic_cast<Expr_Block*>(pExpr);
			if (pExprEx->CountExprElem() != 2) {
				Error::IssueWith(ErrorType::SyntaxError, exprCaller,
								 "block is expected to have a format of {key, value}");
				return;
			}
			Expr* pExprElem = pExprEx->GetExprElemFirst();
			pExprElem->ComposeOrNil(composer);					// [Dict Key]
			pExprElem = pExprElem->GetExprNext();
			pExprElem->ComposeOrNil(composer);					// [Dict Key Elem]
		} else {
			// %{ .. key, value .. }
			pExpr->ComposeOrNil(composer);						// [Dict Key]
			pExpr = pExpr->GetExprNext();
			if (!pExpr) {
				Error::IssueWith(ErrorType::SyntaxError, exprCaller,
								 "value is missing in the initialization list for dictionary");
				return;
			}
			pExpr->ComposeOrNil(composer);						// [Dict Key Elem]
		}
		composer.Add_DictElem(exprCaller, 0);					// [Dict]
	}
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Dict#keys
Gurax_DeclareProperty_R(Dict, keys)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns a list of keys.");
}

Gurax_ImplementPropertyGetter(Dict, keys)
{
	auto& valueThis = GetValueThis(valueTarget);
	RefPtr<ValueOwner> pValueOwner(valueThis.GetValueDict().GetKeys());
	pValueOwner->Sort();
	VType* pVType = pValueOwner->GetVTypeOfElems();
	return new Value_List(new ValueTypedOwner(pVType, pValueOwner.release()));
}

// Dict#len
Gurax_DeclareProperty_R(Dict, len)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns the number of elements in the list.");
}

Gurax_ImplementPropertyGetter(Dict, len)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetValueDict().size());
}

//------------------------------------------------------------------------------
// VType_Dict
//------------------------------------------------------------------------------
VType_Dict VTYPE_Dict("Dict");

void VType_Dict::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Mutable);
	// Assignment of statement
	frameOuter.Assign(Gurax_CreateStatement(_dict_));
	// Assignment of property
	Assign(Gurax_CreateProperty(Dict, len));
	Assign(Gurax_CreateProperty(Dict, keys));
}

//------------------------------------------------------------------------------
// Value_Dict
//------------------------------------------------------------------------------
String Value_Dict::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Printf(":%zuitems>", GetValueDict().size());
	return str;
}

String Value_Dict::ToStringDetail(const StringStyle& ss) const
{
	return GetValueDict().ToString(ss);
}

}
