//==============================================================================
// VType_MaxPool3d.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_MAXPOOL3D_H
#define GURAX_MODULE_ML_VTYPE_MAXPOOL3D_H
#include <gurax.h>
#include "MaxPool3d.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_MaxPool3d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_MaxPool3d : public VType {
public:
	static const SerialId serialId = 0x00000100;
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_MaxPool3d VTYPE_MaxPool3d;

//------------------------------------------------------------------------------
// Value_MaxPool3d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_MaxPool3d : public Value_Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_MaxPool3d);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_MaxPool3d");
public:
	static VType& vtype;
public:
	// Constructor
	Value_MaxPool3d() = delete;
	explicit Value_MaxPool3d(MaxPool3d* pMaxPool3d, VType& vtype = VTYPE_MaxPool3d) : Value_Gear(pMaxPool3d, vtype) {}
	// Copy constructor/operator
	Value_MaxPool3d(const Value_MaxPool3d& src) : Value_Gear(src) {}
	Value_MaxPool3d& operator=(const Value_MaxPool3d& src) = delete;
	// Move constructor/operator
	Value_MaxPool3d(Value_MaxPool3d&& src) noexcept = delete;
	Value_MaxPool3d& operator=(Value_MaxPool3d&& src) noexcept = delete;
protected:
	// Destructor
	~Value_MaxPool3d() = default;
public:
	MaxPool3d& GetMaxPool3d() { return dynamic_cast<MaxPool3d&>(GetGear()); }
	const MaxPool3d& GetMaxPool3d() const { return dynamic_cast<const MaxPool3d&>(GetGear()); }
public:
	static MaxPool3d& GetMaxPool3d(Value& value) {
		return dynamic_cast<Value_MaxPool3d&>(value).GetMaxPool3d();
	}
	static const MaxPool3d& GetMaxPool3d(const Value& value) {
		return dynamic_cast<const Value_MaxPool3d&>(value).GetMaxPool3d();
	}
	static MaxPool3d* GetEntityPtr(Value& value) { return &GetMaxPool3d(value); }
	static const MaxPool3d* GetEntityPtr(const Value& value) { return &GetMaxPool3d(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetMaxPool3d().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetMaxPool3d().IsEqualTo(Value_MaxPool3d::GetMaxPool3d(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetMaxPool3d().IsLessThan(Value_MaxPool3d::GetMaxPool3d(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml)

#endif
