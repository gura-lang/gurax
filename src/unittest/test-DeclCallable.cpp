//==============================================================================
// test-DeclCallable.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static const char* srcTbl[] = {
	"f(a:[]) = {}"
	"f() = {}",
	"f(`v) = {}",
	"f(v) = {}",
	"f(v1, v2, v3) = {}",
	"f(v:Type) = {}",
	"f(v1:g1.Type, v2:g1.g2.Type, v3:g1.g2.g3.Type) = {}",
	"f(v1:Type, v2:String, v3:Array) = {}",
	"f(v1:map, v2:nomap, v3:nil, v4:r, v5:w) = {}",
	"f(v:map:nomap:nil:r:w) = {}",
	"f():map:attr1:attr2:[a,b] = {}",
	"f(v[]) = {}",
	"f(v[]:Type) = {}",
	"f(v[]:Type:map:w) = {}",
	"f(v?) = {}",
	"f(v+) = {}",
	"f(v*) = {}",
	"f(v?:Type) = {}",
	"f(v+:Type) = {}",
	"f(v*:Type) = {}",
	"f(v?:g1.Type) = {}",
	"f(v+:g1.Type) = {}",
	"f(v*:g1.Type) = {}",
	"f(v?:g1.b2.g3.Type) = {}",
	"f(v+:g1.g2.g3.Type) = {}",
	"f(v*:g1.g3.g3.Type) = {}",
	"f(v?:Type:map:w) = {}",
	"f(v+:Type:map:w) = {}",
	"f(v*:Type:map:w) = {}",
	"f(v?:g1.Type:map:w) = {}",
	"f(v+:g1.Type:map:w) = {}",
	"f(v*:g1.Type:map:w) = {}",
	"f(v?:g1.b2.g3.Type:map:w) = {}",
	"f(v+:g1.g2.g3.Type:map:w) = {}",
	"f(v*:g1.g3.g3.Type:map:w) = {}",
	"f(v[]?) = {}",
	"f(v[]+) = {}",
	"f(v[]*) = {}",
	"f(v[]?:Type) = {}",
	"f(v[]+:Type) = {}",
	"f(v[]*:Type) = {}",
	"f(v[]?:g1.Type) = {}",
	"f(v[]+:g1.Type) = {}",
	"f(v[]*:g1.Type) = {}",
	"f(v[]?:g1.b2.g3.Type) = {}",
	"f(v[]+:g1.g2.g3.Type) = {}",
	"f(v[]*:g1.g3.g3.Type) = {}",
	"f(v[]?:Type:map:w) = {}",
	"f(v[]+:Type:map:w) = {}",
	"f(v[]*:Type:map:w) = {}",
	"f(v[]?:g1.Type:map:w) = {}",
	"f(v[]+:g1.Type:map:w) = {}",
	"f(v[]*:g1.Type:map:w) = {}",
	"f(v[]?:g1.b2.g3.Type:map:w) = {}",
	"f(v[]+:g1.g2.g3.Type:map:w) = {}",
	"f(v[]*:g1.g3.g3.Type:map:w) = {}",
	"f() {block} = {}",
	"f() {`block} = {}",
	"f() {block?} = {}",
	"f() {`block?} = {}",
	"f() {foo} = {}",
	"f() {`foo} = {}",
	"f() {foo?} = {}",
	"f() {`foo?} = {}",
	"f() {foo+} = {}",
	"f() {foo*} = {}",
	"f() {foo, bar} = {}",
	"f() {|a| block} = {}",
	"f() {foo + bar} = {}",
	"f() {'hello'} = {}",
	"f(v1:Type1, v2:Type2) {block} = {}",
	"f(v1:Type1, v2:Type2) {`block} = {}",
	"f(v1:Type1, v2:Type2) {block?} = {}",
	"f(v1:Type1, v2:Type2) {`block?} = {}",
	"f(v1:Type1, v2:Type2) {foo} = {}",
	"f(v1:Type1, v2:Type2) {`foo} = {}",
	"f(v1:Type1, v2:Type2) {foo?} = {}",
	"f(v1:Type1, v2:Type2) {`foo?} = {}",
	"f(v1:Type1, v2:Type2):map:attr1:attr2 {block} = {}",
	"f(v1:Type1, v2:Type2):map:attr1:attr2 {`block} = {}",
	"f(v1:Type1, v2:Type2):map:attr1:attr2 {block?} = {}",
	"f(v1:Type1, v2:Type2):map:attr1:attr2 {`block?} = {}",
	"f(v1:Type1, v2:Type2):map:attr1:attr2 {foo} = {}",
	"f(v1:Type1, v2:Type2):map:attr1:attr2 {`foo} = {}",
	"f(v1:Type1, v2:Type2):map:attr1:attr2 {foo?} = {}",
	"f(v1:Type1, v2:Type2):map:attr1:attr2 {`foo?} = {}",
};

Gurax_TesterEntry(DeclCallable)
{
	for (const char* src : srcTbl) {
		::printf("%s .. ", src);
		RefPtr<Expr_Root> pExprRoot(Parser::ParseString(src));
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
				::printf("%s\n", pExprEx->GetDeclCallable().ToString(StringStyle().Verbose()).c_str());
			}
		}
	}
}

}
