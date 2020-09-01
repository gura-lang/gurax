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

// sdl.SDL_GetWindowOpacity(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowOpacity_gurax, "SDL_GetWindowOpacity")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetWindowOpacity_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	float out_opacity;
	if (SDL_GetWindowOpacity(window, &out_opacity) != 0) {
		IssueError_SDL();
		return Value::nil();
	}
	return new Value_Number(out_opacity);
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

// sdl.SDL_RenderGetLogicalSize(renderer:SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_RenderGetLogicalSize_gurax, "SDL_RenderGetLogicalSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderGetLogicalSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	// Function body
	int w, h;
	SDL_RenderGetLogicalSize(renderer, &w, &h);
	return Value_Tuple::Create(new Value_Number(w), new Value_Number(h));
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

// sdl.SDL_RenderGetViewport(renderer:SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_RenderGetViewport_gurax, "SDL_RenderGetViewport")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderGetViewport_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	// Function body
	SDL_Rect rect;
	SDL_RenderGetViewport(renderer, &rect);
	return new Value_SDL_Rect(rect);
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

// sdl.SDL_RenderGetClipRect(renderer:SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_RenderGetClipRect_gurax, "SDL_RenderGetClipRect")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderGetClipRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	// Function body
	SDL_Rect rect;
	SDL_RenderGetClipRect(renderer, &rect);
	return new Value_SDL_Rect(rect);
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

// sdl.SDL_RenderGetScale(renderer:SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_RenderGetScale_gurax, "SDL_RenderGetScale")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderGetScale_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	// Function body
	float scaleX, scaleY;
	SDL_RenderGetScale(renderer, &scaleX, &scaleY);
	return Value_Tuple::Create(new Value_Number(scaleX), new Value_Number(scaleY));
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

// sdl.SDL_RenderDrawPointsF(renderer:SDL_Renderer, points:SDL_FPoint, count:Number)
Gurax_DeclareFunctionAlias(SDL_RenderDrawPointsF_gurax, "SDL_RenderDrawPointsF")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("points", VTYPE_SDL_FPoint, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderDrawPointsF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	const SDL_FPoint* points = args_gurax.Pick<Value_SDL_FPoint>().GetEntityPtr();
	int count = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_RenderDrawPointsF(renderer, points, count);
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

// sdl.SDL_RenderDrawRectF(renderer:SDL_Renderer, rect:SDL_FRect)
Gurax_DeclareFunctionAlias(SDL_RenderDrawRectF_gurax, "SDL_RenderDrawRectF")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_FRect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderDrawRectF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	const SDL_FRect* rect = args_gurax.Pick<Value_SDL_FRect>().GetEntityPtr();
	// Function body
	int rtn = SDL_RenderDrawRectF(renderer, rect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderFillRectF(renderer:SDL_Renderer, rect:SDL_FRect)
Gurax_DeclareFunctionAlias(SDL_RenderFillRectF_gurax, "SDL_RenderFillRectF")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_FRect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderFillRectF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	const SDL_FRect* rect = args_gurax.Pick<Value_SDL_FRect>().GetEntityPtr();
	// Function body
	int rtn = SDL_RenderFillRectF(renderer, rect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderCopyF(renderer:SDL_Renderer, texture:SDL_Texture, srcrect:SDL_Rect, dstrect:SDL_FRect)
Gurax_DeclareFunctionAlias(SDL_RenderCopyF_gurax, "SDL_RenderCopyF")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstrect", VTYPE_SDL_FRect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RenderCopyF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr();
	SDL_Texture* texture = args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr();
	const SDL_Rect* srcrect = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	const SDL_FRect* dstrect = args_gurax.Pick<Value_SDL_FRect>().GetEntityPtr();
	// Function body
	int rtn = SDL_RenderCopyF(renderer, texture, srcrect, dstrect);
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

// sdl.SDL_HasIntersection(A:SDL_Rect, B:SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_HasIntersection_gurax, "SDL_HasIntersection")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("A", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("B", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_HasIntersection_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const SDL_Rect* A = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	const SDL_Rect* B = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_HasIntersection(A, B);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_IntersectRect(A:SDL_Rect, B:SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_IntersectRect_gurax, "SDL_IntersectRect")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("A", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("B", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_IntersectRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const SDL_Rect* A = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	const SDL_Rect* B = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	// Function body
	SDL_Rect result;
	if (!SDL_IntersectRect(A, B, &result)) return Value::nil();
	return new Value_SDL_Rect(result);
}

// sdl.SDL_UnionRect(A:SDL_Rect, B:SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_UnionRect_gurax, "SDL_UnionRect")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("A", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("B", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_UnionRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const SDL_Rect* A = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	const SDL_Rect* B = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	// Function body
	SDL_Rect result;
	SDL_UnionRect(A, B, &result);
	return new Value_SDL_Rect(result);
}

// sdl.SDL_IntersectRectAndLine(rect:SDL_Rect, X1:Number, Y1:Number, X2:Number, Y2:Number)
Gurax_DeclareFunctionAlias(SDL_IntersectRectAndLine_gurax, "SDL_IntersectRectAndLine")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("X1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Y1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("X2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Y2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_IntersectRectAndLine_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const SDL_Rect* rect = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	int X1 = args_gurax.PickNumber<int>();
	int Y1 = args_gurax.PickNumber<int>();
	int X2 = args_gurax.PickNumber<int>();
	int Y2 = args_gurax.PickNumber<int>();
	// Function body
	if (!SDL_IntersectRectAndLine(rect, &X1, &Y1, &X2, &Y2)) return Value::nil();
	return Value_Tuple::Create(new Value_Number(X1), new Value_Number(Y1), new Value_Number(X2), new Value_Number(Y2));
}

// sdl.SDL_SetSurfaceRLE(surface:SDL_Surface, flag:Number)
Gurax_DeclareFunctionAlias(SDL_SetSurfaceRLE_gurax, "SDL_SetSurfaceRLE")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flag", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetSurfaceRLE_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Surface* surface = args_gurax.Pick<Value_SDL_Surface>().GetEntityPtr();
	int flag = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_SetSurfaceRLE(surface, flag);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetColorKey(surface:SDL_Surface, flag:Number, key:Number)
Gurax_DeclareFunctionAlias(SDL_SetColorKey_gurax, "SDL_SetColorKey")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flag", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("key", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetColorKey_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Surface* surface = args_gurax.Pick<Value_SDL_Surface>().GetEntityPtr();
	int flag = args_gurax.PickNumber<int>();
	Uint32 key = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_SetColorKey(surface, flag, key);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HasColorKey(surface:SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_HasColorKey_gurax, "SDL_HasColorKey")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_HasColorKey_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Surface* surface = args_gurax.Pick<Value_SDL_Surface>().GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_HasColorKey(surface);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_SetSurfaceColorMod(surface:SDL_Surface, r:Number, g:Number, b:Number)
Gurax_DeclareFunctionAlias(SDL_SetSurfaceColorMod_gurax, "SDL_SetSurfaceColorMod")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetSurfaceColorMod_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Surface* surface = args_gurax.Pick<Value_SDL_Surface>().GetEntityPtr();
	Uint8 r = args_gurax.PickNumber<Uint8>();
	Uint8 g = args_gurax.PickNumber<Uint8>();
	Uint8 b = args_gurax.PickNumber<Uint8>();
	// Function body
	int rtn = SDL_SetSurfaceColorMod(surface, r, g, b);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetSurfaceAlphaMod(surface:SDL_Surface, alpha:Number)
Gurax_DeclareFunctionAlias(SDL_SetSurfaceAlphaMod_gurax, "SDL_SetSurfaceAlphaMod")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetSurfaceAlphaMod_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Surface* surface = args_gurax.Pick<Value_SDL_Surface>().GetEntityPtr();
	Uint8 alpha = args_gurax.PickNumber<Uint8>();
	// Function body
	int rtn = SDL_SetSurfaceAlphaMod(surface, alpha);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetSurfaceBlendMode(surface:SDL_Surface, blendMode:Number)
Gurax_DeclareFunctionAlias(SDL_SetSurfaceBlendMode_gurax, "SDL_SetSurfaceBlendMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blendMode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetSurfaceBlendMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Surface* surface = args_gurax.Pick<Value_SDL_Surface>().GetEntityPtr();
	SDL_BlendMode blendMode = args_gurax.PickNumber<SDL_BlendMode>();
	// Function body
	int rtn = SDL_SetSurfaceBlendMode(surface, blendMode);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetClipRect(surface:SDL_Surface, rect:SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_SetClipRect_gurax, "SDL_SetClipRect")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetClipRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Surface* surface = args_gurax.Pick<Value_SDL_Surface>().GetEntityPtr();
	const SDL_Rect* rect = args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_SetClipRect(surface, rect);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_DuplicateSurface(surface:SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_DuplicateSurface_gurax, "SDL_DuplicateSurface")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_DuplicateSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Surface* surface = args_gurax.Pick<Value_SDL_Surface>().GetEntityPtr();
	// Function body
	SDL_Surface* rtn = SDL_DuplicateSurface(surface);
	return new Value_SDL_Surface(rtn);
}

// sdl.SDL_GetWindowWMInfo(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowWMInfo_gurax, "SDL_GetWindowWMInfo")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetWindowWMInfo_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	SDL_SysWMinfo info;
	if (!SDL_GetWindowWMInfo(window, &info)) return Value::nil();
	return new Value_SDL_SysWMinfo(info);
}

