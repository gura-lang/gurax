//==============================================================================
// module-opengl.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(opengl)

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Assignment of value
	AssignConsts(GetFrame());
	// Assignment of function
	AssignFunctions(GetFrame());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(opengl)
