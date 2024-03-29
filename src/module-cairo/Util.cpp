﻿//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

RefPtr<Function> g_pFunc_font_face_init;
RefPtr<Function> g_pFunc_font_face_render_glyph;
RefPtr<Function> g_pFunc_font_face_text_to_glyphs;
RefPtr<Function> g_pFunc_font_face_unicode_to_glyph;

RefPtr<Function> g_pFunc_surface_observer_add_paint;
RefPtr<Function> g_pFunc_surface_observer_add_mask;
RefPtr<Function> g_pFunc_surface_observer_add_fill;
RefPtr<Function> g_pFunc_surface_observer_add_stroke;
RefPtr<Function> g_pFunc_surface_observer_add_glyphs;
RefPtr<Function> g_pFunc_surface_observer_add_flush;
RefPtr<Function> g_pFunc_surface_observer_add_finish;
RefPtr<Function> g_pFunc_surface_observer_print;

cairo_status_t font_face_init_func(cairo_scaled_font_t* scaled_font, cairo_t* cr, cairo_font_extents_t* extents)
{
	return CAIRO_STATUS_SUCCESS;
}

cairo_status_t font_face_render_glyph_func(cairo_scaled_font_t* scaled_font, unsigned long glyph, cairo_t* cr, cairo_text_extents_t* extents)
{
	return CAIRO_STATUS_SUCCESS;
}

cairo_status_t font_face_text_to_glyphs_func(cairo_scaled_font_t* scaled_font, const char* utf8, int utf8_len,
	cairo_glyph_t** glyphs, int* num_glyphs, cairo_text_cluster_t** clusters, int* num_clusters, cairo_text_cluster_flags_t* cluster_flags)
{
	return CAIRO_STATUS_SUCCESS;
}

cairo_status_t font_face_unicode_to_glyph_func(cairo_scaled_font_t* scaled_font, unsigned long  unicode, unsigned long* glyph_index)
{
	return CAIRO_STATUS_SUCCESS;
}

cairo_status_t surface_observer_add_paint_callback(cairo_surface_t* observer, cairo_surface_t* target, void* data)
{
	return CAIRO_STATUS_SUCCESS;
}

cairo_status_t surface_observer_add_mask_callback(cairo_surface_t* observer, cairo_surface_t* target, void* data)
{
	return CAIRO_STATUS_SUCCESS;
}

cairo_status_t surface_observer_add_fill_callback(cairo_surface_t* observer, cairo_surface_t* target, void* data)
{
	return CAIRO_STATUS_SUCCESS;
}

cairo_status_t surface_observer_add_stroke_callback(cairo_surface_t* observer, cairo_surface_t* target, void* data)
{
	return CAIRO_STATUS_SUCCESS;
}

cairo_status_t surface_observer_add_glyphs_callback(cairo_surface_t* observer, cairo_surface_t* target, void* data)
{
	return CAIRO_STATUS_SUCCESS;
}

cairo_status_t surface_observer_add_flush_callback(cairo_surface_t* observer, cairo_surface_t* target, void* data)
{
	return CAIRO_STATUS_SUCCESS;
}

cairo_status_t surface_observer_add_finish_callback(cairo_surface_t* observer, cairo_surface_t* target, void* data)
{
	return CAIRO_STATUS_SUCCESS;
}

cairo_status_t surface_observer_print(void* closure, const unsigned char* data, unsigned int length)
{
	return CAIRO_STATUS_SUCCESS;
}


inline UInt8 DemultiplyAlpha(UInt8 elem, UInt8 alpha)
{
	return (alpha == 0)? 0 : static_cast<UInt8>(static_cast<UInt32>(elem) * 255 / alpha);
}

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
#endif

