//==============================================================================
// module-codecs.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(codecs)

//-----------------------------------------------------------------------------
// Implementation of function
//-----------------------------------------------------------------------------

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
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(codecs)
