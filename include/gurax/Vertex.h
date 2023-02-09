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
class GURAX_DLLDECLARE Vertex : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Vertex);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Vertex");
public:
	// Constructor
	Vertex() {}
	// Copy constructor/operator
	Vertex(const Vertex& src) = delete;
	Vertex& operator=(const Vertex& src) = delete;
	// Move constructor/operator
	Vertex(Vertex&& src) noexcept = delete;
	Vertex& operator=(Vertex&& src) noexcept = delete;
protected:
	~Vertex() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Vertex& other) const { return this == &other; }
	bool IsEqualTo(const Vertex& other) const { return IsIdentical(other); }
	bool IsLessThan(const Vertex& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
