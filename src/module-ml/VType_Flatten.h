//==============================================================================
// VType_Flatten.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_Flatten_H
#define GURAX_MODULE_ML_VTYPE_Flatten_H
#include <gurax.h>
#include "Flatten.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_Flatten
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Flatten : public VType {
public:
	static const SerialId serialId = 0x00000109;
public:
	VType_Flatten() : VType(serialId) {}
	explicit VType_Flatten(const Symbol* pSymbol) : VType(serialId) {}
	explicit VType_Flatten(const char* name) : VType(name, serialId) {}
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoDeserialize(Stream& stream) const override;
};

extern GURAX_DLLDECLARE VType_Flatten VTYPE_Flatten;

//------------------------------------------------------------------------------
// Value_Flatten
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Flatten : public Value_Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Flatten);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Flatten");
public:
	static VType& vtype;
public:
	// Constructor
	Value_Flatten() = delete;
	explicit Value_Flatten(Flatten* pFlatten, VType& vtype = VTYPE_Flatten) : Value_Gear(pFlatten, vtype) {}
	// Copy constructor/operator
	Value_Flatten(const Value_Flatten& src) : Value_Gear(src) {}
	Value_Flatten& operator=(const Value_Flatten& src) = delete;
	// Move constructor/operator
	Value_Flatten(Value_Flatten&& src) noexcept = delete;
	Value_Flatten& operator=(Value_Flatten&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Flatten() = default;
public:
	Flatten& GetFlatten() { return dynamic_cast<Flatten&>(GetGear()); }
	const Flatten& GetFlatten() const { return dynamic_cast<const Flatten&>(GetGear()); }
public:
	static Flatten& GetFlatten(Value& value) {
		return dynamic_cast<Value_Flatten&>(value).GetFlatten();
	}
	static const Flatten& GetFlatten(const Value& value) {
		return dynamic_cast<const Value_Flatten&>(value).GetFlatten();
	}
	static Flatten* GetEntityPtr(Value& value) { return &GetFlatten(value); }
	static const Flatten* GetEntityPtr(const Value& value) { return &GetFlatten(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetFlatten().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetFlatten().IsEqualTo(Value_Flatten::GetFlatten(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetFlatten().IsLessThan(Value_Flatten::GetFlatten(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	virtual bool DoSerialize(Stream& stream) const override;
};

Gurax_EndModuleScope(ml)

#endif
