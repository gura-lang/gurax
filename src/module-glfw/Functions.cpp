//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glfw)

// glfwInit()
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

// glfwInitHint()
Gurax_DeclareFunction(glfwInitHint)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("hint", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwInitHint)
{
	// Arguments
	ArgPicker args(argument);
	int hint = args.PickNumber<int>();
	int value = args.PickNumber<int>();
	// Function body
	glfwInitHint(hint, value);
	return Value::nil();
}

// glfwGetVersion()
Gurax_DeclareFunction(glfwGetVersion)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetVersion)
{
	// Function body
	int major, minor, rev;
	glfwGetVersion(&major, &minor, &rev);
	return Value_List::Create(new Value_Number(major), new Value_Number(minor), new Value_Number(rev));
}

// glfwGetVersionString()
Gurax_DeclareFunction(glfwGetVersionString)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetVersionString)
{
	// Function body
	const char* rtn = glfwGetVersionString();
	return new Value_String(rtn);
}

// glfwGetError()
Gurax_DeclareFunction(glfwGetError)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetError)
{
	// Function body
	const char* description;
	glfwGetError(&description);
	return description? new Value_String(description) : Value::nil();
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
	Declare(VTYPE_GLFWwindow, Flag::None);
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
	Declare(VTYPE_Bool, Flag::None);
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
	Declare(VTYPE_Bool, Flag::None);
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

// glfwGetInputMode()
Gurax_DeclareFunction(glfwGetInputMode)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetInputMode)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	int mode = args.PickNumber<int>();
	// Function body
	int rtn = glfwGetInputMode(window, mode);
	return new Value_Number(rtn);
}

// glfwSetInputMode()
Gurax_DeclareFunction(glfwSetInputMode)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetInputMode)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	int mode = args.PickNumber<int>();
	int value = args.PickNumber<int>();
	// Function body
	glfwSetInputMode(window, mode, value);
	return Value::nil();
}

// glfwRawMouseMotionSupported()
Gurax_DeclareFunction(glfwRawMouseMotionSupported)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwRawMouseMotionSupported)
{
	// Function body
	bool rtn = (glfwRawMouseMotionSupported() == GLFW_TRUE);
	return new Value_Bool(rtn);
}

// glfwGetKeyName()
Gurax_DeclareFunction(glfwGetKeyName)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("key", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("scancode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetKeyName)
{
	// Arguments
	ArgPicker args(argument);
	int key = args.PickNumber<int>();
	int scancode = args.PickNumber<int>();
	// Function body
	if (const char* rtn = glfwGetKeyName(key, scancode)) {
		return new Value_String(rtn);
	}
	return Value::nil();
}

// glfwGetKeyScancode()
Gurax_DeclareFunction(glfwGetKeyScancode)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("key", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetKeyScancode)
{
	// Arguments
	ArgPicker args(argument);
	int key = args.PickNumber<int>();
	// Function body
	int rtn = glfwGetKeyScancode(key);
	return new Value_Number(rtn);
}

// glfwGetKey()
Gurax_DeclareFunction(glfwGetKey)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("key", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetKey)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	int key = args.PickNumber<int>();
	// Function body
	int rtn = glfwGetKey(window, key);
	return new Value_Number(rtn);
}

// glfwGetMouseButton()
Gurax_DeclareFunction(glfwGetMouseButton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("button", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetMouseButton)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	int button = args.PickNumber<int>();
	// Function body
	int rtn = glfwGetMouseButton(window, button);
	return new Value_Number(rtn);
}

// glfwGetCursorPos()
Gurax_DeclareFunction(glfwGetCursorPos)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetCursorPos)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return Value_List::Create(new Value_Number(xpos), new Value_Number(ypos));
}

// glfwSetCursorPos()
Gurax_DeclareFunction(glfwSetCursorPos)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xpos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ypos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetCursorPos)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	double xpos = args.PickNumber<double>();
	double ypos = args.PickNumber<double>();
	// Function body
	glfwSetCursorPos(window, xpos, ypos);
	return Value::nil();
}

