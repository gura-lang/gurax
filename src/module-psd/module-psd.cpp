//==============================================================================
// module-psd.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(psd)

struct FileHeader {
	char Signature[4];
	Gurax_PackedUInt16_BE(Version);
	char Reserved1[6];
	Gurax_PackedUInt16_BE(NumberOfChannels);
	Gurax_PackedUInt32_BE(Height);
	Gurax_PackedUInt32_BE(Width);
	Gurax_PackedUInt16_BE(Depth);
	Gurax_PackedUInt16_BE(ColorMode);
}

struct ColorModeDataSectionHeader {
	Gurax_PackedUInt32_BE(Length);
};

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// psd.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Adds up the given two numbers and returns the result.
)**");
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
	Assign(Gurax_CreateFunction(Test));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(psd)
