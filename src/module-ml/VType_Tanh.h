//==============================================================================
// VType_Tanh.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_TANH_H
#define GURAX_MODULE_ML_VTYPE_TANH_H
#include <gurax.h>
#include "Tanh.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_Tanh
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Tanh : public VType {
public:
	static const SerialId serialId = 0x0000010a;
public:
	VType_Tanh() : VType(serialId) {}
	explicit VType_Tanh(const Symbol* pSymbol) : VType(serialId) {}
	explicit VType_Tanh(const char* name) : VType(name, serialId) {}
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoDeserialize(Stream& stream) const override;
};

extern GURAX_DLLDECLARE VType_Tanh VTYPE_Tanh;

//------------------------------------------------------------------------------
// Value_Tanh
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Tanh : public Value_Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Tanh);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Tanh");
public:
	static VType& vtype;
public:
	// Constructor
	Value_Tanh() = delete;
	explicit Value_Tanh(Tanh* pTanh, VType& vtype = VTYPE_Tanh) : Value_Gear(pTanh, vtype) {}
	// Copy constructor/operator
	Value_Tanh(const Value_Tanh& src) : Value_Gear(src) {}
	Value_Tanh& operator=(const Value_Tanh& src) = delete;
	// Move constructor/operator
	Value_Tanh(Value_Tanh&& src) noexcept = delete;
	Value_Tanh& operator=(Value_Tanh&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Tanh() = default;
public:
	Tanh& GetTanh() { return dynamic_cast<Tanh&>(GetGear()); }
	const Tanh& GetTanh() const { return dynamic_cast<const Tanh&>(GetGear()); }
public:
	static Tanh& GetTanh(Value& value) {
		return dynamic_cast<Value_Tanh&>(value).GetTanh();
	}
	static const Tanh& GetTanh(const Value& value) {
		return dynamic_cast<const Value_Tanh&>(value).GetTanh();
	}
	static Tanh* GetEntityPtr(Value& value) { return &GetTanh(value); }
	static const Tanh* GetEntityPtr(const Value& value) { return &GetTanh(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetTanh().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetTanh().IsEqualTo(Value_Tanh::GetTanh(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetTanh().IsLessThan(Value_Tanh::GetTanh(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	virtual bool DoSerialize(Stream& stream) const override;
};

Gurax_EndModuleScope(ml)

#endif
