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
	if (!pValue) {
		Error::Issue(ErrorType::ValueError, "symbol '%s' is not found", GetSymbol()->GetName());
		processor.ErrorDone();
		return;
	}
	if (!discardValueFlag) processor.PushValue(pValue->Reference());
	processor.SetPUnitNext(_GetPUnitCont());
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
// PUnit_Suffixed
// Stack View: [Any] -> [Result] (continue)
//                   -> []       (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_Suffixed<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
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
	if (!discardValueFlag) processor.PushValue(pValueResult.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Suffixed<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Suffixed(`%s)", GetSymbolSuffix()->GetName());
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Suffixed::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Suffixed<1, true>(_pStr.Reference(), _target, _pSymbolSuffix, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Suffixed<1, false>(_pStr.Reference(), _target, _pSymbolSuffix, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Suffixed<0, true>(_pStr.Reference(), _target, _pSymbolSuffix);
		} else {
			_pPUnitCreated = new PUnit_Suffixed<0, false>(_pStr.Reference(), _target, _pSymbolSuffix);
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
		vtype.PrepareForAssignment(processor, GetSymbol());
	} else if (pValueAssigned->IsType(VTYPE_Function)) {
		Function& function = Value_Function::GetFunction(*pValueAssigned);
		if (function.GetSymbol()->IsEmpty()) function.SetSymbol(GetSymbol());
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
// Stack View: keepTargetFlag = false: [Target] -> [Function]        (continue)
//                                              -> []                (discard)
//             keepTargetFlag = true:  [Target] -> [Target Function] (continue)
//                                              -> [Target]          (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, bool keepTargetFlag>
void PUnit_AssignMethod<nExprSrc, discardValueFlag, keepTargetFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValueTarget(keepTargetFlag? processor.PeekValue(0).Reference() : processor.PopValue());
	RefPtr<Function> pFunction(GetFunction().Reference());
	pFunction->SetFrameOuter(frame);
	if (!pValueTarget->DoAssignCustomMethod(pFunction.Reference())) {
		processor.ErrorDone();
		return;
	}
	if (!discardValueFlag) processor.PushValue(new Value_Function(pFunction.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag, bool keepTargetFlag>
String PUnit_AssignMethod<nExprSrc, discardValueFlag, keepTargetFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
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
			if (_keepTargetFlag) {
				_pPUnitCreated = new PUnit_AssignMethod<1, true, true>(_pFunction.release(), _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_AssignMethod<1, true, false>(_pFunction.release(), _pExprSrc.Reference());
			}
		} else {
			if (_keepTargetFlag) {
				_pPUnitCreated = new PUnit_AssignMethod<1, false, true>(_pFunction.release(), _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_AssignMethod<1, false, false>(_pFunction.release(), _pExprSrc.Reference());
			}
		}
	} else {
		if (discardValueFlag) {
			if (_keepTargetFlag) {
				_pPUnitCreated = new PUnit_AssignMethod<0, true, true>(_pFunction.release());
			} else {
				_pPUnitCreated = new PUnit_AssignMethod<0, true, false>(_pFunction.release());
			}
		} else {
			if (_keepTargetFlag) {
				_pPUnitCreated = new PUnit_AssignMethod<0, false, true>(_pFunction.release());
			} else {
				_pPUnitCreated = new PUnit_AssignMethod<0, false, false>(_pFunction.release());
			}
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_AssignPropHandler
// Stack View: initByNilFlag=false .. [VType ValueInit] -> [VType ValueInit] (continue)
//                                                      -> [VType]           (discard)
//             initByNilFlag=true ..  [VType]           -> [VType]           (continue)
//                                                      -> [VType]           (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, bool initByNilFlag>
void PUnit_AssignPropHandler<nExprSrc, discardValueFlag, initByNilFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	Frame& frame = processor.GetFrameCur();
	VTypeCustom& vtypeCustom = dynamic_cast<VTypeCustom&>(
		Value_VType::GetVTypeThis(processor.PeekValue(initByNilFlag? 0 : 1)));
	RefPtr<Value> pValueInit(
		initByNilFlag? Value::nil() :
		(discardValueFlag? processor.PopValue() : processor.PeekValue(0).Reference()));
	if (!vtypeCustom.AssignPropHandler(frame, GetSymbol(), GetDottedSymbol(), GetFlags(), pValueInit.release())) {
		processor.ErrorDone();
		return;
	}		
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag, bool initByNilFlag>
String PUnit_AssignPropHandler<nExprSrc, discardValueFlag, initByNilFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("AssignPropHandler(%s,cont=%s,initByNil=%s)",
			   GetSymbol()->GetName(),
			   MakeSeqIdString(_GetPUnitCont(), seqIdOffset).c_str(), initByNilFlag? "true" : "false");
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_AssignPropHandler::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			if (_initByNilFlag) {
				_pPUnitCreated = new PUnit_AssignPropHandler<1, true, true>(
					_pSymbol, _pDottedSymbol.release(), _flags, _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_AssignPropHandler<1, true, false>(
					_pSymbol, _pDottedSymbol.release(), _flags, _pExprSrc.Reference());
			}
		} else {
			if (_initByNilFlag) {
				_pPUnitCreated = new PUnit_AssignPropHandler<1, false, true>(
					_pSymbol, _pDottedSymbol.release(), _flags, _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_AssignPropHandler<1, false, false>(
					_pSymbol, _pDottedSymbol.release(), _flags, _pExprSrc.Reference());
			}
		}
	} else {
		if (discardValueFlag) {
			if (_initByNilFlag) {
				_pPUnitCreated = new PUnit_AssignPropHandler<0, true, true>(_pSymbol, _pDottedSymbol.release(), _flags);
			} else {
				_pPUnitCreated = new PUnit_AssignPropHandler<0, true, false>(_pSymbol, _pDottedSymbol.release(), _flags);
			}
		} else {
			if (_initByNilFlag) {
				_pPUnitCreated = new PUnit_AssignPropHandler<0, false, true>(_pSymbol, _pDottedSymbol.release(), _flags);
			} else {
				_pPUnitCreated = new PUnit_AssignPropHandler<0, false, false>(_pSymbol, _pDottedSymbol.release(), _flags);
			}
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
	RefPtr<Value> pValueCasted(GetVType().Cast(*pValue, GetFlags()));
	if (!pValueCasted) {
		processor.ErrorDone();
		return;
	}
	if (!discardValueFlag) processor.PushValue(pValueCasted.release());
	processor.SetPUnitNext(_GetPUnitCont());
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
			_pPUnitCreated = new PUnit_Cast<1, true>(_vtype, _flags, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Cast<1, false>(_vtype, _flags, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Cast<0, true>(_vtype, _flags);
		} else {
			_pPUnitCreated = new PUnit_Cast<0, false>(_vtype, _flags);
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
	if (!pIterator) {
		processor.ErrorDone();
		return;
	}
	if (!discardValueFlag) processor.PushValue(new Value_Iterator(pIterator.release()));
	processor.SetPUnitNext(_GetPUnitCont());
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
// PUnit_GenIterator_Range
// Stack View: [Number] -> [Iterator] (continue)
//                      -> []         (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_GenIterator_Range<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValue(processor.PopValue());
	int num = Value_Number::GetNumber<Int>(*pValue);
	RefPtr<Iterator> pIterator(new Iterator_Range(num));
	if (!discardValueFlag) processor.PushValue(new Value_Iterator(pIterator.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_GenIterator_Range<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenIterator_Range()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_GenIterator_Range::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_GenIterator_Range<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_GenIterator_Range<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_GenIterator_Range<0, true>();
		} else {
			_pPUnitCreated = new PUnit_GenIterator_Range<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_GenIterator_Counter
// Stack View: [] -> [Iterator] (continue)
//                -> []         (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_GenIterator_Counter<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Iterator> pIterator(new Iterator_Counter());
	if (!discardValueFlag) processor.PushValue(new Value_Iterator(pIterator.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_GenIterator_Counter<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenIterator_Counter()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_GenIterator_Counter::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_GenIterator_Counter<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_GenIterator_Counter<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_GenIterator_Counter<0, true>();
		} else {
			_pPUnitCreated = new PUnit_GenIterator_Counter<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_GenIterator_ForLister
// Stack View: [Value] -> [Value Iterator] (continue)
//                     -> [Value]          (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_GenIterator_ForLister<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	Value& value(processor.PeekValue(0));
	RefPtr<Iterator> pIterator;
	if (value.IsIterable()) {
		pIterator.reset(value.DoGenIterator());
	} else {
		pIterator.reset(new Iterator_Const(value.Reference()));
	}
	if (!discardValueFlag) processor.PushValue(new Value_Iterator(pIterator.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_GenIterator_ForLister<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenIterator_ForLister()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_GenIterator_ForLister::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_GenIterator_ForLister<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_GenIterator_ForLister<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_GenIterator_ForLister<0, true>();
		} else {
			_pPUnitCreated = new PUnit_GenIterator_ForLister<0, false>();
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_GenIterator_repeat
// Stack View: [] -> [Iterator] (continue)
//                -> []         (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_GenIterator_repeat<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
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
	if (!discardValueFlag) processor.PushValue(new Value_Iterator(pIterator.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_GenIterator_repeat<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "GenIterator_repeat()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_GenIterator_repeat::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_GenIterator_repeat<1, true>(
				_pExprOfBlock.Reference(), _finiteFlag, _skipNilFlag, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_GenIterator_repeat<1, false>(
				_pExprOfBlock.Reference(), _finiteFlag, _skipNilFlag, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_GenIterator_repeat<0, true>(
				_pExprOfBlock.Reference(), _finiteFlag, _skipNilFlag);
		} else {
			_pPUnitCreated = new PUnit_GenIterator_repeat<0, false>(
				_pExprOfBlock.Reference(), _finiteFlag, _skipNilFlag);
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
	} else if (_raiseFlag) {
		Error::Issue(ErrorType::IteratorError, "insufficient number of values");
		processor.ErrorDone();
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
			_pPUnitCreated = new PUnit_EvalIterator<1, true>(_offset, _raiseFlag, _pPUnitBranchDest, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_EvalIterator<1, false>(_offset, _raiseFlag, _pPUnitBranchDest, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_EvalIterator<0, true>(_offset, _raiseFlag, _pPUnitBranchDest);
		} else {
			_pPUnitCreated = new PUnit_EvalIterator<0, false>(_offset, _raiseFlag, _pPUnitBranchDest);
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
		return;
	}
	if (!discardValueFlag) processor.PushValue(pValueResult.release());
	processor.SetPUnitNext(_GetPUnitCont());
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
			_pPUnitCreated = new PUnit_UnaryOp<1, true>(_pOp, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_UnaryOp<1, false>(_pOp, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_UnaryOp<0, true>(_pOp);
		} else {
			_pPUnitCreated = new PUnit_UnaryOp<0, false>(_pOp);
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
		return;
	}
	if (!discardValueFlag) processor.PushValue(pValueResult.release());
	processor.SetPUnitNext(_GetPUnitCont());
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
			_pPUnitCreated = new PUnit_BinaryOp<1, true>(_pOp, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_BinaryOp<1, false>(_pOp, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_BinaryOp<0, true>(_pOp);
		} else {
			_pPUnitCreated = new PUnit_BinaryOp<0, false>(_pOp);
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
	if (!discardValueFlag) processor.PushValue(new Value_Module(pModule.release()));
	processor.SetPUnitNext(_GetPUnitCont());
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
			_pPUnitCreated = new PUnit_Import<1, true>(
				_pDottedSymbol.release(), _pSymbolList.release(),
				_binaryFlag, _mixInFlag, _overwriteFlag, _symbolForModuleFlag, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Import<1, false>(
				_pDottedSymbol.release(), _pSymbolList.release(),
				_binaryFlag, _mixInFlag, _overwriteFlag, _symbolForModuleFlag, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Import<0, true>(
				_pDottedSymbol.release(), _pSymbolList.release(),
				_binaryFlag, _mixInFlag, _overwriteFlag, _symbolForModuleFlag);
		} else {
			_pPUnitCreated = new PUnit_Import<0, false>(
				_pDottedSymbol.release(), _pSymbolList.release(),
				_binaryFlag, _mixInFlag, _overwriteFlag, _symbolForModuleFlag);
		}
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
template<int nExprSrc, bool discardValueFlag, bool inheritFlag>
void PUnit_CreateVType<nExprSrc, discardValueFlag, inheritFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	VType* pVTypeInh = &VTYPE_Object;
	if (inheritFlag) {
		RefPtr<Value> pValueVTypeInh(processor.PopValue());
		pVTypeInh = &Value_VType::GetVTypeThis(*pValueVTypeInh);
	}
	VTypeCustom* pVType = new VTypeCustom();
	pVType->Declare(*pVTypeInh, VType::Flag::Mutable);
	pVType->Inherit();
	if (!discardValueFlag) processor.PushValue(new Value_VType(*pVType));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag, bool inheritFlag>
String PUnit_CreateVType<nExprSrc, discardValueFlag, inheritFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("CreateVType(inheritFlag=%d)", inheritFlag);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_CreateVType::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			if (_inheritFlag) {
				_pPUnitCreated = new PUnit_CreateVType<1, true, true>(_pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_CreateVType<1, true, false>(_pExprSrc.Reference());
			}
		} else {
			if (_inheritFlag) {
				_pPUnitCreated = new PUnit_CreateVType<1, false, true>(_pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_CreateVType<1, false, false>(_pExprSrc.Reference());
			}
		}
	} else {
		if (discardValueFlag) {
			if (_inheritFlag) {
				_pPUnitCreated = new PUnit_CreateVType<0, true, true>();
			} else {
				_pPUnitCreated = new PUnit_CreateVType<0, true, false>();
			}
		} else {
			if (_inheritFlag) {
				_pPUnitCreated = new PUnit_CreateVType<0, false, true>();
			} else {
				_pPUnitCreated = new PUnit_CreateVType<0, false, false>();
			}
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_CompleteStruct
// Stack View: [VType] -> [VType] (continue)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_CompleteStruct<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	VTypeCustom& vtypeCustom = dynamic_cast<VTypeCustom&>(Value_VType::GetVTypeThis(processor.PeekValue(0)));
	RefPtr<PropHandlerOwner> pPropHandlerOwner(vtypeCustom.GetPropHandlerMap().CreatePropHandlerOwner());
	pPropHandlerOwner->SortBySeqId();
	RefPtr<DeclCallable> pDeclCallable(new DeclCallable());
	pDeclCallable->GetDeclBlock().SetOccur(DeclBlock::Occur::ZeroOrOnce);
	for (PropHandler* pPropHandler : *pPropHandlerOwner) {
		PropHandler::Flags flags = pPropHandler->GetFlags();
		//const DeclArg::Occur& occur = (flags & PropHandler::Flag::Nil)?
		//	DeclArg::Occur::ZeroOrOnce : DeclArg::Occur::Once;
		//const DeclArg::Occur& occur = DeclArg::Occur::Once;
		const DeclArg::Occur& occur = DeclArg::Occur::ZeroOrOnce;
		flags &= ~(PropHandler::Flag::Nil | PropHandler::Flag::OfClass | PropHandler::Flag::Public |
				   PropHandler::Flag::Readable | PropHandler::Flag::Writable);
		pDeclCallable->GetDeclArgOwner().push_back(
			new DeclArg(pPropHandler->GetSymbol(), pPropHandler->GetVType(), occur, flags, nullptr));
	}
	vtypeCustom.SetConstructor(new VTypeCustom::ConstructorStruct(
								   vtypeCustom, pDeclCallable.release(), pPropHandlerOwner.release()));
	if (Error::IsIssued()) {
		processor.ErrorDone();
		return;
	}
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_CompleteStruct<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "CompleteStruct()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_CompleteStruct::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_CompleteStruct<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_CompleteStruct<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_CompleteStruct<0, true>();
		} else {
			_pPUnitCreated = new PUnit_CompleteStruct<0, false>();
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
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	if (GetSizeReserve() > 0) pValueOwner->reserve(GetSizeReserve());
	if (!discardValueFlag) processor.PushValue(new Value_List(pValueOwner.release()));
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
// Stack View: [List .. Elem] -> [List ..] (continue)
//                            -> []        (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, bool xlistFlag, bool expandFlag>
void PUnit_ListElem<nExprSrc, discardValueFlag, xlistFlag, expandFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValueElem(processor.PopValue());
	ValueTypedOwner& valueTypedOwner = Value_List::GetValueTypedOwner(processor.PeekValue(GetOffset()));
	if (expandFlag && pValueElem->IsIterator()) {
		Iterator& iterator = Value_Iterator::GetIterator(*pValueElem);
		if (!iterator.MustBeFinite()) return;
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
	if (discardValueFlag) processor.RemoveValues(0, GetOffset() + 1);
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag, bool xlistFlag, bool expandFlag>
String PUnit_ListElem<nExprSrc, discardValueFlag, xlistFlag, expandFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("ListElem(offsetToList=%zu)", GetOffset());
	if (xlistFlag) str += ":xlist";
	if (expandFlag) str += ":expand";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_ListElem::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			if (_xlistFlag) {
				if (_expandFlag) {
					_pPUnitCreated = new PUnit_ListElem<1, true, true, true>(_offset, _pExprSrc.Reference());
				} else {
					_pPUnitCreated = new PUnit_ListElem<1, true, true, false>(_offset, _pExprSrc.Reference());
				}
			} else {
				if (_expandFlag) {
					_pPUnitCreated = new PUnit_ListElem<1, true, false, true>(_offset, _pExprSrc.Reference());
				} else {
					_pPUnitCreated = new PUnit_ListElem<1, true, false, false>(_offset, _pExprSrc.Reference());
				}
			}
		} else {
			if (_xlistFlag) {
				if (_expandFlag) {
					_pPUnitCreated = new PUnit_ListElem<1, false, true, true>(_offset, _pExprSrc.Reference());
				} else {
					_pPUnitCreated = new PUnit_ListElem<1, false, true, false>(_offset, _pExprSrc.Reference());
				}
			} else {
				if (_expandFlag) {
					_pPUnitCreated = new PUnit_ListElem<1, false, false, true>(_offset, _pExprSrc.Reference());
				} else {
					_pPUnitCreated = new PUnit_ListElem<1, false, false, false>(_offset, _pExprSrc.Reference());
				}
			}
		}
	} else {
		if (discardValueFlag) {
			if (_xlistFlag) {
				if (_expandFlag) {
					_pPUnitCreated = new PUnit_ListElem<0, true, true, true>(_offset);
				} else {
					_pPUnitCreated = new PUnit_ListElem<0, true, true, false>(_offset);
				}
			} else {
				if (_expandFlag) {
					_pPUnitCreated = new PUnit_ListElem<0, true, false, true>(_offset);
				} else {
					_pPUnitCreated = new PUnit_ListElem<0, true, false, false>(_offset);
				}
			}
		} else {
			if (_xlistFlag) {
				if (_expandFlag) {
					_pPUnitCreated = new PUnit_ListElem<0, false, true, true>(_offset);
				} else {
					_pPUnitCreated = new PUnit_ListElem<0, false, true, false>(_offset);
				}
			} else {
				if (_expandFlag) {
					_pPUnitCreated = new PUnit_ListElem<0, false, false, true>(_offset);
				} else {
					_pPUnitCreated = new PUnit_ListElem<0, false, false, false>(_offset);
				}
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
		return;
	}
	processor.SetPUnitNext(_GetPUnitCont());
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
		return;
	}
	if (!discardValueFlag) processor.PushValue(pValueElems.release());
	processor.SetPUnitNext(_GetPUnitCont());
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
// Stack View: valueFirst=false: [Index(Car) Elems] -> [Elems] (continue)
//                                                  -> []      (discard)
//             valueFirst=true:  [Elems Index(Car)] -> [Elems] (continue)
//                                                  -> []      (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, bool valueFirstFlag>
void PUnit_IndexSet<nExprSrc, discardValueFlag, valueFirstFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
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
	if (!discardValueFlag) processor.PushValue(pValueElems.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag, bool valueFirstFlag>
String PUnit_IndexSet<nExprSrc, discardValueFlag, valueFirstFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
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
			if (_valueFirstFlag) {
				_pPUnitCreated = new PUnit_IndexSet<1, true, true>(_pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_IndexSet<1, true, false>(_pExprSrc.Reference());
			}
		} else {
			if (_valueFirstFlag) {
				_pPUnitCreated = new PUnit_IndexSet<1, false, true>(_pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_IndexSet<1, false, false>(_pExprSrc.Reference());
			}
		}
	} else {
		if (discardValueFlag) {
			if (_valueFirstFlag) {
				_pPUnitCreated = new PUnit_IndexSet<0, true, true>();
			} else {
				_pPUnitCreated = new PUnit_IndexSet<0, true, false>();
			}
		} else {
			if (_valueFirstFlag) {
				_pPUnitCreated = new PUnit_IndexSet<0, false, true>();
			} else {
				_pPUnitCreated = new PUnit_IndexSet<0, false, false>();
			}
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
template<int nExprSrc, bool discardValueFlag, bool valueFirstFlag>
void PUnit_IndexOpApply<nExprSrc, discardValueFlag, valueFirstFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
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
	if (!discardValueFlag) processor.PushValue(pValueRtn.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag, bool valueFirstFlag>
String PUnit_IndexOpApply<nExprSrc, discardValueFlag, valueFirstFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "IndexOpApply()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_IndexOpApply::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			if (_valueFirstFlag) {
				_pPUnitCreated = new PUnit_IndexOpApply<1, true, true>(_pOp, _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_IndexOpApply<1, true, false>(_pOp, _pExprSrc.Reference());
			}
		} else {
			if (_valueFirstFlag) {
				_pPUnitCreated = new PUnit_IndexOpApply<1, false, true>(_pOp, _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_IndexOpApply<1, false, false>(_pOp, _pExprSrc.Reference());
			}
		}
	} else {
		if (discardValueFlag) {
			if (_valueFirstFlag) {
				_pPUnitCreated = new PUnit_IndexOpApply<0, true, true>(_pOp);
			} else {
				_pPUnitCreated = new PUnit_IndexOpApply<0, true, false>(_pOp);
			}
		} else {
			if (_valueFirstFlag) {
				_pPUnitCreated = new PUnit_IndexOpApply<0, false, true>(_pOp);
			} else {
				_pPUnitCreated = new PUnit_IndexOpApply<0, false, false>(_pOp);
			}
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
	Value* pValueProp = valueTarget.DoPropGet(GetSymbol(), GetAttr(), true);
	if (!pValueProp) {
		processor.ErrorDone();
		return;
	}
	if (!discardValueFlag) processor.PushValue(pValueProp->Reference());
	processor.SetPUnitNext(_GetPUnitCont());
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
// Stack View: valueFirst=false: [Target Assigned] -> [Assigned] (continue)
//                                                 -> []         (discard)
//             valueFirst=true:  [Assigned Target] -> [Assigned] (continue)
//                                                 -> []         (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, bool valueFirstFlag>
void PUnit_PropSet<nExprSrc, discardValueFlag, valueFirstFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValueAssigned;
	RefPtr<Value> pValueTarget;
	if (valueFirstFlag) {
		pValueTarget.reset(processor.PopValue());
		pValueAssigned.reset(processor.PopValue());
	} else {
		pValueAssigned.reset(processor.PopValue());
		pValueTarget.reset(processor.PopValue());
	}
	if (!pValueTarget->DoPropSet(GetSymbol(), pValueAssigned->Reference(), GetAttr())) {
		processor.ErrorDone();
		return;
	}
	if (!discardValueFlag) processor.PushValue(pValueAssigned.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag, bool valueFirstFlag>
String PUnit_PropSet<nExprSrc, discardValueFlag, valueFirstFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
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
			if (_valueFirstFlag) {
				_pPUnitCreated = new PUnit_PropSet<1, true, true>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_PropSet<1, true, false>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
			}
		} else {
			if (_valueFirstFlag) {
				_pPUnitCreated = new PUnit_PropSet<1, false, true>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_PropSet<1, false, false>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
			}
		}
	} else {
		if (discardValueFlag) {
			if (_valueFirstFlag) {
				_pPUnitCreated = new PUnit_PropSet<0, true, true>(_pSymbol, _pAttr.release());
			} else {
				_pPUnitCreated = new PUnit_PropSet<0, true, false>(_pSymbol, _pAttr.release());
			}
		} else {
			if (_valueFirstFlag) {
				_pPUnitCreated = new PUnit_PropSet<0, false, true>(_pSymbol, _pAttr.release());
			} else {
				_pPUnitCreated = new PUnit_PropSet<0, false, false>(_pSymbol, _pAttr.release());
			}
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_PropOpApply
// Stack View: valueFirst=false: [Target Applied] -> [Assigned] (continue)
//                                                -> []         (discard)
//             valueFirst=true:  [Applied Target] -> [Assigned] (continue)
//                                                -> []         (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag, bool valueFirstFlag>
void PUnit_PropOpApply<nExprSrc, discardValueFlag, valueFirstFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValueApplied;
	RefPtr<Value> pValueTarget;
	if (valueFirstFlag) {
		pValueTarget.reset(processor.PopValue());
		pValueApplied.reset(processor.PopValue());
	} else {
		pValueApplied.reset(processor.PopValue());
		pValueTarget.reset(processor.PopValue());
	}
	Value* pValueProp = pValueTarget->DoPropGet(GetSymbol(), GetAttr(), true);
	if (!pValueProp) {
		processor.ErrorDone();
		return;
	}
	RefPtr<Value> pValueAssigned(GetOperator().EvalBinary(processor, *pValueProp, *pValueApplied));
	if (!pValueTarget->DoPropSet(GetSymbol(), pValueAssigned->Reference(), GetAttr())) {
		processor.ErrorDone();
		return;
	}
	if (!discardValueFlag) processor.PushValue(pValueAssigned.release());
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag, bool valueFirstFlag>
String PUnit_PropOpApply<nExprSrc, discardValueFlag, valueFirstFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("PropOpApply(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_PropOpApply::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			if (_valueFirstFlag) {
				_pPUnitCreated = new PUnit_PropOpApply<1, true, true>(_pSymbol, _pAttr.release(), _pOp, _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_PropOpApply<1, true, false>(_pSymbol, _pAttr.release(), _pOp, _pExprSrc.Reference());
			}
		} else {
			if (_valueFirstFlag) {
				_pPUnitCreated = new PUnit_PropOpApply<1, false, true>(_pSymbol, _pAttr.release(), _pOp, _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_PropOpApply<1, false, false>(_pSymbol, _pAttr.release(), _pOp, _pExprSrc.Reference());
			}
		}
	} else {
		if (discardValueFlag) {
			if (_valueFirstFlag) {
				_pPUnitCreated = new PUnit_PropOpApply<0, true, true>(_pSymbol, _pAttr.release(), _pOp);
			} else {
				_pPUnitCreated = new PUnit_PropOpApply<0, true, false>(_pSymbol, _pAttr.release(), _pOp);
			}
		} else {
			if (_valueFirstFlag) {
				_pPUnitCreated = new PUnit_PropOpApply<0, false, true>(_pSymbol, _pAttr.release(), _pOp);
			} else {
				_pPUnitCreated = new PUnit_PropOpApply<0, false, false>(_pSymbol, _pAttr.release(), _pOp);
			}
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Member_Normal
// Stack View: [Target] -> [Member(Target+Prop)] (continue, callable)
//                      -> [Prop]                (continue, not callable)
//                      -> []                    (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_Member_Normal<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValueTarget(processor.PopValue());
	Value* pValueProp = pValueTarget->DoPropGet(GetSymbol(), GetAttr(), true);
	if (!pValueProp) {
		processor.ErrorDone();
		return;
	}
	if (!discardValueFlag) processor.PushValue(pValueProp->AsMember(*pValueTarget));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Member_Normal<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Member_Normal(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Member_Normal::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Member_Normal<1, true>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Member_Normal<1, false>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Member_Normal<0, true>(_pSymbol, _pAttr.release());
		} else {
			_pPUnitCreated = new PUnit_Member_Normal<0, false>(_pSymbol, _pAttr.release());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Member_MapAlong
// Stack View: [Target] -> [Member(Target+Prop)] (continue, callable)
//                      -> [Prop]                (continue, not callable)
//                      -> []                    (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_Member_MapAlong<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValueTarget(processor.PopValue());
	Value* pValueProp = pValueTarget->DoPropGet(GetSymbol(), GetAttr(), true);
	if (!pValueProp) {
		processor.ErrorDone();
		return;
	}
	if (!discardValueFlag) processor.PushValue(pValueProp->AsMember(*pValueTarget));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Member_MapAlong<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Member_MapAlong(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Member_MapAlong::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Member_MapAlong<1, true>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Member_MapAlong<1, false>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Member_MapAlong<0, true>(_pSymbol, _pAttr.release());
		} else {
			_pPUnitCreated = new PUnit_Member_MapAlong<0, false>(_pSymbol, _pAttr.release());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Member_MapToList
// Stack View: [Target] -> [Member(Target+Prop)] (continue, callable)
//                      -> [Prop]                (continue, not callable)
//                      -> []                    (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_Member_MapToList<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValueTarget(processor.PopValue());
	if (pValueTarget->IsIterable()) {
		RefPtr<Iterator> pIteratorTarget(pValueTarget->DoGenIterator());
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		for (;;) {
			RefPtr<Value> pValueTargetElem(pIteratorTarget->NextValue());
			if (!pValueTargetElem) break;
			Value* pValueProp = pValueTargetElem->DoPropGet(GetSymbol(), GetAttr(), true);
			if (!pValueProp) {
				processor.ErrorDone();
				return;
			} else {
				pValueOwner->push_back(pValueProp->AsMember(*pValueTargetElem));
			}
		}
		processor.PushValue(new Value_List(new ValueTypedOwner(pValueOwner.release())));
	} else {
		Value* pValueProp = pValueTarget->DoPropGet(GetSymbol(), GetAttr(), true);
		if (!pValueProp) {
			processor.ErrorDone();
			return;
		} else if (!discardValueFlag) {
			processor.PushValue(pValueProp->AsMember(*pValueTarget));
		}
	}
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Member_MapToList<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Member_MapToList(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Member_MapToList::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Member_MapToList<1, true>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Member_MapToList<1, false>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Member_MapToList<0, true>(_pSymbol, _pAttr.release());
		} else {
			_pPUnitCreated = new PUnit_Member_MapToList<0, false>(_pSymbol, _pAttr.release());
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_Member_MapToIter
// Stack View: [Target] -> [Member(Target+Prop)] (continue, callable)
//                      -> [Prop]                (continue, not callable)
//                      -> []                    (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_Member_MapToIter<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValueTarget(processor.PopValue());
	if (pValueTarget->IsIterable()) {
		RefPtr<Iterator> pIteratorTarget(pValueTarget->DoGenIterator());
		RefPtr<Iterator> pIterator(new Iterator_Member_MapToIter(
									   processor.Reference(), pIteratorTarget.release(),
									   GetSymbol(), GetAttr().Reference()));
		processor.PushValue(new Value_Iterator(pIterator.release()));
	} else {
		Value* pValueProp = pValueTarget->DoPropGet(GetSymbol(), GetAttr(), true);
		if (!pValueProp) {
			processor.ErrorDone();
			return;
		} else if (!discardValueFlag) {
			processor.PushValue(pValueProp->AsMember(*pValueTarget));
		}
	}
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_Member_MapToIter<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str.Printf("Member_MapToIter(`%s)", GetSymbol()->GetName());
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_Member_MapToIter::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Member_MapToIter<1, true>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_Member_MapToIter<1, false>(_pSymbol, _pAttr.release(), _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_Member_MapToIter<0, true>(_pSymbol, _pAttr.release());
		} else {
			_pPUnitCreated = new PUnit_Member_MapToIter<0, false>(_pSymbol, _pAttr.release());
		}
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
template<int nExprSrc, bool discardValueFlag, bool keepCarFlag>
PUnit_Argument<nExprSrc, discardValueFlag, keepCarFlag>::PUnit_Argument(const Attribute& attr, Expr_Block* pExprOfBlock) :
	_pAttr(new Attribute()), _flags(DeclCallable::Flag::None), _pExprOfBlock(pExprOfBlock)
{
	for (const Symbol* pSymbol : attr.GetSymbols()) {
		DeclCallable::Flags flag = DeclCallable::SymbolToFlag(pSymbol);
		_flags |= flag;
		if (!flag) _pAttr->AddSymbol(pSymbol);
	}
	_pAttr->AddSymbolsOpt(attr.GetSymbolsOpt());
}

template<int nExprSrc, bool discardValueFlag, bool keepCarFlag>
void PUnit_Argument<nExprSrc, discardValueFlag, keepCarFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	RefPtr<Value> pValueCar(keepCarFlag? processor.PeekValue(0).Reference() : processor.PopValue());
	const DeclCallable* pDeclCallable = pValueCar->GetDeclCallableWithError();
	if (!pDeclCallable || !pDeclCallable->CheckAttribute(GetAttr())) {
		processor.ErrorDone();
		return;
	}
	RefPtr<Argument> pArgument(
		new Argument(pValueCar.release(), pDeclCallable->Reference(),
					 GetAttr().Reference(), pDeclCallable->GetFlags() | GetFlags(), Value::nil(),
					 Expr_Block::Reference(GetExprOfBlock())));
	if (!discardValueFlag) processor.PushValue(new Value_Argument(pArgument.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag, bool keepCarFlag>
String PUnit_Argument<nExprSrc, discardValueFlag, keepCarFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
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
			if (_keepCarFlag) {
				_pPUnitCreated = new PUnit_Argument<1, true, true>(*_pAttr, _pExprOfBlock.release(), _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_Argument<1, true, false>(*_pAttr, _pExprOfBlock.release(), _pExprSrc.Reference());
			}
		} else {
			if (_keepCarFlag) {
				_pPUnitCreated = new PUnit_Argument<1, false, true>(*_pAttr, _pExprOfBlock.release(), _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_Argument<1, false, false>(*_pAttr, _pExprOfBlock.release(), _pExprSrc.Reference());
			}
		}
	} else {
		if (discardValueFlag) {
			if (_keepCarFlag) {
				_pPUnitCreated = new PUnit_Argument<0, true, true>(*_pAttr, _pExprOfBlock.release());
			} else {
				_pPUnitCreated = new PUnit_Argument<0, true, false>(*_pAttr, _pExprOfBlock.release());
			}
		} else {
			if (_keepCarFlag) {
				_pPUnitCreated = new PUnit_Argument<0, false, true>(*_pAttr, _pExprOfBlock.release());
			} else {
				_pPUnitCreated = new PUnit_Argument<0, false, false>(*_pAttr, _pExprOfBlock.release());
			}
		}
	}
	return _pPUnitCreated;
}

//------------------------------------------------------------------------------
// PUnit_ArgumentDelegation
// Stack View: keepCarFlag = false: [Car Expr] -> [Argument(Car)] (continue)
//                                             -> []              (discard)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
PUnit_ArgumentDelegation<nExprSrc, discardValueFlag>::PUnit_ArgumentDelegation(const Attribute& attr) :
	_pAttr(new Attribute()), _flags(DeclCallable::Flag::None)
{
	for (const Symbol* pSymbol : attr.GetSymbols()) {
		DeclCallable::Flags flag = DeclCallable::SymbolToFlag(pSymbol);
		_flags |= flag;
		if (!flag) _pAttr->AddSymbol(pSymbol);
	}
	_pAttr->AddSymbolsOpt(attr.GetSymbolsOpt());
}

template<int nExprSrc, bool discardValueFlag>
void PUnit_ArgumentDelegation<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
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
					 GetAttr().Reference(), pDeclCallable->GetFlags() | GetFlags(), Value::nil(),
					 pExprOfBlock.release()));
	if (!discardValueFlag) processor.PushValue(new Value_Argument(pArgument.release()));
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag>
String PUnit_ArgumentDelegation<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "ArgumentDelegation()";
	str += GetAttr().ToString(ss);
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_ArgumentDelegation::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_ArgumentDelegation<1, true>(*_pAttr, _pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_ArgumentDelegation<1, false>(*_pAttr, _pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_ArgumentDelegation<0, true>(*_pAttr);
		} else {
			_pPUnitCreated = new PUnit_ArgumentDelegation<0, false>(*_pAttr);
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
		return;
	}
	processor.SetPUnitNext(_GetPUnitCont());
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
// PUnit_EndArgSlotExpand
// Stack View: [Argument(Car) Any] -> [Argument(Car)] (continue)
//------------------------------------------------------------------------------
template<int nExprSrc, bool discardValueFlag>
void PUnit_EndArgSlotExpand<nExprSrc, discardValueFlag>::Exec(Processor& processor) const
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
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
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

template<int nExprSrc, bool discardValueFlag>
String PUnit_EndArgSlotExpand<nExprSrc, discardValueFlag>::ToString(const StringStyle& ss, int seqIdOffset) const
{
	String str;
	str += "EndArgSlotExpand()";
	AppendInfoToString(str, ss);
	return str;
}

PUnit* PUnitFactory_EndArgSlotExpand::Create(bool discardValueFlag)
{
	if (_pExprSrc) {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_EndArgSlotExpand<1, true>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_EndArgSlotExpand<1, false>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_EndArgSlotExpand<0, true>();
		} else {
			_pPUnitCreated = new PUnit_EndArgSlotExpand<0, false>();
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
		return;
	}
	processor.SetPUnitNext(_GetPUnitCont());
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
		if (discardValueFlag) {
			if (_branchDestFlag) {
				_pPUnitCreated = new PUnit_Break<1, true, true>(_pPUnitMarked, _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_Break<1, true, false>(_pPUnitMarked, _pExprSrc.Reference());
			}
		} else {
			if (_branchDestFlag) {
				_pPUnitCreated = new PUnit_Break<1, false, true>(_pPUnitMarked, _pExprSrc.Reference());
			} else {
				_pPUnitCreated = new PUnit_Break<1, false, false>(_pPUnitMarked, _pExprSrc.Reference());
			}
		}
	} else {
		if (discardValueFlag) {
			if (_branchDestFlag) {
				_pPUnitCreated = new PUnit_Break<0, true, true>(_pPUnitMarked);
			} else {
				_pPUnitCreated = new PUnit_Break<0, true, false>(_pPUnitMarked);
			}
		} else {
			if (_branchDestFlag) {
				_pPUnitCreated = new PUnit_Break<0, false, true>(_pPUnitMarked);
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
template<int nExprSrc, bool discardValueFlag, typename T_Frame>
void PUnit_PushFrame<nExprSrc, discardValueFlag, T_Frame>::Exec(Processor& processor) const
{
	if (nExprSrc > 0) processor.SetExprCur(_ppExprSrc[0]);
	processor.PushFrame<T_Frame>();
	if (discardValueFlag) processor.DiscardValue();
	processor.SetPUnitNext(_GetPUnitCont());
}

template<int nExprSrc, bool discardValueFlag, typename T_Frame>
String PUnit_PushFrame<nExprSrc, discardValueFlag, T_Frame>::ToString(const StringStyle& ss, int seqIdOffset) const
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
			_pPUnitCreated = new PUnit_PushFrame<1, true, T_Frame>(_pExprSrc.Reference());
		} else {
			_pPUnitCreated = new PUnit_PushFrame<1, false, T_Frame>(_pExprSrc.Reference());
		}
	} else {
		if (discardValueFlag) {
			_pPUnitCreated = new PUnit_PushFrame<0, true, T_Frame>();
		} else {
			_pPUnitCreated = new PUnit_PushFrame<0, false, T_Frame>();
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
