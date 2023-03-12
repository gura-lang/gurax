//==============================================================================
// VType_MergingGroup.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_MERGINGGROUP_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_MERGINGGROUP_H
#include <gurax.h>
#include "Data.h"
#include "MergingGroup.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_MergingGroup
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_MergingGroup : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_MergingGroup VTYPE_MergingGroup;

//------------------------------------------------------------------------------
// Value_MergingGroup
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_MergingGroup : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_MergingGroup);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_MergingGroup");
protected:
	RefPtr<MergingGroup> _pMergingGroup;
public:
	static VType& vtype;
public:
	// Constructor
	Value_MergingGroup() = delete;
	explicit Value_MergingGroup(MergingGroup* pMergingGroup, VType& vtype = VTYPE_MergingGroup) :
		Value_Object(vtype), _pMergingGroup(pMergingGroup) {}
	// Copy constructor/operator
	Value_MergingGroup(const Value_MergingGroup& src) :
		Value_Object(src), _pMergingGroup(src._pMergingGroup->Reference()) {}
	Value_MergingGroup& operator=(const Value_MergingGroup& src) = delete;
	// Move constructor/operator
	Value_MergingGroup(Value_MergingGroup&& src) noexcept = delete;
	Value_MergingGroup& operator=(Value_MergingGroup&& src) noexcept = delete;
protected:
	// Destructor
	~Value_MergingGroup() = default;
public:
	MergingGroup& GetMergingGroup() { return *_pMergingGroup; }
	const MergingGroup& GetMergingGroup() const { return *_pMergingGroup; }
public:
	static MergingGroup& GetMergingGroup(Value& value) {
		return dynamic_cast<Value_MergingGroup&>(value).GetMergingGroup();
	}
	static const MergingGroup& GetMergingGroup(const Value& value) {
		return dynamic_cast<const Value_MergingGroup&>(value).GetMergingGroup();
	}
	static MergingGroup* GetEntityPtr(Value& value) { return &GetMergingGroup(value); }
	static const MergingGroup* GetEntityPtr(const Value& value) { return &GetMergingGroup(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetMergingGroup().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetMergingGroup().IsEqualTo(Value_MergingGroup::GetMergingGroup(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetMergingGroup().IsLessThan(Value_MergingGroup::GetMergingGroup(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
