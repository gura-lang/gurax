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
	SDL_Rect rect;
	if (SDL_GetDisplayBounds(displayIndex, &rect) != 0) {
		IssueError_SDL();
		return Value::nil();
	}
	return new Value_SDL_Rect(rect);
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
	SDL_Rect rect;
	if (SDL_GetDisplayUsableBounds(displayIndex, &rect) != 0) {
		IssueError_SDL();
		return Value::nil();
	}
	return new Value_SDL_Rect(rect);
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
	return Value_Tuple::Create(new Value_Number(ddpi), new Value_Number(hdpi), new Value_Number(vdpi));
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	SDL_Surface* icon = args_gurax.Pick<Value_SDL_Surface>().GetEntityPtr();
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	int x, y;
	SDL_GetWindowPosition(window, &x, &y);
	return Value_Tuple::Create(new Value_Number(x), new Value_Number(y));
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	return Value_Tuple::Create(new Value_Number(w), new Value_Number(h));
}

// sdl.SDL_GetWindowBordersSize(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowBordersSize_gurax, "SDL_GetWindowBordersSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetWindowBordersSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	int top, left, bottom, right;
	if (SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right) != 0) {
		IssueError_SDL();
		return Value::nil();
	}
	return Value_Tuple::Create(new Value_Number(top), new Value_Number(left), new Value_Number(bottom), new Value_Number(right));
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	int min_w = args_gurax.PickNumber<int>();
	int min_h = args_gurax.PickNumber<int>();
	// Function body
	SDL_SetWindowMinimumSize(window, min_w, min_h);
	return Gurax::Value::nil();
}

// sdl.SDL_GetWindowMinimumSize(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowMinimumSize_gurax, "SDL_GetWindowMinimumSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetWindowMinimumSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	int w, h;
	SDL_GetWindowMinimumSize(window, &w, &h);
	return Value_Tuple::Create(new Value_Number(w), new Value_Number(h));
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	int max_w = args_gurax.PickNumber<int>();
	int max_h = args_gurax.PickNumber<int>();
	// Function body
	SDL_SetWindowMaximumSize(window, max_w, max_h);
	return Gurax::Value::nil();
}

// sdl.SDL_GetWindowMaximumSize(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowMaximumSize_gurax, "SDL_GetWindowMaximumSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetWindowMaximumSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	int w, h;
	SDL_GetWindowMaximumSize(window, &w, &h);
	return Value_Tuple::Create(new Value_Number(w), new Value_Number(h));
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
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
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	SDL_RestoreWindow(window);
	return Gurax::Value::nil();
}

// sdl.SDL_SetWindowFullscreen(window:SDL_Window, flags:Number)
Gurax_DeclareFunctionAlias(SDL_SetWindowFullscreen_gurax, "SDL_SetWindowFullscreen")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetWindowFullscreen_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	Uint32 flags = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_SetWindowFullscreen(window, flags);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetWindowSurface(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowSurface_gurax, "SDL_GetWindowSurface")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetWindowSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	SDL_Surface* rtn = SDL_GetWindowSurface(window);
	return new Value_SDL_Surface(rtn);
}

// sdl.SDL_UpdateWindowSurface(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_UpdateWindowSurface_gurax, "SDL_UpdateWindowSurface")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_UpdateWindowSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	int rtn = SDL_UpdateWindowSurface(window);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetWindowGrab(window:SDL_Window, grabbed:Bool)
Gurax_DeclareFunctionAlias(SDL_SetWindowGrab_gurax, "SDL_SetWindowGrab")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("grabbed", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetWindowGrab_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	SDL_bool grabbed = static_cast<SDL_bool>(args_gurax.PickBool());
	// Function body
	SDL_SetWindowGrab(window, grabbed);
	return Gurax::Value::nil();
}

