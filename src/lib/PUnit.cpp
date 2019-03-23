//==============================================================================
// PUnit.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PUnit
//------------------------------------------------------------------------------
PUnit::PUnit(Expr* pExprSrc, SeqId seqId, Flags flags) :
	_pExprSrc(pExprSrc), _seqId(seqId), _flags(flags)
{
}

void PUnit::AppendInfoToString(String& str, const StringStyle& ss) const
{
	if (GetPopValueToDiscardFlag()) {
		str += ss.GetComma();
		str += "PopValueToDiscard()";
	}
}

void PUnit::Print() const
{
	Stream& stream = *Stream::COut;
	stream.Printf("#%zu %s\n", GetSeqId(), ToString().c_str());
}

void PUnit::PrintSequence(const PUnit* pPUnit)
{
	for ( ; pPUnit; pPUnit = pPUnit->GetPUnitNext()) {
		if (!pPUnit->IsBridge()) pPUnit->Print();
	}
}

//------------------------------------------------------------------------------
// PUnitList
//------------------------------------------------------------------------------
void PUnitList::Print() const
{
	for (auto pPUnit : *this) {
		if (!pPUnit->IsBridge()) pPUnit->Print();
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
	if (!GetPopValueToDiscardFlag()) processor.PushValue(GetValue()->Reference());
	return _GetPUnitCont();
}

String PUnit_Value::ToString(const StringStyle& ss) const
{
	String str;
	str += "Value(";
	str += GetValue()->ToString(StringStyle().Digest());
	str += ")";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_ValueAndJump
// Stack View: [] -> [Value]
//------------------------------------------------------------------------------
const PUnit* PUnit_ValueAndJump::Exec(Processor& processor) const
{
	if (!GetPopValueToDiscardFlag()) processor.PushValue(GetValue()->Reference());
	return _GetPUnitCont();
}

String PUnit_ValueAndJump::ToString(const StringStyle& ss) const
{
	String str;
	str += "ValueAndJump(";
	str += GetValue()->ToString(StringStyle().Digest());
	str.Printf(", #%zu)", _GetPUnitCont()->GetSeqId());
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Lookup
// Stack View: [] -> [Value]
//------------------------------------------------------------------------------
const PUnit* PUnit_Lookup::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrameCur();
	if (GetPopValueToDiscardFlag()) return _GetPUnitCont();
	const Value* pValue = frame.Lookup(GetSymbol());
	if (!pValue) {
		IssueError(ErrorType::ValueError, "symbol '%s' is not found", GetSymbol()->GetName());
		return nullptr;
	}
	processor.PushValue(pValue->Reference());
	return _GetPUnitCont();
}

String PUnit_Lookup::ToString(const StringStyle& ss) const
{
	String str;
	str += "Lookup(`";
	str += GetSymbol()->GetName();
	str += ")";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_AssignToSymbol
// Stack View: [ValueAssigned] -> [ValueAssigned]
//------------------------------------------------------------------------------
const PUnit* PUnit_AssignToSymbol::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValueAssigned(
		GetPopValueToDiscardFlag()? processor.PopValue() : processor.PeekValue(0)->Reference());
	frame.Assign(GetSymbol(), pValueAssigned.release());
	return _GetPUnitCont();
}

String PUnit_AssignToSymbol::ToString(const StringStyle& ss) const
{
	String str;
	str += "AssignToSymbol(`";
	str += GetSymbol()->GetName();
	str += ")";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_AssignToDeclArg
// Stack View: [ValueAssigned] -> [ValueAssigned]
//------------------------------------------------------------------------------
const PUnit* PUnit_AssignToDeclArg::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValueAssigned(
		GetPopValueToDiscardFlag()? processor.PopValue() : processor.PeekValue(0)->Reference());
	RefPtr<Value> pValueCasted(_pDeclArg->Cast(frame, *pValueAssigned));
	if (!pValueCasted) return nullptr;
	frame.AssignFromArgument(GetDeclArg().GetSymbol(), pValueCasted->Reference());
	return _GetPUnitCont();
}

String PUnit_AssignToDeclArg::ToString(const StringStyle& ss) const
{
	String str;
	str += "AssignToDeclArg(`";
	str += GetDeclArg().ToString(ss);
	str += ")";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_AssignFunction
// Stack View: [] -> [Value]
//------------------------------------------------------------------------------
const PUnit* PUnit_AssignFunction::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValueAssigned(new Value_Function(GetFunction().Reference()));
	frame.Assign(GetFunction().GetSymbol(), pValueAssigned->Reference());
	if (!GetPopValueToDiscardFlag()) processor.PushValue(pValueAssigned->Reference());
	return _GetPUnitCont();
}

String PUnit_AssignFunction::ToString(const StringStyle& ss) const
{
	String str;
	str += "AssignFunction(";
	str += GetFunction().ToString(ss);
	str.Printf(", #%zu)", _GetPUnitCont()->GetSeqId());
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Cast
// Stack View: [Value] -> [ValueResult]
//------------------------------------------------------------------------------
const PUnit* PUnit_Cast::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		return _GetPUnitCont();
	}
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Value> pValueCasted(GetVType().Cast(*pValue));
	if (!pValueCasted) return nullptr;
	processor.PushValue(pValueCasted.release());
	return _GetPUnitCont();
}

String PUnit_Cast::ToString(const StringStyle& ss) const
{
	String str;
	str += "Cast(";
	str += GetVType().MakeFullName().c_str();
	str += ")";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_GenIterator
// Stack View: [Value] -> [ValueIterator]
//------------------------------------------------------------------------------
const PUnit* PUnit_GenIterator::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		return _GetPUnitCont();
	}
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Iterator> pIterator(pValue->DoGenIterator());
	if (!pIterator) return nullptr;
	processor.PushValue(new Value_Iterator(pIterator.release()));
	return _GetPUnitCont();
}

