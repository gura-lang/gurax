//==============================================================================
// Image.cpp
//==============================================================================
#include "stdafx.h"
#undef RGB
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
	pRect->x = x, pRect->y = y, pRect->width = width, pRect->height = height;
	return true;
}

bool Image::Metrics::CheckCoord(int x, int y) const
{
	if (0 <= x && x < static_cast<int>(width) && 0 <= y && y < static_cast<int>(height)) return true;
	Error::Issue(ErrorType::RangeError, "out of image size");
	return false;
}

bool Image::Metrics::CheckArea(int x, int y, int width, int height) const
{
	if (0 <= x && 0 <= width && x + width <= static_cast<int>(this->width) &&
		0 <= y && 0 <= height && y + height <= static_cast<int>(this->height)) return true;
	Error::Issue(ErrorType::RangeError, "out of image size");
	return false;
}

//------------------------------------------------------------------------------
// Image::Accumulator
//------------------------------------------------------------------------------
Image::Accumulator::Accumulator(size_t width) :
	_pMemory(new MemoryHeap(sizeof(Elem) * width)), _pElem(_pMemory->GetPointerC<Elem>())
{
	Clear();
}

template<> inline void Image::Accumulator::
Store<Image::PixelRGB>(size_t idx, const UInt8* pSrc) { StoreBGR(idx, pSrc); }

template<> inline void Image::Accumulator::
Store<Image::PixelRGBA>(size_t idx, const UInt8* pSrc) { StoreBGRA(idx, pSrc); }

template<> inline void Image::Accumulator::
Extract<Image::PixelRGB>(size_t idx, UInt8* pDst) { ExtractBGR(idx, pDst); }

template<> inline void Image::Accumulator::
Extract<Image::PixelRGBA>(size_t idx, UInt8* pDst) { ExtractBGRA(idx, pDst); }

//------------------------------------------------------------------------------
// Image::Scanner
//------------------------------------------------------------------------------
Image::Scanner Image::Scanner::CreateByDir(const Image& image, size_t x, size_t y, size_t width, size_t height, ScanDir scanDir)
{
	return
		(scanDir == ScanDir::LeftTopHorz)?     LeftTopHorz(image, x, y, width, height) :
		(scanDir == ScanDir::LeftTopVert)?     LeftTopVert(image, x, y, width, height) :
		(scanDir == ScanDir::LeftBottomHorz)?  LeftBottomHorz(image, x, y, width, height) :
		(scanDir == ScanDir::LeftBottomVert)?  LeftBottomVert(image, x, y, width, height) :
		(scanDir == ScanDir::RightTopHorz)?    RightTopHorz(image, x, y, width, height) :
		(scanDir == ScanDir::RightTopVert)?    RightTopVert(image, x, y, width, height) :
		(scanDir == ScanDir::RightBottomHorz)? RightBottomHorz(image, x, y, width, height) :
		(scanDir == ScanDir::RightBottomVert)? RightBottomVert(image, x, y, width, height) :
		Scanner(image.GetMetrics(), nullptr, 0, 0, 0, 0, 0, 0, true);
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
	return Scanner(image.GetMetrics(), image.GetPointerC(x, y), x, y, width, height,
					bytesPerPixel, bytesPerLine, true);
}

Image::Scanner Image::Scanner::LeftTopVert(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointerC(x, y), x, y, height, width,
					bytesPerLine, bytesPerPixel, false);
}

Image::Scanner Image::Scanner::LeftBottomHorz(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointerC(x, y + height - 1), x, y, width, height,
					bytesPerPixel, -bytesPerLine, true);
}

Image::Scanner Image::Scanner::LeftBottomVert(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointerC(x, y + height - 1), x, y, height, width,
					-bytesPerLine, bytesPerPixel, false);
}

Image::Scanner Image::Scanner::RightTopHorz(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointerC(x + width - 1, y), x, y, width, height,
					-bytesPerPixel, bytesPerLine, true);
}

Image::Scanner Image::Scanner::RightTopVert(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointerC(x + width - 1, y), x, y, height, width,
					bytesPerLine, -bytesPerPixel, false);
}

Image::Scanner Image::Scanner::RightBottomHorz(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointerC(x + width - 1, y + height - 1), x, y, width, height,
					-bytesPerPixel, -bytesPerLine, true);
}

