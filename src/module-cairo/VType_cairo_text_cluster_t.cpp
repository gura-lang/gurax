//==============================================================================
// VType_cairo_text_cluster_t.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(cairo.cairo_text_cluster_t, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(cairo.cairo_text_cluster_t, `en)}

${help.ComposeMethodHelp(cairo.cairo_text_cluster_t, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// cairo.cairo_text_cluster_t#num_bytes
Gurax_DeclareProperty_RW(cairo_text_cluster_t, num_bytes)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
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
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	//Assign(Gurax_CreateMethod(cairo_text_cluster_t, MethodSkeleton));
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
