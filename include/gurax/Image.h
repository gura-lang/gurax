//==============================================================================
// Image.h
//==============================================================================
#ifndef GURAX_IMAGE_H
#define GURAX_IMAGE_H
#include "Referable.h"

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
		static const Format BGR;
		static const Format BGRA;
		Format(size_t bytesPerPixel) : bytesPerPixel(bytesPerPixel) {}
		size_t WidthToBytes(size_t width) const { return bytesPerPixel * width; }
		bool IsIdentical(const Format& format) const { return this == &format; }
	};
	enum ScanDir {
		None, LeftTopHorz, LeftTopVert, RightTopHorz, RightTopVert,
		LeftBottomHorz, LeftBottomVert, RightBottomHorz, RightBottomVert,
	};
	struct Metrics {
		const Format& format;
		size_t width;
		size_t height;
		size_t bytesPerPixel;
		size_t bytesPerLine;
		Metrics(const Format& format, size_t width, size_t height) :
			format(format), width(width), height(height),
			bytesPerPixel(format.bytesPerPixel), bytesPerLine(format.WidthToBytes(width)) {}
	};
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
		UInt8* GetPointer() { return _p; }
		const UInt8* GetPointer() const { return _p; }
		void FwdPixel() { _p += _metrics.bytesPerPixel; }
		void FwdPixel(size_t n) { _p += _metrics.bytesPerPixel * n; }
		void FwdLine() { _p += _metrics.bytesPerLine; }
		void FwdLine(size_t n) { _p += _metrics.bytesPerLine * n; }
		void BwdPixel() { _p -= _metrics.bytesPerPixel; }
		void BwdPixel(size_t n) { _p -= _metrics.bytesPerPixel * n; }
		void BwdLine() { _p -= _metrics.bytesPerLine; }
		void BwdLine(size_t n) { _p -= _metrics.bytesPerLine * n; }
	public:
		template<typename T_PixelDst, typename T_PixelSrc>
		static void ResizePaste(T_PixelDst& pixelDst, size_t wdDst, size_t htDst,
								const T_PixelSrc& pixelSrc, size_t wdSrc, size_t htSrc);
	};
	class PixelBGR : public Pixel {
	public:
		using Pixel::Pixel;
	public:
		template<typename T_Pixel> void Inject(const T_Pixel& pixel) {
			*(_p + 0) = pixel.GetB(), *(_p + 1) = pixel.GetG(), *(_p + 2) = pixel.GetR();
		}
		template<typename T_Pixel> void Paste(const T_Pixel& pixelSrc, size_t width, size_t height) {}
		template<typename T_Pixel> void ResizePaste(const T_Pixel& pixelSrc, size_t wdDst, size_t htDst,
													size_t wdSrc, size_t htSrc) {}
		void SetColor(const Color &color) {
			*(_p + 0) = color.GetB(), *(_p + 1) = color.GetG(), *(_p + 2) = color.GetR();
		}
		void SetColorN(const Color &color, size_t n) {
			UInt8* pDst = _p;
			for (size_t i = 0; i < n; i++) {
				*pDst++ = color.GetB(), *pDst++ = color.GetG(), *pDst++ = color.GetR();
			}
		}
		Color GetColor() const { return Color(*(_p + 2), *(_p + 1), *(_p + 0), 0xff); }
		void SetR(UInt8 r) { *(_p + 2) = r; }
		void SetG(UInt8 g) { *(_p + 1) = g; }
		void SetB(UInt8 b) { *(_p + 0) = b; }
		void SetA(UInt8 a) {}
		static void SetR(UInt8* p, UInt8 r) { *(p + 2) = r; }
		static void SetG(UInt8* p, UInt8 g) { *(p + 1) = g; }
		static void SetB(UInt8* p, UInt8 b) { *(p + 0) = b; }
		static void SetA(UInt8* p, UInt8 a) {}
		UInt8 GetR() const { return *(_p + 2); }
		UInt8 GetG() const { return *(_p + 1); }
		UInt8 GetB() const { return *(_p + 0); }
		UInt8 GetA() const { return 0xff; }
		static UInt8 GetR(const UInt8* p) { return *(p + 2); }
		static UInt8 GetG(const UInt8* p) { return *(p + 1); }
		static UInt8 GetB(const UInt8* p) { return *(p + 0); }
		static UInt8 GetA(const UInt8* p) { return 0xff; }
	};
	class PixelBGRA : public Pixel {
	public:
		using Pixel::Pixel;
	public:
		template<typename T_Pixel> void Inject(const T_Pixel& pixel) {
			*(_p + 0) = pixel.GetB(), *(_p + 1) = pixel.GetG(), *(_p + 2) = pixel.GetR(), *(_p + 3) = pixel.GetA();
		}
		template<typename T_Pixel> void Paste(const T_Pixel& pixelSrc, size_t width, size_t height) {}
		template<typename T_Pixel> void ResizePaste(const T_Pixel& pixelSrc, size_t wdDst, size_t htDst,
													size_t wdSrc, size_t htSrc) {}
		void SetColor(const Color &color) {
			*(_p + 0) = color.GetB(), *(_p + 1) = color.GetG(), *(_p + 2) = color.GetR();
			*(_p + 3) = color.GetA();
		}
		void SetColorN(const Color &color, size_t n) {
			UInt8* pDst = _p;
			for (size_t i = 0; i < n; i++) {
				*pDst++ = color.GetB(), *pDst++ = color.GetG(), *pDst++ = color.GetR(), *pDst++ = color.GetA();
			}
		}
		Color GetColor() const { return Color(*(_p + 2), *(_p + 1), *(_p + 0), *(_p + 3)); }
		void SetR(UInt8 r) { *(_p + 2) = r; }
		void SetG(UInt8 g) { *(_p + 1) = g; }
		void SetB(UInt8 b) { *(_p + 0) = b; }
		void SetA(UInt8 a) { *(_p + 3) = a; }
		static void SetR(UInt8* p, UInt8 r) { *(p + 2) = r; }
		static void SetG(UInt8* p, UInt8 g) { *(p + 1) = g; }
		static void SetB(UInt8* p, UInt8 b) { *(p + 0) = b; }
		static void SetA(UInt8* p, UInt8 a) { *(p + 3) = a; }
		UInt8 GetR() const { return *(_p + 2); }
		UInt8 GetG() const { return *(_p + 1); }
		UInt8 GetB() const { return *(_p + 0); }
		UInt8 GetA() const { return *(_p + 3); }
		static UInt8 GetR(const UInt8* p) { return *(p + 2); }
		static UInt8 GetG(const UInt8* p) { return *(p + 1); }
		static UInt8 GetB(const UInt8* p) { return *(p + 0); }
		static UInt8 GetA(const UInt8* p) { return *(p + 3); }
	};
