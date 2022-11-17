//==============================================================================
// SuffixMgr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// SuffixMgr
//------------------------------------------------------------------------------
const Symbol* SuffixMgr::ModeToSymbol(Mode mode)
{
	return
		(mode == SuffixMgr::Mode::Number)? Gurax_Symbol(number) :
		(mode == SuffixMgr::Mode::String)? Gurax_Symbol(string) :
		(mode == SuffixMgr::Mode::Binary)? Gurax_Symbol(binary) : Symbol::Empty;
}

String SuffixMgr::ToString(const StringStyle& ss) const
{
	return "SuffixMgr";
}

Value* SuffixMgr::Eval(Processor& processor, const char* str) const
{
	return Value::nil();
}

void SuffixMgr::Compose(Composer& composer, const StringReferable& strRef, const Expr* pExpr) const
{
	composer.Add_Suffixed(strRef.Reference(), GetMode(), GetSymbol(), *pExpr);
}

//------------------------------------------------------------------------------
// SuffixMgrMap
//------------------------------------------------------------------------------
void SuffixMgrMap::Clear()
{
	for (auto& pair : _mapForNumber) SuffixMgr::Delete(pair.second);
	for (auto& pair : _mapForString) SuffixMgr::Delete(pair.second);
	for (auto& pair : _mapForBinary) SuffixMgr::Delete(pair.second);
	_mapForNumber.clear();
	_mapForString.clear();
	_mapForBinary.clear();
}

void SuffixMgrMap::Assign(SuffixMgr* pSuffixMgr)
{
	Map& map = GetMap(pSuffixMgr->GetMode());
	const Symbol* pSymbol = pSuffixMgr->GetSymbol();
	auto pPair = map.find(pSymbol);
	if (pPair == map.end()) {
		map.emplace(pSymbol, pSuffixMgr);
	} else {
		SuffixMgr::Delete(pPair->second);
		pPair->second = pSuffixMgr;
	}
}

SuffixMgr* SuffixMgrMap::Lookup(SuffixMgr::Mode mode, const Symbol* pSymbol) const
{
	const Map& map = GetMap(mode);
	auto pPair = map.find(pSymbol);
	return (pPair == map.end())? nullptr : pPair->second;
}

bool SuffixMgrMap::DoesExist(SuffixMgr::Mode mode, const Symbol* pSymbol) const
{
	const Map& map = GetMap(mode);
	return map.find(pSymbol) != map.end();
}

String SuffixMgrMap::ToString(const StringStyle& ss) const
{
	String str;
#if 0
	SymbolList keys = GetKeys().Sort();
	for (const Symbol* pSymbol : keys) {
		Value* pValue = Lookup(pSymbol);
		str += pSymbol->GetName();
		str += ":";
		str += pValue->GetVType().MakeFullName().c_str();
		str += " = ";
		str += pValue->ToString();
		str += "\n";
	}
#endif
	return str;
}

}
