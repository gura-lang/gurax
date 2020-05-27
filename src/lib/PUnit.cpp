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
	return String().Format((seqIdOffset == 0)? "#%zu" : "##%zu", pPUnit->GetSeqId(seqIdOffset));
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
// PUnit_Branch
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PUnit_Value
// Stack View: [] -> [Any] (continue)
//                -> []    (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_Value<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	if constexpr (!discardValueFlag) processor.PushValue(GetValue()->Reference());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_Value<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("Value(%s)", GetValue()->ToString(StringStyle().SetDigest()).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Value::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Value<true>(_pValue.release(), _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_Value<false>(_pValue.release(), _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Lookup
// Stack View: [] -> [Any] (continue)
//                -> []    (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_Lookup<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	Frame& frame = processor.GetFrameCur();
	const Value* pValue = frame.Lookup(GetSymbol());
	if (!pValue) {
		Error::Issue(ErrorType::ValueError, "symbol '%s' is not found", GetSymbol()->GetName());
		processor.ErrorDone();
		return;
	}
	if constexpr (!discardValueFlag) processor.PushValue(pValue->Reference());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_Lookup<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("Lookup(`%s)", GetSymbol()->GetName());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Lookup::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Lookup<true>(_pSymbol, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_Lookup<false>(_pSymbol, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Suffixed
// Stack View: [Any] -> [Result] (continue)
//                   -> []       (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_Suffixed<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	const SuffixMgr* pSuffixMgr = Basement::Inst.LookupSuffixMgr(GetTarget(), GetSymbolSuffix());
	RefPtr<Value> pValueResult;
	if (pSuffixMgr) {
		pValueResult.reset(pSuffixMgr->Eval(processor, GetString()));
	} else if (::strlen(GetSymbolSuffix()->GetName()) == 2) {
		pValueResult.reset(new Value_Help(new Help(GetSymbolSuffix(), GetStringReferable().Reference())));
	} else {
		Error::Issue(ErrorType::SuffixError, "suffix '%s' can not be handled", GetSymbolSuffix()->GetName());
		processor.ErrorDone();
		return;
	}
	if constexpr (!discardValueFlag) processor.PushValue(pValueResult.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_Suffixed<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("Suffixed(`%s)", GetSymbolSuffix()->GetName());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Suffixed::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Suffixed<true>(_pStr.Reference(), _target, _pSymbolSuffix, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_Suffixed<false>(_pStr.Reference(), _target, _pSymbolSuffix, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_AssignToSymbol
// Stack View: [Assigned] -> [Assigned] (continue)
//                        -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_AssignToSymbol<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValueAssigned(
		discardValueFlag? processor.PopValue() : processor.PeekValue(0).Reference());
	if (pValueAssigned->IsVType()) {
		VType& vtype = Value_VType::GetVTypeThis(*pValueAssigned);
		vtype.PrepareForAssignment(processor, GetSymbol());
	} else if (pValueAssigned->IsType(VTYPE_Function)) {
		Function& function = Value_Function::GetFunction(*pValueAssigned);
		if (function.GetSymbol()->IsEmpty()) function.SetSymbol(GetSymbol());
	}
	frame.Assign(GetSymbol(), pValueAssigned.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_AssignToSymbol<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("AssignToSymbol(`%s)", GetSymbol()->GetName());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_AssignToSymbol::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_AssignToSymbol<true>(_pSymbol, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_AssignToSymbol<false>(_pSymbol, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_AssignToDeclArg
// Stack View: [Assigned] -> [Assigned] (continue)
//                           []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_AssignToDeclArg<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValueAssigned(
		discardValueFlag? processor.PopValue() : processor.PeekValue(0).Reference());
	frame.AssignWithCast(*_pDeclArg, *pValueAssigned);
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_AssignToDeclArg<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("AssignToDeclArg(`%s)", GetDeclArg().ToString(ss).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_AssignToDeclArg::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_AssignToDeclArg<true>(_pDeclArg.release(), _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_AssignToDeclArg<false>(_pDeclArg.release(), _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_AssignFunction
// Stack View: [] -> [Function] (continue)
//                -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_AssignFunction<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	Frame& frame = processor.GetFrameCur();
	RefPtr<Function> pFunction(GetFunction().Reference());
	pFunction->SetFrameOuter(frame);
	RefPtr<Value> pValueAssigned(new Value_Function(pFunction.release()));
	frame.Assign(GetFunction().GetSymbol(), pValueAssigned->Reference());
	if constexpr (!discardValueFlag) processor.PushValue(pValueAssigned.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_AssignFunction<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("AssignFunction(%s,cont=%s)",
			   GetFunction().ToString(StringStyle().SetCram()).c_str(),
			   MakeSeqIdString(_GetPUnitCont(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_AssignFunction::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_AssignFunction<true>(_pFunction.release(), _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_AssignFunction<false>(_pFunction.release(), _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_AssignMethod
// Stack View: keepTargetFlag = false: [Target] -> [Function]        (continue)
//                                              -> []                (discard)
//             keepTargetFlag = true:  [Target] -> [Target Function] (continue)
//                                              -> [Target]          (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool keepTargetFlag>
void PUnit_AssignMethod<discardValueFlag, keepTargetFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValueTarget(keepTargetFlag? processor.PeekValue(0).Reference() : processor.PopValue());
	RefPtr<Function> pFunction(GetFunction().Reference());
	pFunction->SetFrameOuter(frame);
	if (!pValueTarget->DoAssignCustomMethod(pFunction.Reference())) {
		processor.ErrorDone();
		return;
	}
	if constexpr (!discardValueFlag) processor.PushValue(new Value_Function(pFunction.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag, bool keepTargetFlag>
String PUnit_AssignMethod<discardValueFlag, keepTargetFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("AssignMethod(%s,cont=%s)",
			   GetFunction().ToString(StringStyle().SetCram()).c_str(),
			   MakeSeqIdString(_GetPUnitCont(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_AssignMethod::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		if (_keepTargetFlag) {
			_pPUnitCreated = new PUnit_AssignMethod<true, true>(_pFunction.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_AssignMethod<true, false>(_pFunction.release(), _pExprSrc.Reference());
		}
	} else {
		if (_keepTargetFlag) {
			_pPUnitCreated = new PUnit_AssignMethod<false, true>(_pFunction.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_AssignMethod<false, false>(_pFunction.release(), _pExprSrc.Reference());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_AssignPropSlot
// Stack View: initByNilFlag=false .. [VType ValueInit] -> [VType ValueInit] (continue)
//                                                      -> [VType]           (discard)
//             initByNilFlag=true ..  [VType]           -> [VType]           (continue)
//                                                      -> [VType]           (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool initByNilFlag>
void PUnit_AssignPropSlot<discardValueFlag, initByNilFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	Frame& frame = processor.GetFrameCur();
	VTypeCustom& vtypeCustom = dynamic_cast<VTypeCustom&>(
		Value_VType::GetVTypeThis(processor.PeekValue(initByNilFlag? 0 : 1)));
	RefPtr<Value> pValueInit(
		initByNilFlag? Value::nil() :
		(discardValueFlag? processor.PopValue() : processor.PeekValue(0).Reference()));
	if (!vtypeCustom.AssignPropSlot(frame, GetSymbol(), GetDottedSymbol(), GetFlags(), pValueInit.release())) {
		processor.ErrorDone();
		return;
	}		
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag, bool initByNilFlag>
String PUnit_AssignPropSlot<discardValueFlag, initByNilFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("AssignPropSlot(%s,cont=%s,initByNil=%s)",
			   GetSymbol()->GetName(),
			   MakeSeqIdString(_GetPUnitCont(), seqIdOffset).c_str(), initByNilFlag? "true" : "false");
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_AssignPropSlot::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		if (_initByNilFlag) {
			_pPUnitCreated = new PUnit_AssignPropSlot<true, true>(
				_pSymbol, _pDottedSymbol.release(), _flags, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_AssignPropSlot<true, false>(
				_pSymbol, _pDottedSymbol.release(), _flags, _pExprSrc.Reference());
		}
	} else {
		if (_initByNilFlag) {
			_pPUnitCreated = new PUnit_AssignPropSlot<false, true>(
				_pSymbol, _pDottedSymbol.release(), _flags, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_AssignPropSlot<false, false>(
				_pSymbol, _pDottedSymbol.release(), _flags, _pExprSrc.Reference());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Cast
// Stack View: [Any] -> [Casted] (continue)
//                   -> []       (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_Cast<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Value> pValueCasted(GetVType().Cast(*pValue, GetFlags()));
	if (!pValueCasted) {
		processor.ErrorDone();
		return;
	}
	if constexpr (!discardValueFlag) processor.PushValue(pValueCasted.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_Cast<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("Cast(%s)", GetVType().MakeFullName().c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Cast::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Cast<true>(_vtype, _flags, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_Cast<false>(_vtype, _flags, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_GenIterator
// Stack View: [Iterable] -> [Iterator] (continue)
//                        -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_GenIterator<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Iterator> pIterator(pValue->GenIterator());
	if (!pIterator) {
		processor.ErrorDone();
		return;
	}
	if constexpr (!discardValueFlag) processor.PushValue(new Value_Iterator(pIterator.release()));
	processor.SetPUnitNext(_GetPUnitCont());
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
		_pPUnitCreated = new PUnit_GenIterator<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_GenIterator<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_GenIterator_Range
// Stack View: [Number] -> [Iterator] (continue)
//                      -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_GenIterator_Range<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValue(processor.PopValue());
	int num = Value_Number::GetNumber<Int>(*pValue);
	RefPtr<Iterator> pIterator(new Iterator_Range(num));
	if constexpr (!discardValueFlag) processor.PushValue(new Value_Iterator(pIterator.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_GenIterator_Range<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenIterator_Range()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_GenIterator_Range::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_GenIterator_Range<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_GenIterator_Range<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_GenIterator_Counter
// Stack View: [] -> [Iterator] (continue)
//                -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_GenIterator_Counter<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Iterator> pIterator(new Iterator_Counter());
	if constexpr (!discardValueFlag) processor.PushValue(new Value_Iterator(pIterator.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_GenIterator_Counter<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenIterator_Counter()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_GenIterator_Counter::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_GenIterator_Counter<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_GenIterator_Counter<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_GenIterator_ForLister
// Stack View: [Value] -> [Value Iterator] (continue)
//                     -> [Value]          (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_GenIterator_ForLister<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	Value& value(processor.PeekValue(0));
	RefPtr<Iterator> pIterator;
	if (value.IsIterable()) {
		pIterator.reset(value.GenIterator());
	} else {
		pIterator.reset(new Iterator_Const(value.Reference()));
	}
	if constexpr (!discardValueFlag) processor.PushValue(new Value_Iterator(pIterator.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_GenIterator_ForLister<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenIterator_ForLister()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_GenIterator_ForLister::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_GenIterator_ForLister<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_GenIterator_ForLister<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_GenIterator_for
// Stack View: [Iterator1 .. IteratorN] -> [Iterator] (continue)
//                                      -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_GenIterator_for<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<IteratorOwner> pIteratorOwner(new IteratorOwner());
	for (size_t i = 0; i < GetDeclArgOwner().size(); i++) {
		RefPtr<Value> pValue(processor.PopValue());
		pIteratorOwner->push_back(Value_Iterator::GetIterator(*pValue).Reference());
	}
	RefPtr<Iterator> pIterator(
		new Iterator_for(processor.Reference(), GetExprOfBlock().Reference(),
						 GetDeclArgOwner().Reference(), pIteratorOwner.release(), GetSkipNilFlag()));
	if constexpr (!discardValueFlag) processor.PushValue(new Value_Iterator(pIterator.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_GenIterator_for<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenIterator_for()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_GenIterator_for::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_GenIterator_for<true>(
			_pExprOfBlock.Reference(), _pDeclArgOwner.Reference(), _skipNilFlag, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_GenIterator_for<false>(
			_pExprOfBlock.Reference(), _pDeclArgOwner.Reference(), _skipNilFlag, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_GenIterator_while
// Stack View: [] -> [Iterator] (continue)
//                -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_GenIterator_while<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Iterator> pIterator(new Iterator_while(
								   processor.Reference(), GetExprCriteria().Reference(),
								   GetExprOfBlock().Reference(), GetSkipNilFlag()));
	if constexpr (!discardValueFlag) processor.PushValue(new Value_Iterator(pIterator.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_GenIterator_while<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenIterator_while()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_GenIterator_while::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_GenIterator_while<true>(
			_pExprCriteria.Reference(), _pExprOfBlock.Reference(), _skipNilFlag, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_GenIterator_while<false>(
			_pExprCriteria.Reference(), _pExprOfBlock.Reference(), _skipNilFlag, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_GenIterator_repeat
// Stack View: finiteFlag = false: []       -> [Iterator] (continue)
//                                          -> []         (discard)
//             finiteFlag = true:  [Number] -> [Iterator] (continue)
//                                          -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_GenIterator_repeat<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Iterator> pIterator;
	if (GetFiniteFlag()) {
		RefPtr<Value> pValue(processor.PopValue());
		size_t cnt = Value_Number::GetNumber<size_t>(*pValue);
		pIterator.reset(new Iterator_repeat(
							processor.Reference(), GetExprOfBlock().Reference(), true, GetSkipNilFlag(), cnt));
	} else {
		pIterator.reset(new Iterator_repeat(
							processor.Reference(), GetExprOfBlock().Reference(), false, GetSkipNilFlag()));
	}
	if constexpr (!discardValueFlag) processor.PushValue(new Value_Iterator(pIterator.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_GenIterator_repeat<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenIterator_repeat()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_GenIterator_repeat::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_GenIterator_repeat<true>(
			_pExprOfBlock.Reference(), _finiteFlag, _skipNilFlag, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_GenIterator_repeat<false>(
			_pExprOfBlock.Reference(), _finiteFlag, _skipNilFlag, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_EvalIterator
// Stack View: [Iterator] -> [Iterator Elem] (continue)
//                        -> [Iterator]      (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_EvalIterator<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	Iterator& iterator = Value_Iterator::GetIterator(processor.PeekValue(GetOffset()));
	RefPtr<Value> pValueElem(iterator.NextValue());
	if (pValueElem) {
		if constexpr (!discardValueFlag) processor.PushValue(pValueElem.release());
		processor.SetPUnitNext(_GetPUnitCont());
	} else if (_raiseFlag) {
		Error::Issue(ErrorType::IteratorError, "insufficient number of values");
		processor.ErrorDone();
	} else {
		processor.SetPUnitNext(GetPUnitBranchDest());
	}
}

template<bool discardValueFlag>
String PUnit_EvalIterator<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("EvalIterator(offsetToIterator=%zu,branchdest=%s)", GetOffset(),
			   MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_EvalIterator::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_EvalIterator<true>(_offset, _raiseFlag, _pPUnitBranchDest, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_EvalIterator<false>(_offset, _raiseFlag, _pPUnitBranchDest, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_ForEach
// Stack View: [Iterator1..n ..] -> [Iterator1..n ..] (continue)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_ForEach<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
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

template<bool discardValueFlag>
String PUnit_ForEach<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("ForEach(offsetToIterator=%zu,branchdest=%s, decls=[%s])", GetOffset(),
			   MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str(),
			   GetDeclArgOwner().ToString(StringStyle().SetDigest().SetCram()).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_ForEach::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_ForEach<true>(
			_offset, _pDeclArgOwner.release(), _pPUnitBranchDest, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_ForEach<false>(
			_offset, _pDeclArgOwner.release(), _pPUnitBranchDest, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_UnaryOp
// Stack View: [Any] -> [Result] (continue)
//                   -> []       (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_UnaryOp<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Value> pValueResult(GetOperator()->EvalUnary(processor, *pValue));
	if (pValueResult->IsUndefined()) {
		processor.ErrorDone();
		return;
	}
	if constexpr (!discardValueFlag) processor.PushValue(pValueResult.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_UnaryOp<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("UnaryOp(%s)", GetOperator()->GetSymbol());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_UnaryOp::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_UnaryOp<true>(_pOp, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_UnaryOp<false>(_pOp, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_BinaryOp
// Stack View: [Left Right] -> [Result] (continue)
//                          -> []       (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_BinaryOp<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValueRight(processor.PopValue());
	RefPtr<Value> pValueLeft(processor.PopValue());
	RefPtr<Value> pValueResult(GetOperator()->EvalBinary(processor, *pValueLeft, *pValueRight));
	if (pValueResult->IsUndefined()) {
		processor.ErrorDone();
		return;
	}
	if constexpr (!discardValueFlag) processor.PushValue(pValueResult.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_BinaryOp<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("BinaryOp(%s)", GetOperator()->GetSymbol());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_BinaryOp::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_BinaryOp<true>(_pOp, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_BinaryOp<false>(_pOp, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Import
// Stack View: [] -> [Module] (continue)
//                -> []    (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_Import<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Module> pModule(Module::ImportHierarchy(
							   processor, GetDottedSymbol(), GetBinaryFlag(), GetOverwriteFlag()));
	if (!pModule) {
		processor.ErrorDone();
		return;
	}
	if (GetMixInFlag()) {
		if (!pModule->GetFrame().ExportTo(processor.GetFrameCur(), GetOverwriteFlag())) {
			processor.ErrorDone();
			return;
		}
	} else if (GetSymbolForModuleFlag()) {
		if (!pModule->AssignToFrame(processor, GetSymbolList(), GetOverwriteFlag())) {
			processor.ErrorDone();
			return;
		}
	}
	if constexpr (!discardValueFlag) processor.PushValue(new Value_Module(pModule.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_Import<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("Import(`%s)", GetDottedSymbol().ToString().c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Import::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Import<true>(
			_pDottedSymbol.release(), _pSymbolList.release(),
			_binaryFlag, _mixInFlag, _overwriteFlag, _symbolForModuleFlag, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_Import<false>(
			_pDottedSymbol.release(), _pSymbolList.release(),
			_binaryFlag, _mixInFlag, _overwriteFlag, _symbolForModuleFlag, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_CreateVType
// Stack View: inheritFlag=false .. []         -> [VType] (continue)
//                                             -> []      (discard)
//             inheritFlag=true ..  [VTypeInh] -> [VType] (continue)
//                                  [VTypeInh] -> []      (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool inheritFlag>
void PUnit_CreateVType<discardValueFlag, inheritFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	VType* pVTypeInh = &VTYPE_Object;
	if (inheritFlag) {
		RefPtr<Value> pValueVTypeInh(processor.PopValue());
		pVTypeInh = &Value_VType::GetVTypeThis(*pValueVTypeInh);
	}
	VTypeCustom* pVType = new VTypeCustom();
	pVType->Declare(*pVTypeInh, VType::Flag::Mutable);
	pVType->Inherit();
	if constexpr (!discardValueFlag) processor.PushValue(new Value_VType(*pVType));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag, bool inheritFlag>
String PUnit_CreateVType<discardValueFlag, inheritFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("CreateVType(inheritFlag=%d)", inheritFlag);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_CreateVType::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		if (_inheritFlag) {
			_pPUnitCreated = new PUnit_CreateVType<true, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_CreateVType<true, false>(_pExprSrc.Reference());
		}
	} else {
		if (_inheritFlag) {
			_pPUnitCreated = new PUnit_CreateVType<false, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_CreateVType<false, false>(_pExprSrc.Reference());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_CompleteStruct
// Stack View: [VType] -> [VType] (continue)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_CompleteStruct<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	VTypeCustom& vtypeCustom = dynamic_cast<VTypeCustom&>(Value_VType::GetVTypeThis(processor.PeekValue(0)));
	RefPtr<PropSlotOwner> pPropSlotOwner(vtypeCustom.GetPropSlotMap().CreatePropSlotOwner());
	pPropSlotOwner->SortBySeqId();
	RefPtr<DeclCallable> pDeclCallable(new DeclCallable());
	pDeclCallable->GetDeclBlock().SetOccur(DeclBlock::Occur::ZeroOrOnce);
	for (PropSlot* pPropSlot : *pPropSlotOwner) {
		PropSlot::Flags flags = pPropSlot->GetFlags();
		const DeclArg::Occur& occur = DeclArg::Occur::ZeroOrOnce;
		flags &= ~(PropSlot::Flag::Nil | PropSlot::Flag::OfClass | PropSlot::Flag::OfInstance |
				   PropSlot::Flag::Public | PropSlot::Flag::Readable | PropSlot::Flag::Writable);
		pDeclCallable->GetDeclArgOwner().push_back(
			new DeclArg(pPropSlot->GetSymbol(), pPropSlot->GetVType(), occur, flags, nullptr));
	}
	vtypeCustom.SetConstructor(new VTypeCustom::ConstructorStruct(
								   vtypeCustom, pDeclCallable.release(), pPropSlotOwner.release()));
	if (Error::IsIssued()) {
		processor.ErrorDone();
		return;
	}
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_CompleteStruct<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "CompleteStruct()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_CompleteStruct::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_CompleteStruct<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_CompleteStruct<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_CreateList
// Stack View: [] -> [List] (continue)
//                -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_CreateList<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	if (GetSizeReserve() > 0) pValueOwner->reserve(GetSizeReserve());
	if constexpr (!discardValueFlag) processor.PushValue(new Value_List(pValueOwner.release()));
	processor.SetPUnitNext(_GetPUnitCont());
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
		_pPUnitCreated = new PUnit_CreateList<true>(_sizeReserve, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_CreateList<false>(_sizeReserve, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_ListElem
// Stack View: [List .. Elem] -> [List ..] (continue)
//                            -> []        (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool xlistFlag, bool expandFlag>
void PUnit_ListElem<discardValueFlag, xlistFlag, expandFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValueElem(processor.PopValue());
	ValueTypedOwner& valueTypedOwner = Value_List::GetValueTypedOwner(processor.PeekValue(GetOffset()));
	if (expandFlag && pValueElem->IsIterator()) {
		Iterator& iterator = Value_Iterator::GetIterator(*pValueElem);
		if (!iterator.MustBeFinite()) {
			processor.ErrorDone();
			return;
		}
		if (xlistFlag) {
			valueTypedOwner.AddX(iterator);
		} else {
			valueTypedOwner.Add(iterator);
		}
	} else if (expandFlag && pValueElem->IsList()) {
		if (xlistFlag) {
			valueTypedOwner.AddX(Value_List::GetValueTypedOwner(*pValueElem));
		} else {
			valueTypedOwner.Add(Value_List::GetValueTypedOwner(*pValueElem));
		}
	} else if (!pValueElem->IsUndefined() && (!xlistFlag || pValueElem->IsValid())) {
		valueTypedOwner.Add(pValueElem.release());
	}
	if constexpr (discardValueFlag) processor.RemoveValues(0, GetOffset() + 1);
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag, bool xlistFlag, bool expandFlag>
String PUnit_ListElem<discardValueFlag, xlistFlag, expandFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("ListElem(offsetToList=%zu)", GetOffset());
	if (xlistFlag) str += ":xlist";
	if (expandFlag) str += ":expand";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_ListElem::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		if (_xlistFlag) {
			if (_expandFlag) {
				_pPUnitCreated = new PUnit_ListElem<true, true, true>(_offset, _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_ListElem<true, true, false>(_offset, _pExprSrc.Reference());
			}
		} else {
			if (_expandFlag) {
				_pPUnitCreated = new PUnit_ListElem<true, false, true>(_offset, _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_ListElem<true, false, false>(_offset, _pExprSrc.Reference());
			}
		}
	} else {
		if (_xlistFlag) {
			if (_expandFlag) {
				_pPUnitCreated = new PUnit_ListElem<false, true, true>(_offset, _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_ListElem<false, true, false>(_offset, _pExprSrc.Reference());
			}
		} else {
			if (_expandFlag) {
				_pPUnitCreated = new PUnit_ListElem<false, false, true>(_offset, _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_ListElem<false, false, false>(_offset, _pExprSrc.Reference());
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
template<bool discardValueFlag>
void PUnit_CreateDict<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	if constexpr (!discardValueFlag) processor.PushValue(new Value_Dict());
	processor.SetPUnitNext(_GetPUnitCont());
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
		_pPUnitCreated = new PUnit_CreateDict<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_CreateDict<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_DictElem
// Stack View: [Dict Key Elem] -> [Dict] (continue)
//                             -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_DictElem<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValueElem(processor.PopValue());
	RefPtr<Value> pValueKey(processor.PopValue());
	ValueDict& valueDict = Value_Dict::GetValueDict(processor.PeekValue(GetOffset()));
	valueDict.Assign(pValueKey.release(), pValueElem.release());
	if constexpr (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_DictElem<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("DictElem(offsetToDict=%zu)", GetOffset());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_DictElem::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_DictElem<true>(_offset, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_DictElem<false>(_offset, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Index
// Stack View: [Car] -> [Index(Car)] (continue)
//                   -> []           (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_Index<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValueCar(processor.PopValue());
	RefPtr<Index> pIndex(new Index(pValueCar.release(), GetAttr().Reference()));
	if (GetSizeReserve() > 0) pIndex->Reserve(GetSizeReserve());
	if constexpr (!discardValueFlag) processor.PushValue(new Value_Index(pIndex.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_Index<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "Index()";
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Index::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Index<true>(_pAttr.release(), _sizeReserve, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_Index<false>(_pAttr.release(), _sizeReserve, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_FeedIndex
// Stack View: [Index(Car) Any] -> [Index(Car)] (continue)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_FeedIndex<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValue(processor.PopValue());
	Index& index = Value_Index::GetIndex(processor.PeekValue(0));
	index.FeedValue(pValue.release());
	if (Error::IsIssued()) {
		processor.ErrorDone();
		return;
	}
	processor.SetPUnitNext(_GetPUnitCont());
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
		_pPUnitCreated = new PUnit_FeedIndex<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_FeedIndex<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_IndexGet
// Stack View: [Index(Car)] -> [Elems] (continue)
//                          -> []      (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_IndexGet<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value_Index> pValueIndex(dynamic_cast<Value_Index*>(processor.PopValue()));
	Index& index = pValueIndex->GetIndex();
	RefPtr<Value> pValueElems(index.IndexGet());
	if (Error::IsIssued()) {
		processor.ErrorDone();
		return;
	}
	if constexpr (!discardValueFlag) processor.PushValue(pValueElems.release());
	processor.SetPUnitNext(_GetPUnitCont());
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
		_pPUnitCreated = new PUnit_IndexGet<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_IndexGet<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_IndexSet
// Stack View: valueFirst=false: [Index(Car) Elems] -> [Elems] (continue)
//                                                  -> []      (discard)
//             valueFirst=true:  [Elems Index(Car)] -> [Elems] (continue)
//                                                  -> []      (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool valueFirstFlag>
void PUnit_IndexSet<discardValueFlag, valueFirstFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValueElems;
	RefPtr<Value_Index> pValueIndex;
	if (valueFirstFlag) {
		pValueIndex.reset(dynamic_cast<Value_Index*>(processor.PopValue()));
		pValueElems.reset(processor.PopValue());
	} else {
		pValueElems.reset(processor.PopValue());
		pValueIndex.reset(dynamic_cast<Value_Index*>(processor.PopValue()));
	}
	Index& index = pValueIndex->GetIndex();
	index.IndexSet(pValueElems->Reference());
	if (Error::IsIssued()) {
		processor.ErrorDone();
		return;
	}
	if constexpr (!discardValueFlag) processor.PushValue(pValueElems.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag, bool valueFirstFlag>
String PUnit_IndexSet<discardValueFlag, valueFirstFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "IndexSet()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_IndexSet::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		if (_valueFirstFlag) {
			_pPUnitCreated = new PUnit_IndexSet<true, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_IndexSet<true, false>(_pExprSrc.Reference());
		}
	} else {
		if (_valueFirstFlag) {
			_pPUnitCreated = new PUnit_IndexSet<false, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_IndexSet<false, false>(_pExprSrc.Reference());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_IndexOpApply
// Stack View: valueFirst=false: [Index(Car) Elems] -> [Rtn] (continue)
//                                                  -> []    (discard)
//             valueFirst=true:  [Elems Index(Car)] -> [Rtn] (continue)
//                                                  -> []    (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool valueFirstFlag>
void PUnit_IndexOpApply<discardValueFlag, valueFirstFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValueElems;
	RefPtr<Value_Index> pValueIndex;
	if (valueFirstFlag) {
		pValueIndex.reset(dynamic_cast<Value_Index*>(processor.PopValue()));
		pValueElems.reset(processor.PopValue());
	} else {
		pValueElems.reset(processor.PopValue());
		pValueIndex.reset(dynamic_cast<Value_Index*>(processor.PopValue()));
	}
	Index& index = pValueIndex->GetIndex();
	RefPtr<Value> pValueRtn(index.IndexOpApply(*pValueElems, processor, *_pOp));
	if (Error::IsIssued()) {
		processor.ErrorDone();
		return;
	}
	if constexpr (!discardValueFlag) processor.PushValue(pValueRtn.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag, bool valueFirstFlag>
String PUnit_IndexOpApply<discardValueFlag, valueFirstFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "IndexOpApply()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_IndexOpApply::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		if (_valueFirstFlag) {
			_pPUnitCreated = new PUnit_IndexOpApply<true, true>(_pOp, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_IndexOpApply<true, false>(_pOp, _pExprSrc.Reference());
		}
	} else {
		if (_valueFirstFlag) {
			_pPUnitCreated = new PUnit_IndexOpApply<false, true>(_pOp, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_IndexOpApply<false, false>(_pOp, _pExprSrc.Reference());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_MemberSet_Normal
// Stack View: valueFirst=false: [Target Assigned] -> [Assigned] (continue)
//                                                 -> []         (discard)
//             valueFirst=true:  [Assigned Target] -> [Assigned] (continue)
//                                                 -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool valueFirstFlag>
void PUnit_MemberSet_Normal<discardValueFlag, valueFirstFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValueAssigned;
	RefPtr<Value> pValueTarget;
	if (valueFirstFlag) {
		pValueTarget.reset(processor.PopValue());
		pValueAssigned.reset(processor.PopValue());
	} else {
		pValueAssigned.reset(processor.PopValue());
		pValueTarget.reset(processor.PopValue());
	}
	if (!pValueTarget->PropSet(GetSymbol(), pValueAssigned->Reference(), GetAttr())) {
		processor.ErrorDone();
		return;
	}
	if constexpr (!discardValueFlag) processor.PushValue(pValueAssigned.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag, bool valueFirstFlag>
String PUnit_MemberSet_Normal<discardValueFlag, valueFirstFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("MemberSet_Normal(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_MemberSet_Normal::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		if (_valueFirstFlag) {
			_pPUnitCreated = new PUnit_MemberSet_Normal<true, true>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_MemberSet_Normal<true, false>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		}
	} else {
		if (_valueFirstFlag) {
			_pPUnitCreated = new PUnit_MemberSet_Normal<false, true>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_MemberSet_Normal<false, false>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_MemberSet_Map
// Stack View: valueFirst=false: [Target Assigned] -> [Assigned] (continue)
//                                                 -> []         (discard)
//             valueFirst=true:  [Assigned Target] -> [Assigned] (continue)
//                                                 -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool valueFirstFlag>
void PUnit_MemberSet_Map<discardValueFlag, valueFirstFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValueAssigned;
	RefPtr<Value> pValueTarget;
	if (valueFirstFlag) {
		pValueTarget.reset(processor.PopValue());
		pValueAssigned.reset(processor.PopValue());
	} else {
		pValueAssigned.reset(processor.PopValue());
		pValueTarget.reset(processor.PopValue());
	}
	RefPtr<Iterator> pIteratorTarget(pValueTarget->GenIterator());
	if (!pIteratorTarget) {
		Error::Issue(ErrorType::IteratorError, "the target not is not iterable");
		processor.ErrorDone();
		return;
	}
	if (GetMapAssignedFlag() && pValueAssigned->IsIterable()) {
		RefPtr<Iterator> pIteratorAssigned(pValueAssigned->GenIterator());
		if (pIteratorTarget->IsInfinite() && pIteratorAssigned->IsInfinite()) {
			Error::Issue(ErrorType::IteratorError, "infinite iterator is unacceptable");
			processor.ErrorDone();
			return;
		}
		for (;;) {
			RefPtr<Value> pValueTargetEach(pIteratorTarget->NextValue());
			if (!pValueTargetEach) break;
			RefPtr<Value> pValueAssignedEach(pIteratorAssigned->NextValue());
			if (!pValueAssignedEach) break;
			if (!pValueTargetEach->PropSet(GetSymbol(), pValueAssignedEach->Reference(), GetAttr())) {
				processor.ErrorDone();
				return;
			}
		}
		if (Error::IsIssued()) {
			processor.ErrorDone();
			return;
		}
	} else {
		if (pIteratorTarget->IsInfinite()) {
			Error::Issue(ErrorType::IteratorError, "infinite iterator is unacceptable");
			processor.ErrorDone();
			return;
		}
		for (;;) {
			RefPtr<Value> pValueTargetEach(pIteratorTarget->NextValue());
			if (!pValueTargetEach) break;
			if (!pValueTargetEach->PropSet(GetSymbol(), pValueAssigned->Reference(), GetAttr())) {
				processor.ErrorDone();
				return;
			}
		}
		if (Error::IsIssued()) {
			processor.ErrorDone();
			return;
		}
	}
	if constexpr (!discardValueFlag) processor.PushValue(pValueAssigned.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag, bool valueFirstFlag>
String PUnit_MemberSet_Map<discardValueFlag, valueFirstFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("MemberSet_Map(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_MemberSet_Map::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		if (_valueFirstFlag) {
			_pPUnitCreated = new PUnit_MemberSet_Map<true, true>(_pSymbol, _pAttr.release(), _mapAssignedFlag, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_MemberSet_Map<true, false>(_pSymbol, _pAttr.release(), _mapAssignedFlag, _pExprSrc.Reference());
		}
	} else {
		if (_valueFirstFlag) {
			_pPUnitCreated = new PUnit_MemberSet_Map<false, true>(_pSymbol, _pAttr.release(), _mapAssignedFlag, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_MemberSet_Map<false, false>(_pSymbol, _pAttr.release(), _mapAssignedFlag, _pExprSrc.Reference());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_MemberOpApply_Normal
// Stack View: valueFirst=false: [Target Applied] -> [Assigned] (continue)
//                                                -> []         (discard)
//             valueFirst=true:  [Applied Target] -> [Assigned] (continue)
//                                                -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool valueFirstFlag>
void PUnit_MemberOpApply_Normal<discardValueFlag, valueFirstFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValueApplied;
	RefPtr<Value> pValueTarget;
	if (valueFirstFlag) {
		pValueTarget.reset(processor.PopValue());
		pValueApplied.reset(processor.PopValue());
	} else {
		pValueApplied.reset(processor.PopValue());
		pValueTarget.reset(processor.PopValue());
	}
	Value* pValueProp = pValueTarget->PropGet(GetSymbol(), GetAttr(), true);
	if (!pValueProp) {
		processor.ErrorDone();
		return;
	}
	RefPtr<Value> pValueAssigned(GetOperator().EvalBinary(processor, *pValueProp, *pValueApplied));
	if (!pValueTarget->PropSet(GetSymbol(), pValueAssigned->Reference(), GetAttr())) {
		processor.ErrorDone();
		return;
	}
	if constexpr (!discardValueFlag) processor.PushValue(pValueAssigned.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag, bool valueFirstFlag>
String PUnit_MemberOpApply_Normal<discardValueFlag, valueFirstFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("MemberOpApply_Normal(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_MemberOpApply_Normal::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		if (_valueFirstFlag) {
			_pPUnitCreated = new PUnit_MemberOpApply_Normal<true, true>(_pSymbol, _pAttr.release(), _pOp, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_MemberOpApply_Normal<true, false>(_pSymbol, _pAttr.release(), _pOp, _pExprSrc.Reference());
		}
	} else {
		if (_valueFirstFlag) {
			_pPUnitCreated = new PUnit_MemberOpApply_Normal<false, true>(_pSymbol, _pAttr.release(), _pOp, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_MemberOpApply_Normal<false, false>(_pSymbol, _pAttr.release(), _pOp, _pExprSrc.Reference());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_MemberOpApply_Map
// Stack View: valueFirst=false: [Target Applied] -> [Assigned] (continue)
//                                                -> []         (discard)
//             valueFirst=true:  [Applied Target] -> [Assigned] (continue)
//                                                -> []         (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool valueFirstFlag>
void PUnit_MemberOpApply_Map<discardValueFlag, valueFirstFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValueApplied;
	RefPtr<Value> pValueTarget;
	if (valueFirstFlag) {
		pValueTarget.reset(processor.PopValue());
		pValueApplied.reset(processor.PopValue());
	} else {
		pValueApplied.reset(processor.PopValue());
		pValueTarget.reset(processor.PopValue());
	}
	Value* pValueProp = pValueTarget->PropGet(GetSymbol(), GetAttr(), true);
	if (!pValueProp) {
		processor.ErrorDone();
		return;
	}
	RefPtr<Value> pValueAssigned(GetOperator().EvalBinary(processor, *pValueProp, *pValueApplied));
	if (!pValueTarget->PropSet(GetSymbol(), pValueAssigned->Reference(), GetAttr())) {
		processor.ErrorDone();
		return;
	}
	if constexpr (!discardValueFlag) processor.PushValue(pValueAssigned.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag, bool valueFirstFlag>
String PUnit_MemberOpApply_Map<discardValueFlag, valueFirstFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("MemberOpApply_Map(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_MemberOpApply_Map::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		if (_valueFirstFlag) {
			_pPUnitCreated = new PUnit_MemberOpApply_Map<true, true>(_pSymbol, _pAttr.release(), _pOp, _mapAssignedFlag, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_MemberOpApply_Map<true, false>(_pSymbol, _pAttr.release(), _pOp, _mapAssignedFlag, _pExprSrc.Reference());
		}
	} else {
		if (_valueFirstFlag) {
			_pPUnitCreated = new PUnit_MemberOpApply_Map<false, true>(_pSymbol, _pAttr.release(), _pOp, _mapAssignedFlag, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_MemberOpApply_Map<false, false>(_pSymbol, _pAttr.release(), _pOp, _mapAssignedFlag, _pExprSrc.Reference());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_MemberGet_Normal
// Stack View: [Target] -> [Member(Target+Prop)] (continue, callable)
//                      -> [Prop]                (continue, not callable)
//                      -> []                    (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_MemberGet_Normal<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValueTarget(processor.PopValue());
	Value* pValueProp = pValueTarget->PropGet(GetSymbol(), GetAttr(), true);
	if (!pValueProp) {
		processor.ErrorDone();
		return;
	}
	if constexpr (!discardValueFlag) processor.PushValue(pValueProp->AsMember(*pValueTarget));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_MemberGet_Normal<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("Member_Normal(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_MemberGet_Normal::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_MemberGet_Normal<true>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_MemberGet_Normal<false>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_MemberGet_MapAlong
// Stack View: [Target] -> [Member(Target+Prop)] (continue, callable)
//                      -> [Prop]                (continue, not callable)
//                      -> []                    (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_MemberGet_MapAlong<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValueTarget(processor.PopValue());
	if (pValueTarget->IsIterable()) {
		RefPtr<Iterator> pIteratorTarget(pValueTarget->GenIterator());
		RefPtr<Iterator> pIterator(new Iterator_Member_MapAlong(
									   processor.Reference(), pIteratorTarget.release(),
									   GetSymbol(), GetAttr().Reference()));
		if constexpr (!discardValueFlag) processor.PushValue(new Value_ArgMapper(pIterator.release()));
	} else {
		Value* pValueProp = pValueTarget->PropGet(GetSymbol(), GetAttr(), true);
		if (!pValueProp) {
			processor.ErrorDone();
			return;
		}
		if constexpr (!discardValueFlag) processor.PushValue(pValueProp->AsMember(*pValueTarget));
	}
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_MemberGet_MapAlong<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("MemberGet_MapAlong(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_MemberGet_MapAlong::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_MemberGet_MapAlong<true>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_MemberGet_MapAlong<false>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_MemberGet_MapToList
// Stack View: [Target] -> [Member(Target+Prop)] (continue, callable)
//                      -> [Prop]                (continue, not callable)
//                      -> []                    (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_MemberGet_MapToList<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValueTarget(processor.PopValue());
	if (pValueTarget->IsIterable()) {
		RefPtr<Iterator> pIteratorTarget(pValueTarget->GenIterator());
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		for (;;) {
			RefPtr<Value> pValueTargetEach(pIteratorTarget->NextValue());
			if (!pValueTargetEach) break;
			Value* pValueProp = pValueTargetEach->PropGet(GetSymbol(), GetAttr(), true);
			if (!pValueProp) {
				processor.ErrorDone();
				return;
			} else {
				pValueOwner->push_back(pValueProp->AsMember(*pValueTargetEach));
			}
		}
		if (Error::IsIssued()) {
			processor.ErrorDone();
			return;
		}
		if constexpr (!discardValueFlag) {
			processor.PushValue(new Value_List(new ValueTypedOwner(pValueOwner.release())));
		}
	} else {
		Value* pValueProp = pValueTarget->PropGet(GetSymbol(), GetAttr(), true);
		if (!pValueProp) {
			processor.ErrorDone();
			return;
		}
		if constexpr (!discardValueFlag) processor.PushValue(pValueProp->AsMember(*pValueTarget));
	}
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_MemberGet_MapToList<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("MemberGet_MapToList(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_MemberGet_MapToList::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_MemberGet_MapToList<true>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_MemberGet_MapToList<false>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_MemberGet_MapToIter
// Stack View: [Target] -> [Member(Target+Prop)] (continue, callable)
//                      -> [Prop]                (continue, not callable)
//                      -> []                    (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_MemberGet_MapToIter<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValueTarget(processor.PopValue());
	if (pValueTarget->IsIterable()) {
		RefPtr<Iterator> pIteratorTarget(pValueTarget->GenIterator());
		RefPtr<Iterator> pIterator(new Iterator_Member_MapToIter(
									   processor.Reference(), pIteratorTarget.release(),
									   GetSymbol(), GetAttr().Reference()));
		if constexpr (!discardValueFlag) processor.PushValue(new Value_Iterator(pIterator.release()));
	} else {
		Value* pValueProp = pValueTarget->PropGet(GetSymbol(), GetAttr(), true);
		if (!pValueProp) {
			processor.ErrorDone();
			return;
		}
		if constexpr (!discardValueFlag) processor.PushValue(pValueProp->AsMember(*pValueTarget));
	}
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_MemberGet_MapToIter<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("MemberGet_MapToIter(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_MemberGet_MapToIter::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_MemberGet_MapToIter<true>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_MemberGet_MapToIter<false>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Argument
// Stack View: keepCarFlag = false: [Car] -> [Argument(Car)]     (continue)
//                                        -> []                  (discard)
//             keepCarFlag = true:  [Car] -> [Car Argument(Car)] (continue)
//                                        -> [Car]               (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool keepCarFlag>
PUnit_Argument<discardValueFlag, keepCarFlag>::PUnit_Argument(const Attribute& attr, Expr_Block* pExprOfBlock, Expr* pExpr) :
	_pAttr(new Attribute()), _flags(DeclCallable::Flag::None), _pExprOfBlock(pExprOfBlock), _pExprSrc(pExpr)
{
	for (const Symbol* pSymbol : attr.GetSymbols()) {
		DeclCallable::Flags flag = DeclCallable::SymbolToFlag(pSymbol);
		_flags |= flag;
		if (!flag) _pAttr->AddSymbol(pSymbol);
	}
	_pAttr->AddSymbolsOpt(attr.GetSymbolsOpt());
}

template<bool discardValueFlag, bool keepCarFlag>
void PUnit_Argument<discardValueFlag, keepCarFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValueCar(keepCarFlag? processor.PeekValue(0).Reference() : processor.PopValue());
	const DeclCallable* pDeclCallable = pValueCar->GetDeclCallableWithError();
	if (!pDeclCallable || !pDeclCallable->CheckAttribute(GetAttr())) {
		processor.ErrorDone();
		return;
	}
	RefPtr<Argument> pArgument(
		new Argument(pValueCar.release(), pDeclCallable->Reference(),
					 GetAttr().Reference(), pDeclCallable->GetFlags() | GetFlags(), Value::undefined(),
					 Expr_Block::Reference(GetExprOfBlock())));
	if constexpr (!discardValueFlag) processor.PushValue(new Value_Argument(pArgument.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag, bool keepCarFlag>
String PUnit_Argument<discardValueFlag, keepCarFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	if (_pExprOfBlock) {
		str.Format("Argument(block=%s)", MakeSeqIdString(_pExprOfBlock->GetPUnitFirst(), seqIdOffset).c_str());
	} else {
		str += "Argument()";
	}
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Argument::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		if (_keepCarFlag) {
			_pPUnitCreated = new PUnit_Argument<true, true>(*_pAttr, _pExprOfBlock.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Argument<true, false>(*_pAttr, _pExprOfBlock.release(), _pExprSrc.Reference());
		}
	} else {
		if (_keepCarFlag) {
			_pPUnitCreated = new PUnit_Argument<false, true>(*_pAttr, _pExprOfBlock.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Argument<false, false>(*_pAttr, _pExprOfBlock.release(), _pExprSrc.Reference());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_ArgumentDelegation
// Stack View: keepCarFlag = false: [Car Expr] -> [Argument(Car)] (continue)
//                                             -> []              (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
PUnit_ArgumentDelegation<discardValueFlag>::PUnit_ArgumentDelegation(const Attribute& attr, Expr* pExpr) :
	_pAttr(new Attribute()), _flags(DeclCallable::Flag::None), _pExprSrc(pExpr)
{
	for (const Symbol* pSymbol : attr.GetSymbols()) {
		DeclCallable::Flags flag = DeclCallable::SymbolToFlag(pSymbol);
		_flags |= flag;
		if (!flag) _pAttr->AddSymbol(pSymbol);
	}
	_pAttr->AddSymbolsOpt(attr.GetSymbolsOpt());
}

template<bool discardValueFlag>
void PUnit_ArgumentDelegation<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValueExpr(processor.PopValue());
	RefPtr<Value> pValueCar(processor.PopValue());
	const DeclCallable* pDeclCallable = pValueCar->GetDeclCallableWithError();
	if (!pDeclCallable || !pDeclCallable->CheckAttribute(GetAttr())) {
		processor.ErrorDone();
		return;
	}
	RefPtr<Expr_Block> pExprOfBlock;
	if (pValueExpr->IsValid()) {
		RefPtr<Value_Expr> pValueExprCasted(pValueExpr->Cast<Value_Expr>());
		if (!pValueExprCasted) {
			processor.ErrorDone();
			return;
		}
		if (!pValueExprCasted->GetExpr().IsType<Expr_Block>()) {
			Error::Issue(ErrorType::TypeError, "block expression must be specified for delegation");
			processor.ErrorDone();
			return;
		}
		pExprOfBlock.reset(dynamic_cast<Expr_Block*>(pValueExprCasted->GetExpr().Reference()));
	}
	RefPtr<Argument> pArgument(
		new Argument(pValueCar.release(), pDeclCallable->Reference(),
					 GetAttr().Reference(), pDeclCallable->GetFlags() | GetFlags(), Value::undefined(),
					 pExprOfBlock.release()));
	if constexpr (!discardValueFlag) processor.PushValue(new Value_Argument(pArgument.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_ArgumentDelegation<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "ArgumentDelegation()";
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_ArgumentDelegation::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_ArgumentDelegation<true>(*_pAttr, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_ArgumentDelegation<false>(*_pAttr, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_BeginArgSlot
// Stack View: [Argument(Car)] -> [Argument(Car)] (continue)
//                             -> [Argument(Car)] (branch)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_BeginArgSlot<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
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

template<bool discardValueFlag>
String PUnit_BeginArgSlot<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	RefPtr<Expr> pExpr(new Expr_UnaryOp(GetExprSrc().Reference(), Operator::Quote));
	str.Format("BeginArgSlot(%s", pExpr->ToString(StringStyle().SetCram()).c_str());
	if (GetExprSrc().GetPUnitFirst()) {
		str.Format(":%s", MakeSeqIdString(GetExprSrc().GetPUnitFirst(), seqIdOffset).c_str());
	}
	str.Format(",sentinel=%s,branchdest=%s)",
			   MakeSeqIdString(GetPUnitSentinel(), seqIdOffset).c_str(),
			   MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_BeginArgSlot::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_BeginArgSlot<true>(_pPUnitBranchDest, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_BeginArgSlot<false>(_pPUnitBranchDest, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_EndArgSlot
// Stack View: [Argument(Car) Any] -> [Argument(Car)] (continue)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_EndArgSlot<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValue(processor.PopValue());
	Argument& argument = Value_Argument::GetArgument(processor.PeekValue(0));
	argument.FeedValue(frame, pValue.release());
	if (Error::IsIssued()) {
		processor.ErrorDone();
		return;
	}
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_EndArgSlot<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "EndArgSlot()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_EndArgSlot::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_EndArgSlot<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_EndArgSlot<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_EndArgSlotExpand
// Stack View: [Argument(Car) Any] -> [Argument(Car)] (continue)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_EndArgSlotExpand<discardValueFlag>::Exec(Processor& processor) const
{
	auto CheckArgSlot = [](Argument& argument) {
		ArgSlot* pArgSlot = argument.GetArgSlotToFeed(); // this may be nullptr
		if (!pArgSlot) {
			if (argument.IsSet(DeclCallable::Flag::CutExtraArgs)) {
				// just ignore extra arguments
			} else {
				Error::Issue(ErrorType::ArgumentError, "too many arguments");
				return false;
			}
		} else if (!pArgSlot->IsVacant()) {
			Error::Issue(ErrorType::ArgumentError, "duplicated assignment of argument");
			return false;
		} else if (pArgSlot->IsVType(VTYPE_Quote)) {
			Error::Issue(ErrorType::ArgumentError, "invalid argument assignment");
			return false;
		}
		return true;
	};
	processor.SetExprCur(_pExprSrc);
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValue(processor.PopValue());
	Argument& argument = Value_Argument::GetArgument(processor.PeekValue(0));
	if (pValue->IsList()) {
		const ValueOwner& valueOwner = Value_List::GetValueOwner(*pValue);
		for (const Value* pValueElem : valueOwner) {
			if (!CheckArgSlot(argument)) {
				processor.ErrorDone();
				return;
			}
			argument.FeedValue(frame, pValueElem->Reference());
			if (Error::IsIssued()) {
				processor.ErrorDone();
				return;
			}
		}
	} else if (pValue->IsIterator()) {
		Iterator& iterator = Value_Iterator::GetIterator(*pValue);
		for (;;) {
			RefPtr<Value> pValueElem(iterator.NextValue());
			if (!pValueElem) {
				if (Error::IsIssued()) {
					processor.ErrorDone();
					return;
				}
				break;
			}
			if (!CheckArgSlot(argument)) {
				processor.ErrorDone();
				return;
			}
			argument.FeedValue(frame, pValueElem.release());
			if (Error::IsIssued()) {
				processor.ErrorDone();
				return;
			}
		}
	} else {
		argument.FeedValue(frame, pValue.release());
		if (Error::IsIssued()) {
			processor.ErrorDone();
			return;
		}
	}
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_EndArgSlotExpand<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "EndArgSlotExpand()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_EndArgSlotExpand::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_EndArgSlotExpand<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_EndArgSlotExpand<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_BeginArgSlotNamed
// Stack View: [Argument(Car)] -> [Argument(Car) ArgSlot] (continue)
//                             -> [Argument(Car)]         (discard)
//                             -> [Argument(Car)]         (branch)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_BeginArgSlotNamed<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	Argument& argument = Value_Argument::GetArgument(processor.PeekValue(0));
	ArgSlot* pArgSlot = argument.FindArgSlot(GetSymbol());
	if (!pArgSlot) {
		Value_Dict* pValueOfDict = argument.GetValueOfDict();
		if (pValueOfDict) {
			processor.PushValue(
				new Value_ArgSlot(new ArgSlot_Dict(pValueOfDict->Reference(), GetSymbol())));
			processor.SetPUnitNext(_GetPUnitCont());
		} else {
			Error::Issue(ErrorType::ArgumentError, "invalid argument: %s", GetSymbol()->GetName());
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
		if constexpr (!discardValueFlag) processor.PushValue(new Value_ArgSlot(pArgSlot->Reference()));
		processor.SetPUnitNext(_GetPUnitCont());
	}
}

template<bool discardValueFlag>
String PUnit_BeginArgSlotNamed<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("BeginArgSlotNamed(`%s,symbol=%s,sentinel=%s,branchdest=%s)",
			   GetExprSrc().ToString(StringStyle().SetCram()).c_str(), GetSymbol()->GetName(),
			   MakeSeqIdString(GetPUnitSentinel(), seqIdOffset).c_str(),
			   MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_BeginArgSlotNamed::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_BeginArgSlotNamed<true>(
			_pSymbol, _pExprAssigned.release(), _pPUnitBranchDest, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_BeginArgSlotNamed<false>(
			_pSymbol, _pExprAssigned.release(), _pPUnitBranchDest, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_EndArgSlotNamed
// Stack View: [Argument ArgSlot Any] -> [Argument] (continue)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_EndArgSlotNamed<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValue(processor.PopValue());
	RefPtr<Value> pValueArgSlot(processor.PopValue());
	Argument& argument = Value_Argument::GetArgument(processor.PeekValue(0));
	ArgSlot& argSlot = Value_ArgSlot::GetArgSlot(*pValueArgSlot);
	argSlot.FeedValue(argument, frame, pValue.release());
	if (Error::IsIssued()) {
		processor.ErrorDone();
		return;
	}
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_EndArgSlotNamed<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "EndArgSlotNamed()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_EndArgSlotNamed::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_EndArgSlotNamed<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_EndArgSlotNamed<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Call
// Stack View: [Argument] -> [Result] (continue)
//                        -> []       (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_Call<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value_Argument> pValue(dynamic_cast<Value_Argument*>(processor.PopValue()));
	Argument& argument = pValue->GetArgument();
	argument.DoCall(processor);
	if (Error::IsIssued()) {
		processor.ErrorDone();
	}
}

template<bool discardValueFlag>
String PUnit_Call<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("Call(cont=%s)", MakeSeqIdString(_GetPUnitCont(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Call::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Call<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_Call<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Jump
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_Jump<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	if constexpr (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_Jump<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("Jump(cont=%s)", MakeSeqIdString(_GetPUnitCont(), seqIdOffset).c_str());
	return str;
}

PUnit* PUnitFactory_Jump::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Jump<true>(_pPUnitCont, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_Jump<false>(_pPUnitCont, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_JumpIf
// Stack View: [Prev Bool] -> [Prev]      (continue)
//                         -> []          (discard)
//                         -> [Prev]      (branch)
//                         -> [Prev Nil]  (branch, nil)
//                         -> [Prev Bool] (branch, keep)
//------------------------------------------------------------------------------
template<bool discardValueFlag, PUnit::BranchMode branchMode>
void PUnit_JumpIf<discardValueFlag, branchMode>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	if constexpr (branchMode == BranchMode::Keep) {
		if (processor.PeekValue(0).GetBool()) {
			processor.SetPUnitNext(GetPUnitBranchDest());
		} else {
			processor.DiscardValue();
			if constexpr (discardValueFlag) processor.DiscardValue();
			processor.SetPUnitNext(_GetPUnitCont());
		}
	} else {
		RefPtr<Value> pValue(processor.PopValue());
		if (pValue->GetBool()) {
			if (branchMode == BranchMode::Nil) processor.PushValue(Value::nil());
			processor.SetPUnitNext(GetPUnitBranchDest());
		} else {
			if constexpr (discardValueFlag) processor.DiscardValue();
			processor.SetPUnitNext(_GetPUnitCont());
		}
	}
}

template<bool discardValueFlag, PUnit::BranchMode branchMode>
String PUnit_JumpIf<discardValueFlag, branchMode>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("JumpIf(branchdest=%s%s)", MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str(),
			(branchMode == BranchMode::Nil)? ",nil" : (branchMode == BranchMode::Keep)? ",keep" : "");
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_JumpIf::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		switch (_branchMode) {
		case PUnit::BranchMode::Empty:
			_pPUnitCreated = new PUnit_JumpIf<true, PUnit::BranchMode::Empty>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		case PUnit::BranchMode::Nil:
			_pPUnitCreated = new PUnit_JumpIf<true, PUnit::BranchMode::Nil>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		default: // PUnit::BranchMode::Keep:
			_pPUnitCreated = new PUnit_JumpIf<true, PUnit::BranchMode::Keep>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		}
	} else {
		switch (_branchMode) {
		case PUnit::BranchMode::Empty:
			_pPUnitCreated = new PUnit_JumpIf<false, PUnit::BranchMode::Empty>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		case PUnit::BranchMode::Nil:
			_pPUnitCreated = new PUnit_JumpIf<false, PUnit::BranchMode::Nil>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		default: // PUnit::BranchMode::Keep:
			_pPUnitCreated = new PUnit_JumpIf<false, PUnit::BranchMode::Keep>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_JumpIfNot
// Stack View: [Prev Bool] -> [Prev]      (continue)
//                         -> []          (discard)
//                         -> [Prev]      (branch)
//                         -> [Prev Nil]  (branch, nil)
//                         -> [Prev Bool] (branch, keep)
//------------------------------------------------------------------------------
template<bool discardValueFlag, PUnit::BranchMode branchMode>
void PUnit_JumpIfNot<discardValueFlag, branchMode>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	if constexpr (branchMode == BranchMode::Keep) {
		if (processor.PeekValue(0).GetBool()) {
			processor.DiscardValue();
			if constexpr (discardValueFlag) processor.DiscardValue();
			processor.SetPUnitNext(_GetPUnitCont());
		} else {
			processor.SetPUnitNext(GetPUnitBranchDest());
		}
	} else {
		RefPtr<Value> pValue(processor.PopValue());
		if (pValue->GetBool()) {
			if constexpr (discardValueFlag) processor.DiscardValue();
			processor.SetPUnitNext(_GetPUnitCont());
		} else {
			if (branchMode == BranchMode::Nil) processor.PushValue(Value::nil());
			processor.SetPUnitNext(GetPUnitBranchDest());
		}
	}
}

template<bool discardValueFlag, PUnit::BranchMode branchMode>
String PUnit_JumpIfNot<discardValueFlag, branchMode>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("JumpIfNot(branchdest=%s%s)", MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str(),
			(branchMode == BranchMode::Nil)? ",nil" : (branchMode == BranchMode::Keep)? ",keep" : "");
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_JumpIfNot::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		switch (_branchMode) {
		case PUnit::BranchMode::Empty:
			_pPUnitCreated = new PUnit_JumpIfNot<true, PUnit::BranchMode::Empty>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		case PUnit::BranchMode::Nil:
			_pPUnitCreated = new PUnit_JumpIfNot<true, PUnit::BranchMode::Nil>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		default: // PUnit::BranchMode::Keep:
			_pPUnitCreated = new PUnit_JumpIfNot<true, PUnit::BranchMode::Keep>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		}
	} else {
		switch (_branchMode) {
		case PUnit::BranchMode::Empty:
			_pPUnitCreated = new PUnit_JumpIfNot<false, PUnit::BranchMode::Empty>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		case PUnit::BranchMode::Nil:
			_pPUnitCreated = new PUnit_JumpIfNot<false, PUnit::BranchMode::Nil>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		default: // PUnit::BranchMode::Keep:
			_pPUnitCreated = new PUnit_JumpIfNot<false, PUnit::BranchMode::Keep>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_BeginTryBlock
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_BeginTryBlock<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	processor.BeginTryBlock(GetPUnitBranchDest());
	if constexpr (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_BeginTryBlock<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("BeginTryBlock(branchdest=%s)", MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_BeginTryBlock::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_BeginTryBlock<true>(_pPUnitBranchDest, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_BeginTryBlock<false>(_pPUnitBranchDest, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_EndTryBlock
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_EndTryBlock<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	processor.EndTryBlock();
	if constexpr (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_EndTryBlock<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("EndTryBlock(cont=%s)", MakeSeqIdString(_GetPUnitCont(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_EndTryBlock::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_EndTryBlock<true>(_pPUnitCont, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_EndTryBlock<false>(_pPUnitCont, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_JumpIfNoCatch
// Stack View: [ErrorType] -> [Error] (continue)
//                         -> []      (discard)
//                         -> []      (branch)
//                         -> [Nil]   (branch, nil)
//------------------------------------------------------------------------------
template<bool discardValueFlag, PUnit::BranchMode branchMode>
void PUnit_JumpIfNoCatch<discardValueFlag, branchMode>::Exec(Processor& processor) const
{
#if 1
	processor.SetExprCur(_pExprSrc);
	const Error* pError = Error::GetLastError();
	RefPtr<Value> pValue(processor.PopValue());
	const ErrorType& errorType = Value_ErrorType::GetErrorType(*pValue);
	if (pError && pError->GetErrorType().IsIdentical(errorType)) {
		if constexpr (!discardValueFlag) processor.PushValue(new Value_Error(pError->Reference()));
		Error::Clear();
		processor.SetPUnitNext(_GetPUnitCont());
	} else {
		if constexpr (branchMode == BranchMode::Nil) processor.PushValue(Value::nil());
		processor.SetPUnitNext(GetPUnitBranchDest());
	}
#else
	processor.SetExprCur(_pExprSrc);
	const Error* pError = Error::GetLastError();
	if (pError) {
		for (;;) {
			RefPtr<Value> pValue(processor.PopValue());
			if (!pValue->IsValid()) break;
			const ErrorType& errorType = Value_ErrorType::GetErrorType(*pValue);
			if (pError->GetErrorType().IsIdentical(errorType)) {
				for (;;) {
					RefPtr<Value> pValue(processor.PopValue());
					if (!pValue->IsValid()) break;
				}
				if constexpr (!discardValueFlag) processor.PushValue(new Value_Error(pError->Reference()));
				Error::Clear();
				processor.SetPUnitNext(_GetPUnitCont());
				return;
			}
		}
	} else {
		for (;;) {
			RefPtr<Value> pValue(processor.PopValue());
			if (!pValue->IsValid()) break;
		}
	}
	if constexpr (branchMode == BranchMode::Nil) processor.PushValue(Value::nil());
	processor.SetPUnitNext(GetPUnitBranchDest());
#endif
}

template<bool discardValueFlag, PUnit::BranchMode branchMode>
String PUnit_JumpIfNoCatch<discardValueFlag, branchMode>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("JumpIfNoCatch(branchdest=%s%s)", MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str(),
			(branchMode == BranchMode::Nil)? ",nil" : (branchMode == BranchMode::Keep)? ",keep" : "");
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_JumpIfNoCatch::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		switch (_branchMode) {
		case PUnit::BranchMode::Empty:
			_pPUnitCreated = new PUnit_JumpIfNoCatch<true, PUnit::BranchMode::Empty>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		case PUnit::BranchMode::Nil:
			_pPUnitCreated = new PUnit_JumpIfNoCatch<true, PUnit::BranchMode::Nil>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		default: // PUnit::BranchMode::Keep:
			_pPUnitCreated = new PUnit_JumpIfNoCatch<true, PUnit::BranchMode::Keep>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		}
	} else {
		switch (_branchMode) {
		case PUnit::BranchMode::Empty:
			_pPUnitCreated = new PUnit_JumpIfNoCatch<false, PUnit::BranchMode::Empty>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		case PUnit::BranchMode::Nil:
			_pPUnitCreated = new PUnit_JumpIfNoCatch<false, PUnit::BranchMode::Nil>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		default: // PUnit::BranchMode::Keep:
			_pPUnitCreated = new PUnit_JumpIfNoCatch<false, PUnit::BranchMode::Keep>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_JumpIfNoCatchAny
// Stack View: [] -> [Error] (continue)
//                -> []      (discard)
//                -> []      (branch)
//                -> [Nil]   (branch, nil)
//------------------------------------------------------------------------------
template<bool discardValueFlag, PUnit::BranchMode branchMode>
void PUnit_JumpIfNoCatchAny<discardValueFlag, branchMode>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	const Error* pError = Error::GetLastError();
	if (pError) {
		if constexpr (!discardValueFlag) processor.PushValue(new Value_Error(pError->Reference()));
		Error::Clear();
		processor.SetPUnitNext(_GetPUnitCont());
	} else {
		if constexpr (branchMode == BranchMode::Nil) processor.PushValue(Value::nil());
		processor.SetPUnitNext(GetPUnitBranchDest());
	}
}

template<bool discardValueFlag, PUnit::BranchMode branchMode>
String PUnit_JumpIfNoCatchAny<discardValueFlag, branchMode>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("JumpIfNoCatchAny(branchdest=%s%s)", MakeSeqIdString(GetPUnitBranchDest(), seqIdOffset).c_str(),
			(branchMode == BranchMode::Nil)? ",nil" : (branchMode == BranchMode::Keep)? ",keep" : "");
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_JumpIfNoCatchAny::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		switch (_branchMode) {
		case PUnit::BranchMode::Empty:
			_pPUnitCreated = new PUnit_JumpIfNoCatchAny<true, PUnit::BranchMode::Empty>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		case PUnit::BranchMode::Nil:
			_pPUnitCreated = new PUnit_JumpIfNoCatchAny<true, PUnit::BranchMode::Nil>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		default: // PUnit::BranchMode::Keep:
			_pPUnitCreated = new PUnit_JumpIfNoCatchAny<true, PUnit::BranchMode::Keep>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		}
	} else {
		switch (_branchMode) {
		case PUnit::BranchMode::Empty:
			_pPUnitCreated = new PUnit_JumpIfNoCatchAny<false, PUnit::BranchMode::Empty>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		case PUnit::BranchMode::Nil:
			_pPUnitCreated = new PUnit_JumpIfNoCatchAny<false, PUnit::BranchMode::Nil>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		default: // PUnit::BranchMode::Keep:
			_pPUnitCreated = new PUnit_JumpIfNoCatchAny<false, PUnit::BranchMode::Keep>(_pPUnitBranchDest, _pExprSrc.Reference());
			break;
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_BeginSequence
// Stack View: [Prev] -> [Prev] (continue)
//                       []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_BeginSequence<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	if constexpr (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_BeginSequence<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("BeginSequence(sentinel=%s)", MakeSeqIdString(GetPUnitSentinel(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_BeginSequence::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_BeginSequence<true>(_pPUnitSentinel, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_BeginSequence<false>(_pPUnitSentinel, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_EndSequence
// Stack View: [Prev] -> [Prev] (always)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_EndSequence<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	processor.ExitRunLoop();
}

template<bool discardValueFlag>
String PUnit_EndSequence<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "EndSequence()";
	//AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_EndSequence::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_EndSequence<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_EndSequence<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_DiscardValue
// Stack View: [Prev Any] -> [Prev] (continue)
//                        -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_DiscardValue<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	processor.DiscardValue();
	if constexpr (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_DiscardValue<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "DiscardValue()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_DiscardValue::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_DiscardValue<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_DiscardValue<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_RemoveValue
// Stack View: [.. Any .. Prev] -> [.. .. Prev] (continue)
//                              -> [.. ..]      (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_RemoveValue<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	processor.RemoveValue(GetOffset());
	if constexpr (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_RemoveValue<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("RemoveValue(offset=%zu)", GetOffset());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_RemoveValue::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_RemoveValue<true>(_offset, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_RemoveValue<false>(_offset, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_RemoveValues
// Stack View: [.. Any1..n .. Prev] -> [.. .. Prev] (continue)
//                                  -> [.. ..]      (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_RemoveValues<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	processor.RemoveValues(GetOffset(), GetCount());
	if constexpr (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_RemoveValues<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("RemoveValues(offset=%zu,count=%zu)", GetOffset(), GetCount());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_RemoveValues::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_RemoveValues<true>(_offset, _cnt, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_RemoveValues<false>(_offset, _cnt, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Break
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag, bool branchDestFlag>
void PUnit_Break<discardValueFlag, branchDestFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	if constexpr (discardValueFlag) processor.DiscardValue();
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

template<bool discardValueFlag, bool branchDestFlag>
String PUnit_Break<discardValueFlag, branchDestFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("Break(marked=%s,branchDestFlag=%s)", MakeSeqIdString(GetPUnitMarked(), seqIdOffset).c_str(),
			   branchDestFlag? "true" : "false");
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Break::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		if (_branchDestFlag) {
			_pPUnitCreated = new PUnit_Break<true, true>(_pPUnitMarked, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Break<true, false>(_pPUnitMarked, _pExprSrc.Reference());
		}
	} else {
		if (_branchDestFlag) {
			_pPUnitCreated = new PUnit_Break<false, true>(_pPUnitMarked, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Break<false, false>(_pPUnitMarked, _pExprSrc.Reference());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Continue
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_Continue<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	if constexpr (discardValueFlag) processor.DiscardValue();
	if (GetPUnitOfLoop()) {
		processor.SetPUnitNext(GetPUnitOfLoop());
	} else {
		processor.SetEventContinue();
		processor.ExitRunLoop();
	}
}

template<bool discardValueFlag>
String PUnit_Continue<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("Continue(loop=%s)", MakeSeqIdString(GetPUnitOfLoop(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Continue::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Continue<true>(_pPUnitOfLoop, _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_Continue<false>(_pPUnitOfLoop, _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_FailCatch
// Stack View: [] -> [Any] (continue)
//                -> []    (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_FailCatch<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	if constexpr (!discardValueFlag) processor.PushValue(GetValue()->Reference());
	processor.ExitRunLoop(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_FailCatch<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("FailCatch(%s)", GetValue()->ToString(StringStyle().SetDigest()).c_str());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_FailCatch::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_FailCatch<true>(_pValue.release(), _pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_FailCatch<false>(_pValue.release(), _pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Return
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_Return<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
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

template<bool discardValueFlag>
String PUnit_Return<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "Return()";
	//AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Return::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_Return<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_Return<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_PushFrame
// Stack View: [prev] -> [prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag, typename T_Frame>
void PUnit_PushFrame<discardValueFlag, T_Frame>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	processor.PushFrame<T_Frame>();
	if constexpr (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag, typename T_Frame>
String PUnit_PushFrame<discardValueFlag, T_Frame>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("PushFrame<%s>()", T_Frame::name);
	AppendInfoToString(str, ss);
	return str;
}

template<typename T_Frame>
PUnit* PUnitFactory_PushFrame<T_Frame>::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_PushFrame<true, T_Frame>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_PushFrame<false, T_Frame>(_pExprSrc.Reference());
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
template<bool discardValueFlag>
void PUnit_PushFrameFromStack<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	RefPtr<Value> pValue(processor.PopValue());
	processor.PushFrame(Value_Frame::GetFrame(*pValue).Reference());
	if constexpr (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<bool discardValueFlag>
String PUnit_PushFrameFromStack<discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Format("PushFrameFromStack()");
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_PushFrameFromStack::Create(bool discardValueFlag)
{
	if (discardValueFlag) {
		_pPUnitCreated = new PUnit_PushFrameFromStack<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_PushFrameFromStack<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_PopFrame
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_PopFrame<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	processor.PopFrame();
	if constexpr (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
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
		_pPUnitCreated = new PUnit_PopFrame<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_PopFrame<false>(_pExprSrc.Reference());
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_NoOperation
// Stack View: [Prev] -> [Prev] (continue)
//                    -> []     (discard)
//------------------------------------------------------------------------------
template<bool discardValueFlag>
void PUnit_NoOperation<discardValueFlag>::Exec(Processor& processor) const
{
	processor.SetExprCur(_pExprSrc);
	if constexpr (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
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
		_pPUnitCreated = new PUnit_NoOperation<true>(_pExprSrc.Reference());
	} else {
		_pPUnitCreated = new PUnit_NoOperation<false>(_pExprSrc.Reference());
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
	str.Format("REPLEnd()");
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
	str.Format("Bridge(cont=%s)", MakeSeqIdString(_GetPUnitCont(), seqIdOffset).c_str());
	AppendInfoToString(str, ss);
	return str;
}

}
