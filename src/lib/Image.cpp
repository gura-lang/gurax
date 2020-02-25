//==============================================================================
// Image.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax/VType_Image.h>

namespace Gurax {

//------------------------------------------------------------------------------
// Image::Format
//------------------------------------------------------------------------------
const Image::Format Image::Format::None(0);
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
				   bytesPerPixel, bytesPerLine);
}

Image::Scanner Image::Scanner::LeftTopVert(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointer(x, y), height, width,
				   bytesPerLine, bytesPerPixel);
}

Image::Scanner Image::Scanner::RightTopHorz(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointer(x + width - 1, y), width, height,
				   -bytesPerPixel, bytesPerLine);
}

Image::Scanner Image::Scanner::RightTopVert(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointer(x + width - 1, y), height, width,
				   bytesPerLine, -bytesPerPixel);
}

Image::Scanner Image::Scanner::LeftBottomHorz(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointer(x, y + height - 1), width, height,
				   bytesPerPixel, -bytesPerLine);
}

Image::Scanner Image::Scanner::LeftBottomVert(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointer(x, y + height - 1), height, width,
				   -bytesPerLine, bytesPerPixel);
}

Image::Scanner Image::Scanner::RightBottomHorz(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointer(x + width - 1, y + height - 1), width, height,
				   -bytesPerPixel, -bytesPerLine);
}

Image::Scanner Image::Scanner::RightBottomVert(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointer(x + width - 1, y + height - 1), height, width,
				   -bytesPerLine, -bytesPerPixel);
}

template<>
void Image::Scanner::PutPixel<Image::PixelRGB, Image::PixelRGB>(const UInt8* p)
{
	::memcpy(GetPointer(), p, PixelRGB::bytesPerPixel);
}

template<>
void Image::Scanner::PutPixel<Image::PixelRGB, Image::PixelRGBA>(const UInt8* p)
{
	SetRGB(GetPointer(), Image::GetR(p), Image::GetG(p), Image::GetB(p));
}

template<>
void Image::Scanner::PutPixel<Image::PixelRGBA, Image::PixelRGB>(const UInt8* p)
{
	SetRGBA(GetPointer(), Image::GetR(p), Image::GetG(p), Image::GetB(p),
			GetMetrics().alphaDefault);
}

template<>
void Image::Scanner::PutPixel<Image::PixelRGBA, Image::PixelRGBA>(const UInt8* p)
{
	PixelRGBA::SetPacked(GetPointer(), PixelRGBA::GetPacked(p));
}

template<typename T_PixelDst, typename T_PixelSrc>
void Image::Scanner::PasteT(Scanner& scannerDst, Scanner& scannerSrc)
{
	do {
		scannerDst.PutPixel<T_PixelDst, T_PixelSrc>(scannerSrc.GetPointer());
	} while (scannerDst.Next(scannerSrc));
}

