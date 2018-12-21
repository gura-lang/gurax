//==============================================================================
// test-Parser.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static const char* text = R"(
c = a + b
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
