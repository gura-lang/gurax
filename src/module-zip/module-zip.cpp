//==============================================================================
// module-zip.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(zip)

//------------------------------------------------------------------------------
// Symbol
//------------------------------------------------------------------------------
Gurax_RealizeSymbol(filename);
Gurax_RealizeSymbol(comment);
Gurax_RealizeSymbol(compression_method);
Gurax_RealizeSymbol(mtime);
Gurax_RealizeSymbol(crc32);
Gurax_RealizeSymbol(size);
Gurax_RealizeSymbol(compressed_size);
Gurax_RealizeSymbol(attributes);

Gurax_RealizeSymbol(store);
Gurax_RealizeSymbol(shrink);
Gurax_RealizeSymbol(factor1);
Gurax_RealizeSymbol(factor2);
Gurax_RealizeSymbol(factor3);
Gurax_RealizeSymbol(factor4);
Gurax_RealizeSymbol(implode);
Gurax_RealizeSymbol(deflate);
Gurax_RealizeSymbol(deflate64);
Gurax_RealizeSymbol(pkware);
Gurax_RealizeSymbol(bzip2);
Gurax_RealizeSymbol(lzma);
Gurax_RealizeSymbol(tersa);
Gurax_RealizeSymbol(lz77);
Gurax_RealizeSymbol(wavpack);
Gurax_RealizeSymbol(ppmd);

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
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
	Assign(Gurax_CreateFunction(Test));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(zip)
