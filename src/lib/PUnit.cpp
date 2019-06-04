//==============================================================================
// PUnit.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PUnit
//------------------------------------------------------------------------------
PUnit::PUnit()
{
}

String PUnit::MakeSeqIdString(int seqIdOffset) const
{
	const PUnit* pPUnit = this;
	for ( ; pPUnit->IsBridge(); pPUnit = pPUnit->GetPUnitNext()) ;
	return String().Printf((seqIdOffset == 0)? "#%zu" : "##%zu", pPUnit->GetSeqId(seqIdOffset));
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

void PUnit::Print(const PUnit* pPUnit, const PUnit* pPUnitSentinel, const StringStyle& ss, int seqIdOffset)
{
	for ( ; pPUnit && pPUnit != pPUnitSentinel; pPUnit = pPUnit->GetPUnitNext()) {
		pPUnit->Print(ss, seqIdOffset);
	}
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
void PUnitStack::Shrink(size_t cnt)
{
	if (cnt >= size()) return;
	auto ppPUnitBegin = begin() + cnt;
	erase(ppPUnitBegin, end());
}

//------------------------------------------------------------------------------
// Iterator_PUnit
//------------------------------------------------------------------------------
Value* Iterator_PUnit::NextValue()
{
	if (!_pPUnit || _pPUnit == _pPUnitSentinel) return nullptr;
	for ( ; _pPUnit->IsBridge(); _pPUnit = _pPUnit->GetPUnitNext()) ;
	if (!_pPUnit || _pPUnit == _pPUnitSentinel) return nullptr;
	RefPtr<Value> pValue(new Value_PUnit(_pPUnit));
	_pPUnit = _pPUnit->GetPUnitNext();
	return pValue.release();
}

size_t Iterator_PUnit::GetLength() const
{
	const PUnit* pPUnit = _pPUnit;
	if (!pPUnit || _pPUnit == _pPUnitSentinel) return 0;
	for ( ; pPUnit && pPUnit->IsBridge(); pPUnit = _pPUnit->GetPUnitNext()) ;
	size_t cnt = 0;
	for ( ; pPUnit && pPUnit != _pPUnitSentinel; pPUnit = pPUnit->GetPUnitNext(), ++cnt) ;
	return cnt;
}

String Iterator_PUnit::ToString(const StringStyle& ss) const
{
	String str;
	str += "PUnit";
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
template<int nExprSrc, bool discardValueFlag>
void PUnit_Value<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	if (!discardValueFlag) processor.PushValue(GetValue()->Reference());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Value<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Value(%s)", GetValue()->ToString(StringStyle().Digest()).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Value::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Value<1, true>(_pValue.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Value<1, false>(_pValue.release(), _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Value<0, true>(_pValue.release());
		} else {
			_pPUnitCreated = new PUnit_Value<0, false>(_pValue.release());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Lookup
// Stack View: [] -> [Any] (continue)
//                -> []    (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_Lookup<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	Frame& frame = processor.GetFrameCur();
	const Value* pValue = frame.Lookup(GetSymbol());
	if (pValue) {
		if (!discardValueFlag) processor.PushValue(pValue->Reference());
		processor.SetPUnitNext(_GetPUnitCont());
	} else {
		Error::Issue(ErrorType::ValueError, "symbol '%s' is not found", GetSymbol()->GetName());
		processor.ErrorDone();
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Lookup<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Lookup(`%s)", GetSymbol()->GetName());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Lookup::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Lookup<1, true>(_pSymbol, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Lookup<1, false>(_pSymbol, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Lookup<0, true>(_pSymbol);
		} else {
			_pPUnitCreated = new PUnit_Lookup<0, false>(_pSymbol);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_AssignToSymbol
// Stack View: [Assigned] -> [Assigned] (continue)
//                        -> []         (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_AssignToSymbol<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValueAssigned(
		discardValueFlag? processor.PopValue() : processor.PeekValue(0).Reference());
	if (pValueAssigned->IsVType()) {
		VType& vtype = Value_VType::GetVTypeThis(*pValueAssigned);
		if (vtype.GetSymbol()->IsEmpty()) {
			vtype.SetSymbol(GetSymbol());
		}
	}
	frame.Assign(GetSymbol(), pValueAssigned.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_AssignToSymbol<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("AssignToSymbol(`%s)", GetSymbol()->GetName());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_AssignToSymbol::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_AssignToSymbol<1, true>(_pSymbol, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_AssignToSymbol<1, false>(_pSymbol, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_AssignToSymbol<0, true>(_pSymbol);
		} else {
			_pPUnitCreated = new PUnit_AssignToSymbol<0, false>(_pSymbol);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_AssignToDeclArg
// Stack View: [Assigned] -> [Assigned] (continue)
//                           []         (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_AssignToDeclArg<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValueAssigned(
		discardValueFlag? processor.PopValue() : processor.PeekValue(0).Reference());
	frame.AssignWithCast(*_pDeclArg, *pValueAssigned);
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_AssignToDeclArg<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("AssignToDeclArg(`%s)", GetDeclArg().ToString(ss).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_AssignToDeclArg::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_AssignToDeclArg<1, true>(_pDeclArg.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_AssignToDeclArg<1, false>(_pDeclArg.release(), _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_AssignToDeclArg<0, true>(_pDeclArg.release());
		} else {
			_pPUnitCreated = new PUnit_AssignToDeclArg<0, false>(_pDeclArg.release());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_AssignFunction
// Stack View: [] -> [Function] (continue)
//                -> []         (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_AssignFunction<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	Frame& frame = processor.GetFrameCur();
	RefPtr<Function> pFunction(GetFunction().Reference());
	pFunction->SetFrameOuter(frame);
	RefPtr<Value> pValueAssigned(new Value_Function(pFunction.release()));
	frame.Assign(GetFunction().GetSymbol(), pValueAssigned->Reference());
	if (!discardValueFlag) processor.PushValue(pValueAssigned.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_AssignFunction<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("AssignFunction(%s,cont=%s)",
			   GetFunction().ToString(StringStyle().Cram()).c_str(),
			   MakeSeqIdString(_GetPUnitCont(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_AssignFunction::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_AssignFunction<1, true>(_pFunction.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_AssignFunction<1, false>(_pFunction.release(), _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_AssignFunction<0, true>(_pFunction.release());
		} else {
			_pPUnitCreated = new PUnit_AssignFunction<0, false>(_pFunction.release());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_AssignMethod
// Stack View: [VType] -> [VType Function] (continue)
//                     -> [VType]         (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_AssignMethod<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	VType& vtype = Value_VType::GetVTypeThis(processor.PeekValue(0));
	Frame& frame = vtype.GetFrame();
	RefPtr<Function> pFunction(GetFunction().Reference());
	pFunction->SetFrameOuter(frame);
	RefPtr<Value> pValueAssigned(new Value_Function(pFunction.release()));
	frame.Assign(GetFunction().GetSymbol(), pValueAssigned->Reference());
	if (!discardValueFlag) processor.PushValue(pValueAssigned.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_AssignMethod<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("AssignMethod(%s,cont=%s)",
			   GetFunction().ToString(StringStyle().Cram()).c_str(),
			   MakeSeqIdString(_GetPUnitCont(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_AssignMethod::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_AssignMethod<1, true>(_pFunction.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_AssignMethod<1, false>(_pFunction.release(), _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_AssignMethod<0, true>(_pFunction.release());
		} else {
			_pPUnitCreated = new PUnit_AssignMethod<0, false>(_pFunction.release());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Cast
// Stack View: [Any] -> [Casted] (continue)
//                   -> []       (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_Cast<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Value> pValueCasted(GetVType().Cast(*pValue, GetListVarFlag()));
	if (pValueCasted) {
		if (!discardValueFlag) processor.PushValue(pValueCasted.release());
		processor.SetPUnitNext(_GetPUnitCont());
	} else {
		processor.ErrorDone();
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Cast<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Cast(%s)", GetVType().MakeFullName().c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Cast::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Cast<1, true>(_vtype, _listVarFlag, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Cast<1, false>(_vtype, _listVarFlag, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Cast<0, true>(_vtype, _listVarFlag);
		} else {
			_pPUnitCreated = new PUnit_Cast<0, false>(_vtype, _listVarFlag);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_GenIterator
// Stack View: [Iterable] -> [Iterator] (continue)
//                        -> []         (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_GenIterator<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Iterator> pIterator(pValue->DoGenIterator());
	if (pIterator) {
		if (!discardValueFlag) processor.PushValue(new Value_Iterator(pIterator.release()));
		processor.SetPUnitNext(_GetPUnitCont());
	} else {
		processor.ErrorDone();
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_GenIterator<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenIterator()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_GenIterator::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_GenIterator<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_GenIterator<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_GenIterator<0, true>();
		} else {
			_pPUnitCreated = new PUnit_GenIterator<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_GenRangeIterator
// Stack View: [Number] -> [Iterator] (continue)
//                      -> []         (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_GenRangeIterator<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValue(processor.PopValue());
	int num = Value_Number::GetInt(*pValue);
	RefPtr<Iterator> pIterator(new Iterator_Range(num));
	if (!discardValueFlag) processor.PushValue(new Value_Iterator(pIterator.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_GenRangeIterator<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenRangeIterator()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_GenRangeIterator::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_GenRangeIterator<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_GenRangeIterator<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_GenRangeIterator<0, true>();
		} else {
			_pPUnitCreated = new PUnit_GenRangeIterator<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_GenCounterIterator
// Stack View: [] -> [Iterator] (continue)
//                -> []         (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_GenCounterIterator<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Iterator> pIterator(new Iterator_Counter());
	if (!discardValueFlag) processor.PushValue(new Value_Iterator(pIterator.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_GenCounterIterator<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenCounterIterator()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_GenCounterIterator::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_GenCounterIterator<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_GenCounterIterator<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_GenCounterIterator<0, true>();
		} else {
			_pPUnitCreated = new PUnit_GenCounterIterator<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_EvalIterator
// Stack View: [Iterator] -> [Iterator Elem] (continue)
//                        -> [Iterator]      (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_EvalIterator<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	Iterator& iterator = Value_Iterator::GetIterator(processor.PeekValue(GetOffset()));
	RefPtr<Value> pValueElem(iterator.NextValue());
	if (pValueElem) {
		if (!discardValueFlag) processor.PushValue(pValueElem.release());
		processor.SetPUnitNext(_GetPUnitCont());
	} else {
		processor.SetPUnitNext(GetPUnitBranchDest());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_EvalIterator<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("EvalIterator(offsetToIterator=%zu,branchdest=%s)", GetOffset(),
			   MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_EvalIterator::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_EvalIterator<1, true>(_offset, _pPUnitBranchDest, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_EvalIterator<1, false>(_offset, _pPUnitBranchDest, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_EvalIterator<0, true>(_offset, _pPUnitBranchDest);
		} else {
			_pPUnitCreated = new PUnit_EvalIterator<0, false>(_offset, _pPUnitBranchDest);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_ForEach
// Stack View: [Iterator1..n ..] -> [Iterator1..n ..] (continue)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_ForEach<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	Frame& frame = processor.GetFrameCur();
	size_t offset = GetOffset() + GetDeclArgOwner().size() - 1;
	for (DeclArg* pDeclArg : GetDeclArgOwner()) {
		Iterator& iterator = Value_Iterator::GetIterator(processor.PeekValue(offset));
		RefPtr<Value> pValueElem(iterator.NextValue());
		if (!pValueElem) {
			processor.SetPUnitNext(GetPUnitBranchDest());
			return;
		}
		frame.AssignWithCast(*pDeclArg, *pValueElem);
		offset--;
	}
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_ForEach<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("ForEach(offsetToIterator=%zu,branchdest=%s, decls=[%s])", GetOffset(),
			   MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str(),
			   GetDeclArgOwner().ToString(StringStyle().Digest().Cram()).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_ForEach::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_ForEach<1, true>(
				_offset, _pDeclArgOwner.release(), _pPUnitBranchDest, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_ForEach<1, false>(
				_offset, _pDeclArgOwner.release(), _pPUnitBranchDest, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_ForEach<0, true>(
				_offset, _pDeclArgOwner.release(), _pPUnitBranchDest);
		} else {
			_pPUnitCreated = new PUnit_ForEach<0, false>(
				_offset, _pDeclArgOwner.release(), _pPUnitBranchDest);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_UnaryOp
// Stack View: [Any] -> [Result] (continue)
//                   -> []       (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_UnaryOp<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Value> pValueResult(GetOperator()->EvalUnary(processor, *pValue));
	if (pValueResult->IsUndefined()) {
		processor.ErrorDone();
	} else {
		if (!discardValueFlag) processor.PushValue(pValueResult.release());
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_UnaryOp<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("UnaryOp(%s)", GetOperator()->GetSymbol());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_UnaryOp::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_UnaryOp<1, true>(_pOperator, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_UnaryOp<1, false>(_pOperator, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_UnaryOp<0, true>(_pOperator);
		} else {
			_pPUnitCreated = new PUnit_UnaryOp<0, false>(_pOperator);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_BinaryOp
// Stack View: [Left Right] -> [Result] (continue)
//                          -> []       (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_BinaryOp<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValueRight(processor.PopValue());
	RefPtr<Value> pValueLeft(processor.PopValue());
	RefPtr<Value> pValueResult(GetOperator()->EvalBinary(processor, *pValueLeft, *pValueRight));
	if (pValueResult->IsUndefined()) {
		processor.ErrorDone();
	} else {
		if (!discardValueFlag) processor.PushValue(pValueResult.release());
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_BinaryOp<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("BinaryOp(%s)", GetOperator()->GetSymbol());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_BinaryOp::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_BinaryOp<1, true>(_pOperator, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_BinaryOp<1, false>(_pOperator, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_BinaryOp<0, true>(_pOperator);
		} else {
			_pPUnitCreated = new PUnit_BinaryOp<0, false>(_pOperator);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Import
// Stack View: [] -> [Module] (continue)
//                -> []    (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_Import<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Module> pModule(Module::ImportHierarchy(processor, GetDottedSymbol()));
	if (pModule) {
		pModule->AssignToFrame(processor, GetSymbolList(), GetMixInFlag());
		if (!discardValueFlag) processor.PushValue(new Value_Module(pModule.release()));
		processor.SetPUnitNext(_GetPUnitCont());
	} else {
		processor.ErrorDone();
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Import<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Import(`%s)", GetDottedSymbol().ToString().c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Import::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Import<1, true>(_pDottedSymbol.release(), _pSymbolList.release(), _mixInFlag, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Import<1, false>(_pDottedSymbol.release(), _pSymbolList.release(), _mixInFlag, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Import<0, true>(_pDottedSymbol.release(), _pSymbolList.release(), _mixInFlag);
		} else {
			_pPUnitCreated = new PUnit_Import<0, false>(_pDottedSymbol.release(), _pSymbolList.release(), _mixInFlag);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_CreateVType
// Stack View: [] -> [VType] (continue)
//                -> []      (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_CreateVType<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	// VType settings
	VType* pVType = new VType(Symbol::Empty);
	pVType->SetAttrs(VTYPE_Object, VType::Flag::Mutable);
	pVType->SetConstructor(Function::Empty->Reference());
	if (!discardValueFlag) processor.PushValue(new Value_VType(*pVType));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_CreateVType<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "CreateVType()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_CreateVType::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_CreateVType<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_CreateVType<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_CreateVType<0, true>();
		} else {
			_pPUnitCreated = new PUnit_CreateVType<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_CreateList
// Stack View: [] -> [List] (continue)
//                -> []     (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_CreateList<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<ValueTypedOwner> pValueTypedOwner(new ValueTypedOwner());
	if (GetSizeReserve() > 0) pValueTypedOwner->Reserve(GetSizeReserve());
	if (!discardValueFlag) processor.PushValue(new Value_List(pValueTypedOwner.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_CreateList<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "CreateList()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_CreateList::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_CreateList<1, true>(_sizeReserve, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_CreateList<1, false>(_sizeReserve, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_CreateList<0, true>(_sizeReserve);
		} else {
			_pPUnitCreated = new PUnit_CreateList<0, false>(_sizeReserve);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_ListElem
// Stack View: [List Elem] -> [List] (continue)
//                         -> []     (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, bool xlistFlag>
void PUnit_ListElem<nExprSrc, discardValueFlag, xlistFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValueElem(processor.PopValue());
	if (pValueElem->IsIterator()) {
		ValueTypedOwner& valueTypedOwner =
			Value_List::GetValueTypedOwner(processor.PeekValue(GetOffset()));
		Iterator& iterator = Value_Iterator::GetIterator(*pValueElem);
		if (!iterator.MustBeFinite()) return;
		for (;;) {
			RefPtr<Value> pValue(iterator.NextValue());
			if (!pValue) break;
			if (!xlistFlag || pValue->IsValid()) valueTypedOwner.Add(pValue.release());
		}
		
	} else if (!pValueElem->IsUndefined() && (!xlistFlag || pValueElem->IsValid())) {
		ValueTypedOwner& valueTypedOwner =
			Value_List::GetValueTypedOwner(processor.PeekValue(GetOffset()));
		valueTypedOwner.Add(pValueElem.release());
	}
	if (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag, bool xlistFlag>
String PUnit_ListElem<nExprSrc, discardValueFlag, xlistFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("ListElem(offsetToList=%zu)", GetOffset());
	if (xlistFlag) str += ":xlist";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_ListElem::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (_xlistFlag) {
			if (discardValueFlag) {
				_pPUnitCreated = new PUnit_ListElem<1, true, true>(_offset, _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_ListElem<1, false, true>(_offset, _pExprSrc.Reference());
			}
		} else {
			if (discardValueFlag) {
				_pPUnitCreated = new PUnit_ListElem<1, true, false>(_offset, _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_ListElem<1, false, false>(_offset, _pExprSrc.Reference());
			}
		}
	} else {
		if (_xlistFlag) {
			if (discardValueFlag) {
				_pPUnitCreated = new PUnit_ListElem<0, true, true>(_offset);
			} else {
				_pPUnitCreated = new PUnit_ListElem<0, false, true>(_offset);
			}
		} else {
			if (discardValueFlag) {
				_pPUnitCreated = new PUnit_ListElem<0, true, false>(_offset);
			} else {
				_pPUnitCreated = new PUnit_ListElem<0, false, false>(_offset);
			}
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_CreateDict
// Stack View: [] -> [Dict] (continue)
//                -> []     (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_CreateDict<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	if (!discardValueFlag) processor.PushValue(new Value_Dict());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_CreateDict<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "CreateDict()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_CreateDict::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_CreateDict<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_CreateDict<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_CreateDict<0, true>();
		} else {
			_pPUnitCreated = new PUnit_CreateDict<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_DictElem
// Stack View: [Dict Key Elem] -> [Dict] (continue)
//                             -> []     (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_DictElem<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValueElem(processor.PopValue());
	RefPtr<Value> pValueKey(processor.PopValue());
	ValueDict& valueDict = Value_Dict::GetValueDict(processor.PeekValue(GetOffset()));
	valueDict.Assign(pValueKey.release(), pValueElem.release());
	if (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_DictElem<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("DictElem(offsetToDict=%zu)", GetOffset());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_DictElem::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_DictElem<1, true>(_offset, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_DictElem<1, false>(_offset, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_DictElem<0, true>(_offset);
		} else {
			_pPUnitCreated = new PUnit_DictElem<0, false>(_offset);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Index
// Stack View: [Car] -> [Index(Car)] (continue)
//                   -> []           (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_Index<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValueCar(processor.PopValue());
	RefPtr<Index> pIndex(new Index(pValueCar.release(), GetAttr().Reference()));
	if (GetSizeReserve() > 0) pIndex->Reserve(GetSizeReserve());
	if (!discardValueFlag) processor.PushValue(new Value_Index(pIndex.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Index<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "Index()";
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Index::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Index<1, true>(_pAttr.release(), _sizeReserve, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Index<1, false>(_pAttr.release(), _sizeReserve, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Index<0, true>(_pAttr.release(), _sizeReserve);
		} else {
			_pPUnitCreated = new PUnit_Index<0, false>(_pAttr.release(), _sizeReserve);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_FeedIndex
// Stack View: [Index(Car) Any] -> [Index(Car)] (continue)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_FeedIndex<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValue(processor.PopValue());
	Index& index = Value_Index::GetIndex(processor.PeekValue(0));
	index.FeedValue(pValue.release());
	if (Error::IsIssued()) {
		processor.ErrorDone();
	} else {
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_FeedIndex<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "FeedIndex()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_FeedIndex::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_FeedIndex<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_FeedIndex<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_FeedIndex<0, true>();
		} else {
			_pPUnitCreated = new PUnit_FeedIndex<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_IndexGet
// Stack View: [Index(Car)] -> [Elems] (continue)
//                          -> []      (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_IndexGet<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value_Index> pValueIndex(dynamic_cast<Value_Index*>(processor.PopValue()));
	Index& index = pValueIndex->GetIndex();
	RefPtr<Value> pValueElems(index.IndexGet());
	if (Error::IsIssued()) {
		processor.ErrorDone();
	} else {
		if (!discardValueFlag) processor.PushValue(pValueElems.release());
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_IndexGet<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "IndexGet()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_IndexGet::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_IndexGet<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_IndexGet<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_IndexGet<0, true>();
		} else {
			_pPUnitCreated = new PUnit_IndexGet<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_IndexSet
// Stack View: [Index(Car) Elems] -> [Elems] (continue)
//                                -> []      (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_IndexSet<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValueElems(processor.PopValue());
	RefPtr<Value_Index> pValueIndex(dynamic_cast<Value_Index*>(processor.PopValue()));
	Index& index = pValueIndex->GetIndex();
	index.IndexSet(pValueElems->Reference());
	if (Error::IsIssued()) {
		processor.ErrorDone();
	} else {
		if (!discardValueFlag) processor.PushValue(pValueElems.release());
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_IndexSet<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "IndexSet()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_IndexSet::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_IndexSet<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_IndexSet<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_IndexSet<0, true>();
		} else {
			_pPUnitCreated = new PUnit_IndexSet<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_PropGet
// Stack View: [Target] -> [Target Prop] (continue)
//                      -> [Target]      (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_PropGet<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	Value& valueTarget = processor.PeekValue(0);
	Value* pValueProp = valueTarget.DoPropGet(GetSymbol(), GetAttr());
	if (!pValueProp) {
		Error::Issue(ErrorType::PropertyError,
				   "value type '%s' doesn't have a property named '%s'",
				   valueTarget.GetVType().MakeFullName().c_str(), GetSymbol()->GetName());
		processor.ErrorDone();
	} else {
		if (!discardValueFlag) processor.PushValue(pValueProp->Reference());
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_PropGet<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("PropGet(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_PropGet::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_PropGet<1, true>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_PropGet<1, false>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_PropGet<0, true>(_pSymbol, _pAttr.release());
		} else {
			_pPUnitCreated = new PUnit_PropGet<0, false>(_pSymbol, _pAttr.release());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_PropSet
// Stack View: [Target Assigned] -> [Assigned] (continue)
//                               -> []         (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_PropSet<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValueProp(processor.PopValue());
	RefPtr<Value> pValueTarget(processor.PopValue());
	if (!pValueTarget->DoPropSet(GetSymbol(), pValueProp->Reference(), GetAttr())) {
		Error::Issue(ErrorType::PropertyError,
				   "failed to set value to symbol '%s'", GetSymbol()->GetName());
		processor.ErrorDone();
	} else {
		if (!discardValueFlag) processor.PushValue(pValueProp.release());
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_PropSet<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("PropSet(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_PropSet::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_PropSet<1, true>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_PropSet<1, false>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_PropSet<0, true>(_pSymbol, _pAttr.release());
		} else {
			_pPUnitCreated = new PUnit_PropSet<0, false>(_pSymbol, _pAttr.release());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Member
// Stack View: [Target] -> [Member(Target+Prop)] (continue, callable)
//                      -> [Prop]                (continue, not callable)
//                      -> []                    (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_Member<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValueTarget(processor.PopValue());
	Value* pValueProp = pValueTarget->DoPropGet(GetSymbol(), GetAttr());
	if (!pValueProp) {
		Error::Issue(ErrorType::PropertyError,
				   "value type '%s' doesn't have a property named '%s'",
				   pValueTarget->GetVType().MakeFullName().c_str(), GetSymbol()->GetName());
		processor.ErrorDone();
	} else {
		if (discardValueFlag) {
			// nothing to do
		} else if (pValueProp->IsCallable()) {
			processor.PushValue(new Value_Member(pValueTarget.release(), pValueProp->Reference()));
		} else {
			processor.PushValue(pValueProp->Reference());
		}
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Member<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Member(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Member::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Member<1, true>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Member<1, false>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Member<0, true>(_pSymbol, _pAttr.release());
		} else {
			_pPUnitCreated = new PUnit_Member<0, false>(_pSymbol, _pAttr.release());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Argument
// Stack View: [Car] -> [Argument(Car)] (continue)
//                   -> []              (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
PUnit_Argument<nExprSrc, discardValueFlag>::PUnit_Argument(const Attribute& attr, Expr_Block* pExprOfBlock) :
	_pAttr(new Attribute()), _flags(DeclCallable::Flag::None), _pExprOfBlock(pExprOfBlock)
{
	for (const Symbol* pSymbol : attr.GetSymbols()) {
		DeclCallable::Flags flag = DeclCallable::SymbolToFlag(pSymbol);
		_flags |= flag;
		if (!flag) _pAttr->AddSymbol(pSymbol);
	}
	_pAttr->AddSymbolsOpt(attr.GetSymbolsOpt());
}

template<int nExprSrc, bool discardValueFlag>
void PUnit_Argument<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValueCar(processor.PopValue());
	const DeclCallable* pDeclCallable = pValueCar->GetDeclCallable();
	if (!pDeclCallable) {
		processor.ErrorDone();
	} else if (!pDeclCallable->CheckAttribute(GetAttr())) {
		processor.ErrorDone();
	} else {
		RefPtr<Argument> pArgument(
			new Argument(pValueCar.release(), pDeclCallable->Reference(),
						 GetAttr().Reference(), pDeclCallable->GetFlags() | GetFlags(), Value::nil(),
						 Expr_Block::Reference(GetExprOfBlock())));
		if (!discardValueFlag) processor.PushValue(new Value_Argument(pArgument.release()));
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Argument<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	if (_pExprOfBlock) {
		str.Printf("Argument(block=%s)", MakeSeqIdString(_pExprOfBlock->GetPUnitFirst(), seqIdOffset).c_str());
	} else {
		str += "Argument()";
	}
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Argument::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Argument<1, true>(*_pAttr, _pExprOfBlock.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Argument<1, false>(*_pAttr, _pExprOfBlock.release(), _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Argument<0, true>(*_pAttr, _pExprOfBlock.release());
		} else {
			_pPUnitCreated = new PUnit_Argument<0, false>(*_pAttr, _pExprOfBlock.release());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_BeginArgSlot
// Stack View: [Argument(Car)] -> [Argument(Car)] (continue)
//                             -> [Argument(Car)] (branch)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_BeginArgSlot<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	Argument& argument = Value_Argument::GetArgument(processor.PeekValue(0));
	ArgSlot* pArgSlot = argument.GetArgSlotToFeed(); // this may be nullptr
	if (!pArgSlot) {
		if (argument.IsSet(DeclCallable::Flag::CutExtraArgs)) {
			// just ignore extra arguments
			processor.SetPUnitNext(_GetPUnitCont());
		} else {
			Error::Issue(ErrorType::ArgumentError, "too many arguments");
			processor.ErrorDone();
		}
	} else if (!pArgSlot->IsVacant()) {
		Error::Issue(ErrorType::ArgumentError, "duplicated assignment of argument");
		processor.ErrorDone();
	} else if (pArgSlot->IsVType(VTYPE_Quote)) {
		Frame& frame = processor.GetFrameCur();
		argument.FeedValue(frame, new Value_Expr(GetExprSrc().Reference()));
		if (Error::IsIssued()) {
			processor.ErrorDone();
			return;
		}
		processor.SetPUnitNext(GetPUnitBranchDest());
	} else {
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_BeginArgSlot<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	RefPtr<Expr> pExpr(new Expr_UnaryOp(GetExprSrc().Reference(), Operator::Quote));
	str.Printf("BeginArgSlot(%s", pExpr->ToString(StringStyle().Cram()).c_str());
	if (GetExprSrc().GetPUnitFirst()) {
		str.Printf(":%s", MakeSeqIdString(GetExprSrc().GetPUnitFirst(), seqIdOffset).c_str());
	}
	str.Printf(",sentinel=%s,branchdest=%s)",
			   MakeSeqIdString(GetPUnitSentinel(), seqIdOffset).c_str(),
			   MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_BeginArgSlot::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_BeginArgSlot<1, true>(_pPUnitBranchDest, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_BeginArgSlot<1, false>(_pPUnitBranchDest, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_BeginArgSlot<0, true>(_pPUnitBranchDest);
		} else {
			_pPUnitCreated = new PUnit_BeginArgSlot<0, false>(_pPUnitBranchDest);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_EndArgSlot
// Stack View: [Argument(Car) Any] -> [Argument(Car)] (continue)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_EndArgSlot<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValue(processor.PopValue());
	Argument& argument = Value_Argument::GetArgument(processor.PeekValue(0));
	argument.FeedValue(frame, pValue.release());
	if (Error::IsIssued()) {
		processor.ErrorDone();
	} else {
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_EndArgSlot<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "EndArgSlot()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_EndArgSlot::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_EndArgSlot<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_EndArgSlot<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_EndArgSlot<0, true>();
		} else {
			_pPUnitCreated = new PUnit_EndArgSlot<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_BeginArgSlotNamed
// Stack View: [Argument(Car)] -> [Argument(Car) ArgSlot] (continue)
//                             -> [Argument(Car)]         (discard)
//                             -> [Argument(Car)]         (branch)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_BeginArgSlotNamed<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	Argument& argument = Value_Argument::GetArgument(processor.PeekValue(0));
	ArgSlot* pArgSlot = argument.FindArgSlot(GetSymbol());
	if (!pArgSlot) {
		Value_Dict* pValueOfDict = argument.GetValueOfDict();
		if (pValueOfDict) {
			processor.PushValue(
				new Value_ArgSlot(new ArgSlot_Dict(pValueOfDict->Reference(), GetSymbol())));
			processor.SetPUnitNext(_GetPUnitCont());
		} else {
			Error::Issue(ErrorType::ArgumentError, "can't find the specified argument: %s", GetSymbol()->GetName());
			processor.ErrorDone();
			return;
		}
	} else if (!pArgSlot->IsVacant()) {
		Error::Issue(ErrorType::ArgumentError, "duplicated assignment of argument");
		processor.ErrorDone();
	} else if (pArgSlot->IsVType(VTYPE_Quote)) {
		Frame& frame = processor.GetFrameCur();
		pArgSlot->FeedValue(argument, frame, new Value_Expr(GetExprAssigned()->Reference()));
		if (Error::IsIssued()) {
			processor.ErrorDone();
			return;
		}
		processor.SetPUnitNext(GetPUnitBranchDest());
	} else {
		if (!discardValueFlag) processor.PushValue(new Value_ArgSlot(pArgSlot->Reference()));
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_BeginArgSlotNamed<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("BeginArgSlotNamed(`%s,symbol=%s,sentinel=%s,branchdest=%s)",
			   GetExprSrc().ToString(StringStyle().Cram()).c_str(), GetSymbol()->GetName(),
			   MakeSeqIdString(GetPUnitSentinel(), seqIdOffset).c_str(),
			   MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_BeginArgSlotNamed::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_BeginArgSlotNamed<1, true>(
				_pSymbol, _pExprAssigned.release(), _pPUnitBranchDest, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_BeginArgSlotNamed<1, false>(
				_pSymbol, _pExprAssigned.release(), _pPUnitBranchDest, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_BeginArgSlotNamed<0, true>(
				_pSymbol, _pExprAssigned.release(), _pPUnitBranchDest);
		} else {
			_pPUnitCreated = new PUnit_BeginArgSlotNamed<0, false>(
				_pSymbol, _pExprAssigned.release(), _pPUnitBranchDest);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_EndArgSlotNamed
// Stack View: [Argument ArgSlot Any] -> [Argument] (continue)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_EndArgSlotNamed<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Value> pValueArgSlot(processor.PopValue());
	Argument& argument = Value_Argument::GetArgument(processor.PeekValue(0));
	ArgSlot& argSlot = Value_ArgSlot::GetArgSlot(*pValueArgSlot);
	argSlot.FeedValue(argument, frame, pValue.release());
	if (Error::IsIssued()) {
		processor.ErrorDone();
	} else {
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_EndArgSlotNamed<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "EndArgSlotNamed()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_EndArgSlotNamed::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_EndArgSlotNamed<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_EndArgSlotNamed<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_EndArgSlotNamed<0, true>();
		} else {
			_pPUnitCreated = new PUnit_EndArgSlotNamed<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Call
// Stack View: [Argument] -> [Result] (continue)
//                        -> []       (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_Call<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value_Argument> pValue(dynamic_cast<Value_Argument*>(processor.PopValue()));
	Argument& argument = pValue->GetArgument();
	argument.DoCall(processor);
	if (Error::IsIssued()) {
		processor.ErrorDone();
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Call<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Call(cont=%s)", MakeSeqIdString(_GetPUnitCont(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Call::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Call<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Call<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Call<0, true>();
		} else {
			_pPUnitCreated = new PUnit_Call<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Jump
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_Jump<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	if (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Jump<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Jump(cont=%s)", MakeSeqIdString(_GetPUnitCont(), seqIdOffset).c_str());
	return str;
}

PUnit* PUnitFactory_Jump::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Jump<1, true>(_pPUnitCont, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Jump<1, false>(_pPUnitCont, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Jump<0, true>(_pPUnitCont);
		} else {
			_pPUnitCreated = new PUnit_Jump<0, false>(_pPUnitCont);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_JumpIf
// Stack View: [Prev Bool] -> [Prev] (continue)
//                         -> []     (discard)
//                         -> [Prev] (branch)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_JumpIf<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		processor.SetPUnitNext(GetPUnitBranchDest());
	} else {
		if (discardValueFlag) processor.DiscardValue();
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_JumpIf<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("JumpIf(branchdest=%s)", MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_JumpIf::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_JumpIf<1, true>(_pPUnitBranchDest, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_JumpIf<1, false>(_pPUnitBranchDest, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_JumpIf<0, true>(_pPUnitBranchDest);
		} else {
			_pPUnitCreated = new PUnit_JumpIf<0, false>(_pPUnitBranchDest);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_JumpIfNot
// Stack View: [Prev Bool] -> [Prev]  (continue)
//                         -> []      (discard)
//                         -> [Prev]  (branch)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_JumpIfNot<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		if (discardValueFlag) processor.DiscardValue();
		processor.SetPUnitNext(_GetPUnitCont());
	} else {
		processor.SetPUnitNext(GetPUnitBranchDest());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_JumpIfNot<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("JumpIfNot(branchdest=%s)", MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_JumpIfNot::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_JumpIfNot<1, true>(_pPUnitBranchDest, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_JumpIfNot<1, false>(_pPUnitBranchDest, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_JumpIfNot<0, true>(_pPUnitBranchDest);
		} else {
			_pPUnitCreated = new PUnit_JumpIfNot<0, false>(_pPUnitBranchDest);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_NilJumpIf
// Stack View: [Prev Bool] -> [Prev]     (continue)
//                         -> []         (discard)
//                         -> [Prev Nil] (branch)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_NilJumpIf<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		processor.PushValue(Value::nil());
		processor.SetPUnitNext(GetPUnitBranchDest());
	} else {
		if (discardValueFlag) processor.DiscardValue();
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_NilJumpIf<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("NilJumpIf(branchdest=%s)", MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_NilJumpIf::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_NilJumpIf<1, true>(_pPUnitBranchDest, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_NilJumpIf<1, false>(_pPUnitBranchDest, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_NilJumpIf<0, true>(_pPUnitBranchDest);
		} else {
			_pPUnitCreated = new PUnit_NilJumpIf<0, false>(_pPUnitBranchDest);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_NilJumpIfNot
// Stack View: [Prev Bool] -> [Prev]     (continue)
//                         -> []         (discard)
//                         -> [Prev Nil] (branch)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_NilJumpIfNot<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValue(processor.PopValue());
	if (pValue->GetBool()) {
		if (discardValueFlag) processor.DiscardValue();
		processor.SetPUnitNext(_GetPUnitCont());
	} else {
		processor.PushValue(Value::nil());
		processor.SetPUnitNext(GetPUnitBranchDest());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_NilJumpIfNot<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("NilJumpIfNot(branchdest=%s)", MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_NilJumpIfNot::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_NilJumpIfNot<1, true>(_pPUnitBranchDest, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_NilJumpIfNot<1, false>(_pPUnitBranchDest, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_NilJumpIfNot<0, true>(_pPUnitBranchDest);
		} else {
			_pPUnitCreated = new PUnit_NilJumpIfNot<0, false>(_pPUnitBranchDest);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_KeepJumpIf
// Stack View: [Prev Bool] -> [Prev]      (continue)
//                         -> []          (discard)
//                         -> [Prev Bool] (branch)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_KeepJumpIf<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	if (processor.PeekValue(0).GetBool()) {
		processor.SetPUnitNext(GetPUnitBranchDest());
	} else {
		processor.DiscardValue();
		if (discardValueFlag) processor.DiscardValue();
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_KeepJumpIf<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("KeepJumpIf(branchdest=%s)", MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_KeepJumpIf::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_KeepJumpIf<1, true>(_pPUnitBranchDest, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_KeepJumpIf<1, false>(_pPUnitBranchDest, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_KeepJumpIf<0, true>(_pPUnitBranchDest);
		} else {
			_pPUnitCreated = new PUnit_KeepJumpIf<0, false>(_pPUnitBranchDest);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_KeepJumpIfNot
// Stack View: [Prev Bool] -> [Prev]      (continue)
//                         -> []          (discard)
//                         -> [Prev Bool] (branch)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_KeepJumpIfNot<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	if (processor.PeekValue(0).GetBool()) {
		processor.DiscardValue();
		if (discardValueFlag) processor.DiscardValue();
		processor.SetPUnitNext(_GetPUnitCont());
	} else {
		processor.SetPUnitNext(GetPUnitBranchDest());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_KeepJumpIfNot<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("KeepJumpIfNot(branchdest=%s)", MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_KeepJumpIfNot::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_KeepJumpIfNot<1, true>(_pPUnitBranchDest, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_KeepJumpIfNot<1, false>(_pPUnitBranchDest, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_KeepJumpIfNot<0, true>(_pPUnitBranchDest);
		} else {
			_pPUnitCreated = new PUnit_KeepJumpIfNot<0, false>(_pPUnitBranchDest);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_BeginTryBlock
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_BeginTryBlock<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	processor.BeginTryBlock(GetPUnitBranchDest());
	if (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_BeginTryBlock<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("BeginTryBlock(branchdest=%s)", MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_BeginTryBlock::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_BeginTryBlock<1, true>(_pPUnitBranchDest, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_BeginTryBlock<1, false>(_pPUnitBranchDest, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_BeginTryBlock<0, true>(_pPUnitBranchDest);
		} else {
			_pPUnitCreated = new PUnit_BeginTryBlock<0, false>(_pPUnitBranchDest);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_EndTryBlock
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_EndTryBlock<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	processor.EndTryBlock();
	if (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_EndTryBlock<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("EndTryBlock(cont=%s)", MakeSeqIdString(_GetPUnitCont(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_EndTryBlock::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_EndTryBlock<1, true>(_pPUnitCont, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_EndTryBlock<1, false>(_pPUnitCont, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_EndTryBlock<0, true>(_pPUnitCont);
		} else {
			_pPUnitCreated = new PUnit_EndTryBlock<0, false>(_pPUnitCont);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_JumpIfNoCatch
// Stack View: [ErrorType] -> [Error] (continue)
//                         -> []      (discard)
//                         -> []      (branch)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_JumpIfNoCatch<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValue(processor.PopValue());
	const ErrorType& errorType = Value_ErrorType::GetErrorType(*pValue);
	const Error* pError = Error::GetLastError();
	if (pError && pError->GetErrorType().IsIdentical(errorType)) {
		if (!discardValueFlag) processor.PushValue(new Value_Error(pError->Reference()));
		Error::Clear();
		processor.SetPUnitNext(_GetPUnitCont());
	} else {
		processor.SetPUnitNext(GetPUnitBranchDest());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_JumpIfNoCatch<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("JumpIfNoCatch(branchdest=%s)", MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_JumpIfNoCatch::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_JumpIfNoCatch<1, true>(_pPUnitBranchDest, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_JumpIfNoCatch<1, false>(_pPUnitBranchDest, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_JumpIfNoCatch<0, true>(_pPUnitBranchDest);
		} else {
			_pPUnitCreated = new PUnit_JumpIfNoCatch<0, false>(_pPUnitBranchDest);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_JumpIfNoCatchAny
// Stack View: [] -> [Error] (continue)
//                -> []      (discard)
//                -> []      (branch)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_JumpIfNoCatchAny<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	const Error* pError = Error::GetLastError();
	if (pError) {
		if (!discardValueFlag) processor.PushValue(new Value_Error(pError->Reference()));
		Error::Clear();
		processor.SetPUnitNext(_GetPUnitCont());
	} else {
		processor.SetPUnitNext(GetPUnitBranchDest());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_JumpIfNoCatchAny<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("JumpIfNoCatchAny(branchdest=%s)", MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_JumpIfNoCatchAny::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_JumpIfNoCatchAny<1, true>(_pPUnitBranchDest, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_JumpIfNoCatchAny<1, false>(_pPUnitBranchDest, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_JumpIfNoCatchAny<0, true>(_pPUnitBranchDest);
		} else {
			_pPUnitCreated = new PUnit_JumpIfNoCatchAny<0, false>(_pPUnitBranchDest);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_NilJumpIfNoCatch
// Stack View: [ErrorType] -> [Error] (continue)
//                         -> []      (discard)
//                         -> [nil]   (branch)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_NilJumpIfNoCatch<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValue(processor.PopValue());
	const ErrorType& errorType = Value_ErrorType::GetErrorType(*pValue);
	const Error* pError = Error::GetLastError();
	if (pError && pError->GetErrorType().IsIdentical(errorType)) {
		if (!discardValueFlag) processor.PushValue(new Value_Error(pError->Reference()));
		Error::Clear();
		processor.SetPUnitNext(_GetPUnitCont());
	} else {
		processor.PushValue(Value::nil());
		processor.SetPUnitNext(GetPUnitBranchDest());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_NilJumpIfNoCatch<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("NilJumpIfNoCatch(branchdest=%s)", MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_NilJumpIfNoCatch::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_NilJumpIfNoCatch<1, true>(_pPUnitBranchDest, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_NilJumpIfNoCatch<1, false>(_pPUnitBranchDest, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_NilJumpIfNoCatch<0, true>(_pPUnitBranchDest);
		} else {
			_pPUnitCreated = new PUnit_NilJumpIfNoCatch<0, false>(_pPUnitBranchDest);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_NilJumpIfNoCatchAny
// Stack View: [] -> [Error] (continue)
//                -> []      (discard)
//                -> [nil]   (branch)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_NilJumpIfNoCatchAny<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	const Error* pError = Error::GetLastError();
	if (pError) {
		if (!discardValueFlag) processor.PushValue(new Value_Error(pError->Reference()));
		Error::Clear();
		processor.SetPUnitNext(_GetPUnitCont());
	} else {
		processor.PushValue(Value::nil());
		processor.SetPUnitNext(GetPUnitBranchDest());
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_NilJumpIfNoCatchAny<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("NilJumpIfNoCatchAny(branchdest=%s)", MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_NilJumpIfNoCatchAny::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_NilJumpIfNoCatchAny<1, true>(_pPUnitBranchDest, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_NilJumpIfNoCatchAny<1, false>(_pPUnitBranchDest, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_NilJumpIfNoCatchAny<0, true>(_pPUnitBranchDest);
		} else {
			_pPUnitCreated = new PUnit_NilJumpIfNoCatchAny<0, false>(_pPUnitBranchDest);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_BeginSequence
// Stack View: [Prev] -> [Prev] (continue)
//                       []     (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_BeginSequence<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	if (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_BeginSequence<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("BeginSequence(sentinel=%s)", MakeSeqIdString(GetPUnitSentinel(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_BeginSequence::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_BeginSequence<1, true>(_pPUnitSentinel, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_BeginSequence<1, false>(_pPUnitSentinel, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_BeginSequence<0, true>(_pPUnitSentinel);
		} else {
			_pPUnitCreated = new PUnit_BeginSequence<0, false>(_pPUnitSentinel);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_EndSequence
// Stack View: [Prev] -> [Prev] (always)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_EndSequence<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	processor.ExitRunLoop();
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_EndSequence<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "EndSequence()";
	//AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_EndSequence::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_EndSequence<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_EndSequence<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_EndSequence<0, true>();
		} else {
			_pPUnitCreated = new PUnit_EndSequence<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_DiscardValue
// Stack View: [Prev Any] -> [Prev] (continue)
//                        -> []     (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_DiscardValue<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	processor.DiscardValue();
	if (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_DiscardValue<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "DiscardValue()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_DiscardValue::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_DiscardValue<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_DiscardValue<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_DiscardValue<0, true>();
		} else {
			_pPUnitCreated = new PUnit_DiscardValue<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_RemoveValue
// Stack View: [.. Any .. Prev] -> [.. .. Prev] (continue)
//                              -> [.. ..]      (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_RemoveValue<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	processor.RemoveValue(GetOffset());
	if (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_RemoveValue<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("RemoveValue(offset=%zu)", GetOffset());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_RemoveValue::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_RemoveValue<1, true>(_offset, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_RemoveValue<1, false>(_offset, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_RemoveValue<0, true>(_offset);
		} else {
			_pPUnitCreated = new PUnit_RemoveValue<0, false>(_offset);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_RemoveValues
// Stack View: [.. Any1..n .. Prev] -> [.. .. Prev] (continue)
//                                  -> [.. ..]      (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_RemoveValues<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	processor.RemoveValues(GetOffset(), GetCount());
	if (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_RemoveValues<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("RemoveValues(offset=%zu,count=%zu)", GetOffset(), GetCount());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_RemoveValues::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_RemoveValues<1, true>(_offset, _cnt, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_RemoveValues<1, false>(_offset, _cnt, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_RemoveValues<0, true>(_offset, _cnt);
		} else {
			_pPUnitCreated = new PUnit_RemoveValues<0, false>(_offset, _cnt);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Break
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, bool branchDestFlag>
void PUnit_Break<nExprSrc, discardValueFlag, branchDestFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	if (discardValueFlag) processor.DiscardValue();
	if (GetPUnitMarked()) {
		if (branchDestFlag) {
			processor.SetPUnitNext(GetPUnitMarked()->GetPUnitBranchDest());
		} else {
			processor.SetPUnitNext(GetPUnitMarked());
		}
	} else {
		processor.SetEventBreak();
		processor.ExitRunLoop();
	}
}

template<int nExprSrc, bool discardValueFlag, bool branchDestFlag>
String PUnit_Break<nExprSrc, discardValueFlag, branchDestFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Break(marked=%s,branchDestFlag=%s)", MakeSeqIdString(GetPUnitMarked(), seqIdOffset).c_str(),
			   branchDestFlag? "true" : "false");
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Break::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (_branchDestFlag) {
			if (discardValueFlag) {
				_pPUnitCreated = new PUnit_Break<1, true, true>(_pPUnitMarked, _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_Break<1, false, true>(_pPUnitMarked, _pExprSrc.Reference());
			}
		} else {
			if (discardValueFlag) {
				_pPUnitCreated = new PUnit_Break<1, true, false>(_pPUnitMarked, _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_Break<1, false, false>(_pPUnitMarked, _pExprSrc.Reference());
			}
		}
	} else {
		if (_branchDestFlag) {
			if (discardValueFlag) {
				_pPUnitCreated = new PUnit_Break<0, true, true>(_pPUnitMarked);
			} else {
				_pPUnitCreated = new PUnit_Break<0, false, true>(_pPUnitMarked);
			}
		} else {
			if (discardValueFlag) {
				_pPUnitCreated = new PUnit_Break<0, true, false>(_pPUnitMarked);
			} else {
				_pPUnitCreated = new PUnit_Break<0, false, false>(_pPUnitMarked);
			}
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Continue
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_Continue<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	if (discardValueFlag) processor.DiscardValue();
	if (GetPUnitOfLoop()) {
		processor.SetPUnitNext(GetPUnitOfLoop());
	} else {
		processor.SetEventContinue();
		processor.ExitRunLoop();
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Continue<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Continue(loop=%s)", MakeSeqIdString(GetPUnitOfLoop(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Continue::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Continue<1, true>(_pPUnitOfLoop, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Continue<1, false>(_pPUnitOfLoop, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Continue<0, true>(_pPUnitOfLoop);
		} else {
			_pPUnitCreated = new PUnit_Continue<0, false>(_pPUnitOfLoop);
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Miscatch
// Stack View: [] -> [Any] (continue)
//                -> []    (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_Miscatch<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	if (!discardValueFlag) processor.PushValue(GetValue()->Reference());
	processor.ExitRunLoop(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Miscatch<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Miscatch(%s)", GetValue()->ToString(StringStyle().Digest()).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Miscatch::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Miscatch<1, true>(_pValue.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Miscatch<1, false>(_pValue.release(), _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Miscatch<0, true>(_pValue.release());
		} else {
			_pPUnitCreated = new PUnit_Miscatch<0, false>(_pValue.release());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Return
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_Return<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	const PUnit* pPUnit = processor.PopPUnit();
	// Since nullptr means the end of the processor loop, there's no need to
	// pop frame or value from their stacks.
	if (pPUnit) {
		processor.PopFrame();
		if (pPUnit->GetDiscardValueFlag()) processor.DiscardValue();
		processor.SetPUnitNext(pPUnit->GetPUnitCont());
	} else {
		processor.ExitRunLoop();
	}
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Return<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "Return()";
	//AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Return::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Return<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Return<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Return<0, true>();
		} else {
			_pPUnitCreated = new PUnit_Return<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_PushFrame
// Stack View: [prev] -> [prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, typename T_Frame, bool discardValueFlag>
void PUnit_PushFrame<nExprSrc, T_Frame, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	processor.PushFrame<T_Frame>();
	if (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, typename T_Frame, bool discardValueFlag>
String PUnit_PushFrame<nExprSrc, T_Frame, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("PushFrame<%s>()", T_Frame::name);
	AppendInfoToString(str, ss);
	return str;
}

template<typename T_Frame>
PUnit* PUnitFactory_PushFrame<T_Frame>::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_PushFrame<1, T_Frame, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_PushFrame<1, T_Frame, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_PushFrame<0, T_Frame, true>();
		} else {
			_pPUnitCreated = new PUnit_PushFrame<0, T_Frame, false>();
		}
	}
	return _pPUnitCreated;
}

template class PUnitFactory_PushFrame<Frame_Block>;
template class PUnitFactory_PushFrame<Frame_Scope>;

//------------------------------------------------------------------------------
// PUnit_PushFrameFromStack
// Stack View: [prev frame] -> [prev] (continue)
//                          -> []     (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_PushFrameFromStack<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValue(processor.PopValue());
	processor.PushFrame(Value_Frame::GetFrame(*pValue).Reference());
	if (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_PushFrameFromStack<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("PushFrameFromStack()");
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_PushFrameFromStack::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_PushFrameFromStack<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_PushFrameFromStack<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_PushFrameFromStack<0, true>();
		} else {
			_pPUnitCreated = new PUnit_PushFrameFromStack<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_PopFrame
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_PopFrame<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	processor.PopFrame();
	if (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_PopFrame<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "PopFrame()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_PopFrame::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_PopFrame<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_PopFrame<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_PopFrame<0, true>();
		} else {
			_pPUnitCreated = new PUnit_PopFrame<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_NoOperation
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_NoOperation<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	if (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_NoOperation<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "NoOperation()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_NoOperation::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_NoOperation<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_NoOperation<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_NoOperation<0, true>();
		} else {
			_pPUnitCreated = new PUnit_NoOperation<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Terminate
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
void PUnit_Terminate::Exec(Processor& processor) const
{
	processor.Terminate();
}

String PUnit_Terminate::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "Terminate()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Terminate::Create(bool discardValueFlag)
{
	_pPUnitCreated = new PUnit_Terminate();
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_REPLEnd
// Stack View: [] -> []
//------------------------------------------------------------------------------
void PUnit_REPLEnd::Exec(Processor& processor) const
{
	processor.SetPUnitNext(_GetPUnitCont());
}

String PUnit_REPLEnd::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("REPLEnd()");
	return str;
}

//------------------------------------------------------------------------------
// PUnit_Bridge
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
void PUnit_Bridge::Exec(Processor& processor) const
{
	processor.SetPUnitNext(_GetPUnitCont());
}

String PUnit_Bridge::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Bridge(cont=%s)", MakeSeqIdString(_GetPUnitCont(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

}
