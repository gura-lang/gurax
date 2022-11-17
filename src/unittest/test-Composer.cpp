//==============================================================================
// test-Composer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

struct Info {
	const char* title;
	const char* src;
};

static const Info infoTbl[] = {
{"Identifier", R"(
var
var = 3
)"},
{"Statement-repeat", R"(
repeat {
}
)"},
{"Statement-for", R"(
for (a in b) {
}
)"},
{"Statement-while", R"(
while (a) {
}
)"},
{"Statement-return", R"(
return
return(1)
)"},
};

Gurax_TesterEntry(Composer)
{
	auto TestFunc = [](const Info& info) {
		PrintTitle(info.title);
		Error::Clear();
		RefPtr<Expr_Root> pExprOfRoot(Parser::ParseString(info.src));
		if (Error::IsIssued()) {
			Error::Print(*Stream::CErr);
			Error::Clear();
			return;
		}
		Composer composer;
		pExprOfRoot->Compose(composer);
		composer.Flush();
		if (Error::IsIssued()) {
			Error::Print(*Stream::CErr);
			Error::Clear();
			return;
		}
		//composer.PrintPUnit();
		PUnit::Print(pExprOfRoot->GetPUnitFirst(), composer.PeekPUnitCont());
	};
	for (size_t i = 0; i < Gurax_ArraySizeOf(infoTbl); i++) TestFunc(infoTbl[i]);
}

}
