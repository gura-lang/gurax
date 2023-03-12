//==============================================================================
// GroupName.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_GROUPNAME_H
#define GURAX_MODULE_MODEL_OBJ_GROUPNAME_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// GroupName
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE GroupName : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(GroupName);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.GroupName");
public:
	// Constructor
	GroupName() {}
	// Copy constructor/operator
	GroupName(const GroupName& src) = delete;
	GroupName& operator=(const GroupName& src) = delete;
	// Move constructor/operator
	GroupName(GroupName&& src) noexcept = delete;
	GroupName& operator=(GroupName&& src) noexcept = delete;
protected:
	~GroupName() = default;
public:
	virtual bool FeedField(const char* field, size_t iParam) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const GroupName& other) const { return this == &other; }
	bool IsEqualTo(const GroupName& other) const { return IsIdentical(other); }
	bool IsLessThan(const GroupName& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// GroupNameList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE GroupNameList : public ListBase<GroupName*> {
};

//------------------------------------------------------------------------------
// GroupNameOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE GroupNameOwner : public GroupNameList {
public:
	~GroupNameOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
