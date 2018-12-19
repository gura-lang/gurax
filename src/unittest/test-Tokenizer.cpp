//==============================================================================
// test-Tokenizer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

class TokenWatcher : public Tokenizer::TokenWatcher {
public:
	virtual void FeedToken(RefPtr<Token> pToken) override {
		::printf("%s\n", pToken->GetSymbol());
	}
};

Gurax_TesterEntry(Tokenizer)
{
	if (argc < 1) {
		::fprintf(stderr, "usage: unittest Tokenizer file\n");
		return;
	}
	const char* pathNameSrc = argv[0];
	TokenWatcher tokenWatcher;
	RefPtr<Tokenizer> pTokenizer(new Tokenizer(tokenWatcher, pathNameSrc));
	FILE* fp = ::fopen(pathNameSrc, "rt");
	for (;;) {
		int chRaw = ::fgetc(fp);
		char ch = (chRaw < 0)? '\0' : static_cast<UChar>(chRaw);
		pTokenizer->FeedChar(ch);
		if (Error::IsIssued()) {
			Error::Print(stdout);
			break;
		}
		if (chRaw < 0) break;
	}
	::fclose(fp);
}

}