// glfwCreateCursor()
Gurax_DeclareFunction(glfwCreateCursor)
{
	Declare(VTYPE_GLFWcursor, Flag::None);
	DeclareArg("image", VTYPE_GLFWimage, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xhot", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yhot", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwCreateCursor)
{
	// Arguments
	ArgPicker args(argument);
	const GLFWimage* image = args.Pick<Value_GLFWimage>().GetEntity();
	int xhot = args.PickNumber<int>();
	int yhot = args.PickNumber<int>();
	// Function body
	if (GLFWcursor* rtn = glfwCreateCursor(image, xhot, yhot)) {
		return new Value_GLFWcursor(rtn);
	}
	IssueError();
	return Value::nil();
}

// glfwCreateStandardCursor()
Gurax_DeclareFunction(glfwCreateStandardCursor)
{
	Declare(VTYPE_GLFWcursor, Flag::None);
	DeclareArg("shape", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwCreateStandardCursor)
{
	// Arguments
	ArgPicker args(argument);
	int shape = args.PickNumber<int>();
	// Function body
	if (GLFWcursor* rtn = glfwCreateStandardCursor(shape)) {
		return new Value_GLFWcursor(rtn);
	}
	IssueError();
	return Value::nil();
}

// glfwDestroyCursor()
Gurax_DeclareFunction(glfwDestroyCursor)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cursor", VTYPE_GLFWcursor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwDestroyCursor)
{
	// Arguments
	ArgPicker args(argument);
	GLFWcursor* cursor = args.Pick<Value_GLFWcursor>().GetEntity();
	// Function body
	glfwDestroyCursor(cursor);
	return Value::nil();
}

// glfwSetCursor()
Gurax_DeclareFunction(glfwSetCursor)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cursor", VTYPE_GLFWcursor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetCursor)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	GLFWcursor* cursor = args.Pick<Value_GLFWcursor>().GetEntity();
	// Function body
	glfwSetCursor(window, cursor);
	return Value::nil();
}

// glfwJoystickPresent()
Gurax_DeclareFunction(glfwJoystickPresent)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwJoystickPresent)
{
	// Arguments
	ArgPicker args(argument);
	int jid = args.PickNumber<int>();
	// Function body
	int rtn = glfwJoystickPresent(jid);
	return new Value_Number(rtn);
}

// glfwGetJoystickAxes()
Gurax_DeclareFunction(glfwGetJoystickAxes)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetJoystickAxes)
{
	// Arguments
	ArgPicker args(argument);
	int jid = args.PickNumber<int>();
	// Function body
	int count;
	if (const float* rtn = glfwGetJoystickAxes(jid, &count)) {
		return Value_List::Create(rtn, count);
	}
	return Value::nil();
}

// glfwGetJoystickButtons()
Gurax_DeclareFunction(glfwGetJoystickButtons)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetJoystickButtons)
{
	// Arguments
	ArgPicker args(argument);
	int jid = args.PickNumber<int>();
	// Function body
	int count;
	if (const unsigned char* rtn = glfwGetJoystickButtons(jid, &count)) {
		return Value_List::Create(rtn, count);
	}
	return Value::nil();
}

// glfwGetJoystickHats()
Gurax_DeclareFunction(glfwGetJoystickHats)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetJoystickHats)
{
	// Arguments
	ArgPicker args(argument);
	int jid = args.PickNumber<int>();
	// Function body
	int count;
	if (const unsigned char* rtn = glfwGetJoystickHats(jid, &count)) {
		return Value_List::Create(rtn, count);
	}
	return Value::nil();
}

// glfwGetJoystickName()
Gurax_DeclareFunction(glfwGetJoystickName)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetJoystickName)
{
	// Arguments
	ArgPicker args(argument);
	int jid = args.PickNumber<int>();
	// Function body
	if (const char* rtn = glfwGetJoystickName(jid)) {
		return new Value_String(rtn);
	}
	return Value::nil();
}

// glfwGetJoystickGUID()
Gurax_DeclareFunction(glfwGetJoystickGUID)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetJoystickGUID)
{
	// Arguments
	ArgPicker args(argument);
	int jid = args.PickNumber<int>();
	// Function body
	if (const char* rtn = glfwGetJoystickGUID(jid)) {
		return new Value_String(rtn);
	}
	return Value::nil();
}

// glfwJoystickIsGamepad()
Gurax_DeclareFunction(glfwJoystickIsGamepad)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwJoystickIsGamepad)
{
	// Arguments
	ArgPicker args(argument);
	int jid = args.PickNumber<int>();
	// Function body
	bool rtn = (glfwJoystickIsGamepad(jid) == GLFW_TRUE);
	return new Value_Bool(rtn);
}

// glfwUpdateGamepadMappings()
Gurax_DeclareFunction(glfwUpdateGamepadMappings)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("string", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwUpdateGamepadMappings)
{
	// Arguments
	ArgPicker args(argument);
	const char* string = args.PickString();
	// Function body
	if (glfwUpdateGamepadMappings(string) != GLFW_TRUE) IssueError();
	return Value::nil();
}

