//==============================================================================
// VType_Color.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

The `Color` class provides a structure to represent color data that consists of red, blue, green and alpha elements.

${help.ComposePropertyHelp(Color, `en)}

- `Color.zero` as `Color` (read only) ... 
- `Color.black` as `Color` (read only) ... 
- `Color.silver` as `Color` (read only) ... 
- `Color.gray` as `Color` (read only) ... 
- `Color.white` as `Color` (read only) ... 
- `Color.maroon` as `Color` (read only) ... 
- `Color.red` as `Color` (read only) ... 
- `Color.purple` as `Color` (read only) ... 
- `Color.fuchsia` as `Color` (read only) ... 
- `Color.green` as `Color` (read only) ... 
- `Color.lime` as `Color` (read only) ... 
- `Color.olive` as `Color` (read only) ... 
- `Color.yellow` as `Color` (read only) ... 
- `Color.navy` as `Color` (read only) ... 
- `Color.blue` as `Color` (read only) ... 
- `Color.teal` as `Color` (read only) ... 
- `Color.aqua` as `Color` (read only) ... 


# Cast Operation

- `String as Color` ... Creates a `Color` that has a name specified by `String`.
- `Expr as Color` ... Creates a `Color` that has a name specified by `Expr`.


${help.ComposeConstructorHelp(Color, `en)}

${help.ComposeMethodHelp(Color, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Color(name:String, alpha? as Number) {block?}
Gurax_DeclareConstructor(Color)
{
	Declare(VTYPE_Color, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `Color` instance from a color name specified by the argument `name`.
The color names are defined by W3C (www.w3.org).
The argument `alpha` specifies the alpha value between 0 and 255.
It will be 255 if omitted.
)**");
}

Gurax_ImplementConstructor(Color)
{
	// Arguments
	ArgPicker args(argument);
	const char* name = args.PickString();
	UInt8 alpha = args.IsValid()? args.PickNumberRanged<UInt8>(0, 255) : 255;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	Color color;
	if (!Color::FromString(color, name, alpha)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Color(color));
}

//------------------------------------------------------------------------------
// Implementation of class method
//------------------------------------------------------------------------------
// Color.RGB(r as Number, g as Number, b as Number) {block?}
Gurax_DeclareClassMethod(Color, RGB)
{
	Declare(VTYPE_Color, Flag::Map);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `Color` instance from the arguments `r` for red, `g` for green, and `b` for blue of color elements,
each of which ranges between 0 and 255.
)**");
}

Gurax_ImplementClassMethod(Color, RGB)
{
	// Arguments
	ArgPicker args(argument);
	UInt8 r = args.PickNumberRanged<UInt8>(0, 255);
	UInt8 g = args.PickNumberRanged<UInt8>(0, 255);
	UInt8 b = args.PickNumberRanged<UInt8>(0, 255);
	if (Error::IsIssued()) return Value::nil();
	// Function body
	return argument.ReturnValue(processor, new Value_Color(Color(r, g, b)));
}

// Color.RGBA(r as Number, g as Number, b as Number, a as Number) {block?}
Gurax_DeclareClassMethod(Color, RGBA)
{
	Declare(VTYPE_Color, Flag::Map);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("a", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `Color` instance from the arguments `r` for red, `g` for green, `b` for blue, and `a` for alpha of color elements,
each of which ranges between 0 and 255.
)**");
}

Gurax_ImplementClassMethod(Color, RGBA)
{
	// Arguments
	ArgPicker args(argument);
	UInt8 r = args.PickNumberRanged<UInt8>(0, 255);
	UInt8 g = args.PickNumberRanged<UInt8>(0, 255);
	UInt8 b = args.PickNumberRanged<UInt8>(0, 255);
	UInt8 a = args.PickNumberRanged<UInt8>(0, 255);
	if (Error::IsIssued()) return Value::nil();
	// Function body
	return argument.ReturnValue(processor, new Value_Color(Color(r, g, b, a)));
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// Color#GrayScale() {block?}
Gurax_DeclareMethod(Color, GrayScale)
{
	Declare(VTYPE_Color, Flag::Map);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Converts the color to gray-scaled one.
)**");
}

Gurax_ImplementMethod(Color, GrayScale)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return argument.ReturnValue(processor, new Value_Color(valueThis.GetColor().GrayScale()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Color#r
Gurax_DeclareProperty_RW(Color, r)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The red element of the color ranging between 0 and 255.
)**");
}

Gurax_ImplementPropertyGetter(Color, r)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetColor().GetR());
}

Gurax_ImplementPropertySetter(Color, r)
{
	auto& valueThis = GetValueThis(valueTarget);
	UInt8 r = Value_Number::GetNumberRanged<UInt8>(value, 0, 255);
	if (Error::IsIssued()) return;
	valueThis.GetColor().SetR(r);
}

