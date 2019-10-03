//==============================================================================
// Pattern.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// Pattern
//------------------------------------------------------------------------------
Pattern::Pattern() : _reg(nullptr)
{
}

bool Pattern::Prepare(const char* pattern)
{
	OnigErrorInfo einfo;
	int r = ::onig_new(&_reg, pattern, pattern + strlen((char* )pattern),
					 ONIG_OPTION_DEFAULT, ONIG_ENCODING_ASCII, ONIG_SYNTAX_DEFAULT, &einfo);
	if (r != ONIG_NORMAL) {
		OnigUChar s[ONIG_MAX_ERROR_MESSAGE_LEN];
		::onig_error_code_to_str(s, r, &einfo);
		Error::Issue(ErrorType::GuestError, "%s", s);
		return false;
	}
	return true;
}

Gurax_EndModuleScope(re)