Image::Scanner Image::Scanner::RightBottomVert(const Image& image, size_t x, size_t y, size_t width, size_t height)
{
	int bytesPerPixel = static_cast<int>(image.GetBytesPerPixel());
	int bytesPerLine = static_cast<int>(image.GetBytesPerLine());
	return Scanner(image.GetMetrics(), image.GetPointerC(x + width - 1, y + height - 1), x, y, height, width,
					-bytesPerLine, -bytesPerPixel, false);
}

template<>
void Image::Scanner::PutPixel<Image::PixelRGB, Image::PixelRGB>(const UInt8* p)
{
	::memcpy(GetPointerC(), p, PixelRGB::bytesPerPixel);
}

template<>
void Image::Scanner::PutPixel<Image::PixelRGB, Image::PixelRGBA>(const UInt8* p)
{
	PixelRGB::SetRGB(GetPointerC(), Pixel::GetR(p), Pixel::GetG(p), Pixel::GetB(p));
}

template<>
void Image::Scanner::PutPixel<Image::PixelRGBA, Image::PixelRGB>(const UInt8* p)
{
	PixelRGBA::SetRGBA(GetPointerC(), Pixel::GetR(p), Pixel::GetG(p), Pixel::GetB(p),
						GetMetrics().alphaDefault);
}

template<>
void Image::Scanner::PutPixel<Image::PixelRGBA, Image::PixelRGBA>(const UInt8* p)
{
	PixelRGBA::SetPacked(GetPointerC(), PixelRGBA::GetPacked(p));
}

