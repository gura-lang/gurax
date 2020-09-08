//==============================================================================
// VType_SDL_Event.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// SDL_Event() {block?}
Gurax_DeclareConstructor(SDL_Event)
{
	Declare(VTYPE_SDL_Event, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `sdl.SDL_Event` instance.\n");
}

Gurax_ImplementConstructor(SDL_Event)
{
	// Function body
	return argument.ReturnValue(processor, new Value_SDL_Event());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// sdl.SDL_Event#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(SDL_Event, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(SDL_Event, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_Event#propSkeleton
Gurax_DeclareProperty_R(SDL_Event, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Event, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_Event
//------------------------------------------------------------------------------
VType_SDL_Event VTYPE_SDL_Event("SDL_Event");

void VType_SDL_Event::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(SDL_Event));
	// Assignment of method
	Assign(Gurax_CreateMethod(SDL_Event, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_Event, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_SDL_Event
//------------------------------------------------------------------------------
VType& Value_SDL_Event::vtype = VTYPE_SDL_Event;

String Value_SDL_Event::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_Event";
}

Gurax_EndModuleScope(sdl)
