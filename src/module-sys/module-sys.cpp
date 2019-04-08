//==============================================================================
// module-sys.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(sys)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// Exit(exitCode?:Number):void
Gurax_DeclareFunction(Exit)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("exitCode", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Exit)
{
	// Arguments
	ArgPicker args(argument);
	int exitCode = args.IsDefined()? args.PickInt() : 0;
	// Function body
	std::exit(exitCode);
	return Value::nil();
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
	// Assignment of value
	Assign("cin", new Value_Stream(Stream::CIn->Reference()));
	Assign("cout", new Value_Stream(Stream::COut->Reference()));
	Assign("cerr", new Value_Stream(Stream::CErr->Reference()));
	// Assignment of function
	Assign(Gurax_CreateFunction(Exit));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(sys)
