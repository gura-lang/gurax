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

The `Color` class provides a structure to represent color data that consists
of red, blue, green and alpha elements.

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
// Color(name:String, alpha?:Number) {block?}
Gurax_DeclareConstructor(Color)
{
	Declare(VTYPE_Color, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Color` instance by looking up a registered table by a name.\n"
		"The argument `alpha` specifies the alpha value of the created color\n"
		"and takes 255 if omitted.\n");
}

Gurax_ImplementConstructor(Color)
{
	// Arguments
	ArgPicker args(argument);
	const char* name = args.PickString();
	bool validFlag_alpha = false;
	UInt8 alpha = (validFlag_alpha = args.IsValid())? args.PickNumberRanged<UInt8>(0, 255) : 255;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const Color* pColor = Color::Lookup(name);
	if (!pColor) {
		Error::Issue(ErrorType::KeyError, "unknown color name");
		return Value::nil();
	}
	Color color(*pColor);
	if (validFlag_alpha) color.SetA(alpha);
	return argument.ReturnValue(processor, new Value_Color(color));
}

//------------------------------------------------------------------------------
// Implementation of class method
//------------------------------------------------------------------------------
// Color.RGB(r:Number, g:Number, b:Number) {block?}
Gurax_DeclareClassMethod(Color, RGB)
{
	Declare(VTYPE_Color, Flag::Map);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Color` instance from red, green and blue elements of color,\n"
		"each of which ranges between 0 and 255.\n");
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

// Color.RGBA(r:Number, g:Number, b:Number, a:Number) {block?}
Gurax_DeclareClassMethod(Color, RGBA)
{
	Declare(VTYPE_Color, Flag::Map);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("a", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Color` instance from red, green, blue and alpha elements of color,\n"
		"each of which ranges between 0 and 255.\n");
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
	AddHelp(
		Gurax_Symbol(en),
		"Converts the color to gray-scaled one.\n");
}

Gurax_ImplementMethod(Color, GrayScale)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return argument.ReturnValue(processor, new Value_Color(valueThis.GetColor().GrayScale()));
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// Color#r
Gurax_DeclareProperty_RW(Color, r)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Value of the red element.");
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
	AddHelp(
		Gurax_Symbol(en),
		"Value of the green element.");
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
	AddHelp(
		Gurax_Symbol(en),
		"Value of the blue element.");
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
	AddHelp(
		Gurax_Symbol(en),
		"Value of the alpha element.");
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

//------------------------------------------------------------------------------
// VType_Color
//------------------------------------------------------------------------------
VType_Color VTYPE_Color("Color");

void VType_Color::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
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
}

Value* VType_Color::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_String)) {
		const char* name = Value_String::GetString(value);
		const Color* pColor = Color::Lookup(name);
		if (!pColor) {
			Error::Issue(ErrorType::KeyError, "unknown color name");
			return nullptr;
		}
		return new Value_Color(*pColor);
	} else if (value.IsType(VTYPE_Expr)) {
		const Symbol* pSymbol = Value_Expr::GetExpr(value).GetPureSymbol();
		if (!pSymbol) return nullptr;
		const Color* pColor = Color::Lookup(pSymbol);
		if (!pColor) {
			Error::Issue(ErrorType::KeyError, "unknown color symbol");
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

}
