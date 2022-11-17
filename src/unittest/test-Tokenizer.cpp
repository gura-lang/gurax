//==============================================================================
// test-Tokenizer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static const char* text = R"(
a = 3
{}
()
[]
`a
?

|+|
)";

class TokenWatcher : public Tokenizer::TokenWatcher {
public:
	virtual void FeedToken(RefPtr<Token> pToken) override {
		::printf("%s\n", pToken->GetSymbol());
	}
};

Gurax_TesterEntry(Tokenizer)
{
	TokenWatcher tokenWatcher;
	RefPtr<Tokenizer> pTokenizer(new Tokenizer(tokenWatcher, new StringReferable("string")));
	for (const char* p = text; ; ++p) {
		char ch = *p;
		pTokenizer->FeedChar(ch);
		if (Error::IsIssued()) {
			Error::Print(*Stream::CErr);
			break;
		}
		if (ch == '\0') break;
	}
}

}
