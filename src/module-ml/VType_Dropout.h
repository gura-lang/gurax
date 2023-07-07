//==============================================================================
// VType_Dropout.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_DROPOUT_H
#define GURAX_MODULE_ML_VTYPE_DROPOUT_H
#include <gurax.h>
#include "Dropout.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_Dropout
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Dropout : public VType {
public:
	static const SerialId serialId = 0x00000106;
public:
	VType_Dropout() : VType(serialId) {}
	explicit VType_Dropout(const Symbol* pSymbol) : VType(serialId) {}
	explicit VType_Dropout(const char* name) : VType(name, serialId) {}
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoDeserialize(Stream& stream) const override;
};

extern GURAX_DLLDECLARE VType_Dropout VTYPE_Dropout;

//------------------------------------------------------------------------------
// Value_Dropout
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Dropout : public Value_Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Dropout);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Dropout");
public:
	static VType& vtype;
public:
	// Constructor
	Value_Dropout() = delete;
	explicit Value_Dropout(Dropout* pDropout, VType& vtype = VTYPE_Dropout) : Value_Gear(pDropout, vtype) {}
	// Copy constructor/operator
	Value_Dropout(const Value_Dropout& src) : Value_Gear(src) {}
	Value_Dropout& operator=(const Value_Dropout& src) = delete;
	// Move constructor/operator
	Value_Dropout(Value_Dropout&& src) noexcept = delete;
	Value_Dropout& operator=(Value_Dropout&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Dropout() = default;
public:
	Dropout& GetDropout() { return dynamic_cast<Dropout&>(GetGear()); }
	const Dropout& GetDropout() const { return dynamic_cast<const Dropout&>(GetGear()); }
public:
	static Dropout& GetDropout(Value& value) {
		return dynamic_cast<Value_Dropout&>(value).GetDropout();
	}
	static const Dropout& GetDropout(const Value& value) {
		return dynamic_cast<const Value_Dropout&>(value).GetDropout();
	}
	static Dropout* GetEntityPtr(Value& value) { return &GetDropout(value); }
	static const Dropout* GetEntityPtr(const Value& value) { return &GetDropout(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetDropout().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetDropout().IsEqualTo(Value_Dropout::GetDropout(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetDropout().IsLessThan(Value_Dropout::GetDropout(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	virtual bool DoSerialize(Stream& stream) const override;
};

Gurax_EndModuleScope(ml)

#endif
