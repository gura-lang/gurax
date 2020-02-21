//==============================================================================
// Image.h
//==============================================================================
#ifndef GURAX_IMAGE_H
#define GURAX_IMAGE_H
#include "Color.h"
#include "Memory.h"
#include "Palette.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Image
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Image : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Image);
public:
	struct Format {
		size_t bytesPerPixel;
		static const Format None;
		static const Format RGB;
		static const Format RGBA;
		Format(size_t bytesPerPixel) : bytesPerPixel(bytesPerPixel) {}
		bool IsValid() const { return bytesPerPixel != 0; }
		size_t WidthToBytes(size_t width) const { return bytesPerPixel * width; }
		bool IsIdentical(const Format& format) const { return this == &format; }
	};
	struct Rect {
		size_t x;
		size_t y;
		size_t width;
		size_t height;
	};
	enum class ScanDir {
		None, LeftTopHorz, LeftTopVert, RightTopHorz, RightTopVert,
		LeftBottomHorz, LeftBottomVert, RightBottomHorz, RightBottomVert,
	};
	struct Metrics {
		const Format& format;
		size_t width;
		size_t height;
		size_t bytesPerPixel;
		size_t bytesPerLine;
		UInt8 alphaDefault;
		Metrics(const Format& format, size_t width, size_t height, UInt8 alphaDefault) :
			format(format), width(width), height(height),
			bytesPerPixel(format.bytesPerPixel), bytesPerLine(format.WidthToBytes(width)),
			alphaDefault(alphaDefault) {}
		bool IsFormat(const Format& format) const { return this->format.IsIdentical(format); }
		bool AdjustCoord(Rect* pRect, int x, int y, int width, int height) const;
		bool CheckCoord(int x, int y) const;
	};
	struct Accumulator {
	public:
		UInt32 r;
		UInt32 g;
		UInt32 b;
		UInt32 a;
		size_t n;
	public:
		template<typename T_Pixel> void Store(const UInt8* pSrc) {}
		template<typename T_Pixel> void Extract(UInt8* pDst) {}
	};
	class Scanner {
	protected:
		const Metrics& _metrics;
		UInt8* _p;
		UInt8* _pRow;
		size_t _iCol, _iRow;
		size_t _nCols, _nRows;
		int _pitchCol;
		int _pitchRow;
	public:
		UInt8* GetPointer() const { return _p; }
	public:
		Scanner(const Metrics& metrics, UInt8* p, size_t nCols, size_t nRows, int pitchCol, int pitchRow) :
			_metrics(metrics), _p(p), _pRow(p), _iCol(0), _iRow(0),
			_nCols(nCols), _nRows(nRows), _pitchCol(pitchCol), _pitchRow(pitchRow) {}
	public:
		bool IsFormat(const Format& format) const { return _metrics.IsFormat(format); }
	public:
		static Scanner CreateByDir(const Image& image, size_t x, size_t y, size_t width, size_t height, ScanDir scanDir);
		static Scanner CreateByFlip(const Image& image, size_t x, size_t y, size_t width, size_t height,
									bool horzFlag, bool vertFlag);
		static Scanner LeftTopHorz(const Image& image, size_t x, size_t y, size_t width, size_t height);
		static Scanner LeftTopVert(const Image& image, size_t x, size_t y, size_t width, size_t height);
		static Scanner RightTopHorz(const Image& image, size_t x, size_t y, size_t width, size_t height);
		static Scanner RightTopVert(const Image& image, size_t x, size_t y, size_t width, size_t height);
		static Scanner LeftBottomHorz(const Image& image, size_t x, size_t y, size_t width, size_t height);
		static Scanner LeftBottomVert(const Image& image, size_t x, size_t y, size_t width, size_t height);
		static Scanner RightBottomHorz(const Image& image, size_t x, size_t y, size_t width, size_t height);
		static Scanner RightBottomVert(const Image& image, size_t x, size_t y, size_t width, size_t height);
		static Scanner CreateByDir(const Image& image, ScanDir scanDir) {
			return CreateByDir(image, 0, 0, image.GetWidth(), image.GetHeight(), scanDir);
		}
		static Scanner CreateByFlip(const Image& image, bool horzFlag, bool vertFlag) {
			return CreateByFlip(image, 0, 0, image.GetWidth(), image.GetHeight(), horzFlag, vertFlag);
		}
		static Scanner LeftTopHorz(const Image& image) {
			return LeftTopHorz(image, 0, 0, image.GetWidth(), image.GetHeight());
		}
		static Scanner LeftTopVert(const Image& image) {
			return LeftTopVert(image, 0, 0, image.GetWidth(), image.GetHeight());
		}
		static Scanner RightTopHorz(const Image& image) {
			return RightTopHorz(image, 0, 0, image.GetWidth(), image.GetHeight());
		}
		static Scanner RightTopVert(const Image& image) {
			return RightTopVert(image, 0, 0, image.GetWidth(), image.GetHeight());
		}
		static Scanner LeftBottomHorz(const Image& image) {
			return LeftBottomHorz(image, 0, 0, image.GetWidth(), image.GetHeight());
		}
		static Scanner LeftBottomVert(const Image& image) {
			return LeftBottomVert(image, 0, 0, image.GetWidth(), image.GetHeight());
		}
		static Scanner RightBottomHorz(const Image& image) {
			return RightBottomHorz(image, 0, 0, image.GetWidth(), image.GetHeight());
		}
		static Scanner RightBottomVert(const Image& image) {
			return RightBottomVert(image, 0, 0, image.GetWidth(), image.GetHeight());
		}
	public:
		const Metrics& GetMetrics() const { return _metrics; }
		bool NextCol() {
			_iCol++;
			_p += _pitchCol;
			return _iCol < _nCols;
		}
		bool NextCol(Scanner& scannerSlave) {
			_iCol++;
			_p += _pitchCol, scannerSlave._p += scannerSlave._pitchCol;
			return _iCol < _nCols;
		}
		bool NextRow() {
			_iCol = 0, _iRow++;
			_pRow += _pitchRow, _p = _pRow;
			return _iRow < _nRows;
		}
		bool NextRow(Scanner& scannerSlave) {
			_iCol = 0, _iRow++;
			_pRow += _pitchRow, _p = _pRow;
			scannerSlave._pRow += scannerSlave._pitchRow, scannerSlave._p = scannerSlave._pRow;
			return _iRow < _nRows;
		}
		bool Next() { return NextCol() || NextRow(); }
		bool Next(Scanner& scannerSlave) { return NextCol(scannerSlave) || NextRow(scannerSlave); }
		size_t GetColIndex() const { return _iCol; }
		size_t GetRowIndex() const { return _iRow; }
		size_t GetColNum() const { return _nCols; }
		size_t GetRowNum() const { return _nRows; }
	public:
		template<typename T_PixelDst, typename T_PixelSrc> void PutPixel(const UInt8* p) {}
		template<typename T_PixelDst, typename T_PixelSrc>
		static void PasteT(Scanner& scannerDst, Scanner& scannerSrc);
		static void Paste(Scanner& scannerDst, Scanner& scannerSrc);
	};
	class PixelRGB;
	class PixelRGBA;
	class Pixel {
	protected:
		const Metrics& _metrics;
		UInt8* _p;
	public:
		// Constructor
		Pixel(const Metrics& metrics, UInt8* p) : _metrics(metrics), _p(p) {}
		// Copy constructor/operator
		Pixel(const Pixel& src) : _metrics(src._metrics), _p(src._p) {}
		Pixel& operator=(const Pixel& src) = delete;
		// Move constructor/operator
		Pixel(const Pixel&& src) : _metrics(src._metrics), _p(src._p) {}
		Pixel& operator=(const Pixel&& src) noexcept = delete;
	public:
		size_t WidthToBytes(size_t width) const { return _metrics.format.WidthToBytes(width); }
		size_t GetBytesPerPixel() const { return _metrics.bytesPerPixel; }
		size_t GetBytesPerLine() const { return _metrics.bytesPerLine; }
		UInt8 GetAlphaDefault() const { return _metrics.alphaDefault; }
		UInt8* GetPointer() const { return _p; }
		UInt8* GetPointer(size_t x, size_t y) const {
			return GetPointer() + x * GetBytesPerPixel() + y * GetBytesPerLine();
		}
	public:
		static void PasteSame(Pixel& pixelDst, const Pixel& pixelSrc, size_t width, size_t height);
		static void Paste(PixelRGB& pixelDst, const PixelRGB& pixelSrc, size_t width, size_t height);
		static void Paste(PixelRGBA& pixelDst, const PixelRGBA& pixelSrc, size_t width, size_t height);
		static void Paste(PixelRGB& pixelDst, const PixelRGBA& pixelSrc, size_t width, size_t height);
		static void Paste(PixelRGBA& pixelDst, const PixelRGB& pixelSrc, size_t width, size_t height);
		template<typename T_PixelDst, typename T_PixelSrc>
		static void ResizePasteT(T_PixelDst& pixelDst, size_t wdDst, size_t htDst,
								 const T_PixelSrc& pixelSrc, size_t wdSrc, size_t htSrc);
	};
	class PixelRGB : public Pixel {
	public:
		using Pixel::Pixel;
	public:
		static const size_t bytesPerPixel = 3;
	public:
		static void SetR(UInt8* p, UInt8 r) { *(p + 2) = r; }
		static void SetG(UInt8* p, UInt8 g) { *(p + 1) = g; }
		static void SetB(UInt8* p, UInt8 b) { *(p + 0) = b; }
		static void SetRGB(UInt8* p, UInt8 r, UInt8 g, UInt8 b) {
			SetR(p, r), SetG(p, g), SetB(p, b);
		}
		static void SetPacked(UInt8* p, UInt32 packed) {
			SetB(p, static_cast<UInt8>(packed));
			SetG(p, static_cast<UInt8>(packed >> 8));
			SetR(p, static_cast<UInt8>(packed >> 16));
		}
		static void SetColor(UInt8* p, const Color &color) {
			SetR(p, color.GetR()), SetG(p, color.GetG()), SetB(p, color.GetB());
		}
		static UInt8 GetR(const UInt8* p) { return *(p + 2); }
		static UInt8 GetG(const UInt8* p) { return *(p + 1); }
		static UInt8 GetB(const UInt8* p) { return *(p + 0); }
	public:
		void SetR(UInt8 r) { SetR(_p, r); }
		void SetG(UInt8 g) { SetG(_p, g); }
		void SetB(UInt8 b) { SetB(_p, b); }
		void SetA(UInt8 a) {}
		void SetPacked(UInt32 packed) {
			SetB(static_cast<UInt8>(packed));
			SetG(static_cast<UInt8>(packed >> 8));
			SetR(static_cast<UInt8>(packed >> 16));
		}
		void SetColor(const Color &color) { SetColor(_p, color); }
		UInt8 GetR() const { return GetR(_p); }
		UInt8 GetG() const { return GetG(_p); }
		UInt8 GetB() const { return GetB(_p); }
		UInt8 GetA() const { return _metrics.alphaDefault; }
		UInt32 GetPacked() const {
			return (static_cast<UInt32>(GetR()) << 16) + (static_cast<UInt32>(GetG()) << 8) +
				static_cast<UInt32>(GetB()) + (static_cast<UInt32>(_metrics.alphaDefault) << 24);
		}
		Color GetColor() const { return Color(GetR(), GetG(), GetB(), _metrics.alphaDefault); }
	public:
		template<typename T_Pixel> void PutPixel(const UInt8* p) {
			SetR(T_Pixel::GetR(p)), SetG(T_Pixel::GetG(p)), SetB(T_Pixel::GetB(p));
		}
		void SetColorN(const Color &color, size_t n) {
			for (UInt8* p = _p; n > 0; n--, p += bytesPerPixel) SetColor(p, color);
		}
	};
	class PixelRGBA : public Pixel {
	public:
		using Pixel::Pixel;
	public:
		static const size_t bytesPerPixel = 4;
	public:
		static void SetR(UInt8* p, UInt8 r) { *(p + 2) = r; }
		static void SetG(UInt8* p, UInt8 g) { *(p + 1) = g; }
		static void SetB(UInt8* p, UInt8 b) { *(p + 0) = b; }
		static void SetA(UInt8* p, UInt8 a) { *(p + 3) = a; }
		static void SetRGBA(UInt8* p, UInt8 r, UInt8 g, UInt8 b, UInt8 a) {
			SetR(p, r), SetG(p, g), SetB(p, b), SetA(p, a);
		}
		static void SetPacked(UInt8* p, UInt32 packed) { *reinterpret_cast<UInt32*>(p) = packed; } 
		static void SetColor(UInt8* p, const Color &color) { SetPacked(p, color.GetPacked()); }
		static UInt8 GetR(const UInt8* p) { return *(p + 2); }
		static UInt8 GetG(const UInt8* p) { return *(p + 1); }
		static UInt8 GetB(const UInt8* p) { return *(p + 0); }
		static UInt8 GetA(const UInt8* p) { return *(p + 3); }
		static UInt32 GetPacked(const UInt8* p) { return *reinterpret_cast<const UInt32*>(p); } 
		static Color GetColor(const UInt8* p) { return Color(GetPacked(p)); }
	public:
		void SetR(UInt8 r) { SetR(_p, r); }
		void SetG(UInt8 g) { SetG(_p, g); }
		void SetB(UInt8 b) { SetB(_p, b); }
		void SetA(UInt8 a) { SetA(_p, a); }
		void SetPacked(UInt32 packed) { SetPacked(_p, packed); }
		void SetColor(const Color &color) { SetColor(_p, color); }
		UInt8 GetR() const { return GetR(_p); }
		UInt8 GetG() const { return GetG(_p); }
		UInt8 GetB() const { return GetB(_p); }
		UInt8 GetA() const { return GetA(_p); }
		UInt32 GetPacked() const { return GetPacked(_p); }
		Color GetColor() const { return GetColor(_p); }
	public:
		template<typename T_Pixel> void PutPixel(const UInt8* p) {}
		void SetColorN(const Color &color, size_t n) {
			for (UInt8* p = _p; n > 0; n--, p += bytesPerPixel) SetColor(p, color);
		}
	};
