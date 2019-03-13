//==============================================================================
// PUnit.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PUnit
//------------------------------------------------------------------------------
int PUnit::_seqIdNext = 0;

PUnit::PUnit(Expr* pExprSrc, Flags flags) :
	_seqId(++_seqIdNext), _flags(flags), _pExprSrc(pExprSrc), _pPUnitCont(nullptr)
{
}

void PUnit::AppendInfoToString(String& str, const StringStyle& ss) const
{
	if (GetPopValueToDiscardFlag()) {
		str += ss.GetComma();
		str += "PopValueToDiscard()";
	}
	if (_pPUnitCont) {
		size_t seqIdNext = _pPUnitCont->GetSeqId();
		if (seqIdNext != GetSeqId() + 1) {
			str += ss.GetComma();
			str += "Jump(#";
			str += std::to_string(seqIdNext);
			str += ")";
		}
	} else {
		str += ss.GetComma();
		str += "Terminate()";
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
	if (!GetPopValueToDiscardFlag()) processor.PushValue(GetValue()->Reference());
	return GetPUnitCont();
}

String PUnit_Value::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Value(";
	rtn += GetValue()->ToString(StringStyle().Digest());
	rtn += ")";
	AppendInfoToString(rtn, ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Lookup
// Stack View: [] -> [Value]
//------------------------------------------------------------------------------
const PUnit* PUnit_Lookup::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) return GetPUnitCont();
	const Value* pValue = processor.GetFrameCur().LookupValue(GetSymbol());
	if (!pValue) {
		IssueError(ErrorType::ValueError, "symbol not found: %s", GetSymbol()->GetName());
		return nullptr;
	}
	processor.PushValue(pValue->Reference());
	return GetPUnitCont();
}

String PUnit_Lookup::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Lookup(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	AppendInfoToString(rtn, ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_AssignToSymbol
// Stack View: [ValueAssigned] -> [ValueAssigned]
//------------------------------------------------------------------------------
const PUnit* PUnit_AssignToSymbol::Exec(Processor& processor) const
{
	RefPtr<Value> pValueAssigned(
		GetPopValueToDiscardFlag()? processor.PopValue() : processor.PeekValue(0)->Reference());
	processor.GetFrameCur().AssignValue(GetSymbol(), pValueAssigned.release());
	return GetPUnitCont();
}

String PUnit_AssignToSymbol::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "AssignToSymbol(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	AppendInfoToString(rtn, ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_AssignToDeclArg
// Stack View: [ValueAssigned] -> [ValueCasted]
//------------------------------------------------------------------------------
const PUnit* PUnit_AssignToDeclArg::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValueAssigned(processor.PopValue());
	RefPtr<Value> pValueCasted(_pDeclArg->Cast(frame, *pValueAssigned));
	if (!pValueCasted) return nullptr;
	frame.AssignValueOfArgument(GetDeclArg().GetSymbol(), pValueCasted->Reference());
	if (!GetPopValueToDiscardFlag()) processor.PushValue(pValueCasted.release());
	return GetPUnitCont();
}

String PUnit_AssignToDeclArg::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "AssignToDeclArg(`";
	rtn += GetDeclArg().ToString(ss);
	rtn += ")";
	AppendInfoToString(rtn, ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_AssignFunction
// Stack View: [] -> [Value]
//------------------------------------------------------------------------------
const PUnit* PUnit_AssignFunction::Exec(Processor& processor) const
{
	RefPtr<Value> pValueAssigned(new Value_Function(GetFunction().Reference()));
	processor.GetFrameCur().AssignValue(GetFunction().GetSymbol(), pValueAssigned->Reference());
	if (!GetPopValueToDiscardFlag()) processor.PushValue(pValueAssigned->Reference());
	return GetPUnitCont();
}

String PUnit_AssignFunction::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "AssignFunction(";
	rtn += GetFunction().ToString(ss);
	rtn += ")";
	AppendInfoToString(rtn, ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Cast
// Stack View: [Value] -> [ValueResult]
//------------------------------------------------------------------------------
const PUnit* PUnit_Cast::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		return GetPUnitCont();
	}
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Value> pValueCasted(GetVType().Cast(*pValue));
	if (!pValueCasted) return nullptr;
	processor.PushValue(pValueCasted.release());
	return GetPUnitCont();
}

String PUnit_Cast::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Cast(";
	rtn += GetVType().MakeFullName().c_str();
	rtn += ")";
	AppendInfoToString(rtn, ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_UnaryOp
// Stack View: [Value] -> [ValueResult]
//------------------------------------------------------------------------------
const PUnit* PUnit_UnaryOp::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		return GetPUnitCont();
	}
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Value> pValueResult(GetOperator()->EvalUnary(*pValue));
	if (pValueResult->IsUndefined()) return nullptr;
	processor.PushValue(pValueResult.release());
	return GetPUnitCont();
}

String PUnit_UnaryOp::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "UnaryOp(";
	rtn += GetOperator()->GetSymbol();
	rtn += ")";
	AppendInfoToString(rtn, ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_BinaryOp
// Stack View: [ValueLeft ValueRight] -> [ValueResult]
//------------------------------------------------------------------------------
const PUnit* PUnit_BinaryOp::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		processor.PopValueToDiscard();
		return GetPUnitCont();
	}
	RefPtr<Value> pValueRight(processor.PopValue());
	RefPtr<Value> pValueLeft(processor.PopValue());
	RefPtr<Value> pValueResult(GetOperator()->EvalBinary(*pValueLeft, *pValueRight));
	if (pValueResult->IsUndefined()) return nullptr;
	processor.PushValue(pValueResult.release());
	return GetPUnitCont();
}

String PUnit_BinaryOp::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "BinaryOp(";
	rtn += GetOperator()->GetSymbol();
	rtn += ")";
	AppendInfoToString(rtn, ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Add
// Stack View: [Value] -> [ValueResult]
//------------------------------------------------------------------------------
const PUnit* PUnit_Add::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		return GetPUnitCont();
	}
	RefPtr<Value> pValue(processor.PopValue());
	int num = dynamic_cast<Value_Number*>(pValue.get())->GetInt();
	processor.PushValue(new Value_Number(num + GetAdded()));
	return GetPUnitCont();
}

