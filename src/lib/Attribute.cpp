//==============================================================================
// Attribute.cpp
//==============================================================================
#include "stdafx.h"

//#define DBGPARSER(x)
#define DBGPARSER(x) x

namespace Gurax {

//------------------------------------------------------------------------------
// Attribute
//------------------------------------------------------------------------------
void Attribute::Bootup()
{
}

void Attribute::AddAttribute(const Attribute& attribute)
{
	if (!IsDottedSymbolSet() && attribute.IsDottedSymbolSet()) {
		SetDottedSymbol(attribute.GetDottedSymbol().Reference());
	}
	AddSymbols(attribute.GetSymbols());
	AddSymbolsOpt(attribute.GetSymbolsOpt());
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
		rtn += '[';
		bool firstFlag = true;
		for (const Symbol* pSymbol : _symbolListOpt) {
			if (firstFlag) {
				rtn += ',';
				firstFlag = false;
			}
			rtn += pSymbol->GetName();
		}
		rtn += ']';
	}
	return rtn;
}

}
