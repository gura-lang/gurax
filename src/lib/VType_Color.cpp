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
// Color(r?:Number, g?:Number, b?:Number, a?:Number) {block?}
Gurax_DeclareConstructor(Color)
{
	Declare(VTYPE_DateTime, Flag::Map);
	DeclareArg("r", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("a", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(ja),
		u8"`Color` インスタンスを生成する。");
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Color` instance.");
}

Gurax_ImplementConstructor(Color)
{
	// Arguments
	ArgPicker args(argument);
	UInt8 r = args.IsValid()? args.PickNumberRanged<UInt8>(0, 255) : 0;
	UInt8 g = args.IsValid()? args.PickNumberRanged<UInt8>(0, 255) : 0;
	UInt8 b = args.IsValid()? args.PickNumberRanged<UInt8>(0, 255) : 0;
	UInt8 a = args.IsValid()? args.PickNumberRanged<UInt8>(0, 255) : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	return argument.ReturnValue(processor, new Value_Color(Color(r, g, b, a)));
}

//------------------------------------------------------------------------------
// Implementation of class method
//------------------------------------------------------------------------------
// Color.Named(name:String, a?:Number)
Gurax_DeclareClassMethod(Color, Named)
{
	Declare(VTYPE_Color, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethod(Color, Named)
{
	// Function body
	return Value::nil();
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
	Assign("zero", new Value_Color(Color::zero));
	Assign("black", new Value_Color(Color::black));
	Assign("maroon", new Value_Color(Color::maroon));
	Assign("green", new Value_Color(Color::green));
	Assign("olive", new Value_Color(Color::olive));
	Assign("navy", new Value_Color(Color::navy));
	Assign("purple", new Value_Color(Color::purple));
	Assign("teal", new Value_Color(Color::teal));
	Assign("gray", new Value_Color(Color::gray));
	Assign("silver", new Value_Color(Color::silver));
	Assign("red", new Value_Color(Color::red));
	Assign("lime", new Value_Color(Color::lime));
	Assign("yellow", new Value_Color(Color::yellow));
	Assign("blue", new Value_Color(Color::blue));
	Assign("fuchsia", new Value_Color(Color::fuchsia));
	Assign("aqua", new Value_Color(Color::aqua));
	Assign("white", new Value_Color(Color::white));
	// Assignment of class method
	Assign(Gurax_CreateClassMethod(Color, Named));
	// Assignment of property
	Assign(Gurax_CreateProperty(Color, r));
	Assign(Gurax_CreateProperty(Color, g));
	Assign(Gurax_CreateProperty(Color, b));
	Assign(Gurax_CreateProperty(Color, a));
}

//------------------------------------------------------------------------------
// Value_Color
//------------------------------------------------------------------------------
VType& Value_Color::vtype = VTYPE_Color;

}
