//==============================================================================
// module-mswin.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(mswin)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// mswin.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Adds up the given two numbers and returns the result.
)""");
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
	Assign(VTYPE_OLE);
	Assign(VTYPE_RegKey);
	// Assignment of function
	//Assign(Gurax_CreateFunction(Test));
	// Assignment of value
	Assign("HKEY_CLASSES_ROOT",			new Value_RegKey(new RegKey(HKEY_CLASSES_ROOT, "HKEY_CLASSES_ROOT", false)));
	Assign("HKEY_CURRENT_CONFIG",		new Value_RegKey(new RegKey(HKEY_CURRENT_CONFIG, "HKEY_CURRENT_CONFIG", false)));
	Assign("HKEY_CURRENT_USER",			new Value_RegKey(new RegKey(HKEY_CURRENT_USER, "HKEY_CURRENT_USER", false)));
	Assign("HKEY_LOCAL_MACHINE",		new Value_RegKey(new RegKey(HKEY_LOCAL_MACHINE, "HKEY_LOCAL_MACHINE", false)));
	Assign("HKEY_USERS",				new Value_RegKey(new RegKey(HKEY_USERS, "HKEY_USERS", false)));
	Assign("HKEY_PERFORMANCE_DATA",		new Value_RegKey(new RegKey(HKEY_PERFORMANCE_DATA, "HKEY_PERFORMANCE_DATA", false)));
	Assign("HKEY_DYN_DATA",				new Value_RegKey(new RegKey(HKEY_DYN_DATA, "HKEY_DYN_DATA", false)));
	Assign("REG_OPTION_NON_VOLATILE",	new Value_Number(REG_OPTION_NON_VOLATILE));
	Assign("REG_OPTION_VOLATILE",		new Value_Number(REG_OPTION_VOLATILE));
	Assign("REG_OPTION_BACKUP_RESTORE",	new Value_Number(REG_OPTION_BACKUP_RESTORE));
	Assign("KEY_CREATE_LINK",			new Value_Number(KEY_CREATE_LINK));
	Assign("KEY_CREATE_SUB_KEY",		new Value_Number(KEY_CREATE_SUB_KEY));
	Assign("KEY_ENUMERATE_SUB_KEYS",	new Value_Number(KEY_ENUMERATE_SUB_KEYS));
	Assign("KEY_EXECUTE",				new Value_Number(KEY_EXECUTE));
	Assign("KEY_NOTIFY",				new Value_Number(KEY_NOTIFY));
	Assign("KEY_QUERY_VALUE",			new Value_Number(KEY_QUERY_VALUE));
	Assign("KEY_SET_VALUE",				new Value_Number(KEY_SET_VALUE));
	Assign("KEY_ALL_ACCESS",			new Value_Number(KEY_ALL_ACCESS));
	Assign("KEY_READ",					new Value_Number(KEY_READ));
	Assign("KEY_WRITE",					new Value_Number(KEY_WRITE));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(mswin)
