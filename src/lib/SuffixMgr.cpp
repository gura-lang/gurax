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
	for (auto& pair : *this) SuffixMgr::Delete(pair.second);
	clear();
}

void SuffixMgrMap::Assign(SuffixMgr* pSuffixMgr)
{
	const Symbol* pSymbol = pSuffixMgr->GetSymbol();
	auto pPair = find(pSymbol);
	if (pPair == end()) {
		emplace(pSymbol, pSuffixMgr);
	} else {
		SuffixMgr::Delete(pPair->second);
		pPair->second = pSuffixMgr;
	}
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
