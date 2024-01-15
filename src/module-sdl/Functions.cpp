//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

// sdl.SDL_Init(flags as Number)
Gurax_DeclareFunctionAlias(SDL_Init_gurax, "SDL_Init")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_InitSubSystem(flags as Number)
Gurax_DeclareFunctionAlias(SDL_InitSubSystem_gurax, "SDL_InitSubSystem")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_QuitSubSystem(flags as Number)
Gurax_DeclareFunctionAlias(SDL_QuitSubSystem_gurax, "SDL_QuitSubSystem")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_WasInit(flags as Number)
Gurax_DeclareFunctionAlias(SDL_WasInit_gurax, "SDL_WasInit")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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
}

Gurax_ImplementFunctionEx(SDL_Quit_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Quit();
	return Gurax::Value::nil();
}

// sdl.SDL_SetHintWithPriority(name as String, value as String, priority as Number)
Gurax_DeclareFunctionAlias(SDL_SetHintWithPriority_gurax, "SDL_SetHintWithPriority")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("priority", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_SetHint(name as String, value as String)
Gurax_DeclareFunctionAlias(SDL_SetHint_gurax, "SDL_SetHint")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GetHint(name as String)
Gurax_DeclareFunctionAlias(SDL_GetHint_gurax, "SDL_GetHint")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GetHintBoolean(name as String, default_value as Bool)
Gurax_DeclareFunctionAlias(SDL_GetHintBoolean_gurax, "SDL_GetHintBoolean")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("default_value", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
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
}

Gurax_ImplementFunctionEx(SDL_ClearError_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_ClearError();
	return Gurax::Value::nil();
}

// sdl.SDL_Error(code as Number)
Gurax_DeclareFunctionAlias(SDL_Error_gurax, "SDL_Error")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("code", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_LogSetAllPriority(priority as Number)
Gurax_DeclareFunctionAlias(SDL_LogSetAllPriority_gurax, "SDL_LogSetAllPriority")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("priority", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_LogSetPriority(category as Number, priority as Number)
Gurax_DeclareFunctionAlias(SDL_LogSetPriority_gurax, "SDL_LogSetPriority")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("category", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("priority", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_LogGetPriority(category as Number)
Gurax_DeclareFunctionAlias(SDL_LogGetPriority_gurax, "SDL_LogGetPriority")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("category", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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
}

Gurax_ImplementFunctionEx(SDL_ResetAssertionReport_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_ResetAssertionReport();
	return Gurax::Value::nil();
}

// sdl.SDL_GetVersion()
Gurax_DeclareFunctionAlias(SDL_GetVersion_gurax, "SDL_GetVersion")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetVersion_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_version ver;
	SDL_GetVersion(&ver);
	return new Value_SDL_version(ver);
}

// sdl.SDL_GetRevision()
Gurax_DeclareFunctionAlias(SDL_GetRevision_gurax, "SDL_GetRevision")
{
	Declare(VTYPE_String, Flag::None);
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
}

Gurax_ImplementFunctionEx(SDL_GetNumVideoDrivers_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_GetNumVideoDrivers();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetVideoDriver(index as Number)
Gurax_DeclareFunctionAlias(SDL_GetVideoDriver_gurax, "SDL_GetVideoDriver")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_VideoInit(driver_name as String)
Gurax_DeclareFunctionAlias(SDL_VideoInit_gurax, "SDL_VideoInit")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("driver_name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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
}

Gurax_ImplementFunctionEx(SDL_GetNumVideoDisplays_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_GetNumVideoDisplays();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetDisplayName(displayIndex as Number)
Gurax_DeclareFunctionAlias(SDL_GetDisplayName_gurax, "SDL_GetDisplayName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GetDisplayBounds(displayIndex as Number, &rect:nilRef as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_GetDisplayBounds_gurax, "SDL_GetDisplayBounds")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetDisplayBounds_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int displayIndex = args_gurax.PickNumber<int>();
	RefPtr<Referencer> rect(args_gurax.PickReferencer().Reference());
	// Function body
	SDL_Rect rect_;
	int rtn = SDL_GetDisplayBounds(displayIndex, &rect_);
	rect->SetValue(new Value_SDL_Rect(rect_));
	return new Value_Number(rtn);
}

// sdl.SDL_GetDisplayUsableBounds(displayIndex as Number, &rect:nilRef as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_GetDisplayUsableBounds_gurax, "SDL_GetDisplayUsableBounds")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetDisplayUsableBounds_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int displayIndex = args_gurax.PickNumber<int>();
	RefPtr<Referencer> rect(args_gurax.PickReferencer().Reference());
	// Function body
	SDL_Rect rect_;
	int rtn = SDL_GetDisplayUsableBounds(displayIndex, &rect_);
	rect->SetValue(new Value_SDL_Rect(rect_));
	return new Value_Number(rtn);
}

// sdl.SDL_GetDisplayDPI(displayIndex as Number, &ddpi:nilRef as Number, &hdpi:nilRef as Number, &vdpi:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GetDisplayDPI_gurax, "SDL_GetDisplayDPI")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ddpi", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("hdpi", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("vdpi", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetDisplayDPI_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int displayIndex = args_gurax.PickNumber<int>();
	RefPtr<Referencer> ddpi(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> hdpi(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> vdpi(args_gurax.PickReferencer().Reference());
	// Function body
	float ddpi_, hdpi_, vdpi_;
	int rtn = SDL_GetDisplayDPI(displayIndex, &ddpi_, &hdpi_, &vdpi_);
	ddpi->SetValue(new Value_Number(ddpi_));
	hdpi->SetValue(new Value_Number(hdpi_));
	vdpi->SetValue(new Value_Number(vdpi_));
	return new Value_Number(rtn);
}

// sdl.SDL_GetDisplayOrientation(displayIndex as Number)
Gurax_DeclareFunctionAlias(SDL_GetDisplayOrientation_gurax, "SDL_GetDisplayOrientation")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GetNumDisplayModes(displayIndex as Number)
Gurax_DeclareFunctionAlias(SDL_GetNumDisplayModes_gurax, "SDL_GetNumDisplayModes")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GetDisplayMode(displayIndex as Number, modeIndex as Number, &mode:nilRef as SDL_DisplayMode)
Gurax_DeclareFunctionAlias(SDL_GetDisplayMode_gurax, "SDL_GetDisplayMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("modeIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_SDL_DisplayMode, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetDisplayMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int displayIndex = args_gurax.PickNumber<int>();
	int modeIndex = args_gurax.PickNumber<int>();
	RefPtr<Referencer> mode(args_gurax.PickReferencer().Reference());
	// Function body
	SDL_DisplayMode mode_ = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
	int rtn = SDL_GetDisplayMode(displayIndex, modeIndex, &mode_);
	mode->SetValue(new Value_SDL_DisplayMode(mode_));
	return new Value_Number(rtn);
}

// sdl.SDL_GetDesktopDisplayMode(displayIndex as Number, &mode:nilRef as SDL_DisplayMode)
Gurax_DeclareFunctionAlias(SDL_GetDesktopDisplayMode_gurax, "SDL_GetDesktopDisplayMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_SDL_DisplayMode, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetDesktopDisplayMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int displayIndex = args_gurax.PickNumber<int>();
	RefPtr<Referencer> mode(args_gurax.PickReferencer().Reference());
	// Function body
	SDL_DisplayMode mode_ = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
	int rtn = SDL_GetDesktopDisplayMode(displayIndex, &mode_);
	mode->SetValue(new Value_SDL_DisplayMode(mode_));
	return new Value_Number(rtn);
}

// sdl.SDL_GetCurrentDisplayMode(displayIndex as Number, &mode:nilRef as SDL_DisplayMode)
Gurax_DeclareFunctionAlias(SDL_GetCurrentDisplayMode_gurax, "SDL_GetCurrentDisplayMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("displayIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_SDL_DisplayMode, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetCurrentDisplayMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int displayIndex = args_gurax.PickNumber<int>();
	RefPtr<Referencer> mode(args_gurax.PickReferencer().Reference());
	// Function body
	SDL_DisplayMode mode_ = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
	int rtn = SDL_GetCurrentDisplayMode(displayIndex, &mode_);
	mode->SetValue(new Value_SDL_DisplayMode(mode_));
	return new Value_Number(rtn);
}

// sdl.SDL_GetWindowDisplayIndex(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowDisplayIndex_gurax, "SDL_GetWindowDisplayIndex")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetWindowDisplayIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	int rtn = SDL_GetWindowDisplayIndex(window);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetWindowDisplayMode(window as SDL_Window, mode as SDL_DisplayMode)
Gurax_DeclareFunctionAlias(SDL_SetWindowDisplayMode_gurax, "SDL_SetWindowDisplayMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_SDL_DisplayMode, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetWindowDisplayMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	auto& value_mode = args_gurax.Pick<Value_SDL_DisplayMode>();
	const SDL_DisplayMode* mode = value_mode.GetEntityPtr();
	// Function body
	int rtn = SDL_SetWindowDisplayMode(window, mode);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetWindowDisplayMode(window as SDL_Window, mode as SDL_DisplayMode)
Gurax_DeclareFunctionAlias(SDL_GetWindowDisplayMode_gurax, "SDL_GetWindowDisplayMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_SDL_DisplayMode, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetWindowDisplayMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	auto& value_mode = args_gurax.Pick<Value_SDL_DisplayMode>();
	SDL_DisplayMode* mode = value_mode.GetEntityPtr();
	// Function body
	int rtn = SDL_GetWindowDisplayMode(window, mode);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetWindowPixelFormat(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowPixelFormat_gurax, "SDL_GetWindowPixelFormat")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetWindowPixelFormat_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	Uint32 rtn = SDL_GetWindowPixelFormat(window);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_CreateWindow(title as String, x as Number, y as Number, w as Number, h as Number, flags as Number)
Gurax_DeclareFunctionAlias(SDL_CreateWindow_gurax, "SDL_CreateWindow")
{
	Declare(VTYPE_SDL_Window, Flag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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
	if (!rtn) return Value::nil();
	return new Value_SDL_Window(rtn);
}

// sdl.SDL_GetWindowID(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowID_gurax, "SDL_GetWindowID")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetWindowID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	Uint32 rtn = SDL_GetWindowID(window);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetWindowFromID(id as Number)
Gurax_DeclareFunctionAlias(SDL_GetWindowFromID_gurax, "SDL_GetWindowFromID")
{
	Declare(VTYPE_SDL_Window, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetWindowFromID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 id = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_Window* rtn = SDL_GetWindowFromID(id);
	if (!rtn) return Value::nil();
	return new Value_SDL_Window(rtn);
}

// sdl.SDL_GetWindowFlags(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowFlags_gurax, "SDL_GetWindowFlags")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetWindowFlags_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	Uint32 rtn = SDL_GetWindowFlags(window);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetWindowTitle(window as SDL_Window, title as String)
Gurax_DeclareFunctionAlias(SDL_SetWindowTitle_gurax, "SDL_SetWindowTitle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetWindowTitle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	const char* title = args_gurax.PickString();
	// Function body
	SDL_SetWindowTitle(window, title);
	return Gurax::Value::nil();
}

// sdl.SDL_GetWindowTitle(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowTitle_gurax, "SDL_GetWindowTitle")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetWindowTitle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	const char* rtn = SDL_GetWindowTitle(window);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_SetWindowIcon(window as SDL_Window, icon as SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_SetWindowIcon_gurax, "SDL_SetWindowIcon")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("icon", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetWindowIcon_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	auto& value_icon = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* icon = value_icon.GetEntityPtr();
	// Function body
	SDL_SetWindowIcon(window, icon);
	return Gurax::Value::nil();
}

// sdl.SDL_SetWindowPosition(window as SDL_Window, x as Number, y as Number)
Gurax_DeclareFunctionAlias(SDL_SetWindowPosition_gurax, "SDL_SetWindowPosition")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetWindowPosition_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	// Function body
	SDL_SetWindowPosition(window, x, y);
	return Gurax::Value::nil();
}

// sdl.SDL_GetWindowPosition(window as SDL_Window, &x:nilRef as Number, &y:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GetWindowPosition_gurax, "SDL_GetWindowPosition")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetWindowPosition_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	RefPtr<Referencer> x(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> y(args_gurax.PickReferencer().Reference());
	// Function body
	int x_, y_;
	SDL_GetWindowPosition(window, &x_, &y_);
	x->SetValue(new Value_Number(x_));
	y->SetValue(new Value_Number(y_));
	return Value::nil();
}

// sdl.SDL_SetWindowSize(window as SDL_Window, w as Number, h as Number)
Gurax_DeclareFunctionAlias(SDL_SetWindowSize_gurax, "SDL_SetWindowSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetWindowSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	int w = args_gurax.PickNumber<int>();
	int h = args_gurax.PickNumber<int>();
	// Function body
	SDL_SetWindowSize(window, w, h);
	return Gurax::Value::nil();
}

// sdl.SDL_GetWindowSize(window as SDL_Window, &w:nilRef as Number, &h:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GetWindowSize_gurax, "SDL_GetWindowSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetWindowSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	RefPtr<Referencer> w(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> h(args_gurax.PickReferencer().Reference());
	// Function body
	int w_, h_;
	SDL_GetWindowSize(window, &w_, &h_);
	w->SetValue(new Value_Number(w_));
	h->SetValue(new Value_Number(h_));
	return Value::nil();
}

// sdl.SDL_GetWindowBordersSize(window as SDL_Window, &top:nilRef as Number, &left:nilRef as Number, &bottom:nilRef as Number, &right:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GetWindowBordersSize_gurax, "SDL_GetWindowBordersSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("top", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("left", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("bottom", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("right", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetWindowBordersSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	RefPtr<Referencer> top(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> left(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> bottom(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> right(args_gurax.PickReferencer().Reference());
	// Function body
	int top_, left_, bottom_, right_;
	int rtn = SDL_GetWindowBordersSize(window, &top_, &left_, &bottom_, &right_);
	top->SetValue(new Value_Number(top_));
	left->SetValue(new Value_Number(left_));
	bottom->SetValue(new Value_Number(bottom_));
	right->SetValue(new Value_Number(right_));
	return new Value_Number(rtn);
}

// sdl.SDL_SetWindowMinimumSize(window as SDL_Window, min_w as Number, min_h as Number)
Gurax_DeclareFunctionAlias(SDL_SetWindowMinimumSize_gurax, "SDL_SetWindowMinimumSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("min_w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("min_h", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetWindowMinimumSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	int min_w = args_gurax.PickNumber<int>();
	int min_h = args_gurax.PickNumber<int>();
	// Function body
	SDL_SetWindowMinimumSize(window, min_w, min_h);
	return Gurax::Value::nil();
}

// sdl.SDL_GetWindowMinimumSize(window as SDL_Window, &w:nilRef as Number, &h:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GetWindowMinimumSize_gurax, "SDL_GetWindowMinimumSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetWindowMinimumSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	RefPtr<Referencer> w(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> h(args_gurax.PickReferencer().Reference());
	// Function body
	int w_, h_;
	SDL_GetWindowMinimumSize(window, &w_, &h_);
	w->SetValue(new Value_Number(w_));
	h->SetValue(new Value_Number(h_));
	return Value::nil();
}

// sdl.SDL_SetWindowMaximumSize(window as SDL_Window, max_w as Number, max_h as Number)
Gurax_DeclareFunctionAlias(SDL_SetWindowMaximumSize_gurax, "SDL_SetWindowMaximumSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("max_w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("max_h", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetWindowMaximumSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	int max_w = args_gurax.PickNumber<int>();
	int max_h = args_gurax.PickNumber<int>();
	// Function body
	SDL_SetWindowMaximumSize(window, max_w, max_h);
	return Gurax::Value::nil();
}

// sdl.SDL_GetWindowMaximumSize(window as SDL_Window, &w:nilRef as Number, &h:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GetWindowMaximumSize_gurax, "SDL_GetWindowMaximumSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetWindowMaximumSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	RefPtr<Referencer> w(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> h(args_gurax.PickReferencer().Reference());
	// Function body
	int w_, h_;
	SDL_GetWindowMaximumSize(window, &w_, &h_);
	w->SetValue(new Value_Number(w_));
	h->SetValue(new Value_Number(h_));
	return Value::nil();
}

// sdl.SDL_SetWindowBordered(window as SDL_Window, bordered as Bool)
Gurax_DeclareFunctionAlias(SDL_SetWindowBordered_gurax, "SDL_SetWindowBordered")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bordered", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetWindowBordered_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	SDL_bool bordered = static_cast<SDL_bool>(args_gurax.PickBool());
	// Function body
	SDL_SetWindowBordered(window, bordered);
	return Gurax::Value::nil();
}

// sdl.SDL_SetWindowResizable(window as SDL_Window, resizable as Bool)
Gurax_DeclareFunctionAlias(SDL_SetWindowResizable_gurax, "SDL_SetWindowResizable")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("resizable", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetWindowResizable_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	SDL_bool resizable = static_cast<SDL_bool>(args_gurax.PickBool());
	// Function body
	SDL_SetWindowResizable(window, resizable);
	return Gurax::Value::nil();
}

// sdl.SDL_ShowWindow(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_ShowWindow_gurax, "SDL_ShowWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_ShowWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	SDL_ShowWindow(window);
	return Gurax::Value::nil();
}

// sdl.SDL_HideWindow(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_HideWindow_gurax, "SDL_HideWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HideWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	SDL_HideWindow(window);
	return Gurax::Value::nil();
}

// sdl.SDL_RaiseWindow(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_RaiseWindow_gurax, "SDL_RaiseWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RaiseWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	SDL_RaiseWindow(window);
	return Gurax::Value::nil();
}

// sdl.SDL_MaximizeWindow(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_MaximizeWindow_gurax, "SDL_MaximizeWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_MaximizeWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	SDL_MaximizeWindow(window);
	return Gurax::Value::nil();
}

// sdl.SDL_MinimizeWindow(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_MinimizeWindow_gurax, "SDL_MinimizeWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_MinimizeWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	SDL_MinimizeWindow(window);
	return Gurax::Value::nil();
}

// sdl.SDL_RestoreWindow(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_RestoreWindow_gurax, "SDL_RestoreWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RestoreWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	SDL_RestoreWindow(window);
	return Gurax::Value::nil();
}

// sdl.SDL_SetWindowFullscreen(window as SDL_Window, flags as Number)
Gurax_DeclareFunctionAlias(SDL_SetWindowFullscreen_gurax, "SDL_SetWindowFullscreen")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetWindowFullscreen_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	Uint32 flags = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_SetWindowFullscreen(window, flags);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetWindowSurface(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowSurface_gurax, "SDL_GetWindowSurface")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetWindowSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	SDL_Surface* rtn = SDL_GetWindowSurface(window);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.SDL_UpdateWindowSurface(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_UpdateWindowSurface_gurax, "SDL_UpdateWindowSurface")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_UpdateWindowSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	int rtn = SDL_UpdateWindowSurface(window);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_UpdateWindowSurfaceRects(window as SDL_Window, rects[] as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_UpdateWindowSurfaceRects_gurax, "SDL_UpdateWindowSurfaceRects")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rects", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementFunctionEx(SDL_UpdateWindowSurfaceRects_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	auto rects = args_gurax.PickListT<SDL_Rect>(Value_SDL_Rect::ValueForVector);
	// Function body
	int numrects = rects.sizeT<int>();
	int rtn = SDL_UpdateWindowSurfaceRects(window, rects, numrects);
	return new Value_Number(rtn);
}

// sdl.SDL_SetWindowGrab(window as SDL_Window, grabbed as Bool)
Gurax_DeclareFunctionAlias(SDL_SetWindowGrab_gurax, "SDL_SetWindowGrab")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("grabbed", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetWindowGrab_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	SDL_bool grabbed = static_cast<SDL_bool>(args_gurax.PickBool());
	// Function body
	SDL_SetWindowGrab(window, grabbed);
	return Gurax::Value::nil();
}

