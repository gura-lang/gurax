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
	static const size_t offsetR = 2;
	static const size_t offsetG = 1;
	static const size_t offsetB = 0;
	static const size_t offsetA = 3;
public:
	struct GURAX_DLLDECLARE Format {
		size_t bytesPerPixel;
		static const Format None;
		static const Format RGB;
		static const Format RGBA;
		Format(size_t bytesPerPixel) : bytesPerPixel(bytesPerPixel) {}
		bool IsValid() const { return bytesPerPixel != 0; }
		size_t WidthToBytes(size_t width) const { return bytesPerPixel * width; }
		bool IsIdentical(const Format& format) const { return this == &format; }
	};
	struct GURAX_DLLDECLARE Rect {
		size_t x;
		size_t y;
		size_t width;
		size_t height;
	};
	enum class ScanDir {
		None,
		LeftTopHorz, LeftTopVert,
		LeftBottomHorz, LeftBottomVert,
		RightTopHorz, RightTopVert,
		RightBottomHorz, RightBottomVert,
	};
	class GURAX_DLLDECLARE SymbolAssoc_ScanDir : public SymbolAssoc<ScanDir, ScanDir::None> {
	public:
		SymbolAssoc_ScanDir() {
			Assoc(Gurax_Symbol(LeftTopHorz),		ScanDir::LeftTopHorz);
			Assoc(Gurax_Symbol(LeftTopVert),		ScanDir::LeftTopVert);
			Assoc(Gurax_Symbol(LeftBottomHorz),		ScanDir::LeftBottomHorz);
			Assoc(Gurax_Symbol(LeftBottomVert),		ScanDir::LeftBottomVert);
			Assoc(Gurax_Symbol(RightTopHorz),		ScanDir::RightTopHorz);
			Assoc(Gurax_Symbol(RightTopVert),		ScanDir::RightTopVert);
			Assoc(Gurax_Symbol(RightBottomHorz),	ScanDir::RightBottomHorz);
			Assoc(Gurax_Symbol(RightBottomVert),	ScanDir::RightBottomVert);
		}
		static const SymbolAssoc& GetInstance() {
			static SymbolAssoc* pSymbolAssoc = nullptr;
			return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_ScanDir());
		}
	};
	struct GURAX_DLLDECLARE Metrics {
		const Format* pFormat;
		size_t width;
		size_t height;
		UInt8 alphaDefault;
		size_t bytesPerPixel;	// calculated
		size_t bytesPerLine;	// calcualted
		Metrics(const Metrics& src) :
			pFormat(src.pFormat), width(src.width), height(src.height), alphaDefault(src.alphaDefault),
			bytesPerPixel(src.bytesPerPixel), bytesPerLine(src.bytesPerLine) {}
		Metrics(const Format& format, size_t width, size_t height, UInt8 alphaDefault) :
			pFormat(&format), width(width), height(height), alphaDefault(alphaDefault),
			bytesPerPixel(format.bytesPerPixel), bytesPerLine(format.WidthToBytes(width)) {}
		void Update() { bytesPerLine = pFormat->WidthToBytes(width); }
		bool IsFormat(const Format& format) const { return this->pFormat->IsIdentical(format); }
		bool AdjustCoord(Rect* pRect, int x, int y, int width, int height) const;
		bool CheckCoord(int x, int y) const;
		bool CheckArea(int x, int y, int width, int height) const;
		size_t CountPixels() const { return width * height; }
		void operator=(const Metrics& src) {
			pFormat = src.pFormat, width = src.width, height = src.height;
			bytesPerPixel = src.bytesPerPixel, bytesPerLine = src.bytesPerLine;
			alphaDefault = src.alphaDefault;
		}
	};
	class GURAX_DLLDECLARE Accumulator {
	public:
		struct Elem {
			UInt32 r;
			UInt32 g;
			UInt32 b;
			UInt32 a;
			size_t n;
		};
	private:
		RefPtr<Memory> _pMemory;
		Elem* _pElem;
	public:
		Accumulator(size_t width);
		void Clear() { _pMemory->Fill(0x00); }
		void StoreRGB(size_t idx, UInt8 r, UInt8 g, UInt8 b) {
			Elem& elem = *(_pElem + idx);
			elem.r += r, elem.g += g, elem.b += b, elem.n++;
		}
		void StoreRGB(size_t idx, const UInt8* pSrc) {
			StoreRGB(idx, *(pSrc + 0), *(pSrc + 1), *(pSrc + 2));
		}
		void StoreBGR(size_t idx, const UInt8* pSrc) {
			StoreRGB(idx, *(pSrc + 2), *(pSrc + 1), *(pSrc + 0));
		}
		void StoreRGBA(size_t idx, UInt8 r, UInt8 g, UInt8 b, UInt8 a) {
			Elem& elem = *(_pElem + idx);
			elem.r += r, elem.g += g, elem.b += b, elem.a += a, elem.n++;
		}
		void StoreRGBA(size_t idx, const UInt8* pSrc) {
			StoreRGBA(idx, *(pSrc + 0), *(pSrc + 1), *(pSrc + 2), *(pSrc + 3));
		}
		void StoreBGRA(size_t idx, const UInt8* pSrc) {
			StoreRGBA(idx, *(pSrc + 2), *(pSrc + 1), *(pSrc + 0), *(pSrc + 3));
		}
		void ExtractRGB(size_t idx, UInt8* pDst) {
			const Elem& elem = *(_pElem + idx);
			size_t n = (elem.n > 0)? elem.n : 1;
			*(pDst + 0) = static_cast<UInt8>(elem.r / n), *(pDst + 1) = static_cast<UInt8>(elem.g / n);
			*(pDst + 2) = static_cast<UInt8>(elem.b / n);
		}
		void ExtractBGR(size_t idx, UInt8* pDst) {
			const Elem& elem = *(_pElem + idx);
			size_t n = (elem.n > 0)? elem.n : 1;
			*(pDst + 0) = static_cast<UInt8>(elem.b / n), *(pDst + 1) = static_cast<UInt8>(elem.g / n);
			*(pDst + 2) = static_cast<UInt8>(elem.r / n);
		}
		void ExtractRGBA(size_t idx, UInt8* pDst) {
			const Elem& elem = *(_pElem + idx);
			size_t n = (elem.n > 0)? elem.n : 1;
			*(pDst + 0) = static_cast<UInt8>(elem.r / n), *(pDst + 1) = static_cast<UInt8>(elem.g / n);
			*(pDst + 2) = static_cast<UInt8>(elem.b / n), *(pDst + 3) = static_cast<UInt8>(elem.a / n);
		}
		void ExtractBGRA(size_t idx, UInt8* pDst) {
			const Elem& elem = *(_pElem + idx);
			size_t n = (elem.n > 0)? elem.n : 1;
			*(pDst + 0) = static_cast<UInt8>(elem.b / n), *(pDst + 1) = static_cast<UInt8>(elem.g / n);
			*(pDst + 2) = static_cast<UInt8>(elem.r / n), *(pDst + 3) = static_cast<UInt8>(elem.a / n);
		}
		template<typename T_Pixel> void Store(size_t idx, const UInt8* pSrc) {}
		template<typename T_Pixel> void Extract(size_t idx, UInt8* pDst) {}
	};
	class PixelRGB;
	class PixelRGBA;
	class GURAX_DLLDECLARE Pixel {
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
		Pixel(const Pixel&& src) noexcept : _metrics(src._metrics), _p(src._p) {}
		Pixel& operator=(const Pixel&& src) noexcept = delete;
	public:
		const Metrics& GetMetrics() const { return _metrics; }
		size_t WidthToBytes(size_t width) const { return _metrics.pFormat->WidthToBytes(width); }
		size_t GetBytesPerPixel() const { return _metrics.bytesPerPixel; }
		size_t GetBytesPerLine() const { return _metrics.bytesPerLine; }
		UInt8 GetAlphaDefault() const { return _metrics.alphaDefault; }
		UInt8* GetPointerC() const { return _p; }
		UInt8* GetPointerC(size_t x, size_t y) const {
			return GetPointerC() + x * GetBytesPerPixel() + y * GetBytesPerLine();
		}
	public:
		static void SetR(UInt8* p, UInt8 r) { *(p + offsetR) = r; }
		static void SetG(UInt8* p, UInt8 g) { *(p + offsetG) = g; }
		static void SetB(UInt8* p, UInt8 b) { *(p + offsetB) = b; }
		static void SetRGB(UInt8* p, UInt8 r, UInt8 g, UInt8 b) {
			SetR(p, r); SetG(p, g); SetB(p, b);
		}
	public:
		static UInt8 GetR(const UInt8* p) { return *(p + offsetR); }
		static UInt8 GetG(const UInt8* p) { return *(p + offsetG); }
		static UInt8 GetB(const UInt8* p) { return *(p + offsetB); }
	public:
		void SetR(UInt8 r) { SetR(_p, r); }
		void SetG(UInt8 g) { SetG(_p, g); }
		void SetB(UInt8 b) { SetB(_p, b); }
		void SetRGB(UInt8 r, UInt8 g, UInt8 b) { SetRGB(_p, r, g, b); }
	public:
		UInt8 GetR() const { return GetR(_p); }
		UInt8 GetG() const { return GetG(_p); }
		UInt8 GetB() const { return GetB(_p); }
	public:
		static void PasteSame(Pixel& pixelDst, const Pixel& pixelSrc, size_t width, size_t height);
		static void Paste(PixelRGB& pixelDst, const PixelRGB& pixelSrc, size_t width, size_t height);
		static void Paste(PixelRGBA& pixelDst, const PixelRGBA& pixelSrc, size_t width, size_t height);
		static void Paste(PixelRGB& pixelDst, const PixelRGBA& pixelSrc, size_t width, size_t height);
		static void Paste(PixelRGBA& pixelDst, const PixelRGB& pixelSrc, size_t width, size_t height);
	};
	class GURAX_DLLDECLARE PixelRGB : public Pixel {
	public:
		using Pixel::Pixel;
	public:
		static const size_t bytesPerPixel = 3;
	public:
		static void SetA(UInt8* p, UInt8 a) {}
		static UInt8 GetA(const UInt8* p) { return 0xff; }
		static UInt8 GetA(const UInt8* p, UInt8 alphaDefault) { return alphaDefault; }
		static void SetRGBA(UInt8* p, UInt8 r, UInt8 g, UInt8 b, UInt8 a) {
			SetR(p, r); SetG(p, g); SetB(p, b);
		}
		static void SetPacked(UInt8* p, UInt32 packed) {
			SetB(p, static_cast<UInt8>(packed));
			SetG(p, static_cast<UInt8>(packed >> 8));
			SetR(p, static_cast<UInt8>(packed >> 16));
		}
		static void SetColor(UInt8* p, const Color &color) {
			SetR(p, color.GetR()), SetG(p, color.GetG()), SetB(p, color.GetB());
		}
		static void SetColor(UInt8* p, const Color &color, UInt8 alpha) {
			SetR(p, color.GetR()), SetG(p, color.GetG()), SetB(p, color.GetB());
		}
		static UInt32 GetPacked(const UInt8* p, UInt8 alphaDefault) {
			return (static_cast<UInt32>(GetR(p)) << 16) + (static_cast<UInt32>(GetG(p)) << 8) +
				static_cast<UInt32>(GetB(p)) + (static_cast<UInt32>(alphaDefault) << 24);
		}
		static Color GetColor(const UInt8* p, UInt8 alphaDefault) {
			return Color(GetR(p), GetG(p), GetB(p), alphaDefault);
		}
	public:
		void SetA(UInt8 a) {}
		void SetRGBA(UInt8 r, UInt8 g, UInt8 b, UInt8 a) { SetRGBA(_p, r, g, b, a); }
		void SetPacked(UInt32 packed) {
			SetB(static_cast<UInt8>(packed));
			SetG(static_cast<UInt8>(packed >> 8));
			SetR(static_cast<UInt8>(packed >> 16));
		}
		void SetColor(const Color &color) { SetColor(_p, color); }
		void SetColor(const Color &color, UInt8 alpha) { SetColor(_p, color, alpha); }
		UInt8 GetA() const { return _metrics.alphaDefault; }
		UInt32 GetPacked() const { return GetPacked(_p, _metrics.alphaDefault); }
		Color GetColor() const { return GetColor(_p, _metrics.alphaDefault); }
	public:
		void PutPixel(const UInt8* p) {
			SetR(GetR(p)), SetG(GetG(p)), SetB(GetB(p));
		}
		void SetColorN(const Color& color, size_t n) {
			for (UInt8* p = _p; n > 0; n--, p += bytesPerPixel) SetColor(p, color);
		}
		void SetColorN(const Color& color, UInt8 alpha, size_t n) {
			for (UInt8* p = _p; n > 0; n--, p += bytesPerPixel) SetColor(p, color, alpha);
		}
	};
	class GURAX_DLLDECLARE PixelRGBA : public Pixel {
	public:
		using Pixel::Pixel;
	public:
		static const size_t bytesPerPixel = 4;
	public:
		static void SetA(UInt8* p, UInt8 a) { *(p + offsetA) = a; }
		static void SetRGBA(UInt8* p, UInt8 r, UInt8 g, UInt8 b, UInt8 a) {
			SetR(p, r); SetG(p, g); SetB(p, b); SetA(p, a);
		}
		static void SetPacked(UInt8* p, UInt32 packed) { *reinterpret_cast<UInt32*>(p) = packed; } 
		static void SetColor(UInt8* p, const Color &color) { SetPacked(p, color.GetPacked()); }
		static void SetColor(UInt8* p, const Color &color, UInt8 alpha) { SetRGBA(p, color.GetR(), color.GetG(), color.GetB(), alpha); }
	public:
		static UInt8 GetA(const UInt8* p) { return *(p + offsetA); }
		static UInt8 GetA(const UInt8* p, UInt8 alphaDefault) { return GetA(p); }
		static UInt32 GetPacked(const UInt8* p) { return *reinterpret_cast<const UInt32*>(p); } 
		static UInt32 GetPacked(const UInt8* p, UInt8 alphaDefault) { return GetPacked(p); }
		static Color GetColor(const UInt8* p) { return Color(GetPacked(p)); }
		static Color GetColor(const UInt8* p, UInt8 alphaDefault) { return Color(GetPacked(p)); }
	public:
		void SetA(UInt8 a) { SetA(_p, a); }
		void SetRGBA(UInt8 r, UInt8 g, UInt8 b, UInt8 a) { SetRGBA(_p, r, g, b, a); }
		void SetPacked(UInt32 packed) { SetPacked(_p, packed); }
		void SetColor(const Color& color) { SetColor(_p, color); }
		void SetColor(const Color& color, UInt8 alpha) { SetColor(_p, color, alpha); }
	public:
		UInt8 GetA() const { return GetA(_p); }
		UInt32 GetPacked() const { return GetPacked(_p); }
		Color GetColor() const { return Color(GetPacked()); }
	public:
		template<typename T_Pixel> void PutPixel(const UInt8* p) {}
		void SetColorN(const Color& color, size_t n) {
			for (UInt8* p = _p; n > 0; n--, p += bytesPerPixel) SetColor(p, color);
		}
		void SetColorN(const Color& color, UInt8 alpha, size_t n) {
			Color colorToSet(color.GetPacked(), alpha);
			for (UInt8* p = _p; n > 0; n--, p += bytesPerPixel) SetColor(p, colorToSet);
		}
	};
	class GURAX_DLLDECLARE Scanner {
	protected:
		const Metrics& _metrics;
		UInt8* _p;
		UInt8* _pRow;
		size_t _x, _y;
		size_t _iCol, _iRow;
		size_t _nCols, _nRows;
		int _pitchCol;
		int _pitchRow;
		bool _horzFlag;
	public:
		UInt8* GetPointerC() const { return _p; }
	public:
		// Constructor
		Scanner(const Metrics& metrics, UInt8* p, size_t x, size_t y,
				size_t nCols, size_t nRows, int pitchCol, int pitchRow, bool horzFlag) :
			_metrics(metrics), _p(p), _pRow(p), _x(x), _y(y), _iCol(0), _iRow(0),
			_nCols(nCols), _nRows(nRows), _pitchCol(pitchCol), _pitchRow(pitchRow), _horzFlag(horzFlag) {}
		// Copy constructor/operator
		Scanner(const Scanner& src) :
			_metrics(src._metrics), _p(src._p), _pRow(src._pRow), _x(src._x), _y(src._y),
			_iCol(src._iCol), _iRow(src._iRow), _nCols(src._nCols), _nRows(src._nRows),
			_pitchCol(src._pitchCol), _pitchRow(src._pitchRow), _horzFlag(src._horzFlag) {}
		Scanner& operator=(const Scanner& src) = delete;
		// Move constructor/operator
		Scanner(Scanner&& src) noexcept :
			_metrics(src._metrics), _p(src._p), _pRow(src._pRow), _x(src._x), _y(src._y),
			_iCol(src._iCol), _iRow(src._iRow), _nCols(src._nCols), _nRows(src._nRows),
			_pitchCol(src._pitchCol), _pitchRow(src._pitchRow), _horzFlag(src._horzFlag) {}
		Scanner& operator=(Scanner&& src) noexcept = delete;
	public:
		~Scanner() = default;
	public:
		bool IsFormat(const Format& format) const { return _metrics.IsFormat(format); }
	public:
		static Scanner CreateByDir(const Image& image, size_t x, size_t y, size_t width, size_t height, ScanDir scanDir);
		static Scanner CreateByFlip(const Image& image, size_t x, size_t y, size_t width, size_t height,
									bool horzFlag, bool vertFlag);
		static Scanner LeftTopHorz(const Image& image, size_t x, size_t y, size_t width, size_t height);
		static Scanner LeftTopVert(const Image& image, size_t x, size_t y, size_t width, size_t height);
		static Scanner LeftBottomHorz(const Image& image, size_t x, size_t y, size_t width, size_t height);
		static Scanner LeftBottomVert(const Image& image, size_t x, size_t y, size_t width, size_t height);
		static Scanner RightTopHorz(const Image& image, size_t x, size_t y, size_t width, size_t height);
		static Scanner RightTopVert(const Image& image, size_t x, size_t y, size_t width, size_t height);
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
		static Scanner LeftBottomHorz(const Image& image) {
			return LeftBottomHorz(image, 0, 0, image.GetWidth(), image.GetHeight());
		}
		static Scanner LeftBottomVert(const Image& image) {
			return LeftBottomVert(image, 0, 0, image.GetWidth(), image.GetHeight());
		}
		static Scanner RightTopHorz(const Image& image) {
			return RightTopHorz(image, 0, 0, image.GetWidth(), image.GetHeight());
		}
		static Scanner RightTopVert(const Image& image) {
			return RightTopVert(image, 0, 0, image.GetWidth(), image.GetHeight());
		}
		static Scanner RightBottomHorz(const Image& image) {
			return RightBottomHorz(image, 0, 0, image.GetWidth(), image.GetHeight());
		}
		static Scanner RightBottomVert(const Image& image) {
			return RightBottomVert(image, 0, 0, image.GetWidth(), image.GetHeight());
		}
	public:
		const Metrics& GetMetrics() const { return _metrics; }
		void PlusCol() { _iCol++, _p += _pitchCol; }
		void MinusCol() { _iCol--, _p -= _pitchCol; }
		void PlusRow() { _iRow++, _p += _pitchRow; }
		void MinusRow() { _iRow--, _p -= _pitchRow; }
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
		size_t GetColPos() const { return ((_pitchCol >= 0)? _iCol : (_nCols > 0)? _nCols - _iCol - 1 : 0); }
		size_t GetRowPos() const { return ((_pitchRow >= 0)? _iRow : (_nRows > 0)? _nRows - _iRow - 1 : 0); }
		size_t GetX() const { return _horzFlag? GetColPos() : GetRowPos(); }
		size_t GetY() const { return _horzFlag? GetRowPos() : GetColPos(); }
		bool IsEmpty() const { return _nCols == 0 || _nRows == 0; }
		size_t GetLength() const { return _nCols * _nRows; }
	public:
		template<typename T_PixelDst, typename T_PixelSrc> void PutPixel(const UInt8* pSrc) {}
		template<typename T_PixelDst, typename T_PixelSrc>
		static void PasteT(Scanner& scannerDst, Scanner& scannerSrc);
		static void Paste(Scanner& scannerDst, Scanner& scannerSrc);
		template<typename T_Pixel> Color GetColorT() const {
			return T_Pixel::GetColor(_p, _metrics.alphaDefault);
		}
		template<typename T_Pixel> Color GetColorT(UInt8 alphaDefault) const {
			return T_Pixel::GetColor(_p, alphaDefault);
		}
		Color GetColor() const {
			return IsFormat(Format::RGBA)? GetColorT<PixelRGBA>() : GetColorT<PixelRGB>();
		}
	};
