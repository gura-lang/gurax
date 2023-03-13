//==============================================================================
// MergingGroup.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_MERGINGGROUP_H
#define GURAX_MODULE_MODEL_OBJ_MERGINGGROUP_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// MergingGroup
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MergingGroup : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(MergingGroup);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.MergingGroup");
public:
	// Constructor
	MergingGroup() {}
	// Copy constructor/operator
	MergingGroup(const MergingGroup& src) = delete;
	MergingGroup& operator=(const MergingGroup& src) = delete;
	// Move constructor/operator
	MergingGroup(MergingGroup&& src) noexcept = delete;
	MergingGroup& operator=(MergingGroup&& src) noexcept = delete;
protected:
	~MergingGroup() = default;
public:
	virtual bool FeedField(const char* field, size_t iParam) override;
	virtual bool FinishField(size_t nParams) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const MergingGroup& other) const { return this == &other; }
	bool IsEqualTo(const MergingGroup& other) const { return IsIdentical(other); }
	bool IsLessThan(const MergingGroup& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// MergingGroupList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MergingGroupList : public ListBase<MergingGroup*> {
};

//------------------------------------------------------------------------------
// MergingGroupOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MergingGroupOwner : public MergingGroupList {
public:
	~MergingGroupOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