String PUnit_GenIterator::ToString(const StringStyle& ss) const
{
	String str;
	str += "GenIterator()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_GenRangeIterator
// Stack View: [ValueNumber] -> [ValueIterator]
//------------------------------------------------------------------------------
const PUnit* PUnit_GenRangeIterator::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		return _GetPUnitCont();
	}
	RefPtr<Value> pValue(processor.PopValue());
	int num = dynamic_cast<Value_Number*>(pValue.get())->GetInt();
	RefPtr<Iterator> pIterator(new Iterator_Range(num));
	processor.PushValue(new Value_Iterator(pIterator.release()));
	return _GetPUnitCont();
}

String PUnit_GenRangeIterator::ToString(const StringStyle& ss) const
{
	String str;
	str += "GenRangeIterator()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_EvalIterator
// Stack View: [ValueIterator] -> [ValueIterator ValueElem]
//------------------------------------------------------------------------------
const PUnit* PUnit_EvalIterator::Exec(Processor& processor) const
{
	Iterator& iterator =
		dynamic_cast<Value_Iterator*>(processor.PeekValue(_offset))->GetIterator();
	RefPtr<Value> pValueElem(iterator.NextValue());
	if (!pValueElem) return GetPUnitBranch();
	if (!GetPopValueToDiscardFlag()) {
		processor.PushValue(pValueElem.release());
	}
	return _GetPUnitCont();
}

String PUnit_EvalIterator::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("EvalIterator(%zu%s#%zu)", GetOffset(), ss.GetComma(), GetPUnitBranch()->GetSeqId());
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_UnaryOp
// Stack View: [Value] -> [ValueResult]
//------------------------------------------------------------------------------
const PUnit* PUnit_UnaryOp::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		return _GetPUnitCont();
	}
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Value> pValueResult(GetOperator()->EvalUnary(*pValue));
	if (pValueResult->IsUndefined()) return nullptr;
	processor.PushValue(pValueResult.release());
	return _GetPUnitCont();
}

