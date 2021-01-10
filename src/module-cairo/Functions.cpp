//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

// cairo.cairo_version()
Gurax_DeclareFunctionAlias(cairo_version_gurax, "cairo_version")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_version_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = cairo_version();
	return new Gurax::Value_Number(rtn);
}

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(cairo_version_gurax));
}

Gurax_EndModuleScope(cairo)
