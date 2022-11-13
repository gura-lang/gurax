//==============================================================================
// module-csv.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(csv)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Function

# Class
)**";

//------------------------------------------------------------------------------
// Symbol
//------------------------------------------------------------------------------
Gurax_RealizeSymbol(asList);
Gurax_RealizeSymbol(asTuple);

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// csv.Test()
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
	// Add help
	AddHelp("en", g_docHelp_en);
	// Assignment of VType
	Assign(VTYPE_Reader);
	Assign(VTYPE_Writer);
	// Assignment of function
	Assign(Gurax_CreateFunction(Test));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(csv)
