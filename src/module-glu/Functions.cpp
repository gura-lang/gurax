//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glu)

// glu.gluErrorString(errCode as Number)
Gurax_DeclareFunctionAlias(gluErrorString_gurax, "gluErrorString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("errCode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluErrorString_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum errCode = args_gurax.PickNumber<GLenum>();
	// Function body
	const GLubyte* rtn = gluErrorString(errCode);
	return new Gurax::Value_String(reinterpret_cast<const char*>(rtn));
}

// glu.gluGetString(name as Number)
Gurax_DeclareFunctionAlias(gluGetString_gurax, "gluGetString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("name", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(gluGetString_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLenum name = args_gurax.PickNumber<GLenum>();
	// Function body
	const GLubyte* rtn = gluGetString(name);
	return new Gurax::Value_String(reinterpret_cast<const char*>(rtn));
}

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(gluErrorString_gurax));
	frame.Assign(Gurax_CreateFunction(gluGetString_gurax));
}

Gurax_EndModuleScope(glu)
