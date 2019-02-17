//==============================================================================
// Property.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Property
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PropertyMap
//------------------------------------------------------------------------------
void PropertyMap::Clear()
{
	for (auto& pair : *this) Property::Delete(pair.second);
	clear();
}

void PropertyMap::Assign(const Symbol* pSymbol, Property* pProperty)
{
	iterator pPair = find(pSymbol);
	if (pPair == end()) {
		emplace(pSymbol, pProperty);
	} else {
		Property::Delete(pPair->second);
		pPair->second = pProperty;
	}
}

String PropertyMap::ToString(const StringStyle& ss) const
{
	String str;
#if 0
	SymbolList keys = GetKeys().Sort();
	for (const Symbol* pSymbol : keys) {
		Property* pProperty = Lookup(pSymbol);
		str += pSymbol->GetName();
		str += ":";
		str += pProperty->GetVType().MakeFullName().c_str();
		str += " = ";
		str += pProperty->ToString();
		str += "\n";
	}
#endif
	return str;
}

}
