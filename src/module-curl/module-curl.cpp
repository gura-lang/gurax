//==============================================================================
// module-curl.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(curl)

// curl.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(Test)
{
	return Value::nil();
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Initialize tables
	Info::Bootup();
	Opt::Bootup();
	// Assignment of VTYPE
	Assign(VTYPE_CURL);
	Assign(VTYPE_CURLU);
	Assign(VTYPE_curl_mime);
	Assign(VTYPE_curl_mimepart);
	Assign(VTYPE_curl_slist);
	Assign(VTYPE_Info);
	Assign(VTYPE_Opt);
	// Assignment of const
	AssignConsts(GetFrame());
	// Assignment of function
	AssignFunctions(GetFrame());
	Assign(Gurax_CreateFunction(Test));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(curl)
