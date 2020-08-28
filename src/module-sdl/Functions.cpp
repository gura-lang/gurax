//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

// sdl.SDL_Init(flags:Number)
Gurax_DeclareFunctionAlias(SDL_Init_gurax, "SDL_Init")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_Init_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 flags = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_Init(flags);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_InitSubSystem(flags:Number)
Gurax_DeclareFunctionAlias(SDL_InitSubSystem_gurax, "SDL_InitSubSystem")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_InitSubSystem_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 flags = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_InitSubSystem(flags);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_QuitSubSystem(flags:Number)
Gurax_DeclareFunctionAlias(SDL_QuitSubSystem_gurax, "SDL_QuitSubSystem")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_QuitSubSystem_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 flags = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_QuitSubSystem(flags);
	return Gurax::Value::nil();
}

// sdl.SDL_WasInit(flags:Number)
Gurax_DeclareFunctionAlias(SDL_WasInit_gurax, "SDL_WasInit")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_WasInit_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 flags = args_gurax.PickNumber<Uint32>();
	// Function body
	Uint32 rtn = SDL_WasInit(flags);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_Quit()
Gurax_DeclareFunctionAlias(SDL_Quit_gurax, "SDL_Quit")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_Quit_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Quit();
	return Gurax::Value::nil();
}

// sdl.SDL_SetHintWithPriority(name:String, value:String, priority:Number)
Gurax_DeclareFunctionAlias(SDL_SetHintWithPriority_gurax, "SDL_SetHintWithPriority")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("priority", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetHintWithPriority_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	const char* value = args_gurax.PickString();
	SDL_HintPriority priority = args_gurax.PickNumber<SDL_HintPriority>();
	// Function body
	SDL_bool rtn = SDL_SetHintWithPriority(name, value, priority);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_SetHint(name:String, value:String)
Gurax_DeclareFunctionAlias(SDL_SetHint_gurax, "SDL_SetHint")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetHint_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	const char* value = args_gurax.PickString();
	// Function body
	SDL_bool rtn = SDL_SetHint(name, value);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_GetHint(name:String)
Gurax_DeclareFunctionAlias(SDL_GetHint_gurax, "SDL_GetHint")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetHint_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	// Function body
	const char* rtn = SDL_GetHint(name);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_GetHintBoolean(name:String, default_value:Bool)
Gurax_DeclareFunctionAlias(SDL_GetHintBoolean_gurax, "SDL_GetHintBoolean")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("default_value", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetHintBoolean_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	SDL_bool default_value = static_cast<SDL_bool>(args_gurax.PickBool());
	// Function body
	SDL_bool rtn = SDL_GetHintBoolean(name, default_value);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_ClearHints()
Gurax_DeclareFunctionAlias(SDL_ClearHints_gurax, "SDL_ClearHints")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_ClearHints_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_ClearHints();
	return Gurax::Value::nil();
}

// sdl.SDL_GetError()
Gurax_DeclareFunctionAlias(SDL_GetError_gurax, "SDL_GetError")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetError_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const char* rtn = SDL_GetError();
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_ClearError()
Gurax_DeclareFunctionAlias(SDL_ClearError_gurax, "SDL_ClearError")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_ClearError_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_ClearError();
	return Gurax::Value::nil();
}

