//==============================================================================
// VType_Array.h
//==============================================================================
#ifndef GURAX_VTYPE_ARRAY_H
#define GURAX_VTYPE_ARRAY_H
#include "VType_Object.h"
#include "Array.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Array
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Array : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Array VTYPE_Array;

//------------------------------------------------------------------------------
// Value_Array
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Array : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Array);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Array");
protected:
	RefPtr<Array> _pArray;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Array() = delete;
	explicit Value_Array(Array* pArray, VType& vtype = VTYPE_Array) :
		Value_Object(vtype), _pArray(pArray) {}
	// Copy constructor/operator
	Value_Array(const Value_Array& src) :
		Value_Object(src), _pArray(src._pArray->Reference()) {}
	Value_Array& operator=(const Value_Array& src) = delete;
	// Move constructor/operator
	Value_Array(Value_Array&& src) = delete;
	Value_Array& operator=(Value_Array&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Array() = default;
public:
	Array& GetArray() { return *_pArray; }
	const Array& GetArray() const { return *_pArray; }
public:
	static Array& GetArray(Value& value) {
		return dynamic_cast<Value_Array&>(value).GetArray();
	}
	static const Array& GetArray(const Value& value) {
		return dynamic_cast<const Value_Array&>(value).GetArray();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetArray().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetArray().IsEqualTo(Value_Array::GetArray(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetArray().IsLessThan(Value_Array::GetArray(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
