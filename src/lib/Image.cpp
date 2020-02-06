//==============================================================================
// Image.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax/VType_Image.h>

namespace Gurax {


//------------------------------------------------------------------------------
// Image
//------------------------------------------------------------------------------
template<typename T_Pixel> void Image::FillTmpl(const Color& color)
{
	if (IsAreaZero()) return;
	T_Pixel(GetPointer()).SetColorN(color, GetWidth());
	const UInt8* pSrc = GetPointer();
	UInt8* pDst = GetPointer() + GetBytesPerLine();
	for (size_t i = 1; i < GetHeight(); i++, pDst += GetBytesPerLine(), pSrc += GetBytesPerLine()) {
		::memcpy(pDst, pSrc, GetBytesPerLine());
	}
}

void Image::Fill(const Color& color)
{
	if (IsFormat(Format::BGR)) {
		FillTmpl<PixelBGR>(color);
	} else if (IsFormat(Format::BGRA)) {
		FillTmpl<PixelBGRA>(color);
	}
}

template<typename T_PixelDst, typename T_PixelSrc>
void Image::CopyTmpl(size_t xDst, size_t yDst, const Image& imageSrc,
					 size_t xSrc, size_t ySrc, size_t width, size_t height)
{
	T_PixelDst pixelDst(GetPointer(xDst, yDst));
	T_PixelSrc pixelSrc(GetPointer(xSrc, ySrc));
	for (size_t i = 0; i < height; i++) {
		pixelDst.InjectN(pixelSrc, width);
		pixelDst.FwdLine(_metrics), pixelSrc.FwdLine(_metrics);
	}
}

void Image::Copy(size_t xDst, size_t yDst, const Image& imageSrc,
				 size_t xSrc, size_t ySrc, size_t width, size_t height)
{
	if (IsFormat(Format::BGR)) {
		if (imageSrc.IsFormat(Format::BGR)) {
			CopyTmpl<PixelBGR, PixelBGR>(xDst, yDst, imageSrc, xSrc, ySrc, width, height);
		} else if (imageSrc.IsFormat(Format::BGRA)) {
			CopyTmpl<PixelBGR, PixelBGRA>(xDst, yDst, imageSrc, xSrc, ySrc, width, height);
		}
	} else if (IsFormat(Format::BGRA)) {
		if (imageSrc.IsFormat(Format::BGR)) {
			CopyTmpl<PixelBGRA, PixelBGR>(xDst, yDst, imageSrc, xSrc, ySrc, width, height);
		} else if (imageSrc.IsFormat(Format::BGRA)) {
			CopyTmpl<PixelBGRA, PixelBGRA>(xDst, yDst, imageSrc, xSrc, ySrc, width, height);
		}
	}
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
