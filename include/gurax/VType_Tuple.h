//==============================================================================
// VType_Tuple.h
//==============================================================================
#ifndef GURAX_VTYPE_TUPLE_H
#define GURAX_VTYPE_TUPLE_H
#include "VType_Object.h"
#include "ValueOwner.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Tuple
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Tuple : public VType {
public:
	static const SerialId serialId = 0x0000000d;
public:
	VType_Tuple() : VType(serialId) {}
	explicit VType_Tuple(const Symbol* pSymbol) : VType(serialId) {}
	explicit VType_Tuple(const char* name) : VType(name, serialId) {}
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_Tuple VTYPE_Tuple;

//------------------------------------------------------------------------------
// Value_Tuple
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Tuple : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Tuple);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Tuple");
protected:
	RefPtr<ValueOwner> _pValueOwner;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Tuple() = delete;
	explicit Value_Tuple(ValueOwner* pValueOwner, VType& vtype = VTYPE_Tuple) :
		Value_Object(vtype), _pValueOwner(pValueOwner) {}
	// Copy constructor/operator
	Value_Tuple(const Value_Tuple& src) :
		Value_Object(src), _pValueOwner(src._pValueOwner.Reference()) {}
	Value_Tuple& operator=(const Value_Tuple& src) = delete;
	// Move constructor/operator
	Value_Tuple(Value_Tuple&& src) noexcept = delete;
	Value_Tuple& operator=(Value_Tuple&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Tuple() = default;
public:
	static Value_Tuple* Create(Value* pValue) {
		return new Value_Tuple(ValueOwner::Create(pValue));
	}
	static Value_Tuple* Create(Value* pValue1, Value* pValue2) {
		return new Value_Tuple(ValueOwner::Create(pValue1, pValue2));
	}
	static Value_Tuple* Create(Value* pValue1, Value* pValue2, Value* pValue3) {
		return new Value_Tuple(ValueOwner::Create(pValue1, pValue2, pValue3));
	}
	static Value_Tuple* Create(Value* pValue1, Value* pValue2, Value* pValue3, Value* pValue4) {
		return new Value_Tuple(ValueOwner::Create(pValue1, pValue2, pValue3, pValue4));
	}
	static Value_Tuple* Create(Value* pValue1, Value* pValue2, Value* pValue3, Value* pValue4, Value* pValue5) {
		return new Value_Tuple(ValueOwner::Create(pValue1, pValue2, pValue3, pValue4, pValue5));
	}
	static Value_Tuple* Create(Value* pValue1, Value* pValue2, Value* pValue3, Value* pValue4, Value* pValue5, Value* pValue6) {
		return new Value_Tuple(ValueOwner::Create(pValue1, pValue2, pValue3, pValue4, pValue5, pValue6));
	}
	template<typename T>
	static Value_Tuple* Create(const T* tbl, size_t n) {
		return new Value_Tuple(ValueOwner::Create(tbl, n));
	}
public:
	ValueOwner& GetValueOwner() { return *_pValueOwner; }
	const ValueOwner& GetValueOwner() const { return *_pValueOwner; }
public:
	static ValueOwner& GetValueOwner(Value& value) {
		return dynamic_cast<Value_Tuple&>(value).GetValueOwner();
	}
	static const ValueOwner& GetValueOwner(const Value& value) {
		return dynamic_cast<const Value_Tuple&>(value).GetValueOwner();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetValueOwner().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetValueOwner().IsEqualTo(dynamic_cast<const Value_Tuple&>(value).GetValueOwner());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetValueOwner().IsLessThan(dynamic_cast<const Value_Tuple&>(value).GetValueOwner()) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
public:
	virtual bool IsIterableOrTuple() const override { return true; }
	virtual bool IsTuple() const override { return true; }
	virtual bool FeedExpandToArgument(Frame& frame, Argument& argument) override;
	virtual bool DoEmptyIndexGet(Value** ppValue) const override;
	virtual bool DoEmptyIndexSet(RefPtr<Value> pValue) override;
	virtual bool DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const override;
	virtual bool DoSingleIndexSet(const Value& valueIndex, RefPtr<Value> pValue) override;

	virtual Iterator* DoGenIterator() const override;
};

}

#endif
