//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

bool IsOK(cairo_status_t status)
{
	if (status == CAIRO_STATUS_SUCCESS) return true;
	Error::Issue(ErrorType::GuestError, "%s", cairo_status_to_string(status));
	return false;
}

Gurax_EndModuleScope(cairo)
