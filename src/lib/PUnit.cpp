//==============================================================================
// PUnit.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PUnit
//------------------------------------------------------------------------------
PUnit* PUnit::_pPUnitCont = nullptr;

//------------------------------------------------------------------------------
// PUnitList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PUnit_Value
// Stack View: [] -> [Value]
//------------------------------------------------------------------------------
void PUnit_Value::Exec(Processor& processor) const
{
	processor.PushStack(GetValue()->Reference());
	processor.Goto(GetPUnitNext());
}

String PUnit_Value::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Value()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Lookup
// Stack View: [] -> [Value]
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
// Stack View: [ValueAssigned] -> [ValueAssigned]
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
// Stack View: [Value] -> []
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
// Stack View: [ValueChild] -> [ValueResult]
//------------------------------------------------------------------------------
void PUnit_UnaryOp::Exec(Processor& processor) const
{
	RefPtr<Value> pValueChild(processor.PopStack());
	RefPtr<Value> pValueResult(GetOperator()->EvalUnary(pValueChild.get()));
	if (!pValueResult) return;
	processor.PushStack(pValueResult.release());
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
// Stack View: [ValueLeft ValueRight] -> [ValueResult]
//------------------------------------------------------------------------------
void PUnit_BinaryOp::Exec(Processor& processor) const
{
	RefPtr<Value> pValueRight(processor.PopStack());
	RefPtr<Value> pValueLeft(processor.PopStack());
	RefPtr<Value> pValueResult(GetOperator()->EvalBinary(pValueLeft.release(), pValueRight.release()));
	if (!pValueResult) return;
	processor.PushStack(pValueResult.release());
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
// Stack View: [] -> [ValueList]
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
// Stack View: [ValueList ValueElem] -> [ValueList]
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
// Stack View: [ValueCar] -> [ValueIndex(ValueCar)]
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
// Stack View: [ValueIndex Value] -> [ValueIndex]
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
// Stack View: [ValueIndex] -> [ValueElems]
//------------------------------------------------------------------------------
void PUnit_IndexGet::Exec(Processor& processor) const
{
	RefPtr<Value_Index> pValueIndex(dynamic_cast<Value_Index*>(Context::PopStack()));
	Index& index = pValueIndex->GetIndex();
	RefPtr<Value> pValueElems(index.IndexGet());
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
// Stack View: [ValueIndex ValueElems] -> [ValueElems]
//------------------------------------------------------------------------------
void PUnit_IndexSet::Exec(Processor& processor) const
{
	RefPtr<Value> pValueElems(processor.PopStack());
	RefPtr<Value_Index> pValueIndex(dynamic_cast<Value_Index*>(Context::PopStack()));
	Index& index = pValueIndex->GetIndex();
	index.IndexSet(pValueElems->Reference());
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
// Stack View: [ValueTarget] -> [ValueTarget ValueProp]
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
// Stack View: [ValueTarget ValueProp] -> [ValueProp]
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
// Stack View: [ValueTarget] -> [ValueMember(ValueTarget+ValueProp)]
//             [ValueTarget] -> [ValueProp]
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
// Stack View: [ValueCar] -> [ValueArgument(ValueCar)]
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
// PUnit_ArgSlot
// Stack View: [ValueArgument] -> [ValueArgument]
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
// Stack View: [ValueArgument Value] -> [ValueArgument]
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
// Stack View: [ValueArgument] -> [ValueArgument ValueArgSlot]
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
// Stack View: [ValueArgSlot Value] -> []
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

//------------------------------------------------------------------------------
// PUnit_Call
// Stack View: [ValueArgument] -> [ValueResult]
//------------------------------------------------------------------------------
void PUnit_Call::Exec(Processor& processor) const
{
	RefPtr<Value_Argument> pValue(dynamic_cast<Value_Argument*>(processor.PopStack()));
	Argument& argument = pValue->GetArgument();
	if (!argument.CheckValidity()) return;
	RefPtr<Value> pValueResult(argument.Call(processor.GetFrame()));
	if (Error::IsIssued()) return;
	processor.PushStack(pValueResult.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_Call::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Call()";
	return rtn;
}

}