// sdl.SDL_SetClipboardText(text:String)
Gurax_DeclareFunctionAlias(SDL_SetClipboardText_gurax, "SDL_SetClipboardText")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetClipboardText_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* text = args_gurax.PickString();
	// Function body
	int rtn = SDL_SetClipboardText(text);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetClipboardText()
Gurax_DeclareFunctionAlias(SDL_GetClipboardText_gurax, "SDL_GetClipboardText")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetClipboardText_gurax, processor_gurax, argument_gurax)
{
	// Function body
	char* rtn = SDL_GetClipboardText();
	RefPtr<Value> pValue(new Value_String(rtn));
	SDL_free(rtn);
	return pValue.release();
}

// sdl.SDL_HasClipboardText()
Gurax_DeclareFunctionAlias(SDL_HasClipboardText_gurax, "SDL_HasClipboardText")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_HasClipboardText_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_HasClipboardText();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_PumpEvents()
Gurax_DeclareFunctionAlias(SDL_PumpEvents_gurax, "SDL_PumpEvents")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_PumpEvents_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_PumpEvents();
	return Gurax::Value::nil();
}

// sdl.SDL_PeepEvents(events:SDL_Event, numevents:Number, action:Number, minType:Number, maxType:Number)
Gurax_DeclareFunctionAlias(SDL_PeepEvents_gurax, "SDL_PeepEvents")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("events", VTYPE_SDL_Event, ArgOccur::Once, ArgFlag::None);
	DeclareArg("numevents", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("action", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("minType", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxType", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_PeepEvents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Event* events = args_gurax.Pick<Value_SDL_Event>().GetEntityPtr();
	int numevents = args_gurax.PickNumber<int>();
	SDL_eventaction action = args_gurax.PickNumber<SDL_eventaction>();
	Uint32 minType = args_gurax.PickNumber<Uint32>();
	Uint32 maxType = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_PeepEvents(events, numevents, action, minType, maxType);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HasEvent(type:Number)
Gurax_DeclareFunctionAlias(SDL_HasEvent_gurax, "SDL_HasEvent")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_HasEvent_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 type = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_bool rtn = SDL_HasEvent(type);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_HasEvents(minType:Number, maxType:Number)
Gurax_DeclareFunctionAlias(SDL_HasEvents_gurax, "SDL_HasEvents")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("minType", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxType", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_HasEvents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 minType = args_gurax.PickNumber<Uint32>();
	Uint32 maxType = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_bool rtn = SDL_HasEvents(minType, maxType);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_FlushEvent(type:Number)
Gurax_DeclareFunctionAlias(SDL_FlushEvent_gurax, "SDL_FlushEvent")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_FlushEvent_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 type = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_FlushEvent(type);
	return Gurax::Value::nil();
}

// sdl.SDL_FlushEvents(minType:Number, maxType:Number)
Gurax_DeclareFunctionAlias(SDL_FlushEvents_gurax, "SDL_FlushEvents")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("minType", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxType", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_FlushEvents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 minType = args_gurax.PickNumber<Uint32>();
	Uint32 maxType = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_FlushEvents(minType, maxType);
	return Gurax::Value::nil();
}

// sdl.SDL_PollEvent(event:SDL_Event)
Gurax_DeclareFunctionAlias(SDL_PollEvent_gurax, "SDL_PollEvent")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("event", VTYPE_SDL_Event, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_PollEvent_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Event* event = args_gurax.Pick<Value_SDL_Event>().GetEntityPtr();
	// Function body
	int rtn = SDL_PollEvent(event);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_WaitEvent(event:SDL_Event)
Gurax_DeclareFunctionAlias(SDL_WaitEvent_gurax, "SDL_WaitEvent")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("event", VTYPE_SDL_Event, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_WaitEvent_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Event* event = args_gurax.Pick<Value_SDL_Event>().GetEntityPtr();
	// Function body
	int rtn = SDL_WaitEvent(event);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_WaitEventTimeout(event:SDL_Event, timeout:Number)
Gurax_DeclareFunctionAlias(SDL_WaitEventTimeout_gurax, "SDL_WaitEventTimeout")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("event", VTYPE_SDL_Event, ArgOccur::Once, ArgFlag::None);
	DeclareArg("timeout", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_WaitEventTimeout_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Event* event = args_gurax.Pick<Value_SDL_Event>().GetEntityPtr();
	int timeout = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_WaitEventTimeout(event, timeout);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_PushEvent(event:SDL_Event)
Gurax_DeclareFunctionAlias(SDL_PushEvent_gurax, "SDL_PushEvent")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("event", VTYPE_SDL_Event, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_PushEvent_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Event* event = args_gurax.Pick<Value_SDL_Event>().GetEntityPtr();
	// Function body
	int rtn = SDL_PushEvent(event);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_EventState(type:Number, state:Number)
Gurax_DeclareFunctionAlias(SDL_EventState_gurax, "SDL_EventState")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("state", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_EventState_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 type = args_gurax.PickNumber<Uint32>();
	int state = args_gurax.PickNumber<int>();
	// Function body
	Uint8 rtn = SDL_EventState(type, state);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RegisterEvents(numevents:Number)
Gurax_DeclareFunctionAlias(SDL_RegisterEvents_gurax, "SDL_RegisterEvents")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("numevents", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_RegisterEvents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int numevents = args_gurax.PickNumber<int>();
	// Function body
	Uint32 rtn = SDL_RegisterEvents(numevents);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetKeyboardFocus()
Gurax_DeclareFunctionAlias(SDL_GetKeyboardFocus_gurax, "SDL_GetKeyboardFocus")
{
	Declare(VTYPE_SDL_Window, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetKeyboardFocus_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Window* rtn = SDL_GetKeyboardFocus();
	return new Value_SDL_Window(rtn);
}

// sdl.SDL_GetModState()
Gurax_DeclareFunctionAlias(SDL_GetModState_gurax, "SDL_GetModState")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetModState_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Keymod rtn = SDL_GetModState();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetModState(modstate:Number)
Gurax_DeclareFunctionAlias(SDL_SetModState_gurax, "SDL_SetModState")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("modstate", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetModState_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Keymod modstate = args_gurax.PickNumber<SDL_Keymod>();
	// Function body
	SDL_SetModState(modstate);
	return Gurax::Value::nil();
}

// sdl.SDL_GetKeyFromScancode(scancode:Number)
Gurax_DeclareFunctionAlias(SDL_GetKeyFromScancode_gurax, "SDL_GetKeyFromScancode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("scancode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetKeyFromScancode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Scancode scancode = args_gurax.PickNumber<SDL_Scancode>();
	// Function body
	SDL_Keycode rtn = SDL_GetKeyFromScancode(scancode);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetScancodeFromKey(key:Number)
Gurax_DeclareFunctionAlias(SDL_GetScancodeFromKey_gurax, "SDL_GetScancodeFromKey")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("key", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetScancodeFromKey_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Keycode key = args_gurax.PickNumber<SDL_Keycode>();
	// Function body
	SDL_Scancode rtn = SDL_GetScancodeFromKey(key);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetScancodeName(scancode:Number)
Gurax_DeclareFunctionAlias(SDL_GetScancodeName_gurax, "SDL_GetScancodeName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("scancode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetScancodeName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Scancode scancode = args_gurax.PickNumber<SDL_Scancode>();
	// Function body
	const char* rtn = SDL_GetScancodeName(scancode);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_GetScancodeFromName(name:String)
Gurax_DeclareFunctionAlias(SDL_GetScancodeFromName_gurax, "SDL_GetScancodeFromName")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetScancodeFromName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	// Function body
	SDL_Scancode rtn = SDL_GetScancodeFromName(name);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetKeyName(key:Number)
Gurax_DeclareFunctionAlias(SDL_GetKeyName_gurax, "SDL_GetKeyName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("key", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetKeyName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Keycode key = args_gurax.PickNumber<SDL_Keycode>();
	// Function body
	const char* rtn = SDL_GetKeyName(key);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_GetKeyFromName(name:String)
Gurax_DeclareFunctionAlias(SDL_GetKeyFromName_gurax, "SDL_GetKeyFromName")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetKeyFromName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	// Function body
	SDL_Keycode rtn = SDL_GetKeyFromName(name);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_StartTextInput()
Gurax_DeclareFunctionAlias(SDL_StartTextInput_gurax, "SDL_StartTextInput")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_StartTextInput_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_StartTextInput();
	return Gurax::Value::nil();
}

// sdl.SDL_IsTextInputActive()
Gurax_DeclareFunctionAlias(SDL_IsTextInputActive_gurax, "SDL_IsTextInputActive")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_IsTextInputActive_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_IsTextInputActive();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_StopTextInput()
Gurax_DeclareFunctionAlias(SDL_StopTextInput_gurax, "SDL_StopTextInput")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_StopTextInput_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_StopTextInput();
	return Gurax::Value::nil();
}

// sdl.SDL_HasScreenKeyboardSupport()
Gurax_DeclareFunctionAlias(SDL_HasScreenKeyboardSupport_gurax, "SDL_HasScreenKeyboardSupport")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_HasScreenKeyboardSupport_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_HasScreenKeyboardSupport();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_IsScreenKeyboardShown(window:SDL_Window)
Gurax_DeclareFunctionAlias(SDL_IsScreenKeyboardShown_gurax, "SDL_IsScreenKeyboardShown")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_IsScreenKeyboardShown_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_IsScreenKeyboardShown(window);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_GetMouseFocus()
Gurax_DeclareFunctionAlias(SDL_GetMouseFocus_gurax, "SDL_GetMouseFocus")
{
	Declare(VTYPE_SDL_Window, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetMouseFocus_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Window* rtn = SDL_GetMouseFocus();
	return new Value_SDL_Window(rtn);
}

// sdl.SDL_WarpMouseInWindow(window:SDL_Window, x:Number, y:Number)
Gurax_DeclareFunctionAlias(SDL_WarpMouseInWindow_gurax, "SDL_WarpMouseInWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_WarpMouseInWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.Pick<Value_SDL_Window>().GetEntityPtr();
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	// Function body
	SDL_WarpMouseInWindow(window, x, y);
	return Gurax::Value::nil();
}

// sdl.SDL_WarpMouseGlobal(x:Number, y:Number)
Gurax_DeclareFunctionAlias(SDL_WarpMouseGlobal_gurax, "SDL_WarpMouseGlobal")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_WarpMouseGlobal_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_WarpMouseGlobal(x, y);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetRelativeMouseMode(enabled:Bool)
Gurax_DeclareFunctionAlias(SDL_SetRelativeMouseMode_gurax, "SDL_SetRelativeMouseMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("enabled", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetRelativeMouseMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_bool enabled = static_cast<SDL_bool>(args_gurax.PickBool());
	// Function body
	int rtn = SDL_SetRelativeMouseMode(enabled);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_CaptureMouse(enabled:Bool)
Gurax_DeclareFunctionAlias(SDL_CaptureMouse_gurax, "SDL_CaptureMouse")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("enabled", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_CaptureMouse_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_bool enabled = static_cast<SDL_bool>(args_gurax.PickBool());
	// Function body
	int rtn = SDL_CaptureMouse(enabled);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetRelativeMouseMode()
Gurax_DeclareFunctionAlias(SDL_GetRelativeMouseMode_gurax, "SDL_GetRelativeMouseMode")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetRelativeMouseMode_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_GetRelativeMouseMode();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_CreateCursor(data:Pointer, mask:Pointer, w:Number, h:Number, hot_x:Number, hot_y:Number)
Gurax_DeclareFunctionAlias(SDL_CreateCursor_gurax, "SDL_CreateCursor")
{
	Declare(VTYPE_SDL_Cursor, Flag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mask", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hot_x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hot_y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_CreateCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Uint8* data = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<Uint8>();
	const Uint8* mask = args_gurax.Pick<Value_Pointer>().GetPointer().GetPointerC<Uint8>();
	int w = args_gurax.PickNumber<int>();
	int h = args_gurax.PickNumber<int>();
	int hot_x = args_gurax.PickNumber<int>();
	int hot_y = args_gurax.PickNumber<int>();
	// Function body
	SDL_Cursor* rtn = SDL_CreateCursor(data, mask, w, h, hot_x, hot_y);
	return new Value_SDL_Cursor(rtn);
}

// sdl.SDL_CreateColorCursor(surface:SDL_Surface, hot_x:Number, hot_y:Number)
Gurax_DeclareFunctionAlias(SDL_CreateColorCursor_gurax, "SDL_CreateColorCursor")
{
	Declare(VTYPE_SDL_Cursor, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hot_x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hot_y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_CreateColorCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Surface* surface = args_gurax.Pick<Value_SDL_Surface>().GetEntityPtr();
	int hot_x = args_gurax.PickNumber<int>();
	int hot_y = args_gurax.PickNumber<int>();
	// Function body
	SDL_Cursor* rtn = SDL_CreateColorCursor(surface, hot_x, hot_y);
	return new Value_SDL_Cursor(rtn);
}

// sdl.SDL_CreateSystemCursor(id:Number)
Gurax_DeclareFunctionAlias(SDL_CreateSystemCursor_gurax, "SDL_CreateSystemCursor")
{
	Declare(VTYPE_SDL_Cursor, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_CreateSystemCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_SystemCursor id = args_gurax.PickNumber<SDL_SystemCursor>();
	// Function body
	SDL_Cursor* rtn = SDL_CreateSystemCursor(id);
	return new Value_SDL_Cursor(rtn);
}

// sdl.SDL_SetCursor(cursor:SDL_Cursor)
Gurax_DeclareFunctionAlias(SDL_SetCursor_gurax, "SDL_SetCursor")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cursor", VTYPE_SDL_Cursor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_SetCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Cursor* cursor = args_gurax.Pick<Value_SDL_Cursor>().GetEntityPtr();
	// Function body
	SDL_SetCursor(cursor);
	return Gurax::Value::nil();
}

// sdl.SDL_GetCursor()
Gurax_DeclareFunctionAlias(SDL_GetCursor_gurax, "SDL_GetCursor")
{
	Declare(VTYPE_SDL_Cursor, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetCursor_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Cursor* rtn = SDL_GetCursor();
	return new Value_SDL_Cursor(rtn);
}

// sdl.SDL_GetDefaultCursor()
Gurax_DeclareFunctionAlias(SDL_GetDefaultCursor_gurax, "SDL_GetDefaultCursor")
{
	Declare(VTYPE_SDL_Cursor, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GetDefaultCursor_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Cursor* rtn = SDL_GetDefaultCursor();
	return new Value_SDL_Cursor(rtn);
}

// sdl.SDL_FreeCursor(cursor:SDL_Cursor)
Gurax_DeclareFunctionAlias(SDL_FreeCursor_gurax, "SDL_FreeCursor")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cursor", VTYPE_SDL_Cursor, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_FreeCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Cursor* cursor = args_gurax.Pick<Value_SDL_Cursor>().GetEntityPtr();
	// Function body
	SDL_FreeCursor(cursor);
	return Gurax::Value::nil();
}

// sdl.SDL_ShowCursor(toggle:Number)
Gurax_DeclareFunctionAlias(SDL_ShowCursor_gurax, "SDL_ShowCursor")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("toggle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_ShowCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int toggle = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_ShowCursor(toggle);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_LockJoysticks()
Gurax_DeclareFunctionAlias(SDL_LockJoysticks_gurax, "SDL_LockJoysticks")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_LockJoysticks_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_LockJoysticks();
	return Gurax::Value::nil();
}

// sdl.SDL_UnlockJoysticks()
Gurax_DeclareFunctionAlias(SDL_UnlockJoysticks_gurax, "SDL_UnlockJoysticks")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_UnlockJoysticks_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_UnlockJoysticks();
	return Gurax::Value::nil();
}

// sdl.SDL_NumJoysticks()
Gurax_DeclareFunctionAlias(SDL_NumJoysticks_gurax, "SDL_NumJoysticks")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_NumJoysticks_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_NumJoysticks();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickNameForIndex(device_index:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickNameForIndex_gurax, "SDL_JoystickNameForIndex")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickNameForIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	const char* rtn = SDL_JoystickNameForIndex(device_index);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_JoystickGetDevicePlayerIndex(device_index:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetDevicePlayerIndex_gurax, "SDL_JoystickGetDevicePlayerIndex")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetDevicePlayerIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_JoystickGetDevicePlayerIndex(device_index);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetDeviceGUID(device_index:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetDeviceGUID_gurax, "SDL_JoystickGetDeviceGUID")
{
	Declare(VTYPE_SDL_JoystickGUID, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetDeviceGUID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_JoystickGUID rtn = SDL_JoystickGetDeviceGUID(device_index);
	return new Value_SDL_JoystickGUID(rtn);
}

// sdl.SDL_JoystickGetDeviceVendor(device_index:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetDeviceVendor_gurax, "SDL_JoystickGetDeviceVendor")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetDeviceVendor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	Uint16 rtn = SDL_JoystickGetDeviceVendor(device_index);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetDeviceProduct(device_index:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetDeviceProduct_gurax, "SDL_JoystickGetDeviceProduct")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetDeviceProduct_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	Uint16 rtn = SDL_JoystickGetDeviceProduct(device_index);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetDeviceProductVersion(device_index:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetDeviceProductVersion_gurax, "SDL_JoystickGetDeviceProductVersion")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetDeviceProductVersion_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	Uint16 rtn = SDL_JoystickGetDeviceProductVersion(device_index);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetDeviceType(device_index:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetDeviceType_gurax, "SDL_JoystickGetDeviceType")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetDeviceType_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_JoystickType rtn = SDL_JoystickGetDeviceType(device_index);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetDeviceInstanceID(device_index:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetDeviceInstanceID_gurax, "SDL_JoystickGetDeviceInstanceID")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetDeviceInstanceID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_JoystickID rtn = SDL_JoystickGetDeviceInstanceID(device_index);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickOpen(device_index:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickOpen_gurax, "SDL_JoystickOpen")
{
	Declare(VTYPE_SDL_Joystick, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickOpen_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_Joystick* rtn = SDL_JoystickOpen(device_index);
	return new Value_SDL_Joystick(rtn);
}

// sdl.SDL_JoystickFromInstanceID(instance_id:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickFromInstanceID_gurax, "SDL_JoystickFromInstanceID")
{
	Declare(VTYPE_SDL_Joystick, Flag::None);
	DeclareArg("instance_id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickFromInstanceID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_JoystickID instance_id = args_gurax.PickNumber<SDL_JoystickID>();
	// Function body
	SDL_Joystick* rtn = SDL_JoystickFromInstanceID(instance_id);
	return new Value_SDL_Joystick(rtn);
}

// sdl.SDL_JoystickFromPlayerIndex(player_index:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickFromPlayerIndex_gurax, "SDL_JoystickFromPlayerIndex")
{
	Declare(VTYPE_SDL_Joystick, Flag::None);
	DeclareArg("player_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickFromPlayerIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int player_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_Joystick* rtn = SDL_JoystickFromPlayerIndex(player_index);
	return new Value_SDL_Joystick(rtn);
}

// sdl.SDL_JoystickName(joystick:SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickName_gurax, "SDL_JoystickName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	// Function body
	const char* rtn = SDL_JoystickName(joystick);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_JoystickGetPlayerIndex(joystick:SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickGetPlayerIndex_gurax, "SDL_JoystickGetPlayerIndex")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetPlayerIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	// Function body
	int rtn = SDL_JoystickGetPlayerIndex(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickSetPlayerIndex(joystick:SDL_Joystick, player_index:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickSetPlayerIndex_gurax, "SDL_JoystickSetPlayerIndex")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	DeclareArg("player_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickSetPlayerIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	int player_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_JoystickSetPlayerIndex(joystick, player_index);
	return Gurax::Value::nil();
}

// sdl.SDL_JoystickGetGUID(joystick:SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickGetGUID_gurax, "SDL_JoystickGetGUID")
{
	Declare(VTYPE_SDL_JoystickGUID, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetGUID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	// Function body
	SDL_JoystickGUID rtn = SDL_JoystickGetGUID(joystick);
	return new Value_SDL_JoystickGUID(rtn);
}

// sdl.SDL_JoystickGetVendor(joystick:SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickGetVendor_gurax, "SDL_JoystickGetVendor")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetVendor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	// Function body
	Uint16 rtn = SDL_JoystickGetVendor(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetProduct(joystick:SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickGetProduct_gurax, "SDL_JoystickGetProduct")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetProduct_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	// Function body
	Uint16 rtn = SDL_JoystickGetProduct(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetProductVersion(joystick:SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickGetProductVersion_gurax, "SDL_JoystickGetProductVersion")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetProductVersion_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	// Function body
	Uint16 rtn = SDL_JoystickGetProductVersion(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetType(joystick:SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickGetType_gurax, "SDL_JoystickGetType")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetType_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	// Function body
	SDL_JoystickType rtn = SDL_JoystickGetType(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetGUIDFromString(pchGUID:String)
Gurax_DeclareFunctionAlias(SDL_JoystickGetGUIDFromString_gurax, "SDL_JoystickGetGUIDFromString")
{
	Declare(VTYPE_SDL_JoystickGUID, Flag::None);
	DeclareArg("pchGUID", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetGUIDFromString_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* pchGUID = args_gurax.PickString();
	// Function body
	SDL_JoystickGUID rtn = SDL_JoystickGetGUIDFromString(pchGUID);
	return new Value_SDL_JoystickGUID(rtn);
}

// sdl.SDL_JoystickGetAttached(joystick:SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickGetAttached_gurax, "SDL_JoystickGetAttached")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetAttached_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_JoystickGetAttached(joystick);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_JoystickInstanceID(joystick:SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickInstanceID_gurax, "SDL_JoystickInstanceID")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickInstanceID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	// Function body
	SDL_JoystickID rtn = SDL_JoystickInstanceID(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickNumAxes(joystick:SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickNumAxes_gurax, "SDL_JoystickNumAxes")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickNumAxes_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	// Function body
	int rtn = SDL_JoystickNumAxes(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickNumBalls(joystick:SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickNumBalls_gurax, "SDL_JoystickNumBalls")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickNumBalls_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	// Function body
	int rtn = SDL_JoystickNumBalls(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickNumHats(joystick:SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickNumHats_gurax, "SDL_JoystickNumHats")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickNumHats_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	// Function body
	int rtn = SDL_JoystickNumHats(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickNumButtons(joystick:SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickNumButtons_gurax, "SDL_JoystickNumButtons")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickNumButtons_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	// Function body
	int rtn = SDL_JoystickNumButtons(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickUpdate()
Gurax_DeclareFunctionAlias(SDL_JoystickUpdate_gurax, "SDL_JoystickUpdate")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickUpdate_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_JoystickUpdate();
	return Gurax::Value::nil();
}

// sdl.SDL_JoystickEventState(state:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickEventState_gurax, "SDL_JoystickEventState")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("state", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickEventState_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int state = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_JoystickEventState(state);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetAxis(joystick:SDL_Joystick, axis:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetAxis_gurax, "SDL_JoystickGetAxis")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	DeclareArg("axis", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetAxis_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	int axis = args_gurax.PickNumber<int>();
	// Function body
	Sint16 rtn = SDL_JoystickGetAxis(joystick, axis);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetHat(joystick:SDL_Joystick, hat:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetHat_gurax, "SDL_JoystickGetHat")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetHat_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	int hat = args_gurax.PickNumber<int>();
	// Function body
	Uint8 rtn = SDL_JoystickGetHat(joystick, hat);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetButton(joystick:SDL_Joystick, button:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetButton_gurax, "SDL_JoystickGetButton")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	DeclareArg("button", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickGetButton_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	int button = args_gurax.PickNumber<int>();
	// Function body
	Uint8 rtn = SDL_JoystickGetButton(joystick, button);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickRumble(joystick:SDL_Joystick, low_frequency_rumble:Number, high_frequency_rumble:Number, duration_ms:Number)
Gurax_DeclareFunctionAlias(SDL_JoystickRumble_gurax, "SDL_JoystickRumble")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	DeclareArg("low_frequency_rumble", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("high_frequency_rumble", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("duration_ms", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickRumble_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	Uint16 low_frequency_rumble = args_gurax.PickNumber<Uint16>();
	Uint16 high_frequency_rumble = args_gurax.PickNumber<Uint16>();
	Uint32 duration_ms = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_JoystickRumble(joystick, low_frequency_rumble, high_frequency_rumble, duration_ms);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickClose(joystick:SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickClose_gurax, "SDL_JoystickClose")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickClose_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	// Function body
	SDL_JoystickClose(joystick);
	return Gurax::Value::nil();
}

// sdl.SDL_JoystickCurrentPowerLevel(joystick:SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickCurrentPowerLevel_gurax, "SDL_JoystickCurrentPowerLevel")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_JoystickCurrentPowerLevel_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Joystick* joystick = args_gurax.Pick<Value_SDL_Joystick>().GetEntityPtr();
	// Function body
	SDL_JoystickPowerLevel rtn = SDL_JoystickCurrentPowerLevel(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerAddMapping(mappingString:String)
Gurax_DeclareFunctionAlias(SDL_GameControllerAddMapping_gurax, "SDL_GameControllerAddMapping")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("mappingString", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerAddMapping_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* mappingString = args_gurax.PickString();
	// Function body
	int rtn = SDL_GameControllerAddMapping(mappingString);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerNumMappings()
Gurax_DeclareFunctionAlias(SDL_GameControllerNumMappings_gurax, "SDL_GameControllerNumMappings")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerNumMappings_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_GameControllerNumMappings();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_IsGameController(joystick_index:Number)
Gurax_DeclareFunctionAlias(SDL_IsGameController_gurax, "SDL_IsGameController")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("joystick_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_IsGameController_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int joystick_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_bool rtn = SDL_IsGameController(joystick_index);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_GameControllerNameForIndex(joystick_index:Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerNameForIndex_gurax, "SDL_GameControllerNameForIndex")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("joystick_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerNameForIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int joystick_index = args_gurax.PickNumber<int>();
	// Function body
	const char* rtn = SDL_GameControllerNameForIndex(joystick_index);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_GameControllerTypeForIndex(joystick_index:Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerTypeForIndex_gurax, "SDL_GameControllerTypeForIndex")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerTypeForIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int joystick_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_GameControllerType rtn = SDL_GameControllerTypeForIndex(joystick_index);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerOpen(joystick_index:Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerOpen_gurax, "SDL_GameControllerOpen")
{
	Declare(VTYPE_SDL_GameController_p, Flag::None);
	DeclareArg("joystick_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerOpen_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int joystick_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_GameController_p rtn = SDL_GameControllerOpen(joystick_index);
	return new Value_SDL_GameController_p(rtn);
}

// sdl.SDL_GameControllerFromInstanceID(joyid:Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerFromInstanceID_gurax, "SDL_GameControllerFromInstanceID")
{
	Declare(VTYPE_SDL_GameController_p, Flag::None);
	DeclareArg("joyid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerFromInstanceID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_JoystickID joyid = args_gurax.PickNumber<SDL_JoystickID>();
	// Function body
	SDL_GameController_p rtn = SDL_GameControllerFromInstanceID(joyid);
	return new Value_SDL_GameController_p(rtn);
}

// sdl.SDL_GameControllerFromPlayerIndex(player_index:Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerFromPlayerIndex_gurax, "SDL_GameControllerFromPlayerIndex")
{
	Declare(VTYPE_SDL_GameController_p, Flag::None);
	DeclareArg("player_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerFromPlayerIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int player_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_GameController_p rtn = SDL_GameControllerFromPlayerIndex(player_index);
	return new Value_SDL_GameController_p(rtn);
}

// sdl.SDL_GameControllerName(gamecontroller:SDL_GameController_p)
Gurax_DeclareFunctionAlias(SDL_GameControllerName_gurax, "SDL_GameControllerName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController_p, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameController_p gamecontroller = args_gurax.Pick<Value_SDL_GameController_p>().GetEntityPtr();
	// Function body
	const char* rtn = SDL_GameControllerName(gamecontroller);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_GameControllerGetType(gamecontroller:SDL_GameController_p)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetType_gurax, "SDL_GameControllerGetType")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController_p, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetType_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameController_p gamecontroller = args_gurax.Pick<Value_SDL_GameController_p>().GetEntityPtr();
	// Function body
	SDL_GameControllerType rtn = SDL_GameControllerGetType(gamecontroller);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerGetPlayerIndex(gamecontroller:SDL_GameController_p)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetPlayerIndex_gurax, "SDL_GameControllerGetPlayerIndex")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController_p, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetPlayerIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameController_p gamecontroller = args_gurax.Pick<Value_SDL_GameController_p>().GetEntityPtr();
	// Function body
	int rtn = SDL_GameControllerGetPlayerIndex(gamecontroller);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerSetPlayerIndex(gamecontroller:SDL_GameController_p, player_index:Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerSetPlayerIndex_gurax, "SDL_GameControllerSetPlayerIndex")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController_p, ArgOccur::Once, ArgFlag::None);
	DeclareArg("player_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerSetPlayerIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameController_p gamecontroller = args_gurax.Pick<Value_SDL_GameController_p>().GetEntityPtr();
	int player_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_GameControllerSetPlayerIndex(gamecontroller, player_index);
	return Gurax::Value::nil();
}

// sdl.SDL_GameControllerGetVendor(gamecontroller:SDL_GameController_p)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetVendor_gurax, "SDL_GameControllerGetVendor")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController_p, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetVendor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameController_p gamecontroller = args_gurax.Pick<Value_SDL_GameController_p>().GetEntityPtr();
	// Function body
	Uint16 rtn = SDL_GameControllerGetVendor(gamecontroller);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerGetProduct(gamecontroller:SDL_GameController_p)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetProduct_gurax, "SDL_GameControllerGetProduct")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController_p, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetProduct_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameController_p gamecontroller = args_gurax.Pick<Value_SDL_GameController_p>().GetEntityPtr();
	// Function body
	Uint16 rtn = SDL_GameControllerGetProduct(gamecontroller);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerGetProductVersion(gamecontroller:SDL_GameController_p)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetProductVersion_gurax, "SDL_GameControllerGetProductVersion")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController_p, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetProductVersion_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameController_p gamecontroller = args_gurax.Pick<Value_SDL_GameController_p>().GetEntityPtr();
	// Function body
	Uint16 rtn = SDL_GameControllerGetProductVersion(gamecontroller);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerGetAttached(gamecontroller:SDL_GameController_p)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetAttached_gurax, "SDL_GameControllerGetAttached")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController_p, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetAttached_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameController_p gamecontroller = args_gurax.Pick<Value_SDL_GameController_p>().GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_GameControllerGetAttached(gamecontroller);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_GameControllerGetJoystick(gamecontroller:SDL_GameController_p)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetJoystick_gurax, "SDL_GameControllerGetJoystick")
{
	Declare(VTYPE_SDL_Joystick, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController_p, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetJoystick_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameController_p gamecontroller = args_gurax.Pick<Value_SDL_GameController_p>().GetEntityPtr();
	// Function body
	SDL_Joystick* rtn = SDL_GameControllerGetJoystick(gamecontroller);
	return new Value_SDL_Joystick(rtn);
}

// sdl.SDL_GameControllerEventState(state:Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerEventState_gurax, "SDL_GameControllerEventState")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("state", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerEventState_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int state = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_GameControllerEventState(state);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerUpdate()
Gurax_DeclareFunctionAlias(SDL_GameControllerUpdate_gurax, "SDL_GameControllerUpdate")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerUpdate_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_GameControllerUpdate();
	return Gurax::Value::nil();
}

// sdl.SDL_GameControllerGetAxisFromString(pchString:String)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetAxisFromString_gurax, "SDL_GameControllerGetAxisFromString")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("pchString", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetAxisFromString_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* pchString = args_gurax.PickString();
	// Function body
	SDL_GameControllerAxis rtn = SDL_GameControllerGetAxisFromString(pchString);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerGetStringForAxis(axis:Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetStringForAxis_gurax, "SDL_GameControllerGetStringForAxis")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("axis", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetStringForAxis_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameControllerAxis axis = args_gurax.PickNumber<SDL_GameControllerAxis>();
	// Function body
	const char* rtn = SDL_GameControllerGetStringForAxis(axis);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_GameControllerGetBindForAxis(gamecontroller:SDL_GameController_p, axis:Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetBindForAxis_gurax, "SDL_GameControllerGetBindForAxis")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController_p, ArgOccur::Once, ArgFlag::None);
	DeclareArg("axis", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetBindForAxis_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameController_p gamecontroller = args_gurax.Pick<Value_SDL_GameController_p>().GetEntityPtr();
	SDL_GameControllerAxis axis = args_gurax.PickNumber<SDL_GameControllerAxis>();
	// Function body
	SDL_GameControllerButtonBind rtn = SDL_GameControllerGetBindForAxis(gamecontroller, axis);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerGetAxis(gamecontroller:SDL_GameController_p, axis:Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetAxis_gurax, "SDL_GameControllerGetAxis")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController_p, ArgOccur::Once, ArgFlag::None);
	DeclareArg("axis", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetAxis_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameController_p gamecontroller = args_gurax.Pick<Value_SDL_GameController_p>().GetEntityPtr();
	SDL_GameControllerAxis axis = args_gurax.PickNumber<SDL_GameControllerAxis>();
	// Function body
	Sint16 rtn = SDL_GameControllerGetAxis(gamecontroller, axis);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerGetButtonFromString(pchString:String)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetButtonFromString_gurax, "SDL_GameControllerGetButtonFromString")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("pchString", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetButtonFromString_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* pchString = args_gurax.PickString();
	// Function body
	SDL_GameControllerButton rtn = SDL_GameControllerGetButtonFromString(pchString);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerGetStringForButton(button:Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetStringForButton_gurax, "SDL_GameControllerGetStringForButton")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("button", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetStringForButton_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameControllerButton button = args_gurax.PickNumber<SDL_GameControllerButton>();
	// Function body
	const char* rtn = SDL_GameControllerGetStringForButton(button);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_GameControllerGetBindForButton(gamecontroller:SDL_GameController_p, button:Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetBindForButton_gurax, "SDL_GameControllerGetBindForButton")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController_p, ArgOccur::Once, ArgFlag::None);
	DeclareArg("button", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetBindForButton_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameController_p gamecontroller = args_gurax.Pick<Value_SDL_GameController_p>().GetEntityPtr();
	SDL_GameControllerButton button = args_gurax.PickNumber<SDL_GameControllerButton>();
	// Function body
	SDL_GameControllerButtonBind rtn = SDL_GameControllerGetBindForButton(gamecontroller, button);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerGetButton(gamecontroller:SDL_GameController_p, button:Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetButton_gurax, "SDL_GameControllerGetButton")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController_p, ArgOccur::Once, ArgFlag::None);
	DeclareArg("button", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetButton_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameController_p gamecontroller = args_gurax.Pick<Value_SDL_GameController_p>().GetEntityPtr();
	SDL_GameControllerButton button = args_gurax.PickNumber<SDL_GameControllerButton>();
	// Function body
	Uint8 rtn = SDL_GameControllerGetButton(gamecontroller, button);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerRumble(gamecontroller:SDL_GameController_p, low_frequency_rumble:Number, high_frequency_rumble:Number, duration_ms:Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerRumble_gurax, "SDL_GameControllerRumble")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController_p, ArgOccur::Once, ArgFlag::None);
	DeclareArg("low_frequency_rumble", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("high_frequency_rumble", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("duration_ms", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerRumble_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameController_p gamecontroller = args_gurax.Pick<Value_SDL_GameController_p>().GetEntityPtr();
	Uint16 low_frequency_rumble = args_gurax.PickNumber<Uint16>();
	Uint16 high_frequency_rumble = args_gurax.PickNumber<Uint16>();
	Uint32 duration_ms = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_GameControllerRumble(gamecontroller, low_frequency_rumble, high_frequency_rumble, duration_ms);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerClose(gamecontroller:SDL_GameController_p)
Gurax_DeclareFunctionAlias(SDL_GameControllerClose_gurax, "SDL_GameControllerClose")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController_p, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(SDL_GameControllerClose_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GameController_p gamecontroller = args_gurax.Pick<Value_SDL_GameController_p>().GetEntityPtr();
	// Function body
	SDL_GameControllerClose(gamecontroller);
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
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowOpacity_gurax));
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
	frame.Assign(Gurax_CreateFunction(SDL_RenderGetLogicalSize_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderSetIntegerScale_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderGetIntegerScale_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderSetViewport_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderGetViewport_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderSetClipRect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderGetClipRect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderIsClipEnabled_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderSetScale_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderGetScale_gurax));
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
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawPointsF_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawLineF_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawRectF_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderFillRectF_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderCopyF_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderReadPixels_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderPresent_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_DestroyTexture_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_DestroyRenderer_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderFlush_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_UnbindTexture_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetPixelFormatName_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_MasksToPixelFormatEnum_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasIntersection_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_IntersectRect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_UnionRect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_IntersectRectAndLine_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetSurfaceRLE_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetColorKey_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasColorKey_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetSurfaceColorMod_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetSurfaceAlphaMod_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetSurfaceBlendMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetClipRect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_DuplicateSurface_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowWMInfo_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetClipboardText_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetClipboardText_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasClipboardText_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_PumpEvents_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_PeepEvents_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasEvent_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasEvents_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_FlushEvent_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_FlushEvents_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_PollEvent_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_WaitEvent_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_WaitEventTimeout_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_PushEvent_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_EventState_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RegisterEvents_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetKeyboardFocus_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetModState_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetModState_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetKeyFromScancode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetScancodeFromKey_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetScancodeName_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetScancodeFromName_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetKeyName_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetKeyFromName_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_StartTextInput_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_IsTextInputActive_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_StopTextInput_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasScreenKeyboardSupport_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_IsScreenKeyboardShown_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetMouseFocus_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_WarpMouseInWindow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_WarpMouseGlobal_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetRelativeMouseMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CaptureMouse_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetRelativeMouseMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CreateCursor_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CreateColorCursor_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CreateSystemCursor_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetCursor_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetCursor_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetDefaultCursor_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_FreeCursor_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ShowCursor_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_LockJoysticks_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_UnlockJoysticks_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_NumJoysticks_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickNameForIndex_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetDevicePlayerIndex_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetDeviceGUID_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetDeviceVendor_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetDeviceProduct_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetDeviceProductVersion_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetDeviceType_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetDeviceInstanceID_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickOpen_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickFromInstanceID_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickFromPlayerIndex_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickName_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetPlayerIndex_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickSetPlayerIndex_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetGUID_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetVendor_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetProduct_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetProductVersion_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetType_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetGUIDFromString_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetAttached_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickInstanceID_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickNumAxes_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickNumBalls_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickNumHats_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickNumButtons_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickUpdate_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickEventState_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetAxis_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetHat_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetButton_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickRumble_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickClose_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickCurrentPowerLevel_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerAddMapping_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerNumMappings_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_IsGameController_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerNameForIndex_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerTypeForIndex_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerOpen_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerFromInstanceID_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerFromPlayerIndex_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerName_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetType_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetPlayerIndex_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerSetPlayerIndex_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetVendor_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetProduct_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetProductVersion_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetAttached_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetJoystick_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerEventState_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerUpdate_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetAxisFromString_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetStringForAxis_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetBindForAxis_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetAxis_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetButtonFromString_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetStringForButton_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetBindForButton_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetButton_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerRumble_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerClose_gurax));
}

Gurax_EndModuleScope(sdl)
