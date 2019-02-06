//==============================================================================
// DeclCaller.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DeclCaller
//------------------------------------------------------------------------------
void DeclCaller::Bootup()
{
}

bool DeclCaller::Prepare(const ExprLink& exprLinkCdr, const Attribute& attr, bool issueErrorFlag)
{
	_declArgOwner.reserve(exprLinkCdr.GetSize());
	for (const Expr* pExpr = exprLinkCdr.GetExprHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		RefPtr<DeclArg> pDeclArg(DeclArg::Create(pExpr, issueErrorFlag));
		if (!pDeclArg) {
			Clear();
			return false;
		}
		_declArgOwner.push_back(pDeclArg.release());
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

void DeclCaller::Clear()
{
	_validFlag = false;
	_declArgOwner.Clear();
	_flagsCaller = 0;
	_pAttr.reset(new Attribute());
}

String DeclCaller::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += '(';
	for (auto ppDeclArg = _declArgOwner.begin(); ppDeclArg != _declArgOwner.end(); ppDeclArg++) {
		const DeclArg* pDeclArg = *ppDeclArg;
		if (ppDeclArg != _declArgOwner.begin()) rtn += ss.GetComma();
		rtn += pDeclArg->ToString(ss);
	}
	rtn += ')';
	rtn += FlagsCallerToString(_flagsCaller);
	rtn += _pAttr->ToString(ss);
	return rtn;
}

String DeclCaller::FlagsCallerToString(UInt32 flagsCaller)
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

}
