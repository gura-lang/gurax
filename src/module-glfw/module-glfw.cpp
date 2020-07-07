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
// Callback function
//------------------------------------------------------------------------------
RefPtr<Processor> g_pProcessor_ErrorCallback;
RefPtr<Function> g_pFunc_ErrorCallback;

void callback_ErrorCallback(int error_code, const char* description)
{
	Function* pFunc = g_pFunc_ErrorCallback.get();
	if (!pFunc) return;
	RefPtr<Frame> pFrame(pFunc->LockFrameOuter());
	RefPtr<Argument> pArgument(new Argument(*pFunc, DeclCallable::Flag::CutExtraArgs));
	ArgFeeder args(*pArgument);
	args.FeedValues(*pFrame, new Value_Number(error_code), new Value_String(description));
	if (Error::IsIssued()) return;
	Value::Delete(pFunc->Eval(*g_pProcessor_ErrorCallback, *pArgument));
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
	Assign(VTYPE_GLFWcursor);
	Assign(VTYPE_GLFWgammaramp);
	Assign(VTYPE_GLFWimage);
	Assign(VTYPE_GLFWmonitor);
	Assign(VTYPE_GLFWvidmode);
	Assign(VTYPE_GLFWwindow);
	// Assignment of function
	AssignConsts(GetFrame());
	AssignFunctions(GetFrame());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(glfw)
