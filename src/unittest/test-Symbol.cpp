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
	Symbol::PrintList();
}

}
