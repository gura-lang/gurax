//==============================================================================
// ValueMap.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ValueMap
//------------------------------------------------------------------------------
void ValueMap::Clear()
{
	for (auto& pair : *this) Value::Delete(pair.second);
	clear();
}

void ValueMap::Assign(const Symbol* pSymbol, Value* pValue)
{
	auto pPair = find(pSymbol);
	if (pPair == end()) {
		emplace(pSymbol, pValue);
	} else {
		Value::Delete(pPair->second);
		pPair->second = pValue;
	}
}

String ValueMap::ToString(const StringStyle& ss) const
{
	String str;
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
	return str;
}

}
