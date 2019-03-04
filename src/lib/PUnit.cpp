//==============================================================================
// PUnit.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PUnit
//------------------------------------------------------------------------------
int PUnit::_idNext = 0;

PUnit::PUnit(Expr* pExprSrc) :
	_id(_idNext++), _pExprSrc(pExprSrc), _pPUnitNext(nullptr), _popToDiscardFlag(false)
{
	_pExprSrc->SetPUnitTop(this);
}

void PUnit::AppendInfoToString(String& str) const
{
	if (GetPopToDiscardFlag()) str += ", PopToDiscard";
	if (_pPUnitNext) {
		size_t idNext = _pPUnitNext->GetId();
		if (idNext != GetId() + 1) {
			str += ", #";
			str += std::to_string(idNext);
		}
	} else {
		str += ", Return";
	}
}

//------------------------------------------------------------------------------
// PUnitList
//------------------------------------------------------------------------------
void PUnitList::Print() const
{
	for (auto pPUnit : *this) {
		::printf("#%zu %s\n", pPUnit->GetId(), pPUnit->ToString().c_str());
	}
}

//------------------------------------------------------------------------------
// PUnitStack
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PUnit_Value
// Stack View: [] -> [Value]
//------------------------------------------------------------------------------
void PUnit_Value::Exec(Processor& processor) const
{
	if (!GetPopToDiscardFlag()) processor.PushValue(GetValue()->Reference());
	processor.Goto(GetPUnitNext());
}

String PUnit_Value::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Value(";
	rtn += GetValue()->ToString(StringStyle().Digest());
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Lookup
// Stack View: [] -> [Value]
//------------------------------------------------------------------------------
void PUnit_Lookup::Exec(Processor& processor) const
{
	if (!GetPopToDiscardFlag()) {
		const Value* pValue = processor.GetFrame().LookupValue(GetSymbol());
		if (!pValue) {
			Error::Issue(ErrorType::ValueError, "symbol not found: %s", GetSymbol()->GetName());
			return;
		}
		processor.PushValue(pValue->Reference());
	}
	processor.Goto(GetPUnitNext());
}

String PUnit_Lookup::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Lookup(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_AssignToSymbol
// Stack View: [ValueAssigned] -> [ValueAssigned]
//------------------------------------------------------------------------------
void PUnit_AssignToSymbol::Exec(Processor& processor) const
{
	RefPtr<Value> pValueAssigned(
		GetPopToDiscardFlag()? processor.PopValue() : processor.PeekValue(0)->Reference());
	processor.GetFrame().AssignValue(GetSymbol(), pValueAssigned.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_AssignToSymbol::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "AssignToSymbol(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_AssignToDeclArg
// Stack View: [ValueAssigned] -> [ValueAssigned]
//------------------------------------------------------------------------------
void PUnit_AssignToDeclArg::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrame();
	RefPtr<Value> pValueAssigned(
		GetPopToDiscardFlag()? processor.PopValue() : processor.PeekValue(0)->Reference());
	RefPtr<Value> pValueCasted(_pDeclArg->Cast(frame, *pValueAssigned));
	if (!pValueCasted) return;
	frame.AssignValue(GetDeclArg().GetSymbol(), pValueCasted.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_AssignToDeclArg::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "AssignToDeclArg(`";
	rtn += GetDeclArg().ToString(ss);
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_AssignFunction
// Stack View: [] -> [Value]
//------------------------------------------------------------------------------
void PUnit_AssignFunction::Exec(Processor& processor) const
{
	RefPtr<Value> pValueAssigned(new Value_Function(GetFunction().Reference()));
	processor.GetFrame().AssignValue(GetFunction().GetSymbol(), pValueAssigned.release());
	if (!GetPopToDiscardFlag()) processor.PushValue(pValueAssigned->Reference());
	processor.Goto(GetPUnitNext());
}

String PUnit_AssignFunction::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "AssignFunction(";
	rtn += GetFunction().ToString(ss);
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_PopToDiscard
// Stack View: [Value] -> []
//------------------------------------------------------------------------------
void PUnit_PopToDiscard::Exec(Processor& processor) const
{
	Value::Delete(processor.PopValue());
	processor.Goto(GetPUnitNext());
}

String PUnit_PopToDiscard::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "PopToDiscard()";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Cast
// Stack View: [Value] -> [ValueResult]
//------------------------------------------------------------------------------
void PUnit_Cast::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) {
		Value::Delete(processor.PopValue());
	} else {
		RefPtr<Value> pValue(processor.PopValue());
		RefPtr<Value> pValueResult(GetVType().Cast(*pValue));
		if (!pValueResult) return;
		processor.PushValue(pValueResult.release());
	}
	processor.Goto(GetPUnitNext());
}

String PUnit_Cast::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Cast(";
	rtn += GetVType().MakeFullName().c_str();
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_UnaryOp
// Stack View: [Value] -> [ValueResult]
//------------------------------------------------------------------------------
void PUnit_UnaryOp::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) {
		Value::Delete(processor.PopValue());
	} else {
		RefPtr<Value> pValue(processor.PopValue());
		RefPtr<Value> pValueResult(GetOperator()->EvalUnary(*pValue));
		if (pValueResult->IsUndefined()) return;
		processor.PushValue(pValueResult.release());
	}
	processor.Goto(GetPUnitNext());
}

String PUnit_UnaryOp::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "UnaryOp(";
	rtn += GetOperator()->GetSymbol();
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_BinaryOp
// Stack View: [ValueLeft ValueRight] -> [ValueResult]
//------------------------------------------------------------------------------
void PUnit_BinaryOp::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) {
		Value::Delete(processor.PopValue());
		Value::Delete(processor.PopValue());
	} else {
		RefPtr<Value> pValueRight(processor.PopValue());
		RefPtr<Value> pValueLeft(processor.PopValue());
		RefPtr<Value> pValueResult(GetOperator()->EvalBinary(*pValueLeft, *pValueRight));
		if (pValueResult->IsUndefined()) return;
		processor.PushValue(pValueResult.release());
	}
	processor.Goto(GetPUnitNext());
}

