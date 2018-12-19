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

int main(int argc, char* argv[])
{
	if (argc < 2) {
		::fprintf(stderr, "usage: test-Tokenizer file\n");
		return 1;
	}
	const char* pathNameSrc = argv[1];
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
	return 0;
}

}

int main(int argc, char* argv[])
{
	Gurax::Bootup();
	return Gurax::main(argc, argv);
}
