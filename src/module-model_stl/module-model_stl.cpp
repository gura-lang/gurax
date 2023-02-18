//==============================================================================
// module-model_stl.cpp
// Specification: https://en.wikipedia.org/wiki/STL_%28file_format%29
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(model_stl)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Assignment of VType
	Assign(VTYPE_Face);
	Assign(VTYPE_Solid);
	// Assignment of function
	//Assign(Gurax_CreateFunction(Test));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(model_stl)
