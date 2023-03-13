//==============================================================================
// SmoothingGroup.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_SMOOTHINGGROUP_H
#define GURAX_MODULE_MODEL_OBJ_SMOOTHINGGROUP_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// SmoothingGroup
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SmoothingGroup : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(SmoothingGroup);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.SmoothingGroup");
public:
	// Constructor
	SmoothingGroup() {}
	// Copy constructor/operator
	SmoothingGroup(const SmoothingGroup& src) = delete;
	SmoothingGroup& operator=(const SmoothingGroup& src) = delete;
	// Move constructor/operator
	SmoothingGroup(SmoothingGroup&& src) noexcept = delete;
	SmoothingGroup& operator=(SmoothingGroup&& src) noexcept = delete;
protected:
	~SmoothingGroup() = default;
public:
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) override;
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const SmoothingGroup& other) const { return this == &other; }
	bool IsEqualTo(const SmoothingGroup& other) const { return IsIdentical(other); }
	bool IsLessThan(const SmoothingGroup& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// SmoothingGroupList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SmoothingGroupList : public ListBase<SmoothingGroup*> {
};

//------------------------------------------------------------------------------
// SmoothingGroupOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SmoothingGroupOwner : public SmoothingGroupList {
public:
	~SmoothingGroupOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
