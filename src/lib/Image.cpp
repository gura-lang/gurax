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
	if (_width == 0 || _height == 0) return;
	size_t bytesPerLine = T_Pixel::bytesPerPixel * _width;
	T_Pixel pixel(GetPointer());
	pixel.SetColorN(color, _width);
	const UInt8* pSrc = GetPointer();
	UInt8* pDst = GetPointer() + bytesPerLine;
	for (size_t i = 1; i < _height; i++, pDst += bytesPerLine, pSrc += bytesPerLine) {
		::memcpy(pDst, pSrc, bytesPerLine);
	}
}

void Image::Fill(const Color& color)
{
	switch (_format) {
	case Format::BGR: FillTmpl<PixelBGR>(color); break;
	case Format::BGRA: FillTmpl<PixelBGRA>(color); break;
	default: break;
	}
}

String Image::ToString(const StringStyle& ss) const
{
	return "";
}

//------------------------------------------------------------------------------
// Image::PixelBGR
//------------------------------------------------------------------------------
template<> void Image::PixelBGR::InjectN<Image::PixelBGR>(const PixelBGR& pixel, size_t n)
{
	::memcpy(GetPointer(), pixel.GetPointer(), bytesPerPixel * n);
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
	::memcpy(GetPointer(), pixel.GetPointer(), bytesPerPixel * n);
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