String PUnit_BinaryOp::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "BinaryOp(";
	rtn += GetOperator()->GetSymbol();
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Add
// Stack View: [Value] -> [ValueResult]
//------------------------------------------------------------------------------
void PUnit_Add::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) {
		Value::Delete(processor.PopValue());
	} else {
		RefPtr<Value> pValue(processor.PopValue());
		if (!pValue->IsType(VTYPE_Number)) {
			Error::Issue(ErrorType::TypeError, "number value is expected");
			return;
		}
		int num = dynamic_cast<Value_Number*>(pValue.get())->GetInt();
		processor.PushValue(new Value_Number(num + GetAdded()));
	}
	processor.Goto(GetPUnitNext());
}

String PUnit_Add::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Add(";
	rtn += std::to_string(GetAdded());
	rtn += ")";
	AppendInfoToString(rtn);
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
	processor.PushValue(new Value_List(pValueTypedOwner.release()));
	processor.Goto(GetPUnitNext());
}

String PUnit_CreateList::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "CreateList()";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_AddList
// Stack View: [ValueList ValueElem] -> [ValueList]
//------------------------------------------------------------------------------
void PUnit_AddList::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) {
		Value::Delete(processor.PopValue());
		Value::Delete(processor.PopValue());
	} else {
		RefPtr<Value> pValueElem(processor.PopValue());
		ValueTypedOwner& valueTypedOwner =
			dynamic_cast<Value_List*>(processor.PeekValue(0))->GetValueTypedOwner();
		valueTypedOwner.Add(pValueElem.release());
	}
	processor.Goto(GetPUnitNext());
}

String PUnit_AddList::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "AddValueList()";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Index
// Stack View: [ValueCar] -> [ValueIndex(ValueCar)]
//------------------------------------------------------------------------------
void PUnit_Index::Exec(Processor& processor) const
{
	RefPtr<Value> pValueCar(processor.PopValue());
	RefPtr<Index> pIndex(new Index(pValueCar.release(), GetAttr().Reference()));
	pIndex->Reserve(GetSizeReserve());
	processor.PushValue(new Value_Index(pIndex.release()));
	processor.Goto(GetPUnitNext());
}

String PUnit_Index::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "CreateIndex()";
	rtn += GetAttr().ToString(ss);
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_FeedIndex
// Stack View: [ValueIndex Value] -> [ValueIndex]
//------------------------------------------------------------------------------
void PUnit_FeedIndex::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	Index& index = dynamic_cast<Value_Index*>(processor.PeekValue(0))->GetIndex();
	index.FeedValue(pValue.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_FeedIndex::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "FeedIndex()";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_IndexGet
// Stack View: [ValueIndex] -> [ValueElems]
//------------------------------------------------------------------------------
void PUnit_IndexGet::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) {
		Value::Delete(processor.PopValue());
	} else {
		RefPtr<Value_Index> pValueIndex(dynamic_cast<Value_Index*>(processor.PopValue()));
		Index& index = pValueIndex->GetIndex();
		RefPtr<Value> pValueElems(index.IndexGet());
		if (Error::IsIssued()) return;
		processor.PushValue(pValueElems.release());
	}
	processor.Goto(GetPUnitNext());
}