protected:
	Metrics _metrics;
	RefPtr<Palette> _pPalette;	// may be nullptr
	RefPtr<Memory> _pMemory;	// may be nullptr
	RefPtr<Value> _pValueExtra;
public:
	static void Bootup();
public:
	// Constructor
	Image(const Format& format, size_t width, size_t height, UInt8 alphaDefault,
							Palette* pPalette, Memory* pMemory, Value* pValueExtra) :
		_metrics(format, width, height, alphaDefault),
		_pPalette(pPalette), _pMemory(pMemory), _pValueExtra(pValueExtra) {}
	Image(const Format& format, UInt8 alphaDefault = 0xff) :
		_metrics(format, 0, 0, alphaDefault), _pValueExtra(Value::nil()) {}
	// Copy constructor/operator
	Image(const Image& src) = delete;
	Image& operator=(const Image& src) = delete;
	// Move constructor/operator
	Image(Image&& src) = delete;
	Image& operator=(Image&& src) noexcept = delete;
protected:
	~Image() = default;
public:
	void CopyRef(const Image& image);
	bool Allocate(size_t width, size_t height);
	void SetMemory(Memory* pMemory) { _pMemory.reset(pMemory); }
	bool SetMemory(Memory* pMemory, size_t width, size_t height);
	Memory* GetMemory() { return _pMemory.get(); }
	const Memory* GetMemory() const { return _pMemory.get(); }
	bool HasMemory() const { return !!_pMemory; }
	void SetPalette(Palette* pPalette) { _pPalette.reset(pPalette); }
	Palette* GetPalette() { return _pPalette.get(); }
	const Palette* GetPalette() const { return _pPalette.get(); }
	bool HasPalette() const { return !!_pPalette; }
	const Format& GetFormat() const { return *_metrics.pFormat; }
	bool IsFormat(const Format& format) const { return _metrics.IsFormat(format); }
	void SetMetrics(const Metrics& metrics) { _metrics = metrics; }
	Metrics& GetMetrics() { return _metrics; }
	const Metrics& GetMetrics() const { return _metrics; }
	bool IsAreaZero() const { return _metrics.width == 0 || _metrics.height == 0; }
	size_t GetWidth() const { return _metrics.width; }
	size_t GetHeight() const { return _metrics.height; }
	size_t GetBytesPerPixel() const { return _metrics.bytesPerPixel; }
	size_t GetBytesPerLine() const { return _metrics.bytesPerLine; }
	void SetAlphaDefault(UInt8 alphaDefault) { _metrics.alphaDefault = alphaDefault; }
	UInt8 GetAlphaDefault() const { return _metrics.alphaDefault; }
	size_t WidthToBytes(size_t width) const { return _metrics.pFormat->WidthToBytes(width); }
	bool AdjustCoord(Rect* pRect, int x, int y, int width, int height) const {
		return _metrics.AdjustCoord(pRect, x, y, width, height);
	}
	void SetValueExtra(Value* pValue) { _pValueExtra.reset(pValue); }
	const Value& GetValueExtra() const { return *_pValueExtra; }
	UInt8* GetPointerC() const { return _pMemory->GetPointerC<UInt8>(); }
	UInt8* GetPointerC(size_t x, size_t y) const {
		return GetPointerC() + x * GetBytesPerPixel() + y * GetBytesPerLine();
	}
	size_t GetBytes() const { return _pMemory->GetBytes(); }
	template<typename T_Pixel> T_Pixel MakePixel() const {
		return T_Pixel(GetMetrics(), GetPointerC());
	}
	template<typename T_Pixel> T_Pixel MakePixel(size_t x, size_t y) const {
		return T_Pixel(GetMetrics(), GetPointerC(x, y));
	}
	bool Read(Stream& stream, const char* imgTypeName = nullptr);
	bool Write(Stream& stream, const char* imgTypeName) const;
	void Fill(UInt8 data) { GetMemory()->Fill(data); }
	void Fill(const Color& color);
	void FillRect(size_t x, size_t y, size_t width, size_t height, const Color& color);
	void Paste(size_t xDst, size_t yDst, const Image& imageSrc,
				size_t xSrc, size_t ySrc, size_t width, size_t height);
	template<typename T_PixelDst, typename T_PixelSrc>
	static void ResizePasteT(T_PixelDst& pixelDst, size_t wdDst, size_t htDst,
							const T_PixelSrc& pixelSrc, size_t wdSrc, size_t htSrc);
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
	template<typename T_PixelDst, typename T_PixelSrc>
	static void GrayScaleT(T_PixelDst& pixelDst, T_PixelSrc& pixelSrc);
	Image* GrayScale(const Format& format) const;
	Image* GrayScale() const { return GrayScale(GetFormat()); }
	template<typename T_PixelDst, typename T_PixelSrc>
	static void MapColorLevelT(T_PixelDst& pixelDst, T_PixelSrc& pixelSrc,
							const UInt8* mapR, const UInt8* mapG, const UInt8* mapB);
	Image* MapColorLevel(const Format& format, const UInt8* mapR, const UInt8* mapG, const UInt8* mapB) const;
	Image* MapColorLevel(const UInt8* mapR, const UInt8* mapG, const UInt8* mapB) const {
		return MapColorLevel(GetFormat(), mapR, mapG, mapB);
	}
	Image* MapAlphaLevel(const UInt8* mapA) const;
	Image* ReduceColor(const Palette& palette) const;
	Color GetPixelColor(size_t x, size_t y) const {
		return IsFormat(Format::RGB)? MakePixel<PixelRGB>(x, y).GetColor() :
			IsFormat(Format::RGBA)? MakePixel<PixelRGBA>(x, y).GetColor() : Color::zero;
	}
	template<typename T_PixelDst, typename T_PixelSrc> static void PutPixel(UInt8* pDst, const UInt8* pSrc) {}
	void PutPixelColor(size_t x, size_t y, const Color& color) const {
		if (IsFormat(Format::RGB)) { MakePixel<PixelRGB>(x, y).SetColor(color); }
		else if (IsFormat(Format::RGBA)) { MakePixel<PixelRGBA>(x, y).SetColor(color); }
	}
	bool CheckCoord(int x, int y) const { return GetMetrics().CheckCoord(x, y); }
	bool CheckArea(int x, int y, int width, int height) const { return GetMetrics().CheckArea(x, y, width, height); }
