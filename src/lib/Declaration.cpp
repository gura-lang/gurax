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
	const UInt32 flagsAcceptable =
		Flag::Closure | Flag::CutExtraArgs | Flag::DynamicScope | Flag::EndMarker |
		Flag::Finalizer | Flag::Flat | Flag::Fork | Flag::Leader | Flag::ListVar |
		Flag::Map | Flag::Nil | Flag::NoCast | Flag::NoMap | Flag::NoNamed | Flag::Private |
		Flag::Privileged | Flag::Public | Flag::SymbolFunc | Flag::Trailer;
	const UInt32 flagArgAcceptable = Flag::Map | Flag::Nil | Flag::NoMap | Flag::Read | Flag::Write;
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
				Clear();
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
				Clear();
				return false;
			}
			// f(x[])
			pExpr = pExprEx->GetExprCar();
			pAttrSrc = &pExprEx->GetAttr();
			flags |= Flag::ListVar;
		}
		if (pExpr->IsType<Expr_UnaryOp>()) {
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
				Clear();
				return false;
			}
		}
		if (!pExpr->IsType<Expr_Identifier>()) {
			if (issueErrorFlag) {
				Error::Issue(ErrorType::SyntaxError, "declaration must be an indentifier");
			}
			Clear();
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
			Clear();
			return false;
		}
		if (!pAttrSrc->GetSymbolsOpt().empty()) {
			if (issueErrorFlag) {
				Error::Issue(ErrorType::SyntaxError, "optional attribute can not be declared");
			}
			Clear();
			return false;
		}
		pDottedSymbol.reset(pAttrSrc->GetDottedSymbol().Reference());
		bool firstFlag = true;
		for (const Symbol* pSymbol : pAttrSrc->GetSymbols()) {
			UInt32 flag = SymbolToFlag(pSymbol) & flagArgAcceptable;
			flags |= flag;
			if (flag) {
				if (firstFlag) pDottedSymbol.reset(nullptr);
			} else {
				if (!firstFlag) {
					if (issueErrorFlag) {
						Error::Issue(ErrorType::SyntaxError, "unsupported symbol: %s", pSymbol->GetName());
					}
					Clear();
					return false;
				}
			}
			firstFlag = false;
		}
		_argInfoOwner.push_back(new ArgInfo(
									pSymbol, occurPattern, pDottedSymbol.release(), flags, pExprDefault.release()));
	}
	_pAttr->SetDottedSymbol(attr.GetDottedSymbol().Reference());
	for (const Symbol* pSymbol : attr.GetSymbols()) {
		UInt32 flag = SymbolToFlag(pSymbol) & flagsAcceptable;
		_flags |= flag;
		if (!flag) _pAttr->AddSymbol(pSymbol);
	}
	_pAttr->AddSymbolsOpt(attr.GetSymbolsOpt());
	_validFlag = true;
	return true;
}

void Declaration::Clear()
{
	_validFlag = false;
	_argInfoOwner.Clear();
	_flags = 0;
	_pAttr.reset(new Attribute());
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
	for (UInt32 flag = 1; flags; flag <<= 1, flags >>= 1) {
		if (flags & 1) {
			rtn += ':';
			rtn += FlagToSymbol(flag)->GetName();
		}
	}
	return rtn;
}

const char* Declaration::OccurPatternToString(OccurPattern occurPattern)
{
	return
		(occurPattern == OccurPattern::ZeroOrOnce)? "?" :
		(occurPattern == OccurPattern::ZeroOrMore)? "*" :
		(occurPattern == OccurPattern::OnceOrMore)? "+" : "";
}

//------------------------------------------------------------------------------
// Declaration::ArgInfo
//------------------------------------------------------------------------------
String Declaration::ArgInfo::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += _pSymbol->GetName();
	if (GetFlags() & Flag::ListVar) rtn += "[]";
	rtn += OccurPatternToString(_occurPattern);
	if (!_pDottedSymbol->IsEmpty()) {
		rtn += ':';
		rtn += _pDottedSymbol->ToString();
	}
	rtn += FlagsToString(_flags);
	if (_pExprDefault) {
		rtn += ss.IsCram()? "=>" : " => ";
		rtn += _pExprDefault->ToString(ss);
	}
	return rtn;
}

}
