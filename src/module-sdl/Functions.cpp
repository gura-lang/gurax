//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

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

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(SDL_GetNumVideoDrivers_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetVideoDriver_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_VideoInit_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_VideoQuit_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetCurrentVideoDriver_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetNumVideoDisplays_gurax));
	frame.Assign(Gurax_CreateFunction(SDL_GetDisplayName_gurax));
}

Gurax_EndModuleScope(sdl)
