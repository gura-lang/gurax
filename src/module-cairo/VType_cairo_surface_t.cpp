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
// cairo.cairo_surface_t#ToImage()
Gurax_DeclareMethod(cairo_surface_t, ToImage)
{
	Declare(VTYPE_Image, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(rgb));
	DeclareAttrOpt(Gurax_Symbol(rgba));
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(cairo_surface_t, ToImage)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	cairo_surface_t* surface = valueThis.GetEntityPtr();
	// Arguments
	ArgPicker args(argument);
	const Image::Format& format =
		argument.IsSet(Gurax_Symbol(rgb))? Image::Format::RGB : Image::Format::RGBA;
	// Function body
	RefPtr<Image> pImage(CreateImageFromSurface(surface, format));
	if (!pImage) return Value::nil();
	return new Value_Image(pImage.release());
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
	Assign(Gurax_CreateMethod(cairo_surface_t, ToImage));
}

//------------------------------------------------------------------------------
// Value_cairo_surface_t
//------------------------------------------------------------------------------
VType& Value_cairo_surface_t::vtype = VTYPE_cairo_surface_t;

String Value_cairo_surface_t::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "cairo.cairo_surface_t");
}

Gurax_EndModuleScope(cairo)
