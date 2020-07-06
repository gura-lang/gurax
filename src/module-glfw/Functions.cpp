//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glfw)

// glfw.glfwMakeContextCurrent(window:glfw.GLFWwindow)
Gurax_DeclareFunction(glfwMakeContextCurrent)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwMakeContextCurrent)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwMakeContextCurrent(window);
	return Value::nil();
}

// glfw.glfwGetCurrentContext()
Gurax_DeclareFunction(glfwGetCurrentContext)
{
	Declare(VTYPE_GLFWwindow, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetCurrentContext)
{
	// Function body
	if (GLFWwindow* rtn = glfwGetCurrentContext()) {
		return new Value_GLFWwindow(rtn, processor.Reference());
	}
	IssueError();
	return Value::nil();
}

// glfw.glfwSwapInterval(interval:Number)
Gurax_DeclareFunction(glfwSwapInterval)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("interval", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSwapInterval)
{
	// Arguments
	ArgPicker args(argument);
	int interval = args.PickNumber<int>();
	// Function body
	glfwSwapInterval(interval);
	return Value::nil();
}

// glfw.glfwExtensionSupported(extension:String)
Gurax_DeclareFunction(glfwExtensionSupported)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("extension", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwExtensionSupported)
{
	// Arguments
	ArgPicker args(argument);
	const char* extension = args.PickString();
	// Function body
	bool rtn =(glfwExtensionSupported(extension) == GLFW_TRUE);
	return new Value_Bool(rtn);
}

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
	if (glfwInit() != GLFW_TRUE) IssueError();
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
	glfwTerminate();
	return Value::nil();
}

// glfw.glfwInitHint(hint:Number, value:Number)
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

// glfw.glfwGetVersion()
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

// glfw.glfwGetVersionString()
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

// glfw.glfwGetError()
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

// glfw.glfwSetErrorCallback()
Gurax_DeclareFunction(glfwSetErrorCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetErrorCallback)
{
	// Function body
	//Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetErrorCallback(callback? Value_GLFWwindow::callback_ErrorCallback : nullptr);
	//valueThis.SetFunc_ErrorCallback(callback.release());
	return Value::nil();
}

// glfw.glfwGetInputMode(window:glfw.GLFWwindow, mode:Number)
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

// glfw.glfwSetInputMode(window:glfw.GLFWwindow, mode:Number, value:Number)
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

// glfw.glfwRawMouseMotionSupported()
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
	bool rtn =(glfwRawMouseMotionSupported() == GLFW_TRUE);
	return new Value_Bool(rtn);
}

// glfw.glfwGetKeyName(key:Number, scancode:Number)
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

// glfw.glfwGetKeyScancode(key:Number)
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

// glfw.glfwGetKey(window:glfw.GLFWwindow, key:Number)
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

// glfw.glfwGetMouseButton(window:glfw.GLFWwindow, button:Number)
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

// glfw.glfwGetCursorPos(window:glfw.GLFWwindow)
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

// glfw.glfwSetCursorPos(window:glfw.GLFWwindow, xpos:Number, ypos:Number)
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

// glfw.glfwCreateCursor(image:glfw.GLFWimage, xhot:Number, yhot:Number)
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

// glfw.glfwCreateStandardCursor(shape:Number)
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

// glfw.glfwDestroyCursor(cursor:glfw.GLFWcursor)
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

// glfw.glfwSetCursor(window:glfw.GLFWwindow, cursor:glfw.GLFWcursor)
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

// glfw.glfwSetKeyCallback(window:glfw.GLFWwindow, callback:Function:nil)
Gurax_DeclareFunction(glfwSetKeyCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetKeyCallback)
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
Gurax_DeclareFunction(glfwSetCharCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetCharCallback)
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
Gurax_DeclareFunction(glfwSetCharModsCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetCharModsCallback)
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
Gurax_DeclareFunction(glfwSetMouseButtonCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetMouseButtonCallback)
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
Gurax_DeclareFunction(glfwSetCursorPosCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetCursorPosCallback)
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
Gurax_DeclareFunction(glfwSetCursorEnterCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetCursorEnterCallback)
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
Gurax_DeclareFunction(glfwSetScrollCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetScrollCallback)
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
Gurax_DeclareFunction(glfwSetDropCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetDropCallback)
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

// glfw.glfwGetJoystickAxes(jid:Number)
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

// glfw.glfwGetJoystickButtons(jid:Number)
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

