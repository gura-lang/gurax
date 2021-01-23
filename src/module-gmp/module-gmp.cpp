//==============================================================================
// module-gmp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(gmp)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// gmp.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Adds up the given two numbers and returns the result.");
}

Gurax_ImplementFunction(Test)
{
	// Function body
	mpz_class m;
	m.set_str("12345678901234567890123456789", 10);
	::printf("%s\n", m.get_str().c_str());
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
	// Assignment of VType
	Assign(VTYPE_mpf);
	Assign(VTYPE_mpq);
	Assign(VTYPE_mpz);
	// Assignment of function
	Assign(Gurax_CreateFunction(Test));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(gmp)
