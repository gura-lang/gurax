//==============================================================================
// module-codecs.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(codecs)

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
	// Assignment of function
	//Assign(Gurax_CreateFunction(Exit));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(codecs)
