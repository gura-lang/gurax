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
		OccurPattern occurPattern = OccurPattern::Once;
		UInt32 flags = 0;
		RefPtr<Expr> pExprDefault;
		const Attribute* pAttrSrc = nullptr;
		if (pExpr->IsType<Expr_BinaryOp>()) {
			const Expr_BinaryOp* pExprEx = dynamic_cast<const Expr_BinaryOp*>(pExpr);
			if (!pExprEx->GetOperator()->IsType(OpType::Pair)) {
				if (issueErrorFlag) {
					Error::Issue(ErrorType::SyntaxError, "invalid format of declaration");
				}
				return false;
			}
			// f(x => value)
			pExpr = pExprEx->GetExprLeft();
			pExprDefault.reset(pExprEx->GetExprRight()->Reference());
		}
		if (pExpr->IsType<Expr_Indexer>()) {
			const Expr_Indexer* pExprEx = dynamic_cast<const Expr_Indexer*>(pExpr);
			if (!pExprEx->GetExprLinkCdr().IsEmpty()) {
				if (issueErrorFlag) {
					Error::Issue(ErrorType::SyntaxError, "bracket must be empty");
				}
				return false;
			}
			// f(x[])
			pExpr = pExprEx->GetExprCar();
			pAttrSrc = &pExprEx->GetAttr();
			flags |= Flag::ListVar;
		} else if (pExpr->IsType<Expr_UnaryOp>()) {
			const Expr_UnaryOp* pExprEx = dynamic_cast<const Expr_UnaryOp*>(pExpr);
			const Operator* pOperator = pExprEx->GetOperator();
			pExpr = pExprEx->GetExprChild();
			if (pOperator->IsType(OpType::PostMod)) {
				// f(x%)
			} else if (pOperator->IsType(OpType::PostMul)) {
				// f(x*)
				occurPattern = OccurPattern::ZeroOrMore;
			} else if (pOperator->IsType(OpType::PostPos)) {
				// f(x+)
				occurPattern = OccurPattern::OnceOrMore;
			} else if (pOperator->IsType(OpType::PostQuestion)) {
				// f(x?)
				occurPattern = OccurPattern::ZeroOrOnce;
			} else {
				if (issueErrorFlag) {
					Error::Issue(ErrorType::SyntaxError, "invalid format of declaration");
				}
				return false;
			}
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
									pSymbol, occurPattern, pDottedSymbol.release(), flags, pExprDefault.release()));
	}
	_pAttr.reset(attr.Reference());
	_validFlag = true;
	return true;
}

String Declaration::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += '(';
	for (auto ppArgInfo = _argInfoOwner.begin(); ppArgInfo != _argInfoOwner.end(); ppArgInfo++) {
		const ArgInfo* pArgInfo = *ppArgInfo;
		if (ppArgInfo != _argInfoOwner.begin()) rtn += ss.GetComma();
		rtn += pArgInfo->ToString(ss);
	}
	rtn += ')';
	rtn += _pAttr->ToString(ss);
	return rtn;
}

String Declaration::FlagsToString(UInt32 flags)
{
	String rtn;
	return rtn;
}

String Declaration::OccurPatternToString(OccurPattern occurPattern)
{
	String rtn;
	return rtn;
}

//------------------------------------------------------------------------------
// Declaration::ArgInfo
//------------------------------------------------------------------------------
String Declaration::ArgInfo::ToString(const StringStyle& ss) const
{
	String rtn;
	return rtn;
}

}
