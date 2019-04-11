//==============================================================================
// VType_Nil.h
//==============================================================================
#ifndef GURAX_VTYPE_NIL_H
#define GURAX_VTYPE_NIL_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Nil
//------------------------------------------------------------------------------
class VType_Nil : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Nil VTYPE_Nil;

//------------------------------------------------------------------------------
// Value_Nil
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Nil : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Nil);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Nil");
public:
	// Constructor
	explicit Value_Nil(VType& vtype = VTYPE_Nil) : Value_Object(vtype) {}
	// Copy constructor/operator
	Value_Nil(const Value_Nil& src) : Value_Object(src) {}
	Value_Nil& operator=(const Value_Nil& src) = delete;
	// Move constructor/operator
	Value_Nil(Value_Nil&& src) = delete;
	Value_Nil& operator=(Value_Nil&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Value_Nil() = default;
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value* pValue) const override { return IsSameType(pValue); }
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)? false : GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return "nil";
	}
	virtual bool GetBool() const override { return false; }
	virtual bool IsValid() const override { return false; }
};

}

#endif