protected:
	RefPtr<Memory> _pMemory;
	RefPtr<Palette> _pPalette;	// may be nullptr
	Metrics _metrics;
public:
	static void Bootup();
public:
	// Constructor
	Image(const Format& format, Memory* pMemory, size_t width, size_t height, UInt8 alphaDefault) :
		_pMemory(pMemory), _metrics(format, width, height, alphaDefault) {}
	Image(const Format& format) : _metrics(format, 0, 0, 0xff) {}
	// Copy constructor/operator
	Image(const Image& src) = delete;
	Image& operator=(const Image& src) = delete;
	// Move constructor/operator
	Image(Image&& src) = delete;
	Image& operator=(Image&& src) noexcept = delete;
protected:
	~Image() = default;
public:
	bool Allocate(size_t width, size_t height);
	void SetPalette(Palette* pPalette) { _pPalette.reset(pPalette); }
	Palette* GetPalette() { return _pPalette.get(); }
	const Palette* GetPalette() const { return _pPalette.get(); }
	const Format& GetFormat() const { return _metrics.format; }
	bool IsFormat(const Format& format) const { return _metrics.IsFormat(format); }
	const Metrics& GetMetrics() const { return _metrics; }
	bool IsAreaZero() const { return _metrics.width == 0 || _metrics.height == 0; }
	size_t GetWidth() const { return _metrics.width; }
	size_t GetHeight() const { return _metrics.height; }
	size_t GetBytesPerPixel() const { return _metrics.bytesPerPixel; }
	size_t GetBytesPerLine() const { return _metrics.bytesPerLine; }
	void SetAlphaDefault(UInt8 alphaDefault) { _metrics.alphaDefault = alphaDefault; }
	UInt8 GetAlphaDefault() const { return _metrics.alphaDefault; }
	size_t WidthToBytes(size_t width) const { return _metrics.format.WidthToBytes(width); }
	bool AdjustCoord(Rect* pRect, int x, int y, int width, int height) const {
		return _metrics.AdjustCoord(pRect, x, y, width, height);
	}
	UInt8* GetPointer() const { return reinterpret_cast<UInt8*>(_pMemory->GetPointer()); }
	UInt8* GetPointer(size_t x, size_t y) const {
		return GetPointer() + x * GetBytesPerPixel() + y * GetBytesPerLine();
	}
	template<typename T_Pixel> T_Pixel GetPixel() const {
		return T_Pixel(GetMetrics(), GetPointer());
	}
	template<typename T_Pixel> T_Pixel GetPixel(size_t x, size_t y) const {
		return T_Pixel(GetMetrics(), GetPointer(x, y));
	}
	bool Read(Stream& stream, const char* imgTypeName = nullptr);
	bool Write(Stream& stream, const char* imgTypeName) const;
	void Fill(const Color& color);
	void FillRect(size_t x, size_t y, size_t width, size_t height, const Color& color);
	void Paste(size_t xDst, size_t yDst, const Image& imageSrc,
			   size_t xSrc, size_t ySrc, size_t width, size_t height);
	void ResizePaste(size_t xDst, size_t yDst, size_t wdDst, size_t htDst, const Image& imageSrc,
					 size_t xSrc, size_t ySrc, size_t width, size_t height);
	Image* Crop(const Format& format, size_t x, size_t y, size_t width, size_t height) const;
	Image* Crop(size_t x, size_t y, size_t width, size_t height) const {
		return Crop(GetFormat(), x, y, width, height);
	}
	Image* Resize(const Format& format, size_t width, size_t height) const;
	Image* Resize(size_t width, size_t height) const { return Resize(GetFormat(), width, height); }
	template<typename T_PixelDst, typename T_PixelSrc>
	Image* RotateT(const Format& format, double angleDeg, const Color& colorBg) const;
	Image* Rotate(const Format& format, double angleDeg, const Color& colorBg) const;
	Image* Rotate(double angleDeg, const Color& colorBg) { return Rotate(GetFormat(), angleDeg, colorBg); }
	Image* Rotate90(const Format& format) const;
	Image* Rotate180(const Format& format) const { return Flip(format, true, true); }
	Image* Rotate270(const Format& format) const;
	Image* Flip(const Format& format, bool horzFlag, bool vertFlag) const;
	Image* Flip(bool horzFlag, bool vertFlag) const { return Flip(GetFormat(), horzFlag, vertFlag); }
	Color GetPixelColor(size_t x, size_t y) const {
		return IsFormat(Format::RGB)? GetPixel<PixelRGB>(x, y).GetColor() :
			IsFormat(Format::RGBA)? GetPixel<PixelRGBA>(x, y).GetColor() : Color::zero;
	}
	void PutPixelColor(size_t x, size_t y, const Color& color) const {
		if (IsFormat(Format::RGB)) { GetPixel<PixelRGB>(x, y).SetColor(color); }
		else if (IsFormat(Format::RGBA)) { GetPixel<PixelRGBA>(x, y).SetColor(color); }
	}
	bool CheckCoord(int x, int y) const { return GetMetrics().CheckCoord(x, y); }
	static void CalcRotatesSize(size_t* pWdDst, size_t* pHtDst, size_t wdSrc, size_t htSrc, int cos1024, int sin1024);
	static const Format& SymbolToFormat(const Symbol* pSymbol);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Image& image) const { return this == &image; }
	bool IsEqualTo(const Image& image) const { return IsIdentical(image); }
	bool IsLessThan(const Image& image) const { return this < &image; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

template<> inline void Image::PixelRGBA::PutPixel<Image::PixelRGB>(const UInt8* p)
{
	SetR(PixelRGB::GetR(p)), SetG(PixelRGB::GetG(p)), SetB(PixelRGB::GetB(p)); SetA(GetAlphaDefault());
}

template<> inline void Image::PixelRGBA::PutPixel<Image::PixelRGBA>(const UInt8* p)
{
	SetPacked(PixelRGBA::GetPacked(p));
}

//------------------------------------------------------------------------------
// ImageList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageList : public std::vector<Image*> {
public:
	using std::vector<Image*>::vector;
};

//------------------------------------------------------------------------------
// ImageOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageOwner : public ImageList {
public:
	~ImageOwner() { Clear(); }
	void Clear();
};

}

#endif
