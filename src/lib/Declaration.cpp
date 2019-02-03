//==============================================================================
// Declaration.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Declaration
//------------------------------------------------------------------------------
void Declaration::Bootup()
{
}

bool Declaration::Prepare(const ExprLink& exprLinkCdr, const Attribute& attr, bool issueErrorFlag)
{
	_argInfoOwner.reserve(exprLinkCdr.GetSize());
	for (const Expr* pExpr = exprLinkCdr.GetExprHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		RefPtr<DottedSymbol> pDottedSymbol;
		UInt32 flags = 0;
		RefPtr<Expr> pExprDefault;
		const Attribute* pAttrSrc = nullptr;
		if (pExpr->IsType<Expr_Assign>()) {
			const Expr_Assign* pExprEx = dynamic_cast<const Expr_Assign*>(pExpr);
			pExpr = pExprEx->GetExprLeft();
			pExprDefault.reset(pExprEx->GetExprRight()->Reference());
		}
		if (pExpr->IsType<Expr_Indexer>()) {
			const Expr_Indexer* pExprEx = dynamic_cast<const Expr_Indexer*>(pExpr);
			pExpr = pExprEx->GetExprCar();
			if (!pExprEx->GetExprLinkCdr().IsEmpty()) {
				if (issueErrorFlag) {
					Error::Issue(ErrorType::SyntaxError, "bracket must be empty");
				}
				return false;
			}
			pAttrSrc = &pExprEx->GetAttr();
			flags |= Flag::ListVar;
		}
		if (!pExpr->IsType<Expr_Identifier>()) {
			if (issueErrorFlag) {
				Error::Issue(ErrorType::SyntaxError, "declaration must be an indentifier");
			}
			return false;
		}
		const Expr_Identifier* pExprIdentifier = dynamic_cast<const Expr_Identifier*>(pExpr);
		const Symbol* pSymbol = pExprIdentifier->GetSymbol();
		if (!pAttrSrc) {
			pAttrSrc = &pExprIdentifier->GetAttr();
		} else if (!pExprIdentifier->GetAttr().IsEmpty()) {
			if (issueErrorFlag) {
				Error::Issue(ErrorType::SyntaxError, "invalid attribute");
			}
			return false;
		}
		if (!pAttrSrc->GetSymbolsOpt().empty()) {
			if (issueErrorFlag) {
				Error::Issue(ErrorType::SyntaxError, "optional attribute can not be declared");
			}
			return false;
		}
		pDottedSymbol.reset(pAttrSrc->GetDottedSymbol().Reference());
		for (const Symbol* pSymbol : pAttrSrc->GetSymbols()) {
			if (pSymbol->IsIdentical(Gurax_Symbol(map))) {
				flags |= Flag::Map;
			} else if (pSymbol->IsIdentical(Gurax_Symbol(nil))) {
				flags |= Flag::Nil;
			} else if (pSymbol->IsIdentical(Gurax_Symbol(nomap))) {
				flags |= Flag::NoMap;
			} else if (pSymbol->IsIdentical(Gurax_Symbol(r))) {
				flags |= Flag::Read;
			} else if (pSymbol->IsIdentical(Gurax_Symbol(w))) {
				flags |= Flag::Write;
			} else {
				if (issueErrorFlag) {
					Error::Issue(ErrorType::SyntaxError, "unsupported symbol: %s", pSymbol->GetName());
				}
				return false;
			}
		}
		_argInfoOwner.push_back(new ArgInfo(
									pSymbol, pDottedSymbol.release(), flags, pExprDefault.release()));
	}
	_pAttr.reset(attr.Reference());
	_validFlag = true;
	return true;
}

}
