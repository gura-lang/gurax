//==============================================================================
// test-Composer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static const char* src = R"(
i = 0
f() = {
	Printf('%d\n', i)
	i += 1
}
f()
)";

#if 0
static const char* src = R"(
a = 3
if (a == 3) {
	Println('a is 3')
} else {
	Println('a is not 3')
}
)";
#endif

#if 0
static const char* src = R"(
a = 3
b = 2
c = a + b
Println('Hello World')
Println(c)
v = [3, 1, 4, 1]
Println(v)
Println(v[0])
//f()
//f(3, 1, 4, 1)
if (a == 3) {
	Println('a is three')
}
a = 0
while (a < 3) {
	Printf('Hello World #%d\n', a)
	a += 1
}
)";
#endif

#if 0
static const char* src = R"(
a = 0
while (a < 3) {|i|
	Printf('Hello World #%d\n', i)
	a += 1
}
)";
#endif

Gurax_TesterEntry(Composer)
{
	RefPtr<Expr_Root> pExprRoot(Parser::ParseString(src));
	if (Error::IsIssued()) {
		Error::Print(*Stream::CErr);
		Error::Clear();
		return;
	}
	Composer composer;
	pExprRoot->Compose(composer);
	//composer.GetPUnitList().Print();
	RefPtr<Processor> pProcessor(Processor::Debug());
	pProcessor->Run(composer.GetPUnitTop());
	if (Error::IsIssued()) Error::Print(*Stream::CErr);
}

}
