//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

void SetError_FormatError()
{
	Error::Issue(ErrorType::FormatError, "invalid format of OBJ file");
}

void SetError_NotImplementedKeyword(const char* keyword)
{
	Error::Issue(ErrorType::FormatError, "not implemented keyword %s", keyword);
}

Gurax_EndModuleScope(model_obj)
