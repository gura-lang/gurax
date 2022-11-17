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
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->push_back(new Value_String(str));
	pValueOwner->push_back(new Value_Number(n));
	Stream::COut->PrintValueList("Hello %s World %d\n", *pValueOwner);
}

}
