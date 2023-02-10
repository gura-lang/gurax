//==============================================================================
// Face.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_STL_FACE_H
#define GURAX_MODULE_MODEL_STL_FACE_H
#include <gurax.h>

Gurax_BeginModuleScope(model_stl)

//------------------------------------------------------------------------------
// Face
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Face : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Face);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.stl.Face");
public:
	struct Packed {
		enum { Size = sizeof(float) * 3 * 4 + sizeof(Uint16) };
		float normal[3];
		float vertex1[3];
		float vertex2[3];
		float vertex3[3];
		UInt16 attr;
	};
private:
	RefPtr<VertexRef> _pNormal;
	VertexRef* _pVertexes[3];
	UInt16 _attr;
public:
	// Constructor
	Face() {}
	// Copy constructor/operator
	Face(const Face& src) = delete;
	Face& operator=(const Face& src) = delete;
	// Move constructor/operator
	Face(Face&& src) noexcept = delete;
	Face& operator=(Face&& src) noexcept = delete;
protected:
	~Face() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Face& other) const { return this == &other; }
	bool IsEqualTo(const Face& other) const { return IsIdentical(other); }
	bool IsLessThan(const Face& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(model_stl)

#endif