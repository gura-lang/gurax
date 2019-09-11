//==============================================================================
// module-fs.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(fs)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return true;
}

Gurax_ModulePrepare()
{
	Frame& frame = GetFrame();
	// Prepare VType
	VTYPE_Stat.Prepare(frame);
	// Assignment of function
	//Assign(Gurax_CreateFunction(Exit));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(fs)
