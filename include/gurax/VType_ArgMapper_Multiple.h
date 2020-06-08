//==============================================================================
// VType_ArgMapper_Multiple.h
//==============================================================================
#ifndef GURAX_VTYPE_ARGMAPPER_MULTIPLE_H
#define GURAX_VTYPE_ARGMAPPER_MULTIPLE_H
#include "VType_List.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_ArgMapper_Multiple
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_ArgMapper_Multiple : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_ArgMapper_Multiple VTYPE_ArgMapper_Multiple;

//------------------------------------------------------------------------------
// Value_ArgMapper_Multiple
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_ArgMapper_Multiple : public Value_List {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_ArgMapper_Multiple);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_ArgMapper_Multiple");
protected:
	RefPtr<Value_List> _pValuePicked;
public:
	static VType& vtype;
public:
	// Constructor
	Value_ArgMapper_Multiple() = delete;
	explicit Value_ArgMapper_Multiple(ValueTypedOwner* pValueTypedOwner, VType& vtype = VTYPE_ArgMapper_Multiple) :
		Value_List(pValueTypedOwner, vtype), _pValuePicked(new Value_List()) {}
	// Copy constructor/operator
	Value_ArgMapper_Multiple(const Value_ArgMapper_Multiple& src) = delete;
	Value_ArgMapper_Multiple& operator=(const Value_ArgMapper_Multiple& src) = delete;
	// Move constructor/operator
	Value_ArgMapper_Multiple(Value_ArgMapper_Multiple&& src) = delete;
	Value_ArgMapper_Multiple& operator=(Value_ArgMapper_Multiple&& src) noexcept = delete;
protected:
	// Destructor
	~Value_ArgMapper_Multiple() = default;
public:
	// Virtual functions of Object
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetValueOwner().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetValueOwner().IsEqualTo(dynamic_cast<const Value_List*>(pValue)->GetValueOwner());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetValueOwner().IsLessThan(dynamic_cast<const Value_List*>(pValue)->GetValueOwner()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringFormatter(const StringStyle& ss) const override;
	virtual String ToString(const StringStyle& ss) const override;
public:
	// Virtual functions for runtime process
	virtual bool ReadyToPickValue(Frame& frame, DeclArg& declArg) override;
	virtual bool ReadyToPickValueWithoutCast() override;
	virtual Value* PickValue() override { return _pValuePicked->Reference(); }
	virtual void UpdateIteratorInfo(Iterator::Flags& flags, size_t& len) const override;
};

}

#endif
