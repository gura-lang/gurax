//==============================================================================
// Attribute.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Attribute
//------------------------------------------------------------------------------
void Attribute::Bootup()
{
}

void Attribute::AddAttribute(const Attribute& attr)
{
	if (!IsDottedSymbolSet() && attr.IsDottedSymbolSet()) {
		SetDottedSymbol(attr.GetDottedSymbol().Reference());
	}
	AddSymbols(attr.GetSymbols());
	AddSymbolsOpt(attr.GetSymbolsOpt());
}

void Attribute::AddSymbol(const Symbol* pSymbol)
{
	_symbolList.push_back(pSymbol);
	_symbolSet.insert(pSymbol);
	if (!_pDottedSymbol) {
		_pDottedSymbol.reset(new DottedSymbol());
		_pDottedSymbol->Append(pSymbol);
	}
}

String Attribute::ToString(const StringStyle& ss) const
{
	String rtn;
	if (_pDottedSymbol && _pDottedSymbol->IsDotted()) {
		rtn += ':';
		rtn += _pDottedSymbol->ToString();
	}
	for (const Symbol* pSymbol : _symbolList) {
		rtn += ':';
		rtn += pSymbol->GetName();
	}
	if (!_symbolListOpt.empty()) {
		rtn += ":[";
		bool firstFlag = true;
		for (const Symbol* pSymbol : _symbolListOpt) {
			if (firstFlag) {
				firstFlag = false;
			} else {
				rtn += ',';
			}
			rtn += pSymbol->GetName();
		}
		rtn += ']';
	}
	return rtn;
}

}