public:
	static void CalcRotatesSize(size_t* pWdDst, size_t* pHtDst, size_t wdSrc, size_t htSrc, int cos1024, int sin1024);
	static ScanDir SymbolToScanDir(const Symbol* pSymbol) {
		return SymbolAssoc_ScanDir::GetInstance().ToAssociated(pSymbol);
	}
	static const Symbol* ScanDirToSymbol(ScanDir scanDir) {
		return SymbolAssoc_ScanDir::GetInstance().ToSymbol(scanDir);
	}
	static const Format& SymbolToFormat(const Symbol* pSymbol);
	static const Symbol* FormatToSymbol(const Format& format);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Image& image) const { return this == &image; }
	bool IsEqualTo(const Image& image) const { return IsIdentical(image); }
	bool IsLessThan(const Image& image) const { return this < &image; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	bool Serialize(Stream& stream) const;
	static Image* Deserialize(Stream& stream);
};

template<>
inline void Image::PutPixel<Image::PixelRGB, Image::PixelRGB>(UInt8* pDst, const UInt8* pSrc)
{
	::memcpy(pDst, pSrc, PixelRGB::bytesPerPixel);
}

template<>
inline void Image::PutPixel<Image::PixelRGB, Image::PixelRGBA>(UInt8* pDst, const UInt8* pSrc)
{
	PixelRGB::SetRGB(pDst, Pixel::GetR(pSrc), Pixel::GetG(pSrc), Pixel::GetB(pSrc));
}

template<>
inline void Image::PutPixel<Image::PixelRGBA, Image::PixelRGB>(UInt8* pDst, const UInt8* pSrc)
{
	PixelRGBA::SetRGBA(pDst, Pixel::GetR(pSrc), Pixel::GetG(pSrc), Pixel::GetB(pSrc), 0xff);
}

template<>
inline void Image::PutPixel<Image::PixelRGBA, Image::PixelRGBA>(UInt8* pDst, const UInt8* pSrc)
{
	PixelRGBA::SetPacked(pDst, PixelRGBA::GetPacked(pSrc));
}

template<> inline void Image::PixelRGBA::PutPixel<Image::PixelRGB>(const UInt8* p)
{
	SetR(GetR(p)), SetG(GetG(p)), SetB(GetB(p)); SetA(GetAlphaDefault());
}

template<> inline void Image::PixelRGBA::PutPixel<Image::PixelRGBA>(const UInt8* p)
{
	SetPacked(PixelRGBA::GetPacked(p));
}

//------------------------------------------------------------------------------
// ImageList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageList : public ListBase<Image*> {
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
