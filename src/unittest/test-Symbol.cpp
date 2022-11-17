//==============================================================================
// test-Symbol.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_RealizeSymbol(hoge);

void Test_PrintAllSymbols()
{
	Symbol::PrintAllSymbols();
}

void Test_Add()
{
	const Symbol* Sym_foo1 = Symbol::Add("foo");
	const Symbol* Sym_foo2 = Symbol::Add("foo");
	const Symbol* Sym_foo3 = Symbol::Add("foo");
	::printf("%d\n", Sym_foo1->IsIdentical(Sym_foo2));
	::printf("%d\n", Sym_foo1->IsIdentical(Sym_foo3));
}

void Test_SymbolList()
{
	SymbolList symbolList1 { Gurax_Symbol(a), Gurax_Symbol(b), Gurax_Symbol(c) };
	SymbolList symbolList2 { Gurax_Symbol(a), Gurax_Symbol(b), Gurax_Symbol(c) };
	SymbolList symbolList3 { Gurax_Symbol(a), Gurax_Symbol(b), Gurax_Symbol(c), Gurax_Symbol(d), Gurax_Symbol(e), Gurax_Symbol(f) };
	SymbolList symbolList4 { Gurax_Symbol(b), Gurax_Symbol(c), Gurax_Symbol(d) };
	auto TestFunc = [](const SymbolList& symbolList1, const SymbolList& symbolList2) {
		::printf("[%s] == [%s]  .. %s\n", symbolList1.ToString().c_str(), symbolList2.ToString().c_str(),
				 symbolList1.IsEqualTo(symbolList2)? "true" : "false");
	};
	TestFunc(symbolList1, symbolList2);
	TestFunc(symbolList1, symbolList3);
	TestFunc(symbolList3, symbolList1);
	TestFunc(symbolList1, symbolList4);
}

void Test_DottedSymbol_IsEqualTo()
{
	RefPtr<DottedSymbol> pDottedSymbol1 = new DottedSymbol(Gurax_Symbol(a), Gurax_Symbol(b), Gurax_Symbol(c));
	RefPtr<DottedSymbol> pDottedSymbol2 = new DottedSymbol(Gurax_Symbol(a), Gurax_Symbol(b), Gurax_Symbol(c));
	RefPtr<DottedSymbol> pDottedSymbol3 = new DottedSymbol(Gurax_Symbol(a), Gurax_Symbol(b), Gurax_Symbol(c), Gurax_Symbol(d), Gurax_Symbol(e), Gurax_Symbol(f));
	RefPtr<DottedSymbol> pDottedSymbol4 = new DottedSymbol(Gurax_Symbol(b), Gurax_Symbol(c), Gurax_Symbol(d));
	auto TestFunc = [](const DottedSymbol& dottedSymbol1, const DottedSymbol& dottedSymbol2) {
		::printf("%s == %s  .. %s\n", dottedSymbol1.ToString().c_str(), dottedSymbol2.ToString().c_str(),
				 dottedSymbol1.IsEqualTo(dottedSymbol2)? "true" : "false");
	};
	TestFunc(*pDottedSymbol1, *pDottedSymbol2);
	TestFunc(*pDottedSymbol1, *pDottedSymbol3);
	TestFunc(*pDottedSymbol3, *pDottedSymbol1);
	TestFunc(*pDottedSymbol1, *pDottedSymbol4);
}

void Test_DottedSymbol_AppendFromString()
{
	const char* strs[] = {
		"aaaa",
		"aaaa.bbbb",
		"aaaa.bbbb.cccc",
		"aaaa.bbbb.cccc.dddd",
		"aaaa..bbbb",
		"0aaa",
		"aaaa.0bbb",
		"aaa+",
		"+aaa",
		"aaaa.+bbb",
		"aaaa.bbb+",
	};
	for (const char* str : strs) {
		RefPtr<DottedSymbol> pDottedSymbol = new DottedSymbol();
		if (pDottedSymbol->AppendFromString(str)) {
			::printf("\"%s\" -> %s\n", str, pDottedSymbol->ToString().c_str());
		} else {
			::printf("\"%s\" -> ** error **\n", str);
		}
	}
}

Gurax_TesterEntry(Symbol)
{
	//Test_PrintAllSymbols();
	Test_Add();
	Test_SymbolList();
	Test_DottedSymbol_IsEqualTo();
	Test_DottedSymbol_AppendFromString();
}

}
