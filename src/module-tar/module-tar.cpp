//==============================================================================
// module-tar.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(tar)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// tar.Test(stream:Stream)
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Adds up the given two numbers and returns the result.");
}

Gurax_ImplementFunction(Test)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	for (;;) {
		std::unique_ptr<Header> pHdr(Header::Read(stream));
		if (!pHdr) break;
	}
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
	// Assignment of function
	Assign(Gurax_CreateFunction(Test));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(tar)
