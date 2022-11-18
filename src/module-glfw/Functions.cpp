//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glfw)

// glfw.glfwMakeContextCurrent(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwMakeContextCurrent_gurax, "glfwMakeContextCurrent")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwMakeContextCurrent_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwMakeContextCurrent(window);
	return Gurax::Value::nil();
}

// glfw.glfwGetCurrentContext()
Gurax_DeclareFunctionAlias(glfwGetCurrentContext_gurax, "glfwGetCurrentContext")
{
	Declare(VTYPE_GLFWwindow, Flag::None);
}

Gurax_ImplementFunctionEx(glfwGetCurrentContext_gurax, processor_gurax, argument_gurax)
{
	// Function body
	if (GLFWwindow* rtn = glfwGetCurrentContext()) {
		return new Value_GLFWwindow(rtn, processor_gurax.Reference());
	}
	IssueError();
	return Gurax::Value::nil();
}

// glfw.glfwSwapInterval(interval as Number)
Gurax_DeclareFunctionAlias(glfwSwapInterval_gurax, "glfwSwapInterval")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("interval", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSwapInterval_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int interval = args_gurax.PickNumber<int>();
	// Function body
	glfwSwapInterval(interval);
	return Gurax::Value::nil();
}

// glfw.glfwExtensionSupported(extension as String)
Gurax_DeclareFunctionAlias(glfwExtensionSupported_gurax, "glfwExtensionSupported")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("extension", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwExtensionSupported_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* extension = args_gurax.PickString();
	// Function body
	bool rtn = (glfwExtensionSupported(extension) == GLFW_TRUE);
	return new Gurax::Value_Bool(rtn);
}

// glfw.glfwInit()
Gurax_DeclareFunctionAlias(glfwInit_gurax, "glfwInit")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(glfwInit_gurax, processor_gurax, argument_gurax)
{
	// Function body
	if (glfwInit() != GLFW_TRUE) IssueError();
	return Gurax::Value::nil();
}

// glfw.glfwTerminate()
Gurax_DeclareFunctionAlias(glfwTerminate_gurax, "glfwTerminate")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(glfwTerminate_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glfwTerminate();
	return Gurax::Value::nil();
}

// glfw.glfwInitHint(hint as Number, value as Number)
Gurax_DeclareFunctionAlias(glfwInitHint_gurax, "glfwInitHint")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("hint", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwInitHint_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int hint = args_gurax.PickNumber<int>();
	int value = args_gurax.PickNumber<int>();
	// Function body
	glfwInitHint(hint, value);
	return Gurax::Value::nil();
}

// glfw.glfwGetVersion()
Gurax_DeclareFunctionAlias(glfwGetVersion_gurax, "glfwGetVersion")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementFunctionEx(glfwGetVersion_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int major, minor, rev;
	glfwGetVersion(&major, &minor, &rev);
	return Value_Tuple::Create(new Value_Number(major), new Value_Number(minor), new Value_Number(rev));
}

// glfw.glfwGetVersionString()
Gurax_DeclareFunctionAlias(glfwGetVersionString_gurax, "glfwGetVersionString")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementFunctionEx(glfwGetVersionString_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const char* rtn = glfwGetVersionString();
	return new Gurax::Value_String(rtn);
}

// glfw.glfwGetError()
Gurax_DeclareFunctionAlias(glfwGetError_gurax, "glfwGetError")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementFunctionEx(glfwGetError_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const char* description;
	glfwGetError(&description);
	return description? new Value_String(description) : Value::nil();
}

// glfw.glfwSetErrorCallback(callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetErrorCallback_gurax, "glfwSetErrorCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetErrorCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	glfwSetErrorCallback(callback? callback_ErrorCallback : nullptr);
	g_pProcessor_ErrorCallback.reset(callback? processor_gurax.Reference() : nullptr);
	g_pFunc_ErrorCallback.reset(callback.release());
	return Value::nil();
}

// glfw.glfwGetInputMode(window as glfw.GLFWwindow, mode as Number)
Gurax_DeclareFunctionAlias(glfwGetInputMode_gurax, "glfwGetInputMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetInputMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	int mode = args_gurax.PickNumber<int>();
	// Function body
	int rtn = glfwGetInputMode(window, mode);
	return new Gurax::Value_Number(rtn);
}

// glfw.glfwSetInputMode(window as glfw.GLFWwindow, mode as Number, value as Number)
Gurax_DeclareFunctionAlias(glfwSetInputMode_gurax, "glfwSetInputMode")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSetInputMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	int mode = args_gurax.PickNumber<int>();
	int value = args_gurax.PickNumber<int>();
	// Function body
	glfwSetInputMode(window, mode, value);
	return Gurax::Value::nil();
}

// glfw.glfwRawMouseMotionSupported()
Gurax_DeclareFunctionAlias(glfwRawMouseMotionSupported_gurax, "glfwRawMouseMotionSupported")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(glfwRawMouseMotionSupported_gurax, processor_gurax, argument_gurax)
{
	// Function body
	bool rtn = (glfwRawMouseMotionSupported() == GLFW_TRUE);
	return new Gurax::Value_Bool(rtn);
}

