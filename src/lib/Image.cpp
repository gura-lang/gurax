//==============================================================================
// Image.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax/VType_Image.h>

namespace Gurax {

//------------------------------------------------------------------------------
// Image::Format
//------------------------------------------------------------------------------
const Image::Format Image::Format::None(3);
const Image::Format Image::Format::RGB(3);
const Image::Format Image::Format::RGBA(4);

//------------------------------------------------------------------------------
// Image::Metrics
//------------------------------------------------------------------------------
bool Image::Metrics::AdjustCoord(Rect* pRect, int x, int y, int width, int height) const
{
	if (x < 0) {
		width += x;
		x = 0;
	}
	if (width <= 0 || x >= static_cast<int>(this->width)) return false;
	if (y < 0) {
		height += y;
		y = 0;
	}
	if (height <= 0 || y >= static_cast<int>(this->height)) return false;
	if (x + width > static_cast<int>(this->width)) width = static_cast<int>(this->width) - x;
	if (y + height > static_cast<int>(this->height)) height = static_cast<int>(this->height) - y;
	return true;
}

bool Image::Metrics::CheckCoord(int x, int y) const
{
	if (0 <= x && x < static_cast<int>(width) && 0 <= y && y < static_cast<int>(height)) return true;
	Error::Issue(ErrorType::RangeError, "out of image size");
	return false;
}		

//------------------------------------------------------------------------------
// Image::Accumulator
//------------------------------------------------------------------------------
template<> inline void Image::Accumulator::Store<Image::PixelRGB>(const UInt8* pSrc)
{
	b += *(pSrc + 0), g += *(pSrc + 1), r += *(pSrc + 2), n++;
}

template<> inline void Image::Accumulator::Store<Image::PixelRGBA>(const UInt8* pSrc)
{
	b += *(pSrc + 0), g += *(pSrc + 1), r += *(pSrc + 2), a += *(pSrc + 3), n++;
}

template<> inline void Image::Accumulator::Extract<Image::PixelRGB>(UInt8* pDst)
{
	*(pDst + 0) = static_cast<UInt8>(b / n), *(pDst + 1) = static_cast<UInt8>(g / n);
	*(pDst + 2) = static_cast<UInt8>(r / n);
}

template<> inline void Image::Accumulator::Extract<Image::PixelRGBA>(UInt8* pDst)
{
	*(pDst + 0) = static_cast<UInt8>(b / n), *(pDst + 1) = static_cast<UInt8>(g / n);
	*(pDst + 2) = static_cast<UInt8>(r / n), *(pDst + 3) = static_cast<UInt8>(a / n);
}

//------------------------------------------------------------------------------
// Image::Scanner
//------------------------------------------------------------------------------
Image::Scanner Image::Scanner::CreateByDir(const Image& image, size_t x, size_t y, size_t width, size_t height, ScanDir scanDir)
{
	return
		(scanDir == ScanDir::LeftTopHorz)?     LeftTopHorz(image, x, y, width, height) :
		(scanDir == ScanDir::LeftTopVert)?     LeftTopVert(image, x, y, width, height) :
		(scanDir == ScanDir::RightTopHorz)?    RightTopHorz(image, x, y, width, height) :
		(scanDir == ScanDir::RightTopVert)?    RightTopVert(image, x, y, width, height) :
		(scanDir == ScanDir::LeftBottomHorz)?  LeftBottomHorz(image, x, y, width, height) :
		(scanDir == ScanDir::LeftBottomVert)?  LeftBottomVert(image, x, y, width, height) :
		(scanDir == ScanDir::RightBottomHorz)? RightBottomHorz(image, x, y, width, height) :
		(scanDir == ScanDir::RightBottomVert)? RightBottomVert(image, x, y, width, height) :
		Scanner(image.GetMetrics(), nullptr, 0, 0, 0, 0);
}

Image::Scanner Image::Scanner::CreateByFlip(const Image& image, size_t x, size_t y, size_t width, size_t height,
											bool horzFlag, bool vertFlag)
{
	return
		(horzFlag && vertFlag)?  RightBottomHorz(image, x, y, width, height) :
		(horzFlag && !vertFlag)? RightTopHorz(image, x, y, width, height) :
		(!horzFlag && vertFlag)? LeftBottomHorz(image, x, y, width, height) :
		LeftTopHorz(image, x, y, width, height);
}

Image::Scanner Image::Scanner::LeftTopHorz(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointer(x, y), width, height,
				   bytesPerPixel, bytesPerLine - bytesPerPixel * width);
}

Image::Scanner Image::Scanner::LeftTopVert(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointer(x, y), height, width,
				   bytesPerLine, bytesPerPixel - bytesPerLine * height);
}

