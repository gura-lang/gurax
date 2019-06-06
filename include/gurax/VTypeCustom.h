//==============================================================================
// VTypeCustom.h
//==============================================================================
#ifndef GURAX_VTYPECUSTOM_H
#define GURAX_VTYPECUSTOM_H
#include "Value.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VTypeCustom
//------------------------------------------------------------------------------
class VTypeCustom : public VType {
private:
	size_t _nProps;
public:
	VTypeCustom(const char* name) : VType(name), _nProps(0) {}
public:
	size_t AddProp() { return _nProps++; }
	size_t CountProps() const { return _nProps; }
public:
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value) const override;
};

extern VTypeCustom VTYPECustom;

//------------------------------------------------------------------------------
// ValueCustom
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueCustom : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(ValueCustom);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ValueCustom");
protected:
	RefPtr<ValueOwner> _pValuesProp;
public:
	// Constructor
	explicit ValueCustom(VType& vtype, size_t nProps) :
		Value_Object(vtype), _pValuesProp(new ValueOwner(nProps, Value::nil(nProps))) {}
	// Copy constructor/operator
	ValueCustom(const ValueCustom& src) = delete;
	ValueCustom& operator=(const ValueCustom& src) = delete;
	// Move constructor/operator
	ValueCustom(ValueCustom&& src) = delete;
	ValueCustom& operator=(ValueCustom&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~ValueCustom() = default;
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value* pValue) const override { return IsSameType(pValue); }
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)? false : GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return "custom";
	}
};

}

#endif
