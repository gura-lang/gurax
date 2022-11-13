//==============================================================================
// VType_cairo_scaled_font_t.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(cairo.cairo_scaled_font_t, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(cairo.cairo_scaled_font_t, `en)}

${help.ComposeMethodHelp(cairo.cairo_scaled_font_t, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// cairo.cairo_scaled_font_t#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(cairo_scaled_font_t, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(cairo_scaled_font_t, MethodSkeleton)
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
// cairo.cairo_scaled_font_t#propSkeleton
Gurax_DeclareProperty_R(cairo_scaled_font_t, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_scaled_font_t, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_cairo_scaled_font_t
//------------------------------------------------------------------------------
VType_cairo_scaled_font_t VTYPE_cairo_scaled_font_t("cairo_scaled_font_t");

void VType_cairo_scaled_font_t::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(cairo_scaled_font_t, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(cairo_scaled_font_t, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_cairo_scaled_font_t
//------------------------------------------------------------------------------
VType& Value_cairo_scaled_font_t::vtype = VTYPE_cairo_scaled_font_t;

String Value_cairo_scaled_font_t::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "cairo.cairo_scaled_font_t");
}

Gurax_EndModuleScope(cairo)
