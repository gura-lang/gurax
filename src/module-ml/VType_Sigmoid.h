//==============================================================================
// VType_Sigmoid.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_SIGMOID_H
#define GURAX_MODULE_ML_VTYPE_SIGMOID_H
#include <gurax.h>
#include "Sigmoid.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_Sigmoid
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Sigmoid : public VType {
public:
	static const SerialId serialId = 0x0000010b;
public:
	VType_Sigmoid() : VType(serialId) {}
	explicit VType_Sigmoid(const Symbol* pSymbol) : VType(serialId) {}
	explicit VType_Sigmoid(const char* name) : VType(name, serialId) {}
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoDeserialize(Stream& stream) const override;
};

extern GURAX_DLLDECLARE VType_Sigmoid VTYPE_Sigmoid;

//------------------------------------------------------------------------------
// Value_Sigmoid
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Sigmoid : public Value_Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Sigmoid);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Sigmoid");
public:
	static VType& vtype;
public:
	// Constructor
	Value_Sigmoid() = delete;
	explicit Value_Sigmoid(Sigmoid* pSigmoid, VType& vtype = VTYPE_Sigmoid) : Value_Gear(pSigmoid, vtype) {}
	// Copy constructor/operator
	Value_Sigmoid(const Value_Sigmoid& src) : Value_Gear(src) {}
	Value_Sigmoid& operator=(const Value_Sigmoid& src) = delete;
	// Move constructor/operator
	Value_Sigmoid(Value_Sigmoid&& src) noexcept = delete;
	Value_Sigmoid& operator=(Value_Sigmoid&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Sigmoid() = default;
public:
	Sigmoid& GetSigmoid() { return dynamic_cast<Sigmoid&>(GetGear()); }
	const Sigmoid& GetSigmoid() const { return dynamic_cast<const Sigmoid&>(GetGear()); }
public:
	static Sigmoid& GetSigmoid(Value& value) {
		return dynamic_cast<Value_Sigmoid&>(value).GetSigmoid();
	}
	static const Sigmoid& GetSigmoid(const Value& value) {
		return dynamic_cast<const Value_Sigmoid&>(value).GetSigmoid();
	}
	static Sigmoid* GetEntityPtr(Value& value) { return &GetSigmoid(value); }
	static const Sigmoid* GetEntityPtr(const Value& value) { return &GetSigmoid(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetSigmoid().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetSigmoid().IsEqualTo(Value_Sigmoid::GetSigmoid(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetSigmoid().IsLessThan(Value_Sigmoid::GetSigmoid(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	virtual bool DoSerialize(Stream& stream) const override;
};

Gurax_EndModuleScope(ml)

#endif
