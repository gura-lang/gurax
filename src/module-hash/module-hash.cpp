//==============================================================================
// module-hash.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(hash)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// hash.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Adds up the given two numbers and returns the result.");
}

Gurax_ImplementFunction(Test)
{
	// Arguments
	ArgPicker args(argument);
	const char* str = args.PickString();
	Int num = args.PickNumber<Int>();
	// Function body
	return new Value_String(String::Repeat(str, num));
}

// hash.MD5() {block?}
Gurax_DeclareFunction(MD5)
{
	Declare(VTYPE_Accumulator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Accumulator` instance.");
}

Gurax_ImplementFunction(MD5)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Accumulator> pAccumulator(new Accumulator_MD5());
	return argument.ReturnValue(processor, new Value_Accumulator(pAccumulator.release()));
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
	Assign(VTYPE_Accumulator);
	// Assignment of function
	Assign(Gurax_CreateFunction(Test));
	Assign(Gurax_CreateFunction(MD5));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(hash)
