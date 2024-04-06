//==============================================================================
// VType_Gear.h
//==============================================================================
#ifndef GURAX_VTYPE_GEAR_H
#define GURAX_VTYPE_GEAR_H
#include "VType_Object.h"
#include "Gear.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Gear
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Gear : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Gear VTYPE_Gear;

//------------------------------------------------------------------------------
// Value_Gear
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Gear : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Gear);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Gear");
protected:
	RefPtr<Gear> _pGear;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Gear() = delete;
	explicit Value_Gear(Gear* pGear, VType& vtype = VTYPE_Gear) :
		Value_Object(vtype), _pGear(pGear) {}
	// Copy constructor/operator
	Value_Gear(const Value_Gear& src) :
		Value_Object(src), _pGear(src._pGear->Reference()) {}
	Value_Gear& operator=(const Value_Gear& src) = delete;
	// Move constructor/operator
	Value_Gear(Value_Gear&& src) noexcept = delete;
	Value_Gear& operator=(Value_Gear&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Gear() = default;
public:
	Gear& GetGear() { return *_pGear; }
	const Gear& GetGear() const { return *_pGear; }
public:
	static Gear& GetGear(Value& value) {
		return dynamic_cast<Value_Gear&>(value).GetGear();
	}
	static const Gear& GetGear(const Value& value) {
		return dynamic_cast<const Value_Gear&>(value).GetGear();
	}
	static Gear* GetEntityPtr(Value& value) { return &GetGear(value); }
	static const Gear* GetEntityPtr(const Value& value) { return &GetGear(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetGear().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetGear().IsEqualTo(Value_Gear::GetGear(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetGear().IsLessThan(Value_Gear::GetGear(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