// glfw.glfwGetKeyName(key as Number, scancode as Number)
Gurax_DeclareFunctionAlias(glfwGetKeyName_gurax, "glfwGetKeyName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("key", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("scancode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetKeyName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int key = args_gurax.PickNumber<int>();
	int scancode = args_gurax.PickNumber<int>();
	// Function body
	if (const char* rtn = glfwGetKeyName(key, scancode)) {
		return new Gurax::Value_String(rtn);
	}
	return Gurax::Value::nil();
}

// glfw.glfwGetKeyScancode(key as Number)
Gurax_DeclareFunctionAlias(glfwGetKeyScancode_gurax, "glfwGetKeyScancode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("key", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetKeyScancode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int key = args_gurax.PickNumber<int>();
	// Function body
	int rtn = glfwGetKeyScancode(key);
	return new Gurax::Value_Number(rtn);
}

// glfw.glfwGetKey(window as glfw.GLFWwindow, key as Number)
Gurax_DeclareFunctionAlias(glfwGetKey_gurax, "glfwGetKey")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("key", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetKey_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	int key = args_gurax.PickNumber<int>();
	// Function body
	int rtn = glfwGetKey(window, key);
	return new Gurax::Value_Number(rtn);
}

// glfw.glfwGetMouseButton(window as glfw.GLFWwindow, button as Number)
Gurax_DeclareFunctionAlias(glfwGetMouseButton_gurax, "glfwGetMouseButton")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("button", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetMouseButton_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	int button = args_gurax.PickNumber<int>();
	// Function body
	int rtn = glfwGetMouseButton(window, button);
	return new Gurax::Value_Number(rtn);
}

// glfw.glfwGetCursorPos(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetCursorPos_gurax, "glfwGetCursorPos")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetCursorPos_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return Value_Tuple::Create(new Value_Number(xpos), new Value_Number(ypos));
}

// glfw.glfwSetCursorPos(window as glfw.GLFWwindow, xpos as Number, ypos as Number)
Gurax_DeclareFunctionAlias(glfwSetCursorPos_gurax, "glfwSetCursorPos")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xpos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ypos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSetCursorPos_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	double xpos = args_gurax.PickNumber<double>();
	double ypos = args_gurax.PickNumber<double>();
	// Function body
	glfwSetCursorPos(window, xpos, ypos);
	return Gurax::Value::nil();
}

// glfw.glfwCreateCursor(image as glfw.GLFWimage, xhot as Number, yhot as Number)
Gurax_DeclareFunctionAlias(glfwCreateCursor_gurax, "glfwCreateCursor")
{
	Declare(VTYPE_GLFWcursor, Flag::None);
	DeclareArg("image", VTYPE_GLFWimage, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xhot", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yhot", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwCreateCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const GLFWimage* image = args_gurax.Pick<Value_GLFWimage>().GetEntity();
	int xhot = args_gurax.PickNumber<int>();
	int yhot = args_gurax.PickNumber<int>();
	// Function body
	if (GLFWcursor* rtn = glfwCreateCursor(image, xhot, yhot)) {
		return new Value_GLFWcursor(rtn);
	}
	IssueError();
	return Gurax::Value::nil();
}

// glfw.glfwCreateStandardCursor(shape as Number)
Gurax_DeclareFunctionAlias(glfwCreateStandardCursor_gurax, "glfwCreateStandardCursor")
{
	Declare(VTYPE_GLFWcursor, Flag::None);
	DeclareArg("shape", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwCreateStandardCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int shape = args_gurax.PickNumber<int>();
	// Function body
	if (GLFWcursor* rtn = glfwCreateStandardCursor(shape)) {
		return new Value_GLFWcursor(rtn);
	}
	IssueError();
	return Gurax::Value::nil();
}

// glfw.glfwDestroyCursor(cursor as glfw.GLFWcursor)
Gurax_DeclareFunctionAlias(glfwDestroyCursor_gurax, "glfwDestroyCursor")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cursor", VTYPE_GLFWcursor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwDestroyCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWcursor* cursor = args_gurax.Pick<Value_GLFWcursor>().GetEntity();
	// Function body
	glfwDestroyCursor(cursor);
	return Gurax::Value::nil();
}

// glfw.glfwSetCursor(window as glfw.GLFWwindow, cursor as glfw.GLFWcursor)
Gurax_DeclareFunctionAlias(glfwSetCursor_gurax, "glfwSetCursor")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cursor", VTYPE_GLFWcursor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSetCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	GLFWcursor* cursor = args_gurax.Pick<Value_GLFWcursor>().GetEntity();
	// Function body
	glfwSetCursor(window, cursor);
	return Gurax::Value::nil();
}

