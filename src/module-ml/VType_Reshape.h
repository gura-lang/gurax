//==============================================================================
// VType_Reshape.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_RESHAPE_H
#define GURAX_MODULE_ML_VTYPE_RESHAPE_H
#include <gurax.h>
#include "Reshape.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_Reshape
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Reshape : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Reshape VTYPE_Reshape;

//------------------------------------------------------------------------------
// Value_Reshape
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Reshape : public Value_Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Reshape);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Reshape");
public:
	static VType& vtype;
public:
	// Constructor
	Value_Reshape() = delete;
	explicit Value_Reshape(Reshape* pReshape, VType& vtype = VTYPE_Reshape) : Value_Gear(pReshape, vtype) {}
	// Copy constructor/operator
	Value_Reshape(const Value_Reshape& src) : Value_Gear(src) {}
	Value_Reshape& operator=(const Value_Reshape& src) = delete;
	// Move constructor/operator
	Value_Reshape(Value_Reshape&& src) noexcept = delete;
	Value_Reshape& operator=(Value_Reshape&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Reshape() = default;
public:
	Reshape& GetReshape() { return dynamic_cast<Reshape&>(GetGear()); }
	const Reshape& GetReshape() const { return dynamic_cast<const Reshape&>(GetGear()); }
public:
	static Reshape& GetReshape(Value& value) {
		return dynamic_cast<Value_Reshape&>(value).GetReshape();
	}
	static const Reshape& GetReshape(const Value& value) {
		return dynamic_cast<const Value_Reshape&>(value).GetReshape();
	}
	static Reshape* GetEntityPtr(Value& value) { return &GetReshape(value); }
	static const Reshape* GetEntityPtr(const Value& value) { return &GetReshape(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetReshape().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetReshape().IsEqualTo(Value_Reshape::GetReshape(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetReshape().IsLessThan(Value_Reshape::GetReshape(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml)

#endif