// sdl.SDL_GetWindowGrab(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowGrab_gurax, "SDL_GetWindowGrab")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetWindowGrab_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_GetWindowGrab(window);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_GetGrabbedWindow()
Gurax_DeclareFunctionAlias(SDL_GetGrabbedWindow_gurax, "SDL_GetGrabbedWindow")
{
	Declare(VTYPE_SDL_Window, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetGrabbedWindow_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Window* rtn = SDL_GetGrabbedWindow();
	return new Value_SDL_Window(rtn);
}

// sdl.SDL_SetWindowBrightness(window:SDL_Window, brightness:Number)
Gurax_DeclareFunctionAlias(SDL_SetWindowBrightness_gurax, "SDL_SetWindowBrightness")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("brightness", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetWindowBrightness_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	float brightness = args_gurax.PickNumber<float>();
	// Function body
	int rtn = SDL_SetWindowBrightness(window, brightness);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetWindowBrightness(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowBrightness_gurax, "SDL_GetWindowBrightness")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetWindowBrightness_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	float rtn = SDL_GetWindowBrightness(window);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetWindowOpacity(window:SDL_Window, opacity:Number)
Gurax_DeclareFunctionAlias(SDL_SetWindowOpacity_gurax, "SDL_SetWindowOpacity")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("opacity", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetWindowOpacity_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	float opacity = args_gurax.PickNumber<float>();
	// Function body
	int rtn = SDL_SetWindowOpacity(window, opacity);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetWindowModalFor(modal_window:SDL_Window, parent_window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_SetWindowModalFor_gurax, "SDL_SetWindowModalFor")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("modal_window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("parent_window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetWindowModalFor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* modal_window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	SDL_Window* parent_window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	int rtn = SDL_SetWindowModalFor(modal_window, parent_window);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetWindowInputFocus(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_SetWindowInputFocus_gurax, "SDL_SetWindowInputFocus")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetWindowInputFocus_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	int rtn = SDL_SetWindowInputFocus(window);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_DestroyWindow(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_DestroyWindow_gurax, "SDL_DestroyWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_DestroyWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	SDL_DestroyWindow(window);
	return Gurax::Value::nil();
}

// sdl.SDL_IsScreenSaverEnabled()
Gurax_DeclareFunctionAlias(SDL_IsScreenSaverEnabled_gurax, "SDL_IsScreenSaverEnabled")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_IsScreenSaverEnabled_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_IsScreenSaverEnabled();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_EnableScreenSaver()
Gurax_DeclareFunctionAlias(SDL_EnableScreenSaver_gurax, "SDL_EnableScreenSaver")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_EnableScreenSaver_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_EnableScreenSaver();
	return Gurax::Value::nil();
}

// sdl.SDL_DisableScreenSaver()
Gurax_DeclareFunctionAlias(SDL_DisableScreenSaver_gurax, "SDL_DisableScreenSaver")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_DisableScreenSaver_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_DisableScreenSaver();
	return Gurax::Value::nil();
}

// sdl.SDL_GL_LoadLibrary(path:String)
Gurax_DeclareFunctionAlias(SDL_GL_LoadLibrary_gurax, "SDL_GL_LoadLibrary")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("path", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GL_LoadLibrary_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* path = args_gurax.PickString();
	// Function body
	int rtn = SDL_GL_LoadLibrary(path);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GL_UnloadLibrary()
Gurax_DeclareFunctionAlias(SDL_GL_UnloadLibrary_gurax, "SDL_GL_UnloadLibrary")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GL_UnloadLibrary_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_GL_UnloadLibrary();
	return Gurax::Value::nil();
}

// sdl.SDL_GL_ExtensionSupported(extension:String)
Gurax_DeclareFunctionAlias(SDL_GL_ExtensionSupported_gurax, "SDL_GL_ExtensionSupported")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("extension", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GL_ExtensionSupported_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* extension = args_gurax.PickString();
	// Function body
	SDL_bool rtn = SDL_GL_ExtensionSupported(extension);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_GL_ResetAttributes()
Gurax_DeclareFunctionAlias(SDL_GL_ResetAttributes_gurax, "SDL_GL_ResetAttributes")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GL_ResetAttributes_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_GL_ResetAttributes();
	return Gurax::Value::nil();
}

// sdl.SDL_GL_SetAttribute(attr:Number, value:Number)
Gurax_DeclareFunctionAlias(SDL_GL_SetAttribute_gurax, "SDL_GL_SetAttribute")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("attr", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GL_SetAttribute_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GLattr attr = args_gurax.PickNumber<SDL_GLattr>();
	int value = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_GL_SetAttribute(attr, value);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GL_GetAttribute(attr:Number)
Gurax_DeclareFunctionAlias(SDL_GL_GetAttribute_gurax, "SDL_GL_GetAttribute")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("attr", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GL_GetAttribute_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GLattr attr = args_gurax.PickNumber<SDL_GLattr>();
	// Function body
	int value;
	if (SDL_GL_GetAttribute(attr, &value) != 0) {
		IssueError_SDL();
		return Value::nil();
	}
	return new Value_Number(value);
}

// sdl.SDL_GL_CreateContext(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GL_CreateContext_gurax, "SDL_GL_CreateContext")
{
	Declare(VTYPE_SDL_GLContext, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GL_CreateContext_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	SDL_GLContext rtn = SDL_GL_CreateContext(window);
	return new Value_SDL_GLContext(rtn);
}

// sdl.SDL_GL_MakeCurrent(window:SDL_Window, context:SDL_GLContext)
Gurax_DeclareFunctionAlias(SDL_GL_MakeCurrent_gurax, "SDL_GL_MakeCurrent")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("context", VTYPE_SDL_GLContext, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GL_MakeCurrent_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	SDL_GLContext context = args_gurax.Pick<Value_SDL_GLContext>().GetEntityPtr();
	// Function body
	int rtn = SDL_GL_MakeCurrent(window, context);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GL_GetCurrentWindow()
Gurax_DeclareFunctionAlias(SDL_GL_GetCurrentWindow_gurax, "SDL_GL_GetCurrentWindow")
{
	Declare(VTYPE_SDL_Window, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GL_GetCurrentWindow_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Window* rtn = SDL_GL_GetCurrentWindow();
	return new Value_SDL_Window(rtn);
}

// sdl.SDL_GL_GetCurrentContext()
Gurax_DeclareFunctionAlias(SDL_GL_GetCurrentContext_gurax, "SDL_GL_GetCurrentContext")
{
	Declare(VTYPE_SDL_GLContext, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GL_GetCurrentContext_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_GLContext rtn = SDL_GL_GetCurrentContext();
	return new Value_SDL_GLContext(rtn);
}

// sdl.SDL_GL_GetDrawableSize(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GL_GetDrawableSize_gurax, "SDL_GL_GetDrawableSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GL_GetDrawableSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	int w, h;
	SDL_GL_GetDrawableSize(window, &w, &h);
	return Value_Tuple::Create(new Value_Number(w), new Value_Number(h));
}

// sdl.SDL_GL_SetSwapInterval(interval:Number)
Gurax_DeclareFunctionAlias(SDL_GL_SetSwapInterval_gurax, "SDL_GL_SetSwapInterval")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("interval", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GL_SetSwapInterval_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int interval = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_GL_SetSwapInterval(interval);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GL_GetSwapInterval()
Gurax_DeclareFunctionAlias(SDL_GL_GetSwapInterval_gurax, "SDL_GL_GetSwapInterval")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GL_GetSwapInterval_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_GL_GetSwapInterval();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GL_SwapWindow(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GL_SwapWindow_gurax, "SDL_GL_SwapWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GL_SwapWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	SDL_GL_SwapWindow(window);
	return Gurax::Value::nil();
}

// sdl.SDL_GL_DeleteContext(context:SDL_GLContext)
Gurax_DeclareFunctionAlias(SDL_GL_DeleteContext_gurax, "SDL_GL_DeleteContext")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("context", VTYPE_SDL_GLContext, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GL_DeleteContext_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GLContext context = args_gurax.Pick<Value_SDL_GLContext>().GetEntityPtr();
	// Function body
	SDL_GL_DeleteContext(context);
	return Gurax::Value::nil();
}

// sdl.SDL_GetNumRenderDrivers()
Gurax_DeclareFunctionAlias(SDL_GetNumRenderDrivers_gurax, "SDL_GetNumRenderDrivers")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetNumRenderDrivers_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_GetNumRenderDrivers();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetRenderDriverInfo(index:Number)
Gurax_DeclareFunctionAlias(SDL_GetRenderDriverInfo_gurax, "SDL_GetRenderDriverInfo")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetRenderDriverInfo_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	// Function body
	SDL_RendererInfo info;
	if (SDL_GetRenderDriverInfo(index, &info) != 0) {
		IssueError_SDL();
		return Value::nil();       
	}
	return new Value_SDL_RendererInfo(info);
}

// sdl.SDL_CreateWindowAndRenderer(width:Number, height:Number, window_flags:Number)
Gurax_DeclareFunctionAlias(SDL_CreateWindowAndRenderer_gurax, "SDL_CreateWindowAndRenderer")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("window_flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_CreateWindowAndRenderer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	Uint32 window_flags = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_Window* window;
	SDL_Renderer* renderer;
	if (SDL_CreateWindowAndRenderer(width, height, window_flags, &window, &renderer) != 0) {
		IssueError_SDL();
		return Value::nil();
	}
	return Value_Tuple::Create(new Value_SDL_Window(window), new Value_SDL_Renderer(renderer));
}

// sdl.SDL_CreateRenderer(window:SDL_Window, index:Number, flags:Number)
Gurax_DeclareFunctionAlias(SDL_CreateRenderer_gurax, "SDL_CreateRenderer")
{
	Declare(VTYPE_SDL_Renderer, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_CreateRenderer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	int index = args_gurax.PickNumber<int>();
	Uint32 flags = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_Renderer* rtn = SDL_CreateRenderer(window, index, flags);
	return new Value_SDL_Renderer(rtn);
}

// sdl.SDL_CreateSoftwareRenderer(surface:SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_CreateSoftwareRenderer_gurax, "SDL_CreateSoftwareRenderer")
{
	Declare(VTYPE_SDL_Renderer, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_CreateSoftwareRenderer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Surface* surface = args_gurax.Pick<Value_SDL_Surface>().GetEntityPtr();
	// Function body
	SDL_Renderer* rtn = SDL_CreateSoftwareRenderer(surface);
	return new Value_SDL_Renderer(rtn);
}

// sdl.SDL_GetRenderer(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetRenderer_gurax, "SDL_GetRenderer")
{
	Declare(VTYPE_SDL_Renderer, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetRenderer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	SDL_Renderer* rtn = SDL_GetRenderer(window);
	return new Value_SDL_Renderer(rtn);
}

// sdl.SDL_GetRendererInfo(renderer:SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_GetRendererInfo_gurax, "SDL_GetRendererInfo")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetRendererInfo_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	// Function body
	SDL_RendererInfo info;
	if (SDL_GetRendererInfo(renderer, &info) != 0) {
		IssueError_SDL();
		return Value::nil();       
	}
	return new Value_SDL_RendererInfo(info);
}

// sdl.SDL_GetRendererOutputSize(renderer:SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_GetRendererOutputSize_gurax, "SDL_GetRendererOutputSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetRendererOutputSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	// Function body
	int w, h;
	if (SDL_GetRendererOutputSize(renderer, &w, &h) != 0) {
		IssueError_SDL();
		return Value::nil();
	}
	return Value_Tuple::Create(new Value_Number(w), new Value_Number(h));
}

// sdl.SDL_CreateTexture(renderer:SDL_Renderer, format:Number, access:Number, w:Number, h:Number)
Gurax_DeclareFunctionAlias(SDL_CreateTexture_gurax, "SDL_CreateTexture")
{
	Declare(VTYPE_SDL_Texture, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("access", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_CreateTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	Uint32 format = args_gurax.PickNumber<Uint32>();
	int access = args_gurax.PickNumber<int>();
	int w = args_gurax.PickNumber<int>();
	int h = args_gurax.PickNumber<int>();
	// Function body
	SDL_Texture* rtn = SDL_CreateTexture(renderer, format, access, w, h);
	return new Value_SDL_Texture(rtn);
}

// sdl.SDL_CreateTextureFromSurface(renderer:SDL_Renderer, surface:SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_CreateTextureFromSurface_gurax, "SDL_CreateTextureFromSurface")
{
	Declare(VTYPE_SDL_Texture, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_CreateTextureFromSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	SDL_Surface* surface = args_gurax.Pick<Value_SDL_Surface>().GetEntityPtr();
	// Function body
	SDL_Texture* rtn = SDL_CreateTextureFromSurface(renderer, surface);
	return new Value_SDL_Texture(rtn);
}

// sdl.SDL_QueryTexture(texture:SDL_Texture)
Gurax_DeclareFunctionAlias(SDL_QueryTexture_gurax, "SDL_QueryTexture")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_QueryTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	// Function body
	Uint32 format;
	int access, w, h;
	if (SDL_QueryTexture(texture, &format, &access, &w, &h) != 0) {
		IssueError_SDL();
		return Value::nil();
	}
	return Value_Tuple::Create(new Value_Number(format), new Value_Number(access), new Value_Number(w), new Value_Number(h));
}

// sdl.SDL_SetTextureColorMod(texture:SDL_Texture, r:Number, g:Number, b:Number)
Gurax_DeclareFunctionAlias(SDL_SetTextureColorMod_gurax, "SDL_SetTextureColorMod")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetTextureColorMod_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	Uint8 r = args_gurax.PickNumber<Uint8>();
	Uint8 g = args_gurax.PickNumber<Uint8>();
	Uint8 b = args_gurax.PickNumber<Uint8>();
	// Function body
	int rtn = SDL_SetTextureColorMod(texture, r, g, b);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetTextureColorMod(texture:SDL_Texture)
Gurax_DeclareFunctionAlias(SDL_GetTextureColorMod_gurax, "SDL_GetTextureColorMod")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetTextureColorMod_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	// Function body
	Uint8 r, g, b;
	if (SDL_GetTextureColorMod(texture, &r, &g, &b) != 0) {
		IssueError_SDL();
		return Value::nil();
	}
	return Value_Tuple::Create(new Value_Number(r), new Value_Number(g), new Value_Number(b));
}

// sdl.SDL_SetTextureAlphaMod(texture:SDL_Texture, alpha:Number)
Gurax_DeclareFunctionAlias(SDL_SetTextureAlphaMod_gurax, "SDL_SetTextureAlphaMod")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetTextureAlphaMod_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	Uint8 alpha = args_gurax.PickNumber<Uint8>();
	// Function body
	int rtn = SDL_SetTextureAlphaMod(texture, alpha);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetTextureAlphaMod(texture:SDL_Texture)
Gurax_DeclareFunctionAlias(SDL_GetTextureAlphaMod_gurax, "SDL_GetTextureAlphaMod")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetTextureAlphaMod_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	// Function body
	Uint8 alpha;
	if (SDL_GetTextureAlphaMod(texture, &alpha) != 0) {
		IssueError_SDL();
		return Value::nil();
	}
	return new Value_Number(alpha);
}

// sdl.SDL_SetTextureBlendMode(texture:SDL_Texture, blendMode:Number)
Gurax_DeclareFunctionAlias(SDL_SetTextureBlendMode_gurax, "SDL_SetTextureBlendMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blendMode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetTextureBlendMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	SDL_BlendMode blendMode = args_gurax.PickNumber<SDL_BlendMode>();
	// Function body
	int rtn = SDL_SetTextureBlendMode(texture, blendMode);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetTextureBlendMode(texture:SDL_Texture)
Gurax_DeclareFunctionAlias(SDL_GetTextureBlendMode_gurax, "SDL_GetTextureBlendMode")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetTextureBlendMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	// Function body
	SDL_BlendMode blendMode;
	if (SDL_GetTextureBlendMode(texture, &blendMode) != 0) {
		IssueError_SDL();
		return Value::nil();
	}
	return new Value_Number(blendMode);
}

// sdl.SDL_SetTextureScaleMode(texture:SDL_Texture, scaleMode:Number)
Gurax_DeclareFunctionAlias(SDL_SetTextureScaleMode_gurax, "SDL_SetTextureScaleMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("scaleMode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetTextureScaleMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	SDL_ScaleMode scaleMode = args_gurax.PickNumber<SDL_ScaleMode>();
	// Function body
	int rtn = SDL_SetTextureScaleMode(texture, scaleMode);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetTextureScaleMode(texture:SDL_Texture)
Gurax_DeclareFunctionAlias(SDL_GetTextureScaleMode_gurax, "SDL_GetTextureScaleMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetTextureScaleMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	// Function body
	SDL_ScaleMode scaleMode;
	if (SDL_GetTextureScaleMode(texture, &scaleMode) != 0) {
		IssueError_SDL();
		return Value::nil();
	}
	return new Value_Number(scaleMode);
}

// sdl.SDL_UpdateTexture(texture:SDL_Texture, rect:SDL_Rect, pixels:Pointer, pitch:Number)
Gurax_DeclareFunctionAlias(SDL_UpdateTexture_gurax, "SDL_UpdateTexture")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pitch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_UpdateTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	const SDL_Rect* rect = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	const void* pixels = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<void>();
	int pitch = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_UpdateTexture(texture, rect, pixels, pitch);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_UpdateYUVTexture(texture:SDL_Texture, rect:SDL_Rect, Yplane:Pointer, Ypitch:Number, Uplane:Pointer, Upitch:Number, Vplane:Pointer, Vpitch:Number)
Gurax_DeclareFunctionAlias(SDL_UpdateYUVTexture_gurax, "SDL_UpdateYUVTexture")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Yplane", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Ypitch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Uplane", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Upitch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Vplane", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Vpitch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_UpdateYUVTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	const SDL_Rect* rect = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	const Uint8* Yplane = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<Uint8>();
	int Ypitch = args_gurax.PickNumber<int>();
	const Uint8* Uplane = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<Uint8>();
	int Upitch = args_gurax.PickNumber<int>();
	const Uint8* Vplane = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<Uint8>();
	int Vpitch = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_UpdateYUVTexture(texture, rect, Yplane, Ypitch, Uplane, Upitch, Vplane, Vpitch);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_UnlockTexture(texture:SDL_Texture)
Gurax_DeclareFunctionAlias(SDL_UnlockTexture_gurax, "SDL_UnlockTexture")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_UnlockTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	// Function body
	SDL_UnlockTexture(texture);
	return Gurax::Value::nil();
}

// sdl.SDL_RenderTargetSupported(renderer:SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_RenderTargetSupported_gurax, "SDL_RenderTargetSupported")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderTargetSupported_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_RenderTargetSupported(renderer);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_SetRenderTarget(renderer:SDL_Renderer, texture:SDL_Texture)
Gurax_DeclareFunctionAlias(SDL_SetRenderTarget_gurax, "SDL_SetRenderTarget")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetRenderTarget_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	// Function body
	int rtn = SDL_SetRenderTarget(renderer, texture);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetRenderTarget(renderer:SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_GetRenderTarget_gurax, "SDL_GetRenderTarget")
{
	Declare(VTYPE_SDL_Texture, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetRenderTarget_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	// Function body
	SDL_Texture* rtn = SDL_GetRenderTarget(renderer);
	return new Value_SDL_Texture(rtn);
}

// sdl.SDL_RenderSetLogicalSize(renderer:SDL_Renderer, w:Number, h:Number)
Gurax_DeclareFunctionAlias(SDL_RenderSetLogicalSize_gurax, "SDL_RenderSetLogicalSize")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderSetLogicalSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	int w = args_gurax.PickNumber<int>();
	int h = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_RenderSetLogicalSize(renderer, w, h);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderSetIntegerScale(renderer:SDL_Renderer, enable:Bool)
Gurax_DeclareFunctionAlias(SDL_RenderSetIntegerScale_gurax, "SDL_RenderSetIntegerScale")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("enable", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderSetIntegerScale_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	SDL_bool enable = static_cast<SDL_bool>(args_gurax.PickBool());
	// Function body
	int rtn = SDL_RenderSetIntegerScale(renderer, enable);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderGetIntegerScale(renderer:SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_RenderGetIntegerScale_gurax, "SDL_RenderGetIntegerScale")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderGetIntegerScale_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_RenderGetIntegerScale(renderer);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_RenderSetViewport(renderer:SDL_Renderer, rect:SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_RenderSetViewport_gurax, "SDL_RenderSetViewport")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderSetViewport_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	const SDL_Rect* rect = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	// Function body
	int rtn = SDL_RenderSetViewport(renderer, rect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderSetClipRect(renderer:SDL_Renderer, rect:SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_RenderSetClipRect_gurax, "SDL_RenderSetClipRect")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderSetClipRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	const SDL_Rect* rect = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	// Function body
	int rtn = SDL_RenderSetClipRect(renderer, rect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderIsClipEnabled(renderer:SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_RenderIsClipEnabled_gurax, "SDL_RenderIsClipEnabled")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderIsClipEnabled_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_RenderIsClipEnabled(renderer);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_RenderSetScale(renderer:SDL_Renderer, scaleX:Number, scaleY:Number)
Gurax_DeclareFunctionAlias(SDL_RenderSetScale_gurax, "SDL_RenderSetScale")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("scaleX", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("scaleY", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderSetScale_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	float scaleX = args_gurax.PickNumber<float>();
	float scaleY = args_gurax.PickNumber<float>();
	// Function body
	int rtn = SDL_RenderSetScale(renderer, scaleX, scaleY);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetRenderDrawColor(renderer:SDL_Renderer, r:Number, g:Number, b:Number, a:Number)
Gurax_DeclareFunctionAlias(SDL_SetRenderDrawColor_gurax, "SDL_SetRenderDrawColor")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("a", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetRenderDrawColor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	Uint8 r = args_gurax.PickNumber<Uint8>();
	Uint8 g = args_gurax.PickNumber<Uint8>();
	Uint8 b = args_gurax.PickNumber<Uint8>();
	Uint8 a = args_gurax.PickNumber<Uint8>();
	// Function body
	int rtn = SDL_SetRenderDrawColor(renderer, r, g, b, a);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetRenderDrawBlendMode(renderer:SDL_Renderer, blendMode:Number)
Gurax_DeclareFunctionAlias(SDL_SetRenderDrawBlendMode_gurax, "SDL_SetRenderDrawBlendMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blendMode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetRenderDrawBlendMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	SDL_BlendMode blendMode = args_gurax.PickNumber<SDL_BlendMode>();
	// Function body
	int rtn = SDL_SetRenderDrawBlendMode(renderer, blendMode);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderClear(renderer:SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_RenderClear_gurax, "SDL_RenderClear")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderClear_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	// Function body
	int rtn = SDL_RenderClear(renderer);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderDrawPoint(renderer:SDL_Renderer, x:Number, y:Number)
Gurax_DeclareFunctionAlias(SDL_RenderDrawPoint_gurax, "SDL_RenderDrawPoint")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderDrawPoint_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_RenderDrawPoint(renderer, x, y);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderDrawLine(renderer:SDL_Renderer, x1:Number, y1:Number, x2:Number, y2:Number)
Gurax_DeclareFunctionAlias(SDL_RenderDrawLine_gurax, "SDL_RenderDrawLine")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderDrawLine_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	int x1 = args_gurax.PickNumber<int>();
	int y1 = args_gurax.PickNumber<int>();
	int x2 = args_gurax.PickNumber<int>();
	int y2 = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderDrawRect(renderer:SDL_Renderer, rect:SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_RenderDrawRect_gurax, "SDL_RenderDrawRect")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderDrawRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	const SDL_Rect* rect = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	// Function body
	int rtn = SDL_RenderDrawRect(renderer, rect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderFillRect(renderer:SDL_Renderer, rect:SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_RenderFillRect_gurax, "SDL_RenderFillRect")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderFillRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	const SDL_Rect* rect = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	// Function body
	int rtn = SDL_RenderFillRect(renderer, rect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderFillRects(renderer:SDL_Renderer, rects:SDL_Rect, count:Number)
Gurax_DeclareFunctionAlias(SDL_RenderFillRects_gurax, "SDL_RenderFillRects")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rects", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderFillRects_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	const SDL_Rect* rects = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	int count = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_RenderFillRects(renderer, rects, count);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderCopy(renderer:SDL_Renderer, texture:SDL_Texture, srcrect:SDL_Rect, dstrect:SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_RenderCopy_gurax, "SDL_RenderCopy")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderCopy_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	const SDL_Rect* srcrect = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	const SDL_Rect* dstrect = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	// Function body
	int rtn = SDL_RenderCopy(renderer, texture, srcrect, dstrect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderDrawPointF(renderer:SDL_Renderer, x:Number, y:Number)
Gurax_DeclareFunctionAlias(SDL_RenderDrawPointF_gurax, "SDL_RenderDrawPointF")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderDrawPointF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	float x = args_gurax.PickNumber<float>();
	float y = args_gurax.PickNumber<float>();
	// Function body
	int rtn = SDL_RenderDrawPointF(renderer, x, y);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderDrawLineF(renderer:SDL_Renderer, x1:Number, y1:Number, x2:Number, y2:Number)
Gurax_DeclareFunctionAlias(SDL_RenderDrawLineF_gurax, "SDL_RenderDrawLineF")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderDrawLineF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	float x1 = args_gurax.PickNumber<float>();
	float y1 = args_gurax.PickNumber<float>();
	float x2 = args_gurax.PickNumber<float>();
	float y2 = args_gurax.PickNumber<float>();
	// Function body
	int rtn = SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderReadPixels(renderer:SDL_Renderer, rect:SDL_Rect, format:Number, pixels:Pointer, pitch:Number)
Gurax_DeclareFunctionAlias(SDL_RenderReadPixels_gurax, "SDL_RenderReadPixels")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pitch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderReadPixels_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	const SDL_Rect* rect = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	Uint32 format = args_gurax.PickNumber<Uint32>();
	void* pixels = args_gurax.Pick<Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!pixels) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	int pitch = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_RenderReadPixels(renderer, rect, format, pixels, pitch);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderPresent(renderer:SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_RenderPresent_gurax, "SDL_RenderPresent")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderPresent_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	// Function body
	SDL_RenderPresent(renderer);
	return Gurax::Value::nil();
}

// sdl.SDL_DestroyTexture(texture:SDL_Texture)
Gurax_DeclareFunctionAlias(SDL_DestroyTexture_gurax, "SDL_DestroyTexture")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_DestroyTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	// Function body
	SDL_DestroyTexture(texture);
	return Gurax::Value::nil();
}

// sdl.SDL_DestroyRenderer(renderer:SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_DestroyRenderer_gurax, "SDL_DestroyRenderer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_DestroyRenderer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	// Function body
	SDL_DestroyRenderer(renderer);
	return Gurax::Value::nil();
}

// sdl.SDL_RenderFlush(renderer:SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_RenderFlush_gurax, "SDL_RenderFlush")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderFlush_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	// Function body
	int rtn = SDL_RenderFlush(renderer);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GL_UnbindTexture(texture:SDL_Texture)
Gurax_DeclareFunctionAlias(SDL_GL_UnbindTexture_gurax, "SDL_GL_UnbindTexture")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GL_UnbindTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	// Function body
	int rtn = SDL_GL_UnbindTexture(texture);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetPixelFormatName(format:Number)
Gurax_DeclareFunctionAlias(SDL_GetPixelFormatName_gurax, "SDL_GetPixelFormatName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetPixelFormatName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 format = args_gurax.PickNumber<Uint32>();
	// Function body
	const char* rtn = SDL_GetPixelFormatName(format);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_MasksToPixelFormatEnum(bpp:Number, Rmask:Number, Gmask:Number, Bmask:Number, Amask:Number)
Gurax_DeclareFunctionAlias(SDL_MasksToPixelFormatEnum_gurax, "SDL_MasksToPixelFormatEnum")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("bpp", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Rmask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Gmask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Bmask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Amask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_MasksToPixelFormatEnum_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int bpp = args_gurax.PickNumber<int>();
	Uint32 Rmask = args_gurax.PickNumber<Uint32>();
	Uint32 Gmask = args_gurax.PickNumber<Uint32>();
	Uint32 Bmask = args_gurax.PickNumber<Uint32>();
	Uint32 Amask = args_gurax.PickNumber<Uint32>();
	// Function body
	Uint32 rtn = SDL_MasksToPixelFormatEnum(bpp, Rmask, Gmask, Bmask, Amask);
	return new Gurax::Value_Number(rtn);
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
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowBordersSize_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowMinimumSize_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowMinimumSize_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowMaximumSize_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowMaximumSize_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowBordered_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowResizable_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ShowWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HideWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RaiseWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_MaximizeWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_MinimizeWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RestoreWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowFullscreen_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowSurface_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_UpdateWindowSurface_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowGrab_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowGrab_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetGrabbedWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowBrightness_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowBrightness_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowOpacity_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowModalFor_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowInputFocus_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_DestroyWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_IsScreenSaverEnabled_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_EnableScreenSaver_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_DisableScreenSaver_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_LoadLibrary_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_UnloadLibrary_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_ExtensionSupported_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_ResetAttributes_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_SetAttribute_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_GetAttribute_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_CreateContext_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_MakeCurrent_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_GetCurrentWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_GetCurrentContext_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_GetDrawableSize_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_SetSwapInterval_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_GetSwapInterval_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_SwapWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_DeleteContext_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetNumRenderDrivers_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetRenderDriverInfo_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CreateWindowAndRenderer_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CreateRenderer_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CreateSoftwareRenderer_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetRenderer_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetRendererInfo_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetRendererOutputSize_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CreateTexture_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CreateTextureFromSurface_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_QueryTexture_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetTextureColorMod_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetTextureColorMod_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetTextureAlphaMod_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetTextureAlphaMod_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetTextureBlendMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetTextureBlendMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetTextureScaleMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetTextureScaleMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_UpdateTexture_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_UpdateYUVTexture_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_UnlockTexture_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderTargetSupported_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetRenderTarget_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetRenderTarget_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderSetLogicalSize_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderSetIntegerScale_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderGetIntegerScale_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderSetViewport_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderSetClipRect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderIsClipEnabled_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderSetScale_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetRenderDrawColor_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetRenderDrawBlendMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderClear_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawPoint_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawLine_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawRect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderFillRect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderFillRects_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderCopy_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawPointF_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawLineF_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderReadPixels_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderPresent_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_DestroyTexture_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_DestroyRenderer_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderFlush_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_UnbindTexture_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetPixelFormatName_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_MasksToPixelFormatEnum_gurax));
}

Gurax_EndModuleScope(sdl)
