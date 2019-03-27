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
	if (GetDiscardValueFlag()) {
		str += ss.GetComma();
		str += "DiscardValue()";
	}
}

void PUnit::Print(const StringStyle& ss, int seqIdOffset) const
{
	Stream& stream = *Stream::COut;
	stream.Printf("%s#%zu %s\n", ss.GetMargin(),
				  GetSeqId(seqIdOffset), ToString(ss, seqIdOffset).c_str());
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
// Stack View: [Prev] -> [Prev Any] (continue)
//                    -> [Prev]     (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_Value::Exec(Processor& processor) const
{
	if (!GetDiscardValueFlag()) processor.PushValue(GetValue()->Reference());
	return _GetPUnitCont();
}

String PUnit_Value::ToString(const StringStyle& ss, int seqIdOffset) const
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
// Stack View: [Prev] -> [Prev Any] (continue)
//                       [Prev]     (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_ValueAndJump::Exec(Processor& processor) const
{
	if (!GetDiscardValueFlag()) processor.PushValue(GetValue()->Reference());
	return _GetPUnitCont();
}

String PUnit_ValueAndJump::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "ValueAndJump(";
	str += GetValue()->ToString(StringStyle().Digest());
	str.Printf(", #%zu)", _GetPUnitCont()->GetSeqId(seqIdOffset));
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Lookup
// Stack View: [Prev] -> [Prev Any] (continue)
//                    -> [Prev]     (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_Lookup::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrameCur();
	const Value* pValue = frame.Lookup(GetSymbol());
	if (!pValue) {
		IssueError(ErrorType::ValueError, "symbol '%s' is not found", GetSymbol()->GetName());
		return nullptr;
	}
	if (!GetDiscardValueFlag()) processor.PushValue(pValue->Reference());
	return _GetPUnitCont();
}

String PUnit_Lookup::ToString(const StringStyle& ss, int seqIdOffset) const
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
// Stack View: [Prev Assigned] -> [Prev Assigned] (continue)
//                             -> [Prev]          (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_AssignToSymbol::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValueAssigned(
		GetDiscardValueFlag()? processor.PopValue() : processor.PeekValue(0)->Reference());
	frame.Assign(GetSymbol(), pValueAssigned.release());
	return _GetPUnitCont();
}

String PUnit_AssignToSymbol::ToString(const StringStyle& ss, int seqIdOffset) const
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
// Stack View: [Prev Assigned] -> [Prev Assigned] (continue)
//                                [Prev]          (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_AssignToDeclArg::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValueAssigned(
		GetDiscardValueFlag()? processor.PopValue() : processor.PeekValue(0)->Reference());
	frame.Assign(*_pDeclArg, *pValueAssigned);
	return _GetPUnitCont();
}

String PUnit_AssignToDeclArg::ToString(const StringStyle& ss, int seqIdOffset) const
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
// Stack View: [Prev] -> [Prev Function] (continue)
//                    -> [Prev]          (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_AssignFunction::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValueAssigned(new Value_Function(GetFunction().Reference()));
	frame.Assign(GetFunction().GetSymbol(), pValueAssigned->Reference());
	if (!GetDiscardValueFlag()) processor.PushValue(pValueAssigned.release());
	return _GetPUnitCont();
}

String PUnit_AssignFunction::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "AssignFunction(";
	str += GetFunction().ToString(ss);
	str.Printf(", #%zu)", _GetPUnitCont()->GetSeqId(seqIdOffset));
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Cast
// Stack View: [Prev Any] -> [Prev Casted] (continue)
//                        -> [Prev]        (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_Cast::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Value> pValueCasted(GetVType().Cast(*pValue));
	if (!pValueCasted) return nullptr;
	if (!GetDiscardValueFlag()) processor.PushValue(pValueCasted.release());
	return _GetPUnitCont();
}

