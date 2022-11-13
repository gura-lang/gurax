//==============================================================================
// VType_SDL_Rect.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_Rect, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_Rect, `en)}

${help.ComposeMethodHelp(sdl.SDL_Rect, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// SDL_Rect(x?:Number, y?:Number, w?:Number, h?:Number) {block?}
Gurax_DeclareConstructor(SDL_Rect)
{
	Declare(VTYPE_Color, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("w", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("h", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `SDL_Rect` instance.
)**");
}

Gurax_ImplementConstructor(SDL_Rect)
{
	// Arguments
	ArgPicker args(argument);
	SDL_Rect rect;
	rect.x = args.IsValid()? args.PickNumber<int>() : 0;
	rect.y = args.IsValid()? args.PickNumber<int>() : 0;
	rect.w = args.IsValid()? args.PickNumber<int>() : 0;
	rect.h = args.IsValid()? args.PickNumber<int>() : 0;
	// Function body
	return argument.ReturnValue(processor, new Value_SDL_Rect(rect));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_Rect#x
Gurax_DeclareProperty_RW(SDL_Rect, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Rect, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().x);
}

Gurax_ImplementPropertySetter(SDL_Rect, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().x = Value_Number::GetNumber<int>(value);
}

// sdl.SDL_Rect#y
Gurax_DeclareProperty_RW(SDL_Rect, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Rect, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().y);
}

Gurax_ImplementPropertySetter(SDL_Rect, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().y = Value_Number::GetNumber<int>(value);
}

// sdl.SDL_Rect#w
Gurax_DeclareProperty_RW(SDL_Rect, w)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Rect, w)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().w);
}

Gurax_ImplementPropertySetter(SDL_Rect, w)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().w = Value_Number::GetNumber<int>(value);
}

// sdl.SDL_Rect#h
Gurax_DeclareProperty_RW(SDL_Rect, h)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Rect, h)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().h);
}

Gurax_ImplementPropertySetter(SDL_Rect, h)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().h = Value_Number::GetNumber<int>(value);
}

//------------------------------------------------------------------------------
// VType_SDL_Rect
//------------------------------------------------------------------------------
VType_SDL_Rect VTYPE_SDL_Rect("SDL_Rect");

void VType_SDL_Rect::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(SDL_Rect));
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_Rect, x));
	Assign(Gurax_CreateProperty(SDL_Rect, y));
	Assign(Gurax_CreateProperty(SDL_Rect, w));
	Assign(Gurax_CreateProperty(SDL_Rect, h));
}

//------------------------------------------------------------------------------
// Value_SDL_Rect
//------------------------------------------------------------------------------
VType& Value_SDL_Rect::vtype = VTYPE_SDL_Rect;

String Value_SDL_Rect::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_Rect");
}

Gurax_EndModuleScope(sdl)
