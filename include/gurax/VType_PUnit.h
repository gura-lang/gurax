//==============================================================================
// VType_PUnit.h
//==============================================================================
#ifndef GURAX_VTYPE_PUNIT_H
#define GURAX_VTYPE_PUNIT_H
#include "VType_Object.h"
#include "PUnit.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_PUnit
//------------------------------------------------------------------------------
class VType_PUnit : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frame) override;
};

extern VType_PUnit VTYPE_PUnit;

//------------------------------------------------------------------------------
// Value_PUnit
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_PUnit : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_PUnit);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_PUnit");
protected:
	const PUnit* _pPUnit;
public:
	// Constructor
	Value_PUnit() = delete;
	Value_PUnit(const PUnit* pPUnit, VType& vtype = VTYPE_PUnit) :
		Value_Object(vtype), _pPUnit(pPUnit) {}
	// Copy constructor/operator
	Value_PUnit(const Value_PUnit& src) :
		Value_Object(src), _pPUnit(src._pPUnit) {}
	Value_PUnit& operator=(const Value_PUnit& src) = delete;
	// Move constructor/operator
	Value_PUnit(Value_PUnit&& src) = delete;
	Value_PUnit& operator=(Value_PUnit&& src) noexcept = delete;
protected:
	// Destructor
	~Value_PUnit() = default;
public:
	const PUnit* GetPUnit() const { return _pPUnit; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetPUnit()->CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetPUnit()->IsEqualTo(dynamic_cast<const Value_PUnit*>(pValue)->GetPUnit());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetPUnit()->IsLessThan(dynamic_cast<const Value_PUnit*>(pValue)->GetPUnit()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetPUnit()->ToString(ss);
	}
};

}

#endif
