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

}
