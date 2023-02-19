//==============================================================================
// Face.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_FACE_H
#define GURAX_MODULE_MODEL_OBJ_FACE_H
#include <gurax.h>
#include "Index.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Face
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Face : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Face);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Face");
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
