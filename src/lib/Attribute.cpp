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