// glfw.glfwGetJoystickHats(jid:Number)
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

// glfw.glfwGetJoystickName(jid:Number)
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

// glfw.glfwGetJoystickGUID(jid:Number)
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

// glfw.glfwJoystickIsGamepad(jid:Number)
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
	bool rtn =(glfwJoystickIsGamepad(jid) == GLFW_TRUE);
	return new Value_Bool(rtn);
}

// glfw.glfwSetJoystickCallback(jid:Number, callback:Function:nil)
Gurax_DeclareFunction(glfwSetJoystickCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("jid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetJoystickCallback)
{
	// Arguments
	ArgPicker args(argument);
	int jid = args.PickNumber<int>();
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	glfwSetJoystickCallback(jid,
			callback? Value_GLFWwindow::callback_JoystickCallback : nullptr);
	//valueThis.SetFunc_JoystickCallback(callback.release());
	return Value::nil();
}

// glfw.glfwUpdateGamepadMappings(string:String)
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

// glfw.glfwGetGamepadName(jid:Number)
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

// glfw.glfwSetClipboardString(window:glfw.GLFWwindow, string:String)
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

// glfw.glfwGetClipboardString(window:glfw.GLFWwindow)
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

// glfw.glfwGetTime()
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

// glfw.glfwSetTime(time:Number)
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

// glfw.glfwGetTimerValue()
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

// glfw.glfwGetTimerFrequency()
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

// glfw.glfwGetMonitors()
Gurax_DeclareFunction(glfwGetMonitors)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetMonitors)
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
Gurax_DeclareFunction(glfwGetPrimaryMonitor)
{
	Declare(VTYPE_GLFWmonitor, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetPrimaryMonitor)
{
	// Function body
	if (GLFWmonitor* rtn = glfwGetPrimaryMonitor()) {
		return new Value_GLFWmonitor(rtn);
	}
	IssueError();
	return Value::nil();
}

// glfw.glfwGetMonitorPos(monitor:glfw.GLFWmonitor)
Gurax_DeclareFunction(glfwGetMonitorPos)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetMonitorPos)
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
Gurax_DeclareFunction(glfwGetMonitorWorkarea)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetMonitorWorkarea)
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
Gurax_DeclareFunction(glfwGetMonitorPhysicalSize)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetMonitorPhysicalSize)
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
Gurax_DeclareFunction(glfwGetMonitorContentScale)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetMonitorContentScale)
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
Gurax_DeclareFunction(glfwGetMonitorName)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetMonitorName)
{
	// Arguments
	ArgPicker args(argument);
	GLFWmonitor* monitor = args.Pick<Value_GLFWmonitor>().GetEntity();
	// Function body
	const char* rtn = glfwGetMonitorName(monitor);
	return new Value_String(rtn);
}

// glfw.glfwSetMonitorCallback(callback:Function:nil)
Gurax_DeclareFunction(glfwSetMonitorCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetMonitorCallback)
{
	// Arguments
	ArgPicker args(argument);
	RefPtr<Function> callback(args.IsValid()? args.PickFunction().Reference() : nullptr);
	// Function body
	Value_GLFWwindow& valueThis = Value_GLFWwindow::GetValue(window);
	glfwSetMonitorCallback(valueThis.GetEntity(),
			callback? Value_GLFWwindow::callback_MonitorCallback : nullptr);
	valueThis.SetFunc_MonitorCallback(callback.release());
	return Value::nil();
}