// Color#g
Gurax_DeclareProperty_RW(Color, g)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The green element of the color ranging between 0 and 255.
)**");
}

Gurax_ImplementPropertyGetter(Color, g)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetColor().GetG());
}

Gurax_ImplementPropertySetter(Color, g)
{
	auto& valueThis = GetValueThis(valueTarget);
	UInt8 g = Value_Number::GetNumberRanged<UInt8>(value, 0, 255);
	if (Error::IsIssued()) return;
	valueThis.GetColor().SetG(g);
}

// Color#b
Gurax_DeclareProperty_RW(Color, b)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The green element of the color ranging between 0 and 255.
)**");
}

Gurax_ImplementPropertyGetter(Color, b)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetColor().GetB());
}

Gurax_ImplementPropertySetter(Color, b)
{
	auto& valueThis = GetValueThis(valueTarget);
	UInt8 b = Value_Number::GetNumberRanged<UInt8>(value, 0, 255);
	if (Error::IsIssued()) return;
	valueThis.GetColor().SetB(b);
}

// Color#a
Gurax_DeclareProperty_RW(Color, a)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The alpha element of the color ranging between 0 and 255.
)**");
}

Gurax_ImplementPropertyGetter(Color, a)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetColor().GetA());
}


Gurax_ImplementPropertySetter(Color, a)
{
	auto& valueThis = GetValueThis(valueTarget);
	UInt8 a = Value_Number::GetNumberRanged<UInt8>(value, 0, 255);
	if (Error::IsIssued()) return;
	valueThis.GetColor().SetA(a);
}

// Color#grayScale
Gurax_DeclareProperty_R(Color, grayScale)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The gray-scaled number the color ranging between 0 and 255.
)**");
}

Gurax_ImplementPropertyGetter(Color, grayScale)
{
	// Target
	auto& valueThis = GetValueThis(valueTarget);
	// Function body
	return new Value_Number(valueThis.GetColor().CalcGray());
}

//------------------------------------------------------------------------------
// VType_Color
//------------------------------------------------------------------------------
VType_Color VTYPE_Color("Color");

void VType_Color::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Color));
	// Assignment of class value
	Assign("zero",		new Value_Color(Color::zero));
	Assign("black",		new Value_Color(Color::black));
	Assign("silver",	new Value_Color(Color::silver));
	Assign("gray",		new Value_Color(Color::gray));
	Assign("white",		new Value_Color(Color::white));
	Assign("maroon",	new Value_Color(Color::maroon));
	Assign("red",		new Value_Color(Color::red));
	Assign("purple",	new Value_Color(Color::purple));
	Assign("fuchsia",	new Value_Color(Color::fuchsia));
	Assign("green",		new Value_Color(Color::green));
	Assign("lime",		new Value_Color(Color::lime));
	Assign("olive",		new Value_Color(Color::olive));
	Assign("yellow",	new Value_Color(Color::yellow));
	Assign("navy",		new Value_Color(Color::navy));
	Assign("blue",		new Value_Color(Color::blue));
	Assign("teal",		new Value_Color(Color::teal));
	Assign("aqua",		new Value_Color(Color::aqua));
	// Assignment of class method
	Assign(Gurax_CreateClassMethod(Color, RGB));
	Assign(Gurax_CreateClassMethod(Color, RGBA));
	// Assignment of method
	Assign(Gurax_CreateMethod(Color, GrayScale));
	// Assignment of property
	Assign(Gurax_CreateProperty(Color, r));
	Assign(Gurax_CreateProperty(Color, g));
	Assign(Gurax_CreateProperty(Color, b));
	Assign(Gurax_CreateProperty(Color, a));
	Assign(Gurax_CreateProperty(Color, grayScale));
}

Value* VType_Color::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_String)) {
		const char* name = Value_String::GetString(value);
		Color color;
		if (!Color::FromString(color, name, 255)) return nullptr;
		return new Value_Color(color);
	} else if (value.IsType(VTYPE_Expr)) {
		const Symbol* pSymbol = Value_Expr::GetExpr(value).GetPureSymbol();
		if (!pSymbol) return nullptr;
		const Color* pColor = Color::Lookup(pSymbol);
		if (!pColor) {
			Error::Issue(ErrorType::KeyError, "unknown color symbol: `%s", pSymbol->GetName());
			return nullptr;
		}
		return new Value_Color(*pColor);
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Color
//------------------------------------------------------------------------------
VType& Value_Color::vtype = VTYPE_Color;

String Value_Color::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetColor().ToString(ss));
}

}
