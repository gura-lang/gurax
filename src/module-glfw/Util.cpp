//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glfw)

void IssueError()
{
	const char* description;
	::glfwGetError(&description);
	Error::Issue(ErrorType::GuestError, "%s", description);
}

Gurax_EndModuleScope(glfw)
