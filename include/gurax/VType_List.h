//==============================================================================
// VType_List.h
//==============================================================================
#ifndef GURAX_VTYPE_LIST_H
#define GURAX_VTYPE_LIST_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_List
//------------------------------------------------------------------------------
class VType_List : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frame) override;
};

extern VType_List VTYPE_List;

//------------------------------------------------------------------------------
// Value_List
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_List : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_List);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_List");
private:
	RefPtr<ValueTypedOwner> _pValueTypedOwner;
public:
	// Constructor
	Value_List(VType& vtype = VTYPE_List) :
		Value_List(new ValueTypedOwner(), vtype) {}
	explicit Value_List(ValueTypedOwner* pValueTypedOwner, VType& vtype = VTYPE_List) :
		Value_Object(vtype), _pValueTypedOwner(pValueTypedOwner) {}
	// Copy constructor/operator
	Value_List(const Value_List& src) :
		Value_Object(src), _pValueTypedOwner(src._pValueTypedOwner->Reference()) {}
	Value_List& operator=(const Value_List& src) = delete;
	// Move constructor/operator
	Value_List(Value_List&& src) = delete;
	Value_List& operator=(Value_List&& src) noexcept = delete;
protected:
	// Destructor
	~Value_List() = default;
public:
	ValueTypedOwner& GetValueTypedOwner() { return *_pValueTypedOwner; }
	const ValueTypedOwner& GetValueTypedOwner() const { return *_pValueTypedOwner; }
	const ValueOwner& GetValueOwner() const { return GetValueTypedOwner().GetValueOwner(); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return new Value_List(*this); }
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
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetValueOwner().ToString(ss);
	}
	virtual Value* DoIndexGet(const Index& index) const override;
	virtual void DoIndexSet(const Index& index, Value* pValue) override;
};

}

#endif
