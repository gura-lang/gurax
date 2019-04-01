//==============================================================================
// PUnit.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PUnit
//------------------------------------------------------------------------------
PUnit::PUnit(Expr* pExprSrc, SeqId seqId) :
	_pExprSrc(pExprSrc), _seqId(seqId), _flags(Flag::None)
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
	stream.Printf("%s%s %s\n", ss.GetMargin(),
				  MakeSeqIdString(seqIdOffset).c_str(), ToString(ss, seqIdOffset).c_str());
}

//------------------------------------------------------------------------------
// PUnitFactory
//------------------------------------------------------------------------------

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
// Iterator_EachPUnit
//------------------------------------------------------------------------------
Value* Iterator_EachPUnit::NextValue()
{
	if (!_pPUnit || _pPUnit == _pPUnitExit) return nullptr;
	for ( ; _pPUnit->IsBridge(); _pPUnit = _pPUnit->GetPUnitNext()) ;
	RefPtr<Value> pValue(new Value_PUnit(_pPUnit));
	_pPUnit = (_returnAsEndFlag && _pPUnit->IsReturn())? nullptr : _pPUnit->GetPUnitNext();
	return pValue.release();
}

size_t Iterator_EachPUnit::GetLength() const
{
	const PUnit* pPUnit = _pPUnit;
	if (!pPUnit || pPUnit == _pPUnitExit) return 0;
	for ( ; pPUnit->IsBridge(); pPUnit = _pPUnit->GetPUnitNext()) ;
	size_t cnt = 0;
	while (pPUnit) {
		cnt++;
		if (_returnAsEndFlag && pPUnit->IsReturn()) break;
		pPUnit = pPUnit->GetPUnitNext();
	}
	return cnt;
}

