//==============================================================================
// VType_Conv1d.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_CONV1D_H
#define GURAX_MODULE_ML_VTYPE_CONV1D_H
#include <gurax.h>
#include "Conv1d.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_Conv1d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Conv1d : public VType {
public:
	static const SerialId serialId = 0x00000100;
public:
	VType_Conv1d() : VType(serialId) {}
	explicit VType_Conv1d(const Symbol* pSymbol) : VType(serialId) {}
	explicit VType_Conv1d(const char* name) : VType(name, serialId) {}
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoDeserialize(Stream& stream) const override;
};

extern GURAX_DLLDECLARE VType_Conv1d VTYPE_Conv1d;

//------------------------------------------------------------------------------
// Value_Conv1d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Conv1d : public Value_Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Conv1d);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Conv1d");
public:
	static VType& vtype;
public:
	// Constructor
	Value_Conv1d() = delete;
	explicit Value_Conv1d(Conv1d* pConv1d, VType& vtype = VTYPE_Conv1d) : Value_Gear(pConv1d, vtype) {}
	// Copy constructor/operator
	Value_Conv1d(const Value_Conv1d& src) : Value_Gear(src) {}
	Value_Conv1d& operator=(const Value_Conv1d& src) = delete;
	// Move constructor/operator
	Value_Conv1d(Value_Conv1d&& src) noexcept = delete;
	Value_Conv1d& operator=(Value_Conv1d&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Conv1d() = default;
public:
	Conv1d& GetConv1d() { return dynamic_cast<Conv1d&>(GetGear()); }
	const Conv1d& GetConv1d() const { return dynamic_cast<const Conv1d&>(GetGear()); }
public:
	static Conv1d& GetConv1d(Value& value) {
		return dynamic_cast<Value_Conv1d&>(value).GetConv1d();
	}
	static const Conv1d& GetConv1d(const Value& value) {
		return dynamic_cast<const Value_Conv1d&>(value).GetConv1d();
	}
	static Conv1d* GetEntityPtr(Value& value) { return &GetConv1d(value); }
	static const Conv1d* GetEntityPtr(const Value& value) { return &GetConv1d(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetConv1d().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetConv1d().IsEqualTo(Value_Conv1d::GetConv1d(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetConv1d().IsLessThan(Value_Conv1d::GetConv1d(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	virtual bool DoSerialize(Stream& stream) const override;
};

Gurax_EndModuleScope(ml)

#endif
