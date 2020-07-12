//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glfw)

// glfw.glfwMakeContextCurrent(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwMakeContextCurrent_gurax, "glfwMakeContextCurrent")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwMakeContextCurrent_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwMakeContextCurrent(window);
	return Value::nil();
}

// glfw.glfwGetCurrentContext()
Gurax_DeclareFunctionAlias(glfwGetCurrentContext_gurax, "glfwGetCurrentContext")
{
	Declare(VTYPE_GLFWwindow, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetCurrentContext_gurax)
{
	// Function body
	if (GLFWwindow* rtn = glfwGetCurrentContext()) {
		return new Value_GLFWwindow(rtn, processor.Reference());
	}
	IssueError();
	return Value::nil();
}

// glfw.glfwSwapInterval(interval:Number)
Gurax_DeclareFunctionAlias(glfwSwapInterval_gurax, "glfwSwapInterval")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("interval", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSwapInterval_gurax)
{
	// Arguments
	ArgPicker args(argument);
	int interval = args.PickNumber<int>();
	// Function body
	glfwSwapInterval(interval);
	return Value::nil();
}

// glfw.glfwExtensionSupported(extension:String)
Gurax_DeclareFunctionAlias(glfwExtensionSupported_gurax, "glfwExtensionSupported")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("extension", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwExtensionSupported_gurax)
{
	// Arguments
	ArgPicker args(argument);
	const char* extension = args.PickString();
	// Function body
	bool rtn =(glfwExtensionSupported(extension) == GLFW_TRUE);
	return new Value_Bool(rtn);
}

// glfw.glfwInit()
Gurax_DeclareFunctionAlias(glfwInit_gurax, "glfwInit")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwInit_gurax)
{
	// Function body
	if (glfwInit() != GLFW_TRUE) IssueError();
	return Value::nil();
}

// glfw.glfwTerminate()
Gurax_DeclareFunctionAlias(glfwTerminate_gurax, "glfwTerminate")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwTerminate_gurax)
{
	// Function body
	glfwTerminate();
	return Value::nil();
}

// glfw.glfwInitHint(hint:Number, value:Number)
Gurax_DeclareFunctionAlias(glfwInitHint_gurax, "glfwInitHint")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("hint", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwInitHint_gurax)
{
	// Arguments
	ArgPicker args(argument);
	int hint = args.PickNumber<int>();
	int value = args.PickNumber<int>();
	// Function body
	glfwInitHint(hint, value);
	return Value::nil();
}

// glfw.glfwGetVersion()
Gurax_DeclareFunctionAlias(glfwGetVersion_gurax, "glfwGetVersion")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetVersion_gurax)
{
	// Function body
	int major, minor, rev;
	glfwGetVersion(&major, &minor, &rev);
	return Value_List::Create(new Value_Number(major), new Value_Number(minor), new Value_Number(rev));
}

// glfw.glfwGetVersionString()
Gurax_DeclareFunctionAlias(glfwGetVersionString_gurax, "glfwGetVersionString")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetVersionString_gurax)
{
	// Function body
	const char* rtn = glfwGetVersionString();
	return new Value_String(rtn);
}

// glfw.glfwGetError()
Gurax_DeclareFunctionAlias(glfwGetError_gurax, "glfwGetError")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetError_gurax)
{
	// Function body
	const char* description;
	glfwGetError(&description);
	return description? new Value_String(description) : Value::nil();
}

// glfw.glfwSetErrorCallback(callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetErrorCallback_gurax, "glfwSetErrorCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetErrorCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	glfwSetErrorCallback(callback? callback_ErrorCallback : nullptr);
	g_pProcessor_ErrorCallback.reset(callback? processor.Reference() : nullptr);
	g_pFunc_ErrorCallback.reset(callback.release());
	return Value::nil();
}

// glfw.glfwGetInputMode(window:glfw.GLFWwindow, mode:Number)
Gurax_DeclareFunctionAlias(glfwGetInputMode_gurax, "glfwGetInputMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetInputMode_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	int mode = args.PickNumber<int>();
	// Function body
	int rtn = glfwGetInputMode(window, mode);
	return new Value_Number(rtn);
}

// glfw.glfwSetInputMode(window:glfw.GLFWwindow, mode:Number, value:Number)
Gurax_DeclareFunctionAlias(glfwSetInputMode_gurax, "glfwSetInputMode")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetInputMode_gurax)
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

// glfw.glfwRawMouseMotionSupported()
Gurax_DeclareFunctionAlias(glfwRawMouseMotionSupported_gurax, "glfwRawMouseMotionSupported")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwRawMouseMotionSupported_gurax)
{
	// Function body
	bool rtn =(glfwRawMouseMotionSupported() == GLFW_TRUE);
	return new Value_Bool(rtn);
}

// glfw.glfwGetKeyName(key:Number, scancode:Number)
Gurax_DeclareFunctionAlias(glfwGetKeyName_gurax, "glfwGetKeyName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("key", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("scancode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetKeyName_gurax)
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

