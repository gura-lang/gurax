//==============================================================================
// Value_Object.h
//==============================================================================
#ifndef GURAX_VALUE_VALUE_H
#define GURAX_VALUE_VALUE_H
#include "Value.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Object
//------------------------------------------------------------------------------
class VType_Object : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VType_Object VTYPE_Object;

//------------------------------------------------------------------------------
// Value_Object
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Object : public Value {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Object);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Object");
public:
	// Constructor
	Value_Object() : Value_Object(VTYPE_Object) {}
	explicit Value_Object(VType& vtype) : Value(vtype) {}
	// Copy constructor/operator
	Value_Object(const Value_Object& src) : Value(src) {}
	Value_Object& operator=(const Value_Object& src) = delete;
	// Move constructor/operator
	Value_Object(Value_Object&& src) = delete;
	Value_Object& operator=(Value_Object&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Value_Object() = default;
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value* pValue) const override { return IsSameType(pValue); }
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)? false : GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return "Object";
	}
};

}

#endif