String PUnit_IndexGet::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "IndexGet()";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_IndexSet
// Stack View: [ValueIndex ValueElems] -> [ValueElems]
//------------------------------------------------------------------------------
void PUnit_IndexSet::Exec(Processor& processor) const
{
	RefPtr<Value> pValueElems(processor.PopValue());
	RefPtr<Value_Index> pValueIndex(dynamic_cast<Value_Index*>(processor.PopValue()));
	Index& index = pValueIndex->GetIndex();
	index.IndexSet(pValueElems->Reference());
	if (Error::IsIssued()) return;
	if (!GetPopToDiscardFlag()) processor.PushValue(pValueElems.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_IndexSet::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "IndexSet()";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_PropGet
// Stack View: [ValueTarget] -> [ValueTarget ValueProp]
//------------------------------------------------------------------------------
void PUnit_PropGet::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) {
		Value::Delete(processor.PopValue());
	} else {
		Value* pValueTarget = processor.PeekValue(0);
		Value* pValueProp = pValueTarget->DoPropGet(GetSymbol(), GetAttr());
		if (!pValueProp) {
			Error::Issue(ErrorType::ValueError, "symbol not found: %s", GetSymbol()->GetName());
			return;
		}
		processor.PushValue(pValueProp->Reference());
	}
	processor.Goto(GetPUnitNext());
}