// glfw.glfwSetKeyCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetKeyCallback_gurax, "glfwSetKeyCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetKeyCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetKeyCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_KeyCallback : nullptr);
	valueThis.SetFunc_KeyCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetCharCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetCharCallback_gurax, "glfwSetCharCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetCharCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetCharCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_CharCallback : nullptr);
	valueThis.SetFunc_CharCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetCharModsCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetCharModsCallback_gurax, "glfwSetCharModsCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetCharModsCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetCharModsCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_CharModsCallback : nullptr);
	valueThis.SetFunc_CharModsCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetMouseButtonCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetMouseButtonCallback_gurax, "glfwSetMouseButtonCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetMouseButtonCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetMouseButtonCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_MouseButtonCallback : nullptr);
	valueThis.SetFunc_MouseButtonCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetCursorPosCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetCursorPosCallback_gurax, "glfwSetCursorPosCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetCursorPosCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetCursorPosCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_CursorPosCallback : nullptr);
	valueThis.SetFunc_CursorPosCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetCursorEnterCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetCursorEnterCallback_gurax, "glfwSetCursorEnterCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetCursorEnterCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetCursorEnterCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_CursorEnterCallback : nullptr);
	valueThis.SetFunc_CursorEnterCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetScrollCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetScrollCallback_gurax, "glfwSetScrollCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetScrollCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetScrollCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_ScrollCallback : nullptr);
	valueThis.SetFunc_ScrollCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetDropCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetDropCallback_gurax, "glfwSetDropCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetDropCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetDropCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_DropCallback : nullptr);
	valueThis.SetFunc_DropCallback(callback.release());
	return Value::nil();
}

// glfw.glfwJoystickPresent(jid as Number)
Gurax_DeclareFunctionAlias(glfwJoystickPresent_gurax, "glfwJoystickPresent")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwJoystickPresent_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int jid = args_gurax.PickNumber<int>();
	// Function body
	int rtn = glfwJoystickPresent(jid);
	return new Gurax::Value_Number(rtn);
}

// glfw.glfwGetJoystickAxes(jid as Number)
Gurax_DeclareFunctionAlias(glfwGetJoystickAxes_gurax, "glfwGetJoystickAxes")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetJoystickAxes_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int jid = args_gurax.PickNumber<int>();
	// Function body
	int count;
	if (const float* rtn = glfwGetJoystickAxes(jid, &count)) {
		return Value_Tuple::Create(rtn, count);
	}
	return Value::nil();
}

// glfw.glfwGetJoystickButtons(jid as Number)
Gurax_DeclareFunctionAlias(glfwGetJoystickButtons_gurax, "glfwGetJoystickButtons")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetJoystickButtons_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int jid = args_gurax.PickNumber<int>();
	// Function body
	int count;
	if (const unsigned char* rtn = glfwGetJoystickButtons(jid, &count)) {
		return Value_Tuple::Create(rtn, count);
	}
	return Value::nil();
}

// glfw.glfwGetJoystickHats(jid as Number)
Gurax_DeclareFunctionAlias(glfwGetJoystickHats_gurax, "glfwGetJoystickHats")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetJoystickHats_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int jid = args_gurax.PickNumber<int>();
	// Function body
	int count;
	if (const unsigned char* rtn = glfwGetJoystickHats(jid, &count)) {
		return Value_Tuple::Create(rtn, count);
	}
	return Value::nil();
}

// glfw.glfwGetJoystickName(jid as Number)
Gurax_DeclareFunctionAlias(glfwGetJoystickName_gurax, "glfwGetJoystickName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetJoystickName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int jid = args_gurax.PickNumber<int>();
	// Function body
	if (const char* rtn = glfwGetJoystickName(jid)) {
		return new Gurax::Value_String(rtn);
	}
	return Gurax::Value::nil();
}

// glfw.glfwGetJoystickGUID(jid as Number)
Gurax_DeclareFunctionAlias(glfwGetJoystickGUID_gurax, "glfwGetJoystickGUID")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetJoystickGUID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int jid = args_gurax.PickNumber<int>();
	// Function body
	if (const char* rtn = glfwGetJoystickGUID(jid)) {
		return new Gurax::Value_String(rtn);
	}
	return Gurax::Value::nil();
}

// glfw.glfwJoystickIsGamepad(jid as Number)
Gurax_DeclareFunctionAlias(glfwJoystickIsGamepad_gurax, "glfwJoystickIsGamepad")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwJoystickIsGamepad_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int jid = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = (glfwJoystickIsGamepad(jid) == GLFW_TRUE);
	return new Gurax::Value_Bool(rtn);
}

// glfw.glfwSetJoystickCallback(jid as Number, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetJoystickCallback_gurax, "glfwSetJoystickCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetJoystickCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int jid = args_gurax.PickNumber<int>();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	//glfwSetJoystickCallback(jid,
	//		callback? Value_GLFWwindow::callback_JoystickCallback : nullptr);
	//valueThis.SetFunc_JoystickCallback(callback.release());
	return Value::nil();
}