// glfw.glfwGetKeyScancode(key:Number)
Gurax_DeclareFunctionAlias(glfwGetKeyScancode_gurax, "glfwGetKeyScancode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("key", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetKeyScancode_gurax)
{
	// Arguments
	ArgPicker args(argument);
	int key = args.PickNumber<int>();
	// Function body
	int rtn = glfwGetKeyScancode(key);
	return new Value_Number(rtn);
}

// glfw.glfwGetKey(window:glfw.GLFWwindow, key:Number)
Gurax_DeclareFunctionAlias(glfwGetKey_gurax, "glfwGetKey")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("key", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetKey_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	int key = args.PickNumber<int>();
	// Function body
	int rtn = glfwGetKey(window, key);
	return new Value_Number(rtn);
}

// glfw.glfwGetMouseButton(window:glfw.GLFWwindow, button:Number)
Gurax_DeclareFunctionAlias(glfwGetMouseButton_gurax, "glfwGetMouseButton")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("button", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetMouseButton_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	int button = args.PickNumber<int>();
	// Function body
	int rtn = glfwGetMouseButton(window, button);
	return new Value_Number(rtn);
}

// glfw.glfwGetCursorPos(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetCursorPos_gurax, "glfwGetCursorPos")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetCursorPos_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return Value_List::Create(new Value_Number(xpos), new Value_Number(ypos));
}

// glfw.glfwSetCursorPos(window:glfw.GLFWwindow, xpos:Number, ypos:Number)
Gurax_DeclareFunctionAlias(glfwSetCursorPos_gurax, "glfwSetCursorPos")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xpos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ypos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetCursorPos_gurax)
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

// glfw.glfwCreateCursor(image:glfw.GLFWimage, xhot:Number, yhot:Number)
Gurax_DeclareFunctionAlias(glfwCreateCursor_gurax, "glfwCreateCursor")
{
	Declare(VTYPE_GLFWcursor, Flag::None);
	DeclareArg("image", VTYPE_GLFWimage, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xhot", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yhot", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwCreateCursor_gurax)
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

// glfw.glfwCreateStandardCursor(shape:Number)
Gurax_DeclareFunctionAlias(glfwCreateStandardCursor_gurax, "glfwCreateStandardCursor")
{
	Declare(VTYPE_GLFWcursor, Flag::None);
	DeclareArg("shape", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwCreateStandardCursor_gurax)
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

// glfw.glfwDestroyCursor(cursor:glfw.GLFWcursor)
Gurax_DeclareFunctionAlias(glfwDestroyCursor_gurax, "glfwDestroyCursor")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cursor", VTYPE_GLFWcursor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwDestroyCursor_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWcursor* cursor = args.Pick<Value_GLFWcursor>().GetEntity();
	// Function body
	glfwDestroyCursor(cursor);
	return Value::nil();
}

// glfw.glfwSetCursor(window:glfw.GLFWwindow, cursor:glfw.GLFWcursor)
Gurax_DeclareFunctionAlias(glfwSetCursor_gurax, "glfwSetCursor")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cursor", VTYPE_GLFWcursor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetCursor_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	GLFWcursor* cursor = args.Pick<Value_GLFWcursor>().GetEntity();
	// Function body
	glfwSetCursor(window, cursor);
	return Value::nil();
}

// glfw.glfwSetKeyCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetKeyCallback_gurax, "glfwSetKeyCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetKeyCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetKeyCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_KeyCallback : nullptr);
	valueThis.SetFunc_KeyCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetCharCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetCharCallback_gurax, "glfwSetCharCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetCharCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetCharCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_CharCallback : nullptr);
	valueThis.SetFunc_CharCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetCharModsCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetCharModsCallback_gurax, "glfwSetCharModsCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetCharModsCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetCharModsCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_CharModsCallback : nullptr);
	valueThis.SetFunc_CharModsCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetMouseButtonCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetMouseButtonCallback_gurax, "glfwSetMouseButtonCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetMouseButtonCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetMouseButtonCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_MouseButtonCallback : nullptr);
	valueThis.SetFunc_MouseButtonCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetCursorPosCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetCursorPosCallback_gurax, "glfwSetCursorPosCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetCursorPosCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetCursorPosCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_CursorPosCallback : nullptr);
	valueThis.SetFunc_CursorPosCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetCursorEnterCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetCursorEnterCallback_gurax, "glfwSetCursorEnterCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetCursorEnterCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetCursorEnterCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_CursorEnterCallback : nullptr);
	valueThis.SetFunc_CursorEnterCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetScrollCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetScrollCallback_gurax, "glfwSetScrollCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetScrollCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetScrollCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_ScrollCallback : nullptr);
	valueThis.SetFunc_ScrollCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetDropCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetDropCallback_gurax, "glfwSetDropCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetDropCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetDropCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_DropCallback : nullptr);
	valueThis.SetFunc_DropCallback(callback.release());
	return Value::nil();
}

// glfw.glfwJoystickPresent(jid:Number)
Gurax_DeclareFunctionAlias(glfwJoystickPresent_gurax, "glfwJoystickPresent")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwJoystickPresent_gurax)
{
	// Arguments
	ArgPicker args(argument);
	int jid = args.PickNumber<int>();
	// Function body
	int rtn = glfwJoystickPresent(jid);
	return new Value_Number(rtn);
}

// glfw.glfwGetJoystickAxes(jid:Number)
Gurax_DeclareFunctionAlias(glfwGetJoystickAxes_gurax, "glfwGetJoystickAxes")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetJoystickAxes_gurax)
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

