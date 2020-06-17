//==============================================================================
// module-glfw.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(glfw)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// glfw.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(Test)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return Value::nil();

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return Value::nil();
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return Value::nil();
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
	Assign(VTYPE_GLFWmonitor);
	Assign(VTYPE_GLFWwindow);
	// Assignment of function
	Assign(Gurax_CreateFunction(Test));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(glfw)