String PUnit_UnaryOp::ToString(const StringStyle& ss) const
{
	String str;
	str += "UnaryOp(";
	str += GetOperator()->GetSymbol();
	str += ")";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_BinaryOp
// Stack View: [ValueLeft ValueRight] -> [ValueResult]
//------------------------------------------------------------------------------
const PUnit* PUnit_BinaryOp::Exec(Processor& processor) const
{
	RefPtr<Value> pValueRight(processor.PopValue());
	RefPtr<Value> pValueLeft(processor.PopValue());
	RefPtr<Value> pValueResult(GetOperator()->EvalBinary(*pValueLeft, *pValueRight));
	if (pValueResult->IsUndefined()) return nullptr;
	if (!GetPopValueToDiscardFlag()) {
		processor.PushValue(pValueResult.release());
	}
	return _GetPUnitCont();
}

String PUnit_BinaryOp::ToString(const StringStyle& ss) const
{
	String str;
	str += "BinaryOp(";
	str += GetOperator()->GetSymbol();
	str += ")";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Add
// Stack View: [ValueNumer] -> [ValueResult]
//------------------------------------------------------------------------------
const PUnit* PUnit_Add::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		return _GetPUnitCont();
	}
	RefPtr<Value> pValue(processor.PopValue());
	int num = dynamic_cast<Value_Number*>(pValue.get())->GetInt();
	processor.PushValue(new Value_Number(num + GetAdded()));
	return _GetPUnitCont();
}

String PUnit_Add::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Add(%d)", GetAdded());
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_CreateList
// Stack View: [] -> [ValueList]
//------------------------------------------------------------------------------
const PUnit* PUnit_CreateList::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) return _GetPUnitCont();
	RefPtr<ValueTypedOwner> pValueTypedOwner(new ValueTypedOwner());
	pValueTypedOwner->Reserve(GetSizeReserve());
	processor.PushValue(new Value_List(pValueTypedOwner.release()));
	return _GetPUnitCont();
}

String PUnit_CreateList::ToString(const StringStyle& ss) const
{
	String str;
	str += "CreateList()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_AddList
// Stack View: [ValueList ValueElem] -> [ValueList]
//------------------------------------------------------------------------------
const PUnit* PUnit_AddList::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		processor.PopValueToDiscard();
		return _GetPUnitCont();
	}
	RefPtr<Value> pValueElem(processor.PopValue());
	ValueTypedOwner& valueTypedOwner =
		dynamic_cast<Value_List*>(processor.PeekValue(0))->GetValueTypedOwner();
	valueTypedOwner.Add(pValueElem.release());
	return _GetPUnitCont();
}

String PUnit_AddList::ToString(const StringStyle& ss) const
{
	String str;
	str += "AddValueList()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_CreateDict
// Stack View: [] -> [ValueDict]
//------------------------------------------------------------------------------
const PUnit* PUnit_CreateDict::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) return _GetPUnitCont();
	processor.PushValue(new Value_Dict());
	return _GetPUnitCont();
}

String PUnit_CreateDict::ToString(const StringStyle& ss) const
{
	String str;
	str += "CreateDict()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_AddDict
// Stack View: [ValueDict ValueKey ValueElem] -> [ValueDict]
//------------------------------------------------------------------------------
const PUnit* PUnit_AddDict::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		processor.PopValueToDiscard();
		processor.PopValueToDiscard();
		return _GetPUnitCont();
	}
	RefPtr<Value> pValueElem(processor.PopValue());
	RefPtr<Value> pValueKey(processor.PopValue());
	ValueDict& valueDict =
		dynamic_cast<Value_Dict*>(processor.PeekValue(0))->GetValueDict();
	valueDict.Assign(pValueKey.release(), pValueElem.release());
	return _GetPUnitCont();
}

