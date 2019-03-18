//==============================================================================
// VType_Argument.h
//==============================================================================
#ifndef GURAX_VTYPE_ARGUMENT_H
#define GURAX_VTYPE_ARGUMENT_H
#include "VType_Object.h"
#include "Argument.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Argument
//------------------------------------------------------------------------------
class VType_Argument : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frame) override;
};

extern VType_Argument VTYPE_Argument;

//------------------------------------------------------------------------------
// Value_Argument
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Argument : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Argument);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Argument");
protected:
	RefPtr<Argument> _pArgument;
public:
	// Constructor
	Value_Argument() = delete;
	Value_Argument(Argument* pArgument, VType& vtype = VTYPE_Argument) :
		Value_Object(vtype), _pArgument(pArgument) {}
	// Copy constructor/operator
	Value_Argument(const Value_Argument& src) :
		Value_Object(src), _pArgument(src._pArgument->Reference()) {}
	Value_Argument& operator=(const Value_Argument& src) = delete;
	// Move constructor/operator
	Value_Argument(Value_Argument&& src) = delete;
	Value_Argument& operator=(Value_Argument&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Argument() = default;
public:
	Argument& GetArgument() { return *_pArgument; }
	const Argument& GetArgument() const { return *_pArgument; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetArgument().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetArgument().IsEqualTo(dynamic_cast<const Value_Argument*>(pValue)->GetArgument());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetArgument().IsLessThan(dynamic_cast<const Value_Argument*>(pValue)->GetArgument()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetArgument().ToString(ss);
	}
};

}

#endif
