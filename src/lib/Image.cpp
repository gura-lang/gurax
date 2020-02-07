//==============================================================================
// Image.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax/VType_Image.h>

namespace Gurax {

//------------------------------------------------------------------------------
// Image::Format
//------------------------------------------------------------------------------
const Image::Format Image::Format::BGR(3);
const Image::Format Image::Format::BGRA(4);


//------------------------------------------------------------------------------
// Image::Accumulator
//------------------------------------------------------------------------------
template<> inline void Image::Accumulator::Store<Image::PixelBGR>(const UInt8* pSrc)
{
	b += *(pSrc + 0), g += *(pSrc + 1), r += *(pSrc + 2), n++;
}

template<> inline void Image::Accumulator::Store<Image::PixelBGRA>(const UInt8* pSrc)
{
	b += *(pSrc + 0), g += *(pSrc + 1), r += *(pSrc + 2), a += *(pSrc + 3), n++;
}

template<> inline void Image::Accumulator::Extract<Image::PixelBGR>(UInt8* pDst)
{
	*(pDst + 0) = static_cast<UInt8>(b / n), *(pDst + 1) = static_cast<UInt8>(g / n);
	*(pDst + 2) = static_cast<UInt8>(r / n);
}

template<> inline void Image::Accumulator::Extract<Image::PixelBGRA>(UInt8* pDst)
{
	*(pDst + 0) = static_cast<UInt8>(b / n), *(pDst + 1) = static_cast<UInt8>(g / n);
	*(pDst + 2) = static_cast<UInt8>(r / n), *(pDst + 3) = static_cast<UInt8>(a / n);
}

//------------------------------------------------------------------------------
// Image::Pixel
//------------------------------------------------------------------------------
void Image::Pixel::Paste(const Pixel& pixelSrc, size_t width, size_t height)
{
	UInt8* pLineDst = GetPointer();
	const UInt8* pLineSrc = pixelSrc.GetPointer();
	size_t bytesToCopy = WidthToBytes(width);
	for (size_t y = 0; y < height; y++) {
		::memcpy(pLineDst, pLineSrc, bytesToCopy);
		pLineDst += GetBytesPerLine();
		pLineSrc += pixelSrc.GetBytesPerLine();
	}
}

template<typename T_PixelDst, typename T_PixelSrc>
void Image::Pixel::ResizePaste(T_PixelDst& pixelDst, size_t wdDst, size_t htDst,
							   const T_PixelSrc& pixelSrc, size_t wdSrc, size_t htSrc)
{
	RefPtr<Memory> pMemory(new MemoryHeap(sizeof(Accumulator) * wdDst));
	pMemory->FillZero();
	Accumulator* accumulators = reinterpret_cast<Accumulator*>(pMemory->GetPointer());
	UInt8* pLineDst = pixelDst.GetPointer();
	const UInt8* pLineSrc = pixelSrc.GetPointer();
	size_t htAccum = 0;
	for (size_t ySrc = 0; ySrc < htSrc; ySrc++) {
		const UInt8* pSrc = pLineSrc;
		size_t wdAccum = 0;
		size_t xDst = 0;
		for (size_t xSrc = 0; xSrc < wdSrc; xSrc++) {
			accumulators[xDst].Store<T_PixelSrc>(pSrc);
			wdAccum += wdDst;
			if (wdAccum >= wdSrc) {
				wdAccum -= wdSrc;
				xDst++;
			}
			pSrc += pixelSrc.GetBytesPerPixel();
		}
		htAccum += htDst;
		if (htAccum >= htSrc) {
			UInt8* pDst = pLineDst;
			for (size_t xDst = 0; xDst < wdDst; xDst++) {
				accumulators[xDst].Extract<T_PixelDst>(pDst);
				pDst += pixelDst.GetBytesPerPixel();
			}
			htAccum -= htSrc;
			pLineDst += pixelDst.GetBytesPerLine();
			pMemory->FillZero();
		}
		pLineSrc += pixelSrc.GetBytesPerLine();
	}
}

//------------------------------------------------------------------------------
// Image::PixelBGR
//------------------------------------------------------------------------------
template<> void Image::PixelBGR::Paste<Image::PixelBGR>(const PixelBGR& pixelSrc, size_t width, size_t height)
{
	Pixel::Paste(pixelSrc, width, height);
}

template<> void Image::PixelBGR::Paste<Image::PixelBGRA>(const PixelBGRA& pixelSrc, size_t width, size_t height)
{
	UInt8* pLineDst = GetPointer();
	const UInt8* pLineSrc = pixelSrc.GetPointer();
	for (size_t y = 0; y < height; y++) {
		UInt8* pDst = pLineDst;
		const UInt8* pSrc = pLineSrc;
		for (size_t x = 0; x < width; x++) {
			*pDst++ = *pSrc++, *pDst++ = *pSrc++, *pDst++ = *pSrc++, pSrc++;
		}
		pLineDst += GetBytesPerLine();
		pLineSrc += pixelSrc.GetBytesPerLine();
	}
}

//------------------------------------------------------------------------------
// Image::PixelBGRA
//------------------------------------------------------------------------------
template<> void Image::PixelBGRA::Paste<Image::PixelBGRA>(const PixelBGRA& pixelSrc, size_t width, size_t height)
{
	Pixel::Paste(pixelSrc, width, height);
}

template<> void Image::PixelBGRA::Paste<Image::PixelBGR>(const PixelBGR& pixelSrc, size_t width, size_t height)
{
	UInt8* pLineDst = GetPointer();
	const UInt8* pLineSrc = pixelSrc.GetPointer();
	for (size_t y = 0; y < height; y++) {
		UInt8* pDst = pLineDst;
		const UInt8* pSrc = pLineSrc;
		for (size_t x = 0; x < width; x++) {
			*pDst++ = *pSrc++, *pDst++ = *pSrc++, *pDst++ = *pSrc++, *pDst++ = 0xff;
		}
		pLineDst += GetBytesPerLine();
		pLineSrc += pixelSrc.GetBytesPerLine();
	}
}

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

void Image::Fill(const Color& color)
{
	if (IsAreaZero()) return;
	if (IsFormat(Format::BGR)) {
		PixelBGR(GetMetrics(), GetPointer()).SetColorN(color, GetWidth());
	} else if (IsFormat(Format::BGRA)) {
		PixelBGRA(GetMetrics(), GetPointer()).SetColorN(color, GetWidth());
	}
	const UInt8* pLineSrc = GetPointer();
	UInt8* pLineDst = GetPointer() + GetBytesPerLine();
	size_t bytesToCopy = GetBytesPerLine();
	for (size_t i = 1; i < GetHeight(); i++, pLineDst += GetBytesPerLine()) {
		::memcpy(pLineDst, pLineSrc, bytesToCopy);
	}
}

void Image::FillRect(size_t x, size_t y, size_t width, size_t height, const Color& color)
{
	if (width == 0 || height == 0) return;
	if (IsFormat(Format::BGR)) {
		PixelBGR(GetMetrics(), GetPointer(x, y)).SetColorN(color, width);
	} else if (IsFormat(Format::BGRA)) {
		PixelBGRA(GetMetrics(), GetPointer(x, y)).SetColorN(color, width);
	}
	const UInt8* pLineSrc = GetPointer();
	UInt8* pLineDst = GetPointer() + GetBytesPerLine();
	size_t bytesToCopy = WidthToBytes(width);
	for (size_t i = 1; i < height; i++, pLineDst += GetBytesPerLine()) {
		::memcpy(pLineDst, pLineSrc, bytesToCopy);
	}
}

void Image::Paste(size_t xDst, size_t yDst, const Image& imageSrc,
				 size_t xSrc, size_t ySrc, size_t width, size_t height)
{
	if (IsFormat(Format::BGR)) {
		if (imageSrc.IsFormat(Format::BGR)) {
			PixelBGR pixelDst(GetMetrics(), GetPointer(xDst, yDst));
			PixelBGR pixelSrc(GetMetrics(), GetPointer(xSrc, ySrc));
			pixelDst.Paste(pixelSrc, width, height);
		} else if (imageSrc.IsFormat(Format::BGRA)) {
			PixelBGR pixelDst(GetMetrics(), GetPointer(xDst, yDst));
			PixelBGRA pixelSrc(GetMetrics(), GetPointer(xSrc, ySrc));
			pixelDst.Paste(pixelSrc, width, height);
		}
	} else if (IsFormat(Format::BGRA)) {
		if (imageSrc.IsFormat(Format::BGR)) {
			PixelBGRA pixelDst(GetMetrics(), GetPointer(xDst, yDst));
			PixelBGR pixelSrc(GetMetrics(), GetPointer(xSrc, ySrc));
			pixelDst.Paste(pixelSrc, width, height);
		} else if (imageSrc.IsFormat(Format::BGRA)) {
			PixelBGRA pixelDst(GetMetrics(), GetPointer(xDst, yDst));
			PixelBGRA pixelSrc(GetMetrics(), GetPointer(xSrc, ySrc));
			pixelDst.Paste(pixelSrc, width, height);
		}
	}
}

void Image::ResizePaste(size_t xDst, size_t yDst, size_t wdDst, size_t htDst, const Image& imageSrc,
						size_t xSrc, size_t ySrc, size_t wdSrc, size_t htSrc)
{
	if (IsFormat(Format::BGR)) {
		if (imageSrc.IsFormat(Format::BGR)) {
			PixelBGR pixelDst(GetMetrics(), GetPointer(xDst, yDst));
			PixelBGR pixelSrc(GetMetrics(), GetPointer(xSrc, ySrc));
			Pixel::ResizePaste(pixelDst, wdDst, htDst, pixelSrc, wdSrc, htSrc);
		} else if (imageSrc.IsFormat(Format::BGRA)) {
			PixelBGR pixelDst(GetMetrics(), GetPointer(xDst, yDst));
			PixelBGRA pixelSrc(GetMetrics(), GetPointer(xSrc, ySrc));
			Pixel::ResizePaste(pixelDst, wdDst, htDst, pixelSrc, wdSrc, htSrc);
		}
	} else if (IsFormat(Format::BGRA)) {
		if (imageSrc.IsFormat(Format::BGR)) {
			PixelBGRA pixelDst(GetMetrics(), GetPointer(xDst, yDst));
			PixelBGR pixelSrc(GetMetrics(), GetPointer(xSrc, ySrc));
			Pixel::ResizePaste(pixelDst, wdDst, htDst, pixelSrc, wdSrc, htSrc);
		} else if (imageSrc.IsFormat(Format::BGRA)) {
			PixelBGRA pixelDst(GetMetrics(), GetPointer(xDst, yDst));
			PixelBGRA pixelSrc(GetMetrics(), GetPointer(xSrc, ySrc));
			Pixel::ResizePaste(pixelDst, wdDst, htDst, pixelSrc, wdSrc, htSrc);
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