String PUnit_AddDict::ToString(const StringStyle& ss) const
{
	String str;
	str += "AddValueDict()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Index
// Stack View: [ValueCar] -> [ValueIndex(ValueCar)]
//------------------------------------------------------------------------------
const PUnit* PUnit_Index::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		return _GetPUnitCont();
	}
	RefPtr<Value> pValueCar(processor.PopValue());
	RefPtr<Index> pIndex(new Index(pValueCar.release(), GetAttr().Reference()));
	pIndex->Reserve(GetSizeReserve());
	processor.PushValue(new Value_Index(pIndex.release()));
	return _GetPUnitCont();
}

String PUnit_Index::ToString(const StringStyle& ss) const
{
	String str;
	str += "CreateIndex()";
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_FeedIndex
// Stack View: [ValueIndex Value] -> [ValueIndex]
//------------------------------------------------------------------------------
const PUnit* PUnit_FeedIndex::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		processor.PopValueToDiscard();
		return _GetPUnitCont();
	}
	RefPtr<Value> pValue(processor.PopValue());
	Index& index = dynamic_cast<Value_Index*>(processor.PeekValue(0))->GetIndex();
	index.FeedValue(pValue.release());
	if (Error::IsIssued()) {
		Error::GetErrorOwner().SetExpr(GetExprSrc());
		return nullptr;
	}
	return _GetPUnitCont();
}

String PUnit_FeedIndex::ToString(const StringStyle& ss) const
{
	String str;
	str += "FeedIndex()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_IndexGet
// Stack View: [ValueIndex] -> [ValueElems]
//------------------------------------------------------------------------------
const PUnit* PUnit_IndexGet::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		return _GetPUnitCont();
	}
	RefPtr<Value_Index> pValueIndex(dynamic_cast<Value_Index*>(processor.PopValue()));
	Index& index = pValueIndex->GetIndex();
	RefPtr<Value> pValueElems(index.IndexGet());
	if (Error::IsIssued()) {
		Error::GetErrorOwner().SetExpr(GetExprSrc());
		return nullptr;
	}
	processor.PushValue(pValueElems.release());
	return _GetPUnitCont();
}

String PUnit_IndexGet::ToString(const StringStyle& ss) const
{
	String str;
	str += "IndexGet()";
	AppendInfoToString(str, ss);
	return str;
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
	if (Error::IsIssued()) {
		Error::GetErrorOwner().SetExpr(GetExprSrc());
		return nullptr;
	}
	if (!GetPopValueToDiscardFlag()) processor.PushValue(pValueElems.release());
	return _GetPUnitCont();
}

String PUnit_IndexSet::ToString(const StringStyle& ss) const
{
	String str;
	str += "IndexSet()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_PropGet
// Stack View: [ValueTarget] -> [ValueTarget ValueProp]
//------------------------------------------------------------------------------
const PUnit* PUnit_PropGet::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		return _GetPUnitCont();
	}
	Value* pValueTarget = processor.PeekValue(0);
	Value* pValueProp = pValueTarget->DoPropGet(GetSymbol(), GetAttr());
	if (!pValueProp) {
		IssueError(ErrorType::ValueError, "symbol '%s' is not found", GetSymbol()->GetName());
		return nullptr;
	}
	processor.PushValue(pValueProp->Reference());
	return _GetPUnitCont();
}