// glfw.glfwGetJoystickButtons(jid:Number)
Gurax_DeclareFunctionAlias(glfwGetJoystickButtons_gurax, "glfwGetJoystickButtons")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetJoystickButtons_gurax)
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

// glfw.glfwGetJoystickHats(jid:Number)
Gurax_DeclareFunctionAlias(glfwGetJoystickHats_gurax, "glfwGetJoystickHats")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetJoystickHats_gurax)
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

// glfw.glfwGetJoystickName(jid:Number)
Gurax_DeclareFunctionAlias(glfwGetJoystickName_gurax, "glfwGetJoystickName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetJoystickName_gurax)
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

// glfw.glfwGetJoystickGUID(jid:Number)
Gurax_DeclareFunctionAlias(glfwGetJoystickGUID_gurax, "glfwGetJoystickGUID")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetJoystickGUID_gurax)
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

// glfw.glfwJoystickIsGamepad(jid:Number)
Gurax_DeclareFunctionAlias(glfwJoystickIsGamepad_gurax, "glfwJoystickIsGamepad")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwJoystickIsGamepad_gurax)
{
	// Arguments
	ArgPicker args(argument);
	int jid = args.PickNumber<int>();
	// Function body
	bool rtn =(glfwJoystickIsGamepad(jid) == GLFW_TRUE);
	return new Value_Bool(rtn);
}

// glfw.glfwSetJoystickCallback(jid:Number, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetJoystickCallback_gurax, "glfwSetJoystickCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetJoystickCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	int jid = args.PickNumber<int>();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	//glfwSetJoystickCallback(jid,
	//		callback? Value_GLFWwindow::callback_JoystickCallback : nullptr);
	//valueThis.SetFunc_JoystickCallback(callback.release());
	return Value::nil();
}

// glfw.glfwUpdateGamepadMappings(string:String)
Gurax_DeclareFunctionAlias(glfwUpdateGamepadMappings_gurax, "glfwUpdateGamepadMappings")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("string", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwUpdateGamepadMappings_gurax)
{
	// Arguments
	ArgPicker args(argument);
	const char* string = args.PickString();
	// Function body
	if (glfwUpdateGamepadMappings(string) != GLFW_TRUE) IssueError();
	return Value::nil();
}

// glfw.glfwGetGamepadName(jid:Number)
Gurax_DeclareFunctionAlias(glfwGetGamepadName_gurax, "glfwGetGamepadName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetGamepadName_gurax)
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

// glfw.glfwSetClipboardString(window:glfw.GLFWwindow, string:String)
Gurax_DeclareFunctionAlias(glfwSetClipboardString_gurax, "glfwSetClipboardString")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("string", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetClipboardString_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	const char* string = args.PickString();
	// Function body
	glfwSetClipboardString(window, string);
	return Value::nil();
}

// glfw.glfwGetClipboardString(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetClipboardString_gurax, "glfwGetClipboardString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetClipboardString_gurax)
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

// glfw.glfwGetTime()
Gurax_DeclareFunctionAlias(glfwGetTime_gurax, "glfwGetTime")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetTime_gurax)
{
	// Function body
	double rtn = glfwGetTime();
	return new Value_Number(rtn);
}

// glfw.glfwSetTime(time:Number)
Gurax_DeclareFunctionAlias(glfwSetTime_gurax, "glfwSetTime")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("time", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetTime_gurax)
{
	// Arguments
	ArgPicker args(argument);
	double time = args.PickNumber<double>();
	// Function body
	glfwSetTime(time);
	return Value::nil();
}

// glfw.glfwGetTimerValue()
Gurax_DeclareFunctionAlias(glfwGetTimerValue_gurax, "glfwGetTimerValue")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetTimerValue_gurax)
{
	// Function body
	uint64_t rtn = glfwGetTimerValue();
	return new Value_Number(rtn);
}

// glfw.glfwGetTimerFrequency()
Gurax_DeclareFunctionAlias(glfwGetTimerFrequency_gurax, "glfwGetTimerFrequency")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetTimerFrequency_gurax)
{
	// Function body
	uint64_t rtn = glfwGetTimerFrequency();
	return new Value_Number(rtn);
}

// glfw.glfwGetMonitors()
Gurax_DeclareFunctionAlias(glfwGetMonitors_gurax, "glfwGetMonitors")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetMonitors_gurax)
{
	// Function body
	int count;
	GLFWmonitor** rtn = glfwGetMonitors(&count);
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(count);
	for (int i = 0; i < count; i++) {
		pValueOwner->push_back(new Value_GLFWmonitor(rtn[i]));
	}
	return new Value_List(pValueOwner.release());
}

// glfw.glfwGetPrimaryMonitor()
Gurax_DeclareFunctionAlias(glfwGetPrimaryMonitor_gurax, "glfwGetPrimaryMonitor")
{
	Declare(VTYPE_GLFWmonitor, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetPrimaryMonitor_gurax)
{
	// Function body
	if (GLFWmonitor* rtn = glfwGetPrimaryMonitor()) {
		return new Value_GLFWmonitor(rtn);
	}
	IssueError();
	return Value::nil();
}

// glfw.glfwGetMonitorPos(monitor:glfw.GLFWmonitor)
Gurax_DeclareFunctionAlias(glfwGetMonitorPos_gurax, "glfwGetMonitorPos")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetMonitorPos_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWmonitor* monitor = args.Pick<Value_GLFWmonitor>().GetEntity();
	// Function body
	int xpos, ypos;
	glfwGetMonitorPos(monitor, &xpos, &ypos);
	return Value_List::Create(new Value_Number(xpos), new Value_Number(ypos));
}

