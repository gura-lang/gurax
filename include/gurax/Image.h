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
		static const Format RGB;
		static const Format RGBA;
		Format(size_t bytesPerPixel) : bytesPerPixel(bytesPerPixel) {}
		size_t WidthToBytes(size_t width) const { return bytesPerPixel * width; }
		bool IsIdentical(const Format& format) const { return this == &format; }
	};
	struct Rect {
		size_t x;
		size_t y;
		size_t width;
		size_t height;
	};
	enum Scanner {
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
		bool AdjustCoord(Rect* pRect, int x, int y, int width, int height) const;
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
		void Paste(const Pixel& pixelSrc, size_t width, size_t height);
		template<typename T_PixelDst, typename T_PixelSrc>
		static void ResizePaste(T_PixelDst& pixelDst, size_t wdDst, size_t htDst,
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
		template<typename T_Pixel> void SetPixel(const T_Pixel& pixel) {
			SetR(pixel.GetR()), SetG(pixel.GetG()), SetB(pixel.GetB());
		}
		template<typename T_Pixel> void Paste(const T_Pixel& pixelSrc, size_t width, size_t height) {}
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
		template<typename T_Pixel> void SetPixel(const T_Pixel& pixel) {}
		template<typename T_Pixel> void Paste(const T_Pixel& pixelSrc, size_t width, size_t height) {}
		void SetColorN(const Color &color, size_t n) {
			for (UInt8* p = _p; n > 0; n--, p += bytesPerPixel) SetColor(p, color);
		}
	};
protected:
	RefPtr<Memory> _pMemory;
	RefPtr<Palette> _pPalette;	// may be nullptr
	Metrics _metrics;
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
	const Format& GetFormat() const { return _metrics.format; }
	bool IsFormat(const Format& format) const { return _metrics.format.IsIdentical(format); }
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
	Image* Resize(const Format& format, size_t width, size_t height) const;
	Image* Resize(size_t width, size_t height) const { return Resize(GetFormat(), width, height); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Image& image) const { return this == &image; }
	bool IsEqualTo(const Image& image) const { return IsIdentical(image); }
	bool IsLessThan(const Image& image) const { return this < &image; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

template<> inline void Image::PixelRGBA::SetPixel<Image::PixelRGB>(const PixelRGB& pixel)
{
	SetR(pixel.GetR()), SetG(pixel.GetG()), SetB(pixel.GetB()); SetA(pixel.GetA());
}

template<> inline void Image::PixelRGBA::SetPixel<Image::PixelRGBA>(const PixelRGBA& pixel)
{
	SetPacked(pixel.GetPacked());
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
