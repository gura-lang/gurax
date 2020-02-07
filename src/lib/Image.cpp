//==============================================================================
// Image.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax/VType_Image.h>

namespace Gurax {

//------------------------------------------------------------------------------
// Image
//------------------------------------------------------------------------------
bool Image::Allocate(size_t width, size_t height)
{
	size_t bytes = WidthToBytes(width) * height;
	_metrics.width = width, _metrics.height = height;
	_pMemory.reset(new MemoryHeap(bytes));
	return !!_pMemory;
}

template<typename T_Pixel>
void Image::FillT(const Color& color)
{
	if (IsAreaZero()) return;
	T_Pixel pixel(GetMetrics(), GetPointer());
	pixel.SetColorN(color, GetWidth());
	const UInt8* pSrc = pixel.GetPointer();
	UInt8* pDst = pixel.GetPointer() + GetBytesPerLine();
	size_t bytesToCopy = GetBytesPerLine();
	for (size_t i = 1; i < GetHeight(); i++, pDst += GetBytesPerLine()) {
		::memcpy(pDst, pSrc, bytesToCopy);
	}
}

void Image::Fill(const Color& color)
{
	if (IsFormat(Format::BGR)) {
		FillT<PixelBGR>(color);
	} else if (IsFormat(Format::BGRA)) {
		FillT<PixelBGRA>(color);
	}
}

template<typename T_Pixel>
void Image::FillRectT(size_t x, size_t y, size_t width, size_t height, const Color& color)
{
	if (IsAreaZero()) return;
	T_Pixel pixel(GetMetrics(), GetPointer(x, y));
	pixel.SetColorN(color, width);
	const UInt8* pSrc = pixel.GetPointer();
	UInt8* pDst = pixel.GetPointer() + GetBytesPerLine();
	size_t bytesToCopy = WidthToBytes(width);
	for (size_t i = 1; i < height; i++, pDst += GetBytesPerLine()) {
		::memcpy(pDst, pSrc, bytesToCopy);
	}
}

void Image::FillRect(size_t x, size_t y, size_t width, size_t height, const Color& color)
{
	if (IsFormat(Format::BGR)) {
		FillRectT<PixelBGR>(x, y, width, height, color);
	} else if (IsFormat(Format::BGRA)) {
		FillRectT<PixelBGRA>(x, y, width, height, color);
	}
}

template<typename T_PixelDst, typename T_PixelSrc>
void Image::PasteT(size_t xDst, size_t yDst, const Image& imageSrc,
				  size_t xSrc, size_t ySrc, size_t width, size_t height)
{
	T_PixelDst pixelDst(GetMetrics(), GetPointer(xDst, yDst));
	T_PixelSrc pixelSrc(GetMetrics(), GetPointer(xSrc, ySrc));

}

void Image::Paste(size_t xDst, size_t yDst, const Image& imageSrc,
				 size_t xSrc, size_t ySrc, size_t width, size_t height)
{
	if (IsFormat(Format::BGR)) {
		if (imageSrc.IsFormat(Format::BGR)) {
			PasteT<PixelBGR, PixelBGR>(xDst, yDst, imageSrc, xSrc, ySrc, width, height);
		} else if (imageSrc.IsFormat(Format::BGRA)) {
			PasteT<PixelBGR, PixelBGRA>(xDst, yDst, imageSrc, xSrc, ySrc, width, height);
		}
	} else if (IsFormat(Format::BGRA)) {
		if (imageSrc.IsFormat(Format::BGR)) {
			PasteT<PixelBGRA, PixelBGR>(xDst, yDst, imageSrc, xSrc, ySrc, width, height);
		} else if (imageSrc.IsFormat(Format::BGRA)) {
			PasteT<PixelBGRA, PixelBGRA>(xDst, yDst, imageSrc, xSrc, ySrc, width, height);
		}
	}
}

template<typename T_PixelDst, typename T_PixelSrc>
void Image::ResizePasteT(size_t xDst, size_t yDst, size_t wdDst, size_t htDst, const Image& imageSrc,
						 size_t xSrc, size_t ySrc, size_t wdSrc, size_t htSrc)
{
#if 0
	T_PixelDst pixelDst(GetMetrics(), GetPointer(xDst, yDst));
	T_PixelSrc pixelSrc(GetMetrics(), GetPointer(xSrc, ySrc));
	for (size_t i = 0; i < height; i++) {
		pixelDst.InjectN(pixelSrc, width);
		pixelDst.FwdLine();
		pixelSrc.FwdLine();
	}
#endif
}

void Image::ResizePaste(size_t xDst, size_t yDst, size_t wdDst, size_t htDst, const Image& imageSrc,
						size_t xSrc, size_t ySrc, size_t wdSrc, size_t htSrc)
{
	if (IsFormat(Format::BGR)) {
		if (imageSrc.IsFormat(Format::BGR)) {
			ResizePasteT<PixelBGR, PixelBGR>(xDst, yDst, wdDst, htDst, imageSrc, xSrc, ySrc, wdSrc, htSrc);
		} else if (imageSrc.IsFormat(Format::BGRA)) {
			ResizePasteT<PixelBGR, PixelBGRA>(xDst, yDst, wdDst, htDst, imageSrc, xSrc, ySrc, wdSrc, htSrc);
		}
	} else if (IsFormat(Format::BGRA)) {
		if (imageSrc.IsFormat(Format::BGR)) {
			ResizePasteT<PixelBGRA, PixelBGR>(xDst, yDst, wdDst, htDst, imageSrc, xSrc, ySrc, wdSrc, htSrc);
		} else if (imageSrc.IsFormat(Format::BGRA)) {
			ResizePasteT<PixelBGRA, PixelBGRA>(xDst, yDst, wdDst, htDst, imageSrc, xSrc, ySrc, wdSrc, htSrc);
		}
	}
}

Image* Image::Crop(const Format& format, size_t x, size_t y, size_t width, size_t height) const
{
	RefPtr<Image> pImage(new Image(format));
	if (!pImage->Allocate(width, height)) return nullptr;
	pImage->Paste(0, 0, *this, x, y, width, height);
	return pImage.release();
}

String Image::ToString(const StringStyle& ss) const
{
	return "";
}

//------------------------------------------------------------------------------
// Image::Format
//------------------------------------------------------------------------------
const Image::Format Image::Format::BGR(3);
const Image::Format Image::Format::BGRA(4);

//------------------------------------------------------------------------------
// Image::PixelBGR
//------------------------------------------------------------------------------
const Image::Format& Image::PixelBGR::format = Format::BGR;

template<> void Image::PixelBGR::Paste<Image::PixelBGR>(const PixelBGR& pixel, size_t width, size_t height)
{
	UInt8* pLineDst = GetPointer();
	const UInt8* pLineSrc = pixel.GetPointer();
	size_t bytesToCopy = WidthToBytes(width);
	for (size_t y = 0; y < height; y++) {
		::memcpy(pLineDst, pLineSrc, bytesToCopy);
		pLineDst += GetBytesPerLine();
		pLineSrc += pixel.GetBytesPerLine();
	}
}

template<> void Image::PixelBGR::Paste<Image::PixelBGRA>(const PixelBGRA& pixel, size_t width, size_t height)
{
	UInt8* pLineDst = GetPointer();
	const UInt8* pLineSrc = pixel.GetPointer();
	for (size_t y = 0; y < height; y++) {
		UInt8* pDst = pLineDst;
		const UInt8* pSrc = pLineSrc;
		for (size_t x = 0; x < width; x++) {
			*pDst++ = *pSrc++, *pDst++ = *pSrc++, *pDst++ = *pSrc++, pSrc++;
		}
		pLineDst += GetBytesPerLine();
		pLineSrc += pixel.GetBytesPerLine();
	}
}

//------------------------------------------------------------------------------
// Image::PixelBGRA
//------------------------------------------------------------------------------
const Image::Format& Image::PixelBGRA::format = Format::BGRA;

template<> void Image::PixelBGRA::Paste<Image::PixelBGRA>(const PixelBGRA& pixel, size_t width, size_t height)
{
	UInt8* pLineDst = GetPointer();
	const UInt8* pLineSrc = pixel.GetPointer();
	size_t bytesToCopy = WidthToBytes(width);
	for (size_t y = 0; y < height; y++) {
		::memcpy(pLineDst, pLineSrc, bytesToCopy);
		pLineDst += GetBytesPerLine();
		pLineSrc += pixel.GetBytesPerLine();
	}
}

template<> void Image::PixelBGRA::Paste<Image::PixelBGR>(const PixelBGR& pixel, size_t width, size_t height)
{
	UInt8* pLineDst = GetPointer();
	const UInt8* pLineSrc = pixel.GetPointer();
	for (size_t y = 0; y < height; y++) {
		UInt8* pDst = pLineDst;
		const UInt8* pSrc = pLineSrc;
		for (size_t x = 0; x < width; x++) {
			*pDst++ = *pSrc++, *pDst++ = *pSrc++, *pDst++ = *pSrc++, *pDst++ = 0xff;
		}
		pLineDst += GetBytesPerLine();
		pLineSrc += pixel.GetBytesPerLine();
	}
}

//------------------------------------------------------------------------------
// ImageList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ImageOwner
//------------------------------------------------------------------------------
void ImageOwner::Clear()
{
	for (Image* pImage : *this) Image::Delete(pImage);
	clear();
}

}
