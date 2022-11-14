//==============================================================================
// VType_cairo_glyph_t.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(cairo.cairo_glyph_t, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(cairo.cairo_glyph_t, `en)}

${help.ComposeMethodHelp(cairo.cairo_glyph_t, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// cairo.cairo_glyph_t#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(cairo_glyph_t, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(cairo_glyph_t, MethodSkeleton)
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
// cairo.cairo_glyph_t#index
Gurax_DeclareProperty_RW(cairo_glyph_t, index)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_glyph_t, index)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().index);
}

Gurax_ImplementPropertySetter(cairo_glyph_t, index)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().index = Value_Number::GetNumber<unsigned long>(value);
}

// cairo.cairo_glyph_t#x
Gurax_DeclareProperty_RW(cairo_glyph_t, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_glyph_t, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().x);
}

Gurax_ImplementPropertySetter(cairo_glyph_t, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().x = Value_Number::GetNumber<double>(value);
}

// cairo.cairo_glyph_t#y
Gurax_DeclareProperty_RW(cairo_glyph_t, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_glyph_t, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().y);
}

Gurax_ImplementPropertySetter(cairo_glyph_t, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().y = Value_Number::GetNumber<double>(value);
}

//------------------------------------------------------------------------------
// VType_cairo_glyph_t
//------------------------------------------------------------------------------
VType_cairo_glyph_t VTYPE_cairo_glyph_t("cairo_glyph_t");

void VType_cairo_glyph_t::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(cairo_glyph_t, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(cairo_glyph_t, index));
	Assign(Gurax_CreateProperty(cairo_glyph_t, x));
	Assign(Gurax_CreateProperty(cairo_glyph_t, y));
}

//------------------------------------------------------------------------------
// Value_cairo_glyph_t
//------------------------------------------------------------------------------
VType& Value_cairo_glyph_t::vtype = VTYPE_cairo_glyph_t;

String Value_cairo_glyph_t::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "cairo.cairo_glyph_t");
}

Gurax_EndModuleScope(cairo)
