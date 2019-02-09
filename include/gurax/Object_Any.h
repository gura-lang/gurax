//==============================================================================
// Value_Any.h
//==============================================================================
#ifndef GURAX_OBJECT_ANY_H
#define GURAX_OBJECT_ANY_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Any
//------------------------------------------------------------------------------
class VType_Any : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VType_Any VTYPE_Any;

//------------------------------------------------------------------------------
// Value_Any
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Any : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Any);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Any");
public:
	// Constructor
	Value_Any() : Object(VTYPE_Any) {}
	// Copy constructor/operator
	Value_Any(const Value_Any& src) = delete;
	Value_Any& operator=(const Value_Any& src) = delete;
	// Move constructor/operator
	Value_Any(Value_Any&& src) = delete;
	Value_Any& operator=(Value_Any&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Value_Any() = default;
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Object* pValue) const override { return IsSameType(pValue); }
	virtual bool IsLessThan(const Object* pValue) const override {
		return IsSameType(pValue)? false : GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return "any";
	}
};

}

#endif
