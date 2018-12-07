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
	if (ppSymbol != _pSymbolPool->end()) return *ppSymbol;
	size_t bytes = sizeof(Symbol) + ::strlen(name) + 1;
	::printf("bytes = %zu, %zu\n", sizeof(Symbol), bytes);
	Symbol* pSymbol = reinterpret_cast<Symbol*>(MemoryPool::Allocate(bytes));
	pSymbol->_uniqId = _pSymbolPool->size();
	pSymbol->_name = pSymbol->_nameBuff;
	::strcpy(pSymbol->_nameBuff, name);
	_pSymbolPool->insert(pSymbol);
	return pSymbol;
}

}
