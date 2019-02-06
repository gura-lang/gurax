//==============================================================================
// DeclArg.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DeclArg
//------------------------------------------------------------------------------
DeclArg::DeclArg(const Symbol* pSymbol, DottedSymbol* pDottedSymbol,
				 OccurPattern occurPattern, UInt32 flags, Expr* pExprDefault) :
	_pSymbol(pSymbol), _pDottedSymbol(pDottedSymbol),
	_pKlass(pDottedSymbol->IsEmpty()?
			dynamic_cast<Klass*>(&Object_any::klass) : dynamic_cast<Klass*>(&Object_undefined::klass)),
	_occurPattern(occurPattern), _flags(flags), _pExprDefault(pExprDefault)
{
}

DeclArg::DeclArg(const Symbol* pSymbol, const Klass& klass,
				 OccurPattern occurPattern, UInt32 flags, Expr* pExprDefault) :
	_pSymbol(pSymbol), _pDottedSymbol(klass.MakeDottedSymbol()), _pKlass(&klass),
	_occurPattern(occurPattern), _flags(flags), _pExprDefault(pExprDefault)
{
}

DeclArg* DeclArg::Create(const Expr* pExpr, bool issueErrorFlag)
{
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
			return nullptr;
		}
		// x => value
		pExpr = pExprEx->GetExprLeft();
		pExprDefault.reset(pExprEx->GetExprRight()->Reference());
	}
	if (pExpr->IsType<Expr_UnaryOp>()) {
		const Expr_UnaryOp* pExprEx = dynamic_cast<const Expr_UnaryOp*>(pExpr);
		const Operator* pOperator = pExprEx->GetOperator();
		pExpr = pExprEx->GetExprChild();
		if (pOperator->IsType(OpType::PostMod)) {
			// x%
		} else if (pOperator->IsType(OpType::PostMul)) {
			// x*
			occurPattern = OccurPattern::ZeroOrMore;
		} else if (pOperator->IsType(OpType::PostPos)) {
			// x+
			occurPattern = OccurPattern::OnceOrMore;
		} else if (pOperator->IsType(OpType::PostQuestion)) {
			// x?
			occurPattern = OccurPattern::ZeroOrOnce;
		} else {
			if (issueErrorFlag) {
				Error::Issue(ErrorType::SyntaxError, "invalid format of declaration");
			}
			return nullptr;
		}
	}
	if (pExpr->IsType<Expr_Indexer>()) {
		const Expr_Indexer* pExprEx = dynamic_cast<const Expr_Indexer*>(pExpr);
		if (!pExprEx->GetExprLinkCdr().IsEmpty()) {
			if (issueErrorFlag) {
				Error::Issue(ErrorType::SyntaxError, "bracket must be empty");
			}
			return nullptr;
		}
		// x[]
		pExpr = pExprEx->GetExprCar();
		pAttrSrc = &pExprEx->GetAttr();
		flags |= Flag::ListVar;
	}
	if (!pExpr->IsType<Expr_Identifier>()) {
		if (issueErrorFlag) {
			Error::Issue(ErrorType::SyntaxError, "declaration must be an indentifier");
		}
		return nullptr;
	}
	const Expr_Identifier* pExprIdentifier = dynamic_cast<const Expr_Identifier*>(pExpr);
	const Symbol* pSymbol = pExprIdentifier->GetSymbol();
	if (!pAttrSrc) {
		pAttrSrc = &pExprIdentifier->GetAttr();
	} else if (!pExprIdentifier->GetAttr().IsEmpty()) {
		if (issueErrorFlag) {
			Error::Issue(ErrorType::SyntaxError, "invalid attribute");
		}
		return nullptr;
	}
	if (!pAttrSrc->GetSymbolsOpt().empty()) {
		if (issueErrorFlag) {
			Error::Issue(ErrorType::SyntaxError, "optional attribute can not be declared");
		}
		return nullptr;
	}
	pDottedSymbol.reset(pAttrSrc->GetDottedSymbol().Reference());
	bool firstFlag = true;
	for (const Symbol* pSymbol : pAttrSrc->GetSymbols()) {
		UInt32 flag = SymbolToFlag(pSymbol);
		flags |= flag;
		if (flag) {
			if (firstFlag) pDottedSymbol.reset(DottedSymbol::Empty.Reference());
		} else {
			if (!firstFlag) {
				if (issueErrorFlag) {
					Error::Issue(ErrorType::SyntaxError, "unsupported symbol: %s", pSymbol->GetName());
				}
				return nullptr;
			}
		}
		firstFlag = false;
	}
	return new DeclArg(pSymbol, pDottedSymbol.release(), occurPattern, flags, pExprDefault.release());
}

String DeclArg::FlagsToString(UInt32 flags)
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

const char* DeclArg::OccurPatternToString(OccurPattern occurPattern)
{
	return
		(occurPattern == OccurPattern::ZeroOrOnce)? "?" :
		(occurPattern == OccurPattern::ZeroOrMore)? "*" :
		(occurPattern == OccurPattern::OnceOrMore)? "+" : "";
}

String DeclArg::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += GetSymbol()->GetName();
	if (GetFlags() & Flag::ListVar) rtn += "[]";
	rtn += GetOccurPatternString();
	if (!GetDottedSymbol().IsEmpty()) {
		rtn += ':';
		rtn += GetDottedSymbol().ToString();
	} else if (ss.IsVerbose()) {
		rtn += ':';
		rtn += Object_any::klass.GetName();
	}
	rtn += FlagsToString(GetFlags() & ~Flag::ListVar);
	if (GetExprDefault()) {
		rtn += ss.IsCram()? "=>" : " => ";
		rtn += GetExprDefault()->ToString(ss);
	}
	return rtn;
}

}
