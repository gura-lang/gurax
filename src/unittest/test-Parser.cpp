//==============================================================================
// test-Parser.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static const char* src1 = R"(
123456
'foo'
b'\x12\x34\x56'
foo
+
*
?
-
123456S
'foo'S
)";

static const char* src2 = R"(
()
[]
{}
{|a| elem1, elem2, elem3}
~123456
-123456
!123456
+123456
`123456
%{}
%{elem1, elem2, elem3}
%{|a| elem1, elem2, elem3}
%{|a, b, c| elem1, elem2, elem3}
%%{}
%%{elem1, elem2, elem3}
%%{|a| elem1, elem2, elem3}
%%{|a, b, c| elem1, elem2, elem3}
&{}
&{elem1, elem2, elem3}
&{|a| elem1, elem2, elem3}
&{|a, b, c| elem1, elem2, elem3}
*foo
)";

static const char* src3 = R"(
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
	auto TestFunc = [](const char* src) {
		RefPtr<Expr_Root> pExprRoot = Parser::ParseString(src);
		for (const Expr* pExpr : pExprRoot->GetExprsElem()) {
			::printf("%s\n", pExpr->ToString().c_str());
		}
	};
	TestFunc(src1);
	TestFunc(src2);
}

}
