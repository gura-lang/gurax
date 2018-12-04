//==============================================================================
// gurax.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

void sub()
{
	UniquePtr<Tokenizer> pTokenizer(new Tokenizer());
	//Tokenizer::Delete(pTokenizer);
}

}

int main()
{
	Gurax::sub();
	::printf("hello\n");
	return 0;
}

