//==============================================================================
// VType_CallableMember.h
//==============================================================================
#ifndef GURAX_VTYPE_CALLABLEMEMBER_H
#define GURAX_VTYPE_CALLABLEMEMBER_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_CallableMember
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_CallableMember : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_CallableMember VTYPE_CallableMember;

//------------------------------------------------------------------------------
// Value_CallableMember
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_CallableMember : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_CallableMember);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_CallableMember");
protected:
	RefPtr<Value> _pValueThis;
	RefPtr<Value> _pValueProp;
public:
	static VType& vtype;
public:
	// Constructor
	Value_CallableMember(Value* pValueThis, Value* pValueProp, VType& vtype = VTYPE_CallableMember) :
		Value_Object(vtype), _pValueThis(pValueThis), _pValueProp(pValueProp) {}
	// Copy constructor/operator
	Value_CallableMember(const Value_CallableMember& src) :
		Value_Object(src), _pValueThis(src._pValueThis->Reference()),
		_pValueProp(src._pValueProp->Reference()) {}
	Value_CallableMember& operator=(const Value_CallableMember& src) = delete;
	// Move constructor/operator
	Value_CallableMember(Value_CallableMember&& src) = delete;
	Value_CallableMember& operator=(Value_CallableMember&& src) noexcept = delete;
protected:
	// Destructor
	~Value_CallableMember() = default;
public:
	Value& GetValueThis() const { return *_pValueThis; }
	Value& GetValueProp() const { return *_pValueProp; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return reinterpret_cast<size_t>(this); }
	virtual bool IsEqualTo(const Value& value) const override { return this == &value; }
	virtual bool IsLessThan(const Value& value) const override { return this < &value; }
	virtual String ToString(const StringStyle& ss) const override;
	virtual bool CanBeCallableMember() const override { return true; }
	virtual void PresentHelp(Processor& processor, const Symbol* pLangCode) const override;
	virtual const DeclCallable* GetDeclCallable() override;
	virtual void DoCall(Processor& processor, Argument& argument) override;
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
	virtual Value* DoIndexGet(const Index& index) const override;
	virtual void DoIndexSet(Processor& processor, const Index& index, RefPtr<Value> pValue) override;
	virtual bool DoEmptyIndexGet(Value** ppValue) const override;
	virtual bool DoEmptyIndexSet(RefPtr<Value> pValue) override;
	virtual bool DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const override;
	virtual bool DoSingleIndexSet(Processor& processor, const Value& valueIndex, RefPtr<Value> pValue) override;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag) override;
	virtual bool DoSetProperty(Processor& processor, const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr) override;
};

}

#endif
