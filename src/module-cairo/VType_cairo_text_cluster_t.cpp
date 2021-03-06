//==============================================================================
// VType_cairo_text_cluster_t.cpp
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

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// cairo.cairo_text_cluster_t#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(cairo_text_cluster_t, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(cairo_text_cluster_t, MethodSkeleton)
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
// cairo.cairo_text_cluster_t#num_bytes
Gurax_DeclareProperty_RW(cairo_text_cluster_t, num_bytes)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(cairo_text_cluster_t, num_bytes)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().num_bytes);
}

Gurax_ImplementPropertySetter(cairo_text_cluster_t, num_bytes)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().num_bytes = Value_Number::GetNumber<int>(value);
}

// cairo.cairo_text_cluster_t#num_glyphs
Gurax_DeclareProperty_RW(cairo_text_cluster_t, num_glyphs)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(cairo_text_cluster_t, num_glyphs)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().num_glyphs);
}

Gurax_ImplementPropertySetter(cairo_text_cluster_t, num_glyphs)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().num_glyphs = Value_Number::GetNumber<int>(value);
}

//------------------------------------------------------------------------------
// VType_cairo_text_cluster_t
//------------------------------------------------------------------------------
VType_cairo_text_cluster_t VTYPE_cairo_text_cluster_t("cairo_text_cluster_t");

void VType_cairo_text_cluster_t::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(cairo_text_cluster_t, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(cairo_text_cluster_t, num_bytes));
	Assign(Gurax_CreateProperty(cairo_text_cluster_t, num_glyphs));
}

//------------------------------------------------------------------------------
// Value_cairo_text_cluster_t
//------------------------------------------------------------------------------
VType& Value_cairo_text_cluster_t::vtype = VTYPE_cairo_text_cluster_t;

String Value_cairo_text_cluster_t::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "cairo.cairo_text_cluster_t");
}

Gurax_EndModuleScope(cairo)
