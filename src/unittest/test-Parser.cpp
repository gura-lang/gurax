//==============================================================================
// test-Parser.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static const char* src_ReduceOneToken = R"(
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

static const char* src_ReduceTwoTokens = R"(
()
[]
{}
{|a| elem1, elem2, elem3}
~123456
-123456
!123456
+123456
`123456
*123456
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
123456+
123456*
123456?
123456%
123456..
)";

static const char* src_ReduceThreeTokens = R"(
a + b
a - b
a * b
a / b
a % b
a %% b
a |.| b
a |^| b
a |*| b
a |+| b
a |-| b
a |&| b
a ||| b
a ** b
a == b
a != b
a < b
a > b
a <= b
a >= b
a <=> b
a in b
a => b
a || b
a && b
a | b
a & b
a ^ b
a <<  b
a >>  b
a ..  b
a = b
a += b
a -= b
a *= b
a /= b
a %= b
a **= b
a |= b
a &= b
a ^= b
a <<= b
a >>= b
a.b
a::b
a:*b
a:&b
a:b
a:b:c:d
a:b.c.d:e:f
a:[b,c,d]
a:[b,c,d]:e:f:g
a:e:f:g:[b,c,d]
a:e:f:g:[b,c,d]:[h,i,k]
()
(a)
((a))
(((a)))
(a,)
(a,b,c)
[]
[a]
[a,b,c]
f()
f(a)
f(a, b, c)
f() {}
f(a) {}
f(a, b, c) {}
f() {
}
f(a) {
}
f(a, b, c) {
}
f {}
f {elem1, elem2, elem3}
f {|a| elem1, elem2, elem3}
f {|a, b, c| elem1, elem2, elem3}
f() {}
f() {elem1, elem2, elem3}
f() {|a| elem1, elem2, elem3}
f() {|a, b, c| elem1, elem2, elem3}
f(a, b, c) {}
f(a, b, c) {elem1, elem2, elem3}
f(a, b, c) {
elem1
elem2
elem3}
f(a, b, c) {|| elem1, elem2, elem3}
f(a, b, c) {|a| elem1, elem2, elem3}
f(a, b, c) {|a|
elem1
elem2
elem3}
f(a, b, c) {|a, b, c| elem1, elem2, elem3}
f(a, b, c) {|a
b
c| elem1, elem2, elem3}
f[]
f[elem1]
f[elem1, elem2, elem3]
f[
]
f[
  elem1
]
f[
  elem1
  elem2
  elem3
]
)";

static const char* src_ReduceFourTokens = R"(
f() g()
f(a, b, c) g()
)";
/*
f(a, b, c) g(a, b, c)
f(a, b, c) {elem1, elem2} g(a, b, c) {}
f(a, b, c) {elem1, elem2} g(a, b, c) {elem1, elem2}
*/

static const char* src_ReduceFiveTokens = R"(
)";

Gurax_TesterEntry(Parser)
{
	auto TestFunc = [](const char* src) {
		Error::Clear();
		RefPtr<Expr_Root> pExprRoot = Parser::ParseString(src);
		if (Error::IsIssued()) {
			Error::Print(stderr);
			return;
		}
		for (const Expr* pExpr : pExprRoot->GetExprsElem()) {
			::printf("%s\n", pExpr->ToString().c_str());
		}
	};
	PrintTitle("ReduceOneToken");
	TestFunc(src_ReduceOneToken);
	PrintTitle("ReduceTwoTokens");
	TestFunc(src_ReduceTwoTokens);
	PrintTitle("ReduceThreeTokens");
	TestFunc(src_ReduceThreeTokens);
	PrintTitle("ReduceFourTokens");
	TestFunc(src_ReduceFourTokens);
	PrintTitle("ReduceFiveTokens");
	TestFunc(src_ReduceFiveTokens);
}

}
