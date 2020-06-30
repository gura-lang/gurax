//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glfw)

// glfwInit()
Gurax_DeclareFunction(glfwInit)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwInit)
{
	// Function body
	if (glfwInit() != GLFW_TRUE) IssueError();
	return Value::nil();
}

// glfwTerminate()
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
	glfwTerminate();
	return Value::nil();
}

// glfwDefaultWindowHints()
Gurax_DeclareFunction(glfwDefaultWindowHints)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwDefaultWindowHints)
{
	// Function body
	glfwDefaultWindowHints();
	return Value::nil();
}

// glfwWindowHint()
Gurax_DeclareFunction(glfwWindowHint)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("hint", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwWindowHint)
{
	// Arguments
	ArgPicker args(argument);
	int hint = args.PickNumber<int>();
	int value = args.PickNumber<int>();
	// Function body
	glfwWindowHint(hint, value);
	return Value::nil();
}

// glfwWindowHintString()
Gurax_DeclareFunction(glfwWindowHintString)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("hint", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwWindowHintString)
{
	// Arguments
	ArgPicker args(argument);
	int hint = args.PickNumber<int>();
	const char* value = args.PickString();
	// Function body
	glfwWindowHintString(hint, value);
	return Value::nil();
}

// glfwCreateWindow()
Gurax_DeclareFunction(glfwCreateWindow)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("share", VTYPE_GLFWwindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwCreateWindow)
{
	// Arguments
	ArgPicker args(argument);
	int width = args.PickNumber<int>();
	int height = args.PickNumber<int>();
	const char* title = args.PickString();
	GLFWmonitor* monitor = args.Pick<Value_GLFWmonitor>().GetEntity();
	GLFWwindow* share = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	if (GLFWwindow* rtn = glfwCreateWindow(width, height, title, monitor, share)) {
		return new Value_GLFWwindow(rtn);
	}
	IssueError();
	return Value::nil();
}

// glfwDestroyWindow()
Gurax_DeclareFunction(glfwDestroyWindow)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwDestroyWindow)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwDestroyWindow(window);
	return Value::nil();
}

// glfwWindowShouldClose()
Gurax_DeclareFunction(glfwWindowShouldClose)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwWindowShouldClose)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	bool rtn = glfwWindowShouldClose(window);
	return new Value_Bool(rtn);
}

// glfwSetWindowShouldClose()
Gurax_DeclareFunction(glfwSetWindowShouldClose)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowShouldClose)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	bool value = args.PickBool();
	// Function body
	glfwSetWindowShouldClose(window, value);
	return Value::nil();
}

// glfwSetWindowTitle()
Gurax_DeclareFunction(glfwSetWindowTitle)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowTitle)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	const char* title = args.PickString();
	// Function body
	glfwSetWindowTitle(window, title);
	return Value::nil();
}

// glfwSetWindowIcon()
Gurax_DeclareFunction(glfwSetWindowIcon)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("images", VTYPE_GLFWimage, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowIcon)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	auto images = args.PickVector<GLFWimage>(Value_GLFWimage::ValueForVector);
	// Function body
	glfwSetWindowIcon(window, static_cast<int>(images.size()), images.data());
	return Value::nil();
}

// glfwGetWindowPos()
Gurax_DeclareFunction(glfwGetWindowPos)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetWindowPos)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	int xpos, ypos;
	glfwGetWindowPos(window, &xpos, &ypos);
	return Value_List::Create(new Value_Number(xpos), new Value_Number(ypos));
}

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(glfwInit));
	frame.Assign(Gurax_CreateFunction(glfwTerminate));
	frame.Assign(Gurax_CreateFunction(glfwDefaultWindowHints));
	frame.Assign(Gurax_CreateFunction(glfwWindowHint));
	frame.Assign(Gurax_CreateFunction(glfwWindowHintString));
	frame.Assign(Gurax_CreateFunction(glfwCreateWindow));
	frame.Assign(Gurax_CreateFunction(glfwDestroyWindow));
	frame.Assign(Gurax_CreateFunction(glfwWindowShouldClose));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowShouldClose));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowTitle));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowIcon));
	frame.Assign(Gurax_CreateFunction(glfwGetWindowPos));
}

Gurax_EndModuleScope(glfw)
