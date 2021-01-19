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
				unsigned char* pSrc = data;
				for (int x = 0; x < width; x++, pSrc += 4, pDst += 4) {
					*(pDst + Image::offsetB) = *(pSrc + 0);
					*(pDst + Image::offsetG) = *(pSrc + 1);
					*(pDst + Image::offsetR) = *(pSrc + 2);
					*(pDst + Image::offsetA) = *(pSrc + 3);
				}
			}
			break;
		}
		case CAIRO_FORMAT_RGB24: {
			break;
		}
		case CAIRO_FORMAT_A8: {
			break;
		}
		case CAIRO_FORMAT_A1: {
			break;
		}
		case CAIRO_FORMAT_RGB16_565: {
			break;
		}
		case CAIRO_FORMAT_RGB30: {
			break;
		}
		default:
			return nullptr;
		}
	}
	return pImage.release();
}

Gurax_EndModuleScope(cairo)
