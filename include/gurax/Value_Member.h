//==============================================================================
// Value_Member.h
//==============================================================================
#ifndef GURAX_VALUE_MEMBER_H
#define GURAX_VALUE_MEMBER_H
#include "Value_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Member
//------------------------------------------------------------------------------
class VType_Member : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frame) override;
};

extern VType_Member VTYPE_Member;

//------------------------------------------------------------------------------
// Value_Member
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Member : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Member);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Member");
private:
	RefPtr<Value> _pValueTarget;
	RefPtr<Value> _pValueSelector;
public:
	// Constructor
	Value_Member(Value* pValueTarget, Value* pValueSelector, VType& vtype = VTYPE_Member) :
		Value_Object(vtype), _pValueTarget(pValueTarget), _pValueSelector(pValueSelector) {}
	// Copy constructor/operator
	Value_Member(const Value_Member& src) :
		Value_Object(src), _pValueTarget(src._pValueTarget->Reference()),
		_pValueSelector(src._pValueSelector->Reference()) {}
	Value_Member& operator=(const Value_Member& src) = delete;
	// Move constructor/operator
	Value_Member(Value_Member&& src) = delete;
	Value_Member& operator=(Value_Member&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Member() = default;
public:
	Value& GetValueTarget() const { return *_pValueTarget; }
	Value& GetValueSelector() const { return *_pValueSelector; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return reinterpret_cast<size_t>(this); }
	virtual bool IsEqualTo(const Value* pValue) const override { return this == pValue; }
	virtual bool IsLessThan(const Value* pValue) const override { return this < pValue; }
	virtual String ToStringDetail(const StringStyle& ss) const override;
};

}

#endif