// glfw.glfwGetMonitorWorkarea(monitor:glfw.GLFWmonitor)
Gurax_DeclareFunctionAlias(glfwGetMonitorWorkarea_gurax, "glfwGetMonitorWorkarea")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetMonitorWorkarea_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWmonitor* monitor = args.Pick<Value_GLFWmonitor>().GetEntity();
	// Function body
	int xpos, ypos, width, height;
	glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);
	return Value_List::Create(new Value_Number(xpos), new Value_Number(ypos),
						new Value_Number(width), new Value_Number(height));
}

// glfw.glfwGetMonitorPhysicalSize(monitor:glfw.GLFWmonitor)
Gurax_DeclareFunctionAlias(glfwGetMonitorPhysicalSize_gurax, "glfwGetMonitorPhysicalSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetMonitorPhysicalSize_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWmonitor* monitor = args.Pick<Value_GLFWmonitor>().GetEntity();
	// Function body
	int widthMM, heightMM;
	glfwGetMonitorPhysicalSize(monitor, &widthMM, &heightMM);
	return Value_List::Create(new Value_Number(widthMM), new Value_Number(heightMM));
}

// glfw.glfwGetMonitorContentScale(monitor:glfw.GLFWmonitor)
Gurax_DeclareFunctionAlias(glfwGetMonitorContentScale_gurax, "glfwGetMonitorContentScale")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetMonitorContentScale_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWmonitor* monitor = args.Pick<Value_GLFWmonitor>().GetEntity();
	// Function body
	float xscale, yscale;
	glfwGetMonitorContentScale(monitor, &xscale, &yscale);
	return Value_List::Create(new Value_Number(xscale), new Value_Number(yscale));
}

// glfw.glfwGetMonitorName(monitor:glfw.GLFWmonitor)
Gurax_DeclareFunctionAlias(glfwGetMonitorName_gurax, "glfwGetMonitorName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetMonitorName_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWmonitor* monitor = args.Pick<Value_GLFWmonitor>().GetEntity();
	// Function body
	const char* rtn = glfwGetMonitorName(monitor);
	return new Value_String(rtn);
}

// glfw.glfwSetMonitorCallback(callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetMonitorCallback_gurax, "glfwSetMonitorCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetMonitorCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	glfwSetMonitorCallback(callback? callback_MonitorCallback : nullptr);
	g_pProcessor_MonitorCallback.reset(callback? processor.Reference() : nullptr);
	g_pFunc_MonitorCallback.reset(callback.release());
	return Value::nil();
}

// glfw.glfwGetVideoModes(monitor:glfw.GLFWmonitor)
Gurax_DeclareFunctionAlias(glfwGetVideoModes_gurax, "glfwGetVideoModes")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetVideoModes_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWmonitor* monitor = args.Pick<Value_GLFWmonitor>().GetEntity();
	// Function body
	int count;
	const GLFWvidmode* rtn = glfwGetVideoModes(monitor, &count);
	if (!rtn) return Value::nil();
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(count);
	for (int i = 0; i < count; i++) {
		pValueOwner->push_back(new Value_GLFWvidmode(&rtn[i]));
	}
	return new Value_List(pValueOwner.release());
}

// glfw.glfwGetVideoMode(monitor:glfw.GLFWmonitor)
Gurax_DeclareFunctionAlias(glfwGetVideoMode_gurax, "glfwGetVideoMode")
{
	Declare(VTYPE_GLFWvidmode, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetVideoMode_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWmonitor* monitor = args.Pick<Value_GLFWmonitor>().GetEntity();
	// Function body
	if (const GLFWvidmode* rtn = glfwGetVideoMode(monitor)) {
		return new Value_GLFWvidmode(rtn);
	}
	IssueError();
	return Value::nil();
}

// glfw.glfwSetGamma(monitor:glfw.GLFWmonitor, gamma:Number)
Gurax_DeclareFunctionAlias(glfwSetGamma_gurax, "glfwSetGamma")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	DeclareArg("gamma", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetGamma_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWmonitor* monitor = args.Pick<Value_GLFWmonitor>().GetEntity();
	float gamma = args.PickNumber<float>();
	// Function body
	glfwSetGamma(monitor, gamma);
	return Value::nil();
}

// glfw.glfwGetGammaRamp(monitor:glfw.GLFWmonitor)
Gurax_DeclareFunctionAlias(glfwGetGammaRamp_gurax, "glfwGetGammaRamp")
{
	Declare(VTYPE_GLFWgammaramp, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetGammaRamp_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWmonitor* monitor = args.Pick<Value_GLFWmonitor>().GetEntity();
	// Function body
	if (const GLFWgammaramp* rtn = glfwGetGammaRamp(monitor)) {
		return new Value_GLFWgammaramp(rtn);
	}
	IssueError();
	return Value::nil();
}

// glfw.glfwSetGammaRamp(monitor:glfw.GLFWmonitor, ramp:glfw.GLFWgammaramp)
Gurax_DeclareFunctionAlias(glfwSetGammaRamp_gurax, "glfwSetGammaRamp")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ramp", VTYPE_GLFWgammaramp, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetGammaRamp_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWmonitor* monitor = args.Pick<Value_GLFWmonitor>().GetEntity();
	const GLFWgammaramp* ramp = args.Pick<Value_GLFWgammaramp>().GetEntity();
	// Function body
	glfwSetGammaRamp(monitor, ramp);
	return Value::nil();
}

// glfw.glfwVulkanSupported()
Gurax_DeclareFunctionAlias(glfwVulkanSupported_gurax, "glfwVulkanSupported")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwVulkanSupported_gurax)
{
	// Function body
	bool rtn =(glfwVulkanSupported() == GLFW_TRUE);
	return new Value_Bool(rtn);
}

