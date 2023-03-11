//==============================================================================
// VType_cairo_font_face_t.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(cairo.cairo_font_face_t, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(cairo.cairo_font_face_t, `en)}

${help.ComposeMethodHelp(cairo.cairo_font_face_t, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// cairo.cairo_font_face_t#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(cairo_font_face_t, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(cairo_font_face_t, MethodSkeleton)
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
// cairo.cairo_font_face_t#propSkeleton
Gurax_DeclareProperty_R(cairo_font_face_t, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(cairo_font_face_t, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_cairo_font_face_t
//------------------------------------------------------------------------------
VType_cairo_font_face_t VTYPE_cairo_font_face_t("cairo_font_face_t");

void VType_cairo_font_face_t::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(cairo_font_face_t, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(cairo_font_face_t, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_cairo_font_face_t
//------------------------------------------------------------------------------
VType& Value_cairo_font_face_t::vtype = VTYPE_cairo_font_face_t;

String Value_cairo_font_face_t::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "cairo.cairo_font_face_t");
}

Gurax_EndModuleScope(cairo)
