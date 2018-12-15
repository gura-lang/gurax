//==============================================================================
// gurax.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

class TokenWatcher : public Tokenizer::TokenWatcher {
public:
	virtual void FeedToken(UniquePtr<Token> pToken) override {
		::printf("%s\n", pToken->GetSymbol());
	}
};

void sub(int argc, char* argv[])
{
#if 0
	UniquePtr<Tokenizer> pTokenizer(new Tokenizer("", 0, false));
	UniquePtr<Object> pObj(new Object_number());
	const Symbol* pSymbol1 = Symbol::Add("hoge");
	const Symbol* pSymbol2 = Symbol::Add("hoge");
	::printf("%p %p\n", pSymbol1, pSymbol2);
	for (UInt32 ch = 0; ch < 256; ch++) {
		::printf("%d %d %d\n", ch, static_cast<char>(static_cast<UChar>(ch)), static_cast<char>(ch));
	}
#endif
	if (argc < 2) {
		return;
	}
	const char* pathNameSrc = argv[1];
	TokenWatcher tokenWatcher;
	UniquePtr<Tokenizer> pTokenizer(new Tokenizer(tokenWatcher, pathNameSrc));
	FILE* fp = ::fopen(pathNameSrc, "rt");
	for (;;) {
		int chRaw = ::fgetc(fp);
		char ch = (chRaw < 0)? '\0' : static_cast<UChar>(chRaw);
		pTokenizer->FeedChar(ch);
		if (chRaw < 0) break;
	}
	::fclose(fp);
}

}

int main(int argc, char* argv[])
{
	Gurax::Bootup();
	Gurax::sub(argc, argv);
	return 0;
}

