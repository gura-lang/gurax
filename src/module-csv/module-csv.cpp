//==============================================================================
// module-csv.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(csv)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Function

# Class
)""";

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
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Assignment of VType
	Assign(VTYPE_Reader);
	Assign(VTYPE_Writer);
	// Assignment of function
	//Assign(Gurax_CreateFunction(Test));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(csv)
