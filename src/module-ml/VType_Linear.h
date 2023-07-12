//==============================================================================
// VType_Linear.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_LINEAR_H
#define GURAX_MODULE_ML_VTYPE_LINEAR_H
#include <gurax.h>
#include "Linear.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_Linear
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Linear : public VType {
public:
	static const SerialId serialId = 0x00000104;
public:
	VType_Linear() : VType(serialId) {}
	explicit VType_Linear(const Symbol* pSymbol) : VType(serialId) {}
	explicit VType_Linear(const char* name) : VType(name, serialId) {}
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoDeserialize(Stream& stream) const override;
};

extern GURAX_DLLDECLARE VType_Linear VTYPE_Linear;

//------------------------------------------------------------------------------
// Value_Linear
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Linear : public Value_Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Linear);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Linear");
public:
	static VType& vtype;
public:
	// Constructor
	Value_Linear() = delete;
	explicit Value_Linear(Linear* pLinear, VType& vtype = VTYPE_Linear) : Value_Gear(pLinear, vtype) {}
	// Copy constructor/operator
	Value_Linear(const Value_Linear& src) : Value_Gear(src) {}
	Value_Linear& operator=(const Value_Linear& src) = delete;
	// Move constructor/operator
	Value_Linear(Value_Linear&& src) noexcept = delete;
	Value_Linear& operator=(Value_Linear&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Linear() = default;
public:
	Linear& GetLinear() { return dynamic_cast<Linear&>(GetGear()); }
	const Linear& GetLinear() const { return dynamic_cast<const Linear&>(GetGear()); }
public:
	static Linear& GetLinear(Value& value) {
		return dynamic_cast<Value_Linear&>(value).GetLinear();
	}
	static const Linear& GetLinear(const Value& value) {
		return dynamic_cast<const Value_Linear&>(value).GetLinear();
	}
	static Linear* GetEntityPtr(Value& value) { return &GetLinear(value); }
	static const Linear* GetEntityPtr(const Value& value) { return &GetLinear(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetLinear().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetLinear().IsEqualTo(Value_Linear::GetLinear(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetLinear().IsLessThan(Value_Linear::GetLinear(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	virtual bool DoSerialize(Stream& stream) const override;
};

Gurax_EndModuleScope(ml)

#endif