// glfw.glfwGetRequiredInstanceExtensions()
Gurax_DeclareFunctionAlias(glfwGetRequiredInstanceExtensions_gurax, "glfwGetRequiredInstanceExtensions")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetRequiredInstanceExtensions_gurax)
{
	// Function body
	uint32_t count;
	const char** rtn = glfwGetRequiredInstanceExtensions(&count);
	if (!rtn) return Value::nil();
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(count);
	for (uint32_t i = 0; i < count; i++) {
		pValueOwner->push_back(new Value_String(rtn[i]));
	}
	return new Value_List(pValueOwner.release());
}

// glfw.glfwDefaultWindowHints()
Gurax_DeclareFunctionAlias(glfwDefaultWindowHints_gurax, "glfwDefaultWindowHints")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwDefaultWindowHints_gurax)
{
	// Function body
	glfwDefaultWindowHints();
	return Value::nil();
}

// glfw.glfwWindowHint(hint:Number, value:Number)
Gurax_DeclareFunctionAlias(glfwWindowHint_gurax, "glfwWindowHint")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("hint", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwWindowHint_gurax)
{
	// Arguments
	ArgPicker args(argument);
	int hint = args.PickNumber<int>();
	int value = args.PickNumber<int>();
	// Function body
	glfwWindowHint(hint, value);
	return Value::nil();
}

// glfw.glfwWindowHintString(hint:Number, value:String)
Gurax_DeclareFunctionAlias(glfwWindowHintString_gurax, "glfwWindowHintString")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("hint", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwWindowHintString_gurax)
{
	// Arguments
	ArgPicker args(argument);
	int hint = args.PickNumber<int>();
	const char* value = args.PickString();
	// Function body
	glfwWindowHintString(hint, value);
	return Value::nil();
}

// glfw.glfwCreateWindow(width:Number, height:Number, title:String, monitor:glfw.GLFWmonitor:nil, share:glfw.GLFWwindow:nil)
Gurax_DeclareFunctionAlias(glfwCreateWindow_gurax, "glfwCreateWindow")
{
	Declare(VTYPE_GLFWwindow, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("share", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwCreateWindow_gurax)
{
	// Arguments
	ArgPicker args(argument);
	int width = args.PickNumber<int>();
	int height = args.PickNumber<int>();
	const char* title = args.PickString();
	GLFWmonitor* monitor = args.IsValid()? args.Pick<Value_GLFWmonitor>().GetEntity() : nullptr;
	GLFWwindow* share = args.IsValid()? args.Pick<Value_GLFWwindow>().GetEntity() : nullptr;
	// Function body
	if (GLFWwindow* rtn = glfwCreateWindow(width, height, title, monitor, share)) {
		return new Value_GLFWwindow(rtn, processor.Reference());
	}
	IssueError();
	return Value::nil();
}

// glfw.glfwDestroyWindow(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwDestroyWindow_gurax, "glfwDestroyWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwDestroyWindow_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwDestroyWindow(window);
	return Value::nil();
}

// glfw.glfwWindowShouldClose(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwWindowShouldClose_gurax, "glfwWindowShouldClose")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwWindowShouldClose_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	bool rtn = glfwWindowShouldClose(window);
	return new Value_Bool(rtn);
}

// glfw.glfwSetWindowShouldClose(window:glfw.GLFWwindow, value:Bool)
Gurax_DeclareFunctionAlias(glfwSetWindowShouldClose_gurax, "glfwSetWindowShouldClose")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowShouldClose_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	bool value = args.PickBool();
	// Function body
	glfwSetWindowShouldClose(window, value);
	return Value::nil();
}

// glfw.glfwSetWindowTitle(window:glfw.GLFWwindow, title:String)
Gurax_DeclareFunctionAlias(glfwSetWindowTitle_gurax, "glfwSetWindowTitle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowTitle_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	const char* title = args.PickString();
	// Function body
	glfwSetWindowTitle(window, title);
	return Value::nil();
}

// glfw.glfwSetWindowIcon(window:glfw.GLFWwindow, images[]:glfw.GLFWimage)
Gurax_DeclareFunctionAlias(glfwSetWindowIcon_gurax, "glfwSetWindowIcon")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("images", VTYPE_GLFWimage, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowIcon_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	auto images = args.PickListT<GLFWimage>(Value_GLFWimage::ValueForVector);
	// Function body
	glfwSetWindowIcon(window, static_cast<int>(images.size()), images.data());
	return Value::nil();
}

