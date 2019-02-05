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
f(a:number, b:string, c:array)
f(a:map, b:nomap, c:nil, d:r, e:w)
f(a:map:nomap:nil:r:w)
f():map:attr1:[a,b]
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
		//::printf("%s .. %s\n", pExpr->ToString().c_str(), pExprEx->GetAttr().ToString().c_str());
		::printf("%s .. %s\n", pExpr->ToString().c_str(),
				 pExprEx->GetDeclaration().ToString(StringStyle().Verbose()).c_str());
	}
}

}
