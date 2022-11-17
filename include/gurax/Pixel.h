//==============================================================================
// Pixel.h
//==============================================================================
#ifndef GURAX_PIXEL_H
#define GURAX_PIXEL_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Pixel
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Pixel : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Pixel);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Pixel");
protected:
	Color _color;
	int _x, _y;
public:
	// Constructor
	Pixel(const Color& color, int x, int y) : _color(color), _x(x), _y(y) {}
	// Copy constructor/operator
	Pixel(const Pixel& src) = delete;
	Pixel& operator=(const Pixel& src) = delete;
	// Move constructor/operator
	Pixel(Pixel&& src) = delete;
	Pixel& operator=(Pixel&& src) noexcept = delete;
protected:
	~Pixel() = default;
public:
	const Color& GetColor() const { return _color; }
	int GetX() const { return _x; }
	int GetY() const { return _y; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Pixel& other) const { return this == &other; }
	bool IsEqualTo(const Pixel& other) const { return IsIdentical(other); }
	bool IsLessThan(const Pixel& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
