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
	static const SerialId serialId = 0x00000016;
public:
	VType_List() : VType(serialId) {}
	explicit VType_List(const Symbol* pSymbol) : VType(serialId) {}
	explicit VType_List(const char* name) : VType(name, serialId) {}
	virtual bool IsList() const override { return true; }
	virtual bool IsListOrIterator() const override { return true; }
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
	virtual Value* DoDeserialize(Stream& stream) const override;
};

extern GURAX_DLLDECLARE VType_List VTYPE_List;

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
	static Value_List* Create(Value* pValue) {
		return new Value_List(ValueOwner::Create(pValue));
	}
	static Value_List* Create(Value* pValue1, Value* pValue2) {
		return new Value_List(ValueOwner::Create(pValue1, pValue2));
	}
	static Value_List* Create(Value* pValue1, Value* pValue2, Value* pValue3) {
		return new Value_List(ValueOwner::Create(pValue1, pValue2, pValue3));
	}
	static Value_List* Create(Value* pValue1, Value* pValue2, Value* pValue3, Value* pValue4) {
		return new Value_List(ValueOwner::Create(pValue1, pValue2, pValue3, pValue4));
	}
	static Value_List* Create(Value* pValue1, Value* pValue2, Value* pValue3, Value* pValue4, Value* pValue5) {
		return new Value_List(ValueOwner::Create(pValue1, pValue2, pValue3, pValue4, pValue5));
	}
	static Value_List* Create(Value* pValue1, Value* pValue2, Value* pValue3, Value* pValue4, Value* pValue5, Value* pValue6) {
		return new Value_List(ValueOwner::Create(pValue1, pValue2, pValue3, pValue4, pValue5, pValue6));
	}
	template<typename T>
	static Value_List* Create(const T* tbl, size_t n) {
		return new Value_List(ValueOwner::Create(tbl, n));
	}
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
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetValueOwner().IsEqualTo(dynamic_cast<const Value_List&>(value).GetValueOwner());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetValueOwner().IsLessThan(dynamic_cast<const Value_List&>(value).GetValueOwner()) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
public:
	virtual bool IsIterable() const override { return true; }
	virtual bool IsIterableOrTuple() const override { return true; }
	virtual bool IsList() const override { return true; }
	virtual bool IsMappable(const DeclArg& declArg, DeclCallable::Flags flags) const override;
	virtual void UpdateMapMode(Argument& argument) const override;
	virtual bool FeedExpandToArgument(Frame& frame, Argument& argument) override;
	virtual const DeclCallable* GetDeclCallable() override;
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
	virtual bool DoEmptyIndexGet(Value** ppValue) const override;
	virtual bool DoEmptyIndexSet(RefPtr<Value> pValue) override;
	virtual bool DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const override;
	virtual bool DoSingleIndexSet(const Value& valueIndex, RefPtr<Value> pValue) override;
	virtual Iterator* DoGenIterator() const override;
	virtual bool DoSerialize(Stream& stream) const override;
};

}

#endif