// glfw.glfwUpdateGamepadMappings(string as String)
Gurax_DeclareFunctionAlias(glfwUpdateGamepadMappings_gurax, "glfwUpdateGamepadMappings")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("string", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwUpdateGamepadMappings_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* string = args_gurax.PickString();
	// Function body
	if (glfwUpdateGamepadMappings(string) != GLFW_TRUE) IssueError();
	return Gurax::Value::nil();
}

// glfw.glfwGetGamepadName(jid as Number)
Gurax_DeclareFunctionAlias(glfwGetGamepadName_gurax, "glfwGetGamepadName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetGamepadName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int jid = args_gurax.PickNumber<int>();
	// Function body
	if (const char* rtn = glfwGetGamepadName(jid)) {
		return new Gurax::Value_String(rtn);
	}
	return Gurax::Value::nil();
}

// glfw.glfwSetClipboardString(window as glfw.GLFWwindow, string as String)
Gurax_DeclareFunctionAlias(glfwSetClipboardString_gurax, "glfwSetClipboardString")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("string", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSetClipboardString_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	const char* string = args_gurax.PickString();
	// Function body
	glfwSetClipboardString(window, string);
	return Gurax::Value::nil();
}

// glfw.glfwGetClipboardString(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetClipboardString_gurax, "glfwGetClipboardString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetClipboardString_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	if (const char* rtn = glfwGetClipboardString(window)) {
		return new Gurax::Value_String(rtn);
	}
	return Gurax::Value::nil();
}

// glfw.glfwGetTime()
Gurax_DeclareFunctionAlias(glfwGetTime_gurax, "glfwGetTime")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(glfwGetTime_gurax, processor_gurax, argument_gurax)
{
	// Function body
	double rtn = glfwGetTime();
	return new Gurax::Value_Number(rtn);
}

// glfw.glfwSetTime(time as Number)
Gurax_DeclareFunctionAlias(glfwSetTime_gurax, "glfwSetTime")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("time", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSetTime_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	double time = args_gurax.PickNumber<double>();
	// Function body
	glfwSetTime(time);
	return Gurax::Value::nil();
}

// glfw.glfwGetTimerValue()
Gurax_DeclareFunctionAlias(glfwGetTimerValue_gurax, "glfwGetTimerValue")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(glfwGetTimerValue_gurax, processor_gurax, argument_gurax)
{
	// Function body
	uint64_t rtn = glfwGetTimerValue();
	return new Gurax::Value_Number(rtn);
}

// glfw.glfwGetTimerFrequency()
Gurax_DeclareFunctionAlias(glfwGetTimerFrequency_gurax, "glfwGetTimerFrequency")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(glfwGetTimerFrequency_gurax, processor_gurax, argument_gurax)
{
	// Function body
	uint64_t rtn = glfwGetTimerFrequency();
	return new Gurax::Value_Number(rtn);
}

// glfw.glfwGetMonitors()
Gurax_DeclareFunctionAlias(glfwGetMonitors_gurax, "glfwGetMonitors")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementFunctionEx(glfwGetMonitors_gurax, processor_gurax, argument_gurax)
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
}

Gurax_ImplementFunctionEx(glfwGetPrimaryMonitor_gurax, processor_gurax, argument_gurax)
{
	// Function body
	if (GLFWmonitor* rtn = glfwGetPrimaryMonitor()) {
		return new Value_GLFWmonitor(rtn);
	}
	IssueError();
	return Gurax::Value::nil();
}

// glfw.glfwGetMonitorPos(monitor as glfw.GLFWmonitor)
Gurax_DeclareFunctionAlias(glfwGetMonitorPos_gurax, "glfwGetMonitorPos")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetMonitorPos_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWmonitor* monitor = args_gurax.Pick<Value_GLFWmonitor>().GetEntity();
	// Function body
	int xpos, ypos;
	glfwGetMonitorPos(monitor, &xpos, &ypos);
	return Value_Tuple::Create(new Value_Number(xpos), new Value_Number(ypos));
}

// glfw.glfwGetMonitorWorkarea(monitor as glfw.GLFWmonitor)
Gurax_DeclareFunctionAlias(glfwGetMonitorWorkarea_gurax, "glfwGetMonitorWorkarea")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetMonitorWorkarea_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWmonitor* monitor = args_gurax.Pick<Value_GLFWmonitor>().GetEntity();
	// Function body
	int xpos, ypos, width, height;
	glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);
	return Value_Tuple::Create(new Value_Number(xpos), new Value_Number(ypos),
						new Value_Number(width), new Value_Number(height));
}

// glfw.glfwGetMonitorPhysicalSize(monitor as glfw.GLFWmonitor)
Gurax_DeclareFunctionAlias(glfwGetMonitorPhysicalSize_gurax, "glfwGetMonitorPhysicalSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetMonitorPhysicalSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWmonitor* monitor = args_gurax.Pick<Value_GLFWmonitor>().GetEntity();
	// Function body
	int widthMM, heightMM;
	glfwGetMonitorPhysicalSize(monitor, &widthMM, &heightMM);
	return Value_Tuple::Create(new Value_Number(widthMM), new Value_Number(heightMM));
}

