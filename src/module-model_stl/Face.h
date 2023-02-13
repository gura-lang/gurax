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
	Vertex _vertex1;
	Vertex _vertex2;
	Vertex _vertex3;
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
	void SetVertex1(const Vertex& vertex) { _vertex1 = vertex; }
	void SetVertex2(const Vertex& vertex) { _vertex2 = vertex; }
	void SetVertex3(const Vertex& vertex) { _vertex3 = vertex; }
	void SetAttr(UInt16 attr) { _attr = attr; }
	const Vertex& GetNormal() const { return _normal; }
	const Vertex& GetVertex1() const { return _vertex1; }
	const Vertex& GetVertex2() const { return _vertex2; }
	const Vertex& GetVertex3() const { return _vertex3; }
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
