//==============================================================================
// module-os.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(os)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// os.Exec(pathName:string, args*:String):map:[fork]
Gurax_DeclareFunction(Exec)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pathName", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("args", VTYPE_String, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
	DeclareAttrOpt(Gurax_Symbol(fork));
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(Exec)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	const ValueList& valList = Value_List::GetValueOwner(args.PickValue());
	// Function body
	Stream& streamCIn = Basement::Inst.GetStreamCIn();
	Stream& streamCOut = Basement::Inst.GetStreamCOut();
	Stream& streamCErr = Basement::Inst.GetStreamCErr();
	bool forkFlag = argument.IsSet(Gurax_Symbol(fork));
	OAL::ExecProgram(pathName, valList, &streamCIn, &streamCOut, &streamCErr, forkFlag);
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
	// Assignment of function
	Assign(Gurax_CreateFunction(Exec));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(os)
