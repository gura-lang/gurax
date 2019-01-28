//==============================================================================
// test-Parser.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static const char* text = R"(
123456
'foo'
b'\x12\x34\x56'
a
a + b
a:b.m.n:c:d
f[]
f[a]
f[a, b, c, d, e]
f()
f(a)
f(a, b, c, d, e)
)";

Gurax_TesterEntry(Parser)
{
	RefPtr<Expr_Root> pExprRoot = Parser::ParseString(text);
	for (const Expr* pExpr : pExprRoot->GetExprsElem()) {
		::printf("%s\n", pExpr->ToString().c_str());
	}
}

}