String PUnit_Add::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Add(";
	rtn += std::to_string(GetAdded());
	rtn += ")";
	AppendInfoToString(rtn, ss);
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
	return GetPUnitCont();
}

String PUnit_CreateList::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "CreateList()";
	AppendInfoToString(rtn, ss);
	return rtn;
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
		return GetPUnitCont();
	}
	RefPtr<Value> pValueElem(processor.PopValue());
	ValueTypedOwner& valueTypedOwner =
		dynamic_cast<Value_List*>(processor.PeekValue(0))->GetValueTypedOwner();
	valueTypedOwner.Add(pValueElem.release());
	return GetPUnitCont();
}

String PUnit_AddList::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "AddValueList()";
	AppendInfoToString(rtn, ss);
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
	return GetPUnitCont();
}

String PUnit_Index::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "CreateIndex()";
	rtn += GetAttr().ToString(ss);
	AppendInfoToString(rtn, ss);
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
	return GetPUnitCont();
}

String PUnit_FeedIndex::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "FeedIndex()";
	AppendInfoToString(rtn, ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_IndexGet
// Stack View: [ValueIndex] -> [ValueElems]
//------------------------------------------------------------------------------
const PUnit* PUnit_IndexGet::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		return GetPUnitCont();
	}
	RefPtr<Value_Index> pValueIndex(dynamic_cast<Value_Index*>(processor.PopValue()));
	Index& index = pValueIndex->GetIndex();
	RefPtr<Value> pValueElems(index.IndexGet());
	if (Error::IsIssued()) return nullptr;
	processor.PushValue(pValueElems.release());
	return GetPUnitCont();
}

String PUnit_IndexGet::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "IndexGet()";
	AppendInfoToString(rtn, ss);
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
	if (!GetPopValueToDiscardFlag()) processor.PushValue(pValueElems.release());
	return GetPUnitCont();
}

