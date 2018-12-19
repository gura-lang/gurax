//==============================================================================
// gurax.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

void sub(int argc, char* argv[])
{
#if 0
	RefPtr<Tokenizer> pTokenizer(new Tokenizer("", 0, false));
	RefPtr<Object> pObj(new Object_number());
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
	//TokenWatcher tokenWatcher;
	//RefPtr<Tokenizer> pTokenizer(new Tokenizer(tokenWatcher, pathNameSrc));
	RefPtr<Parser> pParser(new Parser(pathNameSrc));
	FILE* fp = ::fopen(pathNameSrc, "rt");
	for (;;) {
		int chRaw = ::fgetc(fp);
		char ch = (chRaw < 0)? '\0' : static_cast<UChar>(chRaw);
		pParser->ParseChar(ch);
		if (Error::IsIssued()) {
			Error::Print(stdout);
		}
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

