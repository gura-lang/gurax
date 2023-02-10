//==============================================================================
// Vertex.h
//==============================================================================
#ifndef GURAX_VERTEX_H
#define GURAX_VERTEX_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Vertex
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Vertex {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Vertex");
public:
	Double x, y, z;
public:
	static const Vertex Zero;
public:
	// Constructor
	Vertex() : x(0), y(0), z(0) {}
	Vertex(Double _x, Double _y) : x(_x), y(_y), z(0) {}
	Vertex(Double _x, Double _y, Double _z) : x(_x), y(_y), z(_z) {}
	Vertex(Double _x, Double _y, Double _z, Double _w) : x(_x), y(_y), z(_z) {}
	//Vertex(const Vertex2 &vertex) : x(vertex.x), y(vertex.y), z(0.) {}
	// Copy constructor/operator
	Vertex(const Vertex& src) : x(src.x), y(src.y), z(src.z) {}
	Vertex& operator=(const Vertex& src) { x = src.x, y = src.y, z = src.z; return *this; }
	// Move constructor/operator
	Vertex(Vertex&& src) noexcept = delete;
	Vertex& operator=(Vertex&& src) noexcept = delete;
public:
	~Vertex() = default;
public:
	bool IsZero() const { return x == 0. && y == 0. && z == 0.; }
public:
	static Vertex Translate(const Vertex& v, Double tx, Double ty, Double tz);
	static Vertex RotateX(const Vertex& v, Double rad);
	static Vertex RotateY(const Vertex& v, Double rad);
	static Vertex RotateZ(const Vertex& v, Double rad);
	static Vertex Neg(const Vertex& v);
	static Vertex Add(const Vertex& v1, const Vertex& v2);
	static Vertex Sub(const Vertex& v1, const Vertex& v2);
	static Vertex Mul(const Vertex& v, Double num);
	static Vertex Div(const Vertex& v, Double num);
	static Double Dot(const Vertex& v1, const Vertex& v2);
	static Vertex Cross(const Vertex& v1, const Vertex& v2);
	static Double Norm(const Vertex& v);
	static Vertex Normal(const Vertex& v1, const Vertex& v2, const Vertex& v3, bool unitFlag);
	static Vertex CreateFromValues(const ValueList& valList);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Vertex& other) const { return this == &other; }
	bool IsEqualTo(const Vertex& other) const { return IsIdentical(other); }
	bool IsLessThan(const Vertex& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
