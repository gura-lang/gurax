//==============================================================================
// test-Symbol.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_RealizeSymbol(hoge);

Gurax_TesterEntry(Symbol)
{
	auto Sym_foo1 = Symbol::Add("foo");
	auto Sym_foo2 = Symbol::Add("foo");
	auto Sym_foo3 = Symbol::Add("foo");
	::printf("%d %d %d\n", Sym_foo1->GetUniqId(), Sym_foo2->GetUniqId(), Sym_foo3->GetUniqId());
	::printf("%d\n", Sym_foo1->IsIdentical(Sym_foo2));
	Symbol::PrintAllSymbols();
	SymbolList symbolList1 { Gurax_Symbol(a), Gurax_Symbol(b), Gurax_Symbol(c) };
	SymbolList symbolList2 { Gurax_Symbol(a), Gurax_Symbol(b), Gurax_Symbol(c) };
	SymbolList symbolList3 { Gurax_Symbol(a), Gurax_Symbol(b), Gurax_Symbol(c), Gurax_Symbol(d), Gurax_Symbol(e), Gurax_Symbol(f) };
	SymbolList symbolList4 { Gurax_Symbol(b), Gurax_Symbol(c), Gurax_Symbol(d) };
	auto func = [](const SymbolList& symbolList1, const SymbolList& symbolList2) {
		::printf("[%s] == [%s]  .. %s\n", symbolList1.ToString().c_str(), symbolList2.ToString().c_str(),
				 symbolList1.IsEqualTo(symbolList2)? "true" : "false");
	};
	func(symbolList1, symbolList2);
	func(symbolList1, symbolList3);
	func(symbolList3, symbolList1);
	func(symbolList1, symbolList4);
}

}
