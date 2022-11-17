//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(bmp)

void IssueError_InvalidFormat()
{
	Error::Issue(ErrorType::FormatError, "invalid format of bmp file");
}

void IssueError_FailToWrite()
{
	Error::Issue(ErrorType::StreamError, "failed to write the bmp data");
}

Gurax_EndModuleScope(bmp)
