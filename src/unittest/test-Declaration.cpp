//==============================================================================
// test-Declaration.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {
//f()
//f(a)
//f(a,b,c)

static const char* src = R"(
f(a:number)
)";

Gurax_TesterEntry(Declaration)
{
	RefPtr<Expr_Root> pExprRoot = Parser::ParseString(src);
	if (Error::IsIssued()) {
		Error::Print(stderr);
		return;
	}
	for (const Expr* pExpr = pExprRoot->GetExprElemHead(); pExpr; pExpr = pExpr->GetExprNext()) {
		const Expr_Caller* pExprEx = dynamic_cast<const Expr_Caller*>(pExpr);
		//::printf("%s\n", pExpr->ToString().c_str());
		::printf("%s .. %s\n", pExpr->ToString().c_str(),
				 pExprEx->GetDeclaration().ToString().c_str());
	}
}

}