Image::Scanner Image::Scanner::RightTopHorz(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointer(x + width - 1, y), width, height,
				   -bytesPerPixel, bytesPerLine + bytesPerPixel * width);
}

Image::Scanner Image::Scanner::RightTopVert(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointer(x + width - 1, y), height, width,
				   bytesPerLine, -bytesPerPixel - bytesPerLine * height);
}

Image::Scanner Image::Scanner::LeftBottomHorz(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointer(x, y + height - 1), width, height,
				   bytesPerPixel, -bytesPerLine - bytesPerPixel * width);
}

Image::Scanner Image::Scanner::LeftBottomVert(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointer(x, y + height - 1), height, width,
				   -bytesPerLine, bytesPerPixel + bytesPerLine * height);
}

Image::Scanner Image::Scanner::RightBottomHorz(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointer(x + width - 1, y + height - 1), width, height,
				   -bytesPerPixel, -bytesPerLine + bytesPerPixel * width);
}

Image::Scanner Image::Scanner::RightBottomVert(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointer(x + width - 1, y + height - 1), height, width,
				   -bytesPerLine, -bytesPerPixel + bytesPerLine * height);
}

template<>
void Image::Scanner::PutPixel<Image::PixelRGB, Image::PixelRGB>(Scanner& scannerDst, Scanner& scannerSrc)
{
	::memcpy(scannerDst.GetPointer(), scannerSrc.GetPointer(), PixelRGB::bytesPerPixel);
}

template<>
void Image::Scanner::PutPixel<Image::PixelRGB, Image::PixelRGBA>(Scanner& scannerDst, Scanner& scannerSrc)
{
	const UInt8* p = scannerSrc.GetPointer();
	PixelRGB::SetRGB(scannerDst.GetPointer(), PixelRGBA::GetR(p), PixelRGBA::GetG(p), PixelRGBA::GetB(p));
}

template<>
void Image::Scanner::PutPixel<Image::PixelRGBA, Image::PixelRGB>(Scanner& scannerDst, Scanner& scannerSrc)
{
	const UInt8* p = scannerSrc.GetPointer();
	PixelRGBA::SetRGBA(scannerDst.GetPointer(), PixelRGB::GetR(p), PixelRGB::GetG(p), PixelRGB::GetB(p),
					   scannerDst.GetMetrics().alphaDefault);
}

template<>
void Image::Scanner::PutPixel<Image::PixelRGBA, Image::PixelRGBA>(Scanner& scannerDst, Scanner& scannerSrc)
{
	PixelRGBA::SetPacked(scannerDst.GetPointer(), PixelRGBA::GetPacked(scannerSrc.GetPointer()));
}

template<typename T_PixelDst, typename T_PixelSrc>
void Image::Scanner::Paste(Scanner& scannerDst, Scanner& scannerSrc)
{
	do {
		PutPixel<T_PixelDst, T_PixelSrc>(scannerDst, scannerSrc);
	} while (scannerDst.Next(scannerSrc));
}

//------------------------------------------------------------------------------
// Image::Pixel
//------------------------------------------------------------------------------
void Image::Pixel::PasteSame(Pixel& pixelDst, const Pixel& pixelSrc, size_t width, size_t height)
{
	UInt8* pLineDst = pixelDst.GetPointer();
	const UInt8* pLineSrc = pixelSrc.GetPointer();
	size_t bytesToCopy = pixelDst.WidthToBytes(width);
	for (size_t y = 0; y < height; y++) {
		::memcpy(pLineDst, pLineSrc, bytesToCopy);
		pLineDst += pixelDst.GetBytesPerLine();
		pLineSrc += pixelSrc.GetBytesPerLine();
	}
}

void Image::Pixel::Paste(PixelRGB& pixelDst, const PixelRGB& pixelSrc, size_t width, size_t height)
{
	PasteSame(pixelDst, pixelSrc, width, height);
}

void Image::Pixel::Paste(PixelRGBA& pixelDst, const PixelRGBA& pixelSrc, size_t width, size_t height)
{
	PasteSame(pixelDst, pixelSrc, width, height);
}

void Image::Pixel::Paste(PixelRGB& pixelDst, const PixelRGBA& pixelSrc, size_t width, size_t height)
{
	UInt8* pLineDst = pixelDst.GetPointer();
	const UInt8* pLineSrc = pixelSrc.GetPointer();
	for (size_t y = 0; y < height; y++) {
		UInt8* pDst = pLineDst;
		const UInt8* pSrc = pLineSrc;
		for (size_t x = 0; x < width; x++) {
			*pDst++ = *pSrc++, *pDst++ = *pSrc++, *pDst++ = *pSrc++, pSrc++;
		}
		pLineDst += pixelDst.GetBytesPerLine();
		pLineSrc += pixelSrc.GetBytesPerLine();
	}
}