String PUnit_Cast::ToString(const StringStyle& ss, int seqIdOffset) const
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
// Stack View: [Prev Iterable] -> [Prev Iterator] (continue)
//                             -> [Prev]          (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_GenIterator::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Iterator> pIterator(pValue->DoGenIterator());
	if (!pIterator) return nullptr;
	if (!GetDiscardValueFlag()) processor.PushValue(new Value_Iterator(pIterator.release()));
	return _GetPUnitCont();
}

String PUnit_GenIterator::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenIterator()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_GenRangeIterator
// Stack View: [Prev Number] -> [Prev Iterator] (continue)
//                           -> [Prev]          (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_GenRangeIterator::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	int num = dynamic_cast<Value_Number*>(pValue.get())->GetInt();
	RefPtr<Iterator> pIterator(new Iterator_Range(num));
	if (!GetDiscardValueFlag()) processor.PushValue(new Value_Iterator(pIterator.release()));
	return _GetPUnitCont();
}

String PUnit_GenRangeIterator::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenRangeIterator()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_GenCounterIterator
// Stack View: [Prev] -> [Prev Iterator] (continue)
//                    -> [Prev]          (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_GenCounterIterator::Exec(Processor& processor) const
{
	RefPtr<Iterator> pIterator(new Iterator_Counter());
	if (!GetDiscardValueFlag()) processor.PushValue(new Value_Iterator(pIterator.release()));
	return _GetPUnitCont();
}

String PUnit_GenCounterIterator::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenCounterIterator()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_EvalIterator
// Stack View: [Prev Iterator] -> [Prev Iterator Elem] (continue)
//                             -> [Prev Iterator]      (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_EvalIterator::Exec(Processor& processor) const
{
	Iterator& iterator =
		dynamic_cast<Value_Iterator*>(processor.PeekValue(GetOffset()))->GetIterator();
	RefPtr<Value> pValueElem(iterator.NextValue());
	if (!pValueElem) return GetPUnitBranchDest();
	if (!GetDiscardValueFlag()) processor.PushValue(pValueElem.release());
	return _GetPUnitCont();
}

String PUnit_EvalIterator::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("EvalIterator(%zu%s#%zu)", GetOffset(), ss.GetComma(), GetPUnitBranchDest()->GetSeqId(seqIdOffset));
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_ForEach
// Stack View: [Prev Iterator1..n ..] -> [Prev Iterator1..n ..] (continue)
//------------------------------------------------------------------------------
const PUnit* PUnit_ForEach::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrameCur();
	size_t offset = GetOffset() + GetDeclArgOwner().size() - 1;
	for (DeclArg* pDeclArg : GetDeclArgOwner()) {
		Iterator& iterator =
			dynamic_cast<Value_Iterator*>(processor.PeekValue(offset))->GetIterator();
		RefPtr<Value> pValueElem(iterator.NextValue());
		if (!pValueElem) return GetPUnitBranchDest();
		frame.Assign(*pDeclArg, *pValueElem);
		offset--;
	}
	return _GetPUnitCont();
}

String PUnit_ForEach::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("ForEach(offset=%zu%s#%zu)", GetOffset(),
			   ss.GetComma(), GetPUnitBranchDest()->GetSeqId(seqIdOffset));
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_UnaryOp
// Stack View: [Prev Any] -> [Prev Result] (continue)
//                        -> [Prev]        (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_UnaryOp::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Value> pValueResult(GetOperator()->EvalUnary(*pValue));
	if (pValueResult->IsUndefined()) return nullptr;
	if (!GetDiscardValueFlag()) processor.PushValue(pValueResult.release());
	return _GetPUnitCont();
}

String PUnit_UnaryOp::ToString(const StringStyle& ss, int seqIdOffset) const
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
// Stack View: [Prev Left Right] -> [Prev Result] (continue)
//                               -> [Prev]        (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_BinaryOp::Exec(Processor& processor) const
{
	RefPtr<Value> pValueRight(processor.PopValue());
	RefPtr<Value> pValueLeft(processor.PopValue());
	RefPtr<Value> pValueResult(GetOperator()->EvalBinary(*pValueLeft, *pValueRight));
	if (pValueResult->IsUndefined()) return nullptr;
	if (!GetDiscardValueFlag()) processor.PushValue(pValueResult.release());
	return _GetPUnitCont();
}

