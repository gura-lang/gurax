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
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
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
	const ValueOwner& GetValueOwner() const { return *_pValueOwner; }
public:
	static const ValueOwner& GetValueOwner(const Value& value) {
		return dynamic_cast<const Value_Tuple&>(value).GetValueOwner();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetValueOwner().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetValueOwner().IsEqualTo(dynamic_cast<const Value_Tuple*>(pValue)->GetValueOwner());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetValueOwner().IsLessThan(dynamic_cast<const Value_Tuple*>(pValue)->GetValueOwner()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