// sdl.SDL_GetWindowGrab(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowGrab_gurax, "SDL_GetWindowGrab")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetWindowGrab_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_GetWindowGrab(window);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_GetGrabbedWindow()
Gurax_DeclareFunctionAlias(SDL_GetGrabbedWindow_gurax, "SDL_GetGrabbedWindow")
{
	Declare(VTYPE_SDL_Window, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetGrabbedWindow_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Window* rtn = SDL_GetGrabbedWindow();
	if (!rtn) return Value::nil();
	return new Value_SDL_Window(rtn);
}

// sdl.SDL_SetWindowBrightness(window as SDL_Window, brightness as Number)
Gurax_DeclareFunctionAlias(SDL_SetWindowBrightness_gurax, "SDL_SetWindowBrightness")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("brightness", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetWindowBrightness_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	float brightness = args_gurax.PickNumber<float>();
	// Function body
	int rtn = SDL_SetWindowBrightness(window, brightness);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetWindowBrightness(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowBrightness_gurax, "SDL_GetWindowBrightness")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetWindowBrightness_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	float rtn = SDL_GetWindowBrightness(window);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetWindowOpacity(window as SDL_Window, opacity as Number)
Gurax_DeclareFunctionAlias(SDL_SetWindowOpacity_gurax, "SDL_SetWindowOpacity")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("opacity", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetWindowOpacity_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	float opacity = args_gurax.PickNumber<float>();
	// Function body
	int rtn = SDL_SetWindowOpacity(window, opacity);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetWindowOpacity(window as SDL_Window, &out_opacity:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GetWindowOpacity_gurax, "SDL_GetWindowOpacity")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("out_opacity", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetWindowOpacity_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	RefPtr<Referencer> out_opacity(args_gurax.PickReferencer().Reference());
	// Function body
	float out_opacity_;
	int rtn = SDL_GetWindowOpacity(window, &out_opacity_);
	out_opacity->SetValue(new Value_Number(out_opacity_));
	return new Value_Number(rtn);
}

// sdl.SDL_SetWindowModalFor(modal_window as SDL_Window, parent_window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_SetWindowModalFor_gurax, "SDL_SetWindowModalFor")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("modal_window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("parent_window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetWindowModalFor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_modal_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* modal_window = value_modal_window.GetEntityPtr();
	auto& value_parent_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* parent_window = value_parent_window.GetEntityPtr();
	// Function body
	int rtn = SDL_SetWindowModalFor(modal_window, parent_window);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetWindowInputFocus(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_SetWindowInputFocus_gurax, "SDL_SetWindowInputFocus")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetWindowInputFocus_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	int rtn = SDL_SetWindowInputFocus(window);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_DestroyWindow(window:nil as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_DestroyWindow_gurax, "SDL_DestroyWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_DestroyWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Window* window = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Window>().GetEntityPtr() : nullptr;
	// Function body
	SDL_DestroyWindow(window);
	return Gurax::Value::nil();
}

// sdl.SDL_IsScreenSaverEnabled()
Gurax_DeclareFunctionAlias(SDL_IsScreenSaverEnabled_gurax, "SDL_IsScreenSaverEnabled")
{
	Declare(VTYPE_Bool, Flag::None);
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
}

Gurax_ImplementFunctionEx(SDL_DisableScreenSaver_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_DisableScreenSaver();
	return Gurax::Value::nil();
}

// sdl.SDL_GL_LoadLibrary(path as String)
Gurax_DeclareFunctionAlias(SDL_GL_LoadLibrary_gurax, "SDL_GL_LoadLibrary")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("path", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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
}

Gurax_ImplementFunctionEx(SDL_GL_UnloadLibrary_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_GL_UnloadLibrary();
	return Gurax::Value::nil();
}

// sdl.SDL_GL_ExtensionSupported(extension as String)
Gurax_DeclareFunctionAlias(SDL_GL_ExtensionSupported_gurax, "SDL_GL_ExtensionSupported")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("extension", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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
}

Gurax_ImplementFunctionEx(SDL_GL_ResetAttributes_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_GL_ResetAttributes();
	return Gurax::Value::nil();
}

// sdl.SDL_GL_SetAttribute(attr as Number, value as Number)
Gurax_DeclareFunctionAlias(SDL_GL_SetAttribute_gurax, "SDL_GL_SetAttribute")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("attr", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GL_GetAttribute(attr as Number, &value:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GL_GetAttribute_gurax, "SDL_GL_GetAttribute")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("attr", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GL_GetAttribute_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_GLattr attr = args_gurax.PickNumber<SDL_GLattr>();
	RefPtr<Referencer> value(args_gurax.PickReferencer().Reference());
	// Function body
	int value_;
	int rtn = SDL_GL_GetAttribute(attr, &value_);
	value->SetValue(new Value_Number(value_));
	return new Value_Number(rtn);
}

// sdl.SDL_GL_CreateContext(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GL_CreateContext_gurax, "SDL_GL_CreateContext")
{
	Declare(VTYPE_SDL_GLContext, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GL_CreateContext_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	SDL_GLContext rtn = SDL_GL_CreateContext(window);
	if (!rtn) return Value::nil();
	return new Value_SDL_GLContext(rtn);
}

// sdl.SDL_GL_MakeCurrent(window as SDL_Window, context as SDL_GLContext)
Gurax_DeclareFunctionAlias(SDL_GL_MakeCurrent_gurax, "SDL_GL_MakeCurrent")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("context", VTYPE_SDL_GLContext, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GL_MakeCurrent_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	auto& value_context = args_gurax.Pick<Value_SDL_GLContext>();
	SDL_GLContext context = value_context.GetEntityPtr();
	// Function body
	int rtn = SDL_GL_MakeCurrent(window, context);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GL_GetCurrentWindow()
Gurax_DeclareFunctionAlias(SDL_GL_GetCurrentWindow_gurax, "SDL_GL_GetCurrentWindow")
{
	Declare(VTYPE_SDL_Window, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GL_GetCurrentWindow_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Window* rtn = SDL_GL_GetCurrentWindow();
	if (!rtn) return Value::nil();
	return new Value_SDL_Window(rtn);
}

// sdl.SDL_GL_GetCurrentContext()
Gurax_DeclareFunctionAlias(SDL_GL_GetCurrentContext_gurax, "SDL_GL_GetCurrentContext")
{
	Declare(VTYPE_SDL_GLContext, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GL_GetCurrentContext_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_GLContext rtn = SDL_GL_GetCurrentContext();
	if (!rtn) return Value::nil();
	return new Value_SDL_GLContext(rtn);
}

// sdl.SDL_GL_GetDrawableSize(window as SDL_Window, &w:nilRef as Number, &h:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GL_GetDrawableSize_gurax, "SDL_GL_GetDrawableSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GL_GetDrawableSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	RefPtr<Referencer> w(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> h(args_gurax.PickReferencer().Reference());
	// Function body
	int w_, h_;
	SDL_GL_GetDrawableSize(window, &w_, &h_);
	w->SetValue(new Value_Number(w_));
	h->SetValue(new Value_Number(h_));
	return Value::nil();
}

// sdl.SDL_GL_SetSwapInterval(interval as Number)
Gurax_DeclareFunctionAlias(SDL_GL_SetSwapInterval_gurax, "SDL_GL_SetSwapInterval")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("interval", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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
}

Gurax_ImplementFunctionEx(SDL_GL_GetSwapInterval_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_GL_GetSwapInterval();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GL_SwapWindow(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GL_SwapWindow_gurax, "SDL_GL_SwapWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GL_SwapWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	SDL_GL_SwapWindow(window);
	return Gurax::Value::nil();
}

// sdl.SDL_GL_DeleteContext(context as SDL_GLContext)
Gurax_DeclareFunctionAlias(SDL_GL_DeleteContext_gurax, "SDL_GL_DeleteContext")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("context", VTYPE_SDL_GLContext, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GL_DeleteContext_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_context = args_gurax.Pick<Value_SDL_GLContext>();
	SDL_GLContext context = value_context.GetEntityPtr();
	// Function body
	SDL_GL_DeleteContext(context);
	return Gurax::Value::nil();
}

// sdl.SDL_GetNumRenderDrivers()
Gurax_DeclareFunctionAlias(SDL_GetNumRenderDrivers_gurax, "SDL_GetNumRenderDrivers")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetNumRenderDrivers_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_GetNumRenderDrivers();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetRenderDriverInfo(index as Number, &info:nilRef as SDL_RendererInfo)
Gurax_DeclareFunctionAlias(SDL_GetRenderDriverInfo_gurax, "SDL_GetRenderDriverInfo")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("info", VTYPE_SDL_RendererInfo, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetRenderDriverInfo_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	RefPtr<Referencer> info(args_gurax.PickReferencer().Reference());
	// Function body
	SDL_RendererInfo info_;
	int rtn = SDL_GetRenderDriverInfo(index, &info_);
	info->SetValue(new Value_SDL_RendererInfo(info_));
	return new Value_Number(rtn);
}

// sdl.SDL_CreateWindowAndRenderer(width as Number, height as Number, window_flags as Number, &window:nilRef as SDL_Window, &renderer:nilRef as SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_CreateWindowAndRenderer_gurax, "SDL_CreateWindowAndRenderer")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("window_flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_CreateWindowAndRenderer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	Uint32 window_flags = args_gurax.PickNumber<Uint32>();
	RefPtr<Referencer> window(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> renderer(args_gurax.PickReferencer().Reference());
	// Function body
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	int rtn = SDL_CreateWindowAndRenderer(width, height, window_flags, &window_, &renderer_);
	window->SetValue(new Value_SDL_Window(window_));
	renderer->SetValue(new Value_SDL_Renderer(renderer_));
	return new Value_Number(rtn);
}

// sdl.SDL_CreateRenderer(window as SDL_Window, index as Number, flags as Number)
Gurax_DeclareFunctionAlias(SDL_CreateRenderer_gurax, "SDL_CreateRenderer")
{
	Declare(VTYPE_SDL_Renderer, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_CreateRenderer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	int index = args_gurax.PickNumber<int>();
	Uint32 flags = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_Renderer* rtn = SDL_CreateRenderer(window, index, flags);
	if (!rtn) return Value::nil();
	return new Value_SDL_Renderer(rtn);
}

// sdl.SDL_CreateSoftwareRenderer(surface as SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_CreateSoftwareRenderer_gurax, "SDL_CreateSoftwareRenderer")
{
	Declare(VTYPE_SDL_Renderer, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_CreateSoftwareRenderer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	// Function body
	SDL_Renderer* rtn = SDL_CreateSoftwareRenderer(surface);
	if (!rtn) return Value::nil();
	return new Value_SDL_Renderer(rtn);
}

// sdl.SDL_GetRenderer(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetRenderer_gurax, "SDL_GetRenderer")
{
	Declare(VTYPE_SDL_Renderer, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetRenderer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	SDL_Renderer* rtn = SDL_GetRenderer(window);
	if (!rtn) return Value::nil();
	return new Value_SDL_Renderer(rtn);
}

// sdl.SDL_GetRendererInfo(renderer as SDL_Renderer, &info:nilRef as SDL_RendererInfo)
Gurax_DeclareFunctionAlias(SDL_GetRendererInfo_gurax, "SDL_GetRendererInfo")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("info", VTYPE_SDL_RendererInfo, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetRendererInfo_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	RefPtr<Referencer> info(args_gurax.PickReferencer().Reference());
	// Function body
	SDL_RendererInfo info_;
	int rtn = SDL_GetRendererInfo(renderer, &info_);
	info->SetValue(new Value_SDL_RendererInfo(info_));
	return new Value_Number(rtn);
}

// sdl.SDL_GetRendererOutputSize(renderer as SDL_Renderer, &w:nilRef as Number, &h:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GetRendererOutputSize_gurax, "SDL_GetRendererOutputSize")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetRendererOutputSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	RefPtr<Referencer> w(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> h(args_gurax.PickReferencer().Reference());
	// Function body
	int w_, h_;
	int rtn = SDL_GetRendererOutputSize(renderer, &w_, &h_);
	w->SetValue(new Value_Number(w_));
	h->SetValue(new Value_Number(h_));
	return new Value_Number(rtn);
}

// sdl.SDL_CreateTexture(renderer as SDL_Renderer, format as Number, access as Number, w as Number, h as Number)
Gurax_DeclareFunctionAlias(SDL_CreateTexture_gurax, "SDL_CreateTexture")
{
	Declare(VTYPE_SDL_Texture, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("access", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_CreateTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	Uint32 format = args_gurax.PickNumber<Uint32>();
	int access = args_gurax.PickNumber<int>();
	int w = args_gurax.PickNumber<int>();
	int h = args_gurax.PickNumber<int>();
	// Function body
	SDL_Texture* rtn = SDL_CreateTexture(renderer, format, access, w, h);
	if (!rtn) return Value::nil();
	return new Value_SDL_Texture(rtn);
}

// sdl.SDL_CreateTextureFromSurface(renderer as SDL_Renderer, surface as SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_CreateTextureFromSurface_gurax, "SDL_CreateTextureFromSurface")
{
	Declare(VTYPE_SDL_Texture, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_CreateTextureFromSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	// Function body
	SDL_Texture* rtn = SDL_CreateTextureFromSurface(renderer, surface);
	if (!rtn) return Value::nil();
	return new Value_SDL_Texture(rtn);
}

// sdl.SDL_QueryTexture(texture as SDL_Texture, &format:nilRef as Number, &access:nilRef as Number, &w:nilRef as Number, &h:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_QueryTexture_gurax, "SDL_QueryTexture")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("access", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_QueryTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	RefPtr<Referencer> format(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> access(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> w(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> h(args_gurax.PickReferencer().Reference());
	// Function body
	Uint32 format_;
	int access_, w_, h_;
	int rtn = SDL_QueryTexture(texture, &format_, &access_, &w_, &h_);
	format->SetValue(new Value_Number(format_));
	access->SetValue(new Value_Number(access_));
	w->SetValue(new Value_Number(w_));
	h->SetValue(new Value_Number(h_));
	return new Value_Number(rtn);
}

// sdl.SDL_SetTextureColorMod(texture as SDL_Texture, r as Number, g as Number, b as Number)
Gurax_DeclareFunctionAlias(SDL_SetTextureColorMod_gurax, "SDL_SetTextureColorMod")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetTextureColorMod_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	Uint8 r = args_gurax.PickNumber<Uint8>();
	Uint8 g = args_gurax.PickNumber<Uint8>();
	Uint8 b = args_gurax.PickNumber<Uint8>();
	// Function body
	int rtn = SDL_SetTextureColorMod(texture, r, g, b);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetTextureColorMod(texture as SDL_Texture, &r:nilRef as Number, &g:nilRef as Number, &b:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GetTextureColorMod_gurax, "SDL_GetTextureColorMod")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetTextureColorMod_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	RefPtr<Referencer> r(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> g(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> b(args_gurax.PickReferencer().Reference());
	// Function body
	Uint8 r_, g_, b_;
	int rtn = SDL_GetTextureColorMod(texture, &r_, &g_, &b_);
	r->SetValue(new Value_Number(r_));
	g->SetValue(new Value_Number(g_));
	b->SetValue(new Value_Number(b_));
	return new Value_Number(rtn);
}

// sdl.SDL_SetTextureAlphaMod(texture as SDL_Texture, alpha as Number)
Gurax_DeclareFunctionAlias(SDL_SetTextureAlphaMod_gurax, "SDL_SetTextureAlphaMod")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetTextureAlphaMod_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	Uint8 alpha = args_gurax.PickNumber<Uint8>();
	// Function body
	int rtn = SDL_SetTextureAlphaMod(texture, alpha);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetTextureAlphaMod(texture as SDL_Texture, &alpha:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GetTextureAlphaMod_gurax, "SDL_GetTextureAlphaMod")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetTextureAlphaMod_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	RefPtr<Referencer> alpha(args_gurax.PickReferencer().Reference());
	// Function body
	Uint8 alpha_;
	int rtn = SDL_GetTextureAlphaMod(texture, &alpha_);
	alpha->SetValue(new Value_Number(alpha_));
	return new Value_Number(rtn);
}

// sdl.SDL_SetTextureBlendMode(texture as SDL_Texture, blendMode as Number)
Gurax_DeclareFunctionAlias(SDL_SetTextureBlendMode_gurax, "SDL_SetTextureBlendMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blendMode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetTextureBlendMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	SDL_BlendMode blendMode = args_gurax.PickNumber<SDL_BlendMode>();
	// Function body
	int rtn = SDL_SetTextureBlendMode(texture, blendMode);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetTextureBlendMode(texture as SDL_Texture, &blendMode:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GetTextureBlendMode_gurax, "SDL_GetTextureBlendMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blendMode", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetTextureBlendMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	RefPtr<Referencer> blendMode(args_gurax.PickReferencer().Reference());
	// Function body
	SDL_BlendMode blendMode_;
	int rtn = SDL_GetTextureBlendMode(texture, &blendMode_);
	blendMode->SetValue(new Value_Number(blendMode_));
	return new Value_Number(rtn);
}

// sdl.SDL_SetTextureScaleMode(texture as SDL_Texture, scaleMode as Number)
Gurax_DeclareFunctionAlias(SDL_SetTextureScaleMode_gurax, "SDL_SetTextureScaleMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("scaleMode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetTextureScaleMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	SDL_ScaleMode scaleMode = args_gurax.PickNumber<SDL_ScaleMode>();
	// Function body
	int rtn = SDL_SetTextureScaleMode(texture, scaleMode);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetTextureScaleMode(texture as SDL_Texture, &scaleMode:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GetTextureScaleMode_gurax, "SDL_GetTextureScaleMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("scaleMode", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetTextureScaleMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	RefPtr<Referencer> scaleMode(args_gurax.PickReferencer().Reference());
	// Function body
	SDL_ScaleMode scaleMode_;
	int rtn = SDL_GetTextureScaleMode(texture, &scaleMode_);
	scaleMode->SetValue(new Value_Number(scaleMode_));
	return new Value_Number(rtn);
}

// sdl.SDL_UpdateTexture(texture as SDL_Texture, rect:nil as SDL_Rect, pixels as Pointer, pitch as Number)
Gurax_DeclareFunctionAlias(SDL_UpdateTexture_gurax, "SDL_UpdateTexture")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pitch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_UpdateTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	const SDL_Rect* rect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	const void* pixels = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<void>();
	int pitch = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_UpdateTexture(texture, rect, pixels, pitch);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_UpdateYUVTexture(texture as SDL_Texture, rect:nil as SDL_Rect, Yplane as Pointer, Ypitch as Number, Uplane as Pointer, Upitch as Number, Vplane as Pointer, Vpitch as Number)
Gurax_DeclareFunctionAlias(SDL_UpdateYUVTexture_gurax, "SDL_UpdateYUVTexture")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("Yplane", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Ypitch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Uplane", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Upitch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Vplane", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Vpitch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_UpdateYUVTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	const SDL_Rect* rect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	const Uint8* Yplane = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<Uint8>();
	int Ypitch = args_gurax.PickNumber<int>();
	const Uint8* Uplane = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<Uint8>();
	int Upitch = args_gurax.PickNumber<int>();
	const Uint8* Vplane = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<Uint8>();
	int Vpitch = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_UpdateYUVTexture(texture, rect, Yplane, Ypitch, Uplane, Upitch, Vplane, Vpitch);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_LockTexture(texture as SDL_Texture, rect:nil as SDL_Rect, &pixels:nilRef as Pointer, &pitch:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_LockTexture_gurax, "SDL_LockTexture")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("pitch", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_LockTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	const SDL_Rect* rect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	RefPtr<Referencer> pixels(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> pitch(args_gurax.PickReferencer().Reference());
	// Function body
	void* pixels_;
	int pitch_;
	int rtn = SDL_LockTexture(texture, rect, &pixels_, &pitch_);
	size_t bytes;
	if (rect) {
		bytes = pitch_ * rect->h;
	} else {
		int w, h;
		if (SDL_QueryTexture(texture, nullptr, nullptr, &w, &h) != 0) return Value::nil();
		bytes = pitch_ * h;
	}
	RefPtr<Pointer> pPointer(new Pointer_Memory(new MemorySloth(bytes, pixels_)));
	pixels->SetValue(new Value_Pointer(pPointer.release()));
	pitch->SetValue(new Value_Number(pitch_));
	return new Value_Number(rtn);
}

// sdl.SDL_LockTextureToSurface(texture as SDL_Texture, rect:nil as SDL_Rect, &surface:nilRef as SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_LockTextureToSurface_gurax, "SDL_LockTextureToSurface")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_LockTextureToSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	const SDL_Rect* rect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	RefPtr<Referencer> surface(args_gurax.PickReferencer().Reference());
	// Function body
	SDL_Surface* surface_;
	int rtn = SDL_LockTextureToSurface(texture, rect, &surface_);
	surface->SetValue(new Value_SDL_Surface(surface_));
	return new Value_Number(rtn);
}

// sdl.SDL_UnlockTexture(texture as SDL_Texture)
Gurax_DeclareFunctionAlias(SDL_UnlockTexture_gurax, "SDL_UnlockTexture")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_UnlockTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	// Function body
	SDL_UnlockTexture(texture);
	return Gurax::Value::nil();
}

// sdl.SDL_RenderTargetSupported(renderer as SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_RenderTargetSupported_gurax, "SDL_RenderTargetSupported")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderTargetSupported_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_RenderTargetSupported(renderer);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_SetRenderTarget(renderer as SDL_Renderer, texture as SDL_Texture)
Gurax_DeclareFunctionAlias(SDL_SetRenderTarget_gurax, "SDL_SetRenderTarget")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetRenderTarget_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	// Function body
	int rtn = SDL_SetRenderTarget(renderer, texture);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetRenderTarget(renderer as SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_GetRenderTarget_gurax, "SDL_GetRenderTarget")
{
	Declare(VTYPE_SDL_Texture, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetRenderTarget_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	// Function body
	SDL_Texture* rtn = SDL_GetRenderTarget(renderer);
	if (!rtn) return Value::nil();
	return new Value_SDL_Texture(rtn);
}

// sdl.SDL_RenderSetLogicalSize(renderer as SDL_Renderer, w as Number, h as Number)
Gurax_DeclareFunctionAlias(SDL_RenderSetLogicalSize_gurax, "SDL_RenderSetLogicalSize")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderSetLogicalSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	int w = args_gurax.PickNumber<int>();
	int h = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_RenderSetLogicalSize(renderer, w, h);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderGetLogicalSize(renderer as SDL_Renderer, &w:nilRef as Number, &h:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_RenderGetLogicalSize_gurax, "SDL_RenderGetLogicalSize")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_RenderGetLogicalSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	RefPtr<Referencer> w(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> h(args_gurax.PickReferencer().Reference());
	// Function body
	int w_, h_;
	SDL_RenderGetLogicalSize(renderer, &w_, &h_);
	w->SetValue(new Value_Number(w_));
	h->SetValue(new Value_Number(h_));
	return Value::nil();
}

// sdl.SDL_RenderSetIntegerScale(renderer as SDL_Renderer, enable as Bool)
Gurax_DeclareFunctionAlias(SDL_RenderSetIntegerScale_gurax, "SDL_RenderSetIntegerScale")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("enable", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderSetIntegerScale_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	SDL_bool enable = static_cast<SDL_bool>(args_gurax.PickBool());
	// Function body
	int rtn = SDL_RenderSetIntegerScale(renderer, enable);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderGetIntegerScale(renderer as SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_RenderGetIntegerScale_gurax, "SDL_RenderGetIntegerScale")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderGetIntegerScale_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_RenderGetIntegerScale(renderer);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_RenderSetViewport(renderer as SDL_Renderer, rect:nil as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_RenderSetViewport_gurax, "SDL_RenderSetViewport")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_RenderSetViewport_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	const SDL_Rect* rect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	// Function body
	int rtn = SDL_RenderSetViewport(renderer, rect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderGetViewport(renderer as SDL_Renderer, &rect:nilRef as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_RenderGetViewport_gurax, "SDL_RenderGetViewport")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_RenderGetViewport_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	RefPtr<Referencer> rect(args_gurax.PickReferencer().Reference());
	// Function body
	SDL_Rect rect_;
	SDL_RenderGetViewport(renderer, &rect_);
	rect->SetValue(new Value_SDL_Rect(rect_));
	return Value::nil();
}

// sdl.SDL_RenderSetClipRect(renderer as SDL_Renderer, rect:nil as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_RenderSetClipRect_gurax, "SDL_RenderSetClipRect")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_RenderSetClipRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	const SDL_Rect* rect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	// Function body
	int rtn = SDL_RenderSetClipRect(renderer, rect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderGetClipRect(renderer as SDL_Renderer, &rect:nilRef as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_RenderGetClipRect_gurax, "SDL_RenderGetClipRect")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_RenderGetClipRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	RefPtr<Referencer> rect(args_gurax.PickReferencer().Reference());
	// Function body
	SDL_Rect rect_;
	SDL_RenderGetClipRect(renderer, &rect_);
	rect->SetValue(new Value_SDL_Rect(rect_));
	return Value::nil();
}

// sdl.SDL_RenderIsClipEnabled(renderer as SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_RenderIsClipEnabled_gurax, "SDL_RenderIsClipEnabled")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderIsClipEnabled_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_RenderIsClipEnabled(renderer);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_RenderSetScale(renderer as SDL_Renderer, scaleX as Number, scaleY as Number)
Gurax_DeclareFunctionAlias(SDL_RenderSetScale_gurax, "SDL_RenderSetScale")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("scaleX", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("scaleY", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderSetScale_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	float scaleX = args_gurax.PickNumber<float>();
	float scaleY = args_gurax.PickNumber<float>();
	// Function body
	int rtn = SDL_RenderSetScale(renderer, scaleX, scaleY);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderGetScale(renderer as SDL_Renderer, &scaleX:nilRef as Number, &scaleY:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_RenderGetScale_gurax, "SDL_RenderGetScale")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("scaleX", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("scaleY", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_RenderGetScale_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	RefPtr<Referencer> scaleX(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> scaleY(args_gurax.PickReferencer().Reference());
	// Function body
	float scaleX_, scaleY_;
	SDL_RenderGetScale(renderer, &scaleX_, &scaleY_);
	scaleX->SetValue(new Value_Number(scaleX_));
	scaleY->SetValue(new Value_Number(scaleY_));
	return Value::nil();
}

// sdl.SDL_SetRenderDrawColor(renderer as SDL_Renderer, r as Number, g as Number, b as Number, a as Number)
Gurax_DeclareFunctionAlias(SDL_SetRenderDrawColor_gurax, "SDL_SetRenderDrawColor")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("a", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetRenderDrawColor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	Uint8 r = args_gurax.PickNumber<Uint8>();
	Uint8 g = args_gurax.PickNumber<Uint8>();
	Uint8 b = args_gurax.PickNumber<Uint8>();
	Uint8 a = args_gurax.PickNumber<Uint8>();
	// Function body
	int rtn = SDL_SetRenderDrawColor(renderer, r, g, b, a);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetRenderDrawColor(renderer as SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_GetRenderDrawColor_gurax, "SDL_GetRenderDrawColor")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetRenderDrawColor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	// Function body
	Uint8 r, g, b, a;
	if (SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a) != 0) return Value::nil();
	return Value_Tuple::Create(new Value_Number(r), new Value_Number(g), new Value_Number(b), new Value_Number(a));
}

// sdl.SDL_SetRenderDrawBlendMode(renderer as SDL_Renderer, blendMode as Number)
Gurax_DeclareFunctionAlias(SDL_SetRenderDrawBlendMode_gurax, "SDL_SetRenderDrawBlendMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blendMode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetRenderDrawBlendMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	SDL_BlendMode blendMode = args_gurax.PickNumber<SDL_BlendMode>();
	// Function body
	int rtn = SDL_SetRenderDrawBlendMode(renderer, blendMode);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetRenderDrawBlendMode(renderer as SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_GetRenderDrawBlendMode_gurax, "SDL_GetRenderDrawBlendMode")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetRenderDrawBlendMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	// Function body
	SDL_BlendMode blendMode;
	if (SDL_GetRenderDrawBlendMode(renderer, &blendMode) != 0) return Value::nil();
	return new Value_Number(blendMode);
}

// sdl.SDL_RenderClear(renderer as SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_RenderClear_gurax, "SDL_RenderClear")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderClear_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	// Function body
	int rtn = SDL_RenderClear(renderer);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderDrawPoint(renderer as SDL_Renderer, x as Number, y as Number)
Gurax_DeclareFunctionAlias(SDL_RenderDrawPoint_gurax, "SDL_RenderDrawPoint")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderDrawPoint_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_RenderDrawPoint(renderer, x, y);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderDrawPoints(renderer as SDL_Renderer, points[] as SDL_Point)
Gurax_DeclareFunctionAlias(SDL_RenderDrawPoints_gurax, "SDL_RenderDrawPoints")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("points", VTYPE_SDL_Point, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementFunctionEx(SDL_RenderDrawPoints_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	auto points = args_gurax.PickListT<SDL_Point>(Value_SDL_Point::ValueForVector);
	// Function body
	int count = points.sizeT<int>();
	int rtn = SDL_RenderDrawPoints(renderer, points, count);
	return new Value_Number(rtn);
}

// sdl.SDL_RenderDrawLine(renderer as SDL_Renderer, x1 as Number, y1 as Number, x2 as Number, y2 as Number)
Gurax_DeclareFunctionAlias(SDL_RenderDrawLine_gurax, "SDL_RenderDrawLine")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderDrawLine_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	int x1 = args_gurax.PickNumber<int>();
	int y1 = args_gurax.PickNumber<int>();
	int x2 = args_gurax.PickNumber<int>();
	int y2 = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderDrawLines(renderer as SDL_Renderer, points[] as SDL_Point)
Gurax_DeclareFunctionAlias(SDL_RenderDrawLines_gurax, "SDL_RenderDrawLines")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("points", VTYPE_SDL_Point, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementFunctionEx(SDL_RenderDrawLines_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	auto points = args_gurax.PickListT<SDL_Point>(Value_SDL_Point::ValueForVector);
	// Function body
	int count = points.sizeT<int>();
	int rtn = SDL_RenderDrawLines(renderer, points, count);
	return new Value_Number(rtn);
}

// sdl.SDL_RenderDrawRect(renderer as SDL_Renderer, rect:nil as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_RenderDrawRect_gurax, "SDL_RenderDrawRect")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_RenderDrawRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	const SDL_Rect* rect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	// Function body
	int rtn = SDL_RenderDrawRect(renderer, rect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderDrawRects(renderer as SDL_Renderer, rects[] as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_RenderDrawRects_gurax, "SDL_RenderDrawRects")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rects", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementFunctionEx(SDL_RenderDrawRects_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	auto rects = args_gurax.PickListT<SDL_Rect>(Value_SDL_Rect::ValueForVector);
	// Function body
	int count = rects.sizeT<int>();
	int rtn = SDL_RenderDrawRects(renderer, rects, count);
	return new Value_Number(rtn);
}

// sdl.SDL_RenderFillRect(renderer as SDL_Renderer, rect:nil as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_RenderFillRect_gurax, "SDL_RenderFillRect")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_RenderFillRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	const SDL_Rect* rect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	// Function body
	int rtn = SDL_RenderFillRect(renderer, rect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderFillRects(renderer as SDL_Renderer, rects[] as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_RenderFillRects_gurax, "SDL_RenderFillRects")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rects", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementFunctionEx(SDL_RenderFillRects_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	auto rects = args_gurax.PickListT<SDL_Rect>(Value_SDL_Rect::ValueForVector);
	// Function body
	int count = rects.sizeT<int>();
	int rtn = SDL_RenderFillRects(renderer, rects, count);
	return new Value_Number(rtn);
}

// sdl.SDL_RenderCopy(renderer as SDL_Renderer, texture as SDL_Texture, srcrect:nil as SDL_Rect, dstrect:nil as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_RenderCopy_gurax, "SDL_RenderCopy")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("dstrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_RenderCopy_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	const SDL_Rect* srcrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	const SDL_Rect* dstrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	// Function body
	int rtn = SDL_RenderCopy(renderer, texture, srcrect, dstrect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderCopyEx(renderer as SDL_Renderer, texture as SDL_Texture, srcrect:nil as SDL_Rect, dstrect:nil as SDL_Rect, angle as Number, center:nil as SDL_Point, flip as Number)
Gurax_DeclareFunctionAlias(SDL_RenderCopyEx_gurax, "SDL_RenderCopyEx")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("dstrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("angle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("center", VTYPE_SDL_Point, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("flip", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderCopyEx_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	const SDL_Rect* srcrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	const SDL_Rect* dstrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	double angle = args_gurax.PickNumber<double>();
	const SDL_Point* center = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Point>().GetEntityPtr() : nullptr;
	SDL_RendererFlip flip = args_gurax.PickNumber<SDL_RendererFlip>();
	// Function body
	int rtn = SDL_RenderCopyEx(renderer, texture, srcrect, dstrect, angle, center, flip);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderDrawPointF(renderer as SDL_Renderer, x as Number, y as Number)
Gurax_DeclareFunctionAlias(SDL_RenderDrawPointF_gurax, "SDL_RenderDrawPointF")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderDrawPointF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	float x = args_gurax.PickNumber<float>();
	float y = args_gurax.PickNumber<float>();
	// Function body
	int rtn = SDL_RenderDrawPointF(renderer, x, y);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderDrawPointsF(renderer as SDL_Renderer, points as SDL_FPoint, count as Number)
Gurax_DeclareFunctionAlias(SDL_RenderDrawPointsF_gurax, "SDL_RenderDrawPointsF")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("points", VTYPE_SDL_FPoint, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderDrawPointsF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	auto& value_points = args_gurax.Pick<Value_SDL_FPoint>();
	const SDL_FPoint* points = value_points.GetEntityPtr();
	int count = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_RenderDrawPointsF(renderer, points, count);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderDrawLineF(renderer as SDL_Renderer, x1 as Number, y1 as Number, x2 as Number, y2 as Number)
Gurax_DeclareFunctionAlias(SDL_RenderDrawLineF_gurax, "SDL_RenderDrawLineF")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderDrawLineF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	float x1 = args_gurax.PickNumber<float>();
	float y1 = args_gurax.PickNumber<float>();
	float x2 = args_gurax.PickNumber<float>();
	float y2 = args_gurax.PickNumber<float>();
	// Function body
	int rtn = SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderDrawLinesF(renderer as SDL_Renderer, points[] as SDL_FPoint)
Gurax_DeclareFunctionAlias(SDL_RenderDrawLinesF_gurax, "SDL_RenderDrawLinesF")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("points", VTYPE_SDL_FPoint, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementFunctionEx(SDL_RenderDrawLinesF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	auto points = args_gurax.PickListT<SDL_FPoint>(Value_SDL_FPoint::ValueForVector);
	// Function body
	int count = points.sizeT<int>();
	int rtn = SDL_RenderDrawLinesF(renderer, points, count);
	return new Value_Number(rtn);
}

// sdl.SDL_RenderDrawRectF(renderer as SDL_Renderer, rect as SDL_FRect)
Gurax_DeclareFunctionAlias(SDL_RenderDrawRectF_gurax, "SDL_RenderDrawRectF")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_FRect, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderDrawRectF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	auto& value_rect = args_gurax.Pick<Value_SDL_FRect>();
	const SDL_FRect* rect = value_rect.GetEntityPtr();
	// Function body
	int rtn = SDL_RenderDrawRectF(renderer, rect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderDrawRectsF(renderer as SDL_Renderer, rects[] as SDL_FRect)
Gurax_DeclareFunctionAlias(SDL_RenderDrawRectsF_gurax, "SDL_RenderDrawRectsF")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rects", VTYPE_SDL_FRect, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementFunctionEx(SDL_RenderDrawRectsF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	auto rects = args_gurax.PickListT<SDL_FRect>(Value_SDL_FRect::ValueForVector);
	// Function body
	int count = rects.sizeT<int>();
	int rtn = SDL_RenderDrawRectsF(renderer, rects, count);
	return new Value_Number(rtn);
}

// sdl.SDL_RenderFillRectF(renderer as SDL_Renderer, rect as SDL_FRect)
Gurax_DeclareFunctionAlias(SDL_RenderFillRectF_gurax, "SDL_RenderFillRectF")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_FRect, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderFillRectF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	auto& value_rect = args_gurax.Pick<Value_SDL_FRect>();
	const SDL_FRect* rect = value_rect.GetEntityPtr();
	// Function body
	int rtn = SDL_RenderFillRectF(renderer, rect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderFillRectsF(renderer as SDL_Renderer, rects[] as SDL_FRect)
Gurax_DeclareFunctionAlias(SDL_RenderFillRectsF_gurax, "SDL_RenderFillRectsF")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rects", VTYPE_SDL_FRect, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementFunctionEx(SDL_RenderFillRectsF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	auto rects = args_gurax.PickListT<SDL_FRect>(Value_SDL_FRect::ValueForVector);
	// Function body
	int count = rects.sizeT<int>();
	int rtn = SDL_RenderFillRectsF(renderer, rects, count);
	return new Value_Number(rtn);
}

// sdl.SDL_RenderCopyF(renderer as SDL_Renderer, texture as SDL_Texture, srcrect:nil as SDL_Rect, dstrect as SDL_FRect)
Gurax_DeclareFunctionAlias(SDL_RenderCopyF_gurax, "SDL_RenderCopyF")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("dstrect", VTYPE_SDL_FRect, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderCopyF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	const SDL_Rect* srcrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	auto& value_dstrect = args_gurax.Pick<Value_SDL_FRect>();
	const SDL_FRect* dstrect = value_dstrect.GetEntityPtr();
	// Function body
	int rtn = SDL_RenderCopyF(renderer, texture, srcrect, dstrect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderReadPixels(renderer as SDL_Renderer, rect:nil as SDL_Rect, format as Number, pixels as Pointer, pitch as Number)
Gurax_DeclareFunctionAlias(SDL_RenderReadPixels_gurax, "SDL_RenderReadPixels")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pitch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderReadPixels_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	const SDL_Rect* rect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	Uint32 format = args_gurax.PickNumber<Uint32>();
	void* pixels = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!pixels) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	int pitch = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_RenderReadPixels(renderer, rect, format, pixels, pitch);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RenderPresent(renderer as SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_RenderPresent_gurax, "SDL_RenderPresent")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderPresent_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	// Function body
	SDL_RenderPresent(renderer);
	return Gurax::Value::nil();
}

// sdl.SDL_DestroyTexture(texture:nil as SDL_Texture)
Gurax_DeclareFunctionAlias(SDL_DestroyTexture_gurax, "SDL_DestroyTexture")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_DestroyTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Texture* texture = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Texture>().GetEntityPtr() : nullptr;
	// Function body
	SDL_DestroyTexture(texture);
	return Gurax::Value::nil();
}

// sdl.SDL_DestroyRenderer(renderer:nil as SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_DestroyRenderer_gurax, "SDL_DestroyRenderer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_DestroyRenderer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Renderer* renderer = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Renderer>().GetEntityPtr() : nullptr;
	// Function body
	SDL_DestroyRenderer(renderer);
	return Gurax::Value::nil();
}

// sdl.SDL_RenderFlush(renderer as SDL_Renderer)
Gurax_DeclareFunctionAlias(SDL_RenderFlush_gurax, "SDL_RenderFlush")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("renderer", VTYPE_SDL_Renderer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RenderFlush_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_renderer = args_gurax.Pick<Value_SDL_Renderer>();
	SDL_Renderer* renderer = value_renderer.GetEntityPtr();
	// Function body
	int rtn = SDL_RenderFlush(renderer);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GL_UnbindTexture(texture as SDL_Texture)
Gurax_DeclareFunctionAlias(SDL_GL_UnbindTexture_gurax, "SDL_GL_UnbindTexture")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("texture", VTYPE_SDL_Texture, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GL_UnbindTexture_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_texture = args_gurax.Pick<Value_SDL_Texture>();
	SDL_Texture* texture = value_texture.GetEntityPtr();
	// Function body
	int rtn = SDL_GL_UnbindTexture(texture);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetPixelFormatName(format as Number)
Gurax_DeclareFunctionAlias(SDL_GetPixelFormatName_gurax, "SDL_GetPixelFormatName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_MasksToPixelFormatEnum(bpp as Number, Rmask as Number, Gmask as Number, Bmask as Number, Amask as Number)
Gurax_DeclareFunctionAlias(SDL_MasksToPixelFormatEnum_gurax, "SDL_MasksToPixelFormatEnum")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("bpp", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Rmask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Gmask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Bmask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Amask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_AllocFormat(pixel_format as Number)
Gurax_DeclareFunctionAlias(SDL_AllocFormat_gurax, "SDL_AllocFormat")
{
	Declare(VTYPE_SDL_PixelFormat, Flag::None);
	DeclareArg("pixel_format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_AllocFormat_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 pixel_format = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_PixelFormat* rtn = SDL_AllocFormat(pixel_format);
	if (!rtn) return Value::nil();
	return new Value_SDL_PixelFormat(rtn);
}

// sdl.SDL_FreeFormat(format:nil as SDL_PixelFormat)
Gurax_DeclareFunctionAlias(SDL_FreeFormat_gurax, "SDL_FreeFormat")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("format", VTYPE_SDL_PixelFormat, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_FreeFormat_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_PixelFormat* format = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_PixelFormat>().GetEntityPtr() : nullptr;
	// Function body
	SDL_FreeFormat(format);
	return Gurax::Value::nil();
}

// sdl.SDL_AllocPalette(ncolors as Number)
Gurax_DeclareFunctionAlias(SDL_AllocPalette_gurax, "SDL_AllocPalette")
{
	Declare(VTYPE_SDL_Palette, Flag::None);
	DeclareArg("ncolors", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_AllocPalette_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int ncolors = args_gurax.PickNumber<int>();
	// Function body
	SDL_Palette* rtn = SDL_AllocPalette(ncolors);
	if (!rtn) return Value::nil();
	return new Value_SDL_Palette(rtn);
}

// sdl.SDL_SetPixelFormatPalette(format as SDL_PixelFormat, palette as SDL_Palette)
Gurax_DeclareFunctionAlias(SDL_SetPixelFormatPalette_gurax, "SDL_SetPixelFormatPalette")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("format", VTYPE_SDL_PixelFormat, ArgOccur::Once, ArgFlag::None);
	DeclareArg("palette", VTYPE_SDL_Palette, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetPixelFormatPalette_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_format = args_gurax.Pick<Value_SDL_PixelFormat>();
	SDL_PixelFormat* format = value_format.GetEntityPtr();
	auto& value_palette = args_gurax.Pick<Value_SDL_Palette>();
	SDL_Palette* palette = value_palette.GetEntityPtr();
	// Function body
	int rtn = SDL_SetPixelFormatPalette(format, palette);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetPaletteColors(palette as SDL_Palette, colors[] as SDL_Color, firstcolor as Number)
Gurax_DeclareFunctionAlias(SDL_SetPaletteColors_gurax, "SDL_SetPaletteColors")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("palette", VTYPE_SDL_Palette, ArgOccur::Once, ArgFlag::None);
	DeclareArg("colors", VTYPE_SDL_Color, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("firstcolor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetPaletteColors_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_palette = args_gurax.Pick<Value_SDL_Palette>();
	SDL_Palette* palette = value_palette.GetEntityPtr();
	auto colors = args_gurax.PickListT<SDL_Color>(Value_SDL_Color::ValueForVector);
	int firstcolor = args_gurax.PickNumber<int>();
	// Function body
	int ncolors = colors.sizeT<int>();
	int rtn = SDL_SetPaletteColors(palette, colors, firstcolor, ncolors);
	return new Value_Number(rtn);
}

// sdl.SDL_FreePalette(palette:nil as SDL_Palette)
Gurax_DeclareFunctionAlias(SDL_FreePalette_gurax, "SDL_FreePalette")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("palette", VTYPE_SDL_Palette, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_FreePalette_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Palette* palette = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Palette>().GetEntityPtr() : nullptr;
	// Function body
	SDL_FreePalette(palette);
	return Gurax::Value::nil();
}

// sdl.SDL_MapRGB(format as SDL_PixelFormat, r as Number, g as Number, b as Number)
Gurax_DeclareFunctionAlias(SDL_MapRGB_gurax, "SDL_MapRGB")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("format", VTYPE_SDL_PixelFormat, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_MapRGB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_format = args_gurax.Pick<Value_SDL_PixelFormat>();
	const SDL_PixelFormat* format = value_format.GetEntityPtr();
	Uint8 r = args_gurax.PickNumber<Uint8>();
	Uint8 g = args_gurax.PickNumber<Uint8>();
	Uint8 b = args_gurax.PickNumber<Uint8>();
	// Function body
	Uint32 rtn = SDL_MapRGB(format, r, g, b);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_MapRGBA(format as SDL_PixelFormat, r as Number, g as Number, b as Number, a as Number)
Gurax_DeclareFunctionAlias(SDL_MapRGBA_gurax, "SDL_MapRGBA")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("format", VTYPE_SDL_PixelFormat, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("a", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_MapRGBA_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_format = args_gurax.Pick<Value_SDL_PixelFormat>();
	const SDL_PixelFormat* format = value_format.GetEntityPtr();
	Uint8 r = args_gurax.PickNumber<Uint8>();
	Uint8 g = args_gurax.PickNumber<Uint8>();
	Uint8 b = args_gurax.PickNumber<Uint8>();
	Uint8 a = args_gurax.PickNumber<Uint8>();
	// Function body
	Uint32 rtn = SDL_MapRGBA(format, r, g, b, a);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetRGB(pixel as Number, format as SDL_PixelFormat)
Gurax_DeclareFunctionAlias(SDL_GetRGB_gurax, "SDL_GetRGB")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("pixel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_SDL_PixelFormat, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetRGB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 pixel = args_gurax.PickNumber<Uint32>();
	auto& value_format = args_gurax.Pick<Value_SDL_PixelFormat>();
	const SDL_PixelFormat* format = value_format.GetEntityPtr();
	// Function body
	Uint8 r, g, b;
	SDL_GetRGB(pixel, format, &r, &g, &b);
	return Value_Tuple::Create(new Value_Number(r), new Value_Number(g), new Value_Number(b));
}

// sdl.SDL_GetRGBA(pixel as Number, format as SDL_PixelFormat)
Gurax_DeclareFunctionAlias(SDL_GetRGBA_gurax, "SDL_GetRGBA")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("pixel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_SDL_PixelFormat, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetRGBA_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 pixel = args_gurax.PickNumber<Uint32>();
	auto& value_format = args_gurax.Pick<Value_SDL_PixelFormat>();
	const SDL_PixelFormat* format = value_format.GetEntityPtr();
	// Function body
	Uint8 r, g, b, a;
	SDL_GetRGBA(pixel, format, &r, &g, &b, &a);
	return Value_Tuple::Create(new Value_Number(r), new Value_Number(g), new Value_Number(b), new Value_Number(a));
}

// sdl.SDL_HasIntersection(A as SDL_Rect, B as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_HasIntersection_gurax, "SDL_HasIntersection")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("A", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("B", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HasIntersection_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_A = args_gurax.Pick<Value_SDL_Rect>();
	const SDL_Rect* A = value_A.GetEntityPtr();
	auto& value_B = args_gurax.Pick<Value_SDL_Rect>();
	const SDL_Rect* B = value_B.GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_HasIntersection(A, B);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_IntersectRect(A as SDL_Rect, B as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_IntersectRect_gurax, "SDL_IntersectRect")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("A", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("B", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_IntersectRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_A = args_gurax.Pick<Value_SDL_Rect>();
	const SDL_Rect* A = value_A.GetEntityPtr();
	auto& value_B = args_gurax.Pick<Value_SDL_Rect>();
	const SDL_Rect* B = value_B.GetEntityPtr();
	// Function body
	SDL_Rect result;
	if (!SDL_IntersectRect(A, B, &result)) return Value::nil();
	return new Value_SDL_Rect(result);
}

// sdl.SDL_UnionRect(A as SDL_Rect, B as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_UnionRect_gurax, "SDL_UnionRect")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("A", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("B", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_UnionRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_A = args_gurax.Pick<Value_SDL_Rect>();
	const SDL_Rect* A = value_A.GetEntityPtr();
	auto& value_B = args_gurax.Pick<Value_SDL_Rect>();
	const SDL_Rect* B = value_B.GetEntityPtr();
	// Function body
	SDL_Rect result;
	SDL_UnionRect(A, B, &result);
	return new Value_SDL_Rect(result);
}

// sdl.SDL_IntersectRectAndLine(rect as SDL_Rect, X1 as Number, Y1 as Number, X2 as Number, Y2 as Number)
Gurax_DeclareFunctionAlias(SDL_IntersectRectAndLine_gurax, "SDL_IntersectRectAndLine")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("X1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Y1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("X2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Y2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_IntersectRectAndLine_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_rect = args_gurax.Pick<Value_SDL_Rect>();
	const SDL_Rect* rect = value_rect.GetEntityPtr();
	int X1 = args_gurax.PickNumber<int>();
	int Y1 = args_gurax.PickNumber<int>();
	int X2 = args_gurax.PickNumber<int>();
	int Y2 = args_gurax.PickNumber<int>();
	// Function body
	if (!SDL_IntersectRectAndLine(rect, &X1, &Y1, &X2, &Y2)) return Value::nil();
	return Value_Tuple::Create(new Value_Number(X1), new Value_Number(Y1), new Value_Number(X2), new Value_Number(Y2));
}

// sdl.SDL_CreateRGBSurface(flags as Number, width as Number, height as Number, depth as Number, Rmask as Number, Gmask as Number, Bmask as Number, Amask as Number)
Gurax_DeclareFunctionAlias(SDL_CreateRGBSurface_gurax, "SDL_CreateRGBSurface")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Rmask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Gmask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Bmask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Amask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_CreateRGBSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 flags = args_gurax.PickNumber<Uint32>();
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	int depth = args_gurax.PickNumber<int>();
	Uint32 Rmask = args_gurax.PickNumber<Uint32>();
	Uint32 Gmask = args_gurax.PickNumber<Uint32>();
	Uint32 Bmask = args_gurax.PickNumber<Uint32>();
	Uint32 Amask = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_Surface* rtn = SDL_CreateRGBSurface(flags, width, height, depth, Rmask, Gmask, Bmask, Amask);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.SDL_CreateRGBSurfaceWithFormat(flags as Number, width as Number, height as Number, depth as Number, format as Number)
Gurax_DeclareFunctionAlias(SDL_CreateRGBSurfaceWithFormat_gurax, "SDL_CreateRGBSurfaceWithFormat")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_CreateRGBSurfaceWithFormat_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 flags = args_gurax.PickNumber<Uint32>();
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	int depth = args_gurax.PickNumber<int>();
	Uint32 format = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_Surface* rtn = SDL_CreateRGBSurfaceWithFormat(flags, width, height, depth, format);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.SDL_CreateRGBSurfaceFrom(pixels as Pointer, width as Number, height as Number, depth as Number, pitch as Number, Rmask as Number, Gmask as Number, Bmask as Number, Amask as Number)
Gurax_DeclareFunctionAlias(SDL_CreateRGBSurfaceFrom_gurax, "SDL_CreateRGBSurfaceFrom")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pitch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Rmask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Gmask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Bmask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("Amask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_CreateRGBSurfaceFrom_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	void* pixels = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!pixels) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	int depth = args_gurax.PickNumber<int>();
	int pitch = args_gurax.PickNumber<int>();
	Uint32 Rmask = args_gurax.PickNumber<Uint32>();
	Uint32 Gmask = args_gurax.PickNumber<Uint32>();
	Uint32 Bmask = args_gurax.PickNumber<Uint32>();
	Uint32 Amask = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_Surface* rtn = SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, Rmask, Gmask, Bmask, Amask);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.SDL_CreateRGBSurfaceWithFormatFrom(pixels as Pointer, width as Number, height as Number, depth as Number, pitch as Number, format as Number)
Gurax_DeclareFunctionAlias(SDL_CreateRGBSurfaceWithFormatFrom_gurax, "SDL_CreateRGBSurfaceWithFormatFrom")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("pixels", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pitch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_CreateRGBSurfaceWithFormatFrom_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	void* pixels = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!pixels) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	int depth = args_gurax.PickNumber<int>();
	int pitch = args_gurax.PickNumber<int>();
	Uint32 format = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_Surface* rtn = SDL_CreateRGBSurfaceWithFormatFrom(pixels, width, height, depth, pitch, format);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.SDL_CreateRGBSurfaceFromImage(image as Image)
Gurax_DeclareFunctionAlias(SDL_CreateRGBSurfaceFromImage_gurax, "SDL_CreateRGBSurfaceFromImage")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("image", VTYPE_Image, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_CreateRGBSurfaceFromImage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Gurax::Image& image = args_gurax.Pick<Value_Image>().GetImage();
	// Function body
	return Value_SDL_Surface::Create(image.Reference());
}

// sdl.SDL_FreeSurface(surface:nil as SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_FreeSurface_gurax, "SDL_FreeSurface")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_FreeSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Surface* surface = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Surface>().GetEntityPtr() : nullptr;
	// Function body
	SDL_FreeSurface(surface);
	return Gurax::Value::nil();
}

// sdl.SDL_SetSurfacePalette(surface as SDL_Surface, palette as SDL_Palette)
Gurax_DeclareFunctionAlias(SDL_SetSurfacePalette_gurax, "SDL_SetSurfacePalette")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("palette", VTYPE_SDL_Palette, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetSurfacePalette_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	auto& value_palette = args_gurax.Pick<Value_SDL_Palette>();
	SDL_Palette* palette = value_palette.GetEntityPtr();
	// Function body
	int rtn = SDL_SetSurfacePalette(surface, palette);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_LockSurface(surface as SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_LockSurface_gurax, "SDL_LockSurface")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_LockSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	// Function body
	int rtn = SDL_LockSurface(surface);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_UnlockSurface(surface as SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_UnlockSurface_gurax, "SDL_UnlockSurface")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_UnlockSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	// Function body
	SDL_UnlockSurface(surface);
	return Gurax::Value::nil();
}

// sdl.SDL_LoadBMP(file as String)
Gurax_DeclareFunctionAlias(SDL_LoadBMP_gurax, "SDL_LoadBMP")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("file", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_LoadBMP_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* file = args_gurax.PickString();
	// Function body
	SDL_Surface* rtn = SDL_LoadBMP(file);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.SDL_LoadBMP_RW(src as SDL_RWops, freesrc as Number)
Gurax_DeclareFunctionAlias(SDL_LoadBMP_RW_gurax, "SDL_LoadBMP_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("freesrc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_LoadBMP_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	int freesrc = args_gurax.PickNumber<int>();
	// Function body
	SDL_Surface* rtn = SDL_LoadBMP_RW(src, freesrc);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.SDL_SaveBMP(surface as SDL_Surface, file as String)
Gurax_DeclareFunctionAlias(SDL_SaveBMP_gurax, "SDL_SaveBMP")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("file", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SaveBMP_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	const char* file = args_gurax.PickString();
	// Function body
	int rtn = SDL_SaveBMP(surface, file);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SaveBMP_RW(surface as SDL_Surface, dst as SDL_RWops, freedst as Bool)
Gurax_DeclareFunctionAlias(SDL_SaveBMP_RW_gurax, "SDL_SaveBMP_RW")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dst", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("freedst", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SaveBMP_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	auto& value_dst = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* dst = value_dst.GetEntityPtr();
	bool freedst = args_gurax.PickBool();
	// Function body
	int rtn = SDL_SaveBMP_RW(surface, dst, freedst? 1 : 0);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetSurfaceRLE(surface as SDL_Surface, flag as Bool)
Gurax_DeclareFunctionAlias(SDL_SetSurfaceRLE_gurax, "SDL_SetSurfaceRLE")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetSurfaceRLE_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	bool flag = args_gurax.PickBool();
	// Function body
	int rtn = SDL_SetSurfaceRLE(surface, flag);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetColorKey(surface as SDL_Surface, flag as Bool, key as Number)
Gurax_DeclareFunctionAlias(SDL_SetColorKey_gurax, "SDL_SetColorKey")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("key", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetColorKey_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	bool flag = args_gurax.PickBool();
	Uint32 key = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_SetColorKey(surface, flag, key);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HasColorKey(surface as SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_HasColorKey_gurax, "SDL_HasColorKey")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HasColorKey_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_HasColorKey(surface);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_GetColorKey(surface as SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_GetColorKey_gurax, "SDL_GetColorKey")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetColorKey_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	// Function body
	Uint32 key;
	if (SDL_GetColorKey(surface, &key) != 0) return Value::nil();
	return new Value_Number(key);
}

// sdl.SDL_SetSurfaceColorMod(surface as SDL_Surface, r as Number, g as Number, b as Number)
Gurax_DeclareFunctionAlias(SDL_SetSurfaceColorMod_gurax, "SDL_SetSurfaceColorMod")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetSurfaceColorMod_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	Uint8 r = args_gurax.PickNumber<Uint8>();
	Uint8 g = args_gurax.PickNumber<Uint8>();
	Uint8 b = args_gurax.PickNumber<Uint8>();
	// Function body
	int rtn = SDL_SetSurfaceColorMod(surface, r, g, b);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetSurfaceColorMod(surface as SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_GetSurfaceColorMod_gurax, "SDL_GetSurfaceColorMod")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetSurfaceColorMod_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	// Function body
	Uint8 r, g, b;
	if (SDL_GetSurfaceColorMod(surface, &r, &g, &b) != 0) return Value::nil();
	return Value_Tuple::Create(new Value_Number(r), new Value_Number(g), new Value_Number(b));
}

// sdl.SDL_SetSurfaceAlphaMod(surface as SDL_Surface, alpha as Number)
Gurax_DeclareFunctionAlias(SDL_SetSurfaceAlphaMod_gurax, "SDL_SetSurfaceAlphaMod")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetSurfaceAlphaMod_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	Uint8 alpha = args_gurax.PickNumber<Uint8>();
	// Function body
	int rtn = SDL_SetSurfaceAlphaMod(surface, alpha);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetSurfaceAlphaMod(surface as SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_GetSurfaceAlphaMod_gurax, "SDL_GetSurfaceAlphaMod")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetSurfaceAlphaMod_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	// Function body
	Uint8 alpha;
	if (SDL_GetSurfaceAlphaMod(surface, &alpha) != 0) return Value::nil();
	return new Value_Number(alpha);
}

// sdl.SDL_SetSurfaceBlendMode(surface as SDL_Surface, blendMode as Number)
Gurax_DeclareFunctionAlias(SDL_SetSurfaceBlendMode_gurax, "SDL_SetSurfaceBlendMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blendMode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetSurfaceBlendMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	SDL_BlendMode blendMode = args_gurax.PickNumber<SDL_BlendMode>();
	// Function body
	int rtn = SDL_SetSurfaceBlendMode(surface, blendMode);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetSurfaceBlendMode(surface as SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_GetSurfaceBlendMode_gurax, "SDL_GetSurfaceBlendMode")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetSurfaceBlendMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	// Function body
	SDL_BlendMode blendMode;
	if (SDL_GetSurfaceBlendMode(surface, &blendMode) != 0) return Value::nil();
	return new Value_Number(blendMode);
}

// sdl.SDL_SetClipRect(surface as SDL_Surface, rect:nil as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_SetClipRect_gurax, "SDL_SetClipRect")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_SetClipRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	const SDL_Rect* rect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	// Function body
	SDL_bool rtn = SDL_SetClipRect(surface, rect);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_GetClipRect(surface as SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_GetClipRect_gurax, "SDL_GetClipRect")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetClipRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	// Function body
	SDL_Rect rect;
	SDL_GetClipRect(surface, &rect);
	return new Value_SDL_Rect(rect);
}

// sdl.SDL_DuplicateSurface(surface as SDL_Surface)
Gurax_DeclareFunctionAlias(SDL_DuplicateSurface_gurax, "SDL_DuplicateSurface")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_DuplicateSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	// Function body
	SDL_Surface* rtn = SDL_DuplicateSurface(surface);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.SDL_ConvertSurface(src as SDL_Surface, fmt as SDL_PixelFormat, flags as Number)
Gurax_DeclareFunctionAlias(SDL_ConvertSurface_gurax, "SDL_ConvertSurface")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fmt", VTYPE_SDL_PixelFormat, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_ConvertSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* src = value_src.GetEntityPtr();
	auto& value_fmt = args_gurax.Pick<Value_SDL_PixelFormat>();
	const SDL_PixelFormat* fmt = value_fmt.GetEntityPtr();
	Uint32 flags = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_Surface* rtn = SDL_ConvertSurface(src, fmt, flags);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.SDL_ConvertSurfaceFormat(src as SDL_Surface, pixel_format as Number, flags as Number)
Gurax_DeclareFunctionAlias(SDL_ConvertSurfaceFormat_gurax, "SDL_ConvertSurfaceFormat")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixel_format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_ConvertSurfaceFormat_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* src = value_src.GetEntityPtr();
	Uint32 pixel_format = args_gurax.PickNumber<Uint32>();
	Uint32 flags = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_Surface* rtn = SDL_ConvertSurfaceFormat(src, pixel_format, flags);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.SDL_ConvertPixels(width as Number, height as Number, src_format as Number, src as Pointer, src_pitch as Number, dst_format as Number, dst as Pointer, dst_pitch as Number)
Gurax_DeclareFunctionAlias(SDL_ConvertPixels_gurax, "SDL_ConvertPixels")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("src_format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("src", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("src_pitch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dst_format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dst", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dst_pitch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_ConvertPixels_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	Uint32 src_format = args_gurax.PickNumber<Uint32>();
	const void* src = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<void>();
	int src_pitch = args_gurax.PickNumber<int>();
	Uint32 dst_format = args_gurax.PickNumber<Uint32>();
	void* dst = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!dst) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	int dst_pitch = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_ConvertPixels(width, height, src_format, src, src_pitch, dst_format, dst, dst_pitch);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_FillRect(dst as SDL_Surface, rect:nil as SDL_Rect, color as Number)
Gurax_DeclareFunctionAlias(SDL_FillRect_gurax, "SDL_FillRect")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("color", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_FillRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* dst = value_dst.GetEntityPtr();
	const SDL_Rect* rect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	Uint32 color = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_FillRect(dst, rect, color);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_FillRects(dst as SDL_Surface, rects:nil as SDL_Rect, count as Number, color as Number)
Gurax_DeclareFunctionAlias(SDL_FillRects_gurax, "SDL_FillRects")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rects", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("color", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_FillRects_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* dst = value_dst.GetEntityPtr();
	const SDL_Rect* rects = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	int count = args_gurax.PickNumber<int>();
	Uint32 color = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_FillRects(dst, rects, count, color);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_BlitSurface(src as SDL_Surface, srcrect:nil as SDL_Rect, dst as SDL_Surface, dstrect:nil as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_BlitSurface_gurax, "SDL_BlitSurface")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("dst", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_BlitSurface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* src = value_src.GetEntityPtr();
	const SDL_Rect* srcrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	auto& value_dst = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* dst = value_dst.GetEntityPtr();
	SDL_Rect* dstrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	// Function body
	int rtn = SDL_BlitSurface(src, srcrect, dst, dstrect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_UpperBlit(src as SDL_Surface, srcrect:nil as SDL_Rect, dst as SDL_Surface, dstrect:nil as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_UpperBlit_gurax, "SDL_UpperBlit")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("dst", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_UpperBlit_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* src = value_src.GetEntityPtr();
	const SDL_Rect* srcrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	auto& value_dst = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* dst = value_dst.GetEntityPtr();
	SDL_Rect* dstrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	// Function body
	int rtn = SDL_UpperBlit(src, srcrect, dst, dstrect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_LowerBlit(src as SDL_Surface, srcrect:nil as SDL_Rect, dst as SDL_Surface, dstrect:nil as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_LowerBlit_gurax, "SDL_LowerBlit")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("dst", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_LowerBlit_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* src = value_src.GetEntityPtr();
	SDL_Rect* srcrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	auto& value_dst = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* dst = value_dst.GetEntityPtr();
	SDL_Rect* dstrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	// Function body
	int rtn = SDL_LowerBlit(src, srcrect, dst, dstrect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SoftStretch(src as SDL_Surface, srcrect:nil as SDL_Rect, dst as SDL_Surface, dstrect:nil as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_SoftStretch_gurax, "SDL_SoftStretch")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("dst", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_SoftStretch_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* src = value_src.GetEntityPtr();
	const SDL_Rect* srcrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	auto& value_dst = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* dst = value_dst.GetEntityPtr();
	const SDL_Rect* dstrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	// Function body
	int rtn = SDL_SoftStretch(src, srcrect, dst, dstrect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_BlitScaled(src as SDL_Surface, srcrect:nil as SDL_Rect, dst as SDL_Surface, dstrect:nil as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_BlitScaled_gurax, "SDL_BlitScaled")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("dst", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_BlitScaled_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* src = value_src.GetEntityPtr();
	const SDL_Rect* srcrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	auto& value_dst = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* dst = value_dst.GetEntityPtr();
	SDL_Rect* dstrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	// Function body
	int rtn = SDL_BlitScaled(src, srcrect, dst, dstrect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_UpperBlitScaled(src as SDL_Surface, srcrect:nil as SDL_Rect, dst as SDL_Surface, dstrect:nil as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_UpperBlitScaled_gurax, "SDL_UpperBlitScaled")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("dst", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_UpperBlitScaled_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* src = value_src.GetEntityPtr();
	const SDL_Rect* srcrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	auto& value_dst = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* dst = value_dst.GetEntityPtr();
	SDL_Rect* dstrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	// Function body
	int rtn = SDL_UpperBlitScaled(src, srcrect, dst, dstrect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_LowerBlitScaled(src as SDL_Surface, srcrect:nil as SDL_Rect, dst as SDL_Surface, dstrect:nil as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_LowerBlitScaled_gurax, "SDL_LowerBlitScaled")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("srcrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("dst", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dstrect", VTYPE_SDL_Rect, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_LowerBlitScaled_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* src = value_src.GetEntityPtr();
	SDL_Rect* srcrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	auto& value_dst = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* dst = value_dst.GetEntityPtr();
	SDL_Rect* dstrect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	// Function body
	int rtn = SDL_LowerBlitScaled(src, srcrect, dst, dstrect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetYUVConversionMode(mode as Number)
Gurax_DeclareFunctionAlias(SDL_SetYUVConversionMode_gurax, "SDL_SetYUVConversionMode")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetYUVConversionMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_YUV_CONVERSION_MODE mode = args_gurax.PickNumber<SDL_YUV_CONVERSION_MODE>();
	// Function body
	SDL_SetYUVConversionMode(mode);
	return Gurax::Value::nil();
}

// sdl.SDL_GetYUVConversionMode()
Gurax_DeclareFunctionAlias(SDL_GetYUVConversionMode_gurax, "SDL_GetYUVConversionMode")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetYUVConversionMode_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_YUV_CONVERSION_MODE rtn = SDL_GetYUVConversionMode();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetYUVConversionModeForResolution(width as Number, height as Number)
Gurax_DeclareFunctionAlias(SDL_GetYUVConversionModeForResolution_gurax, "SDL_GetYUVConversionModeForResolution")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetYUVConversionModeForResolution_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	// Function body
	SDL_YUV_CONVERSION_MODE rtn = SDL_GetYUVConversionModeForResolution(width, height);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetWindowWMInfo(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_GetWindowWMInfo_gurax, "SDL_GetWindowWMInfo")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetWindowWMInfo_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	SDL_SysWMinfo info;
	if (!SDL_GetWindowWMInfo(window, &info)) return Value::nil();
	return new Value_SDL_SysWMinfo(info);
}

// sdl.SDL_SetClipboardText(text as String)
Gurax_DeclareFunctionAlias(SDL_SetClipboardText_gurax, "SDL_SetClipboardText")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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
}

Gurax_ImplementFunctionEx(SDL_PumpEvents_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_PumpEvents();
	return Gurax::Value::nil();
}

// sdl.SDL_PeepEvents(events as SDL_Event, numevents as Number, action as Number, minType as Number, maxType as Number)
Gurax_DeclareFunctionAlias(SDL_PeepEvents_gurax, "SDL_PeepEvents")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("events", VTYPE_SDL_Event, ArgOccur::Once, ArgFlag::None);
	DeclareArg("numevents", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("action", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("minType", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxType", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_PeepEvents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_events = args_gurax.Pick<Value_SDL_Event>();
	SDL_Event* events = value_events.GetEntityPtr();
	int numevents = args_gurax.PickNumber<int>();
	SDL_eventaction action = args_gurax.PickNumber<SDL_eventaction>();
	Uint32 minType = args_gurax.PickNumber<Uint32>();
	Uint32 maxType = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_PeepEvents(events, numevents, action, minType, maxType);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HasEvent(type as Number)
Gurax_DeclareFunctionAlias(SDL_HasEvent_gurax, "SDL_HasEvent")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_HasEvents(minType as Number, maxType as Number)
Gurax_DeclareFunctionAlias(SDL_HasEvents_gurax, "SDL_HasEvents")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("minType", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxType", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_FlushEvent(type as Number)
Gurax_DeclareFunctionAlias(SDL_FlushEvent_gurax, "SDL_FlushEvent")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_FlushEvents(minType as Number, maxType as Number)
Gurax_DeclareFunctionAlias(SDL_FlushEvents_gurax, "SDL_FlushEvents")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("minType", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxType", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_PollEvent(event as SDL_Event)
Gurax_DeclareFunctionAlias(SDL_PollEvent_gurax, "SDL_PollEvent")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("event", VTYPE_SDL_Event, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_PollEvent_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_event = args_gurax.Pick<Value_SDL_Event>();
	SDL_Event* event = value_event.GetEntityPtr();
	// Function body
	int rtn = SDL_PollEvent(event);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_WaitEvent(event as SDL_Event)
Gurax_DeclareFunctionAlias(SDL_WaitEvent_gurax, "SDL_WaitEvent")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("event", VTYPE_SDL_Event, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_WaitEvent_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_event = args_gurax.Pick<Value_SDL_Event>();
	SDL_Event* event = value_event.GetEntityPtr();
	// Function body
	int rtn = SDL_WaitEvent(event);
	return new Value_Number(rtn);
}

// sdl.SDL_WaitEventTimeout(event as SDL_Event, timeout as Number)
Gurax_DeclareFunctionAlias(SDL_WaitEventTimeout_gurax, "SDL_WaitEventTimeout")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("event", VTYPE_SDL_Event, ArgOccur::Once, ArgFlag::None);
	DeclareArg("timeout", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_WaitEventTimeout_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_event = args_gurax.Pick<Value_SDL_Event>();
	SDL_Event* event = value_event.GetEntityPtr();
	int timeout = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_WaitEventTimeout(event, timeout);
	return new Value_Number(rtn);
}

// sdl.SDL_PushEvent(event as SDL_Event)
Gurax_DeclareFunctionAlias(SDL_PushEvent_gurax, "SDL_PushEvent")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("event", VTYPE_SDL_Event, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_PushEvent_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_event = args_gurax.Pick<Value_SDL_Event>();
	SDL_Event* event = value_event.GetEntityPtr();
	// Function body
	int rtn = SDL_PushEvent(event);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_EventState(type as Number, state as Number)
Gurax_DeclareFunctionAlias(SDL_EventState_gurax, "SDL_EventState")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("state", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_RegisterEvents(numevents as Number)
Gurax_DeclareFunctionAlias(SDL_RegisterEvents_gurax, "SDL_RegisterEvents")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("numevents", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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
}

Gurax_ImplementFunctionEx(SDL_GetKeyboardFocus_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Window* rtn = SDL_GetKeyboardFocus();
	if (!rtn) return Value::nil();
	return new Value_SDL_Window(rtn);
}

// sdl.SDL_GetKeyboardState()
Gurax_DeclareFunctionAlias(SDL_GetKeyboardState_gurax, "SDL_GetKeyboardState")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetKeyboardState_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int numkeys;
	const Uint8* rtn = SDL_GetKeyboardState(&numkeys);
	RefPtr<Pointer> pPointer(new Pointer_Memory(new MemorySloth(numkeys, const_cast<Uint8*>(rtn))));
	return new Value_Pointer(pPointer.release());
}

// sdl.SDL_GetModState()
Gurax_DeclareFunctionAlias(SDL_GetModState_gurax, "SDL_GetModState")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetModState_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Keymod rtn = SDL_GetModState();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SetModState(modstate as Number)
Gurax_DeclareFunctionAlias(SDL_SetModState_gurax, "SDL_SetModState")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("modstate", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GetKeyFromScancode(scancode as Number)
Gurax_DeclareFunctionAlias(SDL_GetKeyFromScancode_gurax, "SDL_GetKeyFromScancode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("scancode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GetScancodeFromKey(key as Number)
Gurax_DeclareFunctionAlias(SDL_GetScancodeFromKey_gurax, "SDL_GetScancodeFromKey")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("key", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GetScancodeName(scancode as Number)
Gurax_DeclareFunctionAlias(SDL_GetScancodeName_gurax, "SDL_GetScancodeName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("scancode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GetScancodeFromName(name as String)
Gurax_DeclareFunctionAlias(SDL_GetScancodeFromName_gurax, "SDL_GetScancodeFromName")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GetKeyName(key as Number)
Gurax_DeclareFunctionAlias(SDL_GetKeyName_gurax, "SDL_GetKeyName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("key", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GetKeyFromName(name as String)
Gurax_DeclareFunctionAlias(SDL_GetKeyFromName_gurax, "SDL_GetKeyFromName")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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
}

Gurax_ImplementFunctionEx(SDL_StopTextInput_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_StopTextInput();
	return Gurax::Value::nil();
}

// sdl.SDL_SetTextInputRect(rect? as SDL_Rect)
Gurax_DeclareFunctionAlias(SDL_SetTextInputRect_gurax, "SDL_SetTextInputRect")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("rect", VTYPE_SDL_Rect, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetTextInputRect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Rect* rect = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Rect>().GetEntityPtr() : nullptr;
	// Function body
	SDL_SetTextInputRect(rect);
	return Gurax::Value::nil();
}

// sdl.SDL_HasScreenKeyboardSupport()
Gurax_DeclareFunctionAlias(SDL_HasScreenKeyboardSupport_gurax, "SDL_HasScreenKeyboardSupport")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_HasScreenKeyboardSupport_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_HasScreenKeyboardSupport();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_IsScreenKeyboardShown(window as SDL_Window)
Gurax_DeclareFunctionAlias(SDL_IsScreenKeyboardShown_gurax, "SDL_IsScreenKeyboardShown")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_IsScreenKeyboardShown_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_IsScreenKeyboardShown(window);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_GetMouseFocus()
Gurax_DeclareFunctionAlias(SDL_GetMouseFocus_gurax, "SDL_GetMouseFocus")
{
	Declare(VTYPE_SDL_Window, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetMouseFocus_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Window* rtn = SDL_GetMouseFocus();
	if (!rtn) return Value::nil();
	return new Value_SDL_Window(rtn);
}

// sdl.SDL_GetMouseState(&x:nilRef as Number, &y:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GetMouseState_gurax, "SDL_GetMouseState")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetMouseState_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Referencer> x(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> y(args_gurax.PickReferencer().Reference());
	// Function body
	int x_, y_;
	Uint32 state = SDL_GetMouseState(&x_, &y_);
	x->SetValue(new Value_Number(x_));
	y->SetValue(new Value_Number(y_));
	return new Value_Number(state);
}

// sdl.SDL_GetGlobalMouseState(&x:nilRef as Number, &y:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GetGlobalMouseState_gurax, "SDL_GetGlobalMouseState")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetGlobalMouseState_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Referencer> x(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> y(args_gurax.PickReferencer().Reference());
	// Function body
	int x_, y_;
	Uint32 state = SDL_GetGlobalMouseState(&x_, &y_);
	x->SetValue(new Value_Number(x_));
	y->SetValue(new Value_Number(y_));
	return new Value_Number(state);
}

// sdl.SDL_GetRelativeMouseState(&x:nilRef as Number, &y:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GetRelativeMouseState_gurax, "SDL_GetRelativeMouseState")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetRelativeMouseState_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Referencer> x(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> y(args_gurax.PickReferencer().Reference());
	// Function body
	int x_, y_;
	Uint32 state = SDL_GetRelativeMouseState(&x_, &y_);
	x->SetValue(new Value_Number(x_));
	y->SetValue(new Value_Number(y_));
	return new Value_Number(state);
}

// sdl.SDL_WarpMouseInWindow(window as SDL_Window, x as Number, y as Number)
Gurax_DeclareFunctionAlias(SDL_WarpMouseInWindow_gurax, "SDL_WarpMouseInWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_SDL_Window, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_WarpMouseInWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_window = args_gurax.Pick<Value_SDL_Window>();
	SDL_Window* window = value_window.GetEntityPtr();
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	// Function body
	SDL_WarpMouseInWindow(window, x, y);
	return Gurax::Value::nil();
}

// sdl.SDL_WarpMouseGlobal(x as Number, y as Number)
Gurax_DeclareFunctionAlias(SDL_WarpMouseGlobal_gurax, "SDL_WarpMouseGlobal")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_SetRelativeMouseMode(enabled as Bool)
Gurax_DeclareFunctionAlias(SDL_SetRelativeMouseMode_gurax, "SDL_SetRelativeMouseMode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("enabled", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_CaptureMouse(enabled as Bool)
Gurax_DeclareFunctionAlias(SDL_CaptureMouse_gurax, "SDL_CaptureMouse")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("enabled", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
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
}

Gurax_ImplementFunctionEx(SDL_GetRelativeMouseMode_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_GetRelativeMouseMode();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_CreateCursor(data as Pointer, mask as Pointer, w as Number, h as Number, hot_x as Number, hot_y as Number)
Gurax_DeclareFunctionAlias(SDL_CreateCursor_gurax, "SDL_CreateCursor")
{
	Declare(VTYPE_SDL_Cursor, Flag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mask", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("h", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hot_x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hot_y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_CreateCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Uint8* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<Uint8>();
	const Uint8* mask = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<Uint8>();
	int w = args_gurax.PickNumber<int>();
	int h = args_gurax.PickNumber<int>();
	int hot_x = args_gurax.PickNumber<int>();
	int hot_y = args_gurax.PickNumber<int>();
	// Function body
	SDL_Cursor* rtn = SDL_CreateCursor(data, mask, w, h, hot_x, hot_y);
	if (!rtn) return Value::nil();
	return new Value_SDL_Cursor(rtn);
}

// sdl.SDL_CreateColorCursor(surface as SDL_Surface, hot_x as Number, hot_y as Number)
Gurax_DeclareFunctionAlias(SDL_CreateColorCursor_gurax, "SDL_CreateColorCursor")
{
	Declare(VTYPE_SDL_Cursor, Flag::None);
	DeclareArg("surface", VTYPE_SDL_Surface, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hot_x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hot_y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_CreateColorCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_SDL_Surface>();
	SDL_Surface* surface = value_surface.GetEntityPtr();
	int hot_x = args_gurax.PickNumber<int>();
	int hot_y = args_gurax.PickNumber<int>();
	// Function body
	SDL_Cursor* rtn = SDL_CreateColorCursor(surface, hot_x, hot_y);
	if (!rtn) return Value::nil();
	return new Value_SDL_Cursor(rtn);
}

// sdl.SDL_CreateSystemCursor(id as Number)
Gurax_DeclareFunctionAlias(SDL_CreateSystemCursor_gurax, "SDL_CreateSystemCursor")
{
	Declare(VTYPE_SDL_Cursor, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_CreateSystemCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_SystemCursor id = args_gurax.PickNumber<SDL_SystemCursor>();
	// Function body
	SDL_Cursor* rtn = SDL_CreateSystemCursor(id);
	if (!rtn) return Value::nil();
	return new Value_SDL_Cursor(rtn);
}

// sdl.SDL_SetCursor(cursor as SDL_Cursor)
Gurax_DeclareFunctionAlias(SDL_SetCursor_gurax, "SDL_SetCursor")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cursor", VTYPE_SDL_Cursor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SetCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cursor = args_gurax.Pick<Value_SDL_Cursor>();
	SDL_Cursor* cursor = value_cursor.GetEntityPtr();
	// Function body
	SDL_SetCursor(cursor);
	return Gurax::Value::nil();
}

// sdl.SDL_GetCursor()
Gurax_DeclareFunctionAlias(SDL_GetCursor_gurax, "SDL_GetCursor")
{
	Declare(VTYPE_SDL_Cursor, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetCursor_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Cursor* rtn = SDL_GetCursor();
	if (!rtn) return Value::nil();
	return new Value_SDL_Cursor(rtn);
}

// sdl.SDL_GetDefaultCursor()
Gurax_DeclareFunctionAlias(SDL_GetDefaultCursor_gurax, "SDL_GetDefaultCursor")
{
	Declare(VTYPE_SDL_Cursor, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetDefaultCursor_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Cursor* rtn = SDL_GetDefaultCursor();
	if (!rtn) return Value::nil();
	return new Value_SDL_Cursor(rtn);
}

// sdl.SDL_FreeCursor(cursor:nil as SDL_Cursor)
Gurax_DeclareFunctionAlias(SDL_FreeCursor_gurax, "SDL_FreeCursor")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cursor", VTYPE_SDL_Cursor, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_FreeCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_Cursor* cursor = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_Cursor>().GetEntityPtr() : nullptr;
	// Function body
	SDL_FreeCursor(cursor);
	return Gurax::Value::nil();
}

// sdl.SDL_ShowCursor(toggle as Number)
Gurax_DeclareFunctionAlias(SDL_ShowCursor_gurax, "SDL_ShowCursor")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("toggle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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
}

Gurax_ImplementFunctionEx(SDL_NumJoysticks_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_NumJoysticks();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickNameForIndex(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickNameForIndex_gurax, "SDL_JoystickNameForIndex")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_JoystickGetDevicePlayerIndex(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetDevicePlayerIndex_gurax, "SDL_JoystickGetDevicePlayerIndex")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_JoystickGetDeviceGUID(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetDeviceGUID_gurax, "SDL_JoystickGetDeviceGUID")
{
	Declare(VTYPE_SDL_JoystickGUID, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_JoystickGetDeviceVendor(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetDeviceVendor_gurax, "SDL_JoystickGetDeviceVendor")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_JoystickGetDeviceProduct(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetDeviceProduct_gurax, "SDL_JoystickGetDeviceProduct")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_JoystickGetDeviceProductVersion(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetDeviceProductVersion_gurax, "SDL_JoystickGetDeviceProductVersion")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_JoystickGetDeviceType(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetDeviceType_gurax, "SDL_JoystickGetDeviceType")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_JoystickGetDeviceInstanceID(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetDeviceInstanceID_gurax, "SDL_JoystickGetDeviceInstanceID")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_JoystickOpen(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickOpen_gurax, "SDL_JoystickOpen")
{
	Declare(VTYPE_SDL_Joystick, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickOpen_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_Joystick* rtn = SDL_JoystickOpen(device_index);
	if (!rtn) return Value::nil();
	return new Value_SDL_Joystick(rtn);
}

// sdl.SDL_JoystickFromInstanceID(instance_id as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickFromInstanceID_gurax, "SDL_JoystickFromInstanceID")
{
	Declare(VTYPE_SDL_Joystick, Flag::None);
	DeclareArg("instance_id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickFromInstanceID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_JoystickID instance_id = args_gurax.PickNumber<SDL_JoystickID>();
	// Function body
	SDL_Joystick* rtn = SDL_JoystickFromInstanceID(instance_id);
	if (!rtn) return Value::nil();
	return new Value_SDL_Joystick(rtn);
}

// sdl.SDL_JoystickFromPlayerIndex(player_index as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickFromPlayerIndex_gurax, "SDL_JoystickFromPlayerIndex")
{
	Declare(VTYPE_SDL_Joystick, Flag::None);
	DeclareArg("player_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickFromPlayerIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int player_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_Joystick* rtn = SDL_JoystickFromPlayerIndex(player_index);
	if (!rtn) return Value::nil();
	return new Value_SDL_Joystick(rtn);
}

// sdl.SDL_JoystickName(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickName_gurax, "SDL_JoystickName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	const char* rtn = SDL_JoystickName(joystick);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_JoystickGetPlayerIndex(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickGetPlayerIndex_gurax, "SDL_JoystickGetPlayerIndex")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickGetPlayerIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	int rtn = SDL_JoystickGetPlayerIndex(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickSetPlayerIndex(joystick as SDL_Joystick, player_index as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickSetPlayerIndex_gurax, "SDL_JoystickSetPlayerIndex")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	DeclareArg("player_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickSetPlayerIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	int player_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_JoystickSetPlayerIndex(joystick, player_index);
	return Gurax::Value::nil();
}

// sdl.SDL_JoystickGetGUID(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickGetGUID_gurax, "SDL_JoystickGetGUID")
{
	Declare(VTYPE_SDL_JoystickGUID, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickGetGUID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	SDL_JoystickGUID rtn = SDL_JoystickGetGUID(joystick);
	return new Value_SDL_JoystickGUID(rtn);
}

// sdl.SDL_JoystickGetVendor(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickGetVendor_gurax, "SDL_JoystickGetVendor")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickGetVendor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	Uint16 rtn = SDL_JoystickGetVendor(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetProduct(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickGetProduct_gurax, "SDL_JoystickGetProduct")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickGetProduct_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	Uint16 rtn = SDL_JoystickGetProduct(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetProductVersion(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickGetProductVersion_gurax, "SDL_JoystickGetProductVersion")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickGetProductVersion_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	Uint16 rtn = SDL_JoystickGetProductVersion(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetType(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickGetType_gurax, "SDL_JoystickGetType")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickGetType_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	SDL_JoystickType rtn = SDL_JoystickGetType(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetGUIDString(guid as SDL_JoystickGUID)
Gurax_DeclareFunctionAlias(SDL_JoystickGetGUIDString_gurax, "SDL_JoystickGetGUIDString")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("guid", VTYPE_SDL_JoystickGUID, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickGetGUIDString_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_guid = args_gurax.Pick<Value_SDL_JoystickGUID>();
	SDL_JoystickGUID& guid = value_guid.GetEntity();
	// Function body
	char szGUID[64]; // requires at least 33 bytes
	SDL_JoystickGetGUIDString(guid, szGUID, sizeof(szGUID));
	return new Value_String(szGUID);
}

// sdl.SDL_JoystickGetGUIDFromString(pchGUID as String)
Gurax_DeclareFunctionAlias(SDL_JoystickGetGUIDFromString_gurax, "SDL_JoystickGetGUIDFromString")
{
	Declare(VTYPE_SDL_JoystickGUID, Flag::None);
	DeclareArg("pchGUID", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_JoystickGetAttached(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickGetAttached_gurax, "SDL_JoystickGetAttached")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickGetAttached_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_JoystickGetAttached(joystick);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_JoystickInstanceID(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickInstanceID_gurax, "SDL_JoystickInstanceID")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickInstanceID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	SDL_JoystickID rtn = SDL_JoystickInstanceID(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickNumAxes(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickNumAxes_gurax, "SDL_JoystickNumAxes")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickNumAxes_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	int rtn = SDL_JoystickNumAxes(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickNumBalls(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickNumBalls_gurax, "SDL_JoystickNumBalls")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickNumBalls_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	int rtn = SDL_JoystickNumBalls(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickNumHats(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickNumHats_gurax, "SDL_JoystickNumHats")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickNumHats_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	int rtn = SDL_JoystickNumHats(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickNumButtons(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickNumButtons_gurax, "SDL_JoystickNumButtons")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickNumButtons_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	int rtn = SDL_JoystickNumButtons(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickUpdate()
Gurax_DeclareFunctionAlias(SDL_JoystickUpdate_gurax, "SDL_JoystickUpdate")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickUpdate_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_JoystickUpdate();
	return Gurax::Value::nil();
}

// sdl.SDL_JoystickEventState(state as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickEventState_gurax, "SDL_JoystickEventState")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("state", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_JoystickGetAxis(joystick as SDL_Joystick, axis as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetAxis_gurax, "SDL_JoystickGetAxis")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	DeclareArg("axis", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickGetAxis_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	int axis = args_gurax.PickNumber<int>();
	// Function body
	Sint16 rtn = SDL_JoystickGetAxis(joystick, axis);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetHat(joystick as SDL_Joystick, hat as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetHat_gurax, "SDL_JoystickGetHat")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickGetHat_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	int hat = args_gurax.PickNumber<int>();
	// Function body
	Uint8 rtn = SDL_JoystickGetHat(joystick, hat);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickGetBall(joystick as SDL_Joystick, ball as Number, &dx:nilRef as Number, &dy:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetBall_gurax, "SDL_JoystickGetBall")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ball", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dx", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("dy", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_JoystickGetBall_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	int ball = args_gurax.PickNumber<int>();
	RefPtr<Referencer> dx(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> dy(args_gurax.PickReferencer().Reference());
	// Function body
	int dx_, dy_;
	int rtn = SDL_JoystickGetBall(joystick, ball, &dx_, &dy_);
	dx->SetValue(new Value_Number(dx_));
	dy->SetValue(new Value_Number(dy_));
	return new Value_Number(rtn);
}

// sdl.SDL_JoystickGetButton(joystick as SDL_Joystick, button as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickGetButton_gurax, "SDL_JoystickGetButton")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	DeclareArg("button", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickGetButton_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	int button = args_gurax.PickNumber<int>();
	// Function body
	Uint8 rtn = SDL_JoystickGetButton(joystick, button);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickRumble(joystick as SDL_Joystick, low_frequency_rumble as Number, high_frequency_rumble as Number, duration_ms as Number)
Gurax_DeclareFunctionAlias(SDL_JoystickRumble_gurax, "SDL_JoystickRumble")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
	DeclareArg("low_frequency_rumble", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("high_frequency_rumble", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("duration_ms", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickRumble_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	Uint16 low_frequency_rumble = args_gurax.PickNumber<Uint16>();
	Uint16 high_frequency_rumble = args_gurax.PickNumber<Uint16>();
	Uint32 duration_ms = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_JoystickRumble(joystick, low_frequency_rumble, high_frequency_rumble, duration_ms);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_JoystickClose(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickClose_gurax, "SDL_JoystickClose")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickClose_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	SDL_JoystickClose(joystick);
	return Gurax::Value::nil();
}

// sdl.SDL_JoystickCurrentPowerLevel(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickCurrentPowerLevel_gurax, "SDL_JoystickCurrentPowerLevel")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickCurrentPowerLevel_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	SDL_JoystickPowerLevel rtn = SDL_JoystickCurrentPowerLevel(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerAddMappingsFromRW(rw as SDL_RWops, freerw as Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerAddMappingsFromRW_gurax, "SDL_GameControllerAddMappingsFromRW")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("rw", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("freerw", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerAddMappingsFromRW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_rw = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* rw = value_rw.GetEntityPtr();
	int freerw = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_GameControllerAddMappingsFromRW(rw, freerw);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerAddMapping(mappingString as String)
Gurax_DeclareFunctionAlias(SDL_GameControllerAddMapping_gurax, "SDL_GameControllerAddMapping")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("mappingString", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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
}

Gurax_ImplementFunctionEx(SDL_GameControllerNumMappings_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_GameControllerNumMappings();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerMappingForIndex(mapping_index as Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerMappingForIndex_gurax, "SDL_GameControllerMappingForIndex")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("mapping_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerMappingForIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int mapping_index = args_gurax.PickNumber<int>();
	// Function body
	char* rtn = SDL_GameControllerMappingForIndex(mapping_index);
	if (!rtn) return Value::nil();
	RefPtr<Value> pValue(new Value_String(rtn));
	SDL_free(rtn);
	return pValue.release();
}

// sdl.SDL_GameControllerMappingForGUID(guid as SDL_JoystickGUID)
Gurax_DeclareFunctionAlias(SDL_GameControllerMappingForGUID_gurax, "SDL_GameControllerMappingForGUID")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("guid", VTYPE_SDL_JoystickGUID, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerMappingForGUID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_guid = args_gurax.Pick<Value_SDL_JoystickGUID>();
	SDL_JoystickGUID& guid = value_guid.GetEntity();
	// Function body
	char* rtn = SDL_GameControllerMappingForGUID(guid);
	if (!rtn) return Value::nil();
	RefPtr<Value> pValue(new Value_String(rtn));
	SDL_free(rtn);
	return pValue.release();
}

// sdl.SDL_GameControllerMapping(gamecontroller as SDL_GameController)
Gurax_DeclareFunctionAlias(SDL_GameControllerMapping_gurax, "SDL_GameControllerMapping")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerMapping_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_gamecontroller = args_gurax.Pick<Value_SDL_GameController>();
	SDL_GameController* gamecontroller = value_gamecontroller.GetEntityPtr();
	// Function body
	char* rtn = SDL_GameControllerMapping(gamecontroller);
	if (!rtn) return Value::nil();
	RefPtr<Value> pValue(new Value_String(rtn));
	SDL_free(rtn);
	return pValue.release();
}

// sdl.SDL_IsGameController(joystick_index as Number)
Gurax_DeclareFunctionAlias(SDL_IsGameController_gurax, "SDL_IsGameController")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("joystick_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GameControllerNameForIndex(joystick_index as Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerNameForIndex_gurax, "SDL_GameControllerNameForIndex")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("joystick_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GameControllerTypeForIndex(joystick_index as Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerTypeForIndex_gurax, "SDL_GameControllerTypeForIndex")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GameControllerMappingForDeviceIndex(joystick_index as Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerMappingForDeviceIndex_gurax, "SDL_GameControllerMappingForDeviceIndex")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("joystick_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerMappingForDeviceIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int joystick_index = args_gurax.PickNumber<int>();
	// Function body
	char* rtn = SDL_GameControllerMappingForDeviceIndex(joystick_index);
	if (!rtn) return Value::nil();
	RefPtr<Value> pValue(new Value_String(rtn));
	SDL_free(rtn);
	return pValue.release();
}

// sdl.SDL_GameControllerOpen(joystick_index as Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerOpen_gurax, "SDL_GameControllerOpen")
{
	Declare(VTYPE_SDL_GameController, Flag::None);
	DeclareArg("joystick_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerOpen_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int joystick_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_GameController* rtn = SDL_GameControllerOpen(joystick_index);
	if (!rtn) return Value::nil();
	return new Value_SDL_GameController(rtn);
}

// sdl.SDL_GameControllerFromInstanceID(joyid as Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerFromInstanceID_gurax, "SDL_GameControllerFromInstanceID")
{
	Declare(VTYPE_SDL_GameController, Flag::None);
	DeclareArg("joyid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerFromInstanceID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_JoystickID joyid = args_gurax.PickNumber<SDL_JoystickID>();
	// Function body
	SDL_GameController* rtn = SDL_GameControllerFromInstanceID(joyid);
	if (!rtn) return Value::nil();
	return new Value_SDL_GameController(rtn);
}

// sdl.SDL_GameControllerFromPlayerIndex(player_index as Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerFromPlayerIndex_gurax, "SDL_GameControllerFromPlayerIndex")
{
	Declare(VTYPE_SDL_GameController, Flag::None);
	DeclareArg("player_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerFromPlayerIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int player_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_GameController* rtn = SDL_GameControllerFromPlayerIndex(player_index);
	if (!rtn) return Value::nil();
	return new Value_SDL_GameController(rtn);
}

// sdl.SDL_GameControllerName(gamecontroller as SDL_GameController)
Gurax_DeclareFunctionAlias(SDL_GameControllerName_gurax, "SDL_GameControllerName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_gamecontroller = args_gurax.Pick<Value_SDL_GameController>();
	SDL_GameController* gamecontroller = value_gamecontroller.GetEntityPtr();
	// Function body
	const char* rtn = SDL_GameControllerName(gamecontroller);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_GameControllerGetType(gamecontroller as SDL_GameController)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetType_gurax, "SDL_GameControllerGetType")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetType_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_gamecontroller = args_gurax.Pick<Value_SDL_GameController>();
	SDL_GameController* gamecontroller = value_gamecontroller.GetEntityPtr();
	// Function body
	SDL_GameControllerType rtn = SDL_GameControllerGetType(gamecontroller);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerGetPlayerIndex(gamecontroller as SDL_GameController)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetPlayerIndex_gurax, "SDL_GameControllerGetPlayerIndex")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetPlayerIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_gamecontroller = args_gurax.Pick<Value_SDL_GameController>();
	SDL_GameController* gamecontroller = value_gamecontroller.GetEntityPtr();
	// Function body
	int rtn = SDL_GameControllerGetPlayerIndex(gamecontroller);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerSetPlayerIndex(gamecontroller as SDL_GameController, player_index as Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerSetPlayerIndex_gurax, "SDL_GameControllerSetPlayerIndex")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController, ArgOccur::Once, ArgFlag::None);
	DeclareArg("player_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerSetPlayerIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_gamecontroller = args_gurax.Pick<Value_SDL_GameController>();
	SDL_GameController* gamecontroller = value_gamecontroller.GetEntityPtr();
	int player_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_GameControllerSetPlayerIndex(gamecontroller, player_index);
	return Gurax::Value::nil();
}

// sdl.SDL_GameControllerGetVendor(gamecontroller as SDL_GameController)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetVendor_gurax, "SDL_GameControllerGetVendor")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetVendor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_gamecontroller = args_gurax.Pick<Value_SDL_GameController>();
	SDL_GameController* gamecontroller = value_gamecontroller.GetEntityPtr();
	// Function body
	Uint16 rtn = SDL_GameControllerGetVendor(gamecontroller);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerGetProduct(gamecontroller as SDL_GameController)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetProduct_gurax, "SDL_GameControllerGetProduct")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetProduct_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_gamecontroller = args_gurax.Pick<Value_SDL_GameController>();
	SDL_GameController* gamecontroller = value_gamecontroller.GetEntityPtr();
	// Function body
	Uint16 rtn = SDL_GameControllerGetProduct(gamecontroller);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerGetProductVersion(gamecontroller as SDL_GameController)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetProductVersion_gurax, "SDL_GameControllerGetProductVersion")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetProductVersion_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_gamecontroller = args_gurax.Pick<Value_SDL_GameController>();
	SDL_GameController* gamecontroller = value_gamecontroller.GetEntityPtr();
	// Function body
	Uint16 rtn = SDL_GameControllerGetProductVersion(gamecontroller);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerGetAttached(gamecontroller as SDL_GameController)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetAttached_gurax, "SDL_GameControllerGetAttached")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetAttached_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_gamecontroller = args_gurax.Pick<Value_SDL_GameController>();
	SDL_GameController* gamecontroller = value_gamecontroller.GetEntityPtr();
	// Function body
	SDL_bool rtn = SDL_GameControllerGetAttached(gamecontroller);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_GameControllerGetJoystick(gamecontroller as SDL_GameController)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetJoystick_gurax, "SDL_GameControllerGetJoystick")
{
	Declare(VTYPE_SDL_Joystick, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetJoystick_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_gamecontroller = args_gurax.Pick<Value_SDL_GameController>();
	SDL_GameController* gamecontroller = value_gamecontroller.GetEntityPtr();
	// Function body
	SDL_Joystick* rtn = SDL_GameControllerGetJoystick(gamecontroller);
	if (!rtn) return Value::nil();
	return new Value_SDL_Joystick(rtn);
}

// sdl.SDL_GameControllerEventState(state as Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerEventState_gurax, "SDL_GameControllerEventState")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("state", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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
}

Gurax_ImplementFunctionEx(SDL_GameControllerUpdate_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_GameControllerUpdate();
	return Gurax::Value::nil();
}

// sdl.SDL_GameControllerGetAxisFromString(pchString as String)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetAxisFromString_gurax, "SDL_GameControllerGetAxisFromString")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("pchString", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GameControllerGetStringForAxis(axis as Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetStringForAxis_gurax, "SDL_GameControllerGetStringForAxis")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("axis", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GameControllerGetAxis(gamecontroller as SDL_GameController, axis as Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetAxis_gurax, "SDL_GameControllerGetAxis")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController, ArgOccur::Once, ArgFlag::None);
	DeclareArg("axis", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetAxis_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_gamecontroller = args_gurax.Pick<Value_SDL_GameController>();
	SDL_GameController* gamecontroller = value_gamecontroller.GetEntityPtr();
	SDL_GameControllerAxis axis = args_gurax.PickNumber<SDL_GameControllerAxis>();
	// Function body
	Sint16 rtn = SDL_GameControllerGetAxis(gamecontroller, axis);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerGetButtonFromString(pchString as String)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetButtonFromString_gurax, "SDL_GameControllerGetButtonFromString")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("pchString", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GameControllerGetStringForButton(button as Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetStringForButton_gurax, "SDL_GameControllerGetStringForButton")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("button", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
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

// sdl.SDL_GameControllerGetButton(gamecontroller as SDL_GameController, button as Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerGetButton_gurax, "SDL_GameControllerGetButton")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController, ArgOccur::Once, ArgFlag::None);
	DeclareArg("button", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerGetButton_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_gamecontroller = args_gurax.Pick<Value_SDL_GameController>();
	SDL_GameController* gamecontroller = value_gamecontroller.GetEntityPtr();
	SDL_GameControllerButton button = args_gurax.PickNumber<SDL_GameControllerButton>();
	// Function body
	Uint8 rtn = SDL_GameControllerGetButton(gamecontroller, button);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerRumble(gamecontroller as SDL_GameController, low_frequency_rumble as Number, high_frequency_rumble as Number, duration_ms as Number)
Gurax_DeclareFunctionAlias(SDL_GameControllerRumble_gurax, "SDL_GameControllerRumble")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController, ArgOccur::Once, ArgFlag::None);
	DeclareArg("low_frequency_rumble", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("high_frequency_rumble", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("duration_ms", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerRumble_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_gamecontroller = args_gurax.Pick<Value_SDL_GameController>();
	SDL_GameController* gamecontroller = value_gamecontroller.GetEntityPtr();
	Uint16 low_frequency_rumble = args_gurax.PickNumber<Uint16>();
	Uint16 high_frequency_rumble = args_gurax.PickNumber<Uint16>();
	Uint32 duration_ms = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_GameControllerRumble(gamecontroller, low_frequency_rumble, high_frequency_rumble, duration_ms);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GameControllerClose(gamecontroller as SDL_GameController)
Gurax_DeclareFunctionAlias(SDL_GameControllerClose_gurax, "SDL_GameControllerClose")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("gamecontroller", VTYPE_SDL_GameController, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GameControllerClose_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_gamecontroller = args_gurax.Pick<Value_SDL_GameController>();
	SDL_GameController* gamecontroller = value_gamecontroller.GetEntityPtr();
	// Function body
	SDL_GameControllerClose(gamecontroller);
	return Gurax::Value::nil();
}

// sdl.SDL_NumSensors()
Gurax_DeclareFunctionAlias(SDL_NumSensors_gurax, "SDL_NumSensors")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_NumSensors_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_NumSensors();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SensorGetDeviceName(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_SensorGetDeviceName_gurax, "SDL_SensorGetDeviceName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SensorGetDeviceName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	const char* rtn = SDL_SensorGetDeviceName(device_index);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_SensorGetDeviceType(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_SensorGetDeviceType_gurax, "SDL_SensorGetDeviceType")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SensorGetDeviceType_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_SensorType rtn = SDL_SensorGetDeviceType(device_index);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SensorGetDeviceNonPortableType(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_SensorGetDeviceNonPortableType_gurax, "SDL_SensorGetDeviceNonPortableType")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SensorGetDeviceNonPortableType_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_SensorGetDeviceNonPortableType(device_index);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SensorGetDeviceInstanceID(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_SensorGetDeviceInstanceID_gurax, "SDL_SensorGetDeviceInstanceID")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SensorGetDeviceInstanceID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_SensorID rtn = SDL_SensorGetDeviceInstanceID(device_index);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SensorOpen(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_SensorOpen_gurax, "SDL_SensorOpen")
{
	Declare(VTYPE_SDL_Sensor, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SensorOpen_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_Sensor* rtn = SDL_SensorOpen(device_index);
	if (!rtn) return Value::nil();
	return new Value_SDL_Sensor(rtn);
}

// sdl.SDL_SensorFromInstanceID(instance_id as Number)
Gurax_DeclareFunctionAlias(SDL_SensorFromInstanceID_gurax, "SDL_SensorFromInstanceID")
{
	Declare(VTYPE_SDL_Sensor, Flag::None);
	DeclareArg("instance_id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SensorFromInstanceID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_SensorID instance_id = args_gurax.PickNumber<SDL_SensorID>();
	// Function body
	SDL_Sensor* rtn = SDL_SensorFromInstanceID(instance_id);
	if (!rtn) return Value::nil();
	return new Value_SDL_Sensor(rtn);
}

// sdl.SDL_SensorGetName(sensor as SDL_Sensor)
Gurax_DeclareFunctionAlias(SDL_SensorGetName_gurax, "SDL_SensorGetName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("sensor", VTYPE_SDL_Sensor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SensorGetName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_sensor = args_gurax.Pick<Value_SDL_Sensor>();
	SDL_Sensor* sensor = value_sensor.GetEntityPtr();
	// Function body
	const char* rtn = SDL_SensorGetName(sensor);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_SensorGetType(sensor as SDL_Sensor)
Gurax_DeclareFunctionAlias(SDL_SensorGetType_gurax, "SDL_SensorGetType")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("sensor", VTYPE_SDL_Sensor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SensorGetType_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_sensor = args_gurax.Pick<Value_SDL_Sensor>();
	SDL_Sensor* sensor = value_sensor.GetEntityPtr();
	// Function body
	SDL_SensorType rtn = SDL_SensorGetType(sensor);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SensorGetNonPortableType(sensor as SDL_Sensor)
Gurax_DeclareFunctionAlias(SDL_SensorGetNonPortableType_gurax, "SDL_SensorGetNonPortableType")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("sensor", VTYPE_SDL_Sensor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SensorGetNonPortableType_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_sensor = args_gurax.Pick<Value_SDL_Sensor>();
	SDL_Sensor* sensor = value_sensor.GetEntityPtr();
	// Function body
	int rtn = SDL_SensorGetNonPortableType(sensor);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SensorGetInstanceID(sensor as SDL_Sensor)
Gurax_DeclareFunctionAlias(SDL_SensorGetInstanceID_gurax, "SDL_SensorGetInstanceID")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("sensor", VTYPE_SDL_Sensor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SensorGetInstanceID_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_sensor = args_gurax.Pick<Value_SDL_Sensor>();
	SDL_Sensor* sensor = value_sensor.GetEntityPtr();
	// Function body
	SDL_SensorID rtn = SDL_SensorGetInstanceID(sensor);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SensorClose(sensor as SDL_Sensor)
Gurax_DeclareFunctionAlias(SDL_SensorClose_gurax, "SDL_SensorClose")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("sensor", VTYPE_SDL_Sensor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_SensorClose_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_sensor = args_gurax.Pick<Value_SDL_Sensor>();
	SDL_Sensor* sensor = value_sensor.GetEntityPtr();
	// Function body
	SDL_SensorClose(sensor);
	return Gurax::Value::nil();
}

// sdl.SDL_SensorUpdate()
Gurax_DeclareFunctionAlias(SDL_SensorUpdate_gurax, "SDL_SensorUpdate")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_SensorUpdate_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_SensorUpdate();
	return Gurax::Value::nil();
}

// sdl.SDL_NumHaptics()
Gurax_DeclareFunctionAlias(SDL_NumHaptics_gurax, "SDL_NumHaptics")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_NumHaptics_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_NumHaptics();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticName(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_HapticName_gurax, "SDL_HapticName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	const char* rtn = SDL_HapticName(device_index);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_HapticOpen(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_HapticOpen_gurax, "SDL_HapticOpen")
{
	Declare(VTYPE_SDL_Haptic, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticOpen_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	SDL_Haptic* rtn = SDL_HapticOpen(device_index);
	if (!rtn) return Value::nil();
	return new Value_SDL_Haptic(rtn);
}

// sdl.SDL_HapticOpened(device_index as Number)
Gurax_DeclareFunctionAlias(SDL_HapticOpened_gurax, "SDL_HapticOpened")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device_index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticOpened_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int device_index = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_HapticOpened(device_index);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticIndex(haptic as SDL_Haptic)
Gurax_DeclareFunctionAlias(SDL_HapticIndex_gurax, "SDL_HapticIndex")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	// Function body
	int rtn = SDL_HapticIndex(haptic);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_MouseIsHaptic()
Gurax_DeclareFunctionAlias(SDL_MouseIsHaptic_gurax, "SDL_MouseIsHaptic")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_MouseIsHaptic_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_MouseIsHaptic();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticOpenFromMouse()
Gurax_DeclareFunctionAlias(SDL_HapticOpenFromMouse_gurax, "SDL_HapticOpenFromMouse")
{
	Declare(VTYPE_SDL_Haptic, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticOpenFromMouse_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_Haptic* rtn = SDL_HapticOpenFromMouse();
	if (!rtn) return Value::nil();
	return new Value_SDL_Haptic(rtn);
}

// sdl.SDL_JoystickIsHaptic(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_JoystickIsHaptic_gurax, "SDL_JoystickIsHaptic")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_JoystickIsHaptic_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	int rtn = SDL_JoystickIsHaptic(joystick);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticOpenFromJoystick(joystick as SDL_Joystick)
Gurax_DeclareFunctionAlias(SDL_HapticOpenFromJoystick_gurax, "SDL_HapticOpenFromJoystick")
{
	Declare(VTYPE_SDL_Haptic, Flag::None);
	DeclareArg("joystick", VTYPE_SDL_Joystick, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticOpenFromJoystick_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_joystick = args_gurax.Pick<Value_SDL_Joystick>();
	SDL_Joystick* joystick = value_joystick.GetEntityPtr();
	// Function body
	SDL_Haptic* rtn = SDL_HapticOpenFromJoystick(joystick);
	if (!rtn) return Value::nil();
	return new Value_SDL_Haptic(rtn);
}

// sdl.SDL_HapticClose(haptic as SDL_Haptic)
Gurax_DeclareFunctionAlias(SDL_HapticClose_gurax, "SDL_HapticClose")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticClose_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	// Function body
	SDL_HapticClose(haptic);
	return Gurax::Value::nil();
}

// sdl.SDL_HapticNumEffects(haptic as SDL_Haptic)
Gurax_DeclareFunctionAlias(SDL_HapticNumEffects_gurax, "SDL_HapticNumEffects")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticNumEffects_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	// Function body
	int rtn = SDL_HapticNumEffects(haptic);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticNumEffectsPlaying(haptic as SDL_Haptic)
Gurax_DeclareFunctionAlias(SDL_HapticNumEffectsPlaying_gurax, "SDL_HapticNumEffectsPlaying")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticNumEffectsPlaying_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	// Function body
	int rtn = SDL_HapticNumEffectsPlaying(haptic);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticQuery(haptic as SDL_Haptic)
Gurax_DeclareFunctionAlias(SDL_HapticQuery_gurax, "SDL_HapticQuery")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticQuery_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	// Function body
	unsigned int rtn = SDL_HapticQuery(haptic);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticNumAxes(haptic as SDL_Haptic)
Gurax_DeclareFunctionAlias(SDL_HapticNumAxes_gurax, "SDL_HapticNumAxes")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticNumAxes_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	// Function body
	int rtn = SDL_HapticNumAxes(haptic);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticEffectSupported(haptic as SDL_Haptic, effect as SDL_HapticEffect)
Gurax_DeclareFunctionAlias(SDL_HapticEffectSupported_gurax, "SDL_HapticEffectSupported")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
	DeclareArg("effect", VTYPE_SDL_HapticEffect, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticEffectSupported_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	auto& value_effect = args_gurax.Pick<Value_SDL_HapticEffect>();
	SDL_HapticEffect* effect = value_effect.GetEntityPtr();
	// Function body
	int rtn = SDL_HapticEffectSupported(haptic, effect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticNewEffect(haptic as SDL_Haptic, effect as SDL_HapticEffect)
Gurax_DeclareFunctionAlias(SDL_HapticNewEffect_gurax, "SDL_HapticNewEffect")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
	DeclareArg("effect", VTYPE_SDL_HapticEffect, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticNewEffect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	auto& value_effect = args_gurax.Pick<Value_SDL_HapticEffect>();
	SDL_HapticEffect* effect = value_effect.GetEntityPtr();
	// Function body
	int rtn = SDL_HapticNewEffect(haptic, effect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticUpdateEffect(haptic as SDL_Haptic, effect as Number, data as SDL_HapticEffect)
Gurax_DeclareFunctionAlias(SDL_HapticUpdateEffect_gurax, "SDL_HapticUpdateEffect")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
	DeclareArg("effect", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_SDL_HapticEffect, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticUpdateEffect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	int effect = args_gurax.PickNumber<int>();
	auto& value_data = args_gurax.Pick<Value_SDL_HapticEffect>();
	SDL_HapticEffect* data = value_data.GetEntityPtr();
	// Function body
	int rtn = SDL_HapticUpdateEffect(haptic, effect, data);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticRunEffect(haptic as SDL_Haptic, effect as Number, iterations as Number)
Gurax_DeclareFunctionAlias(SDL_HapticRunEffect_gurax, "SDL_HapticRunEffect")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
	DeclareArg("effect", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("iterations", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticRunEffect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	int effect = args_gurax.PickNumber<int>();
	Uint32 iterations = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_HapticRunEffect(haptic, effect, iterations);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticStopEffect(haptic as SDL_Haptic, effect as Number)
Gurax_DeclareFunctionAlias(SDL_HapticStopEffect_gurax, "SDL_HapticStopEffect")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
	DeclareArg("effect", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticStopEffect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	int effect = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_HapticStopEffect(haptic, effect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticDestroyEffect(haptic as SDL_Haptic, effect as Number)
Gurax_DeclareFunctionAlias(SDL_HapticDestroyEffect_gurax, "SDL_HapticDestroyEffect")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
	DeclareArg("effect", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticDestroyEffect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	int effect = args_gurax.PickNumber<int>();
	// Function body
	SDL_HapticDestroyEffect(haptic, effect);
	return Gurax::Value::nil();
}

// sdl.SDL_HapticGetEffectStatus(haptic as SDL_Haptic, effect as Number)
Gurax_DeclareFunctionAlias(SDL_HapticGetEffectStatus_gurax, "SDL_HapticGetEffectStatus")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
	DeclareArg("effect", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticGetEffectStatus_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	int effect = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_HapticGetEffectStatus(haptic, effect);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticSetGain(haptic as SDL_Haptic, gain as Number)
Gurax_DeclareFunctionAlias(SDL_HapticSetGain_gurax, "SDL_HapticSetGain")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
	DeclareArg("gain", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticSetGain_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	int gain = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_HapticSetGain(haptic, gain);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticSetAutocenter(haptic as SDL_Haptic, autocenter as Number)
Gurax_DeclareFunctionAlias(SDL_HapticSetAutocenter_gurax, "SDL_HapticSetAutocenter")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
	DeclareArg("autocenter", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticSetAutocenter_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	int autocenter = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_HapticSetAutocenter(haptic, autocenter);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticPause(haptic as SDL_Haptic)
Gurax_DeclareFunctionAlias(SDL_HapticPause_gurax, "SDL_HapticPause")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticPause_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	// Function body
	int rtn = SDL_HapticPause(haptic);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticUnpause(haptic as SDL_Haptic)
Gurax_DeclareFunctionAlias(SDL_HapticUnpause_gurax, "SDL_HapticUnpause")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticUnpause_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	// Function body
	int rtn = SDL_HapticUnpause(haptic);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticStopAll(haptic as SDL_Haptic)
Gurax_DeclareFunctionAlias(SDL_HapticStopAll_gurax, "SDL_HapticStopAll")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticStopAll_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	// Function body
	int rtn = SDL_HapticStopAll(haptic);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticRumbleSupported(haptic as SDL_Haptic)
Gurax_DeclareFunctionAlias(SDL_HapticRumbleSupported_gurax, "SDL_HapticRumbleSupported")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticRumbleSupported_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	// Function body
	int rtn = SDL_HapticRumbleSupported(haptic);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticRumbleInit(haptic as SDL_Haptic)
Gurax_DeclareFunctionAlias(SDL_HapticRumbleInit_gurax, "SDL_HapticRumbleInit")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticRumbleInit_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	// Function body
	int rtn = SDL_HapticRumbleInit(haptic);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticRumblePlay(haptic as SDL_Haptic, strength as Number, length as Number)
Gurax_DeclareFunctionAlias(SDL_HapticRumblePlay_gurax, "SDL_HapticRumblePlay")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
	DeclareArg("strength", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("length", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticRumblePlay_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	float strength = args_gurax.PickNumber<float>();
	Uint32 length = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_HapticRumblePlay(haptic, strength, length);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HapticRumbleStop(haptic as SDL_Haptic)
Gurax_DeclareFunctionAlias(SDL_HapticRumbleStop_gurax, "SDL_HapticRumbleStop")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("haptic", VTYPE_SDL_Haptic, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_HapticRumbleStop_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_haptic = args_gurax.Pick<Value_SDL_Haptic>();
	SDL_Haptic* haptic = value_haptic.GetEntityPtr();
	// Function body
	int rtn = SDL_HapticRumbleStop(haptic);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetNumAudioDrivers()
Gurax_DeclareFunctionAlias(SDL_GetNumAudioDrivers_gurax, "SDL_GetNumAudioDrivers")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetNumAudioDrivers_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_GetNumAudioDrivers();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetAudioDriver(index as Number)
Gurax_DeclareFunctionAlias(SDL_GetAudioDriver_gurax, "SDL_GetAudioDriver")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetAudioDriver_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	// Function body
	const char* rtn = SDL_GetAudioDriver(index);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_AUDIO_BITSIZE(format as Number)
Gurax_DeclareFunctionAlias(SDL_AUDIO_BITSIZE_gurax, "SDL_AUDIO_BITSIZE")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_AUDIO_BITSIZE_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_AudioFormat format = args_gurax.PickNumber<SDL_AudioFormat>();
	// Function body
	int rtn = SDL_AUDIO_BITSIZE(format);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_AudioInit(driver_name as String)
Gurax_DeclareFunctionAlias(SDL_AudioInit_gurax, "SDL_AudioInit")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("driver_name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_AudioInit_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* driver_name = args_gurax.PickString();
	// Function body
	int rtn = SDL_AudioInit(driver_name);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_AudioQuit()
Gurax_DeclareFunctionAlias(SDL_AudioQuit_gurax, "SDL_AudioQuit")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_AudioQuit_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_AudioQuit();
	return Gurax::Value::nil();
}

// sdl.SDL_GetCurrentAudioDriver()
Gurax_DeclareFunctionAlias(SDL_GetCurrentAudioDriver_gurax, "SDL_GetCurrentAudioDriver")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetCurrentAudioDriver_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const char* rtn = SDL_GetCurrentAudioDriver();
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_OpenAudio(desired as SDL_AudioSpec, obtained as SDL_AudioSpec)
Gurax_DeclareFunctionAlias(SDL_OpenAudio_gurax, "SDL_OpenAudio")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("desired", VTYPE_SDL_AudioSpec, ArgOccur::Once, ArgFlag::None);
	DeclareArg("obtained", VTYPE_SDL_AudioSpec, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_OpenAudio_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_desired = args_gurax.Pick<Value_SDL_AudioSpec>();
	SDL_AudioSpec* desired = value_desired.GetEntityPtr();
	auto& value_obtained = args_gurax.Pick<Value_SDL_AudioSpec>();
	SDL_AudioSpec* obtained = value_obtained.GetEntityPtr();
	// Function body
	int rtn = SDL_OpenAudio(desired, obtained);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetNumAudioDevices(iscapture as Bool)
Gurax_DeclareFunctionAlias(SDL_GetNumAudioDevices_gurax, "SDL_GetNumAudioDevices")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("iscapture", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetNumAudioDevices_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool iscapture = args_gurax.PickBool();
	// Function body
	int rtn = SDL_GetNumAudioDevices(iscapture);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetAudioDeviceName(index as Number, iscapture as Bool)
Gurax_DeclareFunctionAlias(SDL_GetAudioDeviceName_gurax, "SDL_GetAudioDeviceName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("iscapture", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetAudioDeviceName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	bool iscapture = args_gurax.PickBool();
	// Function body
	const char* rtn = SDL_GetAudioDeviceName(index, iscapture);
	return new Gurax::Value_String(rtn);
}

// sdl.SDL_OpenAudioDevice(device:nil as String, iscapture as Bool, desired as SDL_AudioSpec, obtained as SDL_AudioSpec, allowed_changes as Number)
Gurax_DeclareFunctionAlias(SDL_OpenAudioDevice_gurax, "SDL_OpenAudioDevice")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("device", VTYPE_String, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("iscapture", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("desired", VTYPE_SDL_AudioSpec, ArgOccur::Once, ArgFlag::None);
	DeclareArg("obtained", VTYPE_SDL_AudioSpec, ArgOccur::Once, ArgFlag::None);
	DeclareArg("allowed_changes", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_OpenAudioDevice_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* device = args_gurax.IsValid()? args_gurax.PickString() : nullptr;
	bool iscapture = args_gurax.PickBool();
	auto& value_desired = args_gurax.Pick<Value_SDL_AudioSpec>();
	const SDL_AudioSpec* desired = value_desired.GetEntityPtr();
	auto& value_obtained = args_gurax.Pick<Value_SDL_AudioSpec>();
	SDL_AudioSpec* obtained = value_obtained.GetEntityPtr();
	int allowed_changes = args_gurax.PickNumber<int>();
	// Function body
	value_obtained.SetFuncAudioCallback(Function::Reference(value_desired.GetFuncAudioCallback()));
	value_obtained.SetValueUserdata(value_desired.GetValueUserdata().Reference());
	SDL_AudioDeviceID rtn = SDL_OpenAudioDevice(device, iscapture, desired, obtained, allowed_changes);
	return new Value_Number(rtn);
}

// sdl.SDL_GetAudioStatus()
Gurax_DeclareFunctionAlias(SDL_GetAudioStatus_gurax, "SDL_GetAudioStatus")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetAudioStatus_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_AudioStatus rtn = SDL_GetAudioStatus();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetAudioDeviceStatus(dev as Number)
Gurax_DeclareFunctionAlias(SDL_GetAudioDeviceStatus_gurax, "SDL_GetAudioDeviceStatus")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dev", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetAudioDeviceStatus_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_AudioDeviceID dev = args_gurax.PickNumber<SDL_AudioDeviceID>();
	// Function body
	SDL_AudioStatus rtn = SDL_GetAudioDeviceStatus(dev);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_PauseAudio(pause_on as Bool)
Gurax_DeclareFunctionAlias(SDL_PauseAudio_gurax, "SDL_PauseAudio")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pause_on", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_PauseAudio_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool pause_on = args_gurax.PickBool();
	// Function body
	SDL_PauseAudio(pause_on);
	return Gurax::Value::nil();
}

// sdl.SDL_PauseAudioDevice(dev as Number, pause_on as Bool)
Gurax_DeclareFunctionAlias(SDL_PauseAudioDevice_gurax, "SDL_PauseAudioDevice")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dev", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pause_on", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_PauseAudioDevice_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_AudioDeviceID dev = args_gurax.PickNumber<SDL_AudioDeviceID>();
	bool pause_on = args_gurax.PickBool();
	// Function body
	SDL_PauseAudioDevice(dev, pause_on);
	return Gurax::Value::nil();
}

// sdl.SDL_BuildAudioCVT(cvt as SDL_AudioCVT, src_format as Number, src_channels as Number, src_rate as Number, dst_format as Number, dst_channels as Number, dst_rate as Number)
Gurax_DeclareFunctionAlias(SDL_BuildAudioCVT_gurax, "SDL_BuildAudioCVT")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cvt", VTYPE_SDL_AudioCVT, ArgOccur::Once, ArgFlag::None);
	DeclareArg("src_format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("src_channels", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("src_rate", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dst_format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dst_channels", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dst_rate", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_BuildAudioCVT_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cvt = args_gurax.Pick<Value_SDL_AudioCVT>();
	SDL_AudioCVT* cvt = value_cvt.GetEntityPtr();
	SDL_AudioFormat src_format = args_gurax.PickNumber<SDL_AudioFormat>();
	Uint8 src_channels = args_gurax.PickNumber<Uint8>();
	int src_rate = args_gurax.PickNumber<int>();
	SDL_AudioFormat dst_format = args_gurax.PickNumber<SDL_AudioFormat>();
	Uint8 dst_channels = args_gurax.PickNumber<Uint8>();
	int dst_rate = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_BuildAudioCVT(cvt, src_format, src_channels, src_rate, dst_format, dst_channels, dst_rate);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_ConvertAudio(cvt as SDL_AudioCVT)
Gurax_DeclareFunctionAlias(SDL_ConvertAudio_gurax, "SDL_ConvertAudio")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cvt", VTYPE_SDL_AudioCVT, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_ConvertAudio_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cvt = args_gurax.Pick<Value_SDL_AudioCVT>();
	SDL_AudioCVT* cvt = value_cvt.GetEntityPtr();
	// Function body
	int rtn = SDL_ConvertAudio(cvt);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_AudioStreamPut(stream as SDL_AudioStream, buf as Pointer, len as Number)
Gurax_DeclareFunctionAlias(SDL_AudioStreamPut_gurax, "SDL_AudioStreamPut")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("stream", VTYPE_SDL_AudioStream, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buf", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("len", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_AudioStreamPut_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_stream = args_gurax.Pick<Value_SDL_AudioStream>();
	SDL_AudioStream* stream = value_stream.GetEntityPtr();
	const void* buf = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<void>();
	int len = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_AudioStreamPut(stream, buf, len);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_AudioStreamGet(stream as SDL_AudioStream, buf as Pointer, len as Number)
Gurax_DeclareFunctionAlias(SDL_AudioStreamGet_gurax, "SDL_AudioStreamGet")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("stream", VTYPE_SDL_AudioStream, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buf", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("len", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_AudioStreamGet_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_stream = args_gurax.Pick<Value_SDL_AudioStream>();
	SDL_AudioStream* stream = value_stream.GetEntityPtr();
	void* buf = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!buf) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	int len = args_gurax.PickNumber<int>();
	// Function body
	int rtn = SDL_AudioStreamGet(stream, buf, len);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_AudioStreamAvailable(stream as SDL_AudioStream)
Gurax_DeclareFunctionAlias(SDL_AudioStreamAvailable_gurax, "SDL_AudioStreamAvailable")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("stream", VTYPE_SDL_AudioStream, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_AudioStreamAvailable_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_stream = args_gurax.Pick<Value_SDL_AudioStream>();
	SDL_AudioStream* stream = value_stream.GetEntityPtr();
	// Function body
	int rtn = SDL_AudioStreamAvailable(stream);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_AudioStreamFlush(stream as SDL_AudioStream)
Gurax_DeclareFunctionAlias(SDL_AudioStreamFlush_gurax, "SDL_AudioStreamFlush")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("stream", VTYPE_SDL_AudioStream, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_AudioStreamFlush_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_stream = args_gurax.Pick<Value_SDL_AudioStream>();
	SDL_AudioStream* stream = value_stream.GetEntityPtr();
	// Function body
	int rtn = SDL_AudioStreamFlush(stream);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_AudioStreamClear(stream as SDL_AudioStream)
Gurax_DeclareFunctionAlias(SDL_AudioStreamClear_gurax, "SDL_AudioStreamClear")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_SDL_AudioStream, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_AudioStreamClear_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_stream = args_gurax.Pick<Value_SDL_AudioStream>();
	SDL_AudioStream* stream = value_stream.GetEntityPtr();
	// Function body
	SDL_AudioStreamClear(stream);
	return Gurax::Value::nil();
}

// sdl.SDL_FreeAudioStream(stream:nil as SDL_AudioStream)
Gurax_DeclareFunctionAlias(SDL_FreeAudioStream_gurax, "SDL_FreeAudioStream")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_SDL_AudioStream, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_FreeAudioStream_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_AudioStream* stream = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_AudioStream>().GetEntityPtr() : nullptr;
	// Function body
	SDL_FreeAudioStream(stream);
	return Gurax::Value::nil();
}

// sdl.SDL_QueueAudio(dev as Number, data as Pointer, len as Number)
Gurax_DeclareFunctionAlias(SDL_QueueAudio_gurax, "SDL_QueueAudio")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dev", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("len", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_QueueAudio_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_AudioDeviceID dev = args_gurax.PickNumber<SDL_AudioDeviceID>();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<void>();
	Uint32 len = args_gurax.PickNumber<Uint32>();
	// Function body
	int rtn = SDL_QueueAudio(dev, data, len);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_DequeueAudio(dev as Number, data as Pointer, len as Number)
Gurax_DeclareFunctionAlias(SDL_DequeueAudio_gurax, "SDL_DequeueAudio")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dev", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("len", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_DequeueAudio_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_AudioDeviceID dev = args_gurax.PickNumber<SDL_AudioDeviceID>();
	void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!data) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	Uint32 len = args_gurax.PickNumber<Uint32>();
	// Function body
	Uint32 rtn = SDL_DequeueAudio(dev, data, len);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetQueuedAudioSize(dev as Number)
Gurax_DeclareFunctionAlias(SDL_GetQueuedAudioSize_gurax, "SDL_GetQueuedAudioSize")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dev", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_GetQueuedAudioSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_AudioDeviceID dev = args_gurax.PickNumber<SDL_AudioDeviceID>();
	// Function body
	Uint32 rtn = SDL_GetQueuedAudioSize(dev);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_ClearQueuedAudio(dev as Number)
Gurax_DeclareFunctionAlias(SDL_ClearQueuedAudio_gurax, "SDL_ClearQueuedAudio")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dev", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_ClearQueuedAudio_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_AudioDeviceID dev = args_gurax.PickNumber<SDL_AudioDeviceID>();
	// Function body
	SDL_ClearQueuedAudio(dev);
	return Gurax::Value::nil();
}

// sdl.SDL_LockAudio()
Gurax_DeclareFunctionAlias(SDL_LockAudio_gurax, "SDL_LockAudio")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_LockAudio_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_LockAudio();
	return Gurax::Value::nil();
}

// sdl.SDL_LockAudioDevice(dev as Number)
Gurax_DeclareFunctionAlias(SDL_LockAudioDevice_gurax, "SDL_LockAudioDevice")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dev", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_LockAudioDevice_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_AudioDeviceID dev = args_gurax.PickNumber<SDL_AudioDeviceID>();
	// Function body
	SDL_LockAudioDevice(dev);
	return Gurax::Value::nil();
}

// sdl.SDL_UnlockAudio()
Gurax_DeclareFunctionAlias(SDL_UnlockAudio_gurax, "SDL_UnlockAudio")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_UnlockAudio_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_UnlockAudio();
	return Gurax::Value::nil();
}

// sdl.SDL_UnlockAudioDevice(dev as Number)
Gurax_DeclareFunctionAlias(SDL_UnlockAudioDevice_gurax, "SDL_UnlockAudioDevice")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dev", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_UnlockAudioDevice_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_AudioDeviceID dev = args_gurax.PickNumber<SDL_AudioDeviceID>();
	// Function body
	SDL_UnlockAudioDevice(dev);
	return Gurax::Value::nil();
}

// sdl.SDL_CloseAudio()
Gurax_DeclareFunctionAlias(SDL_CloseAudio_gurax, "SDL_CloseAudio")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_CloseAudio_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_CloseAudio();
	return Gurax::Value::nil();
}

// sdl.SDL_CloseAudioDevice(dev as Number)
Gurax_DeclareFunctionAlias(SDL_CloseAudioDevice_gurax, "SDL_CloseAudioDevice")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dev", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_CloseAudioDevice_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_AudioDeviceID dev = args_gurax.PickNumber<SDL_AudioDeviceID>();
	// Function body
	SDL_CloseAudioDevice(dev);
	return Gurax::Value::nil();
}

// sdl.SDL_GetTicks()
Gurax_DeclareFunctionAlias(SDL_GetTicks_gurax, "SDL_GetTicks")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetTicks_gurax, processor_gurax, argument_gurax)
{
	// Function body
	Uint32 rtn = SDL_GetTicks();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetPerformanceCounter()
Gurax_DeclareFunctionAlias(SDL_GetPerformanceCounter_gurax, "SDL_GetPerformanceCounter")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetPerformanceCounter_gurax, processor_gurax, argument_gurax)
{
	// Function body
	Uint64 rtn = SDL_GetPerformanceCounter();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetPerformanceFrequency()
Gurax_DeclareFunctionAlias(SDL_GetPerformanceFrequency_gurax, "SDL_GetPerformanceFrequency")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetPerformanceFrequency_gurax, processor_gurax, argument_gurax)
{
	// Function body
	Uint64 rtn = SDL_GetPerformanceFrequency();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_Delay(ms as Number)
Gurax_DeclareFunctionAlias(SDL_Delay_gurax, "SDL_Delay")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("ms", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_Delay_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Uint32 ms = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_Delay(ms);
	return Gurax::Value::nil();
}

// sdl.SDL_RemoveTimer(id as Number)
Gurax_DeclareFunctionAlias(SDL_RemoveTimer_gurax, "SDL_RemoveTimer")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RemoveTimer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_TimerID id = args_gurax.PickNumber<SDL_TimerID>();
	// Function body
	SDL_bool rtn = SDL_RemoveTimer(id);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_RWFromFile(file as String, mode as String)
Gurax_DeclareFunctionAlias(SDL_RWFromFile_gurax, "SDL_RWFromFile")
{
	Declare(VTYPE_SDL_RWops, Flag::None);
	DeclareArg("file", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RWFromFile_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* file = args_gurax.PickString();
	const char* mode = args_gurax.PickString();
	// Function body
	SDL_RWops* rtn = SDL_RWFromFile(file, mode);
	if (!rtn) return Value::nil();
	return new Value_SDL_RWops(rtn);
}

// sdl.SDL_RWFromConstMem(mem as Pointer, size as Number)
Gurax_DeclareFunctionAlias(SDL_RWFromConstMem_gurax, "SDL_RWFromConstMem")
{
	Declare(VTYPE_SDL_RWops, Flag::None);
	DeclareArg("mem", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RWFromConstMem_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const void* mem = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<void>();
	int size = args_gurax.PickNumber<int>();
	// Function body
	SDL_RWops* rtn = SDL_RWFromConstMem(mem, size);
	if (!rtn) return Value::nil();
	return new Value_SDL_RWops(rtn);
}

// sdl.SDL_AllocRW()
Gurax_DeclareFunctionAlias(SDL_AllocRW_gurax, "SDL_AllocRW")
{
	Declare(VTYPE_SDL_RWops, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_AllocRW_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_RWops* rtn = SDL_AllocRW();
	if (!rtn) return Value::nil();
	return new Value_SDL_RWops(rtn);
}

// sdl.SDL_FreeRW(area:nil as SDL_RWops)
Gurax_DeclareFunctionAlias(SDL_FreeRW_gurax, "SDL_FreeRW")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("area", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_FreeRW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	SDL_RWops* area = args_gurax.IsValid()? args_gurax.Pick<Value_SDL_RWops>().GetEntityPtr() : nullptr;
	// Function body
	SDL_FreeRW(area);
	return Gurax::Value::nil();
}

// sdl.SDL_RWsize(context as SDL_RWops)
Gurax_DeclareFunctionAlias(SDL_RWsize_gurax, "SDL_RWsize")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("context", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RWsize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_context = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* context = value_context.GetEntityPtr();
	// Function body
	Sint64 rtn = SDL_RWsize(context);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RWseek(context as SDL_RWops, offset as Number, whence as Number)
Gurax_DeclareFunctionAlias(SDL_RWseek_gurax, "SDL_RWseek")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("context", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("whence", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RWseek_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_context = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* context = value_context.GetEntityPtr();
	Sint64 offset = args_gurax.PickNumber<Sint64>();
	int whence = args_gurax.PickNumber<int>();
	// Function body
	Sint64 rtn = SDL_RWseek(context, offset, whence);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RWtell(context as SDL_RWops)
Gurax_DeclareFunctionAlias(SDL_RWtell_gurax, "SDL_RWtell")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("context", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RWtell_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_context = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* context = value_context.GetEntityPtr();
	// Function body
	Sint64 rtn = SDL_RWtell(context);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RWread(context as SDL_RWops, ptr as Pointer, size as Number, maxnum as Number)
Gurax_DeclareFunctionAlias(SDL_RWread_gurax, "SDL_RWread")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("context", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ptr", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxnum", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RWread_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_context = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* context = value_context.GetEntityPtr();
	void* ptr = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!ptr) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	size_t size = args_gurax.PickNumber<size_t>();
	size_t maxnum = args_gurax.PickNumber<size_t>();
	// Function body
	size_t rtn = SDL_RWread(context, ptr, size, maxnum);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RWwrite(context as SDL_RWops, ptr as Pointer, size as Number, num as Number)
Gurax_DeclareFunctionAlias(SDL_RWwrite_gurax, "SDL_RWwrite")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("context", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ptr", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RWwrite_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_context = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* context = value_context.GetEntityPtr();
	const void* ptr = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<void>();
	size_t size = args_gurax.PickNumber<size_t>();
	size_t num = args_gurax.PickNumber<size_t>();
	// Function body
	size_t rtn = SDL_RWwrite(context, ptr, size, num);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_RWclose(context as SDL_RWops)
Gurax_DeclareFunctionAlias(SDL_RWclose_gurax, "SDL_RWclose")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("context", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_RWclose_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_context = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* context = value_context.GetEntityPtr();
	// Function body
	int rtn = SDL_RWclose(context);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_ReadU8(src as SDL_RWops)
Gurax_DeclareFunctionAlias(SDL_ReadU8_gurax, "SDL_ReadU8")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_ReadU8_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	Uint8 rtn = SDL_ReadU8(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_ReadLE16(src as SDL_RWops)
Gurax_DeclareFunctionAlias(SDL_ReadLE16_gurax, "SDL_ReadLE16")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_ReadLE16_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	Uint16 rtn = SDL_ReadLE16(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_ReadBE16(src as SDL_RWops)
Gurax_DeclareFunctionAlias(SDL_ReadBE16_gurax, "SDL_ReadBE16")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_ReadBE16_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	Uint16 rtn = SDL_ReadBE16(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_ReadLE32(src as SDL_RWops)
Gurax_DeclareFunctionAlias(SDL_ReadLE32_gurax, "SDL_ReadLE32")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_ReadLE32_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	Uint32 rtn = SDL_ReadLE32(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_ReadBE32(src as SDL_RWops)
Gurax_DeclareFunctionAlias(SDL_ReadBE32_gurax, "SDL_ReadBE32")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_ReadBE32_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	Uint32 rtn = SDL_ReadBE32(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_ReadLE64(src as SDL_RWops)
Gurax_DeclareFunctionAlias(SDL_ReadLE64_gurax, "SDL_ReadLE64")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_ReadLE64_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	Uint64 rtn = SDL_ReadLE64(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_ReadBE64(src as SDL_RWops)
Gurax_DeclareFunctionAlias(SDL_ReadBE64_gurax, "SDL_ReadBE64")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_ReadBE64_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	Uint64 rtn = SDL_ReadBE64(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_WriteU8(dst as SDL_RWops, value as Number)
Gurax_DeclareFunctionAlias(SDL_WriteU8_gurax, "SDL_WriteU8")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_WriteU8_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* dst = value_dst.GetEntityPtr();
	Uint8 value = args_gurax.PickNumber<Uint8>();
	// Function body
	size_t rtn = SDL_WriteU8(dst, value);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_WriteLE16(dst as SDL_RWops, value as Number)
Gurax_DeclareFunctionAlias(SDL_WriteLE16_gurax, "SDL_WriteLE16")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_WriteLE16_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* dst = value_dst.GetEntityPtr();
	Uint16 value = args_gurax.PickNumber<Uint16>();
	// Function body
	size_t rtn = SDL_WriteLE16(dst, value);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_WriteBE16(dst as SDL_RWops, value as Number)
Gurax_DeclareFunctionAlias(SDL_WriteBE16_gurax, "SDL_WriteBE16")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_WriteBE16_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* dst = value_dst.GetEntityPtr();
	Uint16 value = args_gurax.PickNumber<Uint16>();
	// Function body
	size_t rtn = SDL_WriteBE16(dst, value);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_WriteLE32(dst as SDL_RWops, value as Number)
Gurax_DeclareFunctionAlias(SDL_WriteLE32_gurax, "SDL_WriteLE32")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_WriteLE32_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* dst = value_dst.GetEntityPtr();
	Uint32 value = args_gurax.PickNumber<Uint32>();
	// Function body
	size_t rtn = SDL_WriteLE32(dst, value);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_WriteBE32(dst as SDL_RWops, value as Number)
Gurax_DeclareFunctionAlias(SDL_WriteBE32_gurax, "SDL_WriteBE32")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_WriteBE32_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* dst = value_dst.GetEntityPtr();
	Uint32 value = args_gurax.PickNumber<Uint32>();
	// Function body
	size_t rtn = SDL_WriteBE32(dst, value);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_WriteLE64(dst as SDL_RWops, value as Number)
Gurax_DeclareFunctionAlias(SDL_WriteLE64_gurax, "SDL_WriteLE64")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_WriteLE64_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* dst = value_dst.GetEntityPtr();
	Uint64 value = args_gurax.PickNumber<Uint64>();
	// Function body
	size_t rtn = SDL_WriteLE64(dst, value);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_WriteBE64(dst as SDL_RWops, value as Number)
Gurax_DeclareFunctionAlias(SDL_WriteBE64_gurax, "SDL_WriteBE64")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SDL_WriteBE64_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* dst = value_dst.GetEntityPtr();
	Uint64 value = args_gurax.PickNumber<Uint64>();
	// Function body
	size_t rtn = SDL_WriteBE64(dst, value);
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetCPUCount()
Gurax_DeclareFunctionAlias(SDL_GetCPUCount_gurax, "SDL_GetCPUCount")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetCPUCount_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_GetCPUCount();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_GetCPUCacheLineSize()
Gurax_DeclareFunctionAlias(SDL_GetCPUCacheLineSize_gurax, "SDL_GetCPUCacheLineSize")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetCPUCacheLineSize_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_GetCPUCacheLineSize();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_HasRDTSC()
Gurax_DeclareFunctionAlias(SDL_HasRDTSC_gurax, "SDL_HasRDTSC")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_HasRDTSC_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_HasRDTSC();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_HasAltiVec()
Gurax_DeclareFunctionAlias(SDL_HasAltiVec_gurax, "SDL_HasAltiVec")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_HasAltiVec_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_HasAltiVec();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_HasMMX()
Gurax_DeclareFunctionAlias(SDL_HasMMX_gurax, "SDL_HasMMX")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_HasMMX_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_HasMMX();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_Has3DNow()
Gurax_DeclareFunctionAlias(SDL_Has3DNow_gurax, "SDL_Has3DNow")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_Has3DNow_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_Has3DNow();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_HasSSE()
Gurax_DeclareFunctionAlias(SDL_HasSSE_gurax, "SDL_HasSSE")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_HasSSE_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_HasSSE();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_HasSSE2()
Gurax_DeclareFunctionAlias(SDL_HasSSE2_gurax, "SDL_HasSSE2")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_HasSSE2_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_HasSSE2();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_HasSSE3()
Gurax_DeclareFunctionAlias(SDL_HasSSE3_gurax, "SDL_HasSSE3")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_HasSSE3_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_HasSSE3();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_HasSSE41()
Gurax_DeclareFunctionAlias(SDL_HasSSE41_gurax, "SDL_HasSSE41")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_HasSSE41_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_HasSSE41();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_HasSSE42()
Gurax_DeclareFunctionAlias(SDL_HasSSE42_gurax, "SDL_HasSSE42")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_HasSSE42_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_HasSSE42();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_HasAVX()
Gurax_DeclareFunctionAlias(SDL_HasAVX_gurax, "SDL_HasAVX")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_HasAVX_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_HasAVX();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_HasAVX2()
Gurax_DeclareFunctionAlias(SDL_HasAVX2_gurax, "SDL_HasAVX2")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_HasAVX2_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_HasAVX2();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_HasAVX512F()
Gurax_DeclareFunctionAlias(SDL_HasAVX512F_gurax, "SDL_HasAVX512F")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_HasAVX512F_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_HasAVX512F();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_HasARMSIMD()
Gurax_DeclareFunctionAlias(SDL_HasARMSIMD_gurax, "SDL_HasARMSIMD")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_HasARMSIMD_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_HasARMSIMD();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_HasNEON()
Gurax_DeclareFunctionAlias(SDL_HasNEON_gurax, "SDL_HasNEON")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_HasNEON_gurax, processor_gurax, argument_gurax)
{
	// Function body
	SDL_bool rtn = SDL_HasNEON();
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.SDL_GetSystemRAM()
Gurax_DeclareFunctionAlias(SDL_GetSystemRAM_gurax, "SDL_GetSystemRAM")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_GetSystemRAM_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = SDL_GetSystemRAM();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SIMDGetAlignment()
Gurax_DeclareFunctionAlias(SDL_SIMDGetAlignment_gurax, "SDL_SIMDGetAlignment")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(SDL_SIMDGetAlignment_gurax, processor_gurax, argument_gurax)
{
	// Function body
	size_t rtn = SDL_SIMDGetAlignment();
	return new Gurax::Value_Number(rtn);
}

// sdl.SDL_SIMDFree(ptr:nil as Pointer)
Gurax_DeclareFunctionAlias(SDL_SIMDFree_gurax, "SDL_SIMDFree")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("ptr", VTYPE_Pointer, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(SDL_SIMDFree_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	void* ptr = args_gurax.IsValid()? args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<void>() : nullptr;
	// Function body
	SDL_SIMDFree(ptr);
	return Gurax::Value::nil();
}

// sdl.SDL_GetPowerInfo(&secs:nilRef as Number, &pct:nilRef as Number)
Gurax_DeclareFunctionAlias(SDL_GetPowerInfo_gurax, "SDL_GetPowerInfo")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("secs", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("pct", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementFunctionEx(SDL_GetPowerInfo_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Referencer> secs(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> pct(args_gurax.PickReferencer().Reference());
	// Function body
	int secs_, pct_;
	SDL_PowerState state = SDL_GetPowerInfo(&secs_, &pct_);
	secs->SetValue(new Value_Number(secs_));
	pct->SetValue(new Value_Number(pct_));
	return new Value_Number(state);
}

// sdl.IMG_Linked_Version()
Gurax_DeclareFunctionAlias(IMG_Linked_Version_gurax, "IMG_Linked_Version")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementFunctionEx(IMG_Linked_Version_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const SDL_version* ver = IMG_Linked_Version();
	return new Value_SDL_version(*ver);
}

// sdl.IMG_Init(flags as Number)
Gurax_DeclareFunctionAlias(IMG_Init_gurax, "IMG_Init")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_Init_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int flags = args_gurax.PickNumber<int>();
	// Function body
	int rtn = IMG_Init(flags);
	return new Value_Number(rtn);
}

// sdl.IMG_Quit()
Gurax_DeclareFunctionAlias(IMG_Quit_gurax, "IMG_Quit")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(IMG_Quit_gurax, processor_gurax, argument_gurax)
{
	// Function body
	IMG_Quit();
	return Gurax::Value::nil();
}

// sdl.IMG_GetError()
Gurax_DeclareFunctionAlias(IMG_GetError_gurax, "IMG_GetError")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementFunctionEx(IMG_GetError_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const char* rtn = IMG_GetError();
	return new Gurax::Value_String(rtn);
}

// sdl.IMG_Load(file as String)
Gurax_DeclareFunctionAlias(IMG_Load_gurax, "IMG_Load")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("file", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_Load_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* file = args_gurax.PickString();
	// Function body
	SDL_Surface* rtn = IMG_Load(file);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_Load_RW(src as SDL_RWops, freesrc as Number)
Gurax_DeclareFunctionAlias(IMG_Load_RW_gurax, "IMG_Load_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("freesrc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_Load_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	int freesrc = args_gurax.PickNumber<int>();
	// Function body
	SDL_Surface* rtn = IMG_Load_RW(src, freesrc);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_LoadTyped_RW(src as SDL_RWops, freesrc as Number, type as String)
Gurax_DeclareFunctionAlias(IMG_LoadTyped_RW_gurax, "IMG_LoadTyped_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("freesrc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_LoadTyped_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	int freesrc = args_gurax.PickNumber<int>();
	const char* type = args_gurax.PickString();
	// Function body
	SDL_Surface* rtn = IMG_LoadTyped_RW(src, freesrc, type);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_LoadCUR_RW(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_LoadCUR_RW_gurax, "IMG_LoadCUR_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_LoadCUR_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	SDL_Surface* rtn = IMG_LoadCUR_RW(src);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_LoadICO_RW(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_LoadICO_RW_gurax, "IMG_LoadICO_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_LoadICO_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	SDL_Surface* rtn = IMG_LoadICO_RW(src);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_LoadBMP_RW(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_LoadBMP_RW_gurax, "IMG_LoadBMP_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_LoadBMP_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	SDL_Surface* rtn = IMG_LoadBMP_RW(src);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_LoadPNM_RW(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_LoadPNM_RW_gurax, "IMG_LoadPNM_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_LoadPNM_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	SDL_Surface* rtn = IMG_LoadPNM_RW(src);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_LoadXPM_RW(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_LoadXPM_RW_gurax, "IMG_LoadXPM_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_LoadXPM_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	SDL_Surface* rtn = IMG_LoadXPM_RW(src);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_LoadXCF_RW(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_LoadXCF_RW_gurax, "IMG_LoadXCF_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_LoadXCF_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	SDL_Surface* rtn = IMG_LoadXCF_RW(src);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_LoadPCX_RW(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_LoadPCX_RW_gurax, "IMG_LoadPCX_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_LoadPCX_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	SDL_Surface* rtn = IMG_LoadPCX_RW(src);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_LoadGIF_RW(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_LoadGIF_RW_gurax, "IMG_LoadGIF_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_LoadGIF_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	SDL_Surface* rtn = IMG_LoadGIF_RW(src);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_LoadJPG_RW(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_LoadJPG_RW_gurax, "IMG_LoadJPG_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_LoadJPG_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	SDL_Surface* rtn = IMG_LoadJPG_RW(src);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_LoadTIF_RW(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_LoadTIF_RW_gurax, "IMG_LoadTIF_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_LoadTIF_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	SDL_Surface* rtn = IMG_LoadTIF_RW(src);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_LoadPNG_RW(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_LoadPNG_RW_gurax, "IMG_LoadPNG_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_LoadPNG_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	SDL_Surface* rtn = IMG_LoadPNG_RW(src);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_LoadTGA_RW(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_LoadTGA_RW_gurax, "IMG_LoadTGA_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_LoadTGA_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	SDL_Surface* rtn = IMG_LoadTGA_RW(src);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_LoadLBM_RW(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_LoadLBM_RW_gurax, "IMG_LoadLBM_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_LoadLBM_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	SDL_Surface* rtn = IMG_LoadLBM_RW(src);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_LoadXV_RW(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_LoadXV_RW_gurax, "IMG_LoadXV_RW")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_LoadXV_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	SDL_Surface* rtn = IMG_LoadXV_RW(src);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.IMG_isCUR(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_isCUR_gurax, "IMG_isCUR")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_isCUR_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	int rtn = IMG_isCUR(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.IMG_isICO(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_isICO_gurax, "IMG_isICO")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_isICO_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	int rtn = IMG_isICO(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.IMG_isBMP(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_isBMP_gurax, "IMG_isBMP")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_isBMP_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	int rtn = IMG_isBMP(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.IMG_isPNM(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_isPNM_gurax, "IMG_isPNM")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_isPNM_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	int rtn = IMG_isPNM(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.IMG_isXPM(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_isXPM_gurax, "IMG_isXPM")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_isXPM_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	int rtn = IMG_isXPM(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.IMG_isXCF(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_isXCF_gurax, "IMG_isXCF")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_isXCF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	int rtn = IMG_isXCF(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.IMG_isPCX(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_isPCX_gurax, "IMG_isPCX")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_isPCX_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	int rtn = IMG_isPCX(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.IMG_isGIF(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_isGIF_gurax, "IMG_isGIF")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_isGIF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	int rtn = IMG_isGIF(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.IMG_isJPG(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_isJPG_gurax, "IMG_isJPG")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_isJPG_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	int rtn = IMG_isJPG(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.IMG_isTIF(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_isTIF_gurax, "IMG_isTIF")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_isTIF_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	int rtn = IMG_isTIF(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.IMG_isPNG(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_isPNG_gurax, "IMG_isPNG")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_isPNG_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	int rtn = IMG_isPNG(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.IMG_isLBM(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_isLBM_gurax, "IMG_isLBM")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_isLBM_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	int rtn = IMG_isLBM(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.IMG_isXV(src as SDL_RWops)
Gurax_DeclareFunctionAlias(IMG_isXV_gurax, "IMG_isXV")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(IMG_isXV_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	// Function body
	int rtn = IMG_isXV(src);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_Linked_Version()
Gurax_DeclareFunctionAlias(Mix_Linked_Version_gurax, "Mix_Linked_Version")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementFunctionEx(Mix_Linked_Version_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const SDL_version* ver = Mix_Linked_Version();
	return new Value_SDL_version(*ver);
}

// sdl.Mix_Init(flags as Number)
Gurax_DeclareFunctionAlias(Mix_Init_gurax, "Mix_Init")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_Init_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int flags = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_Init(flags);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_Quit()
Gurax_DeclareFunctionAlias(Mix_Quit_gurax, "Mix_Quit")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(Mix_Quit_gurax, processor_gurax, argument_gurax)
{
	// Function body
	Mix_Quit();
	return Gurax::Value::nil();
}

// sdl.Mix_OpenAudio(frequency as Number, format as Number, channels as Number, chunksize as Number)
Gurax_DeclareFunctionAlias(Mix_OpenAudio_gurax, "Mix_OpenAudio")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("frequency", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("channels", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("chunksize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_OpenAudio_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int frequency = args_gurax.PickNumber<int>();
	Uint16 format = args_gurax.PickNumber<Uint16>();
	int channels = args_gurax.PickNumber<int>();
	int chunksize = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_OpenAudio(frequency, format, channels, chunksize);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_OpenAudioDevice(frequency as Number, format as Number, channels as Number, chunksize as Number, device as String, allowed_changes as Number)
Gurax_DeclareFunctionAlias(Mix_OpenAudioDevice_gurax, "Mix_OpenAudioDevice")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("frequency", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("channels", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("chunksize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("device", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("allowed_changes", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_OpenAudioDevice_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int frequency = args_gurax.PickNumber<int>();
	Uint16 format = args_gurax.PickNumber<Uint16>();
	int channels = args_gurax.PickNumber<int>();
	int chunksize = args_gurax.PickNumber<int>();
	const char* device = args_gurax.PickString();
	int allowed_changes = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_OpenAudioDevice(frequency, format, channels, chunksize, device, allowed_changes);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_AllocateChannels(numchans as Number)
Gurax_DeclareFunctionAlias(Mix_AllocateChannels_gurax, "Mix_AllocateChannels")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("numchans", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_AllocateChannels_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int numchans = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_AllocateChannels(numchans);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_GetError()
Gurax_DeclareFunctionAlias(Mix_GetError_gurax, "Mix_GetError")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementFunctionEx(Mix_GetError_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const char* rtn = Mix_GetError();
	return new Gurax::Value_String(rtn);
}

// sdl.Mix_QuerySpec()
Gurax_DeclareFunctionAlias(Mix_QuerySpec_gurax, "Mix_QuerySpec")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementFunctionEx(Mix_QuerySpec_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int frequency;
	Uint16 format;
	int channels;
	if (Mix_QuerySpec(&frequency, &format, &channels) == 0) {
		return Value::nil();
	}
	return Value_Tuple::Create(new Value_Number(frequency),
					new Value_Number(format), new Value_Number(channels));
}

// sdl.Mix_LoadWAV(file as String)
Gurax_DeclareFunctionAlias(Mix_LoadWAV_gurax, "Mix_LoadWAV")
{
	Declare(VTYPE_Mix_Chunk, Flag::None);
	DeclareArg("file", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_LoadWAV_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* file = args_gurax.PickString();
	// Function body
	Mix_Chunk* rtn = Mix_LoadWAV(file);
	if (!rtn) return Value::nil();
	return new Value_Mix_Chunk(rtn);
}

// sdl.Mix_LoadWAV_RW(src as SDL_RWops, freesrc as Number)
Gurax_DeclareFunctionAlias(Mix_LoadWAV_RW_gurax, "Mix_LoadWAV_RW")
{
	Declare(VTYPE_Mix_Chunk, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("freesrc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_LoadWAV_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	int freesrc = args_gurax.PickNumber<int>();
	// Function body
	Mix_Chunk* rtn = Mix_LoadWAV_RW(src, freesrc);
	if (!rtn) return Value::nil();
	return new Value_Mix_Chunk(rtn);
}

// sdl.Mix_LoadMUS(file as String)
Gurax_DeclareFunctionAlias(Mix_LoadMUS_gurax, "Mix_LoadMUS")
{
	Declare(VTYPE_Mix_Music, Flag::None);
	DeclareArg("file", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_LoadMUS_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* file = args_gurax.PickString();
	// Function body
	Mix_Music* rtn = Mix_LoadMUS(file);
	if (!rtn) return Value::nil();
	return new Value_Mix_Music(rtn);
}

// sdl.Mix_LoadMUS_RW(src as SDL_RWops, freesrc as Number)
Gurax_DeclareFunctionAlias(Mix_LoadMUS_RW_gurax, "Mix_LoadMUS_RW")
{
	Declare(VTYPE_Mix_Music, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("freesrc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_LoadMUS_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	int freesrc = args_gurax.PickNumber<int>();
	// Function body
	Mix_Music* rtn = Mix_LoadMUS_RW(src, freesrc);
	if (!rtn) return Value::nil();
	return new Value_Mix_Music(rtn);
}

// sdl.Mix_LoadMUSType_RW(src as SDL_RWops, type as Number, freesrc as Number)
Gurax_DeclareFunctionAlias(Mix_LoadMUSType_RW_gurax, "Mix_LoadMUSType_RW")
{
	Declare(VTYPE_Mix_Music, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("freesrc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_LoadMUSType_RW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	Mix_MusicType type = args_gurax.PickNumber<Mix_MusicType>();
	int freesrc = args_gurax.PickNumber<int>();
	// Function body
	Mix_Music* rtn = Mix_LoadMUSType_RW(src, type, freesrc);
	if (!rtn) return Value::nil();
	return new Value_Mix_Music(rtn);
}

// sdl.Mix_FreeChunk(chunk:nil as Mix_Chunk)
Gurax_DeclareFunctionAlias(Mix_FreeChunk_gurax, "Mix_FreeChunk")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("chunk", VTYPE_Mix_Chunk, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(Mix_FreeChunk_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Mix_Chunk* chunk = args_gurax.IsValid()? args_gurax.Pick<Value_Mix_Chunk>().GetEntityPtr() : nullptr;
	// Function body
	Mix_FreeChunk(chunk);
	return Gurax::Value::nil();
}

// sdl.Mix_FreeMusic(music:nil as Mix_Music)
Gurax_DeclareFunctionAlias(Mix_FreeMusic_gurax, "Mix_FreeMusic")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("music", VTYPE_Mix_Music, ArgOccur::Once, ArgFlag::Nil);
}

Gurax_ImplementFunctionEx(Mix_FreeMusic_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Mix_Music* music = args_gurax.IsValid()? args_gurax.Pick<Value_Mix_Music>().GetEntityPtr() : nullptr;
	// Function body
	Mix_FreeMusic(music);
	return Gurax::Value::nil();
}

// sdl.Mix_GetNumChunkDecoders()
Gurax_DeclareFunctionAlias(Mix_GetNumChunkDecoders_gurax, "Mix_GetNumChunkDecoders")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(Mix_GetNumChunkDecoders_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = Mix_GetNumChunkDecoders();
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_GetChunkDecoder(index as Number)
Gurax_DeclareFunctionAlias(Mix_GetChunkDecoder_gurax, "Mix_GetChunkDecoder")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_GetChunkDecoder_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	// Function body
	const char* rtn = Mix_GetChunkDecoder(index);
	return new Gurax::Value_String(rtn);
}

// sdl.Mix_HasChunkDecoder(name as String)
Gurax_DeclareFunctionAlias(Mix_HasChunkDecoder_gurax, "Mix_HasChunkDecoder")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_HasChunkDecoder_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	// Function body
	SDL_bool rtn = Mix_HasChunkDecoder(name);
	return new Gurax::Value_Bool(!!rtn);
}

// sdl.Mix_GetNumMusicDecoders()
Gurax_DeclareFunctionAlias(Mix_GetNumMusicDecoders_gurax, "Mix_GetNumMusicDecoders")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(Mix_GetNumMusicDecoders_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = Mix_GetNumMusicDecoders();
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_GetMusicDecoder(index as Number)
Gurax_DeclareFunctionAlias(Mix_GetMusicDecoder_gurax, "Mix_GetMusicDecoder")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_GetMusicDecoder_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	// Function body
	const char* rtn = Mix_GetMusicDecoder(index);
	return new Gurax::Value_String(rtn);
}

// sdl.Mix_GetMusicType(music as Mix_Music)
Gurax_DeclareFunctionAlias(Mix_GetMusicType_gurax, "Mix_GetMusicType")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("music", VTYPE_Mix_Music, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_GetMusicType_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_music = args_gurax.Pick<Value_Mix_Music>();
	const Mix_Music* music = value_music.GetEntityPtr();
	// Function body
	Mix_MusicType rtn = Mix_GetMusicType(music);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_UnregisterAllEffects(channel as Number)
Gurax_DeclareFunctionAlias(Mix_UnregisterAllEffects_gurax, "Mix_UnregisterAllEffects")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("channel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_UnregisterAllEffects_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int channel = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_UnregisterAllEffects(channel);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_SetPanning(channel as Number, left as Number, right as Number)
Gurax_DeclareFunctionAlias(Mix_SetPanning_gurax, "Mix_SetPanning")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("channel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("left", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("right", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_SetPanning_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int channel = args_gurax.PickNumber<int>();
	Uint8 left = args_gurax.PickNumber<Uint8>();
	Uint8 right = args_gurax.PickNumber<Uint8>();
	// Function body
	int rtn = Mix_SetPanning(channel, left, right);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_SetPosition(channel as Number, angle as Number, distance as Number)
Gurax_DeclareFunctionAlias(Mix_SetPosition_gurax, "Mix_SetPosition")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("channel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("angle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("distance", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_SetPosition_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int channel = args_gurax.PickNumber<int>();
	Sint16 angle = args_gurax.PickNumber<Sint16>();
	Uint8 distance = args_gurax.PickNumber<Uint8>();
	// Function body
	int rtn = Mix_SetPosition(channel, angle, distance);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_SetDistance(channel as Number, distance as Number)
Gurax_DeclareFunctionAlias(Mix_SetDistance_gurax, "Mix_SetDistance")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("channel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("distance", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_SetDistance_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int channel = args_gurax.PickNumber<int>();
	Uint8 distance = args_gurax.PickNumber<Uint8>();
	// Function body
	int rtn = Mix_SetDistance(channel, distance);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_SetReverseStereo(channel as Number, flip as Number)
Gurax_DeclareFunctionAlias(Mix_SetReverseStereo_gurax, "Mix_SetReverseStereo")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("channel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flip", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_SetReverseStereo_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int channel = args_gurax.PickNumber<int>();
	int flip = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_SetReverseStereo(channel, flip);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_ReserveChannels(num as Number)
Gurax_DeclareFunctionAlias(Mix_ReserveChannels_gurax, "Mix_ReserveChannels")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_ReserveChannels_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int num = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_ReserveChannels(num);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_GroupChannel(which as Number, tag as Number)
Gurax_DeclareFunctionAlias(Mix_GroupChannel_gurax, "Mix_GroupChannel")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("which", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("tag", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_GroupChannel_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int which = args_gurax.PickNumber<int>();
	int tag = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_GroupChannel(which, tag);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_GroupChannels(from as Number, to as Number, tag as Number)
Gurax_DeclareFunctionAlias(Mix_GroupChannels_gurax, "Mix_GroupChannels")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("from", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("to", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("tag", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_GroupChannels_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int from = args_gurax.PickNumber<int>();
	int to = args_gurax.PickNumber<int>();
	int tag = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_GroupChannels(from, to, tag);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_GroupAvailable(tag as Number)
Gurax_DeclareFunctionAlias(Mix_GroupAvailable_gurax, "Mix_GroupAvailable")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("tag", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_GroupAvailable_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int tag = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_GroupAvailable(tag);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_GroupCount(tag as Number)
Gurax_DeclareFunctionAlias(Mix_GroupCount_gurax, "Mix_GroupCount")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("tag", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_GroupCount_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int tag = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_GroupCount(tag);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_GroupOldest(tag as Number)
Gurax_DeclareFunctionAlias(Mix_GroupOldest_gurax, "Mix_GroupOldest")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("tag", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_GroupOldest_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int tag = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_GroupOldest(tag);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_GroupNewer(tag as Number)
Gurax_DeclareFunctionAlias(Mix_GroupNewer_gurax, "Mix_GroupNewer")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("tag", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_GroupNewer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int tag = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_GroupNewer(tag);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_PlayChannel(channel as Number, chunk as Mix_Chunk, loops as Number)
Gurax_DeclareFunctionAlias(Mix_PlayChannel_gurax, "Mix_PlayChannel")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("channel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("chunk", VTYPE_Mix_Chunk, ArgOccur::Once, ArgFlag::None);
	DeclareArg("loops", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_PlayChannel_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int channel = args_gurax.PickNumber<int>();
	auto& value_chunk = args_gurax.Pick<Value_Mix_Chunk>();
	Mix_Chunk* chunk = value_chunk.GetEntityPtr();
	int loops = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_PlayChannel(channel, chunk, loops);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_PlayChannelTimed(channel as Number, chunk as Mix_Chunk, loops as Number, ticks as Number)
Gurax_DeclareFunctionAlias(Mix_PlayChannelTimed_gurax, "Mix_PlayChannelTimed")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("channel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("chunk", VTYPE_Mix_Chunk, ArgOccur::Once, ArgFlag::None);
	DeclareArg("loops", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ticks", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_PlayChannelTimed_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int channel = args_gurax.PickNumber<int>();
	auto& value_chunk = args_gurax.Pick<Value_Mix_Chunk>();
	Mix_Chunk* chunk = value_chunk.GetEntityPtr();
	int loops = args_gurax.PickNumber<int>();
	int ticks = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_PlayChannelTimed(channel, chunk, loops, ticks);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_PlayMusic(music as Mix_Music, loops as Number)
Gurax_DeclareFunctionAlias(Mix_PlayMusic_gurax, "Mix_PlayMusic")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("music", VTYPE_Mix_Music, ArgOccur::Once, ArgFlag::None);
	DeclareArg("loops", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_PlayMusic_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_music = args_gurax.Pick<Value_Mix_Music>();
	Mix_Music* music = value_music.GetEntityPtr();
	int loops = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_PlayMusic(music, loops);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_FadeInMusic(music as Mix_Music, loops as Number, ms as Number)
Gurax_DeclareFunctionAlias(Mix_FadeInMusic_gurax, "Mix_FadeInMusic")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("music", VTYPE_Mix_Music, ArgOccur::Once, ArgFlag::None);
	DeclareArg("loops", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ms", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_FadeInMusic_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_music = args_gurax.Pick<Value_Mix_Music>();
	Mix_Music* music = value_music.GetEntityPtr();
	int loops = args_gurax.PickNumber<int>();
	int ms = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_FadeInMusic(music, loops, ms);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_FadeInMusicPos(music as Mix_Music, loops as Number, ms as Number, position as Number)
Gurax_DeclareFunctionAlias(Mix_FadeInMusicPos_gurax, "Mix_FadeInMusicPos")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("music", VTYPE_Mix_Music, ArgOccur::Once, ArgFlag::None);
	DeclareArg("loops", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ms", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("position", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_FadeInMusicPos_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_music = args_gurax.Pick<Value_Mix_Music>();
	Mix_Music* music = value_music.GetEntityPtr();
	int loops = args_gurax.PickNumber<int>();
	int ms = args_gurax.PickNumber<int>();
	double position = args_gurax.PickNumber<double>();
	// Function body
	int rtn = Mix_FadeInMusicPos(music, loops, ms, position);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_FadeInChannelTimed(channel as Number, chunk as Mix_Chunk, loops as Number, ms as Number, ticks as Number)
Gurax_DeclareFunctionAlias(Mix_FadeInChannelTimed_gurax, "Mix_FadeInChannelTimed")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("channel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("chunk", VTYPE_Mix_Chunk, ArgOccur::Once, ArgFlag::None);
	DeclareArg("loops", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ms", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ticks", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_FadeInChannelTimed_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int channel = args_gurax.PickNumber<int>();
	auto& value_chunk = args_gurax.Pick<Value_Mix_Chunk>();
	Mix_Chunk* chunk = value_chunk.GetEntityPtr();
	int loops = args_gurax.PickNumber<int>();
	int ms = args_gurax.PickNumber<int>();
	int ticks = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_FadeInChannelTimed(channel, chunk, loops, ms, ticks);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_Volume(channel as Number, volume as Number)
Gurax_DeclareFunctionAlias(Mix_Volume_gurax, "Mix_Volume")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("channel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("volume", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_Volume_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int channel = args_gurax.PickNumber<int>();
	int volume = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_Volume(channel, volume);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_VolumeChunk(chunk as Mix_Chunk, volume as Number)
Gurax_DeclareFunctionAlias(Mix_VolumeChunk_gurax, "Mix_VolumeChunk")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("chunk", VTYPE_Mix_Chunk, ArgOccur::Once, ArgFlag::None);
	DeclareArg("volume", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_VolumeChunk_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_chunk = args_gurax.Pick<Value_Mix_Chunk>();
	Mix_Chunk* chunk = value_chunk.GetEntityPtr();
	int volume = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_VolumeChunk(chunk, volume);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_VolumeMusic(volume as Number)
Gurax_DeclareFunctionAlias(Mix_VolumeMusic_gurax, "Mix_VolumeMusic")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("volume", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_VolumeMusic_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int volume = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_VolumeMusic(volume);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_HaltChannel(channel as Number)
Gurax_DeclareFunctionAlias(Mix_HaltChannel_gurax, "Mix_HaltChannel")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("channel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_HaltChannel_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int channel = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_HaltChannel(channel);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_HaltGroup(tag as Number)
Gurax_DeclareFunctionAlias(Mix_HaltGroup_gurax, "Mix_HaltGroup")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("tag", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_HaltGroup_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int tag = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_HaltGroup(tag);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_HaltMusic()
Gurax_DeclareFunctionAlias(Mix_HaltMusic_gurax, "Mix_HaltMusic")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(Mix_HaltMusic_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = Mix_HaltMusic();
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_ExpireChannel(channel as Number, ticks as Number)
Gurax_DeclareFunctionAlias(Mix_ExpireChannel_gurax, "Mix_ExpireChannel")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("channel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ticks", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_ExpireChannel_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int channel = args_gurax.PickNumber<int>();
	int ticks = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_ExpireChannel(channel, ticks);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_FadeOutChannel(which as Number, ms as Number)
Gurax_DeclareFunctionAlias(Mix_FadeOutChannel_gurax, "Mix_FadeOutChannel")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("which", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ms", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_FadeOutChannel_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int which = args_gurax.PickNumber<int>();
	int ms = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_FadeOutChannel(which, ms);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_FadeOutGroup(tag as Number, ms as Number)
Gurax_DeclareFunctionAlias(Mix_FadeOutGroup_gurax, "Mix_FadeOutGroup")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("tag", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ms", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_FadeOutGroup_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int tag = args_gurax.PickNumber<int>();
	int ms = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_FadeOutGroup(tag, ms);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_FadeOutMusic(ms as Number)
Gurax_DeclareFunctionAlias(Mix_FadeOutMusic_gurax, "Mix_FadeOutMusic")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("ms", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_FadeOutMusic_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int ms = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_FadeOutMusic(ms);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_FadingMusic()
Gurax_DeclareFunctionAlias(Mix_FadingMusic_gurax, "Mix_FadingMusic")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(Mix_FadingMusic_gurax, processor_gurax, argument_gurax)
{
	// Function body
	Mix_Fading rtn = Mix_FadingMusic();
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_FadingChannel(which as Number)
Gurax_DeclareFunctionAlias(Mix_FadingChannel_gurax, "Mix_FadingChannel")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("which", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_FadingChannel_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int which = args_gurax.PickNumber<int>();
	// Function body
	Mix_Fading rtn = Mix_FadingChannel(which);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_Pause(channel as Number)
Gurax_DeclareFunctionAlias(Mix_Pause_gurax, "Mix_Pause")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("channel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_Pause_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int channel = args_gurax.PickNumber<int>();
	// Function body
	Mix_Pause(channel);
	return Gurax::Value::nil();
}

// sdl.Mix_Resume(channel as Number)
Gurax_DeclareFunctionAlias(Mix_Resume_gurax, "Mix_Resume")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("channel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_Resume_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int channel = args_gurax.PickNumber<int>();
	// Function body
	Mix_Resume(channel);
	return Gurax::Value::nil();
}

// sdl.Mix_Paused(channel as Number)
Gurax_DeclareFunctionAlias(Mix_Paused_gurax, "Mix_Paused")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("channel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_Paused_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int channel = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_Paused(channel);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_PauseMusic()
Gurax_DeclareFunctionAlias(Mix_PauseMusic_gurax, "Mix_PauseMusic")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(Mix_PauseMusic_gurax, processor_gurax, argument_gurax)
{
	// Function body
	Mix_PauseMusic();
	return Gurax::Value::nil();
}

// sdl.Mix_ResumeMusic()
Gurax_DeclareFunctionAlias(Mix_ResumeMusic_gurax, "Mix_ResumeMusic")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(Mix_ResumeMusic_gurax, processor_gurax, argument_gurax)
{
	// Function body
	Mix_ResumeMusic();
	return Gurax::Value::nil();
}

// sdl.Mix_RewindMusic()
Gurax_DeclareFunctionAlias(Mix_RewindMusic_gurax, "Mix_RewindMusic")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(Mix_RewindMusic_gurax, processor_gurax, argument_gurax)
{
	// Function body
	Mix_RewindMusic();
	return Gurax::Value::nil();
}

// sdl.Mix_PausedMusic()
Gurax_DeclareFunctionAlias(Mix_PausedMusic_gurax, "Mix_PausedMusic")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(Mix_PausedMusic_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = Mix_PausedMusic();
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_SetMusicPosition(position as Number)
Gurax_DeclareFunctionAlias(Mix_SetMusicPosition_gurax, "Mix_SetMusicPosition")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("position", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_SetMusicPosition_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	double position = args_gurax.PickNumber<double>();
	// Function body
	int rtn = Mix_SetMusicPosition(position);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_Playing(channel as Number)
Gurax_DeclareFunctionAlias(Mix_Playing_gurax, "Mix_Playing")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("channel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_Playing_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int channel = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_Playing(channel);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_PlayingMusic()
Gurax_DeclareFunctionAlias(Mix_PlayingMusic_gurax, "Mix_PlayingMusic")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(Mix_PlayingMusic_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = Mix_PlayingMusic();
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_SetMusicCMD(command as String)
Gurax_DeclareFunctionAlias(Mix_SetMusicCMD_gurax, "Mix_SetMusicCMD")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("command", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_SetMusicCMD_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* command = args_gurax.PickString();
	// Function body
	int rtn = Mix_SetMusicCMD(command);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_SetSynchroValue(value as Number)
Gurax_DeclareFunctionAlias(Mix_SetSynchroValue_gurax, "Mix_SetSynchroValue")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_SetSynchroValue_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int value = args_gurax.PickNumber<int>();
	// Function body
	int rtn = Mix_SetSynchroValue(value);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_GetSynchroValue()
Gurax_DeclareFunctionAlias(Mix_GetSynchroValue_gurax, "Mix_GetSynchroValue")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(Mix_GetSynchroValue_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = Mix_GetSynchroValue();
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_SetSoundFonts(paths as String)
Gurax_DeclareFunctionAlias(Mix_SetSoundFonts_gurax, "Mix_SetSoundFonts")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("paths", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_SetSoundFonts_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* paths = args_gurax.PickString();
	// Function body
	int rtn = Mix_SetSoundFonts(paths);
	return new Gurax::Value_Number(rtn);
}

// sdl.Mix_GetSoundFonts()
Gurax_DeclareFunctionAlias(Mix_GetSoundFonts_gurax, "Mix_GetSoundFonts")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementFunctionEx(Mix_GetSoundFonts_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const char* rtn = Mix_GetSoundFonts();
	return new Gurax::Value_String(rtn);
}

// sdl.Mix_GetChunk(channel as Number)
Gurax_DeclareFunctionAlias(Mix_GetChunk_gurax, "Mix_GetChunk")
{
	Declare(VTYPE_Mix_Chunk, Flag::None);
	DeclareArg("channel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Mix_GetChunk_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int channel = args_gurax.PickNumber<int>();
	// Function body
	Mix_Chunk* rtn = Mix_GetChunk(channel);
	if (!rtn) return Value::nil();
	return new Value_Mix_Chunk(rtn);
}

// sdl.Mix_CloseAudio()
Gurax_DeclareFunctionAlias(Mix_CloseAudio_gurax, "Mix_CloseAudio")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(Mix_CloseAudio_gurax, processor_gurax, argument_gurax)
{
	// Function body
	Mix_CloseAudio();
	return Gurax::Value::nil();
}

// sdl.TTF_Linked_Version()
Gurax_DeclareFunctionAlias(TTF_Linked_Version_gurax, "TTF_Linked_Version")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementFunctionEx(TTF_Linked_Version_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const SDL_version* ver = TTF_Linked_Version();
	return new Value_SDL_version(*ver);
}

// sdl.TTF_ByteSwappedUNICODE(swapped as Number)
Gurax_DeclareFunctionAlias(TTF_ByteSwappedUNICODE_gurax, "TTF_ByteSwappedUNICODE")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("swapped", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_ByteSwappedUNICODE_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int swapped = args_gurax.PickNumber<int>();
	// Function body
	TTF_ByteSwappedUNICODE(swapped);
	return Gurax::Value::nil();
}

// sdl.TTF_Init()
Gurax_DeclareFunctionAlias(TTF_Init_gurax, "TTF_Init")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(TTF_Init_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = TTF_Init();
	return new Gurax::Value_Number(rtn);
}

// sdl.TTF_GetError()
Gurax_DeclareFunctionAlias(TTF_GetError_gurax, "TTF_GetError")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementFunctionEx(TTF_GetError_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const char* rtn = TTF_GetError();
	return new Gurax::Value_String(rtn);
}

// sdl.TTF_OpenFont(file as String, ptsize as Number)
Gurax_DeclareFunctionAlias(TTF_OpenFont_gurax, "TTF_OpenFont")
{
	Declare(VTYPE_TTF_Font, Flag::None);
	DeclareArg("file", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ptsize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_OpenFont_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* file = args_gurax.PickString();
	int ptsize = args_gurax.PickNumber<int>();
	// Function body
	TTF_Font* rtn = TTF_OpenFont(file, ptsize);
	if (!rtn) return Value::nil();
	return new Value_TTF_Font(rtn);
}

// sdl.TTF_OpenFontIndex(file as String, ptsize as Number, index as Number)
Gurax_DeclareFunctionAlias(TTF_OpenFontIndex_gurax, "TTF_OpenFontIndex")
{
	Declare(VTYPE_TTF_Font, Flag::None);
	DeclareArg("file", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ptsize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_OpenFontIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* file = args_gurax.PickString();
	int ptsize = args_gurax.PickNumber<int>();
	long index = args_gurax.PickNumber<long>();
	// Function body
	TTF_Font* rtn = TTF_OpenFontIndex(file, ptsize, index);
	if (!rtn) return Value::nil();
	return new Value_TTF_Font(rtn);
}

// sdl.TTF_OpenFontRW(src as SDL_RWops, freesrc as Number, ptsize as Number)
Gurax_DeclareFunctionAlias(TTF_OpenFontRW_gurax, "TTF_OpenFontRW")
{
	Declare(VTYPE_TTF_Font, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("freesrc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ptsize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_OpenFontRW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	int freesrc = args_gurax.PickNumber<int>();
	int ptsize = args_gurax.PickNumber<int>();
	// Function body
	TTF_Font* rtn = TTF_OpenFontRW(src, freesrc, ptsize);
	if (!rtn) return Value::nil();
	return new Value_TTF_Font(rtn);
}

// sdl.TTF_OpenFontIndexRW(src as SDL_RWops, freesrc as Number, ptsize as Number, index as Number)
Gurax_DeclareFunctionAlias(TTF_OpenFontIndexRW_gurax, "TTF_OpenFontIndexRW")
{
	Declare(VTYPE_TTF_Font, Flag::None);
	DeclareArg("src", VTYPE_SDL_RWops, ArgOccur::Once, ArgFlag::None);
	DeclareArg("freesrc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ptsize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_OpenFontIndexRW_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_src = args_gurax.Pick<Value_SDL_RWops>();
	SDL_RWops* src = value_src.GetEntityPtr();
	int freesrc = args_gurax.PickNumber<int>();
	int ptsize = args_gurax.PickNumber<int>();
	long index = args_gurax.PickNumber<long>();
	// Function body
	TTF_Font* rtn = TTF_OpenFontIndexRW(src, freesrc, ptsize, index);
	if (!rtn) return Value::nil();
	return new Value_TTF_Font(rtn);
}

// sdl.TTF_GetFontStyle(font as TTF_Font)
Gurax_DeclareFunctionAlias(TTF_GetFontStyle_gurax, "TTF_GetFontStyle")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_GetFontStyle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	const TTF_Font* font = value_font.GetEntityPtr();
	// Function body
	int rtn = TTF_GetFontStyle(font);
	return new Gurax::Value_Number(rtn);
}

// sdl.TTF_SetFontStyle(font as TTF_Font, style as Number)
Gurax_DeclareFunctionAlias(TTF_SetFontStyle_gurax, "TTF_SetFontStyle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_SetFontStyle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	TTF_Font* font = value_font.GetEntityPtr();
	int style = args_gurax.PickNumber<int>();
	// Function body
	TTF_SetFontStyle(font, style);
	return Gurax::Value::nil();
}

// sdl.TTF_GetFontOutline(font as TTF_Font)
Gurax_DeclareFunctionAlias(TTF_GetFontOutline_gurax, "TTF_GetFontOutline")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_GetFontOutline_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	const TTF_Font* font = value_font.GetEntityPtr();
	// Function body
	int rtn = TTF_GetFontOutline(font);
	return new Gurax::Value_Number(rtn);
}

// sdl.TTF_SetFontOutline(font as TTF_Font, outline as Number)
Gurax_DeclareFunctionAlias(TTF_SetFontOutline_gurax, "TTF_SetFontOutline")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
	DeclareArg("outline", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_SetFontOutline_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	TTF_Font* font = value_font.GetEntityPtr();
	int outline = args_gurax.PickNumber<int>();
	// Function body
	TTF_SetFontOutline(font, outline);
	return Gurax::Value::nil();
}

// sdl.TTF_GetFontHinting(font as TTF_Font)
Gurax_DeclareFunctionAlias(TTF_GetFontHinting_gurax, "TTF_GetFontHinting")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_GetFontHinting_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	const TTF_Font* font = value_font.GetEntityPtr();
	// Function body
	int rtn = TTF_GetFontHinting(font);
	return new Gurax::Value_Number(rtn);
}

// sdl.TTF_SetFontHinting(font as TTF_Font, hinting as Number)
Gurax_DeclareFunctionAlias(TTF_SetFontHinting_gurax, "TTF_SetFontHinting")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hinting", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_SetFontHinting_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	TTF_Font* font = value_font.GetEntityPtr();
	int hinting = args_gurax.PickNumber<int>();
	// Function body
	TTF_SetFontHinting(font, hinting);
	return Gurax::Value::nil();
}

// sdl.TTF_FontHeight(font as TTF_Font)
Gurax_DeclareFunctionAlias(TTF_FontHeight_gurax, "TTF_FontHeight")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_FontHeight_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	const TTF_Font* font = value_font.GetEntityPtr();
	// Function body
	int rtn = TTF_FontHeight(font);
	return new Gurax::Value_Number(rtn);
}

// sdl.TTF_FontAscent(font as TTF_Font)
Gurax_DeclareFunctionAlias(TTF_FontAscent_gurax, "TTF_FontAscent")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_FontAscent_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	const TTF_Font* font = value_font.GetEntityPtr();
	// Function body
	int rtn = TTF_FontAscent(font);
	return new Gurax::Value_Number(rtn);
}

// sdl.TTF_FontDescent(font as TTF_Font)
Gurax_DeclareFunctionAlias(TTF_FontDescent_gurax, "TTF_FontDescent")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_FontDescent_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	const TTF_Font* font = value_font.GetEntityPtr();
	// Function body
	int rtn = TTF_FontDescent(font);
	return new Gurax::Value_Number(rtn);
}

// sdl.TTF_FontLineSkip(font as TTF_Font)
Gurax_DeclareFunctionAlias(TTF_FontLineSkip_gurax, "TTF_FontLineSkip")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_FontLineSkip_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	const TTF_Font* font = value_font.GetEntityPtr();
	// Function body
	int rtn = TTF_FontLineSkip(font);
	return new Gurax::Value_Number(rtn);
}

// sdl.TTF_GetFontKerning(font as TTF_Font)
Gurax_DeclareFunctionAlias(TTF_GetFontKerning_gurax, "TTF_GetFontKerning")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_GetFontKerning_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	const TTF_Font* font = value_font.GetEntityPtr();
	// Function body
	int rtn = TTF_GetFontKerning(font);
	return new Gurax::Value_Number(rtn);
}

// sdl.TTF_SetFontKerning(font as TTF_Font, allowed as Number)
Gurax_DeclareFunctionAlias(TTF_SetFontKerning_gurax, "TTF_SetFontKerning")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
	DeclareArg("allowed", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_SetFontKerning_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	TTF_Font* font = value_font.GetEntityPtr();
	int allowed = args_gurax.PickNumber<int>();
	// Function body
	TTF_SetFontKerning(font, allowed);
	return Gurax::Value::nil();
}

// sdl.TTF_FontFaces(font as TTF_Font)
Gurax_DeclareFunctionAlias(TTF_FontFaces_gurax, "TTF_FontFaces")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_FontFaces_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	const TTF_Font* font = value_font.GetEntityPtr();
	// Function body
	long rtn = TTF_FontFaces(font);
	return new Gurax::Value_Number(rtn);
}

// sdl.TTF_FontFaceIsFixedWidth(font as TTF_Font)
Gurax_DeclareFunctionAlias(TTF_FontFaceIsFixedWidth_gurax, "TTF_FontFaceIsFixedWidth")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_FontFaceIsFixedWidth_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	const TTF_Font* font = value_font.GetEntityPtr();
	// Function body
	int rtn = TTF_FontFaceIsFixedWidth(font);
	return new Gurax::Value_Number(rtn);
}

// sdl.TTF_GlyphIsProvided(font as TTF_Font, ch as Number)
Gurax_DeclareFunctionAlias(TTF_GlyphIsProvided_gurax, "TTF_GlyphIsProvided")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_GlyphIsProvided_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	const TTF_Font* font = value_font.GetEntityPtr();
	Uint16 ch = args_gurax.PickNumber<Uint16>();
	// Function body
	int rtn = TTF_GlyphIsProvided(font, ch);
	return new Gurax::Value_Number(rtn);
}

// sdl.TTF_RenderText_Solid(font as TTF_Font, text as String, fg as SDL_Color)
Gurax_DeclareFunctionAlias(TTF_RenderText_Solid_gurax, "TTF_RenderText_Solid")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fg", VTYPE_SDL_Color, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_RenderText_Solid_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	TTF_Font* font = value_font.GetEntityPtr();
	const char* text = args_gurax.PickString();
	auto& value_fg = args_gurax.Pick<Value_SDL_Color>();
	SDL_Color& fg = value_fg.GetEntity();
	// Function body
	SDL_Surface* rtn = TTF_RenderText_Solid(font, text, fg);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.TTF_RenderUTF8_Solid(font as TTF_Font, text as String, fg as SDL_Color)
Gurax_DeclareFunctionAlias(TTF_RenderUTF8_Solid_gurax, "TTF_RenderUTF8_Solid")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fg", VTYPE_SDL_Color, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_RenderUTF8_Solid_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	TTF_Font* font = value_font.GetEntityPtr();
	const char* text = args_gurax.PickString();
	auto& value_fg = args_gurax.Pick<Value_SDL_Color>();
	SDL_Color& fg = value_fg.GetEntity();
	// Function body
	SDL_Surface* rtn = TTF_RenderUTF8_Solid(font, text, fg);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.TTF_RenderGlyph_Solid(font as TTF_Font, ch as Number, fg as SDL_Color)
Gurax_DeclareFunctionAlias(TTF_RenderGlyph_Solid_gurax, "TTF_RenderGlyph_Solid")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fg", VTYPE_SDL_Color, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_RenderGlyph_Solid_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	TTF_Font* font = value_font.GetEntityPtr();
	Uint16 ch = args_gurax.PickNumber<Uint16>();
	auto& value_fg = args_gurax.Pick<Value_SDL_Color>();
	SDL_Color& fg = value_fg.GetEntity();
	// Function body
	SDL_Surface* rtn = TTF_RenderGlyph_Solid(font, ch, fg);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.TTF_RenderText_Shaded(font as TTF_Font, text as String, fg as SDL_Color, bg as SDL_Color)
Gurax_DeclareFunctionAlias(TTF_RenderText_Shaded_gurax, "TTF_RenderText_Shaded")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fg", VTYPE_SDL_Color, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bg", VTYPE_SDL_Color, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_RenderText_Shaded_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	TTF_Font* font = value_font.GetEntityPtr();
	const char* text = args_gurax.PickString();
	auto& value_fg = args_gurax.Pick<Value_SDL_Color>();
	SDL_Color& fg = value_fg.GetEntity();
	auto& value_bg = args_gurax.Pick<Value_SDL_Color>();
	SDL_Color& bg = value_bg.GetEntity();
	// Function body
	SDL_Surface* rtn = TTF_RenderText_Shaded(font, text, fg, bg);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.TTF_RenderUTF8_Shaded(font as TTF_Font, text as String, fg as SDL_Color, bg as SDL_Color)
Gurax_DeclareFunctionAlias(TTF_RenderUTF8_Shaded_gurax, "TTF_RenderUTF8_Shaded")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fg", VTYPE_SDL_Color, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bg", VTYPE_SDL_Color, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_RenderUTF8_Shaded_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	TTF_Font* font = value_font.GetEntityPtr();
	const char* text = args_gurax.PickString();
	auto& value_fg = args_gurax.Pick<Value_SDL_Color>();
	SDL_Color& fg = value_fg.GetEntity();
	auto& value_bg = args_gurax.Pick<Value_SDL_Color>();
	SDL_Color& bg = value_bg.GetEntity();
	// Function body
	SDL_Surface* rtn = TTF_RenderUTF8_Shaded(font, text, fg, bg);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.TTF_RenderGlyph_Shaded(font as TTF_Font, ch as Number, fg as SDL_Color, bg as SDL_Color)
Gurax_DeclareFunctionAlias(TTF_RenderGlyph_Shaded_gurax, "TTF_RenderGlyph_Shaded")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fg", VTYPE_SDL_Color, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bg", VTYPE_SDL_Color, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_RenderGlyph_Shaded_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	TTF_Font* font = value_font.GetEntityPtr();
	Uint16 ch = args_gurax.PickNumber<Uint16>();
	auto& value_fg = args_gurax.Pick<Value_SDL_Color>();
	SDL_Color& fg = value_fg.GetEntity();
	auto& value_bg = args_gurax.Pick<Value_SDL_Color>();
	SDL_Color& bg = value_bg.GetEntity();
	// Function body
	SDL_Surface* rtn = TTF_RenderGlyph_Shaded(font, ch, fg, bg);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.TTF_RenderText_Blended(font as TTF_Font, text as String, fg as SDL_Color)
Gurax_DeclareFunctionAlias(TTF_RenderText_Blended_gurax, "TTF_RenderText_Blended")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fg", VTYPE_SDL_Color, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_RenderText_Blended_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	TTF_Font* font = value_font.GetEntityPtr();
	const char* text = args_gurax.PickString();
	auto& value_fg = args_gurax.Pick<Value_SDL_Color>();
	SDL_Color& fg = value_fg.GetEntity();
	// Function body
	SDL_Surface* rtn = TTF_RenderText_Blended(font, text, fg);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.TTF_RenderUTF8_Blended(font as TTF_Font, text as String, fg as SDL_Color)
Gurax_DeclareFunctionAlias(TTF_RenderUTF8_Blended_gurax, "TTF_RenderUTF8_Blended")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fg", VTYPE_SDL_Color, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_RenderUTF8_Blended_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	TTF_Font* font = value_font.GetEntityPtr();
	const char* text = args_gurax.PickString();
	auto& value_fg = args_gurax.Pick<Value_SDL_Color>();
	SDL_Color& fg = value_fg.GetEntity();
	// Function body
	SDL_Surface* rtn = TTF_RenderUTF8_Blended(font, text, fg);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.TTF_RenderText_Blended_Wrapped(font as TTF_Font, text as String, fg as SDL_Color, wrapLength as Number)
Gurax_DeclareFunctionAlias(TTF_RenderText_Blended_Wrapped_gurax, "TTF_RenderText_Blended_Wrapped")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fg", VTYPE_SDL_Color, ArgOccur::Once, ArgFlag::None);
	DeclareArg("wrapLength", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_RenderText_Blended_Wrapped_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	TTF_Font* font = value_font.GetEntityPtr();
	const char* text = args_gurax.PickString();
	auto& value_fg = args_gurax.Pick<Value_SDL_Color>();
	SDL_Color& fg = value_fg.GetEntity();
	Uint32 wrapLength = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_Surface* rtn = TTF_RenderText_Blended_Wrapped(font, text, fg, wrapLength);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.TTF_RenderUTF8_Blended_Wrapped(font as TTF_Font, text as String, fg as SDL_Color, wrapLength as Number)
Gurax_DeclareFunctionAlias(TTF_RenderUTF8_Blended_Wrapped_gurax, "TTF_RenderUTF8_Blended_Wrapped")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fg", VTYPE_SDL_Color, ArgOccur::Once, ArgFlag::None);
	DeclareArg("wrapLength", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_RenderUTF8_Blended_Wrapped_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	TTF_Font* font = value_font.GetEntityPtr();
	const char* text = args_gurax.PickString();
	auto& value_fg = args_gurax.Pick<Value_SDL_Color>();
	SDL_Color& fg = value_fg.GetEntity();
	Uint32 wrapLength = args_gurax.PickNumber<Uint32>();
	// Function body
	SDL_Surface* rtn = TTF_RenderUTF8_Blended_Wrapped(font, text, fg, wrapLength);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.TTF_RenderGlyph_Blended(font as TTF_Font, ch as Number, fg as SDL_Color)
Gurax_DeclareFunctionAlias(TTF_RenderGlyph_Blended_gurax, "TTF_RenderGlyph_Blended")
{
	Declare(VTYPE_SDL_Surface, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fg", VTYPE_SDL_Color, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_RenderGlyph_Blended_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	TTF_Font* font = value_font.GetEntityPtr();
	Uint16 ch = args_gurax.PickNumber<Uint16>();
	auto& value_fg = args_gurax.Pick<Value_SDL_Color>();
	SDL_Color& fg = value_fg.GetEntity();
	// Function body
	SDL_Surface* rtn = TTF_RenderGlyph_Blended(font, ch, fg);
	if (!rtn) return Value::nil();
	return new Value_SDL_Surface(rtn);
}

// sdl.TTF_CloseFont(font as TTF_Font)
Gurax_DeclareFunctionAlias(TTF_CloseFont_gurax, "TTF_CloseFont")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("font", VTYPE_TTF_Font, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(TTF_CloseFont_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font = args_gurax.Pick<Value_TTF_Font>();
	TTF_Font* font = value_font.GetEntityPtr();
	// Function body
	TTF_CloseFont(font);
	return Gurax::Value::nil();
}

// sdl.TTF_Quit()
Gurax_DeclareFunctionAlias(TTF_Quit_gurax, "TTF_Quit")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(TTF_Quit_gurax, processor_gurax, argument_gurax)
{
	// Function body
	TTF_Quit();
	return Gurax::Value::nil();
}

// sdl.TTF_WasInit()
Gurax_DeclareFunctionAlias(TTF_WasInit_gurax, "TTF_WasInit")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(TTF_WasInit_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = TTF_WasInit();
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
	frame.Assign(Gurax_CreateFunction(SDL_GetVersion_gurax));
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
	frame.Assign(Gurax_CreateFunction(SDL_SetWindowDisplayMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetWindowDisplayMode_gurax));
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
	frame.Assign(Gurax_CreateFunction(SDL_UpdateWindowSurfaceRects_gurax));
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
	frame.Assign(Gurax_CreateFunction(SDL_LockTexture_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_LockTextureToSurface_gurax));
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
	frame.Assign(Gurax_CreateFunction(SDL_GetRenderDrawColor_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetRenderDrawBlendMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetRenderDrawBlendMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderClear_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawPoint_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawPoints_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawLine_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawLines_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawRect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawRects_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderFillRect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderFillRects_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderCopy_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderCopyEx_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawPointF_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawPointsF_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawLineF_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawLinesF_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawRectF_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderDrawRectsF_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderFillRectF_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderFillRectsF_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderCopyF_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderReadPixels_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderPresent_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_DestroyTexture_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_DestroyRenderer_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RenderFlush_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GL_UnbindTexture_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetPixelFormatName_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_MasksToPixelFormatEnum_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_AllocFormat_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_FreeFormat_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_AllocPalette_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetPixelFormatPalette_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetPaletteColors_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_FreePalette_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_MapRGB_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_MapRGBA_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetRGB_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetRGBA_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasIntersection_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_IntersectRect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_UnionRect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_IntersectRectAndLine_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CreateRGBSurface_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CreateRGBSurfaceWithFormat_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CreateRGBSurfaceFrom_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CreateRGBSurfaceWithFormatFrom_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CreateRGBSurfaceFromImage_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_FreeSurface_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetSurfacePalette_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_LockSurface_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_UnlockSurface_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_LoadBMP_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_LoadBMP_RW_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SaveBMP_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SaveBMP_RW_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetSurfaceRLE_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetColorKey_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasColorKey_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetColorKey_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetSurfaceColorMod_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetSurfaceColorMod_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetSurfaceAlphaMod_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetSurfaceAlphaMod_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetSurfaceBlendMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetSurfaceBlendMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetClipRect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetClipRect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_DuplicateSurface_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ConvertSurface_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ConvertSurfaceFormat_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ConvertPixels_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_FillRect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_FillRects_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_BlitSurface_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_UpperBlit_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_LowerBlit_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SoftStretch_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_BlitScaled_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_UpperBlitScaled_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_LowerBlitScaled_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SetYUVConversionMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetYUVConversionMode_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetYUVConversionModeForResolution_gurax));
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
	frame.Assign(Gurax_CreateFunction(SDL_GetKeyboardState_gurax));
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
	frame.Assign(Gurax_CreateFunction(SDL_SetTextInputRect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasScreenKeyboardSupport_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_IsScreenKeyboardShown_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetMouseFocus_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetMouseState_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetGlobalMouseState_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetRelativeMouseState_gurax));
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
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetGUIDString_gurax));
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
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetBall_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickGetButton_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickRumble_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickClose_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickCurrentPowerLevel_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerAddMappingsFromRW_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerAddMapping_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerNumMappings_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerMappingForIndex_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerMappingForGUID_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerMapping_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_IsGameController_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerNameForIndex_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerTypeForIndex_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerMappingForDeviceIndex_gurax));
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
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetAxis_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetButtonFromString_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetStringForButton_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerGetButton_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerRumble_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GameControllerClose_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_NumSensors_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SensorGetDeviceName_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SensorGetDeviceType_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SensorGetDeviceNonPortableType_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SensorGetDeviceInstanceID_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SensorOpen_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SensorFromInstanceID_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SensorGetName_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SensorGetType_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SensorGetNonPortableType_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SensorGetInstanceID_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SensorClose_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SensorUpdate_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_NumHaptics_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticName_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticOpen_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticOpened_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticIndex_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_MouseIsHaptic_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticOpenFromMouse_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_JoystickIsHaptic_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticOpenFromJoystick_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticClose_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticNumEffects_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticNumEffectsPlaying_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticQuery_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticNumAxes_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticEffectSupported_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticNewEffect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticUpdateEffect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticRunEffect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticStopEffect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticDestroyEffect_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticGetEffectStatus_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticSetGain_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticSetAutocenter_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticPause_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticUnpause_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticStopAll_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticRumbleSupported_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticRumbleInit_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticRumblePlay_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HapticRumbleStop_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetNumAudioDrivers_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetAudioDriver_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_AUDIO_BITSIZE_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_AudioInit_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_AudioQuit_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetCurrentAudioDriver_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_OpenAudio_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetNumAudioDevices_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetAudioDeviceName_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_OpenAudioDevice_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetAudioStatus_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetAudioDeviceStatus_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_PauseAudio_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_PauseAudioDevice_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_BuildAudioCVT_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ConvertAudio_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_AudioStreamPut_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_AudioStreamGet_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_AudioStreamAvailable_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_AudioStreamFlush_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_AudioStreamClear_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_FreeAudioStream_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_QueueAudio_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_DequeueAudio_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetQueuedAudioSize_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ClearQueuedAudio_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_LockAudio_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_LockAudioDevice_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_UnlockAudio_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_UnlockAudioDevice_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CloseAudio_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_CloseAudioDevice_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetTicks_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetPerformanceCounter_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetPerformanceFrequency_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_Delay_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RemoveTimer_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RWFromFile_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RWFromConstMem_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_AllocRW_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_FreeRW_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RWsize_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RWseek_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RWtell_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RWread_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RWwrite_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_RWclose_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ReadU8_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ReadLE16_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ReadBE16_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ReadLE32_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ReadBE32_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ReadLE64_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_ReadBE64_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_WriteU8_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_WriteLE16_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_WriteBE16_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_WriteLE32_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_WriteBE32_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_WriteLE64_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_WriteBE64_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetCPUCount_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetCPUCacheLineSize_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasRDTSC_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasAltiVec_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasMMX_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_Has3DNow_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasSSE_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasSSE2_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasSSE3_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasSSE41_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasSSE42_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasAVX_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasAVX2_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasAVX512F_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasARMSIMD_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_HasNEON_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetSystemRAM_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SIMDGetAlignment_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_SIMDFree_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetPowerInfo_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_Linked_Version_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_Init_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_Quit_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_GetError_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_Load_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_Load_RW_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_LoadTyped_RW_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_LoadCUR_RW_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_LoadICO_RW_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_LoadBMP_RW_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_LoadPNM_RW_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_LoadXPM_RW_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_LoadXCF_RW_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_LoadPCX_RW_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_LoadGIF_RW_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_LoadJPG_RW_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_LoadTIF_RW_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_LoadPNG_RW_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_LoadTGA_RW_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_LoadLBM_RW_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_LoadXV_RW_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_isCUR_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_isICO_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_isBMP_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_isPNM_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_isXPM_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_isXCF_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_isPCX_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_isGIF_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_isJPG_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_isTIF_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_isPNG_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_isLBM_gurax));
	frame.Assign(Gurax_CreateFunction(IMG_isXV_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_Linked_Version_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_Init_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_Quit_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_OpenAudio_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_OpenAudioDevice_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_AllocateChannels_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_GetError_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_QuerySpec_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_LoadWAV_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_LoadWAV_RW_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_LoadMUS_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_LoadMUS_RW_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_LoadMUSType_RW_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_FreeChunk_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_FreeMusic_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_GetNumChunkDecoders_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_GetChunkDecoder_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_HasChunkDecoder_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_GetNumMusicDecoders_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_GetMusicDecoder_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_GetMusicType_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_UnregisterAllEffects_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_SetPanning_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_SetPosition_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_SetDistance_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_SetReverseStereo_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_ReserveChannels_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_GroupChannel_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_GroupChannels_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_GroupAvailable_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_GroupCount_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_GroupOldest_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_GroupNewer_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_PlayChannel_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_PlayChannelTimed_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_PlayMusic_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_FadeInMusic_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_FadeInMusicPos_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_FadeInChannelTimed_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_Volume_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_VolumeChunk_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_VolumeMusic_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_HaltChannel_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_HaltGroup_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_HaltMusic_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_ExpireChannel_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_FadeOutChannel_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_FadeOutGroup_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_FadeOutMusic_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_FadingMusic_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_FadingChannel_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_Pause_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_Resume_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_Paused_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_PauseMusic_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_ResumeMusic_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_RewindMusic_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_PausedMusic_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_SetMusicPosition_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_Playing_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_PlayingMusic_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_SetMusicCMD_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_SetSynchroValue_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_GetSynchroValue_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_SetSoundFonts_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_GetSoundFonts_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_GetChunk_gurax));
	frame.Assign(Gurax_CreateFunction(Mix_CloseAudio_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_Linked_Version_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_ByteSwappedUNICODE_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_Init_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_GetError_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_OpenFont_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_OpenFontIndex_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_OpenFontRW_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_OpenFontIndexRW_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_GetFontStyle_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_SetFontStyle_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_GetFontOutline_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_SetFontOutline_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_GetFontHinting_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_SetFontHinting_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_FontHeight_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_FontAscent_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_FontDescent_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_FontLineSkip_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_GetFontKerning_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_SetFontKerning_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_FontFaces_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_FontFaceIsFixedWidth_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_GlyphIsProvided_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_RenderText_Solid_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_RenderUTF8_Solid_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_RenderGlyph_Solid_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_RenderText_Shaded_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_RenderUTF8_Shaded_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_RenderGlyph_Shaded_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_RenderText_Blended_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_RenderUTF8_Blended_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_RenderText_Blended_Wrapped_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_RenderUTF8_Blended_Wrapped_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_RenderGlyph_Blended_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_CloseFont_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_Quit_gurax));
	frame.Assign(Gurax_CreateFunction(TTF_WasInit_gurax));
}

Gurax_EndModuleScope(sdl)