String PUnit_BinaryOp::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "BinaryOp(";
	str += GetOperator()->GetSymbol();
	str += ")";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_CreateList
// Stack View: [Prev] -> [Prev List] (continue)
//                    -> [Prev]      (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_CreateList::Exec(Processor& processor) const
{
	RefPtr<ValueTypedOwner> pValueTypedOwner(new ValueTypedOwner());
	if (GetSizeReserve() > 0) pValueTypedOwner->Reserve(GetSizeReserve());
	if (!GetDiscardValueFlag()) processor.PushValue(new Value_List(pValueTypedOwner.release()));
	return _GetPUnitCont();
}

String PUnit_CreateList::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "CreateList()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_ListElem
// Stack View: [Prev List Elem] -> [Prev List] (continue)
//                              -> [Prev]      (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_ListElem::Exec(Processor& processor) const
{
	RefPtr<Value> pValueElem(processor.PopValue());
	ValueTypedOwner& valueTypedOwner =
		dynamic_cast<Value_List*>(processor.PeekValue(GetOffset()))->GetValueTypedOwner();
	valueTypedOwner.Add(pValueElem.release());
	if (GetDiscardValueFlag()) processor.PopValue();
	return _GetPUnitCont();
}

String PUnit_ListElem::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("ListElem(offset=%zu)", GetOffset());
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_CreateDict
// Stack View: [Prev] -> [Prev Dict] (continue)
//                    -> [Prev]      (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_CreateDict::Exec(Processor& processor) const
{
	if (!GetDiscardValueFlag()) processor.PushValue(new Value_Dict());
	return _GetPUnitCont();
}

String PUnit_CreateDict::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "CreateDict()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_DictElem
// Stack View: [Prev Dict Key Elem] -> [Prev Dict] (continue)
//                                  -> [Prev]      (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_DictElem::Exec(Processor& processor) const
{
	RefPtr<Value> pValueElem(processor.PopValue());
	RefPtr<Value> pValueKey(processor.PopValue());
	ValueDict& valueDict =
		dynamic_cast<Value_Dict*>(processor.PeekValue(GetOffset()))->GetValueDict();
	valueDict.Assign(pValueKey.release(), pValueElem.release());
	if (GetDiscardValueFlag()) processor.PopValue();
	return _GetPUnitCont();
}

String PUnit_DictElem::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("DictElem(offset=%zu)", GetOffset());
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Index
// Stack View: [Prev Car] -> [Prev Index(Car)] (continue)
//                        -> [Prev]            (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_Index::Exec(Processor& processor) const
{
	RefPtr<Value> pValueCar(processor.PopValue());
	RefPtr<Index> pIndex(new Index(pValueCar.release(), GetAttr().Reference()));
	if (GetSizeReserve() > 0) pIndex->Reserve(GetSizeReserve());
	if (!GetDiscardValueFlag()) processor.PushValue(new Value_Index(pIndex.release()));
	return _GetPUnitCont();
}

String PUnit_Index::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "CreateIndex()";
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_FeedIndex
// Stack View: [Prev Index(Car) Any] -> [Prev Index(Car)] (continue)
//------------------------------------------------------------------------------
const PUnit* PUnit_FeedIndex::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	Index& index = dynamic_cast<Value_Index*>(processor.PeekValue(0))->GetIndex();
	index.FeedValue(pValue.release());
	if (Error::IsIssued()) {
		Error::GetErrorOwner().SetExpr(GetExprSrc());
		return nullptr;
	}
	return _GetPUnitCont();
}

