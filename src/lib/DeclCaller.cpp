//==============================================================================
// DeclCaller.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DeclCaller
//------------------------------------------------------------------------------
const DeclCaller* DeclCaller::Empty = nullptr;
const DeclCaller* DeclCaller::Invalid = nullptr;

void DeclCaller::Bootup()
{
	Empty = new DeclCaller(true);
	Invalid = new DeclCaller(false);
}

bool DeclCaller::Prepare(const ExprLink& exprLinkCdr, const Attribute& attr, bool issueErrorFlag)
{
	_declArgOwner.reserve(exprLinkCdr.GetSize());
	for (const Expr* pExpr = exprLinkCdr.GetExprHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		RefPtr<DeclArg> pDeclArg(DeclArg::CreateFromExpr(pExpr, issueErrorFlag));
		if (!pDeclArg) {
			Clear();
			return false;
		}
		_declArgOwner.push_back(pDeclArg.release());
	}
	for (const Symbol* pSymbol : attr.GetSymbols()) {
		UInt32 flag = SymbolToFlag(pSymbol);
		_flags |= flag;
		if (!flag) _pAttr->AddSymbol(pSymbol);
	}
	_pAttr->AddSymbolsOpt(attr.GetSymbolsOpt());
	_validFlag = true;
	return true;
}

void DeclCaller::Clear()
{
	_validFlag = false;
	_declArgOwner.Clear();
	_flags = 0;
	_pAttr.reset(new Attribute());
}

String DeclCaller::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += '(';
	rtn += GetDeclArgOwner().ToString(ss);
	rtn += ')';
	rtn += FlagsToString(_flags);
	rtn += GetAttr().ToString(ss);
	return rtn;
}

String DeclCaller::FlagsToString(UInt32 flags)
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

}
