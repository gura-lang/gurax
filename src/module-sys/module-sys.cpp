//==============================================================================
// module-sys.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(sys)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// sys.Exit(exitCode?:Number):void
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
// Implementation of property
//------------------------------------------------------------------------------
// sys.ps1
Gurax_DeclareModuleProperty_RW(ps1)
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementModulePropertyGetter(ps1)
{
	return new Value_String(Basement::Inst.GetPS1());
}

Gurax_ImplementModulePropertySetter(ps1)
{
	Basement::Inst.SetPS1(dynamic_cast<const Value_String&>(value).GetString());
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
	// Assignment of property
	Assign(Gurax_CreateModuleProperty(ps1));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(sys)