String PUnit_FeedIndex::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "FeedIndex()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_IndexGet
// Stack View: [Prev Index(Car)] -> [Prev Elems] (continue)
//                               -> [Prev]       (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_IndexGet::Exec(Processor& processor) const
{
	RefPtr<Value_Index> pValueIndex(dynamic_cast<Value_Index*>(processor.PopValue()));
	Index& index = pValueIndex->GetIndex();
	RefPtr<Value> pValueElems(index.IndexGet());
	if (Error::IsIssued()) {
		Error::GetErrorOwner().SetExpr(GetExprSrc());
		return nullptr;
	}
	if (!GetDiscardValueFlag()) processor.PushValue(pValueElems.release());
	return _GetPUnitCont();
}

String PUnit_IndexGet::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "IndexGet()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_IndexSet
// Stack View: [Prev Index(Car) Elems] -> [Prev Elems] (continue)
//                                     -> [Prev]       (discard)
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
	if (!GetDiscardValueFlag()) processor.PushValue(pValueElems.release());
	return _GetPUnitCont();
}

String PUnit_IndexSet::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "IndexSet()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_PropGet
// Stack View: [Prev Target] -> [Prev Target Prop] (continue)
//                           -> [Prev Target]      (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_PropGet::Exec(Processor& processor) const
{
	Value* pValueTarget = processor.PeekValue(0);
	Value* pValueProp = pValueTarget->DoPropGet(GetSymbol(), GetAttr());
	if (!pValueProp) {
		IssueError(ErrorType::ValueError, "symbol '%s' is not found", GetSymbol()->GetName());
		return nullptr;
	}
	if (!GetDiscardValueFlag()) processor.PushValue(pValueProp->Reference());
	return _GetPUnitCont();
}

String PUnit_PropGet::ToString(const StringStyle& ss, int seqIdOffset) const
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
// Stack View: [Prev Target Assigned] -> [Prev Assigned] (continue)
//                                    -> [Prev]          (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_PropSet::Exec(Processor& processor) const
{
	RefPtr<Value> pValueProp(processor.PopValue());
	RefPtr<Value> pValueTarget(processor.PopValue());
	if (!pValueTarget->DoPropSet(GetSymbol(), pValueProp->Reference(), GetAttr())) {
		IssueError(ErrorType::ValueError, "failed to set value to symbol '%s'", GetSymbol()->GetName());
		return nullptr;
	}
	if (!GetDiscardValueFlag()) processor.PushValue(pValueProp.release());
	return _GetPUnitCont();
}

String PUnit_PropSet::ToString(const StringStyle& ss, int seqIdOffset) const
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
// Stack View: [Prev Target] -> [Prev Member(Target+Prop)] (continue, callable)
//                           -> [Prev Prop]                (continue, not callable)
//                           -> [Prev]                     (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_Member::Exec(Processor& processor) const
{
	RefPtr<Value> pValueTarget(processor.PopValue());
	Value* pValueProp = pValueTarget->DoPropGet(GetSymbol(), GetAttr());
	if (!pValueProp) {
		IssueError(ErrorType::ValueError, "symbol '%s' is not found", GetSymbol()->GetName());
		return nullptr;
	}
	if (GetDiscardValueFlag()) {
		// nothing to do
	} else if (pValueProp->IsCallable()) {
		processor.PushValue(new Value_Member(pValueTarget.release(), pValueProp->Reference()));
	} else {
		processor.PushValue(pValueProp->Reference());
	}
	return _GetPUnitCont();
}

String PUnit_Member::ToString(const StringStyle& ss, int seqIdOffset) const
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
// Stack View: [Prev Car] -> [Prev Argument(Car)] (continue)
//                        -> [Prev]               (discard)
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
	if (!GetDiscardValueFlag()) processor.PushValue(new Value_Argument(pArgument.release()));
	return _GetPUnitCont();
}

String PUnit_Argument::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "Argument()";
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_ArgSlot
// Stack View: [Prev Argument(Car)] -> [Prev Argument(Car)] (continue)
//                                  -> [Prev Argument(Car)] (branch)
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
		return GetPUnitBranchDest();
	} else {
		return _GetPUnitCont();
	}
}

