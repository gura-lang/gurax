//==============================================================================
// VType_Function.h
//==============================================================================
#ifndef GURAX_VTYPE_FUNCTION_H
#define GURAX_VTYPE_FUNCTION_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Function
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Function : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Function VTYPE_Function;

//------------------------------------------------------------------------------
// Value_Function
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Function : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Function);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Function");
protected:
	RefPtr<Function> _pFunction;
public:
	static VType& vtype;
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
	static Function& GetFunction(Value& value) {
		return dynamic_cast<Value_Function&>(value).GetFunction();
	}
	static const Function& GetFunction(const Value& value) {
		return dynamic_cast<const Value_Function&>(value).GetFunction();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetFunction().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetFunction().IsEqualTo(dynamic_cast<const Value_Function&>(value).GetFunction());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetFunction().IsLessThan(dynamic_cast<const Value_Function&>(value).GetFunction()) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
public:
	// Virtual functions for runtime process
	virtual HelpHolder* GetHelpHolder() const override { return &_pFunction->GetHelpHolder(); }
	virtual void PresentHelp(Processor& processor, const Symbol* pLangCode) const override;
	virtual bool CanBeCallableMember() const override { return true; }
	virtual const DeclCallable* GetDeclCallable() override;
	virtual void DoCall(Processor& processor, Argument& argument) override;
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
};

}

#endif