Image* CreateImageFromSurface(cairo_surface_t* surface, const Image::Format& formatImg)
{
	unsigned char* data = cairo_image_surface_get_data(surface);
	cairo_format_t format = cairo_image_surface_get_format(surface);
	int width = cairo_image_surface_get_width(surface);
	int height = cairo_image_surface_get_height(surface);
	int stride = cairo_image_surface_get_stride(surface);
	RefPtr<Image> pImage(new Image(formatImg));
	if (!pImage->Allocate(width, height)) return nullptr;
	if (formatImg.IsIdentical(Image::Format::RGBA)) {
		switch (format) {
		case CAIRO_FORMAT_ARGB32: {
			UInt8* pDst = pImage->GetPointerC();
			for (int y = 0; y < height; y++, data += stride) {
				UInt8* pSrc = data;
				for (int x = 0; x < width; x++, pSrc += 4, pDst += 4) {
					UInt8 alpha = *(pSrc + 3);
					*(pDst + Image::offsetB) = DemultiplyAlpha(*(pSrc + 0), alpha);
					*(pDst + Image::offsetG) = DemultiplyAlpha(*(pSrc + 1), alpha);
					*(pDst + Image::offsetR) = DemultiplyAlpha(*(pSrc + 2), alpha);
					*(pDst + Image::offsetA) = alpha;
				}
			}
			break;
		}
		case CAIRO_FORMAT_RGB24: {
			UInt8* pDst = pImage->GetPointerC();
			for (int y = 0; y < height; y++, data += stride) {
				UInt8* pSrc = data;
				for (int x = 0; x < width; x++, pSrc += 4, pDst += 4) {
					*(pDst + Image::offsetB) = *(pSrc + 0);
					*(pDst + Image::offsetG) = *(pSrc + 1);
					*(pDst + Image::offsetR) = *(pSrc + 2);
					*(pDst + Image::offsetA) = 0xff;
				}
			}
			break;
		}
		case CAIRO_FORMAT_A8: {
			UInt8* pDst = pImage->GetPointerC();
			for (int y = 0; y < height; y++, data += stride) {
				UInt8* pSrc = data;
				for (int x = 0; x < width; x++, pSrc++, pDst += 4) {
					UInt8 alpha = *pSrc;
					UInt8 ch = alpha? 0xff : 0x00;
					*(pDst + Image::offsetB) = ch;
					*(pDst + Image::offsetG) = ch;
					*(pDst + Image::offsetR) = ch;
					*(pDst + Image::offsetA) = alpha;
				}
			}
			break;
		}
		case CAIRO_FORMAT_A1: {
			UInt8* pDst = pImage->GetPointerC();
			for (int y = 0; y < height; y++, data += stride) {
				UInt32* pSrc = reinterpret_cast<UInt32*>(data);
				UInt32 alphaPacked = 0;
				size_t nBitsRest = 0;
				for (int x = 0; x < width; x++, pDst += 4) {
					if (nBitsRest == 0) {
						alphaPacked = *pSrc++;
						nBitsRest = 32;
					}
					UInt8 alpha = (alphaPacked & 1) * 0xff;
					alphaPacked >>= 1;
					nBitsRest--;
					UInt8 ch = alpha? 0xff : 0x00;
					*(pDst + Image::offsetB) = ch;
					*(pDst + Image::offsetG) = ch;
					*(pDst + Image::offsetR) = ch;
					*(pDst + Image::offsetA) = alpha;
				}
			}
			break;
		}
		case CAIRO_FORMAT_RGB16_565: {
			UInt8* pDst = pImage->GetPointerC();
			for (int y = 0; y < height; y++, data += stride) {
				UInt16* pSrc = reinterpret_cast<UInt16*>(data);
				for (int x = 0; x < width; x++, pSrc++, pDst += 4) {
					UInt16 packed = *pSrc;
					*(pDst + Image::offsetB) = static_cast<UInt8>((packed >> 0) & 0x1f);
					*(pDst + Image::offsetG) = static_cast<UInt8>((packed >> 5) & 0x3f);
					*(pDst + Image::offsetR) = static_cast<UInt8>((packed >> 11) & 0x1f);
					*(pDst + Image::offsetA) = 0xff;
				}
			}
			break;
		}
		case CAIRO_FORMAT_RGB30: {
			UInt8* pDst = pImage->GetPointerC();
			for (int y = 0; y < height; y++, data += stride) {
				UInt32* pSrc = reinterpret_cast<UInt32*>(data);
				for (int x = 0; x < width; x++, pSrc++, pDst += 4) {
					UInt32 packed = *pSrc;
					*(pDst + Image::offsetB) = static_cast<UInt8>((packed >> 2) & 0xff);
					*(pDst + Image::offsetG) = static_cast<UInt8>((packed >> 12) & 0xff);
					*(pDst + Image::offsetR) = static_cast<UInt8>((packed >> 22) & 0xff);
					*(pDst + Image::offsetA) = 0xff;
				}
			}
			break;
		}
		default:
			return nullptr;
		}
	} else {
		switch (format) {
		case CAIRO_FORMAT_ARGB32: {
			UInt8* pDst = pImage->GetPointerC();
			for (int y = 0; y < height; y++, data += stride) {
				UInt8* pSrc = data;
				for (int x = 0; x < width; x++, pSrc += 4, pDst += 3) {
					UInt8 alpha = *(pSrc + 3);
					*(pDst + Image::offsetB) = DemultiplyAlpha(*(pSrc + 0), alpha);
					*(pDst + Image::offsetG) = DemultiplyAlpha(*(pSrc + 1), alpha);
					*(pDst + Image::offsetR) = DemultiplyAlpha(*(pSrc + 2), alpha);
				}
			}
			break;
		}
		case CAIRO_FORMAT_RGB24: {
			UInt8* pDst = pImage->GetPointerC();
			for (int y = 0; y < height; y++, data += stride) {
				UInt8* pSrc = data;
				for (int x = 0; x < width; x++, pSrc += 4, pDst += 3) {
					*(pDst + Image::offsetB) = *(pSrc + 0);
					*(pDst + Image::offsetG) = *(pSrc + 1);
					*(pDst + Image::offsetR) = *(pSrc + 2);
				}
			}
			break;
		}
		case CAIRO_FORMAT_A8: {
			UInt8* pDst = pImage->GetPointerC();
			for (int y = 0; y < height; y++, data += stride) {
				UInt8* pSrc = data;
				for (int x = 0; x < width; x++, pSrc++, pDst += 3) {
					UInt8 alpha = *pSrc;
					UInt8 ch = alpha? 0xff : 0x00;
					*(pDst + Image::offsetB) = ch;
					*(pDst + Image::offsetG) = ch;
					*(pDst + Image::offsetR) = ch;
				}
			}
			break;
		}
		case CAIRO_FORMAT_A1: {
			UInt8* pDst = pImage->GetPointerC();
			for (int y = 0; y < height; y++, data += stride) {
				UInt32* pSrc = reinterpret_cast<UInt32*>(data);
				UInt32 alphaPacked = 0;
				size_t nBitsRest = 0;
				for (int x = 0; x < width; x++, pDst += 3) {
					if (nBitsRest == 0) {
						alphaPacked = *pSrc++;
						nBitsRest = 32;
					}
					UInt8 alpha = (alphaPacked & 1) * 0xff;
					alphaPacked >>= 1;
					nBitsRest--;
					UInt8 ch = alpha? 0xff : 0x00;
					*(pDst + Image::offsetB) = ch;
					*(pDst + Image::offsetG) = ch;
					*(pDst + Image::offsetR) = ch;
				}
			}
			break;
		}
		case CAIRO_FORMAT_RGB16_565: {
			UInt8* pDst = pImage->GetPointerC();
			for (int y = 0; y < height; y++, data += stride) {
				UInt16* pSrc = reinterpret_cast<UInt16*>(data);
				for (int x = 0; x < width; x++, pSrc++, pDst += 3) {
					UInt16 packed = *pSrc;
					*(pDst + Image::offsetB) = static_cast<UInt8>((packed >> 0) & 0x1f);
					*(pDst + Image::offsetG) = static_cast<UInt8>((packed >> 5) & 0x3f);
					*(pDst + Image::offsetR) = static_cast<UInt8>((packed >> 11) & 0x1f);
				}
			}
			break;
		}
		case CAIRO_FORMAT_RGB30: {
			UInt8* pDst = pImage->GetPointerC();
			for (int y = 0; y < height; y++, data += stride) {
				UInt32* pSrc = reinterpret_cast<UInt32*>(data);
				for (int x = 0; x < width; x++, pSrc++, pDst += 4) {
					UInt32 packed = *pSrc;
					*(pDst + Image::offsetB) = static_cast<UInt8>((packed >> 2) & 0xff);
					*(pDst + Image::offsetG) = static_cast<UInt8>((packed >> 12) & 0xff);
					*(pDst + Image::offsetR) = static_cast<UInt8>((packed >> 22) & 0xff);
				}
			}
			break;
		}
		default:
			return nullptr;
		}
	}
	return pImage.release();
}

Gurax_EndModuleScope(cairo)
