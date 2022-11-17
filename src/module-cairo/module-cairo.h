//==============================================================================
// module-cairo.h
//==============================================================================
#ifndef GURAX_MODULE_CAIRO_H
#define GURAX_MODULE_CAIRO_H
#include <gurax.h>
#define CAIRO_WIN32_STATIC_BUILD
#include <cairo.h>
#include <cairo-pdf.h>
#include <cairo-ps.h>
#include <cairo-script.h>
#include <cairo-svg.h>
//#include <cairo-xml.h>
#include "Util.h"
#include "Consts.h"
#include "Functions.h"
#include "VType_cairo_t.h"
#include "VType_cairo_device_t.h"
#include "VType_cairo_font_extents_t.h"
#include "VType_cairo_font_face_t.h"
#include "VType_cairo_font_options_t.h"
#include "VType_cairo_glyph_t.h"
#include "VType_cairo_matrix_t.h"
#include "VType_cairo_path_t.h"
#include "VType_cairo_pattern_t.h"
#include "VType_cairo_rectangle_t.h"
#include "VType_cairo_rectangle_int_t.h"
#include "VType_cairo_rectangle_list_t.h"
#include "VType_cairo_region_t.h"
#include "VType_cairo_scaled_font_t.h"
#include "VType_cairo_surface_t.h"
#include "VType_cairo_text_cluster_t.h"
#include "VType_cairo_text_extents_t.h"

Gurax_BeginModuleHeader(cairo)
Gurax_EndModuleHeader(cairo)

#endif
