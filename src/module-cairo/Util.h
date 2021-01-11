//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_CAIRO_UTIL_H
#define GURAX_MODULE_CAIRO_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(cairo)

bool IsOK(cairo_status_t status);
cairo_surface_t* CreateSurfaceFromImage(Image& image);

Gurax_EndModuleScope(cairo)

#endif
