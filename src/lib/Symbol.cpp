//==============================================================================
// Symbol.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Symbol
//------------------------------------------------------------------------------
static_assert(std::is_pod<Symbol>::value, "Gurax::Symbol must be a POD class");

const Symbol* Symbol::Empty = nullptr;

void Symbol::Bootup()
{
	Empty = Add("");
}

bool Symbol::IsIdentical(const Expr& expr) const
{
	if (!expr.IsType<Expr_Identifier>()) return false;
	const Expr_Identifier& exprEx = dynamic_cast<const Expr_Identifier&>(expr);
	return IsIdentical(exprEx.GetSymbol());
}

String Symbol::ToString(const StringStyle& ss) const
{
	String str;
	if (ss.IsAsSource()) str += '`';
	str += GetName();
	return str;
}

bool Symbol::IsFlowControl() const
{
	static SymbolSet *pSymbolSet = nullptr;
	if (!pSymbolSet) {
		pSymbolSet = new SymbolSet();
		pSymbolSet->Set(Gurax_Symbol(if_));
		pSymbolSet->Set(Gurax_Symbol(elsif));
		pSymbolSet->Set(Gurax_Symbol(repeat));
		pSymbolSet->Set(Gurax_Symbol(while_));
		pSymbolSet->Set(Gurax_Symbol(for_));
		pSymbolSet->Set(Gurax_Symbol(cross));
	}
	return pSymbolSet->IsSet(this);
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
	//Symbol* pSymbol = reinterpret_cast<Symbol*>(MemoryPool::Global().Allocate(bytes, "Symbol"));
	Symbol* pSymbol = reinterpret_cast<Symbol*>(::malloc(bytes));
	pSymbol->Initialize(symbolPool.size(), name);
	symbolPool.insert(pSymbol);
	return pSymbol;
}

SymbolList Symbol::GetAllSymbols()
{
	const SymbolPool& symbolPool = SymbolPool::GetInstance();
	SymbolList symbolList;
	std::copy(symbolPool.begin(), symbolPool.end(), std::back_inserter(symbolList));
	symbolList.Sort();
	return symbolList;
}

void Symbol::PrintAllSymbols()
{
	Stream& stream = *Stream::COut;
	SymbolList symbolList = GetAllSymbols();
	for (auto pSymbol : symbolList) {
		stream.Printf("%08d %s\n", pSymbol->GetUniqId(), pSymbol->GetName());
	}
}

//------------------------------------------------------------------------------
// SymbolList
//------------------------------------------------------------------------------
const SymbolList SymbolList::Empty;

bool SymbolList::AddFromExprList(const ExprList& exprList)
{
	for (const Expr* pExpr : exprList) {
		if (!pExpr->IsType<Expr_Identifier>()) {
			return false;
		}
		push_back(dynamic_cast<const Expr_Identifier*>(pExpr)->GetSymbol());
	}
	return true;
}

bool SymbolList::AddFromExprLink(const ExprLink& exprLink)
{
	for (const Expr* pExpr = exprLink.GetExprFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
		if (!pExpr->IsType<Expr_Identifier>()) {
			return false;
		}
		push_back(dynamic_cast<const Expr_Identifier*>(pExpr)->GetSymbol());
	}
	return true;
}

SymbolList& SymbolList::Sort(SortOrder sortOrder)
{
	if (sortOrder == SortOrder::Ascend) {
		std::sort(begin(), end(), Symbol::LessThan_Name());
	} else if (sortOrder == SortOrder::Descend) {
		std::sort(begin(), end(), Symbol::GreaterThan_Name());
	}
	return *this;
}

bool SymbolList::IsEqualTo(const SymbolList& symbolList) const
{
	return std::equal(begin(), end(), symbolList.begin(), symbolList.end(), Symbol::EqualTo_UniqId());
}

String SymbolList::ToString(const StringStyle& ss) const
{
	String str;
	for (const Symbol* pSymbol : *this) {
		if (!str.empty()) str += ss.GetComma();
		str += pSymbol->ToString(ss);
	}
	return str;
}

//------------------------------------------------------------------------------
// SymbolSet
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SymbolPool
//------------------------------------------------------------------------------
SymbolPool* SymbolPool::_pSymbolPool = nullptr;

}