// glfw.glfwGetVideoModes(monitor:glfw.GLFWmonitor)
Gurax_DeclareFunction(glfwGetVideoModes)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetVideoModes)
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
Gurax_DeclareFunction(glfwGetVideoMode)
{
	Declare(VTYPE_GLFWvidmode, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetVideoMode)
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
Gurax_DeclareFunction(glfwSetGamma)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	DeclareArg("gamma", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetGamma)
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
Gurax_DeclareFunction(glfwGetGammaRamp)
{
	Declare(VTYPE_GLFWgammaramp, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetGammaRamp)
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
Gurax_DeclareFunction(glfwSetGammaRamp)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("monitor", VTYPE_GLFWmonitor, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ramp", VTYPE_GLFWgammaramp, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetGammaRamp)
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
Gurax_DeclareFunction(glfwVulkanSupported)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwVulkanSupported)
{
	// Function body
	bool rtn =(glfwVulkanSupported() == GLFW_TRUE);
	return new Value_Bool(rtn);
}

// glfw.glfwGetRequiredInstanceExtensions()
Gurax_DeclareFunction(glfwGetRequiredInstanceExtensions)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetRequiredInstanceExtensions)
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

// glfw.glfwWindowHint(hint:Number, value:Number)
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

// glfw.glfwWindowHintString(hint:Number, value:String)
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

// glfw.glfwCreateWindow(width:Number, height:Number, title:String, monitor:glfw.GLFWmonitor:nil, share:glfw.GLFWwindow:nil)
Gurax_DeclareFunction(glfwCreateWindow)
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

Gurax_ImplementFunction(glfwCreateWindow)
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

// glfw.glfwWindowShouldClose(window:glfw.GLFWwindow)
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

// glfw.glfwSetWindowShouldClose(window:glfw.GLFWwindow, value:Bool)
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

// glfw.glfwSetWindowTitle(window:glfw.GLFWwindow, title:String)
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

// glfw.glfwSetWindowIcon(window:glfw.GLFWwindow, images[]:glfw.GLFWimage)
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

// glfw.glfwGetWindowPos(window:glfw.GLFWwindow)
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

// glfw.glfwSetWindowPos(window:glfw.GLFWwindow, xpos:Number, ypos:Number)
Gurax_DeclareFunction(glfwSetWindowPos)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xpos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ypos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowPos)
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
Gurax_DeclareFunction(glfwGetWindowSize)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetWindowSize)
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
Gurax_DeclareFunction(glfwSetWindowSizeLimits)
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

Gurax_ImplementFunction(glfwSetWindowSizeLimits)
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
Gurax_DeclareFunction(glfwSetWindowAspectRatio)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("numer", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("denom", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowAspectRatio)
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
Gurax_DeclareFunction(glfwSetWindowSize)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowSize)
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
Gurax_DeclareFunction(glfwGetFramebufferSize)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetFramebufferSize)
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
Gurax_DeclareFunction(glfwGetWindowFrameSize)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetWindowFrameSize)
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
Gurax_DeclareFunction(glfwGetWindowContentScale)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetWindowContentScale)
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
Gurax_DeclareFunction(glfwGetWindowOpacity)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetWindowOpacity)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	float rtn = glfwGetWindowOpacity(window);
	return new Value_Number(rtn);
}

// glfw.glfwSetWindowOpacity(window:glfw.GLFWwindow, opacity:Number)
Gurax_DeclareFunction(glfwSetWindowOpacity)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("opacity", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowOpacity)
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
Gurax_DeclareFunction(glfwIconifyWindow)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwIconifyWindow)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwIconifyWindow(window);
	return Value::nil();
}

// glfw.glfwRestoreWindow(window:glfw.GLFWwindow)
Gurax_DeclareFunction(glfwRestoreWindow)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwRestoreWindow)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwRestoreWindow(window);
	return Value::nil();
}

// glfw.glfwMaximizeWindow(window:glfw.GLFWwindow)
Gurax_DeclareFunction(glfwMaximizeWindow)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwMaximizeWindow)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwMaximizeWindow(window);
	return Value::nil();
}

// glfw.glfwShowWindow(window:glfw.GLFWwindow)
Gurax_DeclareFunction(glfwShowWindow)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwShowWindow)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwShowWindow(window);
	return Value::nil();
}

// glfw.glfwHideWindow(window:glfw.GLFWwindow)
Gurax_DeclareFunction(glfwHideWindow)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwHideWindow)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwHideWindow(window);
	return Value::nil();
}

// glfw.glfwFocusWindow(window:glfw.GLFWwindow)
Gurax_DeclareFunction(glfwFocusWindow)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwFocusWindow)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwFocusWindow(window);
	return Value::nil();
}

// glfw.glfwRequestWindowAttention(window:glfw.GLFWwindow)
Gurax_DeclareFunction(glfwRequestWindowAttention)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwRequestWindowAttention)
{
	// Arguments
	ArgPicker args(argument);
	GLFWwindow* window = args.Pick<Value_GLFWwindow>().GetEntity();
	// Function body
	glfwRequestWindowAttention(window);
	return Value::nil();
}

