//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

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
