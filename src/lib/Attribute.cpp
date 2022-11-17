//==============================================================================
// Attribute.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Attribute
//------------------------------------------------------------------------------
const Attribute* Attribute::Empty;

void Attribute::Bootup()
{
	Empty = new Attribute();
}

void Attribute::AddAttribute(const Attribute& attr)
{
	AddSymbols(attr.GetSymbols());
	AddSymbolsOpt(attr.GetSymbolsOpt());
}

void Attribute::AddSymbol(const Symbol* pSymbol)
{
	_symbolList.push_back(pSymbol);
	_symbolSet.GetSet().insert(pSymbol);
}

String Attribute::ToString(const StringStyle& ss) const
{
	String str;
	for (const Symbol* pSymbol : _symbolList) {
		str += ':';
		str += pSymbol->GetName();
	}
	if (!_symbolListOpt.empty()) {
		str += ":[";
		bool firstFlag = true;
		for (const Symbol* pSymbol : _symbolListOpt) {
			if (firstFlag) {
				firstFlag = false;
			} else {
				str += ',';
			}
			str += pSymbol->GetName();
		}
		str += ']';
	}
	return str;
}

}
