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
	Declare(VTYPE_Image, Flag::None);
	//DeclareArg("image", VTYPE_Image, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunction(Test)
{
	// Arguments
	ArgPicker args(argument);
	//Image& image = args.PickImage();
	// Function body
	RefPtr<Image> pImage(new Image(Image::Format::RGBA));
	if (!pImage->Allocate(100, 100)) {
		return Value::nil();
	}
	return new Value_Image(pImage.release());
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
	Assign(VTYPE_cairo_rectangle_list_t);
	Assign(VTYPE_cairo_region_t);
	Assign(VTYPE_cairo_scaled_font_t);
	Assign(VTYPE_cairo_surface_t);
	Assign(VTYPE_cairo_text_cluster_t);
	Assign(VTYPE_cairo_text_extents_t);
	// Assignment of function
	//Assign(Gurax_CreateFunction(Test));
	AssignFunctions(GetFrame());
	// Assignment of value
	AssignConsts(GetFrame());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(cairo)
