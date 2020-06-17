//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glfw)

//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------
// glfw.glfwInit()
Gurax_DeclareFunction(glfwInit)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwInit)
{
	// Function body
	if (::glfwInit() != GLFW_TRUE) IssueError();
	return Value::nil();
}

// glfw.glfwTerminate()
Gurax_DeclareFunction(glfwTerminate)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwTerminate)
{
	// Function body
	::glfwTerminate();
	return Value::nil();
}

//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(glfwInit));
	frame.Assign(Gurax_CreateFunction(glfwTerminate));
}

Gurax_EndModuleScope(glfw)
