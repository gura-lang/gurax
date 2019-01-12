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
	Symbol* pSymbol = reinterpret_cast<Symbol*>(MemoryPool::Global().Allocate(bytes, "Symbol"));
	pSymbol->Initialize(symbolPool.size(), name);
	symbolPool.insert(pSymbol);
	return pSymbol;
}

SymbolList Symbol::GetList()
{
	SymbolList symbolList;
	const SymbolPool& symbolPool = SymbolPool::GetInstance();
	symbolList.reserve(symbolPool.size());
	for (auto pSymbol : symbolPool) symbolList.push_back(pSymbol);
	std::sort(symbolList.begin(), symbolList.end(), Symbol::LessThan_Name());
	return symbolList;
}

void Symbol::PrintList()
{
	SymbolList symbolList = GetList();
	for (auto pSymbol : symbolList) {
		::printf("%08d %s\n", pSymbol->GetUniqId(), pSymbol->GetName());
	}
}

//------------------------------------------------------------------------------
// SymbolList
//------------------------------------------------------------------------------
SymbolList& SymbolList::Sort(SortOrder sortOrder)
{
	if (sortOrder == SortOrder::Ascend) {
		std::sort(begin(), end(), Symbol::LessThan_Name());
	} else if (sortOrder == SortOrder::Descend) {
		std::sort(begin(), end(), Symbol::GreaterThan_Name());
	}
	return *this;
}

//------------------------------------------------------------------------------
// SymbolSet
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SymbolPool
//------------------------------------------------------------------------------
SymbolPool* SymbolPool::_pSymbolPool = nullptr;

//------------------------------------------------------------------------------
// DottedSymbol
//------------------------------------------------------------------------------
// Compose from a list of Exprs.
bool DottedSymbol::ComposeFromExprList(const ExprList& exprList)
{
	_symbols.reserve(exprList.size());
	for (const Expr* pExpr : exprList) {
		if (!pExpr->IsType<Expr_Identifier>()) return false;
		_symbols.push_back(dynamic_cast<const Expr_Identifier*>(pExpr)->GetSymbol());
	}
	return true;
}

// Compose from a string.
bool DottedSymbol::ComposeFromString(const char* str)
{
	String field;
	for (const char* p = str; *p != '\0'; p++) {
		char ch = *p;
		if (ch == '.') {
			_symbols.push_back(Symbol::Add(field.c_str()));
			field.clear();
		} else {
			field += ch;
		}
	}
	if (!field.empty()) {
		_symbols.push_back(Symbol::Add(field.c_str()));
	}
	return true;
}

// Compose from Exprs that are chained by member operator ".".
bool DottedSymbol::ComposeFromExpr(const Expr* pExpr)
{
	for (;;) {
		if (pExpr->IsType<Expr_Member>()) {
			const Expr_Member* pExprMember = dynamic_cast<const Expr_Member*>(pExpr);
			if (!pExprMember->GetRight()->IsType<Expr_Identifier>()) return false;
			_symbols.insert(_symbols.begin(),
							dynamic_cast<const Expr_Identifier*>(pExprMember->GetRight())->GetSymbol());
			pExpr = pExprMember->GetLeft();
		} else if (pExpr->IsType<Expr_Identifier>()) {
			_symbols.insert(_symbols.begin(),
							dynamic_cast<const Expr_Identifier*>(pExpr)->GetSymbol());
			break;
		} else {
			return false;
		}
	}
	return true;
}

}
