//==============================================================================
// VType_Member.h
//==============================================================================
#ifndef GURAX_VTYPE_MEMBER_H
#define GURAX_VTYPE_MEMBER_H
#include "VType_Object.h"

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
	RefPtr<Value> _pValueThis;
	RefPtr<Value> _pValueProp;
public:
	// Constructor
	Value_Member(Value* pValueThis, Value* pValueProp, VType& vtype = VTYPE_Member) :
		Value_Object(vtype), _pValueThis(pValueThis), _pValueProp(pValueProp) {}
	// Copy constructor/operator
	Value_Member(const Value_Member& src) :
		Value_Object(src), _pValueThis(src._pValueThis->Reference()),
		_pValueProp(src._pValueProp->Reference()) {}
	Value_Member& operator=(const Value_Member& src) = delete;
	// Move constructor/operator
	Value_Member(Value_Member&& src) = delete;
	Value_Member& operator=(Value_Member&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Member() = default;
public:
	Value& GetValueThis() const { return *_pValueThis; }
	Value& GetValueProp() const { return *_pValueProp; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return reinterpret_cast<size_t>(this); }
	virtual bool IsEqualTo(const Value* pValue) const override { return this == pValue; }
	virtual bool IsLessThan(const Value* pValue) const override { return this < pValue; }
	virtual String ToStringDetail(const StringStyle& ss) const override;
	virtual const DeclCaller* GetDeclCaller() override { return GetValueProp().GetDeclCaller(); }
	virtual void DoCall(Frame& frame, Argument& argument) override {
		argument.SetValueThis(GetValueThis().Reference());
		GetValueProp().DoCall(frame, argument);
	}
	virtual void DoIndexAccess(Frame& frame, Argument& argument) override {
		GetValueProp().DoIndexAccess(frame, argument);
	}
};

}

#endif
