//==============================================================================
// test-DeclCaller.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static const char* srcTbl[] = {
	"f(a:[]) = {}"
	"f() = {}",
	"f(`v) = {}",
	"f(v) = {}",
	"f(v1, v2, v3) = {}",
	"f(v:type) = {}",
	"f(v1:g1.type, v2:g1.g2.type, v3:g1.g2.g3.type) = {}",
	"f(v1:type, v2:string, v3:array) = {}",
	"f(v1:map, v2:nomap, v3:nil, v4:r, v5:w) = {}",
	"f(v:map:nomap:nil:r:w) = {}",
	"f():map:attr1:attr2:[a,b] = {}",
	"f(v[]) = {}",
	"f(v[]:type) = {}",
	"f(v[]:type:map:w) = {}",
	"f(v?) = {}",
	"f(v+) = {}",
	"f(v*) = {}",
	"f(v?:type) = {}",
	"f(v+:type) = {}",
	"f(v*:type) = {}",
	"f(v?:g1.type) = {}",
	"f(v+:g1.type) = {}",
	"f(v*:g1.type) = {}",
	"f(v?:g1.b2.g3.type) = {}",
	"f(v+:g1.g2.g3.type) = {}",
	"f(v*:g1.g3.g3.type) = {}",
	"f(v?:type:map:w) = {}",
	"f(v+:type:map:w) = {}",
	"f(v*:type:map:w) = {}",
	"f(v?:g1.type:map:w) = {}",
	"f(v+:g1.type:map:w) = {}",
	"f(v*:g1.type:map:w) = {}",
	"f(v?:g1.b2.g3.type:map:w) = {}",
	"f(v+:g1.g2.g3.type:map:w) = {}",
	"f(v*:g1.g3.g3.type:map:w) = {}",
	"f(v[]?) = {}",
	"f(v[]+) = {}",
	"f(v[]*) = {}",
	"f(v[]?:type) = {}",
	"f(v[]+:type) = {}",
	"f(v[]*:type) = {}",
	"f(v[]?:g1.type) = {}",
	"f(v[]+:g1.type) = {}",
	"f(v[]*:g1.type) = {}",
	"f(v[]?:g1.b2.g3.type) = {}",
	"f(v[]+:g1.g2.g3.type) = {}",
	"f(v[]*:g1.g3.g3.type) = {}",
	"f(v[]?:type:map:w) = {}",
	"f(v[]+:type:map:w) = {}",
	"f(v[]*:type:map:w) = {}",
	"f(v[]?:g1.type:map:w) = {}",
	"f(v[]+:g1.type:map:w) = {}",
	"f(v[]*:g1.type:map:w) = {}",
	"f(v[]?:g1.b2.g3.type:map:w) = {}",
	"f(v[]+:g1.g2.g3.type:map:w) = {}",
	"f(v[]*:g1.g3.g3.type:map:w) = {}",
};

Gurax_TesterEntry(DeclCaller)
{
	for (const char* src : srcTbl) {
		::printf("%s .. ", src);
		RefPtr<Expr_Root> pExprRoot = Parser::ParseString(src);
		if (Error::IsIssued()) {
			::printf("error: %s\n", Error::GetLastError()->GetText());
			Error::Clear();
			continue;
		}
		const Expr* pExpr = pExprRoot->GetExprElemHead();
		if (pExpr->IsType<Expr_Assign>()) {
			const Expr_Assign* pExprEx = dynamic_cast<const Expr_Assign*>(pExpr);
			const Expr* pExpr = pExprEx->GetExprLeft();
			if (pExpr->IsType<Expr_Caller>()) {
				const Expr_Caller* pExprEx = dynamic_cast<const Expr_Caller*>(pExpr);
				::printf("%s\n", pExprEx->GetDeclCaller().ToString(StringStyle().Verbose()).c_str());
			}
		}
	}
}

}
