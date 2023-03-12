//==============================================================================
// VType_SmoothingGroup.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_SMOOTHINGGROUP_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_SMOOTHINGGROUP_H
#include <gurax.h>
#include "Data.h"
#include "SmoothingGroup.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_SmoothingGroup
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SmoothingGroup : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SmoothingGroup VTYPE_SmoothingGroup;

//------------------------------------------------------------------------------
// Value_SmoothingGroup
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SmoothingGroup : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SmoothingGroup);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SmoothingGroup");
protected:
	RefPtr<SmoothingGroup> _pSmoothingGroup;
public:
	static VType& vtype;
public:
	// Constructor
	Value_SmoothingGroup() = delete;
	explicit Value_SmoothingGroup(SmoothingGroup* pSmoothingGroup, VType& vtype = VTYPE_SmoothingGroup) :
		Value_Object(vtype), _pSmoothingGroup(pSmoothingGroup) {}
	// Copy constructor/operator
	Value_SmoothingGroup(const Value_SmoothingGroup& src) :
		Value_Object(src), _pSmoothingGroup(src._pSmoothingGroup->Reference()) {}
	Value_SmoothingGroup& operator=(const Value_SmoothingGroup& src) = delete;
	// Move constructor/operator
	Value_SmoothingGroup(Value_SmoothingGroup&& src) noexcept = delete;
	Value_SmoothingGroup& operator=(Value_SmoothingGroup&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SmoothingGroup() = default;
public:
	SmoothingGroup& GetSmoothingGroup() { return *_pSmoothingGroup; }
	const SmoothingGroup& GetSmoothingGroup() const { return *_pSmoothingGroup; }
public:
	static SmoothingGroup& GetSmoothingGroup(Value& value) {
		return dynamic_cast<Value_SmoothingGroup&>(value).GetSmoothingGroup();
	}
	static const SmoothingGroup& GetSmoothingGroup(const Value& value) {
		return dynamic_cast<const Value_SmoothingGroup&>(value).GetSmoothingGroup();
	}
	static SmoothingGroup* GetEntityPtr(Value& value) { return &GetSmoothingGroup(value); }
	static const SmoothingGroup* GetEntityPtr(const Value& value) { return &GetSmoothingGroup(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetSmoothingGroup().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetSmoothingGroup().IsEqualTo(Value_SmoothingGroup::GetSmoothingGroup(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetSmoothingGroup().IsLessThan(Value_SmoothingGroup::GetSmoothingGroup(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
