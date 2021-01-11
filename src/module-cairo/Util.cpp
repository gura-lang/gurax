//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

bool IsOK(cairo_status_t status)
{
	if (status == CAIRO_STATUS_SUCCESS) return true;
	Error::Issue(ErrorType::GuestError, "%s", cairo_status_to_string(status));
	return false;
}

#if 0
cairo_surface_t* CreateSurfaceFromImage(Image& image, cairo_format_t format)
{
	unsigned char* data = image.GetPointerC();
	cairo_format_t format;
	int width, height, stride;
	return cairo_image_surface_create_for_data(data, format, width, height, stride);
}

Image* CreateImageFromSurface(cairo_surface_t* surface)
{
}
#endif

Gurax_EndModuleScope(cairo)
