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

${help.ComposePropertyHelp(cairo.cairo_surface_t, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(cairo.cairo_surface_t, `en)}

${help.ComposeMethodHelp(cairo.cairo_surface_t, `en)}
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
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

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// cairo.cairo_surface_t#content
Gurax_DeclareProperty_R(cairo_surface_t, content)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_surface_t, content)
{
	auto& valueThis = GetValueThis(valueTarget);
	cairo_surface_t* surface = valueThis.GetEntityPtr();
	return new Value_Number(cairo_surface_get_content(surface));
}

// cairo.cairo_surface_t#type
Gurax_DeclareProperty_R(cairo_surface_t, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_surface_t, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	cairo_surface_t* surface = valueThis.GetEntityPtr();
	return new Value_Number(cairo_surface_get_type(surface));
}

// cairo.cairo_surface_t#image_format
Gurax_DeclareProperty_R(cairo_surface_t, image_format)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_surface_t, image_format)
{
	auto& valueThis = GetValueThis(valueTarget);
	cairo_surface_t* surface = valueThis.GetEntityPtr();
	if (cairo_surface_get_type(surface) != CAIRO_SURFACE_TYPE_IMAGE) return Value::nil();
	return new Value_Number(cairo_image_surface_get_format(surface));
}

// cairo.cairo_surface_t#image_width
Gurax_DeclareProperty_R(cairo_surface_t, image_width)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_surface_t, image_width)
{
	auto& valueThis = GetValueThis(valueTarget);
	cairo_surface_t* surface = valueThis.GetEntityPtr();
	if (cairo_surface_get_type(surface) != CAIRO_SURFACE_TYPE_IMAGE) return Value::nil();
	return new Value_Number(cairo_image_surface_get_width(surface));
}

// cairo.cairo_surface_t#image_height
Gurax_DeclareProperty_R(cairo_surface_t, image_height)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_surface_t, image_height)
{
	auto& valueThis = GetValueThis(valueTarget);
	cairo_surface_t* surface = valueThis.GetEntityPtr();
	if (cairo_surface_get_type(surface) != CAIRO_SURFACE_TYPE_IMAGE) return Value::nil();
	return new Value_Number(cairo_image_surface_get_height(surface));
}

// cairo.cairo_surface_t#image_stride
Gurax_DeclareProperty_R(cairo_surface_t, image_stride)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(cairo_surface_t, image_stride)
{
	auto& valueThis = GetValueThis(valueTarget);
	cairo_surface_t* surface = valueThis.GetEntityPtr();
	if (cairo_surface_get_type(surface) != CAIRO_SURFACE_TYPE_IMAGE) return Value::nil();
	return new Value_Number(cairo_image_surface_get_stride(surface));
}

//------------------------------------------------------------------------------
// VType_cairo_surface_t
//------------------------------------------------------------------------------
VType_cairo_surface_t VTYPE_cairo_surface_t("cairo_surface_t");

void VType_cairo_surface_t::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(cairo_surface_t, ToImage));
	// Assignment of property
	Assign(Gurax_CreateProperty(cairo_surface_t, content));
	Assign(Gurax_CreateProperty(cairo_surface_t, image_format));
	Assign(Gurax_CreateProperty(cairo_surface_t, image_width));
	Assign(Gurax_CreateProperty(cairo_surface_t, image_height));
	Assign(Gurax_CreateProperty(cairo_surface_t, image_stride));
	Assign(Gurax_CreateProperty(cairo_surface_t, type));
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