String PUnit_ArgSlot::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "ArgSlot(`(";
	str += GetExprSrc().ToString(StringStyle().Cram());
	str += ")";
	if (GetExprSrc().GetPUnitTop()) {
		str.Printf(":PUnit#%zu", GetExprSrc().GetPUnitTop()->GetSeqId(seqIdOffset));
	}
	str += ss.GetComma();
	str.Printf("#%zu, #%zu)", _GetPUnitCont()->GetSeqId(seqIdOffset), GetPUnitBranchDest()->GetSeqId(seqIdOffset));
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_FeedArgSlot
// Stack View: [Prev Argument(Car) Any] -> [Prev Argument(Car)] (continue)
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

String PUnit_FeedArgSlot::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "FeedArgSlot()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_ArgSlotNamed
// Stack View: [Prev Argument(Car)] -> [Prev Argument(Car) ArgSlot] (continue)
//                                  -> [Prev Argument(Car)]         (discard)
//                                  -> [Prev Argument(Car)]         (branch)
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
		return GetPUnitBranchDest();
	} else {
		if (!GetDiscardValueFlag()) processor.PushValue(new Value_ArgSlot(pArgSlot->Reference()));
		return _GetPUnitCont();
	}
}

String PUnit_ArgSlotNamed::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "ArgSlotNamed(`";
	str += GetSymbol()->GetName();
	str += ss.IsCram()? "=>" : " => `(";
	str += GetExprSrc().ToString(StringStyle().Cram());
	str += ")";
	str += ss.GetComma();
	str.Printf("#%zu, #%zu)", _GetPUnitCont()->GetSeqId(seqIdOffset), GetPUnitBranchDest()->GetSeqId(seqIdOffset));
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_FeedArgSlotNamed
// Stack View: [Prev Argument ArgSlot Any] -> [Prev Argument] (continue)
//                                         -> [Prev Argument] (discard)
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

String PUnit_FeedArgSlotNamed::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "FeedArgSlotNamed()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Call
// Stack View: [Prev Argument] -> [Prev Result] (continue)
//                             -> [Prev]        (discard)
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
		// PUnit_Return is responsible of DiscardValue.
		processor.PushPUnit(this);
		return argument.GetPUnitCont();
	} else {
		if (!GetDiscardValueFlag()) processor.PushValue(pValueResult.release());
		return _GetPUnitCont();
	}
}

String PUnit_Call::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Call(#%zu)", _GetPUnitCont()->GetSeqId(seqIdOffset));
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Jump
// Stack View: [Prev] -> [Prev] (continue)
//------------------------------------------------------------------------------
const PUnit* PUnit_Jump::Exec(Processor& processor) const
{
	return _GetPUnitCont();
}

String PUnit_Jump::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Jump(#%zu)", _GetPUnitCont()->GetSeqId(seqIdOffset));
	return str;
}

//------------------------------------------------------------------------------
// PUnit_JumpIf
// Stack View: [Prev Bool] -> [Prev] (continue)
//                         -> [Prev] (branch)
//------------------------------------------------------------------------------
const PUnit* PUnit_JumpIf::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		return GetPUnitBranchDest();
	} else {
		return _GetPUnitCont();
	}
}

String PUnit_JumpIf::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("JumpIf(#%zu)", GetPUnitBranchDest()->GetSeqId(seqIdOffset));
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_JumpIfNot
// Stack View: [Prev Bool] -> [Prev]  (continue)
//                         -> [Prev]  (branch)
//------------------------------------------------------------------------------
const PUnit* PUnit_JumpIfNot::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		return _GetPUnitCont();
	} else {
		return GetPUnitBranchDest();
	}
}

String PUnit_JumpIfNot::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("JumpIfNot(#%zu)", GetPUnitBranchDest()->GetSeqId(seqIdOffset));
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_NilJumpIf
// Stack View: [Prev Bool] -> [Prev]     (continue)
//                         -> [Prev Nil] (branch)
//------------------------------------------------------------------------------
const PUnit* PUnit_NilJumpIf::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		processor.PushValue(Value::nil());
		return GetPUnitBranchDest();
	} else {
		return _GetPUnitCont();
	}
}