// glfw.glfwGetMonitorContentScale(monitor as glfw.GLFWmonitor)
Gurax_DeclareFunctionAlias(glfwGetMonitorContentScale_gurax, "glfwGetMonitorContentScale")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetMonitorContentScale_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWmonitor* monitor = args_gurax.Pick<Value_GLFWmonitor>().GetEntity();
	// Function body
	float xscale, yscale;
	glfwGetMonitorContentScale(monitor, &xscale, &yscale);
	return Value_Tuple::Create(new Value_Number(xscale), new Value_Number(yscale));
}

// glfw.glfwGetMonitorName(monitor as glfw.GLFWmonitor)
Gurax_DeclareFunctionAlias(glfwGetMonitorName_gurax, "glfwGetMonitorName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetMonitorName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWmonitor* monitor = args_gurax.Pick<Value_GLFWmonitor>().GetEntity();
	// Function body
	const char* rtn = glfwGetMonitorName(monitor);
	return new Gurax::Value_String(rtn);
}

// glfw.glfwSetMonitorCallback(callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetMonitorCallback_gurax, "glfwSetMonitorCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetMonitorCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	glfwSetMonitorCallback(callback? callback_MonitorCallback : nullptr);
	g_pProcessor_MonitorCallback.reset(callback? processor_gurax.Reference() : nullptr);
	g_pFunc_MonitorCallback.reset(callback.release());
	return Value::nil();
}

// glfw.glfwGetVideoModes(monitor as glfw.GLFWmonitor)
Gurax_DeclareFunctionAlias(glfwGetVideoModes_gurax, "glfwGetVideoModes")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetVideoModes_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWmonitor* monitor = args_gurax.Pick<Value_GLFWmonitor>().GetEntity();
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

// glfw.glfwGetVideoMode(monitor as glfw.GLFWmonitor)
Gurax_DeclareFunctionAlias(glfwGetVideoMode_gurax, "glfwGetVideoMode")
{
	Declare(VTYPE_GLFWvidmode, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetVideoMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWmonitor* monitor = args_gurax.Pick<Value_GLFWmonitor>().GetEntity();
	// Function body
	if (const GLFWvidmode* rtn = glfwGetVideoMode(monitor)) {
		return new Value_GLFWvidmode(rtn);
	}
	IssueError();
	return Gurax::Value::nil();
}

// glfw.glfwSetGamma(monitor as glfw.GLFWmonitor, gamma as Number)
Gurax_DeclareFunctionAlias(glfwSetGamma_gurax, "glfwSetGamma")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	DeclareArg("gamma", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSetGamma_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWmonitor* monitor = args_gurax.Pick<Value_GLFWmonitor>().GetEntity();
	float gamma = args_gurax.PickNumber<float>();
	// Function body
	glfwSetGamma(monitor, gamma);
	return Gurax::Value::nil();
}

// glfw.glfwGetGammaRamp(monitor as glfw.GLFWmonitor)
Gurax_DeclareFunctionAlias(glfwGetGammaRamp_gurax, "glfwGetGammaRamp")
{
	Declare(VTYPE_GLFWgammaramp, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetGammaRamp_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWmonitor* monitor = args_gurax.Pick<Value_GLFWmonitor>().GetEntity();
	// Function body
	if (const GLFWgammaramp* rtn = glfwGetGammaRamp(monitor)) {
		return new Value_GLFWgammaramp(rtn);
	}
	IssueError();
	return Gurax::Value::nil();
}

// glfw.glfwSetGammaRamp(monitor as glfw.GLFWmonitor, ramp as glfw.GLFWgammaramp)
Gurax_DeclareFunctionAlias(glfwSetGammaRamp_gurax, "glfwSetGammaRamp")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ramp", VTYPE_GLFWgammaramp, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSetGammaRamp_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWmonitor* monitor = args_gurax.Pick<Value_GLFWmonitor>().GetEntity();
	const GLFWgammaramp* ramp = args_gurax.Pick<Value_GLFWgammaramp>().GetEntity();
	// Function body
	glfwSetGammaRamp(monitor, ramp);
	return Gurax::Value::nil();
}

// glfw.glfwVulkanSupported()
Gurax_DeclareFunctionAlias(glfwVulkanSupported_gurax, "glfwVulkanSupported")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(glfwVulkanSupported_gurax, processor_gurax, argument_gurax)
{
	// Function body
	bool rtn = (glfwVulkanSupported() == GLFW_TRUE);
	return new Gurax::Value_Bool(rtn);
}

// glfw.glfwGetRequiredInstanceExtensions()
Gurax_DeclareFunctionAlias(glfwGetRequiredInstanceExtensions_gurax, "glfwGetRequiredInstanceExtensions")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementFunctionEx(glfwGetRequiredInstanceExtensions_gurax, processor_gurax, argument_gurax)
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
}

Gurax_ImplementFunctionEx(glfwDefaultWindowHints_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glfwDefaultWindowHints();
	return Gurax::Value::nil();
}

