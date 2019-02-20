//==============================================================================
// PUnit.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

class Processor;

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
	virtual void Exec(Processor& processor) const = 0;
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
	virtual void Exec(Processor& processor) const override;
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
	virtual void Exec(Processor& processor) const override;
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
	virtual void Exec(Processor& processor) const override;
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
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_LookupPropValue
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_LookupPropValue : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("LookupPropValue");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_LookupPropValue(const Symbol* pSymbol, Attribute* pAttr) :
		_pSymbol(pSymbol), _pAttr(pAttr) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
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
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_AssignPropValue
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_AssignPropValue : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("AssignPropValue");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_AssignPropValue(const Symbol* pSymbol, Attribute* pAttr) : _pSymbol(pSymbol), _pAttr(pAttr) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_Member
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Member : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("Member");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_Member(const Symbol* pSymbol, Attribute* pAttr) : _pSymbol(pSymbol), _pAttr(pAttr) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
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
	virtual void Exec(Processor& processor) const override;
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
	virtual void Exec(Processor& processor) const override;
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
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_CreateArgumentForIndex
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_CreateArgumentForIndex : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("CreateArgumentForIndex");
private:
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_CreateArgumentForIndex(Attribute* pAttr) : _pAttr(pAttr) {}
public:
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
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
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_IndexAccess
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_IndexAccess : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("IndexAccess");
public:
	// Constructor
	PUnit_IndexAccess() {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_PrepareArgument
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_PrepareArgument : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("PrepareArgument");
private:
	RefPtr<Expr> _pExpr;
public:
	// Constructor
	explicit PUnit_PrepareArgument(Expr* pExpr) : _pExpr(pExpr) {}
public:
	const Expr* GetExpr() const { return _pExpr.get(); }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_FeedArgument
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_FeedArgument : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("FeedArgument");
public:
	// Constructor
	PUnit_FeedArgument() {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_PrepareNamedArgument
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_PrepareNamedArgument : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("PrepareNamedArgument");
private:
	const Symbol* _pSymbol;
	RefPtr<Expr> _pExpr;
public:
	// Constructor
	explicit PUnit_PrepareNamedArgument(const Symbol* pSymbol, Expr* pExpr) :
		_pSymbol(pSymbol), _pExpr(pExpr) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Expr* GetExpr() const { return _pExpr.get(); }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_FeedNamedArgument
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_FeedNamedArgument : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("FeedNamedArgument");
public:
	// Constructor
	PUnit_FeedNamedArgument() {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Processor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Processor {
private:
	const PUnit* _pPUnitCur;
	RefPtr<ValueStack> _pValueStack;
	RefPtr<Frame> _pFrame;
public:
	// Constructor
	Processor();
	// Copy constructor/operator
	Processor(const Processor& src) = delete;
	Processor& operator=(const Processor& src) = delete;
	// Move constructor/operator
	Processor(Processor&& src) = delete;
	Processor& operator=(Processor&& src) noexcept = delete;
	// Destructor
	virtual ~Processor() = default;
public:
	ValueStack& GetValueStack() { return *_pValueStack; }
	void PushStack(Value* pValue) { GetValueStack().Push(pValue); }
	Value* PopStack() { return GetValueStack().Pop(); }
	Value* PeekStack(size_t offset) { return GetValueStack().Peek(offset); }
	Frame& GetFrame() { return *_pFrame; }
	void Goto(const PUnit* pPUnit) { _pPUnitCur = pPUnit; }
	void Run(const PUnit* pPUnit);
};

//------------------------------------------------------------------------------
// Processor
//------------------------------------------------------------------------------
Processor::Processor() :
	_pPUnitCur(nullptr), _pValueStack(new ValueStack()), _pFrame(Context::GetFrame().Reference())
{
}

void Processor::Run(const PUnit* pPUnit)
{
	while (pPUnit) {
		_pPUnitCur = nullptr;
		pPUnit->Exec(*this);
		pPUnit = _pPUnitCur;
	}
}

//------------------------------------------------------------------------------
// PUnit
//------------------------------------------------------------------------------
PUnit* PUnit::_pPUnitCont = nullptr;

//------------------------------------------------------------------------------
// PUnitList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PUnit_CreateList
// [] -> [ValueList]
//------------------------------------------------------------------------------
void PUnit_CreateList::Exec(Processor& processor) const
{
	RefPtr<ValueTypedOwner> pValueTypedOwner(new ValueTypedOwner());
	pValueTypedOwner->Reserve(GetSizeReserve());
	processor.PushStack(new Value_List(pValueTypedOwner.release()));
	processor.Goto(GetPUnitNext());
}

String PUnit_CreateList::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "CreateList()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_AddValueToList
// [ValueList ValueElem] -> [ValueList]
//------------------------------------------------------------------------------
void PUnit_AddValueToList::Exec(Processor& processor) const
{
	RefPtr<Value> pValueElem(processor.PopStack());
	ValueTypedOwner& valueTypedOwner =
		dynamic_cast<Value_List*>(processor.PeekStack(0))->GetValueTypedOwner();
	valueTypedOwner.Add(pValueElem.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_AddValueToList::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "AddValueList()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_EraseStack
// [any] -> []
//------------------------------------------------------------------------------
void PUnit_EraseStack::Exec(Processor& processor) const
{
	Value::Delete(processor.PopStack());
	processor.Goto(GetPUnitNext());
}

String PUnit_EraseStack::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "EraseStack()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_LookupValue
// [] -> [ValueFound]
//------------------------------------------------------------------------------
void PUnit_LookupValue::Exec(Processor& processor) const
{
	const Value* pValue = processor.GetFrame().LookupValue(GetSymbol());
	if (!pValue) {
		Error::Issue(ErrorType::ValueError, "symbol not found: %s", GetSymbol()->GetName());
		return;
	}
	processor.PushStack(pValue->Reference());
	processor.Goto(GetPUnitNext());
}

String PUnit_LookupValue::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "LookupValue(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_LookupPropValue
// [ValueTarget] -> [ValueTarget ValueFound]
//------------------------------------------------------------------------------
void PUnit_LookupPropValue::Exec(Processor& processor) const
{
	Value* pValueTarget = processor.PeekStack(0);
	Value* pValue = pValueTarget->LookupPropValue(GetSymbol(), GetAttr());
	if (!pValue) {
		Error::Issue(ErrorType::ValueError, "symbol not found: %s", GetSymbol()->GetName());
		return;
	}
	processor.PushStack(pValue->Reference());
	processor.Goto(GetPUnitNext());
}

String PUnit_LookupPropValue::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "LookupPropValue(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_AssignValue
// [ValueAssigned] -> [ValueAssigned]
//------------------------------------------------------------------------------
void PUnit_AssignValue::Exec(Processor& processor) const
{
	RefPtr<Value> pValueAssigned(processor.PeekStack(0)->Reference());
	processor.GetFrame().AssignValue(GetSymbol(), pValueAssigned.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_AssignValue::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "AssignValue(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_AssignPropValue
// [ValueTarget ValueAssigned] -> [ValueAssigned]
//------------------------------------------------------------------------------
void PUnit_AssignPropValue::Exec(Processor& processor) const
{
	RefPtr<Value> pValueAssigned(processor.PopStack());
	RefPtr<Value> pValueTarget(processor.PopStack());
	pValueTarget->AssignPropValue(GetSymbol(), pValueAssigned->Reference(), GetAttr());
	processor.PushStack(pValueAssigned.release());
}

String PUnit_AssignPropValue::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "AssignPropValue(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Member
// [ValueTarget] -> [ValueMember(ValueTarget+ValueFound)]
// [ValueTarget] -> [ValueFound]
//------------------------------------------------------------------------------
void PUnit_Member::Exec(Processor& processor) const
{
	RefPtr<Value> pValueTarget(processor.PopStack());
	Value* pValue = pValueTarget->LookupPropValue(GetSymbol(), GetAttr());
	if (!pValue) {
		Error::Issue(ErrorType::ValueError, "symbol not found: %s", GetSymbol()->GetName());
		return;
	}
	if (pValue->IsCallable()) {
		processor.PushStack(new Value_Member(pValueTarget.release(), pValue->Reference()));
	} else {
		processor.PushStack(pValue->Reference());
	}
	processor.Goto(GetPUnitNext());
}

String PUnit_Member::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Member()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_UnaryOp
// [Value] -> [ValueResult]
//------------------------------------------------------------------------------
void PUnit_UnaryOp::Exec(Processor& processor) const
{
	RefPtr<Value> pValueChild(processor.PopStack());
	RefPtr<Value> pValue(GetOperator()->EvalUnary(pValueChild.get()));
	if (!pValue) return;
	processor.PushStack(pValue.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_UnaryOp::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "UnaryOp(";
	rtn += GetOperator()->GetSymbol();
	rtn += ")";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_BinaryOp
// [ValueLeft ValueRight] -> [ValueResult]
//------------------------------------------------------------------------------
void PUnit_BinaryOp::Exec(Processor& processor) const
{
	RefPtr<Value> pValueRight(processor.PopStack());
	RefPtr<Value> pValueLeft(processor.PopStack());
	RefPtr<Value> pValue(GetOperator()->EvalBinary(pValueLeft.release(), pValueRight.release()));
	if (!pValue) return;
	processor.PushStack(pValue.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_BinaryOp::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "BinaryOp(";
	rtn += GetOperator()->GetSymbol();
	rtn += ")";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_CreateArgumentForCall
// [ValueCar] -> [ValueArgument(ValueCar)]
//------------------------------------------------------------------------------
void PUnit_CreateArgumentForCall::Exec(Processor& processor) const
{
	RefPtr<Value> pValueCar(processor.PopStack());
	const DeclCaller* pDeclCaller = pValueCar->GetDeclCaller();
	if (!pDeclCaller) {
		Error::Issue(ErrorType::ValueError,
					 "value type %s can not be called", pValueCar->GetVType().MakeFullName().c_str());
		return;
	}
	if (!pDeclCaller->CheckAttribute(GetAttr())) return;
	RefPtr<Argument> pArgument(
		new Argument(pDeclCaller->Reference(), GetAttr().Reference(), Value::nil(), pValueCar.release()));
	processor.PushStack(new Value_Argument(pArgument.release()));
	processor.Goto(GetPUnitNext());
}

String PUnit_CreateArgumentForCall::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "CreateArgumentForCall()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_CreateArgumentForIndex
// [ValueCar] -> [ValueArgument(ValueCar)]
//------------------------------------------------------------------------------
void PUnit_CreateArgumentForIndex::Exec(Processor& processor) const
{
	RefPtr<Value> pValueCar(processor.PopStack());
	RefPtr<Argument> pArgument(
		new Argument(DeclCaller::Empty->Reference(), GetAttr().Reference(), Value::nil(), pValueCar.release()));
	processor.PushStack(new Value_Argument(pArgument.release()));
	processor.Goto(GetPUnitNext());
}

String PUnit_CreateArgumentForIndex::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "CreateArgumentForIndex()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Call
// [ValueArgument] -> [ValueResult]
//------------------------------------------------------------------------------
void PUnit_Call::Exec(Processor& processor) const
{
	RefPtr<Value_Argument> pValue(dynamic_cast<Value_Argument*>(processor.PopStack()));
	Argument& argument = pValue->GetArgument();
	if (!argument.CheckValidity()) return;
	argument.Call(processor.GetFrame());
	processor.Goto(GetPUnitNext());
}

String PUnit_Call::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Call()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_IndexAccess
// [ValueArgument] -> [ValueResult]
//------------------------------------------------------------------------------
void PUnit_IndexAccess::Exec(Processor& processor) const
{
	RefPtr<Value_Argument> pValue(dynamic_cast<Value_Argument*>(Context::PopStack()));
	Argument& argument = pValue->GetArgument();
	if (!argument.CheckValidity()) return;
	argument.IndexAccess(processor.GetFrame());
	processor.Goto(GetPUnitNext());
}

String PUnit_IndexAccess::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "IndexAccess()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_PrepareArgument
// [ValueArgument] -> [ValueArgument]
//------------------------------------------------------------------------------
void PUnit_PrepareArgument::Exec(Processor& processor) const
{
	Argument& argument = dynamic_cast<Value_Argument*>(processor.PeekStack(0))->GetArgument();
	ArgSlot* pArgSlot = argument.GetArgSlotToFeed(); // this may be nullptr
	if (!pArgSlot) {
		Error::Issue(ErrorType::ArgumentError, "too many arguments");
		return;
	}
	if (!pArgSlot->IsVacant()) {
		Error::Issue(ErrorType::ArgumentError, "duplicated assignment of argument");
		return;
	}
	if (pArgSlot->IsVType(VTYPE_Quote)) {
		argument.FeedValue(new Value_Expr(GetExpr()->Reference()));
		//processor.Goto(GetPUnitNext());
	} else {
		processor.Goto(GetPUnitNext());
	}
}

String PUnit_PrepareArgument::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "PrepareArgument()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_FeedArgument
// [ValueArgument Value] -> [ValueArgument]
//------------------------------------------------------------------------------
void PUnit_FeedArgument::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopStack());
	Argument& argument = dynamic_cast<Value_Argument*>(processor.PeekStack(0))->GetArgument();
	argument.FeedValue(pValue.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_FeedArgument::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "FeedArgument()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_PrepareNamedArgument
// [ValueArgument] -> [ValueArgument ValueArgSlot]
//------------------------------------------------------------------------------
void PUnit_PrepareNamedArgument::Exec(Processor& processor) const
{
	Argument& argument = dynamic_cast<Value_Argument*>(processor.PeekStack(0))->GetArgument();
	ArgSlot* pArgSlot = argument.FindArgSlot(GetSymbol());
	if (!pArgSlot) {
		Error::Issue(ErrorType::ArgumentError, "can't find argument with a name: %s", GetSymbol()->GetName());
		return;
	}
	if (!pArgSlot->IsVacant()) {
		Error::Issue(ErrorType::ArgumentError, "duplicated assignment of argument");
		return;
	}
	if (pArgSlot->IsVType(VTYPE_Quote)) {
		pArgSlot->FeedValue(new Value_Expr(GetExpr()->Reference()));
		//processor.Goto(GetPUnitNext());
	} else {
		processor.PushStack(new Value_ArgSlot(pArgSlot->Reference()));
		processor.Goto(GetPUnitNext());
	}
}

String PUnit_PrepareNamedArgument::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "PrepareNamesArgument(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_FeedNamedArgument
// [ValueArgSlot Value] -> []
//------------------------------------------------------------------------------
void PUnit_FeedNamedArgument::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopStack());
	ArgSlot& argSlot = dynamic_cast<Value_ArgSlot*>(processor.PopStack())->GetArgSlot();
	argSlot.FeedValue(pValue.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_FeedNamedArgument::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "FeedNamedArgument()";
	return rtn;
}

}
