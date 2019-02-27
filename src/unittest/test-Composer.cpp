//==============================================================================
// test-Composer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static const char* src = R"(
a = 3
c = a + b
v = [1, 2, 3, 4]
v[0]
f()
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
