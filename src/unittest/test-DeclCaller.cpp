//==============================================================================
// test-DeclCaller.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static const char* src = R"(
f()
f(v)
f(v1, v2, v3)
f(v:type)
f(v1:g1.type, v2:g1.g2.type, v3:g1.g2.g3.type)
f(v1:type, v2:string, v3:array)
f(v1:map, v2:nomap, v3:nil, v4:r, v5:w)
f(v:map:nomap:nil:r:w)
f():map:attr1:attr2:[a,b]
f(v[])
f(v[]:type)
f(v[]:type:map)
f(v?)
f(v+)
f(v*)
f(v?:type)
f(v+:type)
f(v*:type)
f(v?:g1.type)
f(v+:g1.type)
f(v*:g1.type)
f(v?:g1.b2.g3.type)
f(v+:g1.g2.g3.type)
f(v*:g1.g3.g3.type)
f(v?:type:map)
f(v+:type:map)
f(v*:type:map)
f(v?:g1.type:map)
f(v+:g1.type:map)
f(v*:g1.type:map)
f(v?:g1.b2.g3.type:map)
f(v+:g1.g2.g3.type:map)
f(v*:g1.g3.g3.type:map)
f(v[]?)
f(v[]+)
f(v[]*)
f(v[]?:type)
f(v[]+:type)
f(v[]*:type)
f(v[]?:g1.type)
f(v[]+:g1.type)
f(v[]*:g1.type)
f(v[]?:g1.b2.g3.type)
f(v[]+:g1.g2.g3.type)
f(v[]*:g1.g3.g3.type)
)";

Gurax_TesterEntry(DeclCaller)
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
				 pExprEx->GetDeclCaller().ToString(StringStyle().Verbose()).c_str());
	}
}

}
