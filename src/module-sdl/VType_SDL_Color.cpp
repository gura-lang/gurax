//==============================================================================
// VType_SDL_Color.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_Color, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_Color, `en)}

${help.ComposeMethodHelp(sdl.SDL_Color, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// SDL_Color(r?:Number, g?:Number, b?:Number, a?:Number) {block?}
Gurax_DeclareConstructor(SDL_Color)
{
	Declare(VTYPE_Color, Flag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("a", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `SDL_Color` instance.
)""");
}

Gurax_ImplementConstructor(SDL_Color)
{
	// Arguments
	ArgPicker args(argument);
	SDL_Color color;
	color.r = args.IsValid()? args.PickNumberRanged<Uint8>(0, 255) : 0;
	color.g = args.IsValid()? args.PickNumberRanged<Uint8>(0, 255) : 0;
	color.b = args.IsValid()? args.PickNumberRanged<Uint8>(0, 255) : 0;
	color.a = args.IsValid()? args.PickNumberRanged<Uint8>(0, 255) : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	return argument.ReturnValue(processor, new Value_SDL_Color(color));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_Color#r
Gurax_DeclareProperty_RW(SDL_Color, r)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Color, r)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().r);
}

Gurax_ImplementPropertySetter(SDL_Color, r)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().r = Value_Number::GetNumberRanged<Uint8>(value, 0, 255);
}

// sdl.SDL_Color#g
Gurax_DeclareProperty_RW(SDL_Color, g)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Color, g)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().g);
}

Gurax_ImplementPropertySetter(SDL_Color, g)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().g = Value_Number::GetNumberRanged<Uint8>(value, 0, 255);
}

// sdl.SDL_Color#b
Gurax_DeclareProperty_RW(SDL_Color, b)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Color, b)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().b);
}

Gurax_ImplementPropertySetter(SDL_Color, b)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().b = Value_Number::GetNumberRanged<Uint8>(value, 0, 255);
}

// sdl.SDL_Color#a
Gurax_DeclareProperty_RW(SDL_Color, a)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Color, a)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().a);
}

Gurax_ImplementPropertySetter(SDL_Color, a)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().a = Value_Number::GetNumberRanged<Uint8>(value, 0, 255);
}

//------------------------------------------------------------------------------
// VType_SDL_Color
//------------------------------------------------------------------------------
VType_SDL_Color VTYPE_SDL_Color("SDL_Color");

void VType_SDL_Color::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(SDL_Color));
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_Color, r));
	Assign(Gurax_CreateProperty(SDL_Color, g));
	Assign(Gurax_CreateProperty(SDL_Color, b));
	Assign(Gurax_CreateProperty(SDL_Color, a));
}

Value* VType_SDL_Color::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_Tuple)) {
		const ValueOwner& values = Value_Tuple::GetValueOwner(value);
		SDL_Color color;
		color.r = color.g = color.b = color.a = 0;
		if (values.size() > 0) {
			VType& vtype = values.GetVTypeOfElems();
			if (!vtype.IsIdentical(VTYPE_Number)) {
				Error::Issue(ErrorType::TypeError, "the tuple must contain Number elements");
				return nullptr;
			}
			//color.r = dynamic_cast<Value_Number&>(values[0]).GetNumberRanged<Uint8>(0, 255);

			//color.r = Value_Number::GetNumberRanged<Uint8>(values[0], 0, 255);
			//Value_Number::GetNumber<Uint8>;
		}

		//return Value_SDL_Surface::Create(Value_Image::GetImage(value).Reference());
		return Value::nil();
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_SDL_Color
//------------------------------------------------------------------------------
VType& Value_SDL_Color::vtype = VTYPE_SDL_Color;

String Value_SDL_Color::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_Color");
}

Gurax_EndModuleScope(sdl)
