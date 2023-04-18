//==============================================================================
// VType_ReLU.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_RELU_H
#define GURAX_MODULE_ML_VTYPE_RELU_H
#include <gurax.h>
#include "ReLU.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_ReLU
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_ReLU : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_ReLU VTYPE_ReLU;

//------------------------------------------------------------------------------
// Value_ReLU
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_ReLU : public Value_Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_ReLU);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_ReLU");
public:
	static VType& vtype;
public:
	// Constructor
	Value_ReLU() = delete;
	explicit Value_ReLU(ReLU* pReLU, VType& vtype = VTYPE_ReLU) : Value_Gear(pReLU, vtype) {}
	// Copy constructor/operator
	Value_ReLU(const Value_ReLU& src) : Value_Gear(src) {}
	Value_ReLU& operator=(const Value_ReLU& src) = delete;
	// Move constructor/operator
	Value_ReLU(Value_ReLU&& src) noexcept = delete;
	Value_ReLU& operator=(Value_ReLU&& src) noexcept = delete;
protected:
	// Destructor
	~Value_ReLU() = default;
public:
	ReLU& GetReLU() { return dynamic_cast<ReLU&>(GetGear()); }
	const ReLU& GetReLU() const { return dynamic_cast<const ReLU&>(GetGear()); }
public:
	static ReLU& GetReLU(Value& value) {
		return dynamic_cast<Value_ReLU&>(value).GetReLU();
	}
	static const ReLU& GetReLU(const Value& value) {
		return dynamic_cast<const Value_ReLU&>(value).GetReLU();
	}
	static ReLU* GetEntityPtr(Value& value) { return &GetReLU(value); }
	static const ReLU* GetEntityPtr(const Value& value) { return &GetReLU(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetReLU().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetReLU().IsEqualTo(Value_ReLU::GetReLU(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetReLU().IsLessThan(Value_ReLU::GetReLU(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml)

#endif
