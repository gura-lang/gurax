//==============================================================================
// module-re.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(re)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// re.test()
Gurax_DeclareFunction(test)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("a", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(test)
{
	// Arguments
	ArgPicker args(argument);
	Int a = args.PickNumber<Int>();
	Int b = args.PickNumber<Int>();
	// Function body
	return new Value_Number(a + b);
}

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
	Assign(Gurax_CreateFunction(test));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(re)
