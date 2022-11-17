//==============================================================================
// VType_NumberTrait.h
//==============================================================================
#ifndef GURAX_VTYPE_NUMBERTRAIT_H
#define GURAX_VTYPE_NUMBERTRAIT_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_NumberTrait
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_NumberTrait : public VType {
public:
	RefPtr<Value> pValue_int8;
	RefPtr<Value> pValue_uint8;
	RefPtr<Value> pValue_int16;
	RefPtr<Value> pValue_uint16;
	RefPtr<Value> pValue_int32;
	RefPtr<Value> pValue_uint32;
	RefPtr<Value> pValue_int64;
	RefPtr<Value> pValue_uint64;
	RefPtr<Value> pValue_half;
	RefPtr<Value> pValue_float;
	RefPtr<Value> pValue_double;
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_NumberTrait VTYPE_NumberTrait;

//------------------------------------------------------------------------------
// Value_NumberTrait
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_NumberTrait : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_NumberTrait);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_NumberTrait");
protected:
	size_t _bytes;
	Double _numMin, _numMax;
public:
	static VType& vtype;
public:
	// Constructor
	Value_NumberTrait() = delete;
	explicit Value_NumberTrait(size_t bytes, Double numMin, Double numMax, VType& vtype = VTYPE_NumberTrait) :
		Value_Object(vtype), _bytes(bytes), _numMin(numMin), _numMax(numMax) {}
	// Copy constructor/operator
	Value_NumberTrait(const Value_NumberTrait& src) = delete;
	Value_NumberTrait& operator=(const Value_NumberTrait& src) = delete;
	// Move constructor/operator
	Value_NumberTrait(Value_NumberTrait&& src) noexcept = delete;
	Value_NumberTrait& operator=(Value_NumberTrait&& src) noexcept = delete;
protected:
	// Destructor
	~Value_NumberTrait() = default;
public:
	size_t GetBytes() const { return _bytes; }
	Double GetNumMin() const { return _numMin; }
	Double GetNumMax() const { return _numMax; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return 0;
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return this == &value;
	}
	virtual bool IsLessThan(const Value& value) const override {
		return this < &value;
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
