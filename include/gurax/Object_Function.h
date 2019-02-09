//==============================================================================
// Value_Function.h
//==============================================================================
#ifndef GURAX_OBJECT_FUNCTION_H
#define GURAX_OBJECT_FUNCTION_H
#include "Value_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Function
//------------------------------------------------------------------------------
class VType_Function : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VType_Function VTYPE_Function;

//------------------------------------------------------------------------------
// Value_Function
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Function : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Function);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Function");
private:
	RefPtr<Function> _pFunction;
public:
	// Constructor
	Value_Function() = delete;
	explicit Value_Function(Function* pFunction, VType& vtype = VTYPE_Function) :
		Value_Object(vtype), _pFunction(pFunction) {}
	// Copy constructor/operator
	Value_Function(const Value_Function& src) :
		Value_Object(src), _pFunction(src._pFunction->Reference()) {}
	Value_Function& operator=(const Value_Function& src) = delete;
	// Move constructor/operator
	Value_Function(Value_Function&& src) = delete;
	Value_Function& operator=(Value_Function&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Function() = default;
public:
	Function& GetFunction() { return *_pFunction; }
	const Function& GetFunction() const { return *_pFunction; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetFunction().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pValue) const override {
		return IsSameType(pValue) &&
			GetFunction().IsEqualTo(dynamic_cast<const Value_Function*>(pValue)->GetFunction());
	}
	virtual bool IsLessThan(const Object* pValue) const override {
		return IsSameType(pValue)?
			GetFunction().IsLessThan(dynamic_cast<const Value_Function*>(pValue)->GetFunction()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetFunction().ToString(ss);
	}
};

}

#endif
