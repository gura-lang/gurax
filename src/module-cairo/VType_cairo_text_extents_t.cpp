//==============================================================================
// VType_cairo_text_extents_t.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(cairo.cairo_text_extents_t, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(cairo.cairo_text_extents_t, `en)}

${help.ComposeMethodHelp(cairo.cairo_text_extents_t, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// cairo_text_extents_t() {block?}
Gurax_DeclareConstructor(cairo_text_extents_t)
{
	Declare(VTYPE_cairo_text_extents_t, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `cairo_text_extents_t` instance.
)**");
}

Gurax_ImplementConstructor(cairo_text_extents_t)
{
	// Arguments
	ArgPicker args(argument);
	cairo_text_extents_t extents {};
	// Function body
	return argument.ReturnValue(processor, new Value_cairo_text_extents_t(extents));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// cairo.cairo_text_extents_t#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(cairo_text_extents_t, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(cairo_text_extents_t, MethodSkeleton)
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
// cairo.cairo_text_extents_t#x_bearing
Gurax_DeclareProperty_RW(cairo_text_extents_t, x_bearing)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_text_extents_t, x_bearing)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().x_bearing);
}

Gurax_ImplementPropertySetter(cairo_text_extents_t, x_bearing)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().x_bearing = Value_Number::GetNumber<double>(value);
}

// cairo.cairo_text_extents_t#y_bearing
Gurax_DeclareProperty_RW(cairo_text_extents_t, y_bearing)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_text_extents_t, y_bearing)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().y_bearing);
}

Gurax_ImplementPropertySetter(cairo_text_extents_t, y_bearing)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().y_bearing = Value_Number::GetNumber<double>(value);
}

// cairo.cairo_text_extents_t#width
Gurax_DeclareProperty_RW(cairo_text_extents_t, width)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_text_extents_t, width)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().width);
}

Gurax_ImplementPropertySetter(cairo_text_extents_t, width)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().width = Value_Number::GetNumber<double>(value);
}

// cairo.cairo_text_extents_t#height
Gurax_DeclareProperty_RW(cairo_text_extents_t, height)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_text_extents_t, height)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().height);
}

Gurax_ImplementPropertySetter(cairo_text_extents_t, height)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().height = Value_Number::GetNumber<double>(value);
}

// cairo.cairo_text_extents_t#x_advance
Gurax_DeclareProperty_RW(cairo_text_extents_t, x_advance)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_text_extents_t, x_advance)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().x_advance);
}

Gurax_ImplementPropertySetter(cairo_text_extents_t, x_advance)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().x_advance = Value_Number::GetNumber<double>(value);
}

// cairo.cairo_text_extents_t#y_advance
Gurax_DeclareProperty_RW(cairo_text_extents_t, y_advance)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_text_extents_t, y_advance)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().y_advance);
}

Gurax_ImplementPropertySetter(cairo_text_extents_t, y_advance)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().y_advance = Value_Number::GetNumber<double>(value);
}

//------------------------------------------------------------------------------
// VType_cairo_text_extents_t
//------------------------------------------------------------------------------
VType_cairo_text_extents_t VTYPE_cairo_text_extents_t("cairo_text_extents_t");

void VType_cairo_text_extents_t::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(cairo_text_extents_t));
	// Assignment of method
	Assign(Gurax_CreateMethod(cairo_text_extents_t, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(cairo_text_extents_t, x_bearing));
	Assign(Gurax_CreateProperty(cairo_text_extents_t, y_bearing));
	Assign(Gurax_CreateProperty(cairo_text_extents_t, width));
	Assign(Gurax_CreateProperty(cairo_text_extents_t, height));
	Assign(Gurax_CreateProperty(cairo_text_extents_t, x_advance));
	Assign(Gurax_CreateProperty(cairo_text_extents_t, y_advance));
}

//------------------------------------------------------------------------------
// Value_cairo_text_extents_t
//------------------------------------------------------------------------------
VType& Value_cairo_text_extents_t::vtype = VTYPE_cairo_text_extents_t;

String Value_cairo_text_extents_t::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "cairo.cairo_text_extents_t");
}

Gurax_EndModuleScope(cairo)
