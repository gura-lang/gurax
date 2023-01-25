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

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(gluErrorString_gurax));
}

Gurax_EndModuleScope(glu)
