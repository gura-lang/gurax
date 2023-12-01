//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_CAIRO_UTIL_H
#define GURAX_MODULE_CAIRO_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(cairo)

cairo_status_t font_face_init_func(cairo_scaled_font_t* scaled_font, cairo_t* cr, cairo_font_extents_t* extents);
cairo_status_t font_face_render_glyph_func(cairo_scaled_font_t* scaled_font, unsigned long glyph, cairo_t* cr, cairo_text_extents_t* extents);
cairo_status_t font_face_text_to_glyphs_func(cairo_scaled_font_t* scaled_font, const char* utf8, int utf8_len,
	cairo_glyph_t** glyphs, int* num_glyphs, cairo_text_cluster_t** clusters, int* num_clusters, cairo_text_cluster_flags_t* cluster_flags);
cairo_status_t font_face_unicode_to_glyph_func(cairo_scaled_font_t* scaled_font, unsigned long  unicode, unsigned long* glyph_index);

extern RefPtr<Function> g_pFunc_font_face_init;
extern RefPtr<Function> g_pFunc_font_face_render_glyph;
extern RefPtr<Function> g_pFunc_font_face_text_to_glyphs;
extern RefPtr<Function> g_pFunc_font_face_unicode_to_glyph;

bool IsOK(cairo_status_t status);
cairo_surface_t* CreateSurfaceFromImage(Image& image, cairo_format_t format);
Image* CreateImageFromSurface(cairo_surface_t* surface, const Image::Format& formatImg);

Gurax_EndModuleScope(cairo)

#endif
