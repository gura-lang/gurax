//==============================================================================
// module-model_obj.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(model_obj)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// model.obj.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
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
	// Assignment of VType
	Assign(VTYPE_Content);
	Assign(VTYPE_Face);
	Assign(VTYPE_Line);
	Assign(VTYPE_Point);
	Assign(VTYPE_Vertex3);
	Assign(VTYPE_Vertex4);
	// Assignment of function
	Assign(Gurax_CreateFunction(Test));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(model_obj)
