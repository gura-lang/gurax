//==============================================================================
// VType_MaxPool1d.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_MAXPOOL1D_H
#define GURAX_MODULE_ML_VTYPE_MAXPOOL1D_H
#include <gurax.h>
#include "MaxPool1d.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_MaxPool1d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_MaxPool1d : public VType {
public:
	static const SerialId serialId = 0x00000106;
public:
	VType_MaxPool1d() : VType(serialId) {}
	explicit VType_MaxPool1d(const Symbol* pSymbol) : VType(serialId) {}
	explicit VType_MaxPool1d(const char* name) : VType(name, serialId) {}
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoDeserialize(Stream& stream) const override;
};

extern GURAX_DLLDECLARE VType_MaxPool1d VTYPE_MaxPool1d;

//------------------------------------------------------------------------------
// Value_MaxPool1d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_MaxPool1d : public Value_Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_MaxPool1d);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_MaxPool1d");
public:
	static VType& vtype;
public:
	// Constructor
	Value_MaxPool1d() = delete;
	explicit Value_MaxPool1d(MaxPool1d* pMaxPool1d, VType& vtype = VTYPE_MaxPool1d) : Value_Gear(pMaxPool1d, vtype) {}
	// Copy constructor/operator
	Value_MaxPool1d(const Value_MaxPool1d& src) : Value_Gear(src) {}
	Value_MaxPool1d& operator=(const Value_MaxPool1d& src) = delete;
	// Move constructor/operator
	Value_MaxPool1d(Value_MaxPool1d&& src) noexcept = delete;
	Value_MaxPool1d& operator=(Value_MaxPool1d&& src) noexcept = delete;
protected:
	// Destructor
	~Value_MaxPool1d() = default;
public:
	MaxPool1d& GetMaxPool1d() { return dynamic_cast<MaxPool1d&>(GetGear()); }
	const MaxPool1d& GetMaxPool1d() const { return dynamic_cast<const MaxPool1d&>(GetGear()); }
public:
	static MaxPool1d& GetMaxPool1d(Value& value) {
		return dynamic_cast<Value_MaxPool1d&>(value).GetMaxPool1d();
	}
	static const MaxPool1d& GetMaxPool1d(const Value& value) {
		return dynamic_cast<const Value_MaxPool1d&>(value).GetMaxPool1d();
	}
	static MaxPool1d* GetEntityPtr(Value& value) { return &GetMaxPool1d(value); }
	static const MaxPool1d* GetEntityPtr(const Value& value) { return &GetMaxPool1d(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetMaxPool1d().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetMaxPool1d().IsEqualTo(Value_MaxPool1d::GetMaxPool1d(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetMaxPool1d().IsLessThan(Value_MaxPool1d::GetMaxPool1d(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	virtual bool DoSerialize(Stream& stream) const override;
};

Gurax_EndModuleScope(ml)

#endif
