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
		float normal[3];
		float vertex1[3];
		float vertex2[3];
		float vertex3[3];
		UInt16 attr;
		enum { Size = sizeof(float) * 3 * 4 + sizeof(UInt16) };
	};
private:
	Vertex _normal;
	Vertex _vertexes[3];
	UInt16 _attr;
public:
	// Constructor
	Face() {}
	// Copy constructor/operator
	Face(const Face& src);
	Face& operator=(const Face& src) = delete;
	// Move constructor/operator
	Face(Face&& src) noexcept = delete;
	Face& operator=(Face&& src) noexcept = delete;
protected:
	~Face() = default;
public:
	void SetNormal(Vertex& normal) { _normal = normal; }
	void SetVertex(size_t idx, const Vertex& vertex) { _vertexes[idx] = vertex; }
	void SetAttr(UShort attr) { _attr = attr; }
	const Vertex &GetNormal() const { return _normal; }
	const Vertex &GetVertex(size_t idx) const { return _vertexes[idx]; }
	UInt16 GetAttr() const { return _attr; }
	void UpdateNormal();
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Face& other) const { return this == &other; }
	bool IsEqualTo(const Face& other) const { return IsIdentical(other); }
	bool IsLessThan(const Face& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(model_stl)

#endif