void Image::Pixel::Paste(PixelRGBA& pixelDst, const PixelRGB& pixelSrc, size_t width, size_t height)
{
	UInt8 alphaDefault = pixelDst.GetAlphaDefault();
	UInt8* pLineDst = pixelDst.GetPointer();
	const UInt8* pLineSrc = pixelSrc.GetPointer();
	for (size_t y = 0; y < height; y++) {
		UInt8* pDst = pLineDst;
		const UInt8* pSrc = pLineSrc;
		for (size_t x = 0; x < width; x++) {
			*pDst++ = *pSrc++, *pDst++ = *pSrc++, *pDst++ = *pSrc++, *pDst++ = alphaDefault;
		}
		pLineDst += pixelDst.GetBytesPerLine();
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
			pSrc += T_PixelSrc::bytesPerPixel;
		}
		htAccum += htDst;
		if (htAccum >= htSrc) {
			UInt8* pDst = pLineDst;
			for (size_t xDst = 0; xDst < wdDst; xDst++) {
				accumulators[xDst].Extract<T_PixelDst>(pDst);
				pDst += T_PixelDst::bytesPerPixel;
			}
			htAccum -= htSrc;
			pLineDst += pixelDst.GetBytesPerLine();
			pMemory->FillZero();
		}
		pLineSrc += pixelSrc.GetBytesPerLine();
	}
}

//------------------------------------------------------------------------------
// Image::PixelRGB
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Image::PixelRGBA
//------------------------------------------------------------------------------

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

bool Image::Read(Stream& stream, const char* imgTypeName)
{
	const ImageMgrList& imageMgrList = Basement::Inst.GetImageMgrList();
	const ImageMgr* pImageMgr;
	RefPtr<Stream> pStream(stream.Reference());
	if (imgTypeName) {
		pImageMgr = imageMgrList.FindByImgTypeName(imgTypeName);
	} else {
		pImageMgr = imageMgrList.FindByFileName(stream.GetIdentifier());
		if (!pImageMgr) {
			pStream.reset(stream.CreateBwdSeekable());
			pImageMgr = imageMgrList.FindResponsible(*pStream);
		}
	}
	if (!pImageMgr) {
		Error::Issue(ErrorType::FormatError, "unsupported image format");
		return false;
	}
	return pImageMgr->Read(stream, *this);
}

bool Image::Write(Stream& stream, const char* imgTypeName) const
{
	const ImageMgrList& imageMgrList = Basement::Inst.GetImageMgrList();
	const ImageMgr* pImageMgr;
	if (imgTypeName) {
		pImageMgr = imageMgrList.FindByImgTypeName(imgTypeName);
	} else {
		pImageMgr = imageMgrList.FindByFileName(stream.GetIdentifier());
	}
	if (!pImageMgr) {
		Error::Issue(ErrorType::FormatError, "unsupported image format");
		return false;
	}
	return pImageMgr->Write(stream, *this);
}

