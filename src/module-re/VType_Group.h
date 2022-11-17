//==============================================================================
// VType_Group.h
//==============================================================================
#ifndef GURAX_MODULE_RE_VTYPE_GROUP_H
#define GURAX_MODULE_RE_VTYPE_GROUP_H
#include <gurax.h>
#include "Group.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// VType_Group
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Group : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Group VTYPE_Group;

//------------------------------------------------------------------------------
// Value_Group
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Group : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Group);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Group");
protected:
	RefPtr<Group> _pGroup;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Group() = delete;
	Value_Group(Group* pGroup, VType& vtype = VTYPE_Group) :
		Value_Object(vtype), _pGroup(pGroup) {}
	// Copy constructor/operator
	Value_Group(const Value_Group& src) :
		Value_Object(src), _pGroup(src._pGroup->Reference()) {}
	Value_Group& operator=(const Value_Group& src) = delete;
	// Move constructor/operator
	Value_Group(Value_Group&& src) = delete;
	Value_Group& operator=(Value_Group&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Group() = default;
public:
	Group& GetGroup() { return *_pGroup; }
	const Group& GetGroup() const { return *_pGroup; }
public:
	static Group& GetGroup(Value& value) {
		return dynamic_cast<Value_Group&>(value).GetGroup();
	}
	static const Group& GetGroup(const Value& value) {
		return dynamic_cast<const Value_Group&>(value).GetGroup();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetGroup().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetGroup().IsEqualTo(Value_Group::GetGroup(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetGroup().IsLessThan(Value_Group::GetGroup(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(re)

#endif
