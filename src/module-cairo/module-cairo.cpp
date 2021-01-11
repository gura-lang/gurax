//==============================================================================
// module-cairo.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(cairo)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// cairo.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(Test)
{
	cairo_surface_t *surface;
	cairo_t *cr;

	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 390, 60);
	cr = cairo_create(surface);

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
		CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 40.0);

	cairo_move_to(cr, 10.0, 50.0);
	cairo_show_text(cr, "hoge Disziplin ist Macht.");

	cairo_surface_write_to_png(surface, "image.png");

	cairo_destroy(cr);
	cairo_surface_destroy(surface);

	return Value::nil();
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Assignment of VType
	Assign(VTYPE_cairo_t);
	Assign(VTYPE_cairo_device_t);
	Assign(VTYPE_cairo_font_extents_t);
	Assign(VTYPE_cairo_font_face_t);
	Assign(VTYPE_cairo_font_options_t);
	Assign(VTYPE_cairo_glyph_t);
	Assign(VTYPE_cairo_matrix_t);
	Assign(VTYPE_cairo_path_t);
	Assign(VTYPE_cairo_pattern_t);
	Assign(VTYPE_cairo_rectangle_t);
	Assign(VTYPE_cairo_rectangle_int_t);
	Assign(VTYPE_cairo_region_t);
	Assign(VTYPE_cairo_scaled_font_t);
	Assign(VTYPE_cairo_surface_t);
	Assign(VTYPE_cairo_text_cluster_t);
	Assign(VTYPE_cairo_text_extents_t);
	// Assignment of function
	Assign(Gurax_CreateFunction(Test));
	AssignFunctions(GetFrame());
	// Assignment of value
	AssignConsts(GetFrame());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(cairo)
