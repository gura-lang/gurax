//==============================================================================
// DeclProp.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DeclProp
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// DeclPropMap
//------------------------------------------------------------------------------
void DeclPropMap::Clear()
{
	for (auto& pair : *this) DeclProp::Delete(pair.second);
	clear();
}

void DeclPropMap::Assign(const Symbol* pSymbol, DeclProp* pDeclProp)
{
	iterator pPair = find(pSymbol);
	if (pPair == end()) {
		emplace(pSymbol, pDeclProp);
	} else {
		DeclProp::Delete(pPair->second);
		pPair->second = pDeclProp;
	}
}

String DeclPropMap::ToString(const StringStyle& ss) const
{
	String str;
#if 0
	SymbolList keys = GetKeys().Sort();
	for (const Symbol* pSymbol : keys) {
		DeclProp* pDeclProp = Lookup(pSymbol);
		str += pSymbol->GetName();
		str += ":";
		str += pDeclProp->GetVType().MakeFullName().c_str();
		str += " = ";
		str += pDeclProp->ToString();
		str += "\n";
	}
#endif
	return str;
}

}
