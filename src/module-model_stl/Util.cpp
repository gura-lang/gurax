//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_stl)

void SetError_FormatError()
{
	Error::Issue(ErrorType::FormatError, "invalid format of STL file");
}

Gurax_EndModuleScope(model_stl)
