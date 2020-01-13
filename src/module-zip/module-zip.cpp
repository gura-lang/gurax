//==============================================================================
// module-zip.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(zip)

//------------------------------------------------------------------------------
// Symbol
//------------------------------------------------------------------------------
/*
Gurax_RealizeSymbol(filename);
Gurax_RealizeSymbol(comment);
Gurax_RealizeSymbol(compression_method);
Gurax_RealizeSymbol(mtime);
Gurax_RealizeSymbol(crc32);
Gurax_RealizeSymbol(size);
Gurax_RealizeSymbol(compressed_size);
Gurax_RealizeSymbol(attributes);
*/

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// zip.Open() {block?}
Gurax_DeclareFunction(Open)
{
	Declare(VTYPE_Directory, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Returns a `Directory` instance that browses the contents in a ZIP stream.");
}

Gurax_ImplementFunction(Open)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<Directory> pDirectory(ReadCentralDirectory(stream, nullptr, nullptr, Directory::Type::None));
	if (!pDirectory) return Value::nil();
	return new Value_Directory(pDirectory.release());
}

// re.Test()
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
	Assign(VTYPE_Reader);
	Assign(VTYPE_Stat);
	Assign(VTYPE_Writer);
	// Assignment of function
	Assign(Gurax_CreateFunction(Open));
	Assign(Gurax_CreateFunction(Test));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(zip)
