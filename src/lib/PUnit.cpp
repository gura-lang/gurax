//==============================================================================
// PUnit.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PUnit
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit {
protected:
	const PUnit* _pPUnitNext;
	static PUnit* _pPUnitCont;
public:
	// Constructor
	PUnit() : _pPUnitNext(nullptr) {
		if (_pPUnitCont) _pPUnitCont->SetPUnitNext(this);
		_pPUnitCont = this;
	}
	// Copy constructor/operator
	PUnit(const PUnit& src) = delete;
	PUnit& operator=(const PUnit& src) = delete;
	// Move constructor/operator
	PUnit(PUnit&& src) = delete;
	PUnit& operator=(PUnit&& src) noexcept = delete;
	// Destructor
	virtual ~PUnit() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const PUnit* pPUnit) const { return this == pPUnit; }
	bool IsEqualTo(const PUnit* pPUnit) const { return IsIdentical(pPUnit); }
	bool IsLessThan(const PUnit* pPUnit) const { return this < pPUnit; }
	String ToString() const { return ToString(StringStyle::Empty); }
public:
	static void PutTerminator() { _pPUnitCont = nullptr; }
	void SetPUnitNext(const PUnit* pPUnit) { _pPUnitNext = pPUnit; }
	const PUnit* GetPUnitNext() const { return _pPUnitNext; }
public:
	// Virtual functions
	virtual void Exec() const = 0;
	virtual String ToString(const StringStyle& ss) const = 0;
};

//------------------------------------------------------------------------------
// PUnitList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnitList : public std::vector<const PUnit*> {
};

//------------------------------------------------------------------------------
// PUnitStack
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnitStack : public PUnitList {
public:
	const PUnit* Peek(int offset) { return *(rbegin() + offset); }
	void Push(const PUnit* pPUnit) { push_back(pPUnit); }
	const PUnit* Pop() { const PUnit* pPUnit = back(); pop_back(); return pPUnit; }
};

//------------------------------------------------------------------------------
// PUnit_EraseStack
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_EraseStack : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("EraseStack");
public:
	// Constructor
	PUnit_EraseStack() {}
public:
	// Virtual functions of PUnit
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_CreateList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_CreateList : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("CreateList");
private:
	size_t _sizeReserve;
public:
	// Constructor
	PUnit_CreateList(size_t sizeReserve = 0) : _sizeReserve(sizeReserve) {}
public:
	size_t GetSizeReserve() const { return _sizeReserve; }
public:
	// Virtual functions of PUnit
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_AddValueToList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_AddValueToList : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("AddValueToList");
public:
	// Constructor
	PUnit_AddValueToList() {}
public:
	// Virtual functions of PUnit
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_LookupValue
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_LookupValue : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("LookupValue");
private:
	const Symbol* _pSymbol;
public:
	// Constructor
	PUnit_LookupValue(const Symbol* pSymbol) : _pSymbol(pSymbol) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	// Virtual functions of PUnit
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_AssignValue
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_AssignValue : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("AssignValue");
private:
	const Symbol* _pSymbol;
public:
	// Constructor
	PUnit_AssignValue(const Symbol* pSymbol) : _pSymbol(pSymbol) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	// Virtual functions of PUnit
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_UnaryOp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_UnaryOp : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("UnaryOp");
private:
	const Operator* _pOperator;
public:
	// Constructor
	PUnit_UnaryOp(const Operator* pOperator) : _pOperator(pOperator) {}
public:
	const Operator* GetOperator() const { return _pOperator; }
public:
	// Virtual functions of PUnit
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_BinaryOp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_BinaryOp : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("BinaryOp");
private:
	const Operator* _pOperator;
public:
	// Constructor
	PUnit_BinaryOp(const Operator* pOperator) : _pOperator(pOperator) {}
public:
	const Operator* GetOperator() const { return _pOperator; }
public:
	// Virtual functions of PUnit
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_CreateArgumentForCall
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_CreateArgumentForCall : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("CreateArgumentForCall");
private:
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_CreateArgumentForCall(Attribute* pAttr) : _pAttr(pAttr) {}
public:
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_Call
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Call : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("Call");
public:
	// Constructor
	PUnit_Call() {}
public:
	// Virtual functions of PUnit
	virtual void Exec() const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit
//------------------------------------------------------------------------------
PUnit* PUnit::_pPUnitCont = nullptr;

