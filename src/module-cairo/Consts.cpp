//==============================================================================
// Consts.cpp
//==============================================================================
#include "stdafx.h"

#define AssignNumber(name) frame.Assign(#name, new Value_Number(name))
#define AssignString(name) frame.Assign(#name, new Value_String(name))

Gurax_BeginModuleScope(cairo)

void AssignConsts(Frame& frame)
{
	// cairo_status_t
	AssignNumber(CAIRO_STATUS_SUCCESS);
	AssignNumber(CAIRO_STATUS_NO_MEMORY);
	AssignNumber(CAIRO_STATUS_INVALID_RESTORE);
	AssignNumber(CAIRO_STATUS_INVALID_POP_GROUP);
	AssignNumber(CAIRO_STATUS_NO_CURRENT_POINT);
	AssignNumber(CAIRO_STATUS_INVALID_MATRIX);
	AssignNumber(CAIRO_STATUS_INVALID_STATUS);
	AssignNumber(CAIRO_STATUS_NULL_POINTER);
	AssignNumber(CAIRO_STATUS_INVALID_STRING);
	AssignNumber(CAIRO_STATUS_INVALID_PATH_DATA);
	AssignNumber(CAIRO_STATUS_READ_ERROR);
	AssignNumber(CAIRO_STATUS_WRITE_ERROR);
	AssignNumber(CAIRO_STATUS_SURFACE_FINISHED);
	AssignNumber(CAIRO_STATUS_SURFACE_TYPE_MISMATCH);
	AssignNumber(CAIRO_STATUS_PATTERN_TYPE_MISMATCH);
	AssignNumber(CAIRO_STATUS_INVALID_CONTENT);
	AssignNumber(CAIRO_STATUS_INVALID_FORMAT);
	AssignNumber(CAIRO_STATUS_INVALID_VISUAL);
	AssignNumber(CAIRO_STATUS_FILE_NOT_FOUND);
	AssignNumber(CAIRO_STATUS_INVALID_DASH);
	AssignNumber(CAIRO_STATUS_INVALID_DSC_COMMENT);
	AssignNumber(CAIRO_STATUS_INVALID_INDEX);
	AssignNumber(CAIRO_STATUS_CLIP_NOT_REPRESENTABLE);
	AssignNumber(CAIRO_STATUS_TEMP_FILE_ERROR);
	AssignNumber(CAIRO_STATUS_INVALID_STRIDE);
	AssignNumber(CAIRO_STATUS_FONT_TYPE_MISMATCH);
	AssignNumber(CAIRO_STATUS_USER_FONT_IMMUTABLE);
	AssignNumber(CAIRO_STATUS_USER_FONT_ERROR);
	AssignNumber(CAIRO_STATUS_NEGATIVE_COUNT);
	AssignNumber(CAIRO_STATUS_INVALID_CLUSTERS);
	AssignNumber(CAIRO_STATUS_INVALID_SLANT);
	AssignNumber(CAIRO_STATUS_INVALID_WEIGHT);
	AssignNumber(CAIRO_STATUS_INVALID_SIZE);
	AssignNumber(CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED);
	AssignNumber(CAIRO_STATUS_DEVICE_TYPE_MISMATCH);
	AssignNumber(CAIRO_STATUS_DEVICE_ERROR);
	AssignNumber(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	AssignNumber(CAIRO_STATUS_DEVICE_FINISHED);
	AssignNumber(CAIRO_STATUS_JBIG2_GLOBAL_MISSING);
	AssignNumber(CAIRO_STATUS_PNG_ERROR);
	AssignNumber(CAIRO_STATUS_FREETYPE_ERROR);
	AssignNumber(CAIRO_STATUS_WIN32_GDI_ERROR);
	AssignNumber(CAIRO_STATUS_TAG_ERROR);
	AssignNumber(CAIRO_STATUS_LAST_STATUS);
	// cairo_content_t
	AssignNumber(CAIRO_CONTENT_COLOR);
	AssignNumber(CAIRO_CONTENT_ALPHA);
	AssignNumber(CAIRO_CONTENT_COLOR_ALPHA);
	// cairo_format_t
	AssignNumber(CAIRO_FORMAT_INVALID);
	AssignNumber(CAIRO_FORMAT_ARGB32);
	AssignNumber(CAIRO_FORMAT_RGB24);
	AssignNumber(CAIRO_FORMAT_A8);
	AssignNumber(CAIRO_FORMAT_A1);
	AssignNumber(CAIRO_FORMAT_RGB16_565);
	AssignNumber(CAIRO_FORMAT_RGB30);
	// cairo_operator_t
	AssignNumber(CAIRO_OPERATOR_CLEAR);
	AssignNumber(CAIRO_OPERATOR_SOURCE);
	AssignNumber(CAIRO_OPERATOR_OVER);
	AssignNumber(CAIRO_OPERATOR_IN);
	AssignNumber(CAIRO_OPERATOR_OUT);
	AssignNumber(CAIRO_OPERATOR_ATOP);
	AssignNumber(CAIRO_OPERATOR_DEST);
	AssignNumber(CAIRO_OPERATOR_DEST_OVER);
	AssignNumber(CAIRO_OPERATOR_DEST_IN);
	AssignNumber(CAIRO_OPERATOR_DEST_OUT);
	AssignNumber(CAIRO_OPERATOR_DEST_ATOP);
	AssignNumber(CAIRO_OPERATOR_XOR);
	AssignNumber(CAIRO_OPERATOR_ADD);
	AssignNumber(CAIRO_OPERATOR_SATURATE);
	AssignNumber(CAIRO_OPERATOR_MULTIPLY);
	AssignNumber(CAIRO_OPERATOR_SCREEN);
	AssignNumber(CAIRO_OPERATOR_OVERLAY);
	AssignNumber(CAIRO_OPERATOR_DARKEN);
	AssignNumber(CAIRO_OPERATOR_LIGHTEN);
	AssignNumber(CAIRO_OPERATOR_COLOR_DODGE);
	AssignNumber(CAIRO_OPERATOR_COLOR_BURN);
	AssignNumber(CAIRO_OPERATOR_HARD_LIGHT);
	AssignNumber(CAIRO_OPERATOR_SOFT_LIGHT);
	AssignNumber(CAIRO_OPERATOR_DIFFERENCE);
	AssignNumber(CAIRO_OPERATOR_EXCLUSION);
	AssignNumber(CAIRO_OPERATOR_HSL_HUE);
	AssignNumber(CAIRO_OPERATOR_HSL_SATURATION);
	AssignNumber(CAIRO_OPERATOR_HSL_COLOR);
	AssignNumber(CAIRO_OPERATOR_HSL_LUMINOSITY);
	// cairo_antialias_t
	AssignNumber(CAIRO_ANTIALIAS_DEFAULT);
	AssignNumber(CAIRO_ANTIALIAS_NONE);
	AssignNumber(CAIRO_ANTIALIAS_GRAY);
	AssignNumber(CAIRO_ANTIALIAS_SUBPIXEL);
	AssignNumber(CAIRO_ANTIALIAS_FAST);
	AssignNumber(CAIRO_ANTIALIAS_GOOD);
	AssignNumber(CAIRO_ANTIALIAS_BEST);
	// cairo_fill_rule_t
	AssignNumber(CAIRO_FILL_RULE_WINDING);
	AssignNumber(CAIRO_FILL_RULE_EVEN_ODD);
	// cairo_line_cap_t
	AssignNumber(CAIRO_LINE_CAP_BUTT);
	AssignNumber(CAIRO_LINE_CAP_ROUND);
	AssignNumber(CAIRO_LINE_CAP_SQUARE);
	// cairo_line_join_t
	AssignNumber(CAIRO_LINE_JOIN_MITER);
	AssignNumber(CAIRO_LINE_JOIN_ROUND);
	AssignNumber(CAIRO_LINE_JOIN_BEVEL);
	// cairo_text_cluster_flags
	AssignNumber(CAIRO_TEXT_CLUSTER_FLAG_BACKWARD);
	// cairo_font_slant_t
	AssignNumber(CAIRO_FONT_SLANT_NORMAL);
	AssignNumber(CAIRO_FONT_SLANT_ITALIC);
	AssignNumber(CAIRO_FONT_SLANT_OBLIQUE);
	// cairo_font_weight_t
	AssignNumber(CAIRO_FONT_WEIGHT_NORMAL);
	AssignNumber(CAIRO_FONT_WEIGHT_BOLD);
	// cairo_subpixel_order_t
	AssignNumber(CAIRO_SUBPIXEL_ORDER_DEFAULT);
	AssignNumber(CAIRO_SUBPIXEL_ORDER_RGB);
	AssignNumber(CAIRO_SUBPIXEL_ORDER_BGR);
	AssignNumber(CAIRO_SUBPIXEL_ORDER_VRGB);
	AssignNumber(CAIRO_SUBPIXEL_ORDER_VBGR);
	// cairo_hint_style_t
	AssignNumber(CAIRO_HINT_STYLE_DEFAULT);
	AssignNumber(CAIRO_HINT_STYLE_NONE);
	AssignNumber(CAIRO_HINT_STYLE_SLIGHT);
	AssignNumber(CAIRO_HINT_STYLE_MEDIUM);
	AssignNumber(CAIRO_HINT_STYLE_FULL);
	// cairo_hint_metrics_t
	AssignNumber(CAIRO_HINT_METRICS_DEFAULT);
	AssignNumber(CAIRO_HINT_METRICS_OFF);
	AssignNumber(CAIRO_HINT_METRICS_ON);
	// cairo_font_type_t
	AssignNumber(CAIRO_FONT_TYPE_TOY);
	AssignNumber(CAIRO_FONT_TYPE_FT);
	AssignNumber(CAIRO_FONT_TYPE_WIN32);
	AssignNumber(CAIRO_FONT_TYPE_QUARTZ);
	AssignNumber(CAIRO_FONT_TYPE_USER);
	// cairo_path_data_type_t
	AssignNumber(CAIRO_PATH_MOVE_TO);
	AssignNumber(CAIRO_PATH_LINE_TO);
	AssignNumber(CAIRO_PATH_CURVE_TO);
	AssignNumber(CAIRO_PATH_CLOSE_PATH);
	// cairo_device_type_t
	AssignNumber(CAIRO_DEVICE_TYPE_DRM);
	AssignNumber(CAIRO_DEVICE_TYPE_GL);
	AssignNumber(CAIRO_DEVICE_TYPE_SCRIPT);
	AssignNumber(CAIRO_DEVICE_TYPE_XCB);
	AssignNumber(CAIRO_DEVICE_TYPE_XLIB);
	AssignNumber(CAIRO_DEVICE_TYPE_XML);
	AssignNumber(CAIRO_DEVICE_TYPE_COGL);
	AssignNumber(CAIRO_DEVICE_TYPE_WIN32);
	AssignNumber(CAIRO_DEVICE_TYPE_INVALID);
	// cairo_surface_observer_mode_t
	AssignNumber(CAIRO_SURFACE_OBSERVER_NORMAL);
	AssignNumber(CAIRO_SURFACE_OBSERVER_RECORD_OPERATIONS);
	// cairo_surface_type_t
	AssignNumber(CAIRO_SURFACE_TYPE_IMAGE);
	AssignNumber(CAIRO_SURFACE_TYPE_PDF);
	AssignNumber(CAIRO_SURFACE_TYPE_PS);
	AssignNumber(CAIRO_SURFACE_TYPE_XLIB);
	AssignNumber(CAIRO_SURFACE_TYPE_XCB);
	AssignNumber(CAIRO_SURFACE_TYPE_GLITZ);
	AssignNumber(CAIRO_SURFACE_TYPE_QUARTZ);
	AssignNumber(CAIRO_SURFACE_TYPE_WIN32);
	AssignNumber(CAIRO_SURFACE_TYPE_BEOS);
	AssignNumber(CAIRO_SURFACE_TYPE_DIRECTFB);
	AssignNumber(CAIRO_SURFACE_TYPE_SVG);
	AssignNumber(CAIRO_SURFACE_TYPE_OS2);
	AssignNumber(CAIRO_SURFACE_TYPE_WIN32_PRINTING);
	AssignNumber(CAIRO_SURFACE_TYPE_QUARTZ_IMAGE);
	AssignNumber(CAIRO_SURFACE_TYPE_SCRIPT);
	AssignNumber(CAIRO_SURFACE_TYPE_QT);
	AssignNumber(CAIRO_SURFACE_TYPE_RECORDING);
	AssignNumber(CAIRO_SURFACE_TYPE_VG);
	AssignNumber(CAIRO_SURFACE_TYPE_GL);
	AssignNumber(CAIRO_SURFACE_TYPE_DRM);
	AssignNumber(CAIRO_SURFACE_TYPE_TEE);
	AssignNumber(CAIRO_SURFACE_TYPE_XML);
	AssignNumber(CAIRO_SURFACE_TYPE_SKIA);
	AssignNumber(CAIRO_SURFACE_TYPE_SUBSURFACE);
	AssignNumber(CAIRO_SURFACE_TYPE_COGL);
	// cairo_pattern_type_t
	AssignNumber(CAIRO_PATTERN_TYPE_SOLID);
	AssignNumber(CAIRO_PATTERN_TYPE_SURFACE);
	AssignNumber(CAIRO_PATTERN_TYPE_LINEAR);
	AssignNumber(CAIRO_PATTERN_TYPE_RADIAL);
	AssignNumber(CAIRO_PATTERN_TYPE_MESH);
	AssignNumber(CAIRO_PATTERN_TYPE_RASTER_SOURCE);
	// cairo_extend_t
	AssignNumber(CAIRO_EXTEND_NONE);
	AssignNumber(CAIRO_EXTEND_REPEAT);
	AssignNumber(CAIRO_EXTEND_REFLECT);
	AssignNumber(CAIRO_EXTEND_PAD);
	// cairo_filter_t
	AssignNumber(CAIRO_FILTER_FAST);
	AssignNumber(CAIRO_FILTER_GOOD);
	AssignNumber(CAIRO_FILTER_BEST);
	AssignNumber(CAIRO_FILTER_NEAREST);
	AssignNumber(CAIRO_FILTER_BILINEAR);
	AssignNumber(CAIRO_FILTER_GAUSSIAN);
	// cairo_region_overlap_t
	AssignNumber(CAIRO_REGION_OVERLAP_IN);
	AssignNumber(CAIRO_REGION_OVERLAP_OUT);
	AssignNumber(CAIRO_REGION_OVERLAP_PART);
	// cairo_pdf_version_t
    AssignNumber(CAIRO_PDF_VERSION_1_4);
    AssignNumber(CAIRO_PDF_VERSION_1_5);
	// Tagging function
	AssignString(CAIRO_TAG_DEST);
	AssignString(CAIRO_TAG_LINK);
	// MIME type
	AssignString(CAIRO_MIME_TYPE_JPEG);
	AssignString(CAIRO_MIME_TYPE_PNG);
	AssignString(CAIRO_MIME_TYPE_JP2);
	AssignString(CAIRO_MIME_TYPE_URI);
	AssignString(CAIRO_MIME_TYPE_UNIQUE_ID);
	AssignString(CAIRO_MIME_TYPE_JBIG2);
	AssignString(CAIRO_MIME_TYPE_JBIG2_GLOBAL);
	AssignString(CAIRO_MIME_TYPE_JBIG2_GLOBAL_ID);
	AssignString(CAIRO_MIME_TYPE_CCITT_FAX);
	AssignString(CAIRO_MIME_TYPE_CCITT_FAX_PARAMS);
	AssignString(CAIRO_MIME_TYPE_EPS);
	AssignString(CAIRO_MIME_TYPE_EPS_PARAMS);
}

Gurax_EndModuleScope(cairo)
