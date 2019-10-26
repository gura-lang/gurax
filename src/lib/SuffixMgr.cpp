//==============================================================================
// SuffixMgr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// SuffixMgr
//------------------------------------------------------------------------------
String SuffixMgr::ToString(const StringStyle& ss) const
{
	return "";
}

//------------------------------------------------------------------------------
// SuffixMgrMap
//------------------------------------------------------------------------------
void SuffixMgrMap::Clear()
{
	for (auto& pair : _mapForNumber) SuffixMgr::Delete(pair.second);
	for (auto& pair : _mapForString) SuffixMgr::Delete(pair.second);
	_mapForNumber.clear();
	_mapForString.clear();
}

void SuffixMgrMap::Assign(SuffixMgr* pSuffixMgr)
{
	Map& map = GetMap(pSuffixMgr->GetTarget());
	const Symbol* pSymbol = pSuffixMgr->GetSymbol();
	auto pPair = map.find(pSymbol);
	if (pPair == map.end()) {
		map.emplace(pSymbol, pSuffixMgr);
	} else {
		SuffixMgr::Delete(pPair->second);
		pPair->second = pSuffixMgr;
	}
}

SuffixMgr* SuffixMgrMap::Lookup(SuffixMgr::Target target, const Symbol* pSymbol) const
{
	const Map& map = GetMap(target);
	auto pPair = map.find(pSymbol);
	return (pPair == map.end())? nullptr : pPair->second;
}

bool SuffixMgrMap::DoesExist(SuffixMgr::Target target, const Symbol* pSymbol) const
{
	const Map& map = GetMap(target);
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