// glfw.glfwWindowHint(hint as Number, value as Number)
Gurax_DeclareFunctionAlias(glfwWindowHint_gurax, "glfwWindowHint")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("hint", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwWindowHint_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int hint = args_gurax.PickNumber<int>();
	int value = args_gurax.PickNumber<int>();
	// Function body
	glfwWindowHint(hint, value);
	return Gurax::Value::nil();
}

// glfw.glfwWindowHintString(hint as Number, value as String)
Gurax_DeclareFunctionAlias(glfwWindowHintString_gurax, "glfwWindowHintString")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("hint", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwWindowHintString_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int hint = args_gurax.PickNumber<int>();
	const char* value = args_gurax.PickString();
	// Function body
	glfwWindowHintString(hint, value);
	return Gurax::Value::nil();
}

// glfw.glfwCreateWindow(width as Number, height as Number, title as String, monitor:nil as glfw.GLFWmonitor, share:nil as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwCreateWindow_gurax, "glfwCreateWindow")
{
	Declare(VTYPE_GLFWwindow, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("share", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwCreateWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	const char* title = args_gurax.PickString();
	GLFWmonitor* monitor = args_gurax.IsValid()? args_gurax.Pick<Value_GLFWmonitor>().GetEntity() : nullptr;
	GLFWwindow* share = args_gurax.IsValid()? args_gurax.Pick<Value_GLFWwindow>().GetEntity() : nullptr;
	// Function body
	if (GLFWwindow* rtn = glfwCreateWindow(width, height, title, monitor, share)) {
		return new Value_GLFWwindow(rtn, processor_gurax.Reference());
	}
	IssueError();
	return Gurax::Value::nil();
}

// glfw.glfwDestroyWindow(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwDestroyWindow_gurax, "glfwDestroyWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwDestroyWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwDestroyWindow(window);
	return Gurax::Value::nil();
}

// glfw.glfwWindowShouldClose(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwWindowShouldClose_gurax, "glfwWindowShouldClose")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwWindowShouldClose_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	bool rtn = glfwWindowShouldClose(window);
	return new Gurax::Value_Bool(rtn);
}

// glfw.glfwSetWindowShouldClose(window as glfw.GLFWwindow, value as Bool)
Gurax_DeclareFunctionAlias(glfwSetWindowShouldClose_gurax, "glfwSetWindowShouldClose")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSetWindowShouldClose_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	bool value = args_gurax.PickBool();
	// Function body
	glfwSetWindowShouldClose(window, value);
	return Gurax::Value::nil();
}

// glfw.glfwSetWindowTitle(window as glfw.GLFWwindow, title as String)
Gurax_DeclareFunctionAlias(glfwSetWindowTitle_gurax, "glfwSetWindowTitle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSetWindowTitle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	const char* title = args_gurax.PickString();
	// Function body
	glfwSetWindowTitle(window, title);
	return Gurax::Value::nil();
}

// glfw.glfwSetWindowIcon(window as glfw.GLFWwindow, images[] as glfw.GLFWimage)
Gurax_DeclareFunctionAlias(glfwSetWindowIcon_gurax, "glfwSetWindowIcon")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("images", VTYPE_GLFWimage, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementFunctionEx(glfwSetWindowIcon_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	auto images = args_gurax.PickListT<GLFWimage>(Value_GLFWimage::ValueForVector);
	// Function body
	glfwSetWindowIcon(window, static_cast<int>(images.size()), images.data());
	return Value::nil();
}

// glfw.glfwGetWindowPos(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetWindowPos_gurax, "glfwGetWindowPos")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetWindowPos_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	int xpos, ypos;
	glfwGetWindowPos(window, &xpos, &ypos);
	return Value_Tuple::Create(new Value_Number(xpos), new Value_Number(ypos));
}

// glfw.glfwSetWindowPos(window as glfw.GLFWwindow, xpos as Number, ypos as Number)
Gurax_DeclareFunctionAlias(glfwSetWindowPos_gurax, "glfwSetWindowPos")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xpos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ypos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSetWindowPos_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	int xpos = args_gurax.PickNumber<int>();
	int ypos = args_gurax.PickNumber<int>();
	// Function body
	glfwSetWindowPos(window, xpos, ypos);
	return Gurax::Value::nil();
}

// glfw.glfwGetWindowSize(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetWindowSize_gurax, "glfwGetWindowSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetWindowSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return Value_Tuple::Create(new Value_Number(width), new Value_Number(height));
}

// glfw.glfwSetWindowSizeLimits(window as glfw.GLFWwindow, minwidth as Number, minheight as Number, maxwidth as Number, maxheight as Number)
Gurax_DeclareFunctionAlias(glfwSetWindowSizeLimits_gurax, "glfwSetWindowSizeLimits")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("minwidth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("minheight", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxwidth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxheight", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSetWindowSizeLimits_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	int minwidth = args_gurax.PickNumber<int>();
	int minheight = args_gurax.PickNumber<int>();
	int maxwidth = args_gurax.PickNumber<int>();
	int maxheight = args_gurax.PickNumber<int>();
	// Function body
	glfwSetWindowSizeLimits(window, minwidth, minheight, maxwidth, maxheight);
	return Gurax::Value::nil();
}

