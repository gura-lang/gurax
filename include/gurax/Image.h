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
	enum class Format { None, BGR, BGRA };
	enum ScanDir {
		None, LeftTopHorz, LeftTopVert, RightTopHorz, RightTopVert,
		LeftBottomHorz, LeftBottomVert, RightBottomHorz, RightBottomVert,
	};
	class PixelBGR {
	protected:
		UInt8* _p;
	public:
		static const size_t bytesPerPixel = 3;
	public:
		// Constructor
		PixelBGR(UInt8* p) : _p(p) {}
		// Copy constructor/operator
		PixelBGR(const PixelBGR& src) : _p(src._p) {}
		PixelBGR& operator=(const PixelBGR& src) { _p = src._p; return *this; }
		// Move constructor/operator
		PixelBGR(const PixelBGR&& src) : _p(src._p) {}
		PixelBGR& operator=(const PixelBGR&& src) noexcept { _p = src._p; return *this; }
	public:
		UInt8* GetPointer() { return _p; }
		const UInt8* GetPointer() const { return _p; }
		void Forward() { _p += bytesPerPixel; }
		void Forward(size_t n) { _p += bytesPerPixel * n; }
		template<typename T_Pixel> void Inject(const T_Pixel& pixel) {
			*(_p + 0) = pixel.GetB(), *(_p + 1) = pixel.GetG(), *(_p + 2) = pixel.GetR();
		}
		template<typename T_Pixel> void InjectN(const T_Pixel& pixel, size_t n) {}
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
	class PixelBGRA {
	protected:
		UInt8* _p;
	public:
		static const size_t bytesPerPixel = 4;
	public:
		// Constructor
		PixelBGRA(UInt8* p) : _p(p) {}
		// Copy constructor/operator
		PixelBGRA(const PixelBGRA& src) : _p(src._p) {}
		PixelBGRA& operator=(const PixelBGRA& src) { _p = src._p; return *this; }
		// Move constructor/operator
		PixelBGRA(const PixelBGRA&& src) : _p(src._p) {}
		PixelBGRA& operator=(const PixelBGRA&& src) noexcept { _p = src._p; return *this; }
	public:
		UInt8* GetPointer() { return _p; }
		const UInt8* GetPointer() const { return _p; }
		void Forward() { _p += bytesPerPixel; }
		void Forward(size_t n) { _p += bytesPerPixel * n; }
		template<typename T_Pixel> void Inject(const T_Pixel& pixel) {
			*(_p + 0) = pixel.GetB(), *(_p + 1) = pixel.GetG(), *(_p + 2) = pixel.GetR(), *(_p + 3) = pixel.GetA();
		}
		template<typename T_Pixel> void InjectN(const T_Pixel& pixel, size_t n) {}
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
	Format _format;
	size_t _width, _height;
public:
	// Constructor
	Image(Format format, Memory* pMemory, size_t width, size_t height) :
		_pMemory(pMemory), _format(format), _width(width), _height(height) {}
	// Copy constructor/operator
	Image(const Image& src) = delete;
	Image& operator=(const Image& src) = delete;
	// Move constructor/operator
	Image(Image&& src) = delete;
	Image& operator=(Image&& src) noexcept = delete;
protected:
	~Image() = default;
public:
	UInt8* GetPointer() { return reinterpret_cast<UInt8*>(_pMemory->GetPointer()); }
	template<typename T_Pixel> void FillTmpl(const Color& color);
	void Fill(const Color& color);
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