String PUnit_IndexSet::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "IndexSet()";
	AppendInfoToString(rtn, ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_PropGet
// Stack View: [ValueTarget] -> [ValueTarget ValueProp]
//------------------------------------------------------------------------------
const PUnit* PUnit_PropGet::Exec(Processor& processor) const
{
	if (GetPopValueToDiscardFlag()) {
		processor.PopValueToDiscard();
		return GetPUnitCont();
	}
	Value* pValueTarget = processor.PeekValue(0);
	Value* pValueProp = pValueTarget->DoPropGet(GetSymbol(), GetAttr());
	if (!pValueProp) {
		IssueError(ErrorType::ValueError, "symbol not found: %s", GetSymbol()->GetName());
		return nullptr;
	}
	processor.PushValue(pValueProp->Reference());
	return GetPUnitCont();
}

String PUnit_PropGet::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "PropGet(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	rtn += GetAttr().ToString(ss);
	AppendInfoToString(rtn, ss);
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
	if (!GetPopValueToDiscardFlag()) processor.PushValue(pValueProp.release());
	return GetPUnitCont();
}

String PUnit_PropSet::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "PropSet(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	rtn += GetAttr().ToString(ss);
	AppendInfoToString(rtn, ss);
	return rtn;
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
		return GetPUnitCont();
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
	return GetPUnitCont();
}

String PUnit_Member::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Member(`";
	rtn += GetSymbol()->GetName();
	rtn += ")";
	rtn += GetAttr().ToString(ss);
	AppendInfoToString(rtn, ss);
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
		new Argument(pValueCar.release(), pDeclCallable->Reference(),
					 GetAttr().Reference(), Value::nil(), Expr_Block::Reference(GetExprBlock())));
	processor.PushValue(new Value_Argument(pArgument.release()));
	return GetPUnitCont();
}

String PUnit_Argument::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Argument()";
	rtn += GetAttr().ToString(ss);
	AppendInfoToString(rtn, ss);
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
		return GetPUnitBranch();
	} else {
		return GetPUnitCont();
	}
}

String PUnit_ArgSlot::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "ArgSlot(`(";
	rtn += GetExprSrc()->ToString(ss);
	rtn += ")";
	rtn += ss.GetComma();
	rtn += "#";
	rtn += std::to_string(GetPUnitBranch()->GetSeqId());
	rtn += ")";
	AppendInfoToString(rtn, ss);
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
	return GetPUnitCont();
}

String PUnit_FeedArgSlot::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "FeedArgSlot()";
	AppendInfoToString(rtn, ss);
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
			return GetPUnitCont();
		} else {
			IssueError(ErrorType::ArgumentError, "can't find argument with a name: %s", GetSymbol()->GetName());
			return nullptr;
		}
	} else if (!pArgSlot->IsVacant()) {
		IssueError(ErrorType::ArgumentError, "duplicated assignment of argument");
		return nullptr;
	} else if (pArgSlot->IsVType(VTYPE_Quote)) {
		pArgSlot->FeedValue(new Value_Expr(GetExprAssigned()->Reference()));
		return GetPUnitBranch();
	} else {
		processor.PushValue(new Value_ArgSlot(pArgSlot->Reference()));
		return GetPUnitCont();
	}
}

String PUnit_ArgSlotNamed::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "ArgSlotNamed(`";
	rtn += GetSymbol()->GetName();
	rtn += ss.IsCram()? "=>" : " => `(";
	rtn += GetExprSrc()->ToString(ss);
	rtn += ")";
	rtn += ss.GetComma();
	rtn += "#";
	rtn += std::to_string(GetPUnitBranch()->GetSeqId());
	rtn += ")";
	AppendInfoToString(rtn, ss);
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
	return GetPUnitCont();
}

String PUnit_FeedArgSlotNamed::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "FeedArgSlotNamed()";
	AppendInfoToString(rtn, ss);
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
	RefPtr<Value> pValueResult(argument.DoCall(processor));
	if (Error::IsIssued()) {
		for (auto pExpr : Error::GetErrorOwner()) pExpr->SetExpr(GetExprSrc()->Reference());
		return nullptr;
	}
	if (argument.GetPUnitCont()) {
		// PUnit_Return is responsible of PopValueToDiscard.
		processor.PushPUnit(this);
		return argument.GetPUnitCont();
	} else {
		if (!GetPopValueToDiscardFlag()) processor.PushValue(pValueResult.release());
		return GetPUnitCont();
	}
}