String PUnit_PropGet::ToString(const StringStyle& ss) const
{
	String str;
	str += "PropGet(`";
	str += GetSymbol()->GetName();
	str += ")";
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_PropSet
// Stack View: [ValueTarget ValueProp] -> [ValueProp]
//------------------------------------------------------------------------------
const PUnit* PUnit_PropSet::Exec(Processor& processor) const
{
	RefPtr<Value> pValueProp(processor.PopValue());
	RefPtr<Value> pValueTarget(processor.PopValue());
	if (!pValueTarget->DoPropSet(GetSymbol(), pValueProp->Reference(), GetAttr())) {
		IssueError(ErrorType::ValueError, "failed to set value to symbol '%s'", GetSymbol()->GetName());
		return nullptr;
	}
	if (!GetPopValueToDiscardFlag()) processor.PushValue(pValueProp.release());
	return _GetPUnitCont();
}

String PUnit_PropSet::ToString(const StringStyle& ss) const
{
	String str;
	str += "PropSet(`";
	str += GetSymbol()->GetName();
	str += ")";
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Member
// Stack View: [ValueTarget] -> [ValueMember(ValueTarget+ValueProp)]
//             [ValueTarget] -> [ValueProp]
//------------------------------------------------------------------------------
const PUnit* PUnit_Member::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		return _GetPUnitCont();
	}
	RefPtr<Value> pValueTarget(processor.PopValue());
	Value* pValueProp = pValueTarget->DoPropGet(GetSymbol(), GetAttr());
	if (!pValueProp) {
		IssueError(ErrorType::ValueError, "symbol '%s' is not found", GetSymbol()->GetName());
		return nullptr;
	}
	if (pValueProp->IsCallable()) {
		processor.PushValue(new Value_Member(pValueTarget.release(), pValueProp->Reference()));
	} else {
		processor.PushValue(pValueProp->Reference());
	}
	return _GetPUnitCont();
}

String PUnit_Member::ToString(const StringStyle& ss) const
{
	String str;
	str += "Member(`";
	str += GetSymbol()->GetName();
	str += ")";
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
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
		new Argument(pValueCar.release(), pDeclCallable->Reference(),
					 GetAttr().Reference(), Value::nil(), Expr_Block::Reference(GetExprOfBlock())));
	processor.PushValue(new Value_Argument(pArgument.release()));
	return _GetPUnitCont();
}

String PUnit_Argument::ToString(const StringStyle& ss) const
{
	String str;
	str += "Argument()";
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
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
		Frame& frame = processor.GetFrameCur();
		argument.FeedValue(frame, new Value_Expr(GetExprSrc().Reference()));
		if (Error::IsIssued()) {
			Error::GetErrorOwner().SetExpr(GetExprSrc());
			return nullptr;
		}
		return GetPUnitBranch();
	} else {
		return _GetPUnitCont();
	}
}

String PUnit_ArgSlot::ToString(const StringStyle& ss) const
{
	String str;
	str += "ArgSlot(`(";
	str += GetExprSrc().ToString(StringStyle().Cram());
	str += ")";
	if (GetExprSrc().GetPUnitTop()) {
		str.Printf(":PUnit#%zu", GetExprSrc().GetPUnitTop()->GetSeqId());
	}
	str += ss.GetComma();
	str.Printf("#%zu, #%zu)", _GetPUnitCont()->GetSeqId(), GetPUnitBranch()->GetSeqId());
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_FeedArgSlot
// Stack View: [ValueArgument Value] -> [ValueArgument]
//------------------------------------------------------------------------------
const PUnit* PUnit_FeedArgSlot::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValue(processor.PopValue());
	Argument& argument = dynamic_cast<Value_Argument*>(processor.PeekValue(0))->GetArgument();
	argument.FeedValue(frame, pValue.release());
	if (Error::IsIssued()) {
		Error::GetErrorOwner().SetExpr(GetExprSrc());
		return nullptr;
	}
	return _GetPUnitCont();
}

