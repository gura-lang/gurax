//==============================================================================
// test-Composer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static const char* src = R"(
a = 3
c = a + b
v = [3, 1, 4, 1]
v[0]
f()
f(3, 1, 4, 1)
Println('Hello World')
if (a == 3) {
	Println('a is three')
}
a = 0
while (a < 3) {
	Println('Hello World')
	a += 1
}
)";

Gurax_TesterEntry(Composer)
{
	RefPtr<Expr_Root> pExprRoot = Parser::ParseString(src);
	if (Error::IsIssued()) {
		::printf("error: %s\n", Error::GetLastError()->GetText());
		Error::Clear();
		return;
	}
	Composer composer;
	pExprRoot->Compose(composer);
	const PUnitList& punitList = composer.GetPUnitList();
	for (auto pPUnit : punitList) {
		::printf("#%zu %s\n", pPUnit->GetIndex(), pPUnit->ToString().c_str());
	}
}

}
