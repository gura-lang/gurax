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
		Float normal[3];
		Float vertex1[3];
		Float vertex2[3];
		Float vertex3[3];
		UInt16 attr;
		enum { Size = sizeof(Float) * 3 * 4 + sizeof(UInt16) };
	};
private:
	RefPtr<VertexRef> _pNormal;
	RefPtr<VertexRef> _pVertex1;
	RefPtr<VertexRef> _pVertex2;
	RefPtr<VertexRef> _pVertex3;
	UInt16 _attr;
public:
	// Constructor
	Face() : _attr(0) {}
	Face(VertexRef* pVertex1, VertexRef* pVertex2, VertexRef* pVertex3, UInt16 attr) :
		_pVertex1(pVertex1), _pVertex2(pVertex2), _pVertex3(pVertex3), _attr(attr) {}
	// Copy constructor/operator
	Face(const Face& src);
	Face& operator=(const Face& src) = delete;
	// Move constructor/operator
	Face(Face&& src) noexcept = delete;
	Face& operator=(Face&& src) noexcept = delete;
protected:
	~Face() = default;
public:
	void SetNormal(VertexRef* pNormal) { _pNormal.reset(pNormal); }
	void SetVertex1(VertexRef* pVertex) { _pVertex1.reset(pVertex); }
	void SetVertex2(VertexRef* pVertex) { _pVertex2.reset(pVertex); }
	void SetVertex3(VertexRef* pVertex) { _pVertex3.reset(pVertex); }
	void SetAttr(UInt16 attr) { _attr = attr; }
	const VertexRef& GetNormalRef() const;
	const VertexRef& GetVertex1Ref() const { return *_pVertex1; }
	const VertexRef& GetVertex2Ref() const { return *_pVertex2; }
	const VertexRef& GetVertex3Ref() const { return *_pVertex3; }
	const Vertex& GetNormal() const { return GetNormalRef().v; }
	const Vertex& GetVertex1() const { return _pVertex1->v; }
	const Vertex& GetVertex2() const { return _pVertex2->v; }
	const Vertex& GetVertex3() const { return _pVertex3->v; }
	UInt16 GetAttr() const { return _attr; }
	void UpdateNormal() const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Face& other) const { return this == &other; }
	bool IsEqualTo(const Face& other) const { return IsIdentical(other); }
	bool IsLessThan(const Face& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(model_stl)

#endif
