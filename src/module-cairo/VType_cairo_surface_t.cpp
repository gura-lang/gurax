//==============================================================================
// VType_cairo_surface_t.cpp
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
// cairo.cairo_surface_t#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(cairo_surface_t, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(cairo_surface_t, MethodSkeleton)
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
// cairo.cairo_surface_t#propSkeleton
Gurax_DeclareProperty_R(cairo_surface_t, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(cairo_surface_t, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_cairo_surface_t
//------------------------------------------------------------------------------
VType_cairo_surface_t VTYPE_cairo_surface_t("cairo_surface_t");

void VType_cairo_surface_t::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(cairo_surface_t, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(cairo_surface_t, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_cairo_surface_t
//------------------------------------------------------------------------------
VType& Value_cairo_surface_t::vtype = VTYPE_cairo_surface_t;

String Value_cairo_surface_t::ToString(const StringStyle& ss) const
{
	return "cairo.cairo_surface_t";
}

Gurax_EndModuleScope(cairo)