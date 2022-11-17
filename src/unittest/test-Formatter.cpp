//==============================================================================
// test-Formatter.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_TesterEntry(Formatter)
{
	Stream::COut->Printf("%zu\n", 0xfffffff);
	Stream::COut->Printf("%zx\n", 0xfffffffffffff);
}

}