// glfw.glfwGetWindowMonitor(window:glfw.GLFWwindow)
Gurax_DeclareFunction(glfwGetWindowMonitor)
{
	Declare(VTYPE_GLFWmonitor, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetWindowMonitor)
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
Gurax_DeclareFunction(glfwSetWindowMonitor)
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

Gurax_ImplementFunction(glfwSetWindowMonitor)
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
Gurax_DeclareFunction(glfwGetWindowAttrib)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attrib", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwGetWindowAttrib)
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
Gurax_DeclareFunction(glfwSetWindowAttrib)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attrib", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowAttrib)
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
Gurax_DeclareFunction(glfwSetWindowPosCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowPosCallback)
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
Gurax_DeclareFunction(glfwSetWindowSizeCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowSizeCallback)
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
Gurax_DeclareFunction(glfwSetWindowCloseCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowCloseCallback)
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
Gurax_DeclareFunction(glfwSetWindowRefreshCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowRefreshCallback)
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
Gurax_DeclareFunction(glfwSetWindowFocusCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowFocusCallback)
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
Gurax_DeclareFunction(glfwSetWindowIconifyCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowIconifyCallback)
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
Gurax_DeclareFunction(glfwSetWindowMaximizeCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowMaximizeCallback)
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
Gurax_DeclareFunction(glfwSetFramebufferSizeCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetFramebufferSizeCallback)
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
Gurax_DeclareFunction(glfwSetWindowContentScaleCallback)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("callback", VTYPE_Function, ArgOccur::Once, ArgFlag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSetWindowContentScaleCallback)
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
Gurax_DeclareFunction(glfwPollEvents)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwPollEvents)
{
	// Function body
	glfwPollEvents();
	return Value::nil();
}

// glfw.glfwWaitEvents()
Gurax_DeclareFunction(glfwWaitEvents)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwWaitEvents)
{
	// Function body
	glfwWaitEvents();
	return Value::nil();
}

// glfw.glfwWaitEventsTimeout(timeout:Number)
Gurax_DeclareFunction(glfwWaitEventsTimeout)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("timeout", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwWaitEventsTimeout)
{
	// Arguments
	ArgPicker args(argument);
	double timeout = args.PickNumber<double>();
	// Function body
	glfwWaitEventsTimeout(timeout);
	return Value::nil();
}

// glfw.glfwPostEmptyEvent()
Gurax_DeclareFunction(glfwPostEmptyEvent)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwPostEmptyEvent)
{
	// Function body
	glfwPostEmptyEvent();
	return Value::nil();
}

