//==============================================================================
// Symbol.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Symbol
//------------------------------------------------------------------------------
SymbolSet *Symbol::_pSymbolPool = nullptr;

void Symbol::Bootup()
{
	_pSymbolPool = new SymbolSet();
}

const Symbol* Symbol::Add(const char* name)
{
	Symbol symbol(0, const_cast<char *>(name));
	auto ppSymbol = _pSymbolPool->find(&symbol);
	if (ppSymbol == _pSymbolPool->end()) return *ppSymbol;
	char* nameStored = reinterpret_cast<char*>(MemoryPool::Allocate(::strlen(name) + 1));
	::strcpy(nameStored, name);
	Symbol* pSymbol = new Symbol(_pSymbolPool->size(), nameStored);
	_pSymbolPool->insert(pSymbol);
	return pSymbol;
}

}
