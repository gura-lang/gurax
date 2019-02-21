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
// PUnit_Lookup
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Lookup : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("Lookup");
private:
	const Symbol* _pSymbol;
public:
	// Constructor
	PUnit_Lookup(const Symbol* pSymbol) : _pSymbol(pSymbol) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_Assign
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Assign : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("Assign");
private:
	const Symbol* _pSymbol;
public:
	// Constructor
	PUnit_Assign(const Symbol* pSymbol) : _pSymbol(pSymbol) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_Erase
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Erase : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("Erase");
public:
	// Constructor
	PUnit_Erase() {}
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
// PUnit_CreateList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_CreateList : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("List");
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
// PUnit_AddList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_AddList : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("AddList");
public:
	// Constructor
	PUnit_AddList() {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_Index
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Index : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("CreateIndex");
private:
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_Index(Attribute* pAttr) : _pAttr(pAttr) {}
public:
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_FeedIndex
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_FeedIndex : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("FeedIndex");
public:
	// Constructor
	PUnit_FeedIndex() {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_IndexGet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_IndexGet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("IndexGet");
public:
	// Constructor
	PUnit_IndexGet() {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_IndexSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_IndexSet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("IndexSet");
public:
	// Constructor
	PUnit_IndexSet() {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_PropGet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_PropGet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("PropGet");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_PropGet(const Symbol* pSymbol, Attribute* pAttr) :
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
// PUnit_PropSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_PropSet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("PropSet");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_PropSet(const Symbol* pSymbol, Attribute* pAttr) : _pSymbol(pSymbol), _pAttr(pAttr) {}
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
// PUnit_Argument
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Argument : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("CreateArgument");
private:
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_Argument(Attribute* pAttr) : _pAttr(pAttr) {}
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
// PUnit_ArgSlot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_ArgSlot : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("ArgSlot");
private:
	RefPtr<Expr> _pExpr;
public:
	// Constructor
	explicit PUnit_ArgSlot(Expr* pExpr) : _pExpr(pExpr) {}
public:
	const Expr* GetExpr() const { return _pExpr.get(); }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_FeedArgSlot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_FeedArgSlot : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("FeedArgSlot");
public:
	// Constructor
	PUnit_FeedArgSlot() {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_ArgSlotNamed
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_ArgSlotNamed : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("ArgSlotNamed");
private:
	const Symbol* _pSymbol;
	RefPtr<Expr> _pExpr;
public:
	// Constructor
	explicit PUnit_ArgSlotNamed(const Symbol* pSymbol, Expr* pExpr) :
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
// PUnit_FeedArgSlotNamed
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_FeedArgSlotNamed : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("FeedArgSlotNamed");
public:
	// Constructor
	PUnit_FeedArgSlotNamed() {}
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
// PUnit_Lookup
// [] -> [Value]
//------------------------------------------------------------------------------
void PUnit_Lookup::Exec(Processor& processor) const
{
	const Value* pValue = processor.GetFrame().LookupValue(GetSymbol());
	if (!pValue) {
		Error::Issue(ErrorType::ValueError, "symbol not found: %s", GetSymbol()->GetName());
		return;
	}
	processor.PushStack(pValue->Reference());
	processor.Goto(GetPUnitNext());
}

String PUnit_Lookup::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Lookup(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Assign
// [ValueAssigned] -> [ValueAssigned]
//------------------------------------------------------------------------------
void PUnit_Assign::Exec(Processor& processor) const
{
	RefPtr<Value> pValueAssigned(processor.PeekStack(0)->Reference());
	processor.GetFrame().AssignValue(GetSymbol(), pValueAssigned.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_Assign::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Assign(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Erase
// [Value] -> []
//------------------------------------------------------------------------------
void PUnit_Erase::Exec(Processor& processor) const
{
	Value::Delete(processor.PopStack());
	processor.Goto(GetPUnitNext());
}

String PUnit_Erase::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Erase()";
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
// PUnit_AddList
// [ValueList ValueElem] -> [ValueList]
//------------------------------------------------------------------------------
void PUnit_AddList::Exec(Processor& processor) const
{
	RefPtr<Value> pValueElem(processor.PopStack());
	ValueTypedOwner& valueTypedOwner =
		dynamic_cast<Value_List*>(processor.PeekStack(0))->GetValueTypedOwner();
	valueTypedOwner.Add(pValueElem.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_AddList::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "AddValueList()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Index
// [ValueCar] -> [ValueIndex(ValueCar)]
//------------------------------------------------------------------------------
void PUnit_Index::Exec(Processor& processor) const
{
	RefPtr<Value> pValueCar(processor.PopStack());
	RefPtr<Index> pIndex(new Index(pValueCar.release(), GetAttr().Reference()));
	processor.PushStack(new Value_Index(pIndex.release()));
	processor.Goto(GetPUnitNext());
}

String PUnit_Index::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "CreateIndex()";
	rtn += GetAttr().ToString(ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_FeedIndex
// [ValueIndex Value] -> [ValueIndex]
//------------------------------------------------------------------------------
void PUnit_FeedIndex::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopStack());
	Index& index = dynamic_cast<Value_Index*>(processor.PeekStack(0))->GetIndex();
	index.FeedValue(pValue.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_FeedIndex::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "FeedIndex()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_IndexGet
// [ValueArgument] -> [ValueElems]
//------------------------------------------------------------------------------
void PUnit_IndexGet::Exec(Processor& processor) const
{
	RefPtr<Value_Argument> pValueArgument(dynamic_cast<Value_Argument*>(Context::PopStack()));
	Argument& argument = pValueArgument->GetArgument();
	if (!argument.CheckValidity()) return;
	RefPtr<Value> pValueElems(argument.IndexGet());
	if (Error::IsIssued()) return;
	processor.PushStack(pValueElems.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_IndexGet::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "IndexGet()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_IndexSet
// [ValueArgument ValueElems] -> [ValueElems]
//------------------------------------------------------------------------------
void PUnit_IndexSet::Exec(Processor& processor) const
{
	RefPtr<Value> pValueElems(processor.PopStack());
	RefPtr<Value_Argument> pValueArgument(dynamic_cast<Value_Argument*>(Context::PopStack()));
	Argument& argument = pValueArgument->GetArgument();
	if (!argument.CheckValidity()) return;
	argument.IndexSet(pValueElems->Reference());
	if (Error::IsIssued()) return;
	processor.PushStack(pValueElems.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_IndexSet::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "IndexSet()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_PropGet
// [ValueTarget] -> [ValueTarget ValueProp]
//------------------------------------------------------------------------------
void PUnit_PropGet::Exec(Processor& processor) const
{
	Value* pValueTarget = processor.PeekStack(0);
	Value* pValueProp = pValueTarget->DoPropGet(GetSymbol(), GetAttr());
	if (!pValueProp) {
		Error::Issue(ErrorType::ValueError, "symbol not found: %s", GetSymbol()->GetName());
		return;
	}
	processor.PushStack(pValueProp->Reference());
	processor.Goto(GetPUnitNext());
}

String PUnit_PropGet::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "PropGet(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	rtn += GetAttr().ToString(ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_PropSet
// [ValueTarget ValueProp] -> [ValueProp]
//------------------------------------------------------------------------------
void PUnit_PropSet::Exec(Processor& processor) const
{
	RefPtr<Value> pValueProp(processor.PopStack());
	RefPtr<Value> pValueTarget(processor.PopStack());
	pValueTarget->DoPropSet(GetSymbol(), pValueProp->Reference(), GetAttr());
	processor.PushStack(pValueProp.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_PropSet::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "PropSet(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	rtn += GetAttr().ToString(ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Member
// [ValueTarget] -> [ValueMember(ValueTarget+ValueProp)]
// [ValueTarget] -> [ValueProp]
//------------------------------------------------------------------------------
void PUnit_Member::Exec(Processor& processor) const
{
	RefPtr<Value> pValueTarget(processor.PopStack());
	Value* pValue = pValueTarget->DoPropGet(GetSymbol(), GetAttr());
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
	rtn += "Member(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	rtn += GetAttr().ToString(ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Argument
// [ValueCar] -> [ValueArgument(ValueCar)]
//------------------------------------------------------------------------------
void PUnit_Argument::Exec(Processor& processor) const
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
		new Argument(pValueCar.release(), pDeclCaller->Reference(), GetAttr().Reference(), Value::nil()));
	processor.PushStack(new Value_Argument(pArgument.release()));
	processor.Goto(GetPUnitNext());
}

String PUnit_Argument::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Argument()";
	rtn += GetAttr().ToString(ss);
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
	RefPtr<Value> pValueRtn(argument.Call(processor.GetFrame()));
	if (Error::IsIssued()) return;
	processor.PushStack(pValueRtn.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_Call::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Call()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_ArgSlot
// [ValueArgument] -> [ValueArgument]
//------------------------------------------------------------------------------
void PUnit_ArgSlot::Exec(Processor& processor) const
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

String PUnit_ArgSlot::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "ArgSlot()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_FeedArgSlot
// [ValueArgument Value] -> [ValueArgument]
//------------------------------------------------------------------------------
void PUnit_FeedArgSlot::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopStack());
	Argument& argument = dynamic_cast<Value_Argument*>(processor.PeekStack(0))->GetArgument();
	argument.FeedValue(pValue.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_FeedArgSlot::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "FeedArgSlot()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_ArgSlotNamed
// [ValueArgument] -> [ValueArgument ValueArgSlot]
//------------------------------------------------------------------------------
void PUnit_ArgSlotNamed::Exec(Processor& processor) const
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

String PUnit_ArgSlotNamed::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "ArgSlotNamed(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_FeedArgSlotNamed
// [ValueArgSlot Value] -> []
//------------------------------------------------------------------------------
void PUnit_FeedArgSlotNamed::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopStack());
	ArgSlot& argSlot = dynamic_cast<Value_ArgSlot*>(processor.PopStack())->GetArgSlot();
	argSlot.FeedValue(pValue.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_FeedArgSlotNamed::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "FeedArgSlotNamed()";
	return rtn;
}

}