void Image::Fill(const Color& color)
{
	if (IsAreaZero()) return;
	if (IsFormat(Format::RGB)) {
		PixelRGB(GetMetrics(), GetPointer()).SetColorN(color, GetWidth());
	} else if (IsFormat(Format::RGBA)) {
		PixelRGBA(GetMetrics(), GetPointer()).SetColorN(color, GetWidth());
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
	if (IsFormat(Format::RGB)) {
		PixelRGB(GetMetrics(), GetPointer(x, y)).SetColorN(color, width);
	} else if (IsFormat(Format::RGBA)) {
		PixelRGBA(GetMetrics(), GetPointer(x, y)).SetColorN(color, width);
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
	if (IsFormat(Format::RGB)) {
		if (imageSrc.IsFormat(Format::RGB)) {
			auto pixelDst(GetPixel<PixelRGB>(xDst, yDst));
			auto pixelSrc(imageSrc.GetPixel<PixelRGB>(xSrc, ySrc));
			Pixel::Paste(pixelDst, pixelSrc, width, height);
		} else if (imageSrc.IsFormat(Format::RGBA)) {
			auto pixelDst(GetPixel<PixelRGB>(xDst, yDst));
			auto pixelSrc(imageSrc.GetPixel<PixelRGBA>(xSrc, ySrc));
			Pixel::Paste(pixelDst, pixelSrc, width, height);
		}
	} else if (IsFormat(Format::RGBA)) {
		if (imageSrc.IsFormat(Format::RGB)) {
			auto pixelDst(GetPixel<PixelRGBA>(xDst, yDst));
			auto pixelSrc(imageSrc.GetPixel<PixelRGB>(xSrc, ySrc));
			Pixel::Paste(pixelDst, pixelSrc, width, height);
		} else if (imageSrc.IsFormat(Format::RGBA)) {
			auto pixelDst(GetPixel<PixelRGBA>(xDst, yDst));
			auto pixelSrc(imageSrc.GetPixel<PixelRGBA>(xSrc, ySrc));
			Pixel::Paste(pixelDst, pixelSrc, width, height);
		}
	}
}

void Image::FlipPaste(size_t xDst, size_t yDst, const Image& imageSrc,
					  size_t xSrc, size_t ySrc, size_t width, size_t height, bool horzFlag, bool vertFlag)
{
	Scanner scannerDst(Scanner::LeftTopHorz(*this, xDst, yDst, width, height));
	Scanner scannerSrc(Scanner::CreateByFlip(imageSrc, xSrc, ySrc, width, height, horzFlag, vertFlag));
	if (IsFormat(Format::RGB)) {
		if (imageSrc.IsFormat(Format::RGB)) {
			Scanner::Paste<PixelRGB, PixelRGB>(scannerDst, scannerSrc);
		} else if (imageSrc.IsFormat(Format::RGBA)) {
			Scanner::Paste<PixelRGB, PixelRGBA>(scannerDst, scannerSrc);
		}
	} else if (IsFormat(Format::RGBA)) {
		if (imageSrc.IsFormat(Format::RGB)) {
			Scanner::Paste<PixelRGBA, PixelRGB>(scannerDst, scannerSrc);
		} else if (imageSrc.IsFormat(Format::RGBA)) {
			Scanner::Paste<PixelRGBA, PixelRGBA>(scannerDst, scannerSrc);
		}
	}
}

void Image::ResizePaste(size_t xDst, size_t yDst, size_t wdDst, size_t htDst, const Image& imageSrc,
						size_t xSrc, size_t ySrc, size_t wdSrc, size_t htSrc)
{
	if (IsFormat(Format::RGB)) {
		if (imageSrc.IsFormat(Format::RGB)) {
			auto pixelDst(GetPixel<PixelRGB>(xDst, yDst));
			auto pixelSrc(imageSrc.GetPixel<PixelRGB>(xSrc, ySrc));
			Pixel::ResizePaste(pixelDst, wdDst, htDst, pixelSrc, wdSrc, htSrc);
		} else if (imageSrc.IsFormat(Format::RGBA)) {
			auto pixelDst(GetPixel<PixelRGB>(xDst, yDst));
			auto pixelSrc(imageSrc.GetPixel<PixelRGBA>(xSrc, ySrc));
			Pixel::ResizePaste(pixelDst, wdDst, htDst, pixelSrc, wdSrc, htSrc);
		}
	} else if (IsFormat(Format::RGBA)) {
		if (imageSrc.IsFormat(Format::RGB)) {
			auto pixelDst(GetPixel<PixelRGBA>(xDst, yDst));
			auto pixelSrc(imageSrc.GetPixel<PixelRGB>(xSrc, ySrc));
			Pixel::ResizePaste(pixelDst, wdDst, htDst, pixelSrc, wdSrc, htSrc);
		} else if (imageSrc.IsFormat(Format::RGBA)) {
			auto pixelDst(GetPixel<PixelRGBA>(xDst, yDst));
			auto pixelSrc(imageSrc.GetPixel<PixelRGBA>(xSrc, ySrc));
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

Image* Image::Resize(const Format& format, size_t width, size_t height) const
{
	RefPtr<Image> pImage(new Image(format));
	if (!pImage->Allocate(width, height)) return nullptr;
	pImage->ResizePaste(0, 0, width, height, *this, 0, 0, GetWidth(), GetHeight());
	return pImage.release();
}

Image* Image::Flip(const Format& format, bool horzFlag, bool vertFlag) const
{
	RefPtr<Image> pImage(new Image(format));
	if (!pImage->Allocate(GetWidth(), GetHeight())) return nullptr;
	pImage->FlipPaste(0, 0, *this, 0, 0, GetWidth(), GetHeight(), horzFlag, vertFlag);
	return pImage.release();
}

const Image::Format& Image::SymbolToFormat(const Symbol* pSymbol)
{
	return
		pSymbol->IsIdentical(Gurax_Symbol(rgb))? Format::RGB :
		pSymbol->IsIdentical(Gurax_Symbol(rgba))? Format::RGBA :
		Format::None;
}

String Image::ToString(const StringStyle& ss) const
{
	String str;
	str += "Image";
	str.Printf("%zux%zu", GetWidth(), GetHeight());
	return str;
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
