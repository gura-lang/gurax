//==============================================================================
// Value_Bool.h
//==============================================================================
#ifndef GURAX_VALUE_BOOL_H
#define GURAX_VALUE_BOOL_H
#include "Value_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Bool
//------------------------------------------------------------------------------
class VType_Bool : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frame) override;
};

extern VType_Bool VTYPE_Bool;

//------------------------------------------------------------------------------
// Value_Bool
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Bool : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Bool);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Bool");
private:
	bool _flag;
public:
	// Constructor
	explicit Value_Bool(VType& vtype = VTYPE_Bool) :
		Value_Bool(false, vtype) {}
	explicit Value_Bool(bool flag, VType& vtype = VTYPE_Bool) :
		Value_Object(vtype), _flag(flag) {}
	// Copy constructor/operator
	Value_Bool(const Value_Bool& src) :
		Value_Object(src), _flag(src._flag) {}
	Value_Bool& operator=(const Value_Bool& src) = delete;
	// Move constructor/operator
	Value_Bool(Value_Bool&& src) = delete;
	Value_Bool& operator=(Value_Bool&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Bool() = default;
public:
	bool GetBool() const { return _flag; } // override Object::GetBool()
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return static_cast<size_t>(GetBool());
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) && GetBool() == dynamic_cast<const Value_Bool*>(pValue)->GetBool();
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetBool() < dynamic_cast<const Value_Bool*>(pValue)->GetBool() :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return _flag? "true" : "false";
	}
};

}

#endif