// glfw.glfwGetWindowPos(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetWindowPos_gurax, "glfwGetWindowPos")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetWindowPos_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	int xpos, ypos;
	glfwGetWindowPos(window, &xpos, &ypos);
	return Value_List::Create(new Value_Number(xpos), new Value_Number(ypos));
}

// glfw.glfwSetWindowPos(window:glfw.GLFWwindow, xpos:Number, ypos:Number)
Gurax_DeclareFunctionAlias(glfwSetWindowPos_gurax, "glfwSetWindowPos")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xpos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ypos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowPos_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	int xpos = args.PickNumber<int>();
	int ypos = args.PickNumber<int>();
	// Function body
	glfwSetWindowPos(window, xpos, ypos);
	return Value::nil();
}

// glfw.glfwGetWindowSize(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetWindowSize_gurax, "glfwGetWindowSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetWindowSize_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return Value_List::Create(new Value_Number(width), new Value_Number(height));
}

// glfw.glfwSetWindowSizeLimits(window:glfw.GLFWwindow, minwidth:Number, minheight:Number, maxwidth:Number, maxheight:Number)
Gurax_DeclareFunctionAlias(glfwSetWindowSizeLimits_gurax, "glfwSetWindowSizeLimits")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("minwidth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("minheight", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxwidth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxheight", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowSizeLimits_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	int minwidth = args.PickNumber<int>();
	int minheight = args.PickNumber<int>();
	int maxwidth = args.PickNumber<int>();
	int maxheight = args.PickNumber<int>();
	// Function body
	glfwSetWindowSizeLimits(window, minwidth, minheight, maxwidth, maxheight);
	return Value::nil();
}

// glfw.glfwSetWindowAspectRatio(window:glfw.GLFWwindow, numer:Number, denom:Number)
Gurax_DeclareFunctionAlias(glfwSetWindowAspectRatio_gurax, "glfwSetWindowAspectRatio")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("numer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("denom", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowAspectRatio_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	int numer = args.PickNumber<int>();
	int denom = args.PickNumber<int>();
	// Function body
	glfwSetWindowAspectRatio(window, numer, denom);
	return Value::nil();
}

// glfw.glfwSetWindowSize(window:glfw.GLFWwindow, width:Number, height:Number)
Gurax_DeclareFunctionAlias(glfwSetWindowSize_gurax, "glfwSetWindowSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowSize_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	int width = args.PickNumber<int>();
	int height = args.PickNumber<int>();
	// Function body
	glfwSetWindowSize(window, width, height);
	return Value::nil();
}

// glfw.glfwGetFramebufferSize(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetFramebufferSize_gurax, "glfwGetFramebufferSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetFramebufferSize_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	return Value_List::Create(new Value_Number(width), new Value_Number(height));
}

// glfw.glfwGetWindowFrameSize(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetWindowFrameSize_gurax, "glfwGetWindowFrameSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetWindowFrameSize_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	int left, top, right, bottom;
	glfwGetWindowFrameSize(window, &left, &top, &right, &bottom);
	return Value_List::Create(new Value_Number(left), new Value_Number(top),
							new Value_Number(right), new Value_Number(bottom));
}

// glfw.glfwGetWindowContentScale(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetWindowContentScale_gurax, "glfwGetWindowContentScale")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetWindowContentScale_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	float xscale, yscale;
	glfwGetWindowContentScale(window, &xscale, &yscale);
	return Value_List::Create(new Value_Number(xscale), new Value_Number(yscale));
}

// glfw.glfwGetWindowOpacity(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetWindowOpacity_gurax, "glfwGetWindowOpacity")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetWindowOpacity_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	float rtn = glfwGetWindowOpacity(window);
	return new Value_Number(rtn);
}

// glfw.glfwSetWindowOpacity(window:glfw.GLFWwindow, opacity:Number)
Gurax_DeclareFunctionAlias(glfwSetWindowOpacity_gurax, "glfwSetWindowOpacity")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("opacity", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowOpacity_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	float opacity = args.PickNumber<float>();
	// Function body
	glfwSetWindowOpacity(window, opacity);
	return Value::nil();
}

// glfw.glfwIconifyWindow(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwIconifyWindow_gurax, "glfwIconifyWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwIconifyWindow_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwIconifyWindow(window);
	return Value::nil();
}

// glfw.glfwRestoreWindow(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwRestoreWindow_gurax, "glfwRestoreWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwRestoreWindow_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwRestoreWindow(window);
	return Value::nil();
}

// glfw.glfwMaximizeWindow(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwMaximizeWindow_gurax, "glfwMaximizeWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwMaximizeWindow_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwMaximizeWindow(window);
	return Value::nil();
}

// glfw.glfwShowWindow(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwShowWindow_gurax, "glfwShowWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwShowWindow_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwShowWindow(window);
	return Value::nil();
}

// glfw.glfwHideWindow(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwHideWindow_gurax, "glfwHideWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwHideWindow_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwHideWindow(window);
	return Value::nil();
}

