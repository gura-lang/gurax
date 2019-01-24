//==============================================================================
// test-Stream.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_TesterEntry(Stream)
{
	const char *str = "Gura";
	int n = 123456;
	Stream::COut->Printf("Hello %s World %d\n", str, n);
	RefPtr<ObjectOwner> pObjOwner(new ObjectOwner());
	pObjOwner->push_back(new Object_string(str));
	pObjOwner->push_back(new Object_number(n));
	Stream::COut->PrintFmt("Hello %s World %d\n", *pObjOwner);
}

}