String PUnit_FeedArgSlot::ToString(const StringStyle& ss) const
{
	String str;
	str += "FeedArgSlot()";
	AppendInfoToString(str, ss);
	return str;
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
			return _GetPUnitCont();
		} else {
			IssueError(ErrorType::ArgumentError, "can't find argument with a name: %s", GetSymbol()->GetName());
			return nullptr;
		}
	} else if (!pArgSlot->IsVacant()) {
		IssueError(ErrorType::ArgumentError, "duplicated assignment of argument");
		return nullptr;
	} else if (pArgSlot->IsVType(VTYPE_Quote)) {
		Frame& frame = processor.GetFrameCur();
		pArgSlot->FeedValue(frame, new Value_Expr(GetExprAssigned()->Reference()));
		if (Error::IsIssued()) {
			Error::GetErrorOwner().SetExpr(GetExprSrc());
			return nullptr;
		}
		return GetPUnitBranch();
	} else {
		processor.PushValue(new Value_ArgSlot(pArgSlot->Reference()));
		return _GetPUnitCont();
	}
}

String PUnit_ArgSlotNamed::ToString(const StringStyle& ss) const
{
	String str;
	str += "ArgSlotNamed(`";
	str += GetSymbol()->GetName();
	str += ss.IsCram()? "=>" : " => `(";
	str += GetExprSrc().ToString(StringStyle().Cram());
	str += ")";
	str += ss.GetComma();
	str.Printf("#%zu, #%zu)", _GetPUnitCont()->GetSeqId(), GetPUnitBranch()->GetSeqId());
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_FeedArgSlotNamed
// Stack View: [ValueArgSlot Value] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_FeedArgSlotNamed::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValue(processor.PopValue());
	ArgSlot& argSlot = dynamic_cast<Value_ArgSlot*>(processor.PopValue())->GetArgSlot();
	argSlot.FeedValue(frame, pValue.release());
	if (Error::IsIssued()) {
		Error::GetErrorOwner().SetExpr(GetExprSrc());
		return nullptr;
	}
	return _GetPUnitCont();
}

String PUnit_FeedArgSlotNamed::ToString(const StringStyle& ss) const
{
	String str;
	str += "FeedArgSlotNamed()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Call
// Stack View: [ValueArgument] -> [ValueResult]
//------------------------------------------------------------------------------
const PUnit* PUnit_Call::Exec(Processor& processor) const
{
	RefPtr<Value_Argument> pValue(dynamic_cast<Value_Argument*>(processor.PopValue()));
	Argument& argument = pValue->GetArgument();
	RefPtr<Value> pValueResult(argument.DoCall(processor));
	if (Error::IsIssued()) {
		Error::GetErrorOwner().SetExpr(GetExprSrc());
		return nullptr;
	}
	if (argument.GetPUnitCont()) {
		// PUnit_Return is responsible of PopValueToDiscard.
		processor.PushPUnit(this);
		return argument.GetPUnitCont();
	} else {
		if (!GetPopValueToDiscardFlag()) processor.PushValue(pValueResult.release());
		return _GetPUnitCont();
	}
}

String PUnit_Call::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Call(#%zu)", _GetPUnitCont()->GetSeqId());
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Jump
// Stack View: [] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_Jump::Exec(Processor& processor) const
{
	return _GetPUnitCont();
}

String PUnit_Jump::ToString(const StringStyle& ss) const
{
	String str;
	if (GetPopValueToDiscardFlag()) {
		str += "PopValueToDiscard()";
		str += ss.GetComma();
	}
	str.Printf("Jump(#%zu)", _GetPUnitCont()->GetSeqId());
	return str;
}

//------------------------------------------------------------------------------
// PUnit_JumpIf
// Stack View: [Value] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_JumpIf::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		return GetPUnitBranch();
	} else {
		if (GetPopValueToDiscardFlag()) processor.PopValueToDiscard();
		return _GetPUnitCont();
	}
}

String PUnit_JumpIf::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("JumpIf(#%zu)", GetPUnitBranch()->GetSeqId());
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_JumpIfNot
// Stack View: [Value] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_JumpIfNot::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		if (GetPopValueToDiscardFlag()) processor.PopValueToDiscard();
		return _GetPUnitCont();
	} else {
		return GetPUnitBranch();
	}
}

