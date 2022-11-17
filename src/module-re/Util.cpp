//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// Utility Functions
//------------------------------------------------------------------------------
void IssueError_Onigmo()
{
	Error::Issue(ErrorType::GuestError,
				 "something's wrong in the process of Onigmo library");
}

void IssueError_Onigmo(int rtn)
{
	OnigUChar str[ONIG_MAX_ERROR_MESSAGE_LEN];
	::onig_error_code_to_str(str, rtn);
	Error::Issue(ErrorType::GuestError, "%s", str);
}

void IssueError_Onigmo(int rtn, const OnigErrorInfo& einfo)
{
	OnigUChar str[ONIG_MAX_ERROR_MESSAGE_LEN];
	::onig_error_code_to_str(str, rtn, &einfo);
	Error::Issue(ErrorType::GuestError, "%s", str);
}

Gurax_EndModuleScope(re)
