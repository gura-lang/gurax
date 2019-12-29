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

// hash.CRC32() {block?}
Gurax_DeclareFunction(CRC32)
{
	Declare(VTYPE_Accumulator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Accumulator` instance.");
}

Gurax_ImplementFunction(CRC32)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Accumulator> pAccumulator(new Accumulator_CRC32());
	return argument.ReturnValue(processor, new Value_Accumulator(pAccumulator.release()));
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

// hash.SHA1() {block?}
Gurax_DeclareFunction(SHA1)
{
	Declare(VTYPE_Accumulator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Accumulator` instance.");
}

Gurax_ImplementFunction(SHA1)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Accumulator> pAccumulator(new Accumulator_SHA1());
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
	Assign(Gurax_CreateFunction(CRC32));
	Assign(Gurax_CreateFunction(MD5));
	Assign(Gurax_CreateFunction(SHA1));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(hash)
