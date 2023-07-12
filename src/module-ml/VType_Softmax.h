//==============================================================================
// VType_Softmax.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_SOFTMAX_H
#define GURAX_MODULE_ML_VTYPE_SOFTMAX_H
#include <gurax.h>
#include "Softmax.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_Softmax
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Softmax : public VType {
public:
	static const SerialId serialId = 0x0000010b;
public:
	VType_Softmax() : VType(serialId) {}
	explicit VType_Softmax(const Symbol* pSymbol) : VType(serialId) {}
	explicit VType_Softmax(const char* name) : VType(name, serialId) {}
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoDeserialize(Stream& stream) const override;
};

extern GURAX_DLLDECLARE VType_Softmax VTYPE_Softmax;

//------------------------------------------------------------------------------
// Value_Softmax
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Softmax : public Value_Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Softmax);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Softmax");
public:
	static VType& vtype;
public:
	// Constructor
	Value_Softmax() = delete;
	explicit Value_Softmax(Softmax* pSoftmax, VType& vtype = VTYPE_Softmax) : Value_Gear(pSoftmax, vtype) {}
	// Copy constructor/operator
	Value_Softmax(const Value_Softmax& src) : Value_Gear(src) {}
	Value_Softmax& operator=(const Value_Softmax& src) = delete;
	// Move constructor/operator
	Value_Softmax(Value_Softmax&& src) noexcept = delete;
	Value_Softmax& operator=(Value_Softmax&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Softmax() = default;
public:
	Softmax& GetSoftmax() { return dynamic_cast<Softmax&>(GetGear()); }
	const Softmax& GetSoftmax() const { return dynamic_cast<const Softmax&>(GetGear()); }
public:
	static Softmax& GetSoftmax(Value& value) {
		return dynamic_cast<Value_Softmax&>(value).GetSoftmax();
	}
	static const Softmax& GetSoftmax(const Value& value) {
		return dynamic_cast<const Value_Softmax&>(value).GetSoftmax();
	}
	static Softmax* GetEntityPtr(Value& value) { return &GetSoftmax(value); }
	static const Softmax* GetEntityPtr(const Value& value) { return &GetSoftmax(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetSoftmax().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetSoftmax().IsEqualTo(Value_Softmax::GetSoftmax(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetSoftmax().IsLessThan(Value_Softmax::GetSoftmax(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	virtual bool DoSerialize(Stream& stream) const override;
};

Gurax_EndModuleScope(ml)

#endif
