//==============================================================================
// VType_GroupName.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_GROUPNAME_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_GROUPNAME_H
#include <gurax.h>
#include "GroupName.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_GroupName
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_GroupName : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_GroupName VTYPE_GroupName;

//------------------------------------------------------------------------------
// Value_GroupName
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_GroupName : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_GroupName);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_GroupName");
protected:
	RefPtr<GroupName> _pGroupName;
public:
	static VType& vtype;
public:
	// Constructor
	Value_GroupName() = delete;
	explicit Value_GroupName(GroupName* pGroupName, VType& vtype = VTYPE_GroupName) :
		Value_Object(vtype), _pGroupName(pGroupName) {}
	// Copy constructor/operator
	Value_GroupName(const Value_GroupName& src) :
		Value_Object(src), _pGroupName(src._pGroupName->Reference()) {}
	Value_GroupName& operator=(const Value_GroupName& src) = delete;
	// Move constructor/operator
	Value_GroupName(Value_GroupName&& src) noexcept = delete;
	Value_GroupName& operator=(Value_GroupName&& src) noexcept = delete;
protected:
	// Destructor
	~Value_GroupName() = default;
public:
	GroupName& GetGroupName() { return *_pGroupName; }
	const GroupName& GetGroupName() const { return *_pGroupName; }
public:
	static GroupName& GetGroupName(Value& value) {
		return dynamic_cast<Value_GroupName&>(value).GetGroupName();
	}
	static const GroupName& GetGroupName(const Value& value) {
		return dynamic_cast<const Value_GroupName&>(value).GetGroupName();
	}
	static GroupName* GetEntityPtr(Value& value) { return &GetGroupName(value); }
	static const GroupName* GetEntityPtr(const Value& value) { return &GetGroupName(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetGroupName().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetGroupName().IsEqualTo(Value_GroupName::GetGroupName(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetGroupName().IsLessThan(Value_GroupName::GetGroupName(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
