//==============================================================================
// gurax.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

void sub()
{
	Symbol::Bootup();
	Object::Bootup();
	//UniquePtr<Tokenizer> pTokenizer(new Tokenizer());
	UniquePtr<Object> pObj(new Object_number());
	const Symbol* pSymbol1 = Symbol::Add("hoge");
	const Symbol* pSymbol2 = Symbol::Add("hoge");
	::printf("%p %p\n", pSymbol1, pSymbol2);
	for (UInt32 ch = 0; ch < 256; ch++) {
		::printf("%d %d %d\n", ch, static_cast<char>(static_cast<UChar>(ch)), static_cast<char>(ch));
	}
}

}

int main()
{
	Gurax::sub();
	return 0;
}

