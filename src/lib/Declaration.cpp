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
		RefPtr<ArgInfo> pArgInfo(CreateArgInfo(pExpr, issueErrorFlag));
		if (!pArgInfo) {
			Clear();
			return false;
		}
		_argInfoOwner.push_back(pArgInfo.release());
	}
	for (const Symbol* pSymbol : attr.GetSymbols()) {
		UInt32 flagCaller = SymbolToFlagCaller(pSymbol);
		_flagsCaller |= flagCaller;
		if (!flagCaller) _pAttr->AddSymbol(pSymbol);
	}
	_pAttr->AddSymbolsOpt(attr.GetSymbolsOpt());
	_validFlag = true;
	return true;
}

void Declaration::Clear()
{
	_validFlag = false;
	_argInfoOwner.Clear();
	_flagsCaller = 0;
	_pAttr.reset(new Attribute());
}

Declaration::ArgInfo* Declaration::CreateArgInfo(const Expr* pExpr, bool issueErrorFlag)
{
	RefPtr<DottedSymbol> pDottedSymbol;
	OccurPattern occurPattern = OccurPattern::Once;
	UInt32 flagsArg = 0;
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
		flagsArg |= FlagArg::ListVar;
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
		UInt32 flagArg = SymbolToFlagArg(pSymbol);
		flagsArg |= flagArg;
		if (flagArg) {
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
	return new ArgInfo(pSymbol, pDottedSymbol.release(), occurPattern, flagsArg, pExprDefault.release());
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
	rtn += FlagsCallerToString(_flagsCaller);
	rtn += _pAttr->ToString(ss);
	return rtn;
}

String Declaration::FlagsArgToString(UInt32 flagsArg)
{
	String rtn;
	for (UInt32 flagArg = 1; flagsArg; flagArg <<= 1, flagsArg >>= 1) {
		if (flagsArg & 1) {
			rtn += ':';
			rtn += FlagArgToSymbol(flagArg)->GetName();
		}
	}
	return rtn;
}

String Declaration::FlagsCallerToString(UInt32 flagsCaller)
{
	String rtn;
	for (UInt32 flagCaller = 1; flagsCaller; flagCaller <<= 1, flagsCaller >>= 1) {
		if (flagsCaller & 1) {
			rtn += ':';
			rtn += FlagCallerToSymbol(flagCaller)->GetName();
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
Declaration::ArgInfo::ArgInfo(const Symbol* pSymbol, DottedSymbol* pDottedSymbol,
							  OccurPattern occurPattern, UInt32 flagsArg, Expr* pExprDefault) :
	_pSymbol(pSymbol), _pDottedSymbol(pDottedSymbol), _pKlass(&Object_undefined::klass),
	_occurPattern(occurPattern), _flagsArg(flagsArg), _pExprDefault(pExprDefault)
{
}

Declaration::ArgInfo::ArgInfo(const Symbol* pSymbol, const Klass& klass,
							  OccurPattern occurPattern, UInt32 flagsArg, Expr* pExprDefault) :
	_pSymbol(pSymbol), _pDottedSymbol(klass.MakeDottedSymbol()), _pKlass(&klass),
	_occurPattern(occurPattern), _flagsArg(flagsArg), _pExprDefault(pExprDefault)
{
}

String Declaration::ArgInfo::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += GetSymbol()->GetName();
	if (GetFlagsArg() & FlagArg::ListVar) rtn += "[]";
	rtn += GetOccurPatternString();
	if (!GetDottedSymbol().IsEmpty()) {
		rtn += ':';
		rtn += GetDottedSymbol().ToString();
	} else if (ss.IsVerbose()) {
		rtn += ":any";
	}
	rtn += FlagsArgToString(GetFlagsArg() & ~FlagArg::ListVar);
	if (GetExprDefault()) {
		rtn += ss.IsCram()? "=>" : " => ";
		rtn += GetExprDefault()->ToString(ss);
	}
	return rtn;
}

}
