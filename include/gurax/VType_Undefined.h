//==============================================================================
// VType_Undefined.h
//==============================================================================
#ifndef GURAX_VTYPE_UNDEFINED_H
#define GURAX_VTYPE_UNDEFINED_H
#include "Value.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Undefined
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Undefined : public VType {
public:
	using VType::VType;
	virtual bool IsUndefined() const override { return true; }
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Undefined VTYPE_Undefined;

//------------------------------------------------------------------------------
// Value_Undefined
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Undefined : public Value {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Undefined);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Undefined");
public:
	// Constructor
	Value_Undefined() : Value(VTYPE_Undefined) {}
	// Copy constructor/operator
	Value_Undefined(const Value_Undefined& src) = delete;
	Value_Undefined& operator=(const Value_Undefined& src) = delete;
	// Move constructor/operator
	Value_Undefined(Value_Undefined&& src) = delete;
	Value_Undefined& operator=(Value_Undefined&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Value_Undefined() = default;
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value* pValue) const override { return IsSameType(pValue); }
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)? false : GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override { return ToStringDigest(ss); }
	// Virtual functions for runtime process
	virtual bool IsValid() const override { return false; }
	virtual bool IsUndefined() const override { return true; }
	virtual Value* PickValue() override { return Value::nil(); }
	virtual bool GetBool() const override { return false; }
};

}

#endif
