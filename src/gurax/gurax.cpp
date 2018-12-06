//==============================================================================
// gurax.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

void sub()
{
	Object::Bootup();
	UniquePtr<Tokenizer> pTokenizer(new Tokenizer());
	UniquePtr<Object> pObj(new Object_number());
}

}

int main()
{
	Gurax::sub();
	::printf("hello\n");
	return 0;
}