String PUnit_Call::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Call()";
	AppendInfoToString(rtn, ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Jump
// Stack View: [] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_Jump::Exec(Processor& processor) const
{
	return GetPUnitCont();
}

String PUnit_Jump::ToString(const StringStyle& ss) const
{
	String rtn;
	if (GetPopValueToDiscardFlag()) {
		rtn += "PopValueToDiscard()";
		rtn += ss.GetComma();
	}
	rtn += "Jump(#";
	rtn += std::to_string(GetPUnitCont()->GetSeqId());
	rtn += ")";
	return rtn;
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
		return GetPUnitCont();
	}
}

String PUnit_JumpIf::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "JumpIf(#";
	rtn += std::to_string(GetPUnitBranch()->GetSeqId());
	rtn += ")";
	AppendInfoToString(rtn, ss);
	return rtn;
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
		return GetPUnitCont();
	} else {
		return GetPUnitBranch();
	}
}

String PUnit_JumpIfNot::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "JumpIfNot(#";
	rtn += std::to_string(GetPUnitBranch()->GetSeqId());
	rtn += ")";
	AppendInfoToString(rtn, ss);
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
		return GetPUnitBranch();
	} else {
		if (GetPopValueToDiscardFlag()) processor.PopValueToDiscard();
		return GetPUnitCont();
	}
}

String PUnit_NilJumpIf::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "NilJumpIf(#";
	rtn += std::to_string(GetPUnitBranch()->GetSeqId());
	rtn += ")";
	AppendInfoToString(rtn, ss);
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
		if (GetPopValueToDiscardFlag()) processor.PopValueToDiscard();
		return GetPUnitCont();
	} else {
		processor.PushValue(Value::nil());
		return GetPUnitBranch();
	}
}

String PUnit_NilJumpIfNot::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "NilJumpIfNot(#";
	rtn += std::to_string(GetPUnitBranch()->GetSeqId());
	rtn += ")";
	AppendInfoToString(rtn, ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_PopValueToDiscard
// Stack View: [Value] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_PopValueToDiscard::Exec(Processor& processor) const
{
	processor.PopValueToDiscard();
	return GetPUnitCont();
}

String PUnit_PopValueToDiscard::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "PopValueToDiscard()";
	AppendInfoToString(rtn, ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_RemoveValue
// Stack View: [.. Value ..] -> [.. ..]
//------------------------------------------------------------------------------
const PUnit* PUnit_RemoveValue::Exec(Processor& processor) const
{
	processor.RemoveValue(GetOffset());
	return GetPUnitCont();
}

String PUnit_RemoveValue::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "RemoveValue(offset=";
	rtn += std::to_string(GetOffset());
	rtn += ")";
	AppendInfoToString(rtn, ss);
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_Return
// Stack View: [] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_Return::Exec(Processor& processor) const
{
	processor.PopFrame();
	const PUnit* pPUnit = processor.PopPUnit();
	if (!pPUnit) return nullptr;
	if (pPUnit->GetPopValueToDiscardFlag()) processor.PopValueToDiscard();
	return pPUnit->GetPUnitCont();
}

String PUnit_Return::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Return()";
	if (GetPopValueToDiscardFlag()) rtn += ", PopValueToDiscard()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_PushFrame_Block
// Stack View: [] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_PushFrame_Block::Exec(Processor& processor) const
{
	processor.PushFrame_Block();
	if (GetPopValueToDiscardFlag()) processor.PopValueToDiscard();
	return GetPUnitCont();
}

String PUnit_PushFrame_Block::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "PushFrame_Block()";
	if (GetPopValueToDiscardFlag()) rtn += ", PopValueToDiscard()";
	return rtn;
}

//------------------------------------------------------------------------------
// PUnit_PopFrame
// Stack View: [] -> []
//------------------------------------------------------------------------------
const PUnit* PUnit_PopFrame::Exec(Processor& processor) const
{
	processor.PopFrame();
	if (GetPopValueToDiscardFlag()) processor.PopValueToDiscard();
	return GetPUnitCont();
}

String PUnit_PopFrame::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "PopFrame()";
	if (GetPopValueToDiscardFlag()) rtn += ", PopValueToDiscard()";
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
	return rtn;
}

}
