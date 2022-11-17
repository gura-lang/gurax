//==============================================================================
// VType_Operator.h
//==============================================================================
#ifndef GURAX_VTYPE_OPERATOR_H
#define GURAX_VTYPE_OPERATOR_H
#include "VType_Object.h"
#include "Operator.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Operator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Operator : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Operator VTYPE_Operator;

//------------------------------------------------------------------------------
// Value_Operator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Operator : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Operator);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Operator");
protected:
	Operator* _pOperator;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Operator() = delete;
	explicit Value_Operator(Operator* pOperator, VType& vtype = VTYPE_Operator) :
		Value_Object(vtype), _pOperator(pOperator) {}
	// Copy constructor/operator
	Value_Operator(const Value_Operator& src) :
		Value_Object(src), _pOperator(src._pOperator) {}
	Value_Operator& operator=(const Value_Operator& src) = delete;
	// Move constructor/operator
	Value_Operator(Value_Operator&& src) noexcept = delete;
	Value_Operator& operator=(Value_Operator&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Operator() = default;
public:
	Operator& GetOperator() { return *_pOperator; }
	Operator& GetOperator() const { return *_pOperator; }
public:
	static Operator& GetOperator(Value& value) {
		return dynamic_cast<Value_Operator&>(value).GetOperator();
	}
	static Operator& GetOperator(const Value& value) {
		return dynamic_cast<const Value_Operator&>(value).GetOperator();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(&GetOperator());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			&GetOperator() == &Value_Operator::GetOperator(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			&GetOperator() < &Value_Operator::GetOperator(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
public:
	virtual const DeclCallable* GetDeclCallable() override;
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
};

}

#endif
