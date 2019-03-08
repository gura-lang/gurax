//==============================================================================
// PUnit.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PUnit
//------------------------------------------------------------------------------
int PUnit::_seqIdNext = 0;

PUnit::PUnit(Expr* pExprSrc) :
	_seqId(++_seqIdNext), _flags(Flag::None), _pExprSrc(pExprSrc), _pPUnitNext(nullptr)
{
	_pExprSrc->SetPUnitTop(this);
}

void PUnit::AppendInfoToString(String& str) const
{
	if (GetPopToDiscardFlag()) str += ", PopToDiscard()";
	if (_pPUnitNext) {
		size_t seqIdNext = _pPUnitNext->GetSeqId();
		if (seqIdNext != GetSeqId() + 1) {
			str += ", Jump(#";
			str += std::to_string(seqIdNext);
			str += ")";
		}
	} else {
		str += ", Terminate()";
	}
}

//------------------------------------------------------------------------------
// PUnitList
//------------------------------------------------------------------------------
void PUnitList::Print() const
{
	for (auto pPUnit : *this) {
		::printf("#%zu %s\n", pPUnit->GetSeqId(), pPUnit->ToString().c_str());
	}
}

//------------------------------------------------------------------------------
// PUnitStack
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PUnit_Value
// Stack View: [] -> [Value]
//------------------------------------------------------------------------------
const PUnit* PUnit_Value::Exec(Processor& processor) const
{
	if (!GetPopToDiscardFlag()) processor.PushValue(GetValue()->Reference());
	return GetPUnitNext();
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
const PUnit* PUnit_Lookup::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) return GetPUnitNext();
	const Value* pValue = processor.GetFrame().LookupValue(GetSymbol());
	if (!pValue) {
		IssueError(ErrorType::ValueError, "symbol not found: %s", GetSymbol()->GetName());
		return nullptr;
	}
	processor.PushValue(pValue->Reference());
	return GetPUnitNext();
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
const PUnit* PUnit_AssignToSymbol::Exec(Processor& processor) const
{
	RefPtr<Value> pValueAssigned(
		GetPopToDiscardFlag()? processor.PopValue() : processor.PeekValue(0)->Reference());
	processor.GetFrame().AssignValue(GetSymbol(), pValueAssigned.release());
	return GetPUnitNext();
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
// Stack View: [ValueAssigned] -> [ValueCasted]
//------------------------------------------------------------------------------
const PUnit* PUnit_AssignToDeclArg::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrame();
	RefPtr<Value> pValueAssigned(processor.PopValue());
	RefPtr<Value> pValueCasted(_pDeclArg->Cast(frame, *pValueAssigned));
	if (!pValueCasted) return nullptr;
	frame.AssignValue(GetDeclArg().GetSymbol(), pValueCasted->Reference());
	if (!GetPopToDiscardFlag()) processor.PushValue(pValueCasted.release());
	return GetPUnitNext();
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
const PUnit* PUnit_AssignFunction::Exec(Processor& processor) const
{
	RefPtr<Value> pValueAssigned(new Value_Function(GetFunction().Reference()));
	processor.GetFrame().AssignValue(GetFunction().GetSymbol(), pValueAssigned->Reference());
	if (!GetPopToDiscardFlag()) processor.PushValue(pValueAssigned->Reference());
	return GetPUnitNext();
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
// PUnit_Cast
// Stack View: [Value] -> [ValueResult]
//------------------------------------------------------------------------------
const PUnit* PUnit_Cast::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) {
		Value::Delete(processor.PopValue());
		return GetPUnitNext();
	}
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Value> pValueCasted(GetVType().Cast(*pValue));
	if (!pValueCasted) return nullptr;
	processor.PushValue(pValueCasted.release());
	return GetPUnitNext();
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
const PUnit* PUnit_UnaryOp::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) {
		Value::Delete(processor.PopValue());
		return GetPUnitNext();
	}
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Value> pValueResult(GetOperator()->EvalUnary(*pValue));
	if (pValueResult->IsUndefined()) return nullptr;
	processor.PushValue(pValueResult.release());
	return GetPUnitNext();
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
const PUnit* PUnit_BinaryOp::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) {
		Value::Delete(processor.PopValue());
		Value::Delete(processor.PopValue());
		return GetPUnitNext();
	}
	RefPtr<Value> pValueRight(processor.PopValue());
	RefPtr<Value> pValueLeft(processor.PopValue());
	RefPtr<Value> pValueResult(GetOperator()->EvalBinary(*pValueLeft, *pValueRight));
	if (pValueResult->IsUndefined()) return nullptr;
	processor.PushValue(pValueResult.release());
	return GetPUnitNext();
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
const PUnit* PUnit_Add::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) {
		Value::Delete(processor.PopValue());
		return GetPUnitNext();
	}
	RefPtr<Value> pValue(processor.PopValue());
	int num = dynamic_cast<Value_Number*>(pValue.get())->GetInt();
	processor.PushValue(new Value_Number(num + GetAdded()));
	return GetPUnitNext();
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
const PUnit* PUnit_CreateList::Exec(Processor& processor) const
{
	RefPtr<ValueTypedOwner> pValueTypedOwner(new ValueTypedOwner());
	pValueTypedOwner->Reserve(GetSizeReserve());
	processor.PushValue(new Value_List(pValueTypedOwner.release()));
	return GetPUnitNext();
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
const PUnit* PUnit_AddList::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) {
		Value::Delete(processor.PopValue());
		Value::Delete(processor.PopValue());
		return GetPUnitNext();
	}
	RefPtr<Value> pValueElem(processor.PopValue());
	ValueTypedOwner& valueTypedOwner =
		dynamic_cast<Value_List*>(processor.PeekValue(0))->GetValueTypedOwner();
	valueTypedOwner.Add(pValueElem.release());
	return GetPUnitNext();
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
const PUnit* PUnit_Index::Exec(Processor& processor) const
{
	RefPtr<Value> pValueCar(processor.PopValue());
	RefPtr<Index> pIndex(new Index(pValueCar.release(), GetAttr().Reference()));
	pIndex->Reserve(GetSizeReserve());
	processor.PushValue(new Value_Index(pIndex.release()));
	return GetPUnitNext();
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
const PUnit* PUnit_FeedIndex::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	Index& index = dynamic_cast<Value_Index*>(processor.PeekValue(0))->GetIndex();
	index.FeedValue(pValue.release());
	return GetPUnitNext();
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
const PUnit* PUnit_IndexGet::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) {
		Value::Delete(processor.PopValue());
		return GetPUnitNext();
	}
	RefPtr<Value_Index> pValueIndex(dynamic_cast<Value_Index*>(processor.PopValue()));
	Index& index = pValueIndex->GetIndex();
	RefPtr<Value> pValueElems(index.IndexGet());
	if (Error::IsIssued()) return nullptr;
	processor.PushValue(pValueElems.release());
	return GetPUnitNext();
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
const PUnit* PUnit_IndexSet::Exec(Processor& processor) const
{
	RefPtr<Value> pValueElems(processor.PopValue());
	RefPtr<Value_Index> pValueIndex(dynamic_cast<Value_Index*>(processor.PopValue()));
	Index& index = pValueIndex->GetIndex();
	index.IndexSet(pValueElems->Reference());
	if (Error::IsIssued()) return nullptr;
	if (!GetPopToDiscardFlag()) processor.PushValue(pValueElems.release());
	return GetPUnitNext();
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
const PUnit* PUnit_PropGet::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) {
		Value::Delete(processor.PopValue());
		return GetPUnitNext();
	}
	Value* pValueTarget = processor.PeekValue(0);
	Value* pValueProp = pValueTarget->DoPropGet(GetSymbol(), GetAttr());
	if (!pValueProp) {
		IssueError(ErrorType::ValueError, "symbol not found: %s", GetSymbol()->GetName());
		return nullptr;
	}
	processor.PushValue(pValueProp->Reference());
	return GetPUnitNext();
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
const PUnit* PUnit_PropSet::Exec(Processor& processor) const
{
	RefPtr<Value> pValueProp(processor.PopValue());
	RefPtr<Value> pValueTarget(processor.PopValue());
	pValueTarget->DoPropSet(GetSymbol(), pValueProp->Reference(), GetAttr());
	if (!GetPopToDiscardFlag()) processor.PushValue(pValueProp.release());
	return GetPUnitNext();
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
const PUnit* PUnit_Member::Exec(Processor& processor) const
{
	if (GetPopToDiscardFlag()) {
		Value::Delete(processor.PopValue());
		return GetPUnitNext();
	}
	RefPtr<Value> pValueTarget(processor.PopValue());
	Value* pValueProp = pValueTarget->DoPropGet(GetSymbol(), GetAttr());
	if (!pValueProp) {
		IssueError(ErrorType::ValueError, "symbol not found: %s", GetSymbol()->GetName());
		return nullptr;
	}
	if (pValueProp->IsCallable()) {
		processor.PushValue(new Value_Member(pValueTarget.release(), pValueProp->Reference()));
	} else {
		processor.PushValue(pValueProp->Reference());
	}
	return GetPUnitNext();
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
const PUnit* PUnit_Argument::Exec(Processor& processor) const
{
	RefPtr<Value> pValueCar(processor.PopValue());
	const DeclCallable* pDeclCallable = pValueCar->GetDeclCallable();
	if (!pDeclCallable) {
		IssueError(ErrorType::ValueError,
				   "value type %s can not be called", pValueCar->GetVType().MakeFullName().c_str());
		return nullptr;
	}
	if (!pDeclCallable->CheckAttribute(GetAttr())) return nullptr;
	RefPtr<Argument> pArgument(
		new Argument(pValueCar.release(), pDeclCallable->Reference(), GetAttr().Reference(), Value::nil()));
	processor.PushValue(new Value_Argument(pArgument.release()));
	return GetPUnitNext();
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
const PUnit* PUnit_ArgSlot::Exec(Processor& processor) const
{
	Argument& argument = dynamic_cast<Value_Argument*>(processor.PeekValue(0))->GetArgument();
	ArgSlot* pArgSlot = argument.GetArgSlotToFeed(); // this may be nullptr
	if (!pArgSlot) {
		IssueError(ErrorType::ArgumentError, "too many arguments");
		return nullptr;
	} else if (!pArgSlot->IsVacant()) {
		IssueError(ErrorType::ArgumentError, "duplicated assignment of argument");
		return nullptr;
	} else if (pArgSlot->IsVType(VTYPE_Quote)) {
		argument.FeedValue(new Value_Expr(GetExprSrc()->Reference()));
		return GetPUnitSkipDest();
	} else {
		return GetPUnitNext();
	}
}

String PUnit_ArgSlot::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "ArgSlot(`(";
	rtn += GetExprSrc()->ToString(ss);
	rtn += "), #";
	rtn += std::to_string(GetPUnitSkipDest()->GetSeqId());
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_FeedArgSlot
// Stack View: [ValueArgument Value] -> [ValueArgument]
//------------------------------------------------------------------------------
const PUnit* PUnit_FeedArgSlot::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	Argument& argument = dynamic_cast<Value_Argument*>(processor.PeekValue(0))->GetArgument();
	argument.FeedValue(pValue.release());
	return GetPUnitNext();
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
const PUnit* PUnit_ArgSlotNamed::Exec(Processor& processor) const
{
	Argument& argument = dynamic_cast<Value_Argument*>(processor.PeekValue(0))->GetArgument();
	ArgSlot* pArgSlot = argument.FindArgSlot(GetSymbol());
	if (!pArgSlot) {
		Value_Dict* pValueOfDict = argument.GetValueOfDict();
		if (pValueOfDict) {
			processor.PushValue(
				new Value_ArgSlot(
					new ArgSlot_Dict(pValueOfDict->GetValueDict().Reference(), GetSymbol())));
			return GetPUnitNext();
		} else {
			IssueError(ErrorType::ArgumentError, "can't find argument with a name: %s", GetSymbol()->GetName());
			return nullptr;
		}
	} else if (!pArgSlot->IsVacant()) {
		IssueError(ErrorType::ArgumentError, "duplicated assignment of argument");
		return nullptr;
	} else if (pArgSlot->IsVType(VTYPE_Quote)) {
		pArgSlot->FeedValue(new Value_Expr(GetExprAssigned()->Reference()));
		return GetPUnitSkipDest();
	} else {
		processor.PushValue(new Value_ArgSlot(pArgSlot->Reference()));
		return GetPUnitNext();
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
	rtn += std::to_string(GetPUnitSkipDest()->GetSeqId());
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_FeedArgSlotNamed
// Stack View: [ValueArgSlot Value] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_FeedArgSlotNamed::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	ArgSlot& argSlot = dynamic_cast<Value_ArgSlot*>(processor.PopValue())->GetArgSlot();
	argSlot.FeedValue(pValue.release());
	return GetPUnitNext();
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
const PUnit* PUnit_Call::Exec(Processor& processor) const
{
	RefPtr<Value_Argument> pValue(dynamic_cast<Value_Argument*>(processor.PopValue()));
	Argument& argument = pValue->GetArgument();
	if (!argument.CheckValidity()) return nullptr;
	RefPtr<Value> pValueResult(argument.DoCall(processor));
	if (Error::IsIssued()) {
		for (auto pExpr : Error::GetErrorOwner()) pExpr->SetExpr(GetExprSrc()->Reference());
		return nullptr;
	}
	if (argument.GetPUnitNext()) {
		processor.PushPUnit(GetPUnitNext());
		return argument.GetPUnitNext();
	} else {
		if (!GetPopToDiscardFlag()) processor.PushValue(pValueResult.release());
		return GetPUnitNext();
	}
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
const PUnit* PUnit_Jump::Exec(Processor& processor) const
{
	return GetPUnitJumpDest();
}

String PUnit_Jump::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Jump(#";
	rtn += std::to_string(GetPUnitJumpDest()->GetSeqId());
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_JumpIf
// Stack View: [Value] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_JumpIf::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	return pValue->GetBool()? GetPUnitJumpDest() : GetPUnitNext();
}

String PUnit_JumpIf::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "JumpIf(#";
	rtn += std::to_string(GetPUnitJumpDest()->GetSeqId());
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_JumpIfNot
// Stack View: [Value] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_JumpIfNot::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	return pValue->GetBool()? GetPUnitNext() : GetPUnitJumpDest();
}

String PUnit_JumpIfNot::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "JumpIfNot(#";
	rtn += std::to_string(GetPUnitJumpDest()->GetSeqId());
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_NilJumpIf
// Stack View: [Value] -> [] or [nil]
//------------------------------------------------------------------------------
const PUnit* PUnit_NilJumpIf::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		processor.PushValue(Value::nil());
		return GetPUnitJumpDest();
	} else {
		return GetPUnitNext();
	}
}

String PUnit_NilJumpIf::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "NilJumpIf(#";
	rtn += std::to_string(GetPUnitJumpDest()->GetSeqId());
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_NilJumpIfNot
// Stack View: [Value] -> [] or [nil]
//------------------------------------------------------------------------------
const PUnit* PUnit_NilJumpIfNot::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		return GetPUnitNext();
	} else {
		processor.PushValue(Value::nil());
		return GetPUnitJumpDest();
	}
}

String PUnit_NilJumpIfNot::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "NilJumpIfNot(#";
	rtn += std::to_string(GetPUnitJumpDest()->GetSeqId());
	rtn += ")";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_PopToDiscard
// Stack View: [Value] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_PopToDiscard::Exec(Processor& processor) const
{
	Value::Delete(processor.PopValue());
	return GetPUnitNext();
}

String PUnit_PopToDiscard::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "PopToDiscard()";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Return
// Stack View: [] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_Return::Exec(Processor& processor) const
{
	return processor.IsPUnitStackEmpty()? nullptr : processor.PopPUnit();
}

String PUnit_Return::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Return()";
	AppendInfoToString(rtn);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Terminate
// Stack View: [] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_Terminate::Exec(Processor& processor) const
{
	return nullptr;
}

String PUnit_Terminate::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Terminate()";
	AppendInfoToString(rtn);
	return rtn;
}

}