protected:
	RefPtr<Memory> _pMemory;
	RefPtr<Palette> _pPalette;	// may be nullptr
	Metrics _metrics;
public:
	// Constructor
	Image(const Format& format, Memory* pMemory, size_t width, size_t height) :
		_pMemory(pMemory), _metrics(format, width, height) {}
	Image(const Format& format) : _metrics(format, 0, 0) {}
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
	const Format& GetFormat() const { return _metrics.format; }
	bool IsFormat(const Format& format) const { return _metrics.format.IsIdentical(format); }
	const Metrics& GetMetrics() const { return _metrics; }
	bool IsAreaZero() const { return _metrics.width == 0 || _metrics.height == 0; }
	size_t GetWidth() const { return _metrics.width; }
	size_t GetHeight() const { return _metrics.height; }
	size_t GetBytesPerPixel() const { return _metrics.bytesPerPixel; }
	size_t GetBytesPerLine() const { return _metrics.bytesPerLine; }
	size_t WidthToBytes(size_t width) const { return _metrics.format.WidthToBytes(width); }
	UInt8* GetPointer() { return reinterpret_cast<UInt8*>(_pMemory->GetPointer()); }
	UInt8* GetPointer(size_t x, size_t y) {
		return GetPointer() + x * GetBytesPerPixel() + y * GetBytesPerLine();
	}
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
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Image& image) const { return this == &image; }
	bool IsEqualTo(const Image& image) const { return IsIdentical(image); }
	bool IsLessThan(const Image& image) const { return this < &image; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

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