String PUnit_PropGet::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "PropGet(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	rtn += GetAttr().ToString(ss);
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_PropSet
// Stack View: [ValueTarget ValueProp] -> [ValueProp]
//------------------------------------------------------------------------------
void PUnit_PropSet::Exec(Processor& processor) const
{
	RefPtr<Value> pValueProp(processor.PopValue());
	RefPtr<Value> pValueTarget(processor.PopValue());
	pValueTarget->DoPropSet(GetSymbol(), pValueProp->Reference(), GetAttr());
	if (!GetPopToDiscardFlag()) processor.PushValue(pValueProp.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_PropSet::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "PropSet(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	rtn += GetAttr().ToString(ss);
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Member
// Stack View: [ValueTarget] -> [ValueMember(ValueTarget+ValueProp)]
//             [ValueTarget] -> [ValueProp]
//------------------------------------------------------------------------------
void PUnit_Member::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) {
		Value::Delete(processor.PopValue());
	} else {
		RefPtr<Value> pValueTarget(processor.PopValue());
		Value* pValue = pValueTarget->DoPropGet(GetSymbol(), GetAttr());
		if (!pValue) {
			Error::Issue(ErrorType::ValueError, "symbol not found: %s", GetSymbol()->GetName());
			return;
		}
		if (pValue->IsCallable()) {
			processor.PushValue(new Value_Member(pValueTarget.release(), pValue->Reference()));
		} else {
			processor.PushValue(pValue->Reference());
		}
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
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Argument
// Stack View: [ValueCar] -> [ValueArgument(ValueCar)]
//------------------------------------------------------------------------------
void PUnit_Argument::Exec(Processor& processor) const
{
	RefPtr<Value> pValueCar(processor.PopValue());
	const DeclCallable* pDeclCallable = pValueCar->GetDeclCallable();
	if (!pDeclCallable) {
		Error::Issue(ErrorType::ValueError,
					 "value type %s can not be called", pValueCar->GetVType().MakeFullName().c_str());
		return;
	}
	if (!pDeclCallable->CheckAttribute(GetAttr())) return;
	RefPtr<Argument> pArgument(
		new Argument(pValueCar.release(), pDeclCallable->Reference(), GetAttr().Reference(), Value::nil()));
	processor.PushValue(new Value_Argument(pArgument.release()));
	processor.Goto(GetPUnitNext());
}

String PUnit_Argument::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Argument()";
	rtn += GetAttr().ToString(ss);
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_ArgSlot
// Stack View: [ValueArgument] -> [ValueArgument]
//------------------------------------------------------------------------------
void PUnit_ArgSlot::Exec(Processor& processor) const
{
	Argument& argument = dynamic_cast<Value_Argument*>(processor.PeekValue(0))->GetArgument();
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
		argument.FeedValue(new Value_Expr(GetExprSrc()->Reference()));
		processor.Goto(GetPUnitSkipDest());
	} else {
		processor.Goto(GetPUnitNext());
	}
}

String PUnit_ArgSlot::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "ArgSlot(`(";
	rtn += GetExprSrc()->ToString(ss);
	rtn += "), #";
	rtn += std::to_string(GetPUnitSkipDest()->GetId());
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_FeedArgSlot
// Stack View: [ValueArgument Value] -> [ValueArgument]
//------------------------------------------------------------------------------
void PUnit_FeedArgSlot::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	Argument& argument = dynamic_cast<Value_Argument*>(processor.PeekValue(0))->GetArgument();
	argument.FeedValue(pValue.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_FeedArgSlot::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "FeedArgSlot()";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_ArgSlotNamed
// Stack View: [ValueArgument] -> [ValueArgument ValueArgSlot]
//------------------------------------------------------------------------------
void PUnit_ArgSlotNamed::Exec(Processor& processor) const
{
	Argument& argument = dynamic_cast<Value_Argument*>(processor.PeekValue(0))->GetArgument();
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
		pArgSlot->FeedValue(new Value_Expr(GetExprAssigned()->Reference()));
		processor.Goto(GetPUnitSkipDest());
	} else {
		processor.PushValue(new Value_ArgSlot(pArgSlot->Reference()));
		processor.Goto(GetPUnitNext());
	}
}

String PUnit_ArgSlotNamed::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "ArgSlotNamed(`";
	rtn += GetSymbol()->GetName();
	rtn += ss.IsCram()? "=>" : " => `(";
	rtn += GetExprSrc()->ToString(ss);
	rtn += "), #";
	rtn += std::to_string(GetPUnitSkipDest()->GetId());
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_FeedArgSlotNamed
// Stack View: [ValueArgSlot Value] -> []
//------------------------------------------------------------------------------
void PUnit_FeedArgSlotNamed::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	ArgSlot& argSlot = dynamic_cast<Value_ArgSlot*>(processor.PopValue())->GetArgSlot();
	argSlot.FeedValue(pValue.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_FeedArgSlotNamed::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "FeedArgSlotNamed()";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Call
// Stack View: [ValueArgument] -> [ValueResult]
//------------------------------------------------------------------------------
void PUnit_Call::Exec(Processor& processor) const
{
	RefPtr<Value_Argument> pValue(dynamic_cast<Value_Argument*>(processor.PopValue()));
	Argument& argument = pValue->GetArgument();
	if (!argument.CheckValidity()) return;
	RefPtr<Value> pValueResult(argument.DoCall(processor));
	if (Error::IsIssued()) return;
	if (!GetPopToDiscardFlag()) processor.PushValue(pValueResult.release());
	processor.Goto(GetPUnitNext());
}

String PUnit_Call::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Call()";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Jump
// Stack View: [] -> []
//------------------------------------------------------------------------------
void PUnit_Jump::Exec(Processor& processor) const
{
	processor.Goto(GetPUnitDest());
}

String PUnit_Jump::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Jump(#";
	rtn += std::to_string(GetPUnitDest()->GetId());
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_JumpSub
// Stack View: [] -> []
//------------------------------------------------------------------------------
void PUnit_JumpSub::Exec(Processor& processor) const
{
	processor.PushPUnit(this);
	processor.Goto(GetPUnitDest());
}

String PUnit_JumpSub::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "JumpSub(#";
	rtn += std::to_string(GetPUnitDest()->GetId());
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_BranchIf
// Stack View: [Value] -> []
//------------------------------------------------------------------------------
void PUnit_BranchIf::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	processor.Goto(pValue->GetBool()? GetPUnitAtMerging()->GetPUnitNext() : GetPUnitNext());
}

String PUnit_BranchIf::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "BranchIf(##";
	rtn += std::to_string(GetPUnitAtMerging()->GetId());
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_BranchIfNot
// Stack View: [Value] -> []
//------------------------------------------------------------------------------
void PUnit_BranchIfNot::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	processor.Goto(pValue->GetBool()? GetPUnitNext() : GetPUnitAtMerging()->GetPUnitNext());
}

String PUnit_BranchIfNot::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "BranchIfNot(##";
	rtn += std::to_string(GetPUnitAtMerging()->GetId());
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_NilBranchIf
// Stack View: [Value] -> [] or [nil]
//------------------------------------------------------------------------------
void PUnit_NilBranchIf::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		processor.PushValue(Value::nil());
		processor.Goto(GetPUnitAtMerging()->GetPUnitNext());
	} else {
		processor.Goto(GetPUnitNext());
	}
}

String PUnit_NilBranchIf::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "NilBranchIf(##";
	rtn += std::to_string(GetPUnitAtMerging()->GetId());
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_NilBranchIfNot
// Stack View: [Value] -> [] or [nil]
//------------------------------------------------------------------------------
void PUnit_NilBranchIfNot::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		processor.Goto(GetPUnitNext());
	} else {
		processor.PushValue(Value::nil());
		processor.Goto(GetPUnitAtMerging()->GetPUnitNext());
	}
}

String PUnit_NilBranchIfNot::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "NilBranchIfNot(##";
	rtn += std::to_string(GetPUnitAtMerging()->GetId());
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

}
