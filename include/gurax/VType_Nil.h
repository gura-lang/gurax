//==============================================================================
// VType_Nil.h
//==============================================================================
#ifndef GURAX_VTYPE_NIL_H
#define GURAX_VTYPE_NIL_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Nil
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Nil : public VType {
public:
	static const SerialId serialId = 0x00000000;
public:
	VType_Nil() : VType(serialId) {}
	explicit VType_Nil(const Symbol* pSymbol) : VType(serialId) {}
	explicit VType_Nil(const char* name) : VType(name, serialId) {}
	virtual bool IsNil() const override { return true; }
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Nil VTYPE_Nil;

//------------------------------------------------------------------------------
// Value_Nil
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Nil : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Nil);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Nil");
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_Nil(VType& vtype = VTYPE_Nil) : Value_Object(vtype) {}
	// Copy constructor/operator
	Value_Nil(const Value_Nil& src) : Value_Object(src) {}
	Value_Nil& operator=(const Value_Nil& src) = delete;
	// Move constructor/operator
	Value_Nil(Value_Nil&& src) = delete;
	Value_Nil& operator=(Value_Nil&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Value_Nil() = default;
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value& value) const override { return IsSameType(value); }
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)? false : GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	// Virtual functions for runtime process
	//virtual bool CanEvalAsMethod(const Function& function) const override { return true; }
	virtual bool IsValid() const override { return false; }
	virtual bool IsNil() const override { return true; }
	virtual bool GetBool() const override { return false; }
};

}

#endif
