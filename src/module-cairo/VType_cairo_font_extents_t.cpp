//==============================================================================
// VType_cairo_font_extents_t.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

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
// cairo_font_extents_t() {block?}
Gurax_DeclareConstructor(cairo_font_extents_t)
{
	Declare(VTYPE_cairo_font_extents_t, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `cairo_font_extents_t` instance.\n");
}

Gurax_ImplementConstructor(cairo_font_extents_t)
{
	// Arguments
	ArgPicker args(argument);
	cairo_font_extents_t extents {};
	// Function body
	return argument.ReturnValue(processor, new Value_cairo_font_extents_t(extents));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// cairo.cairo_font_extents_t#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(cairo_font_extents_t, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(cairo_font_extents_t, MethodSkeleton)
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
// cairo.cairo_font_extents_t#ascent
Gurax_DeclareProperty_RW(cairo_font_extents_t, ascent)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(cairo_font_extents_t, ascent)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().ascent);
}

Gurax_ImplementPropertySetter(cairo_font_extents_t, ascent)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().ascent = Value_Number::GetNumber<double>(value);
}

// cairo.cairo_font_extents_t#descent
Gurax_DeclareProperty_RW(cairo_font_extents_t, descent)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(cairo_font_extents_t, descent)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().descent);
}

Gurax_ImplementPropertySetter(cairo_font_extents_t, descent)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().descent = Value_Number::GetNumber<double>(value);
}

// cairo.cairo_font_extents_t#height
Gurax_DeclareProperty_RW(cairo_font_extents_t, height)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(cairo_font_extents_t, height)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().height);
}

Gurax_ImplementPropertySetter(cairo_font_extents_t, height)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().height = Value_Number::GetNumber<double>(value);
}

// cairo.cairo_font_extents_t#max_x_advance
Gurax_DeclareProperty_RW(cairo_font_extents_t, max_x_advance)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(cairo_font_extents_t, max_x_advance)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().max_x_advance);
}

Gurax_ImplementPropertySetter(cairo_font_extents_t, max_x_advance)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().max_x_advance = Value_Number::GetNumber<double>(value);
}

// cairo.cairo_font_extents_t#max_y_advance
Gurax_DeclareProperty_RW(cairo_font_extents_t, max_y_advance)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(cairo_font_extents_t, max_y_advance)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().max_y_advance);
}

Gurax_ImplementPropertySetter(cairo_font_extents_t, max_y_advance)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().max_y_advance = Value_Number::GetNumber<double>(value);
}

//------------------------------------------------------------------------------
// VType_cairo_font_extents_t
//------------------------------------------------------------------------------
VType_cairo_font_extents_t VTYPE_cairo_font_extents_t("cairo_font_extents_t");

void VType_cairo_font_extents_t::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(cairo_font_extents_t));
	// Assignment of method
	Assign(Gurax_CreateMethod(cairo_font_extents_t, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(cairo_font_extents_t, ascent));
	Assign(Gurax_CreateProperty(cairo_font_extents_t, descent));
	Assign(Gurax_CreateProperty(cairo_font_extents_t, height));
	Assign(Gurax_CreateProperty(cairo_font_extents_t, max_x_advance));
	Assign(Gurax_CreateProperty(cairo_font_extents_t, max_y_advance));
}

//------------------------------------------------------------------------------
// Value_cairo_font_extents_t
//------------------------------------------------------------------------------
VType& Value_cairo_font_extents_t::vtype = VTYPE_cairo_font_extents_t;

String Value_cairo_font_extents_t::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "cairo.cairo_font_extents_t");
}

Gurax_EndModuleScope(cairo)
