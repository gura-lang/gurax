//==============================================================================
// VType_Conv3d.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_CONV3D_H
#define GURAX_MODULE_ML_VTYPE_CONV3D_H
#include <gurax.h>
#include "Conv3d.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_Conv3d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Conv3d : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Conv3d VTYPE_Conv3d;

//------------------------------------------------------------------------------
// Value_Conv3d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Conv3d : public Value_Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Conv3d);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Conv3d");
public:
	static VType& vtype;
public:
	// Constructor
	Value_Conv3d() = delete;
	explicit Value_Conv3d(Conv3d* pConv3d, VType& vtype = VTYPE_Conv3d) : Value_Gear(pConv3d, vtype) {}
	// Copy constructor/operator
	Value_Conv3d(const Value_Conv3d& src) : Value_Gear(src) {}
	Value_Conv3d& operator=(const Value_Conv3d& src) = delete;
	// Move constructor/operator
	Value_Conv3d(Value_Conv3d&& src) noexcept = delete;
	Value_Conv3d& operator=(Value_Conv3d&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Conv3d() = default;
public:
	Conv3d& GetConv3d() { return dynamic_cast<Conv3d&>(GetGear()); }
	const Conv3d& GetConv3d() const { return dynamic_cast<const Conv3d&>(GetGear()); }
public:
	static Conv3d& GetConv3d(Value& value) {
		return dynamic_cast<Value_Conv3d&>(value).GetConv3d();
	}
	static const Conv3d& GetConv3d(const Value& value) {
		return dynamic_cast<const Value_Conv3d&>(value).GetConv3d();
	}
	static Conv3d* GetEntityPtr(Value& value) { return &GetConv3d(value); }
	static const Conv3d* GetEntityPtr(const Value& value) { return &GetConv3d(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetConv3d().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetConv3d().IsEqualTo(Value_Conv3d::GetConv3d(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetConv3d().IsLessThan(Value_Conv3d::GetConv3d(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml)

#endif