// glfw.glfwFocusWindow(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwFocusWindow_gurax, "glfwFocusWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwFocusWindow_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwFocusWindow(window);
	return Value::nil();
}

// glfw.glfwRequestWindowAttention(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwRequestWindowAttention_gurax, "glfwRequestWindowAttention")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwRequestWindowAttention_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwRequestWindowAttention(window);
	return Value::nil();
}

// glfw.glfwGetWindowMonitor(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetWindowMonitor_gurax, "glfwGetWindowMonitor")
{
	Declare(VTYPE_GLFWmonitor, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetWindowMonitor_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	if (GLFWmonitor* rtn = glfwGetWindowMonitor(window)) {
		return new Value_GLFWmonitor(rtn);
	}
	IssueError();
	return Value::nil();
}

// glfw.glfwSetWindowMonitor(window:glfw.GLFWwindow, monitor:glfw.GLFWmonitor, xpos:Number, ypos:Number, width:Number, height:Number, refreshRate:Number)
Gurax_DeclareFunctionAlias(glfwSetWindowMonitor_gurax, "glfwSetWindowMonitor")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xpos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ypos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("refreshRate", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowMonitor_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	GLFWmonitor* monitor = args.Pick<Value_GLFWmonitor>().GetEntity();
	int xpos = args.PickNumber<int>();
	int ypos = args.PickNumber<int>();
	int width = args.PickNumber<int>();
	int height = args.PickNumber<int>();
	int refreshRate = args.PickNumber<int>();
	// Function body
	glfwSetWindowMonitor(window, monitor, xpos, ypos, width, height, refreshRate);
	return Value::nil();
}

// glfw.glfwGetWindowAttrib(window:glfw.GLFWwindow, attrib:Number)
Gurax_DeclareFunctionAlias(glfwGetWindowAttrib_gurax, "glfwGetWindowAttrib")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attrib", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetWindowAttrib_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	int attrib = args.PickNumber<int>();
	// Function body
	int rtn = glfwGetWindowAttrib(window, attrib);
	return new Value_Number(rtn);
}

// glfw.glfwSetWindowAttrib(window:glfw.GLFWwindow, attrib:Number, value:Number)
Gurax_DeclareFunctionAlias(glfwSetWindowAttrib_gurax, "glfwSetWindowAttrib")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attrib", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowAttrib_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	int attrib = args.PickNumber<int>();
	int value = args.PickNumber<int>();
	// Function body
	glfwSetWindowAttrib(window, attrib, value);
	return Value::nil();
}

// glfw.glfwSetWindowPosCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetWindowPosCallback_gurax, "glfwSetWindowPosCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowPosCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetWindowPosCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_WindowPosCallback : nullptr);
	valueThis.SetFunc_WindowPosCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetWindowSizeCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetWindowSizeCallback_gurax, "glfwSetWindowSizeCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowSizeCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetWindowSizeCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_WindowSizeCallback : nullptr);
	valueThis.SetFunc_WindowSizeCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetWindowCloseCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetWindowCloseCallback_gurax, "glfwSetWindowCloseCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowCloseCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetWindowCloseCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_WindowCloseCallback : nullptr);
	valueThis.SetFunc_WindowCloseCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetWindowRefreshCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetWindowRefreshCallback_gurax, "glfwSetWindowRefreshCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowRefreshCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetWindowRefreshCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_WindowRefreshCallback : nullptr);
	valueThis.SetFunc_WindowRefreshCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetWindowFocusCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetWindowFocusCallback_gurax, "glfwSetWindowFocusCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowFocusCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetWindowFocusCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_WindowFocusCallback : nullptr);
	valueThis.SetFunc_WindowFocusCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetWindowIconifyCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetWindowIconifyCallback_gurax, "glfwSetWindowIconifyCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowIconifyCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetWindowIconifyCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_WindowIconifyCallback : nullptr);
	valueThis.SetFunc_WindowIconifyCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetWindowMaximizeCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetWindowMaximizeCallback_gurax, "glfwSetWindowMaximizeCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowMaximizeCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetWindowMaximizeCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_WindowMaximizeCallback : nullptr);
	valueThis.SetFunc_WindowMaximizeCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetFramebufferSizeCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetFramebufferSizeCallback_gurax, "glfwSetFramebufferSizeCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetFramebufferSizeCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetFramebufferSizeCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_FramebufferSizeCallback : nullptr);
	valueThis.SetFunc_FramebufferSizeCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetWindowContentScaleCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunctionAlias(glfwSetWindowContentScaleCallback_gurax, "glfwSetWindowContentScaleCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowContentScaleCallback_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetWindowContentScaleCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_WindowContentScaleCallback : nullptr);
	valueThis.SetFunc_WindowContentScaleCallback(callback.release());
	return Value::nil();
}

// glfw.glfwPollEvents()
Gurax_DeclareFunctionAlias(glfwPollEvents_gurax, "glfwPollEvents")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwPollEvents_gurax)
{
	// Function body
	glfwPollEvents();
	return Value::nil();
}

// glfw.glfwWaitEvents()
Gurax_DeclareFunctionAlias(glfwWaitEvents_gurax, "glfwWaitEvents")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwWaitEvents_gurax)
{
	// Function body
	glfwWaitEvents();
	return Value::nil();
}

