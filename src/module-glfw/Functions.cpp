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

// f()
Gurax_DeclareFunction(f)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("windows", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(f)
{
	// Arguments
	ArgPicker args(argument);
	auto windows = args.PickVector<GLFWwindow*>(Value_GLFWwindow::ValueForVector);
	// Function body
	//f(windows);
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