String PUnit_NilJumpIf::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("NilJumpIf(#%zu)", GetPUnitBranchDest()->GetSeqId(seqIdOffset));
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_NilJumpIfNot
// Stack View: [Prev Bool] -> [Prev]     (continue)
//                         -> [Prev Nil] (branch)
//------------------------------------------------------------------------------
const PUnit* PUnit_NilJumpIfNot::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		return _GetPUnitCont();
	} else {
		processor.PushValue(Value::nil());
		return GetPUnitBranchDest();
	}
}

String PUnit_NilJumpIfNot::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("NilJumpIfNot(#%zu)", GetPUnitBranchDest()->GetSeqId(seqIdOffset));
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_ExitPoint
// Stack View: [Prev] -> [Prev] (always)
//------------------------------------------------------------------------------
const PUnit* PUnit_ExitPoint::Exec(Processor& processor) const
{
	return _GetPUnitCont();
}

String PUnit_ExitPoint::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("ExitPoint(#%zu)", GetPUnitExit()->GetSeqId(seqIdOffset));
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_PopValue
// Stack View: [Prev] -> [] (always)
//------------------------------------------------------------------------------
const PUnit* PUnit_PopValue::Exec(Processor& processor) const
{
	processor.PopValue();
	return _GetPUnitCont();
}

String PUnit_PopValue::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "PopValue()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_RemoveValue
// Stack View: [.. Any ..] -> [.. ..] (always)
//------------------------------------------------------------------------------
const PUnit* PUnit_RemoveValue::Exec(Processor& processor) const
{
	processor.RemoveValue(GetOffset());
	return _GetPUnitCont();
}

String PUnit_RemoveValue::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("RemoveValue(offset=%zu)", GetOffset());
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_RemoveValues
// Stack View: [.. Any1..n ..] -> [.. ..] (always)
//------------------------------------------------------------------------------
const PUnit* PUnit_RemoveValues::Exec(Processor& processor) const
{
	processor.RemoveValues(GetOffset(), GetCount());
	return _GetPUnitCont();
}

String PUnit_RemoveValues::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("RemoveValues(offset=%zu%scount=%zu)", GetOffset(), ss.GetComma(), GetCount());
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Return
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_Return::Exec(Processor& processor) const
{
	const PUnit* pPUnit = processor.PopPUnit();
	// Since nullptr means the end of the processor loop, there's no need to
	// pop frame or value from their stacks.
	if (!pPUnit) return nullptr;	
	processor.PopFrame();
	if (pPUnit->GetDiscardValueFlag()) processor.PopValue();
	return pPUnit->GetPUnitCont();
}

String PUnit_Return::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "Return()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_PushFrame_Block
// Stack View: [prev] -> [prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_PushFrame_Block::Exec(Processor& processor) const
{
	processor.PushFrame_Block();
	if (GetDiscardValueFlag()) processor.PopValue();
	return _GetPUnitCont();
}

String PUnit_PushFrame_Block::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "PushFrame_Block()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_PopFrame
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_PopFrame::Exec(Processor& processor) const
{
	processor.PopFrame();
	if (GetDiscardValueFlag()) processor.PopValue();
	return _GetPUnitCont();
}

String PUnit_PopFrame::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "PopFrame()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Terminate
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_Terminate::Exec(Processor& processor) const
{
	if (GetDiscardValueFlag()) processor.PopValue();
	return nullptr;
}

String PUnit_Terminate::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "Terminate()";
	AppendInfoToString(str, ss);
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Bridge
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
const PUnit* PUnit_Bridge::Exec(Processor& processor) const
{
	if (GetDiscardValueFlag()) processor.PopValue();
	return _GetPUnitCont();
}

String PUnit_Bridge::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Bridge(#%zu)", _GetPUnitCont()->GetSeqId(seqIdOffset));
	AppendInfoToString(str, ss);
	return str;
}

}
