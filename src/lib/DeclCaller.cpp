//==============================================================================
// DeclCaller.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DeclCaller
//------------------------------------------------------------------------------
const DeclCaller* DeclCaller::Empty = nullptr;

void DeclCaller::Bootup()
{
	Empty = new DeclCaller();
}

DeclCaller::DeclCaller() : _pVType(&VTYPE_Any), _flags(0), _pAttr(new Attribute())
{
}

bool DeclCaller::Prepare(const ExprLink& exprLinkCdr, const Attribute& attr)
{
	_declArgOwner.reserve(exprLinkCdr.GetSize());
	for (const Expr* pExpr = exprLinkCdr.GetExprHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		RefPtr<DeclArg> pDeclArg(DeclArg::CreateFromExpr(pExpr));
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
	return true;
}

void DeclCaller::Clear()
{
	_declArgOwner.Clear();
	_flags = 0;
	_pAttr.reset(new Attribute());
}

bool DeclCaller::CheckAttribute(const Attribute& attr) const
{
	for (const Symbol* pSymbol: attr.GetSymbols()) {
		if (!GetAttr().GetSymbolSetOpt().IsSet(pSymbol)) {
			Error::Issue(ErrorType::ArgumentError, "unacceptable attribute symbol: %s", pSymbol->GetName());
			return false;
		}
	}
	return true;
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

UInt32 DeclCaller::SymbolsToFlags(const SymbolList& symbols)
{
	UInt32 flags = 0;
	for (const Symbol* pSymbol : symbols) flags |= SymbolToFlag(pSymbol);
	return flags;
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