// glfw.glfwWaitEventsTimeout(timeout:Number)
Gurax_DeclareFunctionAlias(glfwWaitEventsTimeout_gurax, "glfwWaitEventsTimeout")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("timeout", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwWaitEventsTimeout_gurax)
{
	// Arguments
	ArgPicker args(argument);
	double timeout = args.PickNumber<double>();
	// Function body
	glfwWaitEventsTimeout(timeout);
	return Value::nil();
}

// glfw.glfwPostEmptyEvent()
Gurax_DeclareFunctionAlias(glfwPostEmptyEvent_gurax, "glfwPostEmptyEvent")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwPostEmptyEvent_gurax)
{
	// Function body
	glfwPostEmptyEvent();
	return Value::nil();
}

// glfw.glfwSwapBuffers(window:glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwSwapBuffers_gurax, "glfwSwapBuffers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSwapBuffers_gurax)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwSwapBuffers(window);
	return Value::nil();
}

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(glfwMakeContextCurrent_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetCurrentContext_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSwapInterval_gurax));
	frame.Assign(Gurax_CreateFunction(glfwExtensionSupported_gurax));
	frame.Assign(Gurax_CreateFunction(glfwInit_gurax));
	frame.Assign(Gurax_CreateFunction(glfwTerminate_gurax));
	frame.Assign(Gurax_CreateFunction(glfwInitHint_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetVersion_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetVersionString_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetError_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetErrorCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetInputMode_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetInputMode_gurax));
	frame.Assign(Gurax_CreateFunction(glfwRawMouseMotionSupported_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetKeyName_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetKeyScancode_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetKey_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetMouseButton_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetCursorPos_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetCursorPos_gurax));
	frame.Assign(Gurax_CreateFunction(glfwCreateCursor_gurax));
	frame.Assign(Gurax_CreateFunction(glfwCreateStandardCursor_gurax));
	frame.Assign(Gurax_CreateFunction(glfwDestroyCursor_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetCursor_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetKeyCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetCharCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetCharModsCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetMouseButtonCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetCursorPosCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetCursorEnterCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetScrollCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetDropCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwJoystickPresent_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetJoystickAxes_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetJoystickButtons_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetJoystickHats_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetJoystickName_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetJoystickGUID_gurax));
	frame.Assign(Gurax_CreateFunction(glfwJoystickIsGamepad_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetJoystickCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwUpdateGamepadMappings_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetGamepadName_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetClipboardString_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetClipboardString_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetTime_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetTime_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetTimerValue_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetTimerFrequency_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetMonitors_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetPrimaryMonitor_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetMonitorPos_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetMonitorWorkarea_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetMonitorPhysicalSize_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetMonitorContentScale_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetMonitorName_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetMonitorCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetVideoModes_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetVideoMode_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetGamma_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetGammaRamp_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetGammaRamp_gurax));
	frame.Assign(Gurax_CreateFunction(glfwVulkanSupported_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetRequiredInstanceExtensions_gurax));
	frame.Assign(Gurax_CreateFunction(glfwDefaultWindowHints_gurax));
	frame.Assign(Gurax_CreateFunction(glfwWindowHint_gurax));
	frame.Assign(Gurax_CreateFunction(glfwWindowHintString_gurax));
	frame.Assign(Gurax_CreateFunction(glfwCreateWindow_gurax));
	frame.Assign(Gurax_CreateFunction(glfwDestroyWindow_gurax));
	frame.Assign(Gurax_CreateFunction(glfwWindowShouldClose_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowShouldClose_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowTitle_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowIcon_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetWindowPos_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowPos_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetWindowSize_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowSizeLimits_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowAspectRatio_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowSize_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetFramebufferSize_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetWindowFrameSize_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetWindowContentScale_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetWindowOpacity_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowOpacity_gurax));
	frame.Assign(Gurax_CreateFunction(glfwIconifyWindow_gurax));
	frame.Assign(Gurax_CreateFunction(glfwRestoreWindow_gurax));
	frame.Assign(Gurax_CreateFunction(glfwMaximizeWindow_gurax));
	frame.Assign(Gurax_CreateFunction(glfwShowWindow_gurax));
	frame.Assign(Gurax_CreateFunction(glfwHideWindow_gurax));
	frame.Assign(Gurax_CreateFunction(glfwFocusWindow_gurax));
	frame.Assign(Gurax_CreateFunction(glfwRequestWindowAttention_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetWindowMonitor_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowMonitor_gurax));
	frame.Assign(Gurax_CreateFunction(glfwGetWindowAttrib_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowAttrib_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowPosCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowSizeCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowCloseCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowRefreshCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowFocusCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowIconifyCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowMaximizeCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetFramebufferSizeCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowContentScaleCallback_gurax));
	frame.Assign(Gurax_CreateFunction(glfwPollEvents_gurax));
	frame.Assign(Gurax_CreateFunction(glfwWaitEvents_gurax));
	frame.Assign(Gurax_CreateFunction(glfwWaitEventsTimeout_gurax));
	frame.Assign(Gurax_CreateFunction(glfwPostEmptyEvent_gurax));
	frame.Assign(Gurax_CreateFunction(glfwSwapBuffers_gurax));
}

Gurax_EndModuleScope(glfw)