// sdl.SDL_Error(code:Number)
Gurax_DeclareFunctionAlias(SDL_Error_gurax, "SDL_Error")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("code", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_Error_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_errorcode code = args_gurax.PickNumber<SDL_errorcode>();
	// Function body
	int rtn = SDL_Error(code);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_LogSetAllPriority(priority:Number)
Gurax_DeclareFunctionAlias(SDL_LogSetAllPriority_gurax, "SDL_LogSetAllPriority")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("priority", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_LogSetAllPriority_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_LogPriority priority = args_gurax.PickNumber<SDL_LogPriority>();
	// Function body
	SDL_LogSetAllPriority(priority);
	return Gurax::Value::nil();
}

// sdl.SDL_LogSetPriority(category:Number, priority:Number)
Gurax_DeclareFunctionAlias(SDL_LogSetPriority_gurax, "SDL_LogSetPriority")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("category", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("priority", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_LogSetPriority_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int category = args_gurax.PickNumber<int>();
	SDL_LogPriority priority = args_gurax.PickNumber<SDL_LogPriority>();
	// Function body
	SDL_LogSetPriority(category, priority);
	return Gurax::Value::nil();
}

// sdl.SDL_LogGetPriority(category:Number)
Gurax_DeclareFunctionAlias(SDL_LogGetPriority_gurax, "SDL_LogGetPriority")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("category", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_LogGetPriority_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int category = args_gurax.PickNumber<int>();
	// Function body
	SDL_LogPriority rtn = SDL_LogGetPriority(category);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_LogResetPriorities()
Gurax_DeclareFunctionAlias(SDL_LogResetPriorities_gurax, "SDL_LogResetPriorities")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_LogResetPriorities_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_LogResetPriorities();
	return Gurax::Value::nil();
}

// sdl.SDL_ResetAssertionReport()
Gurax_DeclareFunctionAlias(SDL_ResetAssertionReport_gurax, "SDL_ResetAssertionReport")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_ResetAssertionReport_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_ResetAssertionReport();
	return Gurax::Value::nil();
}

// sdl.SDL_GetRevision()
Gurax_DeclareFunctionAlias(SDL_GetRevision_gurax, "SDL_GetRevision")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetRevision_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const char* rtn = SDL_GetRevision();
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_GetRevisionNumber()
Gurax_DeclareFunctionAlias(SDL_GetRevisionNumber_gurax, "SDL_GetRevisionNumber")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetRevisionNumber_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_GetRevisionNumber();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetNumVideoDrivers()
Gurax_DeclareFunctionAlias(SDL_GetNumVideoDrivers_gurax, "SDL_GetNumVideoDrivers")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetNumVideoDrivers_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_GetNumVideoDrivers();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetVideoDriver(index:Number)
Gurax_DeclareFunctionAlias(SDL_GetVideoDriver_gurax, "SDL_GetVideoDriver")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetVideoDriver_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	// Function body
	const char* rtn = SDL_GetVideoDriver(index);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_VideoInit(driver_name:String)
Gurax_DeclareFunctionAlias(SDL_VideoInit_gurax, "SDL_VideoInit")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("driver_name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_VideoInit_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* driver_name = args_gurax.PickString();
	// Function body
	int rtn = SDL_VideoInit(driver_name);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_VideoQuit()
Gurax_DeclareFunctionAlias(SDL_VideoQuit_gurax, "SDL_VideoQuit")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_VideoQuit_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_VideoQuit();
	return Gurax::Value::nil();
}

// sdl.SDL_GetCurrentVideoDriver()
Gurax_DeclareFunctionAlias(SDL_GetCurrentVideoDriver_gurax, "SDL_GetCurrentVideoDriver")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetCurrentVideoDriver_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const char* rtn = SDL_GetCurrentVideoDriver();
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_GetNumVideoDisplays()
Gurax_DeclareFunctionAlias(SDL_GetNumVideoDisplays_gurax, "SDL_GetNumVideoDisplays")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetNumVideoDisplays_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_GetNumVideoDisplays();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetDisplayName(displayIndex:Number)
Gurax_DeclareFunctionAlias(SDL_GetDisplayName_gurax, "SDL_GetDisplayName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetDisplayName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int displayIndex = args_gurax.PickNumber<int>();
	// Function body
	const char* rtn = SDL_GetDisplayName(displayIndex);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_GetDisplayBounds(displayIndex:Number)
Gurax_DeclareFunctionAlias(SDL_GetDisplayBounds_gurax, "SDL_GetDisplayBounds")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetDisplayBounds_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int displayIndex = args_gurax.PickNumber<int>();
	// Function body
	RefPtr<Value_SDL_Rect> pValue(new Value_SDL_Rect());
	if (SDL_GetDisplayBounds(displayIndex, &pValue->GetEntity()) != 0) {
		IssueError_SDL();
		return Value::nil();
	}
	return pValue.release();
}

// sdl.SDL_GetDisplayUsableBounds(displayIndex:Number)
Gurax_DeclareFunctionAlias(SDL_GetDisplayUsableBounds_gurax, "SDL_GetDisplayUsableBounds")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetDisplayUsableBounds_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int displayIndex = args_gurax.PickNumber<int>();
	// Function body
	RefPtr<Value_SDL_Rect> pValue(new Value_SDL_Rect());
	if (SDL_GetDisplayUsableBounds(displayIndex, &pValue->GetEntity()) != 0) {
		IssueError_SDL();
		return Value::nil();
	}
	return pValue.release();
}

