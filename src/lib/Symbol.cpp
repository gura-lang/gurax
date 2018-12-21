//==============================================================================
// Symbol.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Symbol
//------------------------------------------------------------------------------
static_assert(std::is_pod<Symbol>::value, "Gurax::Symbol must be a POD class");

void Symbol::Bootup()
{
}

const Symbol* Symbol::Add(const char* name)
{
	SymbolPool& symbolPool = SymbolPool::GetInstance();
	do {
		Symbol symbol(0, const_cast<char *>(name));
		auto ppSymbol = symbolPool.find(&symbol);
		if (ppSymbol != symbolPool.end()) return *ppSymbol;
	} while (0);
	size_t bytes = sizeof(Symbol) + ::strlen(name) + 1;
	Symbol* pSymbol = reinterpret_cast<Symbol*>(MemoryPool::Allocate(bytes));
	pSymbol->Initialize(symbolPool.size(), name);
	symbolPool.insert(pSymbol);
	return pSymbol;
}

SymbolList Symbol::GetList()
{
	const SymbolPool& symbolPool = SymbolPool::GetInstance();
	SymbolList symbolList;
	symbolList.reserve(symbolPool.size());
	for (auto pSymbol : symbolPool) symbolList.push_back(pSymbol);
	std::sort(symbolList.begin(), symbolList.end(), Symbol::LessThan_Name());
	return symbolList;
}

void Symbol::PrintList()
{
	SymbolList symbolList = GetList();
	for (auto pSymbol : symbolList) {
		::printf("%08zu %s\n", pSymbol->GetUniqId(), pSymbol->GetName());
	}
}

//------------------------------------------------------------------------------
// SymbolSet
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SymbolPool
//------------------------------------------------------------------------------
SymbolPool* SymbolPool::_pSymbolPool = nullptr;

}