String Iterator_EachPUnit::ToString(const StringStyle& ss) const
{
	String str;
	str += "EachPUnit";
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Branch
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PUnit_Value
// Stack View: [] -> [Any] (continue)
//                -> []    (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_Value<discardValueFlag>::Exec(Processor& processor) const
{
	if (!GetDiscardValueFlag()) processor.PushValue(GetValue()->Reference());
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_Value<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Value(%s)", GetValue()->ToString(StringStyle().Digest()).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Value::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Value<true>(_pExprSrc.release(), _seqId, _pValue.release());
	} else {
		_pPUnitCreated = new PUnit_Value<false>(_pExprSrc.release(), _seqId, _pValue.release());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_ValueAndJump
// Stack View: [] -> [Any] (continue)
//                   []    (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_ValueAndJump<discardValueFlag>::Exec(Processor& processor) const
{
	if (!GetDiscardValueFlag()) processor.PushValue(GetValue()->Reference());
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_ValueAndJump<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("ValueAndJump(%s,cont=%s)",
			   GetValue()->ToString(StringStyle().Digest()).c_str(),
			   _GetPUnitCont()->MakeSeqIdString(seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_ValueAndJump::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_ValueAndJump<true>(_pExprSrc.release(), _seqId, _pValue.release());
	} else {
		_pPUnitCreated = new PUnit_ValueAndJump<false>(_pExprSrc.release(), _seqId, _pValue.release());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Lookup
// Stack View: [] -> [Any] (continue)
//                -> []    (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_Lookup<discardValueFlag>::Exec(Processor& processor) const
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

template<bool discardValueFlag>
String PUnit_Lookup<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "Lookup(`";
	str += GetSymbol()->GetName();
	str += ")";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Lookup::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Lookup<true>(_pExprSrc.release(), _seqId, _pSymbol);
	} else {
		_pPUnitCreated = new PUnit_Lookup<false>(_pExprSrc.release(), _seqId, _pSymbol);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_AssignToSymbol
// Stack View: [Assigned] -> [Assigned] (continue)
//                        -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_AssignToSymbol<discardValueFlag>::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValueAssigned(
		GetDiscardValueFlag()? processor.PopValue() : processor.PeekValue(0)->Reference());
	frame.Assign(GetSymbol(), pValueAssigned.release());
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_AssignToSymbol<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "AssignToSymbol(`";
	str += GetSymbol()->GetName();
	str += ")";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_AssignToSymbol::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_AssignToSymbol<true>(_pExprSrc.release(), _seqId, _pSymbol);
	} else {
		_pPUnitCreated = new PUnit_AssignToSymbol<false>(_pExprSrc.release(), _seqId, _pSymbol);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_AssignToDeclArg
// Stack View: [Assigned] -> [Assigned] (continue)
//                           []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_AssignToDeclArg<discardValueFlag>::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValueAssigned(
		GetDiscardValueFlag()? processor.PopValue() : processor.PeekValue(0)->Reference());
	frame.Assign(*_pDeclArg, *pValueAssigned);
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_AssignToDeclArg<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "AssignToDeclArg(`";
	str += GetDeclArg().ToString(ss);
	str += ")";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_AssignToDeclArg::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_AssignToDeclArg<true>(_pExprSrc.release(), _seqId, _pDeclArg.release());
	} else {
		_pPUnitCreated = new PUnit_AssignToDeclArg<false>(_pExprSrc.release(), _seqId, _pDeclArg.release());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_AssignFunction
// Stack View: [] -> [Function] (continue)
//                -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_AssignFunction<discardValueFlag>::Exec(Processor& processor) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValueAssigned(new Value_Function(GetFunction().Reference()));
	frame.Assign(GetFunction().GetSymbol(), pValueAssigned->Reference());
	if (!GetDiscardValueFlag()) processor.PushValue(pValueAssigned.release());
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_AssignFunction<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("AssignFunction(%s,cont=%s)",
			   GetFunction().ToString(ss).c_str(),
			   _GetPUnitCont()->MakeSeqIdString(seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_AssignFunction::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_AssignFunction<true>(_pExprSrc.release(), _seqId, _pFunction.release());
	} else {
		_pPUnitCreated = new PUnit_AssignFunction<false>(_pExprSrc.release(), _seqId, _pFunction.release());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Cast
// Stack View: [Any] -> [Casted] (continue)
//                   -> []       (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_Cast<discardValueFlag>::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Value> pValueCasted(GetVType().Cast(*pValue));
	if (!pValueCasted) return nullptr;
	if (!GetDiscardValueFlag()) processor.PushValue(pValueCasted.release());
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_Cast<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Cast(%s)", GetVType().MakeFullName().c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Cast::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Cast<true>(_pExprSrc.release(), _seqId, _vtype);
	} else {
		_pPUnitCreated = new PUnit_Cast<false>(_pExprSrc.release(), _seqId, _vtype);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_GenIterator
// Stack View: [Iterable] -> [Iterator] (continue)
//                        -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_GenIterator<discardValueFlag>::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Iterator> pIterator(pValue->DoGenIterator());
	if (!pIterator) return nullptr;
	if (!GetDiscardValueFlag()) processor.PushValue(new Value_Iterator(pIterator.release()));
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_GenIterator<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenIterator()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_GenIterator::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_GenIterator<true>(_pExprSrc.release(), _seqId);
	} else {
		_pPUnitCreated = new PUnit_GenIterator<false>(_pExprSrc.release(), _seqId);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_GenRangeIterator
// Stack View: [Number] -> [Iterator] (continue)
//                      -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_GenRangeIterator<discardValueFlag>::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	int num = dynamic_cast<Value_Number*>(pValue.get())->GetInt();
	RefPtr<Iterator> pIterator(new Iterator_Range(num));
	if (!GetDiscardValueFlag()) processor.PushValue(new Value_Iterator(pIterator.release()));
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_GenRangeIterator<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenRangeIterator()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_GenRangeIterator::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_GenRangeIterator<true>(_pExprSrc.release(), _seqId);
	} else {
		_pPUnitCreated = new PUnit_GenRangeIterator<false>(_pExprSrc.release(), _seqId);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_GenCounterIterator
// Stack View: [] -> [Iterator] (continue)
//                -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_GenCounterIterator<discardValueFlag>::Exec(Processor& processor) const
{
	RefPtr<Iterator> pIterator(new Iterator_Counter());
	if (!GetDiscardValueFlag()) processor.PushValue(new Value_Iterator(pIterator.release()));
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_GenCounterIterator<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenCounterIterator()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_GenCounterIterator::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_GenCounterIterator<true>(_pExprSrc.release(), _seqId);
	} else {
		_pPUnitCreated = new PUnit_GenCounterIterator<false>(_pExprSrc.release(), _seqId);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_EvalIterator
// Stack View: [Iterator] -> [Iterator Elem] (continue)
//                        -> [Iterator]      (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_EvalIterator<discardValueFlag>::Exec(Processor& processor) const
{
	Iterator& iterator =
		dynamic_cast<Value_Iterator*>(processor.PeekValue(GetOffset()))->GetIterator();
	RefPtr<Value> pValueElem(iterator.NextValue());
	if (!pValueElem) return GetPUnitBranchDest();
	if (!GetDiscardValueFlag()) processor.PushValue(pValueElem.release());
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_EvalIterator<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("EvalIterator(offset=%zu,branch=%s)", GetOffset(),
			   GetPUnitBranchDest()->MakeSeqIdString(seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_EvalIterator::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_EvalIterator<true>(_pExprSrc.release(), _seqId, _offset, _pPUnitBranchDest);
	} else {
		_pPUnitCreated = new PUnit_EvalIterator<false>(_pExprSrc.release(), _seqId, _offset, _pPUnitBranchDest);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_ForEach
// Stack View: [Iterator1..n ..] -> [Iterator1..n ..] (continue)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_ForEach<discardValueFlag>::Exec(Processor& processor) const
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

template<bool discardValueFlag>
String PUnit_ForEach<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("ForEach(offset=%zu,branch=%s)", GetOffset(),
			   GetPUnitBranchDest()->MakeSeqIdString(seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_ForEach::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_ForEach<true>(
			_pExprSrc.release(), _seqId, _offset, _pDeclArgOwner.release(), _pPUnitBranchDest);
	} else {
		_pPUnitCreated = new PUnit_ForEach<false>(
			_pExprSrc.release(), _seqId, _offset, _pDeclArgOwner.release(), _pPUnitBranchDest);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_UnaryOp
// Stack View: [Any] -> [Result] (continue)
//                   -> []       (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_UnaryOp<discardValueFlag>::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Value> pValueResult(GetOperator()->EvalUnary(*pValue));
	if (pValueResult->IsUndefined()) return nullptr;
	if (!GetDiscardValueFlag()) processor.PushValue(pValueResult.release());
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_UnaryOp<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("UnaryOp(%s)", GetOperator()->GetSymbol());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_UnaryOp::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_UnaryOp<true>(_pExprSrc.release(), _seqId, _pOperator);
	} else {
		_pPUnitCreated = new PUnit_UnaryOp<false>(_pExprSrc.release(), _seqId, _pOperator);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_BinaryOp
// Stack View: [Left Right] -> [Result] (continue)
//                          -> []       (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_BinaryOp<discardValueFlag>::Exec(Processor& processor) const
{
	RefPtr<Value> pValueRight(processor.PopValue());
	RefPtr<Value> pValueLeft(processor.PopValue());
	RefPtr<Value> pValueResult(GetOperator()->EvalBinary(*pValueLeft, *pValueRight));
	if (pValueResult->IsUndefined()) return nullptr;
	if (!GetDiscardValueFlag()) processor.PushValue(pValueResult.release());
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_BinaryOp<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("BinaryOp(%s)", GetOperator()->GetSymbol());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_BinaryOp::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_BinaryOp<true>(_pExprSrc.release(), _seqId, _pOperator);
	} else {
		_pPUnitCreated = new PUnit_BinaryOp<false>(_pExprSrc.release(), _seqId, _pOperator);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_CreateList
// Stack View: [] -> [List] (continue)
//                -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_CreateList<discardValueFlag>::Exec(Processor& processor) const
{
	RefPtr<ValueTypedOwner> pValueTypedOwner(new ValueTypedOwner());
	if (GetSizeReserve() > 0) pValueTypedOwner->Reserve(GetSizeReserve());
	if (!GetDiscardValueFlag()) processor.PushValue(new Value_List(pValueTypedOwner.release()));
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_CreateList<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "CreateList()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_CreateList::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_CreateList<true>(_pExprSrc.release(), _seqId, _sizeReserve);
	} else {
		_pPUnitCreated = new PUnit_CreateList<false>(_pExprSrc.release(), _seqId, _sizeReserve);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_ListElem
// Stack View: [List Elem] -> [List] (continue)
//                         -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_ListElem<discardValueFlag>::Exec(Processor& processor) const
{
	RefPtr<Value> pValueElem(processor.PopValue());
	ValueTypedOwner& valueTypedOwner =
		dynamic_cast<Value_List*>(processor.PeekValue(GetOffset()))->GetValueTypedOwner();
	valueTypedOwner.Add(pValueElem.release());
	if (GetDiscardValueFlag()) processor.PopValue();
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_ListElem<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("ListElem(offset=%zu)", GetOffset());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_ListElem::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_ListElem<true>(_pExprSrc.release(), _seqId, _offset);
	} else {
		_pPUnitCreated = new PUnit_ListElem<false>(_pExprSrc.release(), _seqId, _offset);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_CreateDict
// Stack View: [] -> [Dict] (continue)
//                -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_CreateDict<discardValueFlag>::Exec(Processor& processor) const
{
	if (!GetDiscardValueFlag()) processor.PushValue(new Value_Dict());
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_CreateDict<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "CreateDict()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_CreateDict::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_CreateDict<true>(_pExprSrc.release(), _seqId);
	} else {
		_pPUnitCreated = new PUnit_CreateDict<false>(_pExprSrc.release(), _seqId);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_DictElem
// Stack View: [Dict Key Elem] -> [Dict] (continue)
//                             -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_DictElem<discardValueFlag>::Exec(Processor& processor) const
{
	RefPtr<Value> pValueElem(processor.PopValue());
	RefPtr<Value> pValueKey(processor.PopValue());
	ValueDict& valueDict =
		dynamic_cast<Value_Dict*>(processor.PeekValue(GetOffset()))->GetValueDict();
	valueDict.Assign(pValueKey.release(), pValueElem.release());
	if (GetDiscardValueFlag()) processor.PopValue();
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_DictElem<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("DictElem(offset=%zu)", GetOffset());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_DictElem::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_DictElem<true>(_pExprSrc.release(), _seqId, _offset);
	} else {
		_pPUnitCreated = new PUnit_DictElem<false>(_pExprSrc.release(), _seqId, _offset);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Index
// Stack View: [Car] -> [Index(Car)] (continue)
//                   -> []           (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_Index<discardValueFlag>::Exec(Processor& processor) const
{
	RefPtr<Value> pValueCar(processor.PopValue());
	RefPtr<Index> pIndex(new Index(pValueCar.release(), GetAttr().Reference()));
	if (GetSizeReserve() > 0) pIndex->Reserve(GetSizeReserve());
	if (!GetDiscardValueFlag()) processor.PushValue(new Value_Index(pIndex.release()));
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_Index<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "CreateIndex()";
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Index::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Index<true>(_pExprSrc.release(), _seqId, _pAttr.release(), _sizeReserve);
	} else {
		_pPUnitCreated = new PUnit_Index<false>(_pExprSrc.release(), _seqId, _pAttr.release(), _sizeReserve);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_FeedIndex
// Stack View: [Index(Car) Any] -> [Index(Car)] (continue)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_FeedIndex<discardValueFlag>::Exec(Processor& processor) const
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

template<bool discardValueFlag>
String PUnit_FeedIndex<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "FeedIndex()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_FeedIndex::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_FeedIndex<true>(_pExprSrc.release(), _seqId);
	} else {
		_pPUnitCreated = new PUnit_FeedIndex<false>(_pExprSrc.release(), _seqId);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_IndexGet
// Stack View: [Index(Car)] -> [Elems] (continue)
//                          -> []      (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_IndexGet<discardValueFlag>::Exec(Processor& processor) const
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

template<bool discardValueFlag>
String PUnit_IndexGet<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "IndexGet()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_IndexGet::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_IndexGet<true>(_pExprSrc.release(), _seqId);
	} else {
		_pPUnitCreated = new PUnit_IndexGet<false>(_pExprSrc.release(), _seqId);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_IndexSet
// Stack View: [Index(Car) Elems] -> [Elems] (continue)
//                                -> []      (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_IndexSet<discardValueFlag>::Exec(Processor& processor) const
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

template<bool discardValueFlag>
String PUnit_IndexSet<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "IndexSet()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_IndexSet::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_IndexSet<true>(_pExprSrc.release(), _seqId);
	} else {
		_pPUnitCreated = new PUnit_IndexSet<false>(_pExprSrc.release(), _seqId);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_PropGet
// Stack View: [Target] -> [Target Prop] (continue)
//                      -> [Target]      (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_PropGet<discardValueFlag>::Exec(Processor& processor) const
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

template<bool discardValueFlag>
String PUnit_PropGet<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("PropGet(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_PropGet::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_PropGet<true>(_pExprSrc.release(), _seqId, _pSymbol, _pAttr.release());
	} else {
		_pPUnitCreated = new PUnit_PropGet<false>(_pExprSrc.release(), _seqId, _pSymbol, _pAttr.release());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_PropSet
// Stack View: [Target Assigned] -> [Assigned] (continue)
//                               -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_PropSet<discardValueFlag>::Exec(Processor& processor) const
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

template<bool discardValueFlag>
String PUnit_PropSet<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("PropSet(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_PropSet::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_PropSet<true>(_pExprSrc.release(), _seqId, _pSymbol, _pAttr.release());
	} else {
		_pPUnitCreated = new PUnit_PropSet<false>(_pExprSrc.release(), _seqId, _pSymbol, _pAttr.release());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Member
// Stack View: [Target] -> [Member(Target+Prop)] (continue, callable)
//                      -> [Prop]                (continue, not callable)
//                      -> []                    (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_Member<discardValueFlag>::Exec(Processor& processor) const
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

template<bool discardValueFlag>
String PUnit_Member<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Member(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Member::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Member<true>(_pExprSrc.release(), _seqId, _pSymbol, _pAttr.release());
	} else {
		_pPUnitCreated = new PUnit_Member<false>(_pExprSrc.release(), _seqId, _pSymbol, _pAttr.release());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Argument
// Stack View: [Car] -> [Argument(Car)] (continue)
//                   -> []              (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_Argument<discardValueFlag>::Exec(Processor& processor) const
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

template<bool discardValueFlag>
String PUnit_Argument<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "Argument()";
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Argument::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Argument<true>(
			_pExprSrc.release(), _seqId, _pAttr.release(), _pExprOfBlock.release());
	} else {
		_pPUnitCreated = new PUnit_Argument<false>(
			_pExprSrc.release(), _seqId, _pAttr.release(), _pExprOfBlock.release());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_ArgSlot
// Stack View: [Argument(Car)] -> [Argument(Car)] (continue)
//                             -> [Argument(Car)] (branch)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_ArgSlot<discardValueFlag>::Exec(Processor& processor) const
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

template<bool discardValueFlag>
String PUnit_ArgSlot<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("ArgSlot(`(%s)", GetExprSrc().ToString(StringStyle().Cram()).c_str());
	if (GetExprSrc().GetPUnitTop()) {
		str.Printf(":%s", GetExprSrc().GetPUnitTop()->MakeSeqIdString(seqIdOffset).c_str());
	}
	str.Printf(",cont=%s,branch=%s)",
			   _GetPUnitCont()->MakeSeqIdString(seqIdOffset).c_str(),
			   GetPUnitBranchDest()->MakeSeqIdString(seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_ArgSlot::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_ArgSlot<true>(_pExprSrc.release(), _seqId, _pPUnitBranchDest);
	} else {
		_pPUnitCreated = new PUnit_ArgSlot<false>(_pExprSrc.release(), _seqId, _pPUnitBranchDest);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_FeedArgSlot
// Stack View: [Argument(Car) Any] -> [Argument(Car)] (continue)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_FeedArgSlot<discardValueFlag>::Exec(Processor& processor) const
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

template<bool discardValueFlag>
String PUnit_FeedArgSlot<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "FeedArgSlot()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_FeedArgSlot::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_FeedArgSlot<true>(_pExprSrc.release(), _seqId);
	} else {
		_pPUnitCreated = new PUnit_FeedArgSlot<false>(_pExprSrc.release(), _seqId);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_ArgSlotNamed
// Stack View: [Argument(Car)] -> [Argument(Car) ArgSlot] (continue)
//                             -> [Argument(Car)]         (discard)
//                             -> [Argument(Car)]         (branch)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_ArgSlotNamed<discardValueFlag>::Exec(Processor& processor) const
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

template<bool discardValueFlag>
String PUnit_ArgSlotNamed<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("ArgSlotNamed(`%s=>%s,cont=%s,branch=%s)", GetSymbol()->GetName(),
			   GetExprSrc().ToString(StringStyle().Cram()).c_str(),
			   _GetPUnitCont()->MakeSeqIdString(seqIdOffset).c_str(),
			   GetPUnitBranchDest()->MakeSeqIdString(seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_ArgSlotNamed::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_ArgSlotNamed<true>(
			_pExprSrc.release(), _seqId, _pSymbol, _pExprAssigned.release(), _pPUnitBranchDest);
	} else {
		_pPUnitCreated = new PUnit_ArgSlotNamed<false>(
			_pExprSrc.release(), _seqId, _pSymbol, _pExprAssigned.release(), _pPUnitBranchDest);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_FeedArgSlotNamed
// Stack View: [Argument ArgSlot Any] -> [Argument] (continue)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_FeedArgSlotNamed<discardValueFlag>::Exec(Processor& processor) const
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

template<bool discardValueFlag>
String PUnit_FeedArgSlotNamed<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "FeedArgSlotNamed()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_FeedArgSlotNamed::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_FeedArgSlotNamed<true>(_pExprSrc.release(), _seqId);
	} else {
		_pPUnitCreated = new PUnit_FeedArgSlotNamed<false>(_pExprSrc.release(), _seqId);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Call
// Stack View: [Argument] -> [Result] (continue)
//                        -> []       (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_Call<discardValueFlag>::Exec(Processor& processor) const
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

template<bool discardValueFlag>
String PUnit_Call<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Call(cont=%s)", _GetPUnitCont()->MakeSeqIdString(seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Call::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Call<true>(_pExprSrc.release(), _seqId);
	} else {
		_pPUnitCreated = new PUnit_Call<false>(_pExprSrc.release(), _seqId);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Jump
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_Jump<discardValueFlag>::Exec(Processor& processor) const
{
	if (GetDiscardValueFlag()) processor.PopValue();
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_Jump<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Jump(%s)", _GetPUnitCont()->MakeSeqIdString(seqIdOffset).c_str());
	return str;
}

PUnit* PUnitFactory_Jump::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Jump<true>(_pExprSrc.release(), _seqId, _pPUnitCont);
	} else {
		_pPUnitCreated = new PUnit_Jump<false>(_pExprSrc.release(), _seqId, _pPUnitCont);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_JumpIf
// Stack View: [Prev Bool] -> [Prev] (continue)
//                         -> []     (discard)
//                         -> [Prev] (branch)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_JumpIf<discardValueFlag>::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		return GetPUnitBranchDest();
	} else {
		if (GetDiscardValueFlag()) processor.PopValue();
		return _GetPUnitCont();
	}
}

template<bool discardValueFlag>
String PUnit_JumpIf<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("JumpIf(branch=%s)", GetPUnitBranchDest()->MakeSeqIdString(seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_JumpIf::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_JumpIf<true>(_pExprSrc.release(), _seqId, _pPUnitBranchDest);
	} else {
		_pPUnitCreated = new PUnit_JumpIf<false>(_pExprSrc.release(), _seqId, _pPUnitBranchDest);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_JumpIfNot
// Stack View: [Prev Bool] -> [Prev]  (continue)
//                         -> []      (discard)
//                         -> [Prev]  (branch)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_JumpIfNot<discardValueFlag>::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		if (GetDiscardValueFlag()) processor.PopValue();
		return _GetPUnitCont();
	} else {
		return GetPUnitBranchDest();
	}
}

template<bool discardValueFlag>
String PUnit_JumpIfNot<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("JumpIfNot(branch=%s)", GetPUnitBranchDest()->MakeSeqIdString(seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_JumpIfNot::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_JumpIfNot<true>(_pExprSrc.release(), _seqId, _pPUnitBranchDest);
	} else {
		_pPUnitCreated = new PUnit_JumpIfNot<false>(_pExprSrc.release(), _seqId, _pPUnitBranchDest);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_NilJumpIf
// Stack View: [Prev Bool] -> [Prev]     (continue)
//                         -> []         (discard)
//                         -> [Prev Nil] (branch)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_NilJumpIf<discardValueFlag>::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		processor.PushValue(Value::nil());
		return GetPUnitBranchDest();
	} else {
		if (GetDiscardValueFlag()) processor.PopValue();
		return _GetPUnitCont();
	}
}

template<bool discardValueFlag>
String PUnit_NilJumpIf<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("NilJumpIf(branch=%s)", GetPUnitBranchDest()->MakeSeqIdString(seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_NilJumpIf::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_NilJumpIf<true>(_pExprSrc.release(), _seqId, _pPUnitBranchDest);
	} else {
		_pPUnitCreated = new PUnit_NilJumpIf<false>(_pExprSrc.release(), _seqId, _pPUnitBranchDest);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_NilJumpIfNot
// Stack View: [Prev Bool] -> [Prev]     (continue)
//                         -> []         (discard)
//                         -> [Prev Nil] (branch)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_NilJumpIfNot<discardValueFlag>::Exec(Processor& processor) const
{
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		if (GetDiscardValueFlag()) processor.PopValue();
		return _GetPUnitCont();
	} else {
		processor.PushValue(Value::nil());
		return GetPUnitBranchDest();
	}
}

template<bool discardValueFlag>
String PUnit_NilJumpIfNot<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("NilJumpIfNot(branch=%s)", GetPUnitBranchDest()->MakeSeqIdString(seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_NilJumpIfNot::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_NilJumpIfNot<true>(_pExprSrc.release(), _seqId, _pPUnitBranchDest);
	} else {
		_pPUnitCreated = new PUnit_NilJumpIfNot<false>(_pExprSrc.release(), _seqId, _pPUnitBranchDest);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_ExitPoint
// Stack View: [Prev] -> [Prev] (continue)
//                       []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_ExitPoint<discardValueFlag>::Exec(Processor& processor) const
{
	if (GetDiscardValueFlag()) processor.PopValue();
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_ExitPoint<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("ExitPoint(exit=%s)", GetPUnitExit()->MakeSeqIdString(seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_ExitPoint::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_ExitPoint<true>(_pExprSrc.release(), _seqId, _pPUnitExit);
	} else {
		_pPUnitCreated = new PUnit_ExitPoint<false>(_pExprSrc.release(), _seqId, _pPUnitExit);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_PopValue
// Stack View: [Prev Any] -> [Prev] (continue)
//                        -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_PopValue<discardValueFlag>::Exec(Processor& processor) const
{
	processor.PopValue();
	if (GetDiscardValueFlag()) processor.PopValue();
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_PopValue<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "PopValue()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_PopValue::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_PopValue<true>(_pExprSrc.release(), _seqId);
	} else {
		_pPUnitCreated = new PUnit_PopValue<false>(_pExprSrc.release(), _seqId);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_RemoveValue
// Stack View: [.. Any .. Prev] -> [.. .. Prev] (continue)
//                              -> [.. ..]      (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_RemoveValue<discardValueFlag>::Exec(Processor& processor) const
{
	processor.RemoveValue(GetOffset());
	if (GetDiscardValueFlag()) processor.PopValue();
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_RemoveValue<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("RemoveValue(offset=%zu)", GetOffset());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_RemoveValue::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_RemoveValue<true>(_pExprSrc.release(), _seqId, _offset);
	} else {
		_pPUnitCreated = new PUnit_RemoveValue<false>(_pExprSrc.release(), _seqId, _offset);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_RemoveValues
// Stack View: [.. Any1..n .. Prev] -> [.. .. Prev] (continue)
//                                  -> [.. ..]      (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_RemoveValues<discardValueFlag>::Exec(Processor& processor) const
{
	processor.RemoveValues(GetOffset(), GetCount());
	if (GetDiscardValueFlag()) processor.PopValue();
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_RemoveValues<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("RemoveValues(offset=%zu,count=%zu)", GetOffset(), GetCount());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_RemoveValues::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_RemoveValues<true>(_pExprSrc.release(), _seqId, _offset, _cnt);
	} else {
		_pPUnitCreated = new PUnit_RemoveValues<false>(_pExprSrc.release(), _seqId, _offset, _cnt);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Return
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_Return<discardValueFlag>::Exec(Processor& processor) const
{
	const PUnit* pPUnit = processor.PopPUnit();
	// Since nullptr means the end of the processor loop, there's no need to
	// pop frame or value from their stacks.
	if (!pPUnit) return nullptr;	
	processor.PopFrame();
	if (GetDiscardValueFlag()) processor.PopValue();
	return pPUnit->GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_Return<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "Return()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Return::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Return<true>(_pExprSrc.release(), _seqId);
	} else {
		_pPUnitCreated = new PUnit_Return<false>(_pExprSrc.release(), _seqId);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_PushFrame_Block
// Stack View: [prev] -> [prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_PushFrame_Block<discardValueFlag>::Exec(Processor& processor) const
{
	processor.PushFrame_Block();
	if (GetDiscardValueFlag()) processor.PopValue();
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_PushFrame_Block<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "PushFrame_Block()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_PushFrame_Block::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_PushFrame_Block<true>(_pExprSrc.release(), _seqId);
	} else {
		_pPUnitCreated = new PUnit_PushFrame_Block<false>(_pExprSrc.release(), _seqId);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_PopFrame
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_PopFrame<discardValueFlag>::Exec(Processor& processor) const
{
	processor.PopFrame();
	if (GetDiscardValueFlag()) processor.PopValue();
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_PopFrame<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "PopFrame()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_PopFrame::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_PopFrame<true>(_pExprSrc.release(), _seqId);
	} else {
		_pPUnitCreated = new PUnit_PopFrame<false>(_pExprSrc.release(), _seqId);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_NoOperation
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_NoOperation<discardValueFlag>::Exec(Processor& processor) const
{
	if (GetDiscardValueFlag()) processor.PopValue();
	return _GetPUnitCont();
}

template<bool discardValueFlag>
String PUnit_NoOperation<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "NoOperation()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_NoOperation::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_NoOperation<true>(_pExprSrc.release(), _seqId);
	} else {
		_pPUnitCreated = new PUnit_NoOperation<false>(_pExprSrc.release(), _seqId);
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Terminate
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
const PUnit* PUnit_Terminate<discardValueFlag>::Exec(Processor& processor) const
{
	if (GetDiscardValueFlag()) processor.PopValue();
	return nullptr;
}

template<bool discardValueFlag>
String PUnit_Terminate<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "Terminate()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Terminate::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Terminate<true>(_pExprSrc.release(), _seqId);
	} else {
		_pPUnitCreated = new PUnit_Terminate<false>(_pExprSrc.release(), _seqId);
	}
	return _pPUnitCreated;
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
	str.Printf("Bridge(cont=%s)", _GetPUnitCont()->MakeSeqIdString(seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

}