// sdl.SDL_GetDisplayDPI(displayIndex:Number)
Gurax_DeclareFunctionAlias(SDL_GetDisplayDPI_gurax, "SDL_GetDisplayDPI")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetDisplayDPI_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int displayIndex = args_gurax.PickNumber<int>();
	// Function body
	float ddpi, hdpi, vdpi;
	if (SDL_GetDisplayDPI(displayIndex, &ddpi, &hdpi, &vdpi) != 0) {
		IssueError_SDL();
		return Value::nil();
	}
	return Value_List::Create(new Value_Number(ddpi), new Value_Number(hdpi), new Value_Number(vdpi));
}

// sdl.SDL_GetDisplayOrientation(displayIndex:Number)
Gurax_DeclareFunctionAlias(SDL_GetDisplayOrientation_gurax, "SDL_GetDisplayOrientation")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetDisplayOrientation_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int displayIndex = args_gurax.PickNumber<int>();
	// Function body
	SDL_DisplayOrientation rtn = SDL_GetDisplayOrientation(displayIndex);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetNumDisplayModes(displayIndex:Number)
Gurax_DeclareFunctionAlias(SDL_GetNumDisplayModes_gurax, "SDL_GetNumDisplayModes")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetNumDisplayModes_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int displayIndex = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_GetNumDisplayModes(displayIndex);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetDisplayMode(displayIndex:Number, modeIndex:Number)
Gurax_DeclareFunctionAlias(SDL_GetDisplayMode_gurax, "SDL_GetDisplayMode")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("modeIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetDisplayMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int displayIndex = args_gurax.PickNumber<int>();
	int modeIndex = args_gurax.PickNumber<int>();
	// Function body
	SDL_DisplayMode mode = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
	if (SDL_GetDisplayMode(displayIndex, modeIndex, &mode) != 0) {
		IssueError_SDL();
		return Value::nil();       
	}
	return new Value_SDL_DisplayMode(mode);
}

// sdl.SDL_GetDesktopDisplayMode(displayIndex:Number)
Gurax_DeclareFunctionAlias(SDL_GetDesktopDisplayMode_gurax, "SDL_GetDesktopDisplayMode")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetDesktopDisplayMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int displayIndex = args_gurax.PickNumber<int>();
	// Function body
	SDL_DisplayMode mode = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
	if (SDL_GetDesktopDisplayMode(displayIndex, &mode) != 0) {
		IssueError_SDL();
		return Value::nil();       
	}
	return new Value_SDL_DisplayMode(mode);
}

// sdl.SDL_GetCurrentDisplayMode(displayIndex:Number)
Gurax_DeclareFunctionAlias(SDL_GetCurrentDisplayMode_gurax, "SDL_GetCurrentDisplayMode")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetCurrentDisplayMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int displayIndex = args_gurax.PickNumber<int>();
	// Function body
	SDL_DisplayMode mode = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
	if (SDL_GetCurrentDisplayMode(displayIndex, &mode) != 0) {
		IssueError_SDL();
		return Value::nil();       
	}
	return new Value_SDL_DisplayMode(mode);
}

// sdl.SDL_GetWindowDisplayIndex(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowDisplayIndex_gurax, "SDL_GetWindowDisplayIndex")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetWindowDisplayIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	// Function body
	int rtn = SDL_GetWindowDisplayIndex(window);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetWindowPixelFormat(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowPixelFormat_gurax, "SDL_GetWindowPixelFormat")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetWindowPixelFormat_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	// Function body
	Uint32 rtn = SDL_GetWindowPixelFormat(window);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_CreateWindow(title:String, x:Number, y:Number, w:Number, h:Number, flags:Number)
