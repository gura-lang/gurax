//==============================================================================
// test-Stream.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_TesterEntry(Stream)
{
	Stream::COut->Printf("Hello World\n");
	RefPtr<ObjectOwner> pObjOwner(new ObjectOwner());
	pObjOwner->push_back(new Object_number(3));
	Stream::COut->PrintFmt("Hello World %d\n", *pObjOwner);
}

}