//------------------------------------------------------------------------------
// PUnitList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PUnit_CreateList
//------------------------------------------------------------------------------
void PUnit_CreateList::Exec() const
{
	RefPtr<ValueTypedOwner> pValueTypedOwner(new ValueTypedOwner());
	pValueTypedOwner->Reserve(GetSizeReserve());
	Context::PushStack(new Value_List(pValueTypedOwner.release()));
}

String PUnit_CreateList::ToString(const StringStyle& ss) const
{
	String rtn;
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_AddValueToList
//------------------------------------------------------------------------------
void PUnit_AddValueToList::Exec() const
{
	RefPtr<Value> pValue(Context::PopStack());
	ValueTypedOwner& valueTypedOwner =
		dynamic_cast<Value_List*>(Context::PeekStack(0))->GetValueTypedOwner();
	valueTypedOwner.Add(pValue.release());
}

String PUnit_AddValueToList::ToString(const StringStyle& ss) const
{
	String rtn;
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_EraseStack
//------------------------------------------------------------------------------
void PUnit_EraseStack::Exec() const
{
	Value::Delete(Context::PopStack());
}

String PUnit_EraseStack::ToString(const StringStyle& ss) const
{
	String rtn;
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_LookupValue
//------------------------------------------------------------------------------
void PUnit_LookupValue::Exec() const
{
	const Value* pValue = Context::GetFrame().LookupValue(GetSymbol());
	if (!pValue) {
		Error::Issue(ErrorType::ValueError, "symbol not found: %s", GetSymbol()->GetName());
		return;
	}
	Context::PushStack(pValue->Reference());
}

String PUnit_LookupValue::ToString(const StringStyle& ss) const
{
	String rtn;
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_AssignValue
//------------------------------------------------------------------------------
void PUnit_AssignValue::Exec() const
{
	RefPtr<Value> pValueAssigned(Context::PeekStack(0)->Reference());
	Context::GetFrame().AssignValue(GetSymbol(), pValueAssigned.release());
}

String PUnit_AssignValue::ToString(const StringStyle& ss) const
{
	String rtn;
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_UnaryOp
//------------------------------------------------------------------------------
void PUnit_UnaryOp::Exec() const
{
	RefPtr<Value> pValueChild(Context::PopStack());
	RefPtr<Value> pValue(GetOperator()->EvalUnary(pValueChild.release()));
	if (!pValue) return;
	Context::PushStack(pValue.release());
}

String PUnit_UnaryOp::ToString(const StringStyle& ss) const
{
	String rtn;
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_BinaryOp
//------------------------------------------------------------------------------
void PUnit_BinaryOp::Exec() const
{
	RefPtr<Value> pValueRight(Context::PopStack());
	RefPtr<Value> pValueLeft(Context::PopStack());
	RefPtr<Value> pValue(GetOperator()->EvalBinary(pValueLeft.release(), pValueRight.release()));
	if (!pValue) return;
	Context::PushStack(pValue.release());
}

String PUnit_BinaryOp::ToString(const StringStyle& ss) const
{
	String rtn;
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_CreateArgumentForCall
//------------------------------------------------------------------------------
void PUnit_CreateArgumentForCall::Exec() const
{
	RefPtr<Value> pValueCar(Context::PopStack());
	const DeclCaller* pDeclCaller = pValueCar->GetDeclCaller();
	if (!pDeclCaller) {
		Error::Issue(ErrorType::ValueError,
					 "value type %s can not be called", pValueCar->GetVType().MakeFullName().c_str());
		return;
	}
	if (!pDeclCaller->CheckAttribute(GetAttr())) return;
	RefPtr<Argument> pArgument(
		new Argument(pDeclCaller->Reference(), GetAttr().Reference(), Value::nil(), pValueCar.release()));
	Context::PushStack(new Value_Argument(pArgument.release()));
}

String PUnit_CreateArgumentForCall::ToString(const StringStyle& ss) const
{
	String rtn;
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Call
//------------------------------------------------------------------------------
void PUnit_Call::Exec() const
{
	RefPtr<Value_Argument> pValue(dynamic_cast<Value_Argument*>(Context::PopStack()));
	Argument& argument = pValue->GetArgument();
	if (!argument.CheckValidity()) return;
	argument.Call(Context::GetFrame());
}

String PUnit_Call::ToString(const StringStyle& ss) const
{
	String rtn;
	return rtn;
}

}