// glfw.glfwSetWindowAspectRatio(window as glfw.GLFWwindow, numer as Number, denom as Number)
Gurax_DeclareFunctionAlias(glfwSetWindowAspectRatio_gurax, "glfwSetWindowAspectRatio")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("numer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("denom", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSetWindowAspectRatio_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	int numer = args_gurax.PickNumber<int>();
	int denom = args_gurax.PickNumber<int>();
	// Function body
	glfwSetWindowAspectRatio(window, numer, denom);
	return Gurax::Value::nil();
}

// glfw.glfwSetWindowSize(window as glfw.GLFWwindow, width as Number, height as Number)
Gurax_DeclareFunctionAlias(glfwSetWindowSize_gurax, "glfwSetWindowSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSetWindowSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	// Function body
	glfwSetWindowSize(window, width, height);
	return Gurax::Value::nil();
}

// glfw.glfwGetFramebufferSize(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetFramebufferSize_gurax, "glfwGetFramebufferSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetFramebufferSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	return Value_Tuple::Create(new Value_Number(width), new Value_Number(height));
}

// glfw.glfwGetWindowFrameSize(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetWindowFrameSize_gurax, "glfwGetWindowFrameSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetWindowFrameSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	int left, top, right, bottom;
	glfwGetWindowFrameSize(window, &left, &top, &right, &bottom);
	return Value_Tuple::Create(new Value_Number(left), new Value_Number(top),
							new Value_Number(right), new Value_Number(bottom));
}

// glfw.glfwGetWindowContentScale(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetWindowContentScale_gurax, "glfwGetWindowContentScale")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetWindowContentScale_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	float xscale, yscale;
	glfwGetWindowContentScale(window, &xscale, &yscale);
	return Value_Tuple::Create(new Value_Number(xscale), new Value_Number(yscale));
}

// glfw.glfwGetWindowOpacity(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetWindowOpacity_gurax, "glfwGetWindowOpacity")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetWindowOpacity_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	float rtn = glfwGetWindowOpacity(window);
	return new Gurax::Value_Number(rtn);
}

// glfw.glfwSetWindowOpacity(window as glfw.GLFWwindow, opacity as Number)
Gurax_DeclareFunctionAlias(glfwSetWindowOpacity_gurax, "glfwSetWindowOpacity")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("opacity", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSetWindowOpacity_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	float opacity = args_gurax.PickNumber<float>();
	// Function body
	glfwSetWindowOpacity(window, opacity);
	return Gurax::Value::nil();
}

// glfw.glfwIconifyWindow(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwIconifyWindow_gurax, "glfwIconifyWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwIconifyWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwIconifyWindow(window);
	return Gurax::Value::nil();
}

// glfw.glfwRestoreWindow(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwRestoreWindow_gurax, "glfwRestoreWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwRestoreWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwRestoreWindow(window);
	return Gurax::Value::nil();
}

// glfw.glfwMaximizeWindow(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwMaximizeWindow_gurax, "glfwMaximizeWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwMaximizeWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwMaximizeWindow(window);
	return Gurax::Value::nil();
}

// glfw.glfwShowWindow(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwShowWindow_gurax, "glfwShowWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwShowWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwShowWindow(window);
	return Gurax::Value::nil();
}

// glfw.glfwHideWindow(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwHideWindow_gurax, "glfwHideWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwHideWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwHideWindow(window);
	return Gurax::Value::nil();
}

// glfw.glfwFocusWindow(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwFocusWindow_gurax, "glfwFocusWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwFocusWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwFocusWindow(window);
	return Gurax::Value::nil();
}

// glfw.glfwRequestWindowAttention(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwRequestWindowAttention_gurax, "glfwRequestWindowAttention")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwRequestWindowAttention_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwRequestWindowAttention(window);
	return Gurax::Value::nil();
}

// glfw.glfwGetWindowMonitor(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwGetWindowMonitor_gurax, "glfwGetWindowMonitor")
{
	Declare(VTYPE_GLFWmonitor, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetWindowMonitor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	if (GLFWmonitor* rtn = glfwGetWindowMonitor(window)) {
		return new Value_GLFWmonitor(rtn);
	}
	IssueError();
	return Gurax::Value::nil();
}

// glfw.glfwSetWindowMonitor(window as glfw.GLFWwindow, monitor as glfw.GLFWmonitor, xpos as Number, ypos as Number, width as Number, height as Number, refreshRate as Number)
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
}

Gurax_ImplementFunctionEx(glfwSetWindowMonitor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	GLFWmonitor* monitor = args_gurax.Pick<Value_GLFWmonitor>().GetEntity();
	int xpos = args_gurax.PickNumber<int>();
	int ypos = args_gurax.PickNumber<int>();
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	int refreshRate = args_gurax.PickNumber<int>();
	// Function body
	glfwSetWindowMonitor(window, monitor, xpos, ypos, width, height, refreshRate);
	return Gurax::Value::nil();
}

