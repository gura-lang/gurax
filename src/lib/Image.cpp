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
	T_Pixel pixel(GetPointer());
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
	T_Pixel pixel(GetPointer(x, y));
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
	T_PixelDst pixelDst(GetPointer(xDst, yDst));
	T_PixelSrc pixelSrc(GetPointer(xSrc, ySrc));
	for (size_t i = 0; i < height; i++) {
		pixelDst.InjectN(pixelSrc, width);
		pixelDst.FwdLine(_metrics), pixelSrc.FwdLine(_metrics);
	}
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

template<> void Image::PixelBGR::InjectN<Image::PixelBGR>(const PixelBGR& pixel, size_t n)
{
	::memcpy(GetPointer(), pixel.GetPointer(), format.bytesPerPixel * n);
}

template<> void Image::PixelBGR::InjectN<Image::PixelBGRA>(const PixelBGRA& pixel, size_t n)
{
	UInt8* pDst = GetPointer();
	const UInt8* pSrc = pixel.GetPointer();
	for (size_t i = 0; i < n; i++) {
		*pDst++ = *pSrc++, *pDst++ = *pSrc++, *pDst++ = *pSrc++, pSrc++;
	}
}

//------------------------------------------------------------------------------
// Image::PixelBGRA
//------------------------------------------------------------------------------
const Image::Format& Image::PixelBGRA::format = Format::BGRA;

template<> void Image::PixelBGRA::InjectN<Image::PixelBGR>(const PixelBGR& pixel, size_t n)
{
	UInt8* pDst = GetPointer();
	const UInt8* pSrc = pixel.GetPointer();
	for (size_t i = 0; i < n; i++) {
		*pDst++ = *pSrc++, *pDst++ = *pSrc++, *pDst++ = *pSrc++, *pDst++ = 0xff;
	}
}

template<> void Image::PixelBGRA::InjectN<Image::PixelBGRA>(const PixelBGRA& pixel, size_t n)
{
	::memcpy(GetPointer(), pixel.GetPointer(), format.bytesPerPixel * n);
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
