//==============================================================================
// VType_ArgSlot.h
//==============================================================================
#ifndef GURAX_VTYPE_ARGSLOT_H
#define GURAX_VTYPE_ARGSLOT_H
#include "VType_Object.h"
#include "ArgSlot.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_ArgSlot
//------------------------------------------------------------------------------
class VType_ArgSlot : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frame) override;
};

extern VType_ArgSlot VTYPE_ArgSlot;

//------------------------------------------------------------------------------
// Value_ArgSlot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_ArgSlot : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_ArgSlot);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_ArgSlot");
private:
	RefPtr<ArgSlot> _pArgSlot;
public:
	// Constructor
	Value_ArgSlot() = delete;
	Value_ArgSlot(ArgSlot* pArgSlot, VType& vtype = VTYPE_ArgSlot) :
		Value_Object(vtype), _pArgSlot(pArgSlot) {}
	// Copy constructor/operator
	Value_ArgSlot(const Value_ArgSlot& src) :
		Value_Object(src), _pArgSlot(src._pArgSlot->Reference()) {}
	Value_ArgSlot& operator=(const Value_ArgSlot& src) = delete;
	// Move constructor/operator
	Value_ArgSlot(Value_ArgSlot&& src) = delete;
	Value_ArgSlot& operator=(Value_ArgSlot&& src) noexcept = delete;
protected:
	// Destructor
	~Value_ArgSlot() = default;
public:
	ArgSlot& GetArgSlot() { return *_pArgSlot; }
	const ArgSlot& GetArgSlot() const { return *_pArgSlot; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetArgSlot().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetArgSlot().IsEqualTo(dynamic_cast<const Value_ArgSlot*>(pValue)->GetArgSlot());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetArgSlot().IsLessThan(dynamic_cast<const Value_ArgSlot*>(pValue)->GetArgSlot()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetArgSlot().ToString(ss);
	}
};

}

#endif
