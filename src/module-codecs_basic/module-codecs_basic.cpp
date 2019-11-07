//==============================================================================
// module-codecs_basic.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(codecs_basic)

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(codecs_basic)
