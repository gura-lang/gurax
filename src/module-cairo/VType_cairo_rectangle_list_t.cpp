//==============================================================================
// VType_cairo_rectangle_list_t.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(cairo.cairo_rectangle_list_t, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(cairo.cairo_rectangle_list_t, `en)}

${help.ComposeMethodHelp(cairo.cairo_rectangle_list_t, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// cairo.cairo_rectangle_list_t#status
Gurax_DeclareProperty_R(cairo_rectangle_list_t, status)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(cairo_rectangle_list_t, status)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().status);
}

// cairo.cairo_rectangle_list_t#rectangles
Gurax_DeclareProperty_R(cairo_rectangle_list_t, rectangles)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(cairo_rectangle_list_t, rectangles)
{
	//**************************************************************************
	//auto& valueThis = GetValueThis(valueTarget);
	//return new Value_Number(valueThis.GetEntity().rectangles);
	return Value::nil();
}

// cairo.cairo_rectangle_list_t#num_rectangles
Gurax_DeclareProperty_R(cairo_rectangle_list_t, num_rectangles)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(cairo_rectangle_list_t, num_rectangles)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().num_rectangles);
}

//------------------------------------------------------------------------------
// VType_cairo_rectangle_list_t
//------------------------------------------------------------------------------
VType_cairo_rectangle_list_t VTYPE_cairo_rectangle_list_t("cairo_rectangle_list_t");

void VType_cairo_rectangle_list_t::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	//Assign(Gurax_CreateMethod(cairo_rectangle_list_t, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(cairo_rectangle_list_t, status));
	Assign(Gurax_CreateProperty(cairo_rectangle_list_t, rectangles));
	Assign(Gurax_CreateProperty(cairo_rectangle_list_t, num_rectangles));
}

//------------------------------------------------------------------------------
// Value_cairo_rectangle_list_t
//------------------------------------------------------------------------------
VType& Value_cairo_rectangle_list_t::vtype = VTYPE_cairo_rectangle_list_t;

String Value_cairo_rectangle_list_t::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "cairo.cairo_rectangle_list_t");
}

Gurax_EndModuleScope(cairo)
