//==============================================================================
// VType_Member_MapToIter.h
//==============================================================================
#ifndef GURAX_VTYPE_MEMBER_MAPTOITER_H
#define GURAX_VTYPE_MEMBER_MAPTOITER_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Member_MapToIter
//------------------------------------------------------------------------------
class VType_Member_MapToIter : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Member_MapToIter VTYPE_Member_MapToIter;

//------------------------------------------------------------------------------
// Value_Member_MapToIter
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Member_MapToIter : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Member_MapToIter);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Member_MapToIter");
protected:
	RefPtr<Value> _pValueThis;
	RefPtr<Value> _pValueProp;
public:
	// Constructor
	Value_Member_MapToIter(Value* pValueThis, Value* pValueProp, VType& vtype = VTYPE_Member_MapToIter) :
		Value_Object(vtype), _pValueThis(pValueThis), _pValueProp(pValueProp) {}
	// Copy constructor/operator
	Value_Member_MapToIter(const Value_Member_MapToIter& src) :
		Value_Object(src), _pValueThis(src._pValueThis->Reference()),
		_pValueProp(src._pValueProp->Reference()) {}
	Value_Member_MapToIter& operator=(const Value_Member_MapToIter& src) = delete;
	// Move constructor/operator
	Value_Member_MapToIter(Value_Member_MapToIter&& src) = delete;
	Value_Member_MapToIter& operator=(Value_Member_MapToIter&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Member_MapToIter() = default;
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
	virtual const DeclCallable* GetDeclCallable() const override;
	virtual void DoCall(Processor& processor, Argument& argument) override;
	virtual Value* DoIndexGet(const Index& index) const override;
	virtual void DoIndexSet(const Index& index, Value* pValue) override;
	virtual Value* DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag) override;
	virtual bool DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr) override;
};

}

#endif
