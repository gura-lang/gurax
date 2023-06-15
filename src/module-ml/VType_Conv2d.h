//==============================================================================
// VType_MaxPool2d.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_MAXPOOL2D_H
#define GURAX_MODULE_ML_VTYPE_MAXPOOL2D_H
#include <gurax.h>
#include "MaxPool2d.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_MaxPool2d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_MaxPool2d : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_MaxPool2d VTYPE_MaxPool2d;

//------------------------------------------------------------------------------
// Value_MaxPool2d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_MaxPool2d : public Value_Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_MaxPool2d);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_MaxPool2d");
public:
	static VType& vtype;
public:
	// Constructor
	Value_MaxPool2d() = delete;
	explicit Value_MaxPool2d(MaxPool2d* pMaxPool2d, VType& vtype = VTYPE_MaxPool2d) : Value_Gear(pMaxPool2d, vtype) {}
	// Copy constructor/operator
	Value_MaxPool2d(const Value_MaxPool2d& src) : Value_Gear(src) {}
	Value_MaxPool2d& operator=(const Value_MaxPool2d& src) = delete;
	// Move constructor/operator
	Value_MaxPool2d(Value_MaxPool2d&& src) noexcept = delete;
	Value_MaxPool2d& operator=(Value_MaxPool2d&& src) noexcept = delete;
protected:
	// Destructor
	~Value_MaxPool2d() = default;
public:
	MaxPool2d& GetMaxPool2d() { return dynamic_cast<MaxPool2d&>(GetGear()); }
	const MaxPool2d& GetMaxPool2d() const { return dynamic_cast<const MaxPool2d&>(GetGear()); }
public:
	static MaxPool2d& GetMaxPool2d(Value& value) {
		return dynamic_cast<Value_MaxPool2d&>(value).GetMaxPool2d();
	}
	static const MaxPool2d& GetMaxPool2d(const Value& value) {
		return dynamic_cast<const Value_MaxPool2d&>(value).GetMaxPool2d();
	}
	static MaxPool2d* GetEntityPtr(Value& value) { return &GetMaxPool2d(value); }
	static const MaxPool2d* GetEntityPtr(const Value& value) { return &GetMaxPool2d(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetMaxPool2d().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetMaxPool2d().IsEqualTo(Value_MaxPool2d::GetMaxPool2d(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetMaxPool2d().IsLessThan(Value_MaxPool2d::GetMaxPool2d(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml)

#endif