// glfwGetGamepadName()
Gurax_DeclareFunction(glfwGetGamepadName)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetGamepadName)
{
	// Arguments
	ArgPicker args(argument);
	int jid = args.PickNumber<int>();
	// Function body
	if (const char* rtn = glfwGetGamepadName(jid)) {
		return new Value_String(rtn);
	}
	return Value::nil();
}

// glfwSetClipboardString()
Gurax_DeclareFunction(glfwSetClipboardString)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("string", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetClipboardString)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	const char* string = args.PickString();
	// Function body
	glfwSetClipboardString(window, string);
	return Value::nil();
}

// glfwGetClipboardString()
Gurax_DeclareFunction(glfwGetClipboardString)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetClipboardString)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	if (const char* rtn = glfwGetClipboardString(window)) {
		return new Value_String(rtn);
	}
	return Value::nil();
}

// glfwGetTime()
Gurax_DeclareFunction(glfwGetTime)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetTime)
{
	// Function body
	double rtn = glfwGetTime();
	return new Value_Number(rtn);
}

// glfwSetTime()
Gurax_DeclareFunction(glfwSetTime)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("time", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetTime)
{
	// Arguments
	ArgPicker args(argument);
	double time = args.PickNumber<double>();
	// Function body
	glfwSetTime(time);
	return Value::nil();
}

// glfwGetTimerValue()
Gurax_DeclareFunction(glfwGetTimerValue)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetTimerValue)
{
	// Function body
	uint64_t rtn = glfwGetTimerValue();
	return new Value_Number(rtn);
}

// glfwGetTimerFrequency()
Gurax_DeclareFunction(glfwGetTimerFrequency)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetTimerFrequency)
{
	// Function body
	uint64_t rtn = glfwGetTimerFrequency();
	return new Value_Number(rtn);
}

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(glfwInit));
	frame.Assign(Gurax_CreateFunction(glfwTerminate));
	frame.Assign(Gurax_CreateFunction(glfwInitHint));
	frame.Assign(Gurax_CreateFunction(glfwGetVersion));
	frame.Assign(Gurax_CreateFunction(glfwGetVersionString));
	frame.Assign(Gurax_CreateFunction(glfwGetError));
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
	frame.Assign(Gurax_CreateFunction(glfwGetInputMode));
	frame.Assign(Gurax_CreateFunction(glfwSetInputMode));
	frame.Assign(Gurax_CreateFunction(glfwRawMouseMotionSupported));
	frame.Assign(Gurax_CreateFunction(glfwGetKeyName));
	frame.Assign(Gurax_CreateFunction(glfwGetKeyScancode));
	frame.Assign(Gurax_CreateFunction(glfwGetKey));
	frame.Assign(Gurax_CreateFunction(glfwGetMouseButton));
	frame.Assign(Gurax_CreateFunction(glfwGetCursorPos));
	frame.Assign(Gurax_CreateFunction(glfwSetCursorPos));
	frame.Assign(Gurax_CreateFunction(glfwCreateCursor));
	frame.Assign(Gurax_CreateFunction(glfwCreateStandardCursor));
	frame.Assign(Gurax_CreateFunction(glfwDestroyCursor));
	frame.Assign(Gurax_CreateFunction(glfwSetCursor));
	frame.Assign(Gurax_CreateFunction(glfwJoystickPresent));
	frame.Assign(Gurax_CreateFunction(glfwGetJoystickAxes));
	frame.Assign(Gurax_CreateFunction(glfwGetJoystickButtons));
	frame.Assign(Gurax_CreateFunction(glfwGetJoystickHats));
	frame.Assign(Gurax_CreateFunction(glfwGetJoystickName));
	frame.Assign(Gurax_CreateFunction(glfwGetJoystickGUID));
	frame.Assign(Gurax_CreateFunction(glfwJoystickIsGamepad));
	frame.Assign(Gurax_CreateFunction(glfwUpdateGamepadMappings));
	frame.Assign(Gurax_CreateFunction(glfwGetGamepadName));
	frame.Assign(Gurax_CreateFunction(glfwSetClipboardString));
	frame.Assign(Gurax_CreateFunction(glfwGetClipboardString));
	frame.Assign(Gurax_CreateFunction(glfwGetTime));
	frame.Assign(Gurax_CreateFunction(glfwSetTime));
	frame.Assign(Gurax_CreateFunction(glfwGetTimerValue));
	frame.Assign(Gurax_CreateFunction(glfwGetTimerFrequency));
}

Gurax_EndModuleScope(glfw)