void Image::Scanner::Paste(Scanner& scannerDst, Scanner& scannerSrc)
{
	if (scannerDst.IsFormat(Format::RGB)) {
		if (scannerSrc.IsFormat(Format::RGB)) {
			Scanner::PasteT<PixelRGB, PixelRGB>(scannerDst, scannerSrc);
		} else if (scannerSrc.IsFormat(Format::RGBA)) {
			Scanner::PasteT<PixelRGB, PixelRGBA>(scannerDst, scannerSrc);
		}
	} else if (scannerDst.IsFormat(Format::RGBA)) {
		if (scannerSrc.IsFormat(Format::RGB)) {
			Scanner::PasteT<PixelRGBA, PixelRGB>(scannerDst, scannerSrc);
		} else if (scannerSrc.IsFormat(Format::RGBA)) {
			Scanner::PasteT<PixelRGBA, PixelRGBA>(scannerDst, scannerSrc);
		}
	}
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
void Image::Pixel::ResizePasteT(T_PixelDst& pixelDst, size_t wdDst, size_t htDst,
								const T_PixelSrc& pixelSrc, size_t wdSrc, size_t htSrc)
{
	RefPtr<Memory> pMemory(new MemoryHeap(sizeof(Accumulator) * wdDst));
	pMemory->Fill(0x00);
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
			pMemory->Fill(0x00);
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
void Image::Bootup()
{
}

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

template<typename T_PixelDst, typename T_PixelSrc>
Image* Image::RotateT(const Format& format, double angleDeg, const Color& colorBg) const
{
	double angleRad = Math::DegToRad(angleDeg);
	int cos1024 = static_cast<int>(::cos(angleRad) * 1024);
	int sin1024 = -static_cast<int>(::sin(angleRad) * 1024);
	size_t wdSrc = GetWidth(), htSrc = GetHeight();
	size_t wdDst, htDst;
	CalcRotatesSize(&wdDst, &htDst, wdSrc, htSrc, cos1024, sin1024);
	RefPtr<Image> pImage(new Image(format));
	if (!pImage->Allocate(wdDst, htDst)) return nullptr;
	auto scanner(Scanner::LeftTopHorz(*pImage));
	int xCenterSrc = static_cast<int>(wdSrc / 2);
	int yCenterSrc = static_cast<int>(htSrc / 2);
	int xCenterDst = static_cast<int>(wdDst / 2);
	int yCenterDst = static_cast<int>(htDst / 2);
	do {
		int xDst = static_cast<int>(scanner.GetColIndex()) - xCenterDst;
		int yDst = static_cast<int>(scanner.GetRowIndex()) - yCenterDst;
		int xSrc = ((xDst * cos1024 - yDst * sin1024) >> 10) + xCenterSrc;
		int ySrc = ((xDst * sin1024 + yDst * cos1024) >> 10) + yCenterSrc;
		if (xSrc >= 0 && xSrc < wdSrc && ySrc >= 0 && ySrc <= htSrc) {
			scanner.PutPixel<T_PixelDst, T_PixelSrc>(GetPointer(xSrc, ySrc));
		} else {
			T_PixelDst::SetColor(scanner.GetPointer(), colorBg);
		}
	} while (scanner.Next());
	return pImage.release();
}

Image* Image::Rotate(const Format& format, double angleDeg, const Color& colorBg) const
{
	int angleInt = static_cast<int>(angleDeg) % 360;
	if (angleInt == 180 || angleInt == -180) {
		return Rotate180(format);
	} else if (angleInt == -90 || angleInt == 270) {
		return Rotate90(format);
	} else if (angleInt == 90 || angleInt == -270) {
		return Rotate270(format);
	}
	if (format.IsIdentical(Format::RGB)) {
		if (IsFormat(Format::RGB)) {
			return RotateT<PixelRGB, PixelRGB>(format, angleDeg, colorBg);
		} else if (IsFormat(Format::RGBA)) {
			return RotateT<PixelRGB, PixelRGBA>(format, angleDeg, colorBg);
		}
	} else if (format.IsIdentical(Format::RGBA)) {
		if (IsFormat(Format::RGB)) {
			return RotateT<PixelRGBA, PixelRGB>(format, angleDeg, colorBg);
		} else if (IsFormat(Format::RGBA)) {
			return RotateT<PixelRGBA, PixelRGBA>(format, angleDeg, colorBg);
		}
	}
	return nullptr;
}

Image* Image::Rotate90(const Format& format) const
{
	RefPtr<Image> pImage(new Image(format));
	size_t wdSrc = GetWidth(), htSrc = GetHeight();
	size_t wdDst = htSrc, htDst = wdSrc;
	if (!pImage->Allocate(wdDst, htDst)) return nullptr;
	Scanner scannerDst(Scanner::RightTopVert(*pImage));
	Scanner scannerSrc(Scanner::LeftTopHorz(*this));
	Scanner::Paste(scannerDst, scannerSrc);
	return pImage.release();
}

Image* Image::Rotate270(const Format& format) const
{
	RefPtr<Image> pImage(new Image(format));
	size_t wdSrc = GetWidth(), htSrc = GetHeight();
	size_t wdDst = htSrc, htDst = wdSrc;
	if (!pImage->Allocate(wdDst, htDst)) return nullptr;
	Scanner scannerDst(Scanner::LeftBottomVert(*pImage));
	Scanner scannerSrc(Scanner::LeftTopHorz(*this));
	Scanner::Paste(scannerDst, scannerSrc);
	return pImage.release();
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

void Image::ResizePaste(size_t xDst, size_t yDst, size_t wdDst, size_t htDst, const Image& imageSrc,
						size_t xSrc, size_t ySrc, size_t wdSrc, size_t htSrc)
{
	if (IsFormat(Format::RGB)) {
		if (imageSrc.IsFormat(Format::RGB)) {
			auto pixelDst(GetPixel<PixelRGB>(xDst, yDst));
			auto pixelSrc(imageSrc.GetPixel<PixelRGB>(xSrc, ySrc));
			Pixel::ResizePasteT(pixelDst, wdDst, htDst, pixelSrc, wdSrc, htSrc);
		} else if (imageSrc.IsFormat(Format::RGBA)) {
			auto pixelDst(GetPixel<PixelRGB>(xDst, yDst));
			auto pixelSrc(imageSrc.GetPixel<PixelRGBA>(xSrc, ySrc));
			Pixel::ResizePasteT(pixelDst, wdDst, htDst, pixelSrc, wdSrc, htSrc);
		}
	} else if (IsFormat(Format::RGBA)) {
		if (imageSrc.IsFormat(Format::RGB)) {
			auto pixelDst(GetPixel<PixelRGBA>(xDst, yDst));
			auto pixelSrc(imageSrc.GetPixel<PixelRGB>(xSrc, ySrc));
			Pixel::ResizePasteT(pixelDst, wdDst, htDst, pixelSrc, wdSrc, htSrc);
		} else if (imageSrc.IsFormat(Format::RGBA)) {
			auto pixelDst(GetPixel<PixelRGBA>(xDst, yDst));
			auto pixelSrc(imageSrc.GetPixel<PixelRGBA>(xSrc, ySrc));
			Pixel::ResizePasteT(pixelDst, wdDst, htDst, pixelSrc, wdSrc, htSrc);
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
	Scanner scannerDst(Scanner::LeftTopHorz(*pImage));
	Scanner scannerSrc(Scanner::CreateByFlip(*this, horzFlag, vertFlag));
	Scanner::Paste(scannerDst, scannerSrc);
	return pImage.release();
}

void Image::CalcRotatesSize(size_t* pWdDst, size_t* pHtDst, size_t wdSrc, size_t htSrc, int cos1024, int sin1024)
{
	int xCenterSrc = static_cast<int>(wdSrc / 2);
	int yCenterSrc = static_cast<int>(htSrc / 2);
	auto RotateCoord = [&](int& xm, int& ym, int x, int y) {
		xm = (x * cos1024 - y * sin1024) >> 10, ym = (x * sin1024 + y * cos1024) >> 10;
	};
	int left = -xCenterSrc;
	int right = left + static_cast<int>(wdSrc);
	int bottom = -yCenterSrc;
	int top = bottom + static_cast<int>(htSrc);
	int xs[4], ys[4];
	RotateCoord(xs[0], ys[0], left, top);
	RotateCoord(xs[1], ys[1], left, bottom);
	RotateCoord(xs[2], ys[2], right, top);
	RotateCoord(xs[3], ys[3], right, bottom);
	int xMin = *std::min_element(xs, xs + 4);
	int xMax = *std::max_element(xs, xs + 4);
	int yMin = *std::min_element(ys, ys + 4);
	int yMax = *std::max_element(ys, ys + 4);
	*pWdDst = xMax - xMin;
	*pHtDst = yMax - yMin;
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
