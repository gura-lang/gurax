//==============================================================================
// Lod.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_LOD_H
#define GURAX_MODULE_MODEL_OBJ_LOD_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Lod
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Lod : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Lod);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Lod");
public:
	// Constructor
	Lod() {}
	// Copy constructor/operator
	Lod(const Lod& src) = delete;
	Lod& operator=(const Lod& src) = delete;
	// Move constructor/operator
	Lod(Lod&& src) noexcept = delete;
	Lod& operator=(Lod&& src) noexcept = delete;
protected:
	~Lod() = default;
public:
	virtual bool FeedField(const char* field, size_t iParam) override;
	virtual bool FinishField(size_t nParams) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Lod& other) const { return this == &other; }
	bool IsEqualTo(const Lod& other) const { return IsIdentical(other); }
	bool IsLessThan(const Lod& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// LodList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE LodList : public ListBase<Lod*> {
};

//------------------------------------------------------------------------------
// LodOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE LodOwner : public LodList {
public:
	~LodOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
