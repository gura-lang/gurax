//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_CAIRO_UTIL_H
#define GURAX_MODULE_CAIRO_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(cairo)

bool IsOK(cairo_status_t status);
cairo_surface_t* CreateSurfaceFromImage(Image& image);
Image* CreateImageFromSurface(cairo_surface_t* surface);

Gurax_EndModuleScope(cairo)

#endif
