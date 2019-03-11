//==============================================================================
// test-Parser.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static const char* src_ReduceOneToken = R"(
123456
'foo'
b'\x12\x34\x56'
e'<html></html>'
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

static const char* src_ReduceFourAndFiveTokens = R"(
f() g()
f() g() h() k() l() m()
f() g(a)
f() g(a, b, c)
f(a, b, c) g()
f(a, b, c) g(a, b, c)
f(a, b, c) {elem1, elem2} g(a, b, c) {}
f(a, b, c) {elem1, elem2} g(a, b, c) {elem1, elem2}
f(a, b, c) {|a, b, c| elem1, elem2, elem3} g(a, b, c) {|a, b, c| elem1, elem2, elem3}
f(a, b, c) {|a, b, c|
  elem1, elem2, elem3
} g(a, b, c) {|a, b, c|
  elem1, elem2, elem3
} h(a, b, c) {|a, b, c|
  elem1, elem2, elem3
} k(a, b, c) {|a, b, c|
  elem1, elem2, elem3
}
if (a == b) {foo}
f(a:number, b:string, c:symbol) = {}
)";

static const char* src_Attribute = R"(
a:b
a:b:c:d
a:b.c.d:e:f
a:[b,c,d]
a:[b,c,d]:e:f:g
a:e:f:g:[b,c,d]
a:e:f:g:[b,c,d]:[h,i,k]
f(elem1,elem2,elem3):b
f(elem1,elem2,elem3):b:c:d
f(elem1,elem2,elem3):b.c.d:e:f
f(elem1,elem2,elem3):[b,c,d]
f(elem1,elem2,elem3):[b,c,d]:e:f:g
f(elem1,elem2,elem3):e:f:g:[b,c,d]
f(elem1,elem2,elem3):e:f:g:[b,c,d]:[h,i,k]
f:B(elem1,elem2,elem3):b
f:B:C:D(elem1,elem2,elem3):b:c:d
f:B.C.D:E:F(elem1,elem2,elem3):b.c.d:e:f
f:[B,C,D](elem1,elem2,elem3):[b,c,d]
f:[B,C,D]:E:F:G(elem1,elem2,elem3):[b,c,d]:e:f:g
f:E:F:G:[B,C,D](elem1,elem2,elem3):e:f:g:[b,c,d]
f:E:F:G:[B,C,D]:[H,I,K](elem1,elem2,elem3):e:f:g:[b,c,d]:[h,i,k]
v[elem1,elem2,elem3]:b
v[elem1,elem2,elem3]:b:c:d
v[elem1,elem2,elem3]:b.c.d:e:f
v[elem1,elem2,elem3]:[b,c,d]
v[elem1,elem2,elem3]:[b,c,d]:e:f:g
v[elem1,elem2,elem3]:e:f:g:[b,c,d]
v[elem1,elem2,elem3]:e:f:g:[b,c,d]:[h,i,k]
)";

Gurax_TesterEntry(Parser)
{
	auto TestFunc = [](const char* src) {
		Error::Clear();
		RefPtr<Expr_Root> pExprRoot = Parser::ParseString(src);
		if (Error::IsIssued()) {
			Error::Print(*Stream::CErr);
			return;
		}
		for (const Expr* pExpr = pExprRoot->GetExprElemFirst(); pExpr; pExpr = pExpr->GetExprNext()) {
			::printf("%s\n", pExpr->ToString().c_str());
		}
	};
#if 1
	PrintTitle("ReduceOneToken");
	TestFunc(src_ReduceOneToken);
	PrintTitle("ReduceTwoTokens");
	TestFunc(src_ReduceTwoTokens);
	PrintTitle("ReduceThreeTokens");
	TestFunc(src_ReduceThreeTokens);
	PrintTitle("ReduceFourAndFiveTokens");
	TestFunc(src_ReduceFourAndFiveTokens);
	PrintTitle("Attribute");
	TestFunc(src_Attribute);
#else
	TestFunc(src_Attribute);
#endif
}

}