Gurax_DeclareFunctionAlias(SDL_CreateWindow_gurax, "SDL_CreateWindow")
{
	Declare(VTYPE_SDL_Window, Flag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_CreateWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* title = args_gurax.PickString();
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	int w = args_gurax.PickNumber<int>();
	int h = args_gurax.PickNumber<int>();
	Uint32 flags = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_Window* rtn = SDL_CreateWindow(title, x, y, w, h, flags);
	return new Value_SDL_Window(rtn);
}

// sdl.SDL_GetWindowID(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowID_gurax, "SDL_GetWindowID")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetWindowID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	// Function body
	Uint32 rtn = SDL_GetWindowID(window);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetWindowFromID(id:Number)
Gurax_DeclareFunctionAlias(SDL_GetWindowFromID_gurax, "SDL_GetWindowFromID")
{
	Declare(VTYPE_SDL_Window, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetWindowFromID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 id = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_Window* rtn = SDL_GetWindowFromID(id);
	return new Value_SDL_Window(rtn);
}

// sdl.SDL_GetWindowFlags(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowFlags_gurax, "SDL_GetWindowFlags")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetWindowFlags_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	// Function body
	Uint32 rtn = SDL_GetWindowFlags(window);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetWindowTitle(window:SDL_Window, title:String)
Gurax_DeclareFunctionAlias(SDL_SetWindowTitle_gurax, "SDL_SetWindowTitle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetWindowTitle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	const char* title = args_gurax.PickString();
	// Function body
	SDL_SetWindowTitle(window, title);
	return Gurax::Value::nil();
}

// sdl.SDL_GetWindowTitle(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowTitle_gurax, "SDL_GetWindowTitle")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetWindowTitle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	// Function body
	const char* rtn = SDL_GetWindowTitle(window);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_SetWindowIcon(window:SDL_Window, icon:SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_SetWindowIcon_gurax, "SDL_SetWindowIcon")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("icon", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetWindowIcon_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	SDL_Surface* icon = args_gurax.Pick<Value_SDL_Surface>().GetEntity();
	// Function body
	SDL_SetWindowIcon(window, icon);
	return Gurax::Value::nil();
}

// sdl.SDL_SetWindowPosition(window:SDL_Window, x:Number, y:Number)
Gurax_DeclareFunctionAlias(SDL_SetWindowPosition_gurax, "SDL_SetWindowPosition")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetWindowPosition_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	// Function body
	SDL_SetWindowPosition(window, x, y);
	return Gurax::Value::nil();
}

// sdl.SDL_GetWindowPosition(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowPosition_gurax, "SDL_GetWindowPosition")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetWindowPosition_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	// Function body
	int x, y;
	SDL_GetWindowPosition(window, &x, &y);
	return Value_List::Create(new Value_Number(x), new Value_Number(y));
}

// sdl.SDL_SetWindowSize(window:SDL_Window, w:Number, h:Number)
Gurax_DeclareFunctionAlias(SDL_SetWindowSize_gurax, "SDL_SetWindowSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetWindowSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	int w = args_gurax.PickNumber<int>();
	int h = args_gurax.PickNumber<int>();
	// Function body
	SDL_SetWindowSize(window, w, h);
	return Gurax::Value::nil();
}

// sdl.SDL_GetWindowSize(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowSize_gurax, "SDL_GetWindowSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetWindowSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	// Function body
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	return Value_List::Create(new Value_Number(w), new Value_Number(h));
}