// glfw.glfwGetWindowAttrib(window as glfw.GLFWwindow, attrib as Number)
Gurax_DeclareFunctionAlias(glfwGetWindowAttrib_gurax, "glfwGetWindowAttrib")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attrib", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwGetWindowAttrib_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	int attrib = args_gurax.PickNumber<int>();
	// Function body
	int rtn = glfwGetWindowAttrib(window, attrib);
	return new Gurax::Value_Number(rtn);
}

// glfw.glfwSetWindowAttrib(window as glfw.GLFWwindow, attrib as Number, value as Number)
Gurax_DeclareFunctionAlias(glfwSetWindowAttrib_gurax, "glfwSetWindowAttrib")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attrib", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSetWindowAttrib_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	int attrib = args_gurax.PickNumber<int>();
	int value = args_gurax.PickNumber<int>();
	// Function body
	glfwSetWindowAttrib(window, attrib, value);
	return Gurax::Value::nil();
}

// glfw.glfwSetWindowPosCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetWindowPosCallback_gurax, "glfwSetWindowPosCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetWindowPosCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetWindowPosCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_WindowPosCallback : nullptr);
	valueThis.SetFunc_WindowPosCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetWindowSizeCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetWindowSizeCallback_gurax, "glfwSetWindowSizeCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetWindowSizeCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetWindowSizeCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_WindowSizeCallback : nullptr);
	valueThis.SetFunc_WindowSizeCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetWindowCloseCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetWindowCloseCallback_gurax, "glfwSetWindowCloseCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetWindowCloseCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetWindowCloseCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_WindowCloseCallback : nullptr);
	valueThis.SetFunc_WindowCloseCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetWindowRefreshCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetWindowRefreshCallback_gurax, "glfwSetWindowRefreshCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetWindowRefreshCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetWindowRefreshCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_WindowRefreshCallback : nullptr);
	valueThis.SetFunc_WindowRefreshCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetWindowFocusCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetWindowFocusCallback_gurax, "glfwSetWindowFocusCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetWindowFocusCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetWindowFocusCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_WindowFocusCallback : nullptr);
	valueThis.SetFunc_WindowFocusCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetWindowIconifyCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetWindowIconifyCallback_gurax, "glfwSetWindowIconifyCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetWindowIconifyCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetWindowIconifyCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_WindowIconifyCallback : nullptr);
	valueThis.SetFunc_WindowIconifyCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetWindowMaximizeCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetWindowMaximizeCallback_gurax, "glfwSetWindowMaximizeCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetWindowMaximizeCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetWindowMaximizeCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_WindowMaximizeCallback : nullptr);
	valueThis.SetFunc_WindowMaximizeCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetFramebufferSizeCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetFramebufferSizeCallback_gurax, "glfwSetFramebufferSizeCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetFramebufferSizeCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetFramebufferSizeCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_FramebufferSizeCallback : nullptr);
	valueThis.SetFunc_FramebufferSizeCallback(callback.release());
	return Value::nil();
}

// glfw.glfwSetWindowContentScaleCallback(window as glfw.GLFWwindow, callback:nil as Function)
Gurax_DeclareFunctionAlias(glfwSetWindowContentScaleCallback_gurax, "glfwSetWindowContentScaleCallback")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(glfwSetWindowContentScaleCallback_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	RefPtr<Function> callback(args_gurax.IsValid()? args_gurax.PickFunction().Reference() : nullptr);
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
}

Gurax_ImplementFunctionEx(glfwPollEvents_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glfwPollEvents();
	return Gurax::Value::nil();
}

// glfw.glfwWaitEvents()
Gurax_DeclareFunctionAlias(glfwWaitEvents_gurax, "glfwWaitEvents")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(glfwWaitEvents_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glfwWaitEvents();
	return Gurax::Value::nil();
}

// glfw.glfwWaitEventsTimeout(timeout as Number)
Gurax_DeclareFunctionAlias(glfwWaitEventsTimeout_gurax, "glfwWaitEventsTimeout")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("timeout", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwWaitEventsTimeout_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	double timeout = args_gurax.PickNumber<double>();
	// Function body
	glfwWaitEventsTimeout(timeout);
	return Gurax::Value::nil();
}

// glfw.glfwPostEmptyEvent()
Gurax_DeclareFunctionAlias(glfwPostEmptyEvent_gurax, "glfwPostEmptyEvent")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(glfwPostEmptyEvent_gurax, processor_gurax, argument_gurax)
{
	// Function body
	glfwPostEmptyEvent();
	return Gurax::Value::nil();
}

// glfw.glfwSwapBuffers(window as glfw.GLFWwindow)
Gurax_DeclareFunctionAlias(glfwSwapBuffers_gurax, "glfwSwapBuffers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(glfwSwapBuffers_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	GLFWwindow* window = args_gurax.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwSwapBuffers(window);
	return Gurax::Value::nil();
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
