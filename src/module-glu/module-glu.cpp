//==============================================================================
// module-glu.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(glu)

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Assignment of function
	AssignFunctions(GetFrame());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(glu)
