//==============================================================================
// VType_cairo_pattern_t.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(cairo.cairo_pattern_t, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(cairo.cairo_pattern_t, `en)}

${help.ComposeMethodHelp(cairo.cairo_pattern_t, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_cairo_pattern_t
//------------------------------------------------------------------------------
VType_cairo_pattern_t VTYPE_cairo_pattern_t("cairo_pattern_t");

void VType_cairo_pattern_t::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	//Assign(Gurax_CreateMethod(cairo_pattern_t, MethodSkeleton));
	// Assignment of property
	//Assign(Gurax_CreateProperty(cairo_pattern_t, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_cairo_pattern_t
//------------------------------------------------------------------------------
VType& Value_cairo_pattern_t::vtype = VTYPE_cairo_pattern_t;

String Value_cairo_pattern_t::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "cairo.cairo_pattern_t");
}

Gurax_EndModuleScope(cairo)
