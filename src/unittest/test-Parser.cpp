//==============================================================================
// test-Parser.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//c = a + b
static const char* text = R"(
a:b.m.n:c:d
)";

Gurax_TesterEntry(Parser)
{
	RefPtr<Expr_Root> pExprRoot = Parser::ParseString(text);
	for (const Expr* pExpr : pExprRoot->GetExprsElem()) {
		::printf("%s\n", pExpr->ToString().c_str());
	}
}

}
