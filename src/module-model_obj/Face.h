//==============================================================================
// Face.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_FACE_H
#define GURAX_MODULE_MODEL_OBJ_FACE_H
#include <gurax.h>
#include "Index.h"
#include "Vertex3.h"
#include "Vertex4.h"

Gurax_BeginModuleScope(model_obj)

class Content;

//------------------------------------------------------------------------------
// Face
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Face : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Face);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Face");
private:
	IndexTripletList _indexTripletList;
public:
	// Constructor
	Face() { _indexTripletList.reserve(4); }
	// Copy constructor/operator
	Face(const Face& src) = delete;
	Face& operator=(const Face& src) = delete;
	// Move constructor/operator
	Face(Face&& src) noexcept = delete;
	Face& operator=(Face&& src) noexcept = delete;
protected:
	~Face() = default;
public:
	void AddIndexTriplet(int iV, int iVt, int iVn) { _indexTripletList.push_back(IndexTriplet(iV, iVt, iVn)); }
	const IndexTripletList& GetIndexTripletList() const { return _indexTripletList; }
	const Vertex4* GetV(const Content& content, size_t iIndexTriplet) const;
	const Vertex3* GetVt(const Content& content, size_t iIndexTriplet) const;
	const Vertex3* GetVn(const Content& content, size_t iIndexTriplet) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Face& other) const { return this == &other; }
	bool IsEqualTo(const Face& other) const { return IsIdentical(other); }
	bool IsLessThan(const Face& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// FaceList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE FaceList : public ListBase<Face*> {
};

//------------------------------------------------------------------------------
// FaceOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE FaceOwner : public FaceList {
public:
	~FaceOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
