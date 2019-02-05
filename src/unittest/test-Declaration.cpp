//==============================================================================
// test-Declaration.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static const char* src = R"(
f()
f(a)
f(a, b, c)
f(a:number)
f(a:g1.type, b:g1.g2.type, c:g1.g2.g3.type)
f(a:number, b:string, c:array)
f(a:map, b:nomap, c:nil, d:r, e:w)
f(a:map:nomap:nil:r:w)
f():map:attr1:attr2:[a,b]
f(a[])
f(a[]:number)
f(a[]:number:map)
f(a?)
f(a+)
f(c*)
f(a?:number)
f(b+:number)
f(c*:number)
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