template<typename T_PixelDst, typename T_PixelSrc>
void Image::Scanner::PasteT(Scanner& scannerDst, Scanner& scannerSrc)
{
	do {
		scannerDst.PutPixel<T_PixelDst, T_PixelSrc>(scannerSrc.GetPointerC());
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
	UInt8* pLineDst = pixelDst.GetPointerC();
	const UInt8* pLineSrc = pixelSrc.GetPointerC();
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
	UInt8* pLineDst = pixelDst.GetPointerC();
	const UInt8* pLineSrc = pixelSrc.GetPointerC();
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
	UInt8* pLineDst = pixelDst.GetPointerC();
	const UInt8* pLineSrc = pixelSrc.GetPointerC();
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

void Image::CopyRef(const Image& image)
{

	_pMemory.reset(image._pMemory.Reference());
	_pPalette.reset(image._pPalette.Reference());
	_metrics = image._metrics;
	_pValueExtra.reset(image._pValueExtra.Reference());
}

bool Image::Allocate(size_t width, size_t height)
{
	size_t bytes = WidthToBytes(width) * height;
	_metrics.width = width, _metrics.height = height;
	_metrics.Update();
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
		if (xSrc >= 0 && xSrc < static_cast<int>(wdSrc) && ySrc >= 0 && ySrc < static_cast<int>(htSrc)) {
			scanner.PutPixel<T_PixelDst, T_PixelSrc>(GetPointerC(xSrc, ySrc));
		} else {
			T_PixelDst::SetColor(scanner.GetPointerC(), colorBg);
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
		return Rotate270(format);
	} else if (angleInt == 90 || angleInt == -270) {
		return Rotate90(format);
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
	UInt8* pLineSrc = GetPointerC();
	if (IsFormat(Format::RGB)) {
		PixelRGB(GetMetrics(), pLineSrc).SetColorN(color, GetWidth());
	} else if (IsFormat(Format::RGBA)) {
		PixelRGBA(GetMetrics(), pLineSrc).SetColorN(color, GetWidth());
	}
	UInt8* pLineDst = pLineSrc + GetBytesPerLine();
	size_t bytesToCopy = GetBytesPerLine();
	for (size_t i = 1; i < GetHeight(); i++, pLineDst += GetBytesPerLine()) {
		::memcpy(pLineDst, pLineSrc, bytesToCopy);
	}
}

void Image::FillRect(size_t x, size_t y, size_t width, size_t height, const Color& color)
{
	if (width == 0 || height == 0) return;
	UInt8* pLineSrc = GetPointerC(x, y);
	if (IsFormat(Format::RGB)) {
		PixelRGB(GetMetrics(), pLineSrc).SetColorN(color, width);
	} else if (IsFormat(Format::RGBA)) {
		PixelRGBA(GetMetrics(), pLineSrc).SetColorN(color, width);
	}
	UInt8* pLineDst = pLineSrc + GetBytesPerLine();
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
			auto pixelDst(MakePixel<PixelRGB>(xDst, yDst));
			auto pixelSrc(imageSrc.MakePixel<PixelRGB>(xSrc, ySrc));
			Pixel::Paste(pixelDst, pixelSrc, width, height);
		} else if (imageSrc.IsFormat(Format::RGBA)) {
			auto pixelDst(MakePixel<PixelRGB>(xDst, yDst));
			auto pixelSrc(imageSrc.MakePixel<PixelRGBA>(xSrc, ySrc));
			Pixel::Paste(pixelDst, pixelSrc, width, height);
		}
	} else if (IsFormat(Format::RGBA)) {
		if (imageSrc.IsFormat(Format::RGB)) {
			auto pixelDst(MakePixel<PixelRGBA>(xDst, yDst));
			auto pixelSrc(imageSrc.MakePixel<PixelRGB>(xSrc, ySrc));
			Pixel::Paste(pixelDst, pixelSrc, width, height);
		} else if (imageSrc.IsFormat(Format::RGBA)) {
			auto pixelDst(MakePixel<PixelRGBA>(xDst, yDst));
			auto pixelSrc(imageSrc.MakePixel<PixelRGBA>(xSrc, ySrc));
			Pixel::Paste(pixelDst, pixelSrc, width, height);
		}
	}
}

template<typename T_PixelDst, typename T_PixelSrc>
void Image::ResizePasteT(T_PixelDst& pixelDst, size_t wdDst, size_t htDst,
						const T_PixelSrc& pixelSrc, size_t wdSrc, size_t htSrc)
{
	Accumulator accumulator(wdDst);
	UInt8* pLineDst = pixelDst.GetPointerC();
	const UInt8* pLineSrc = pixelSrc.GetPointerC();
	size_t htAccum = 0;
	if (wdDst == wdSrc && htDst == htSrc) {
		Pixel::Paste(pixelDst, pixelSrc, wdDst, htDst);
	} else if (wdDst < wdSrc && htDst < htSrc) {
		for (size_t ySrc = 0; ySrc < htSrc; ySrc++) {
			const UInt8* pSrc = pLineSrc;
			size_t wdAccum = 0;
			size_t xDst = 0;
			for (size_t xSrc = 0; xSrc < wdSrc; xSrc++) {
				accumulator.Store<T_PixelSrc>(xDst, pSrc);
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
					accumulator.Extract<T_PixelDst>(xDst, pDst);
					pDst += T_PixelDst::bytesPerPixel;
				}
				htAccum -= htSrc;
				pLineDst += pixelDst.GetBytesPerLine();
				accumulator.Clear();
			}
			pLineSrc += pixelSrc.GetBytesPerLine();
		}
	} else if (wdDst > wdSrc && htDst > htSrc) {
		size_t yAccum = 0, yOffset = 0;
		for (size_t yDst = 0; yDst < htDst; yDst++) {
			size_t xAccum = 0;
			const UInt8* pSrc = pLineSrc;
			const UInt8* pDst = pLineDst;
			for (size_t xDst = 0; xDst < wdDst; xDst++) {
				
				xAccum += wdSrc;
				if (xAccum >= wdDst) {
					pSrc++;
					xAccum -= wdDst;
				}
			}
			yAccum += htSrc;
			if (yAccum >= htDst) {
				pLineSrc += pixelSrc.GetBytesPerLine();
				yAccum -= htDst;

			}
			pLineDst += pixelDst.GetBytesPerLine();
		}
	}
}

