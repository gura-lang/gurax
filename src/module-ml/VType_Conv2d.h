//==============================================================================
// VType_Conv2d.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_CONV2D_H
#define GURAX_MODULE_ML_VTYPE_CONV2D_H
#include <gurax.h>
#include "Conv2d.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_Conv2d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Conv2d : public VType {
public:
	static const SerialId serialId = 0x00000100;
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Conv2d VTYPE_Conv2d;

//------------------------------------------------------------------------------
// Value_Conv2d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Conv2d : public Value_Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Conv2d);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Conv2d");
public:
	static VType& vtype;
public:
	// Constructor
	Value_Conv2d() = delete;
	explicit Value_Conv2d(Conv2d* pConv2d, VType& vtype = VTYPE_Conv2d) : Value_Gear(pConv2d, vtype) {}
	// Copy constructor/operator
	Value_Conv2d(const Value_Conv2d& src) : Value_Gear(src) {}
	Value_Conv2d& operator=(const Value_Conv2d& src) = delete;
	// Move constructor/operator
	Value_Conv2d(Value_Conv2d&& src) noexcept = delete;
	Value_Conv2d& operator=(Value_Conv2d&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Conv2d() = default;
public:
	Conv2d& GetConv2d() { return dynamic_cast<Conv2d&>(GetGear()); }
	const Conv2d& GetConv2d() const { return dynamic_cast<const Conv2d&>(GetGear()); }
public:
	static Conv2d& GetConv2d(Value& value) {
		return dynamic_cast<Value_Conv2d&>(value).GetConv2d();
	}
	static const Conv2d& GetConv2d(const Value& value) {
		return dynamic_cast<const Value_Conv2d&>(value).GetConv2d();
	}
	static Conv2d* GetEntityPtr(Value& value) { return &GetConv2d(value); }
	static const Conv2d* GetEntityPtr(const Value& value) { return &GetConv2d(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetConv2d().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetConv2d().IsEqualTo(Value_Conv2d::GetConv2d(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetConv2d().IsLessThan(Value_Conv2d::GetConv2d(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml)

#endif