// sdl.SDL_SetWindowMinimumSize(window:SDL_Window, min_w:Number, min_h:Number)
Gurax_DeclareFunctionAlias(SDL_SetWindowMinimumSize_gurax, "SDL_SetWindowMinimumSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("min_w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("min_h", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetWindowMinimumSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	int min_w = args_gurax.PickNumber<int>();
	int min_h = args_gurax.PickNumber<int>();
	// Function body
	SDL_SetWindowMinimumSize(window, min_w, min_h);
	return Gurax::Value::nil();
}

// sdl.SDL_SetWindowMaximumSize(window:SDL_Window, max_w:Number, max_h:Number)
Gurax_DeclareFunctionAlias(SDL_SetWindowMaximumSize_gurax, "SDL_SetWindowMaximumSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("max_w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("max_h", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetWindowMaximumSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	int max_w = args_gurax.PickNumber<int>();
	int max_h = args_gurax.PickNumber<int>();
	// Function body
	SDL_SetWindowMaximumSize(window, max_w, max_h);
	return Gurax::Value::nil();
}

// sdl.SDL_SetWindowBordered(window:SDL_Window, bordered:Bool)
Gurax_DeclareFunctionAlias(SDL_SetWindowBordered_gurax, "SDL_SetWindowBordered")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bordered", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetWindowBordered_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	SDL_bool bordered = static_cast<SDL_bool>(args_gurax.PickBool());
	// Function body
	SDL_SetWindowBordered(window, bordered);
	return Gurax::Value::nil();
}

// sdl.SDL_SetWindowResizable(window:SDL_Window, resizable:Bool)
Gurax_DeclareFunctionAlias(SDL_SetWindowResizable_gurax, "SDL_SetWindowResizable")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("resizable", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetWindowResizable_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	SDL_bool resizable = static_cast<SDL_bool>(args_gurax.PickBool());
	// Function body
	SDL_SetWindowResizable(window, resizable);
	return Gurax::Value::nil();
}

// sdl.SDL_ShowWindow(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_ShowWindow_gurax, "SDL_ShowWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_ShowWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	// Function body
	SDL_ShowWindow(window);
	return Gurax::Value::nil();
}

// sdl.SDL_HideWindow(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_HideWindow_gurax, "SDL_HideWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_HideWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	// Function body
	SDL_HideWindow(window);
	return Gurax::Value::nil();
}

// sdl.SDL_RaiseWindow(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_RaiseWindow_gurax, "SDL_RaiseWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RaiseWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	// Function body
	SDL_RaiseWindow(window);
	return Gurax::Value::nil();
}

// sdl.SDL_MaximizeWindow(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_MaximizeWindow_gurax, "SDL_MaximizeWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_MaximizeWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	// Function body
	SDL_MaximizeWindow(window);
	return Gurax::Value::nil();
}

// sdl.SDL_MinimizeWindow(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_MinimizeWindow_gurax, "SDL_MinimizeWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_MinimizeWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	// Function body
	SDL_MinimizeWindow(window);
	return Gurax::Value::nil();
}

// sdl.SDL_RestoreWindow(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_RestoreWindow_gurax, "SDL_RestoreWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RestoreWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntity();
	// Function body
	SDL_RestoreWindow(window);
	return Gurax::Value::nil();
}

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(SDL_Init_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_InitSubSystem_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_QuitSubSystem_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_WasInit_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_Quit_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetHintWithPriority_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetHint_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetHint_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetHintBoolean_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ClearHints_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetError_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ClearError_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_Error_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_LogSetAllPriority_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_LogSetPriority_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_LogGetPriority_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_LogResetPriorities_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ResetAssertionReport_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetRevision_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetRevisionNumber_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetNumVideoDrivers_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetVideoDriver_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_VideoInit_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_VideoQuit_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetCurrentVideoDriver_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetNumVideoDisplays_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetDisplayName_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetDisplayBounds_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetDisplayUsableBounds_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetDisplayDPI_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetDisplayOrientation_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetNumDisplayModes_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetDisplayMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetDesktopDisplayMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetCurrentDisplayMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowDisplayIndex_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowPixelFormat_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CreateWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowID_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowFromID_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowFlags_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowTitle_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowTitle_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowIcon_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowPosition_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowPosition_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowSize_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowSize_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowMinimumSize_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowMaximumSize_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowBordered_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowResizable_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ShowWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HideWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RaiseWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_MaximizeWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_MinimizeWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RestoreWindow_gurax));
}

Gurax_EndModuleScope(sdl)
