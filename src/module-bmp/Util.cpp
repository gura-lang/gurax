//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(bmp)

void IssueError_InvalidFormat()
{
	Error::Issue(ErrorType::FormatError, "invalid format of bmp file");
}

Gurax_EndModuleScope(bmp)