void Image::ResizePaste(size_t xDst, size_t yDst, size_t wdDst, size_t htDst, const Image& imageSrc,
						size_t xSrc, size_t ySrc, size_t wdSrc, size_t htSrc)
{
	if (IsFormat(Format::RGB)) {
		if (imageSrc.IsFormat(Format::RGB)) {
			auto pixelDst(MakePixel<PixelRGB>(xDst, yDst));
			auto pixelSrc(imageSrc.MakePixel<PixelRGB>(xSrc, ySrc));
			ResizePasteT(pixelDst, wdDst, htDst, pixelSrc, wdSrc, htSrc);
		} else if (imageSrc.IsFormat(Format::RGBA)) {
			auto pixelDst(MakePixel<PixelRGB>(xDst, yDst));
			auto pixelSrc(imageSrc.MakePixel<PixelRGBA>(xSrc, ySrc));
			ResizePasteT(pixelDst, wdDst, htDst, pixelSrc, wdSrc, htSrc);
		}
	} else if (IsFormat(Format::RGBA)) {
		if (imageSrc.IsFormat(Format::RGB)) {
			auto pixelDst(MakePixel<PixelRGBA>(xDst, yDst));
			auto pixelSrc(imageSrc.MakePixel<PixelRGB>(xSrc, ySrc));
			ResizePasteT(pixelDst, wdDst, htDst, pixelSrc, wdSrc, htSrc);
		} else if (imageSrc.IsFormat(Format::RGBA)) {
			auto pixelDst(MakePixel<PixelRGBA>(xDst, yDst));
			auto pixelSrc(imageSrc.MakePixel<PixelRGBA>(xSrc, ySrc));
			ResizePasteT(pixelDst, wdDst, htDst, pixelSrc, wdSrc, htSrc);
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

template<typename T_PixelDst, typename T_PixelSrc>
void Image::GrayScaleT(T_PixelDst& pixelDst, T_PixelSrc& pixelSrc)
{
	UInt8* pDst = pixelDst.GetPointerC();
	const UInt8* pSrc = pixelSrc.GetPointerC();
	UInt8 alphaDefault = pixelDst.GetMetrics().alphaDefault;
	size_t nPixels = pixelDst.GetMetrics().CountPixels();
	for (size_t iPixel = 0; iPixel < nPixels; iPixel++) {
		UInt8 gray = Color::CalcGray(Pixel::GetR(pSrc), Pixel::GetG(pSrc), Pixel::GetB(pSrc));
		T_PixelDst::SetRGBA(pDst, gray, gray, gray, T_PixelSrc::GetA(pSrc, alphaDefault));
		pDst += T_PixelDst::bytesPerPixel;
		pSrc += T_PixelSrc::bytesPerPixel;
	}
}

Image* Image::GrayScale(const Format& format) const
{
	RefPtr<Image> pImage(new Image(format));
	if (!pImage->Allocate(GetWidth(), GetHeight())) return nullptr;
	if (format.IsIdentical(Format::RGB)) {
		if (IsFormat(Format::RGB)) {
			auto pixelDst(pImage->MakePixel<PixelRGB>());
			auto pixelSrc(MakePixel<PixelRGB>());
			GrayScaleT(pixelDst, pixelSrc);
		} else if (IsFormat(Format::RGBA)) {
			auto pixelDst(pImage->MakePixel<PixelRGB>());
			auto pixelSrc(MakePixel<PixelRGBA>());
			GrayScaleT(pixelDst, pixelSrc);
		}
	} else if (format.IsIdentical(Format::RGBA)) {
		if (IsFormat(Format::RGB)) {
			auto pixelDst(pImage->MakePixel<PixelRGBA>());
			auto pixelSrc(MakePixel<PixelRGB>());
			GrayScaleT(pixelDst, pixelSrc);
		} else if (IsFormat(Format::RGBA)) {
			auto pixelDst(pImage->MakePixel<PixelRGBA>());
			auto pixelSrc(MakePixel<PixelRGBA>());
			GrayScaleT(pixelDst, pixelSrc);
		}
	}
	return pImage.release();
}

template<typename T_PixelDst, typename T_PixelSrc>
void Image::MapColorLevelT(T_PixelDst& pixelDst, T_PixelSrc& pixelSrc,
							const UInt8* mapR, const UInt8* mapG, const UInt8* mapB)
{
	UInt8* pDst = pixelDst.GetPointerC();
	const UInt8* pSrc = pixelSrc.GetPointerC();
	UInt8 alphaDefault = pixelDst.GetMetrics().alphaDefault;
	size_t nPixels = pixelDst.GetMetrics().CountPixels();
	for (size_t iPixel = 0; iPixel < nPixels; iPixel++) {
		T_PixelDst::SetRGBA(pDst, mapR[Pixel::GetR(pSrc)], mapG[Pixel::GetG(pSrc)],
							mapB[Pixel::GetB(pSrc)], T_PixelSrc::GetA(pSrc, alphaDefault));
		pDst += T_PixelDst::bytesPerPixel;
		pSrc += T_PixelSrc::bytesPerPixel;
	}
}

Image* Image::MapColorLevel(const Format& format, const UInt8* mapR, const UInt8* mapG, const UInt8* mapB) const
{
	RefPtr<Image> pImage(new Image(format));
	if (!pImage->Allocate(GetWidth(), GetHeight())) return nullptr;
	if (format.IsIdentical(Format::RGB)) {
		if (IsFormat(Format::RGB)) {
			auto pixelDst(pImage->MakePixel<PixelRGB>());
			auto pixelSrc(MakePixel<PixelRGB>());
			MapColorLevelT(pixelDst, pixelSrc, mapR, mapG, mapB);
		} else if (IsFormat(Format::RGBA)) {
			auto pixelDst(pImage->MakePixel<PixelRGB>());
			auto pixelSrc(MakePixel<PixelRGBA>());
			MapColorLevelT(pixelDst, pixelSrc, mapR, mapG, mapB);
		}
	} else if (format.IsIdentical(Format::RGBA)) {
		if (IsFormat(Format::RGB)) {
			auto pixelDst(pImage->MakePixel<PixelRGBA>());
			auto pixelSrc(MakePixel<PixelRGB>());
			MapColorLevelT(pixelDst, pixelSrc, mapR, mapG, mapB);
		} else if (IsFormat(Format::RGBA)) {
			auto pixelDst(pImage->MakePixel<PixelRGBA>());
			auto pixelSrc(MakePixel<PixelRGBA>());
			MapColorLevelT(pixelDst, pixelSrc, mapR, mapG, mapB);
		}
	}
	return pImage.release();
}

Image* Image::MapAlphaLevel(const UInt8* mapA) const
{
	if (!IsFormat(Format::RGBA)) return nullptr;
	RefPtr<Image> pImage(new Image(GetFormat()));
	if (!pImage->Allocate(GetWidth(), GetHeight())) return nullptr;
	UInt8* pDst = pImage->GetPointerC();
	const UInt8* pSrc = GetPointerC();
	size_t nPixels = GetMetrics().CountPixels();
	for (size_t iPixel = 0; iPixel < nPixels; iPixel++) {
		PixelRGBA::SetRGBA(pDst, PixelRGBA::GetR(pSrc), PixelRGBA::GetG(pSrc),
							PixelRGBA::GetB(pSrc), mapA[PixelRGBA::GetA(pSrc)]);
		pDst += PixelRGBA::bytesPerPixel;
		pSrc += PixelRGBA::bytesPerPixel;
	}
	return pImage.release();
}

Image* Image::ReduceColor(const Palette& palette) const
{
	RefPtr<Image> pImage(new Image(GetFormat()));
	if (!pImage->Allocate(GetWidth(), GetHeight())) return nullptr;
	UInt8* pDst = pImage->GetPointerC();
	const UInt8* pSrc = GetPointerC();
	size_t nPixels = GetMetrics().CountPixels();
	if (GetFormat().IsIdentical(Format::RGB)) {
		for (size_t iPixel = 0; iPixel < nPixels; iPixel++,
				pSrc += Format::RGB.bytesPerPixel, pDst += Format::RGB.bytesPerPixel) {
			size_t idx = palette.LookupNearest(PixelRGB::GetR(pSrc), PixelRGB::GetG(pSrc), PixelRGB::GetG(pSrc));
			PixelRGB::SetColor(pDst, palette.GetColor(idx));
		}
	} else {
		for (size_t iPixel = 0; iPixel < nPixels; iPixel++,
				pSrc += Format::RGBA.bytesPerPixel, pDst += Format::RGBA.bytesPerPixel) {
			size_t idx = palette.LookupNearest(PixelRGBA::GetR(pSrc), PixelRGBA::GetG(pSrc), PixelRGBA::GetG(pSrc));
			const Color& color = palette.GetColor(idx);
			PixelRGBA::SetRGBA(pDst, color.GetR(), color.GetG(), color.GetB(), PixelRGBA::GetA(pSrc));
		}
	}
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

const Symbol* Image::FormatToSymbol(const Format& format)
{
	return format.IsIdentical(Format::RGB)? Gurax_Symbol(rgb) :
		format.IsIdentical(Format::RGBA)? Gurax_Symbol(rgba) : Gurax_Symbol(none);
}

String Image::ToString(const StringStyle& ss) const
{
	return String().Format("Image:%s:%zux%zu",
			FormatToSymbol(GetFormat())->GetName(), GetWidth(), GetHeight());
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