String PUnit_JumpIfNot::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("JumpIfNot(#%zu)", GetPUnitBranch()->GetSeqId());
	AppendInfoToString(str, ss);
	return str;
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
		return GetPUnitBranch();
	} else {
		if (GetPopValueToDiscardFlag()) processor.PopValueToDiscard();
		return _GetPUnitCont();
	}
}

String PUnit_NilJumpIf::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("NilJumpIf(#%zu)", GetPUnitBranch()->GetSeqId());
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_NilJumpIfNot
// Stack View: [Value] -> [] or [nil]
//------------------------------------------------------------------------------
const PUnit* PUnit_NilJumpIfNot::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		if (GetPopValueToDiscardFlag()) processor.PopValueToDiscard();
		return _GetPUnitCont();
	} else {
		processor.PushValue(Value::nil());
		return GetPUnitBranch();
	}
}

String PUnit_NilJumpIfNot::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("NilJumpIfNot(#%zu)", GetPUnitBranch()->GetSeqId());
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_ExitPoint
// Stack View: [] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_ExitPoint::Exec(Processor& processor) const
{
	return _GetPUnitCont();
}

String PUnit_ExitPoint::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("ExitPoint(#%zu)", GetPUnitExit()->GetSeqId());
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_PopValueToDiscard
// Stack View: [Value] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_PopValueToDiscard::Exec(Processor& processor) const
{
	processor.PopValueToDiscard();
	return _GetPUnitCont();
}

String PUnit_PopValueToDiscard::ToString(const StringStyle& ss) const
{
	String str;
	str += "PopValueToDiscard()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_RemoveValue
// Stack View: [.. Value ..] -> [.. ..]
//------------------------------------------------------------------------------
const PUnit* PUnit_RemoveValue::Exec(Processor& processor) const
{
	processor.RemoveValue(GetOffset());
	return _GetPUnitCont();
}

String PUnit_RemoveValue::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("RemoveValue(offset=%zu)", GetOffset());
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Return
// Stack View: [] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_Return::Exec(Processor& processor) const
{
	const PUnit* pPUnit = processor.PopPUnit();
	// Since nullptr means the end of the processor loop, there's no need to
	// pop frame or value from their stacks.
	if (!pPUnit) return nullptr;	
	processor.PopFrame();
	if (pPUnit->GetPopValueToDiscardFlag()) processor.PopValueToDiscard();
	return pPUnit->GetPUnitCont();
}

String PUnit_Return::ToString(const StringStyle& ss) const
{
	String str;
	str += "Return()";
	if (GetPopValueToDiscardFlag()) str += ", PopValueToDiscard()";
	return str;
}

//------------------------------------------------------------------------------
// PUnit_PushFrame_Block
// Stack View: [] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_PushFrame_Block::Exec(Processor& processor) const
{
	processor.PushFrame_Block();
	if (GetPopValueToDiscardFlag()) processor.PopValueToDiscard();
	return _GetPUnitCont();
}

String PUnit_PushFrame_Block::ToString(const StringStyle& ss) const
{
	String str;
	str += "PushFrame_Block()";
	if (GetPopValueToDiscardFlag()) str += ", PopValueToDiscard()";
	return str;
}

//------------------------------------------------------------------------------
// PUnit_PopFrame
// Stack View: [] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_PopFrame::Exec(Processor& processor) const
{
	processor.PopFrame();
	if (GetPopValueToDiscardFlag()) processor.PopValueToDiscard();
	return _GetPUnitCont();
}

String PUnit_PopFrame::ToString(const StringStyle& ss) const
{
	String str;
	str += "PopFrame()";
	if (GetPopValueToDiscardFlag()) str += ", PopValueToDiscard()";
	return str;
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
	String str;
	str += "Terminate()";
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Bridge
// Stack View: [] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_Bridge::Exec(Processor& processor) const
{
	return nullptr;
}

String PUnit_Bridge::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Bridge(#%zu)", _GetPUnitCont()->GetSeqId());
	return str;
}

}
