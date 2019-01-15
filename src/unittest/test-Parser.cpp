//==============================================================================
// test-Parser.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//c = a + b
static const char* text = R"(
a:b.m.n:c:d
)";

Gurax_TesterEntry(Parser)
{
	RefPtr<Parser> pParser(new Parser("string"));
	for (const char* p = text; ; ++p) {
		char ch = *p;
		pParser->ParseChar(ch);
		if (Error::IsIssued()) {
			Error::Print(stdout);
			break;
		}
		if (ch == '\0') break;
	}
}

}
