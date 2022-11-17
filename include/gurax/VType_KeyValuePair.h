//==============================================================================
// VType_KeyValuePair.h
//==============================================================================
#ifndef GURAX_VTYPE_KeyValuePair_H
#define GURAX_VTYPE_KeyValuePair_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_KeyValuePair
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_KeyValuePair : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_KeyValuePair VTYPE_KeyValuePair;

//------------------------------------------------------------------------------
// Value_KeyValuePair
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_KeyValuePair : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_KeyValuePair);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_KeyValuePair");
protected:
	RefPtr<Value> _pValueKey;
	RefPtr<Value> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_KeyValuePair(Value* pValueKey, Value* pValue, VType& vtype = VTYPE_KeyValuePair) :
		Value_Object(vtype), _pValueKey(pValueKey), _pValue(pValue) {}
	// Copy constructor/operator
	Value_KeyValuePair(const Value_KeyValuePair& src) :
		Value_Object(vtype), _pValueKey(src._pValueKey->Reference()), _pValue(src._pValue->Reference()) {}
	Value_KeyValuePair& operator=(const Value_KeyValuePair& src) = delete;
	// Move constructor/operator
	Value_KeyValuePair(Value_KeyValuePair&& src) = delete;
	Value_KeyValuePair& operator=(Value_KeyValuePair&& src) noexcept = delete;
protected:
	// Destructor
	~Value_KeyValuePair() = default;
public:
	// Virtual functions of Value
	virtual const Value& GetValueKey() const override { return *_pValueKey; }
	virtual const Value& GetValue() const override { return *_pValue; }
	virtual Value* Clone() const override { return Reference(); }
};

}

#endif
