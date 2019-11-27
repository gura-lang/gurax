//==============================================================================
// VType_List.h
//==============================================================================
#ifndef GURAX_VTYPE_LIST_H
#define GURAX_VTYPE_LIST_H
#include "VType_Object.h"
#include "VType_Undefined.h"
#include "ValueTypedOwner.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_List
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_List : public VType {
public:
	using VType::VType;
	virtual bool IsList() const override { return true; }
	virtual bool IsListOrIterator() const override { return true; }
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
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
protected:
	RefPtr<ValueTypedOwner> _pValueTypedOwner;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_List(ValueTypedOwner* pValueTypedOwner, VType& vtype = VTYPE_List) :
		Value_Object(vtype), _pValueTypedOwner(pValueTypedOwner) {}
	Value_List(VType& vtype = VTYPE_List) :
		Value_List(new ValueTypedOwner(VTYPE_Undefined, new ValueOwner()), vtype) {}
	Value_List(VType& vtypeOfElems, ValueOwner* pValueOwner, VType& vtype = VTYPE_List) :
		Value_List(new ValueTypedOwner(vtypeOfElems, pValueOwner), vtype) {}
	explicit Value_List(ValueOwner* pValueOwner, VType& vtype = VTYPE_List) :
		Value_List(new ValueTypedOwner(pValueOwner), vtype) {}
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
	static Value_List* Create(Value* pValue);
	static Value_List* Create(Value* pValue1, Value* pValue2);
	static Value_List* Create(Value* pValue1, Value* pValue2, Value* pValue3);
	static Value_List* Create(Value* pValue1, Value* pValue2, Value* pValue3, Value* pValue4);
public:
	ValueTypedOwner& GetValueTypedOwner() { return *_pValueTypedOwner; }
	const ValueTypedOwner& GetValueTypedOwner() const { return *_pValueTypedOwner; }
	const ValueOwner& GetValueOwner() const { return GetValueTypedOwner().GetValueOwner(); }
public:
	static ValueTypedOwner& GetValueTypedOwner(Value& value) {
		return dynamic_cast<Value_List&>(value).GetValueTypedOwner();
	}
	static const ValueTypedOwner& GetValueTypedOwner(const Value& value) {
		return dynamic_cast<const Value_List&>(value).GetValueTypedOwner();
	}
	static const ValueOwner& GetValueOwner(const Value& value) {
		return dynamic_cast<const Value_List&>(value).GetValueOwner();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return new Value_List(GetValueTypedOwner().Clone()); }
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
	virtual String ToStringDigest(const StringStyle& ss) const override;
	virtual String ToStringDetail(const StringStyle& ss) const override;
public:
	virtual bool IsIterable() const override { return true; }
	virtual bool IsList() const override { return true; }
	virtual bool IsMappable(const DeclArg& declArg, DeclCallable::Flags flags) const override;
	virtual void UpdateMapMode(Argument& argument) const override;
	virtual const DeclCallable* GetDeclCallable() override;
	virtual void DoCall(Processor& processor, Argument& argument) override;
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
	virtual Value* DoIndexGet(const Index& index) const override;
	virtual void DoIndexSet(const Index& index, Value* pValue) override;
	virtual Value* DoIndexOpApply(const Index& index, const Value& value, Processor& processor, const Operator& op) override;
	virtual Iterator* DoGenIterator() const override;
};

}

#endif
