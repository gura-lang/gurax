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
		::printf("%s\n", pPUnit->ToString().c_str());
	}
}

}
