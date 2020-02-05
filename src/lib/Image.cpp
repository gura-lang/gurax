//==============================================================================
// Image.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax/VType_Image.h>

namespace Gurax {

class PixelBGR {
protected:
	UInt8* _p;
public:
	static const size_t bytes = 3;
public:
	PixelBGR(UInt8* p) : _p(p) {}
public:
	void SetColor(const Color &color) {
		*(_p + 2) = color.GetR(); *(_p + 1) = color.GetG(); *(_p + 0) = color.GetB();
	}
	void SetR(UInt8 r) { *(_p + 2) = r; }
	void SetG(UInt8 g) { *(_p + 1) = g; }
	void SetB(UInt8 b) { *(_p + 0) = b; }
	void SetA(UInt8 a) {}
	UInt8 GetR() const { return *(_p + 2); }
	UInt8 GetG() const { return *(_p + 1); }
	UInt8 GetB() const { return *(_p + 0); }
	UInt8 GetA() const { return 0xff; }
};

class PixelBGRA {
protected:
	UInt8* _p;
public:
	static const size_t bytes = 4;
public:
	PixelBGRA(UInt8* p) : _p(p) {}
public:
	void SetColor(const Color &color) {
		*(_p + 2) = color.GetR(); *(_p + 1) = color.GetG(); *(_p + 0) = color.GetB();
		*(_p + 3) = color.GetA();
	}
	void SetR(UInt8 r) { *(_p + 2) = r; }
	void SetG(UInt8 g) { *(_p + 1) = g; }
	void SetB(UInt8 b) { *(_p + 0) = b; }
	void SetA(UInt8 a) { *(_p + 3) = a; }
	UInt8 GetR() const { return *(_p + 2); }
	UInt8 GetG() const { return *(_p + 1); }
	UInt8 GetB() const { return *(_p + 0); }
	UInt8 GetA() const { return *(_p + 3); }
};

//------------------------------------------------------------------------------
// Image
//------------------------------------------------------------------------------
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