// glfw.glfwSwapBuffers(window:glfw.GLFWwindow)
Gurax_DeclareFunction(glfwSwapBuffers)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_GLFWwindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(glfwSwapBuffers)
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
	frame.Assign(Gurax_CreateFunction(glfwMakeContextCurrent));
	frame.Assign(Gurax_CreateFunction(glfwGetCurrentContext));
	frame.Assign(Gurax_CreateFunction(glfwSwapInterval));
	frame.Assign(Gurax_CreateFunction(glfwExtensionSupported));
	frame.Assign(Gurax_CreateFunction(glfwInit));
	frame.Assign(Gurax_CreateFunction(glfwTerminate));
	frame.Assign(Gurax_CreateFunction(glfwInitHint));
	frame.Assign(Gurax_CreateFunction(glfwGetVersion));
	frame.Assign(Gurax_CreateFunction(glfwGetVersionString));
	frame.Assign(Gurax_CreateFunction(glfwGetError));
	frame.Assign(Gurax_CreateFunction(glfwSetErrorCallback));
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
	frame.Assign(Gurax_CreateFunction(glfwSetKeyCallback));
	frame.Assign(Gurax_CreateFunction(glfwSetCharCallback));
	frame.Assign(Gurax_CreateFunction(glfwSetCharModsCallback));
	frame.Assign(Gurax_CreateFunction(glfwSetMouseButtonCallback));
	frame.Assign(Gurax_CreateFunction(glfwSetCursorPosCallback));
	frame.Assign(Gurax_CreateFunction(glfwSetCursorEnterCallback));
	frame.Assign(Gurax_CreateFunction(glfwSetScrollCallback));
	frame.Assign(Gurax_CreateFunction(glfwSetDropCallback));
	frame.Assign(Gurax_CreateFunction(glfwJoystickPresent));
	frame.Assign(Gurax_CreateFunction(glfwGetJoystickAxes));
	frame.Assign(Gurax_CreateFunction(glfwGetJoystickButtons));
	frame.Assign(Gurax_CreateFunction(glfwGetJoystickHats));
	frame.Assign(Gurax_CreateFunction(glfwGetJoystickName));
	frame.Assign(Gurax_CreateFunction(glfwGetJoystickGUID));
	frame.Assign(Gurax_CreateFunction(glfwJoystickIsGamepad));
	frame.Assign(Gurax_CreateFunction(glfwSetJoystickCallback));
	frame.Assign(Gurax_CreateFunction(glfwUpdateGamepadMappings));
	frame.Assign(Gurax_CreateFunction(glfwGetGamepadName));
	frame.Assign(Gurax_CreateFunction(glfwSetClipboardString));
	frame.Assign(Gurax_CreateFunction(glfwGetClipboardString));
	frame.Assign(Gurax_CreateFunction(glfwGetTime));
	frame.Assign(Gurax_CreateFunction(glfwSetTime));
	frame.Assign(Gurax_CreateFunction(glfwGetTimerValue));
	frame.Assign(Gurax_CreateFunction(glfwGetTimerFrequency));
	frame.Assign(Gurax_CreateFunction(glfwGetMonitors));
	frame.Assign(Gurax_CreateFunction(glfwGetPrimaryMonitor));
	frame.Assign(Gurax_CreateFunction(glfwGetMonitorPos));
	frame.Assign(Gurax_CreateFunction(glfwGetMonitorWorkarea));
	frame.Assign(Gurax_CreateFunction(glfwGetMonitorPhysicalSize));
	frame.Assign(Gurax_CreateFunction(glfwGetMonitorContentScale));
	frame.Assign(Gurax_CreateFunction(glfwGetMonitorName));
	frame.Assign(Gurax_CreateFunction(glfwSetMonitorCallback));
	frame.Assign(Gurax_CreateFunction(glfwGetVideoModes));
	frame.Assign(Gurax_CreateFunction(glfwGetVideoMode));
	frame.Assign(Gurax_CreateFunction(glfwSetGamma));
	frame.Assign(Gurax_CreateFunction(glfwGetGammaRamp));
	frame.Assign(Gurax_CreateFunction(glfwSetGammaRamp));
	frame.Assign(Gurax_CreateFunction(glfwVulkanSupported));
	frame.Assign(Gurax_CreateFunction(glfwGetRequiredInstanceExtensions));
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
	frame.Assign(Gurax_CreateFunction(glfwSetWindowPos));
	frame.Assign(Gurax_CreateFunction(glfwGetWindowSize));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowSizeLimits));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowAspectRatio));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowSize));
	frame.Assign(Gurax_CreateFunction(glfwGetFramebufferSize));
	frame.Assign(Gurax_CreateFunction(glfwGetWindowFrameSize));
	frame.Assign(Gurax_CreateFunction(glfwGetWindowContentScale));
	frame.Assign(Gurax_CreateFunction(glfwGetWindowOpacity));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowOpacity));
	frame.Assign(Gurax_CreateFunction(glfwIconifyWindow));
	frame.Assign(Gurax_CreateFunction(glfwRestoreWindow));
	frame.Assign(Gurax_CreateFunction(glfwMaximizeWindow));
	frame.Assign(Gurax_CreateFunction(glfwShowWindow));
	frame.Assign(Gurax_CreateFunction(glfwHideWindow));
	frame.Assign(Gurax_CreateFunction(glfwFocusWindow));
	frame.Assign(Gurax_CreateFunction(glfwRequestWindowAttention));
	frame.Assign(Gurax_CreateFunction(glfwGetWindowMonitor));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowMonitor));
	frame.Assign(Gurax_CreateFunction(glfwGetWindowAttrib));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowAttrib));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowPosCallback));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowSizeCallback));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowCloseCallback));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowRefreshCallback));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowFocusCallback));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowIconifyCallback));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowMaximizeCallback));
	frame.Assign(Gurax_CreateFunction(glfwSetFramebufferSizeCallback));
	frame.Assign(Gurax_CreateFunction(glfwSetWindowContentScaleCallback));
	frame.Assign(Gurax_CreateFunction(glfwPollEvents));
	frame.Assign(Gurax_CreateFunction(glfwWaitEvents));
	frame.Assign(Gurax_CreateFunction(glfwWaitEventsTimeout));
	frame.Assign(Gurax_CreateFunction(glfwPostEmptyEvent));
	frame.Assign(Gurax_CreateFunction(glfwSwapBuffers));
}

Gurax_EndModuleScope(glfw)
