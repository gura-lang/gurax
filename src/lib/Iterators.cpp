//==============================================================================
// Iterators.cpp
//==============================================================================
#include "stdafx.h"
#include "../boost/combination.hpp"

namespace Gurax {

//------------------------------------------------------------------------------
// Iterator_Const
//------------------------------------------------------------------------------
String Iterator_Const::ToString(const StringStyle& ss) const
{
	String str;
	str += "Const:";
	str += _pValue->ToString();
	return str;
}

//------------------------------------------------------------------------------
// Iterator_ConstN
//------------------------------------------------------------------------------
Value* Iterator_ConstN::DoNextValue()
{
	if (_idx >= _num) return nullptr;
	_idx++;
	return _pValue->Reference();
}

String Iterator_ConstN::ToString(const StringStyle& ss) const
{
	String str;
	str += "ConstN:";
	str += _pValue->ToString();
	str.Printf(":n=%zu", _num);
	return str;
}

//------------------------------------------------------------------------------
// Iterator_Counter
//------------------------------------------------------------------------------
Value* Iterator_Counter::DoNextValue()
{
	Value* pValue = new Value_Number(_idx);
	_idx += _idxStep;
	return pValue;
}

String Iterator_Counter::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Counter:begin=%d:step=%d", _idxBegin, _idxStep);
	return str;
}

//------------------------------------------------------------------------------
// Iterator_UnaryOpImpMap
//------------------------------------------------------------------------------
Iterator_UnaryOpImpMap::Iterator_UnaryOpImpMap(Processor* pProcessor, const Operator* pOp, Value* pValue) :
	_pProcessor(pProcessor), _pOp(pOp), _pOpEntry(&OpEntry::Empty), _pValue(pValue),
	_pVTypePrev(&VTYPE_Undefined), _flags(Flag::None), _len(0)
{
	_flags = Flag::Finite | Flag::LenDetermined;
	_len = static_cast<size_t>(-1);
	GetValue().UpdateIteratorInfo(_flags, _len);
	if (!(_flags & Flag::LenDetermined)) _len = 0;
}

Value* Iterator_UnaryOpImpMap::DoNextValue()
{
	Frame& frame = GetProcessor().GetFrameCur();
	if (!GetValue().ReadyToPickValue(frame, *DeclArg::Any)) return nullptr;
	RefPtr<Value> pValueEach(GetValue().PickValue());
	const VType& vtype = pValueEach->GetVType();
	if (!vtype.IsIdentical(*_pVTypePrev)) {
		if (!(_pOpEntry = _pOp->FindMatchedEntry(vtype))) return nullptr;
	}
	return _pOpEntry->EvalUnary(GetProcessor(), *pValueEach);
}

String Iterator_UnaryOpImpMap::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("UnaryOpImpMap");
	return str;
}

//------------------------------------------------------------------------------
// Iterator_BinaryOpImpMap
//------------------------------------------------------------------------------
Iterator_BinaryOpImpMap::Iterator_BinaryOpImpMap(Processor* pProcessor, const Operator* pOp,
												 Value* pValueL, Value* pValueR) :
	_pProcessor(pProcessor), _pOp(pOp), _pOpEntry(&OpEntry::Empty),
	_pValueL(pValueL), _pValueR(pValueR), _pVTypePrevL(&VTYPE_Undefined), _pVTypePrevR(&VTYPE_Undefined),
	_flags(Flag::None), _len(0)
{
	_flags = Flag::Finite | Flag::LenDetermined;
	_len = static_cast<size_t>(-1);
	GetValueL().UpdateIteratorInfo(_flags, _len);
	GetValueR().UpdateIteratorInfo(_flags, _len);
	if (!(_flags & Flag::LenDetermined)) _len = 0;
}

Value* Iterator_BinaryOpImpMap::DoNextValue()
{
	Frame& frame = GetProcessor().GetFrameCur();
	if (!GetValueL().ReadyToPickValue(frame, *DeclArg::Any) ||
		!GetValueR().ReadyToPickValue(frame, *DeclArg::Any)) return nullptr;
	RefPtr<Value> pValueEachL(GetValueL().PickValue());
	RefPtr<Value> pValueEachR(GetValueR().PickValue());
	const VType& vtypeL = pValueEachL->GetVType();
	const VType& vtypeR = pValueEachR->GetVType();
	if (!vtypeL.IsIdentical(*_pVTypePrevL) || !vtypeR.IsIdentical(*_pVTypePrevR)) {
		if (!(_pOpEntry = _pOp->FindMatchedEntry(vtypeL, vtypeR))) return nullptr;
	}
	return _pOpEntry->EvalBinary(GetProcessor(), *pValueEachL, *pValueEachR);
}

String Iterator_BinaryOpImpMap::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("BinaryOpImpMap");
	return str;
}

//------------------------------------------------------------------------------
// Iterator_FunctionImpMap
//------------------------------------------------------------------------------
template<bool skipNilFlag>
Iterator_FunctionImpMap<skipNilFlag>::Iterator_FunctionImpMap(
	Processor* pProcessor, Function* pFunction, Argument* pArgument) :
	_pProcessor(pProcessor), _pFunction(pFunction), _pArgument(pArgument),
	_flags(Flag::None), _len(0)
{
	ArgSlot* pArgSlot = GetArgument().GetArgSlotFirst();
	_flags = Flag::Finite | Flag::LenDetermined;
	_len = static_cast<size_t>(-1);
	for ( ; pArgSlot; pArgSlot = pArgSlot->GetNext()) {
		pArgSlot->UpdateIteratorInfo(_flags, _len);
	}
	if (!(_flags & Flag::LenDetermined)) _len = 0;
}

template<bool skipNilFlag>
Value* Iterator_FunctionImpMap<skipNilFlag>::DoNextValue()
{
	Frame& frame = GetProcessor().GetFrameCur();
	if (skipNilFlag) {
		for (;;) {
			if (!GetArgument().ReadyToPickValue(frame)) break;
			RefPtr<Value> pValueRtn(GetFunction().DoEval(GetProcessor(), GetArgument()));
			if (pValueRtn->IsValid()) return pValueRtn.release();
		}
		return nullptr;
	} else {
		if (!GetArgument().ReadyToPickValue(frame)) return nullptr;
		RefPtr<Value> pValueRtn(GetFunction().DoEval(GetProcessor(), GetArgument()));
		if (Error::IsIssued()) return nullptr;
		return pValueRtn.release();
	}
}

template<bool skipNilFlag>
String Iterator_FunctionImpMap<skipNilFlag>::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("FunctionImpMap");
	return str;
}

template class Iterator_FunctionImpMap<true>;
template class Iterator_FunctionImpMap<false>;

//------------------------------------------------------------------------------
// Iterator_Range
//------------------------------------------------------------------------------
Value* Iterator_Range::DoNextValue()
{
	if (_idx == _idxEnd) return nullptr;
	Value* pValue = new Value_Number(_idx);
	_idx += _idxStep;
	return pValue;
}

String Iterator_Range::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Range:begin=%d:end=%d:step=%d", _idxBegin, _idxEnd, _idxStep);
	return str;
}

//------------------------------------------------------------------------------
// Iterator_Member_MapAlong
//------------------------------------------------------------------------------
Value* Iterator_Member_MapAlong::DoNextValue()
{
	RefPtr<Value> pValueTargetElem(GetIteratorTarget().NextValue());
	if (!pValueTargetElem) return nullptr;
	Value* pValueProp = pValueTargetElem->DoPropGet(GetSymbol(), GetAttr(), true);
	return pValueProp? pValueProp->AsMember(*pValueTargetElem) : nullptr;
}

String Iterator_Member_MapAlong::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Member_MapAlong");
	return str;
}

//------------------------------------------------------------------------------
// Iterator_Member_MapToIter
//------------------------------------------------------------------------------
Value* Iterator_Member_MapToIter::DoNextValue()
{
	RefPtr<Value> pValueTargetElem(GetIteratorTarget().NextValue());
	if (!pValueTargetElem) return nullptr;
	Value* pValueProp = pValueTargetElem->DoPropGet(GetSymbol(), GetAttr(), true);
	return pValueProp? pValueProp->AsMember(*pValueTargetElem) : nullptr;
}

String Iterator_Member_MapToIter::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Member_MapToIter");
	return str;
}

//------------------------------------------------------------------------------
// Iterator_IteratorEvaluator
//------------------------------------------------------------------------------
Value* Iterator_IteratorEvaluator::DoNextValue()
{
	RefPtr<Value> pValueElem(GetIterator().NextValue());
	if (!pValueElem) return nullptr;
	if (!GetArgument().GetDeclCallable().IsIdentical(pValueElem->GetDeclCallable())) {
		Error::Issue(ErrorType::ValueError,
					 "member mapping cannot be applied to an iterator that returns different type of values");
		return nullptr;
	}
	RefPtr<Value> pValueRtn(pValueElem->DoEval(GetProcessor(), GetArgument()));
	if (Error::IsIssued()) return nullptr;
	return pValueRtn.release();
}

String Iterator_IteratorEvaluator::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("IteratorEvaluator:%s", GetArgument().ToString(StringStyle().Cram()).c_str());
	return str;
}

//------------------------------------------------------------------------------
// Iterator_for
//------------------------------------------------------------------------------
Value* Iterator_for::DoNextValue()
{
#if 0
	while (_contFlag) {
		

		if (GetFiniteFlag() && _idx >= _cnt) break;
		if (GetArgument().HasArgSlot()) {
			ArgFeeder args(GetArgument());
			if (!args.FeedValue(GetFrame(), new Value_Number(_idx))) return Value::nil();
		}
		_idx++;
		Processor::Event event;
		RefPtr<Value> pValueRtn(GetProcessor().EvalExpr(GetExprOfBlock(), GetArgument(), &event));
		if (Error::IsIssued()) break;
		if (Processor::IsEventBreak(event)) {
			_contFlag = false;
			if (pValueRtn->IsUndefined()) break;
		}
		if (GetSkipNilFlag()) {
			if (pValueRtn->IsValid()) return pValueRtn.release();
		} else {
			return pValueRtn->IsValid()? pValueRtn.release() : Value::nil();
		}
	}
#endif
	return nullptr;
}

String Iterator_for::ToString(const StringStyle& ss) const
{
	return "for";
}

//------------------------------------------------------------------------------
// Iterator_while
//------------------------------------------------------------------------------
Value* Iterator_while::DoNextValue()
{
#if 0
	while (_contFlag) {
		if (GetFiniteFlag() && _idx >= _cnt) break;
		if (GetArgument().HasArgSlot()) {
			ArgFeeder args(GetArgument());
			if (!args.FeedValue(GetFrame(), new Value_Number(_idx))) return Value::nil();
		}
		_idx++;
		Processor::Event event;
		RefPtr<Value> pValueRtn(GetProcessor().EvalExpr(GetExprOfBlock(), GetArgument(), &event));
		if (Error::IsIssued()) break;
		if (Processor::IsEventBreak(event)) {
			_contFlag = false;
			if (pValueRtn->IsUndefined()) break;
		}
		if (GetSkipNilFlag()) {
			if (pValueRtn->IsValid()) return pValueRtn.release();
		} else {
			return pValueRtn->IsValid()? pValueRtn.release() : Value::nil();
		}
	}
#endif
	return nullptr;
}

String Iterator_while::ToString(const StringStyle& ss) const
{
	return "while";
}

//------------------------------------------------------------------------------
// Iterator_repeat
//------------------------------------------------------------------------------
Value* Iterator_repeat::DoNextValue()
{
	while (_contFlag) {
		if (GetFiniteFlag() && _idx >= _cnt) break;
		if (GetArgument().HasArgSlot()) {
			ArgFeeder args(GetArgument());
			if (!args.FeedValue(GetFrame(), new Value_Number(_idx))) return Value::nil();
		}
		_idx++;
		Processor::Event event;
		RefPtr<Value> pValueRtn(GetProcessor().EvalExpr(GetExprOfBlock(), GetArgument(), &event));
		if (Error::IsIssued()) break;
		if (Processor::IsEventBreak(event)) {
			_contFlag = false;
			if (pValueRtn->IsUndefined()) break;
		}
		if (GetSkipNilFlag()) {
			if (pValueRtn->IsValid()) return pValueRtn.release();
		} else {
			return pValueRtn->IsValid()? pValueRtn.release() : Value::nil();
		}
	}
	return nullptr;
}

String Iterator_repeat::ToString(const StringStyle& ss) const
{
	return "repeat";
}

//------------------------------------------------------------------------------
// Iterator_DoEach
//------------------------------------------------------------------------------
Value* Iterator_DoEach::DoNextValue()
{
	while (_contFlag) {
		RefPtr<Value> pValue(GetIteratorSrc().NextValue());
		if (!pValue) return nullptr;
		if (GetArgument().HasArgSlot()) {
			ArgFeeder args(GetArgument());
			if (!args.FeedValue(GetFrame(), pValue.Reference())) return Value::nil();
			if (args.IsValid() && !args.FeedValue(GetFrame(), new Value_Number(_idx))) return Value::nil();
		}
		_idx++;
		Processor::Event event;
		GetProcessor().PushFrame(GetFrame().Reference());
		RefPtr<Value> pValueRtn(GetProcessor().EvalExpr(GetExprOfBlock(), GetArgument(), &event));
		GetProcessor().PopFrame();
		if (Error::IsIssued()) break;
		if (Processor::IsEventBreak(event)) {
			_contFlag = false;
			if (pValueRtn->IsUndefined()) break;
		}
		if (GetSkipNilFlag()) {
			if (pValueRtn->IsValid()) return pValueRtn.release();
		} else {
			return pValueRtn->IsValid()? pValueRtn.release() : Value::nil();
		}
	}
	return nullptr;
}

String Iterator_DoEach::ToString(const StringStyle& ss) const
{
	return "DoEach";
}

//------------------------------------------------------------------------------
// Iterator_Each
//------------------------------------------------------------------------------
Value* Iterator_Each::DoNextValue()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (_idx >= _idxEnd) return nullptr;
	return valueOwner[_idx++]->Reference();
}

String Iterator_Each::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Each:begin=%zu:end=%zu", _idxBegin, _idxEnd);
	return str;
}

//------------------------------------------------------------------------------
// Iterator_Reverse
//------------------------------------------------------------------------------
Value* Iterator_Reverse::DoNextValue()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (_idx >= valueOwner.size()) return nullptr;
	RefPtr<Value> pValue((*(valueOwner.rbegin() + _idx))->Reference());
	_idx++;
	return pValue.release();
}

String Iterator_Reverse::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Reverse:n=%zu", GetValueOwner().size());
	return str;
}

//------------------------------------------------------------------------------
// Iterator_Cycle
//------------------------------------------------------------------------------
Value* Iterator_Cycle::DoNextValue()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (_cnt >= 0 && _idxCur >= _cnt) return nullptr;
	if (_idx == static_cast<Int>(valueOwner.size())) _idx = 0;
	return valueOwner[_idx++]->Reference();
}

String Iterator_Cycle::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Cycle:n=%zu", GetValueOwner().size());
	return str;
}

//-----------------------------------------------------------------------------
// Iterator_Align
//-----------------------------------------------------------------------------
Value* Iterator_Align::DoNextValue()
{
	if (_cnt == 0) return nullptr;
	_cnt--;
	if (_stuffFlag) return _pValueStuff.Reference();
	RefPtr<Value> pValueElem(GetIteratorSrc().NextValue());
	if (pValueElem) return pValueElem.release();
	_stuffFlag = true;
	return _pValueStuff.Reference();
}

String Iterator_Align::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Align(";
	rtn += GetIteratorSrc().ToString(ss);
	rtn += ")";
	return rtn;
}

//------------------------------------------------------------------------------
// Iterator_Head
//------------------------------------------------------------------------------
Value* Iterator_Head::DoNextValue()
{
	if (_doneFlag || _idxCur >= _cnt) return nullptr;
	RefPtr<Value> pValueElem(GetIteratorSrc().NextValue());
	if (!pValueElem) {
		_doneFlag = true;
		return nullptr;
	}
	return pValueElem.release();
}

String Iterator_Head::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Head:n=%zu", _cnt);
	return str;
}

//------------------------------------------------------------------------------
// Iterator_Offset
//------------------------------------------------------------------------------
Value* Iterator_Offset::DoNextValue()
{
	if (_firstFlag) {
		_firstFlag = false;
		for (size_t i = 0; i < _offset; i++) {
			RefPtr<Value> pValueElem(GetIteratorSrc().NextValue());
			if (pValueElem) {
				// nothing to do
			} else {
				if (Error::IsIssued()) return nullptr;
				if (_raiseFlag) {
					Error::Issue(ErrorType::RangeError, "offset value exceeds the length of elements");
				}
				return nullptr;
			}
		}
	}
	return GetIteratorSrc().NextValue();
}

String Iterator_Offset::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Offset:offset=%d", _offset);
	return str;
}

//------------------------------------------------------------------------------
// Iterator_PingPong
//------------------------------------------------------------------------------
Value* Iterator_PingPong::DoNextValue()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (_cnt >= 0 && _idxCur >= _cnt) return nullptr;
	RefPtr<Value> pValue(valueOwner[_idx]->Reference());
	if (_forwardFlag) {
		if (_idx + 1 == valueOwner.size()) {
			if (!_stickyFlagBtm) _idx--;
			_forwardFlag = false;
		} else {
			_idx++;
		}
	} else {
		if (_idx == 0) {
			if (!_stickyFlagTop) _idx++;
			_forwardFlag = true;
		} else {
			_idx--;
		}
	}
	return pValue.release();
}

String Iterator_PingPong::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("PingPong:n=%zu", GetValueOwner().size());
	return str;
}

//-----------------------------------------------------------------------------
// Iterator_Fold
//-----------------------------------------------------------------------------
Iterator_Fold::Iterator_Fold(Iterator* pIteratorSrc, size_t nSize, size_t nAdvance,
							 bool itemAsIterFlag, bool neatFlag) :
	_pIteratorSrc(pIteratorSrc), _nSize(nSize), _nAdvance(nAdvance),
	_itemAsIterFlag(itemAsIterFlag), _neatFlag(neatFlag), _doneFlag(false)
{
	if (_nAdvance < _nSize) {
		_pValueOwnerRemain.reset(new ValueOwner());
		_pValueOwnerRemain->reserve(_nSize - _nAdvance);
	}
}

Value* Iterator_Fold::DoNextValue()
{
	if (_doneFlag) return nullptr;
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(_nSize);
	if (_nAdvance < _nSize) {
		std::copy(_pValueOwnerRemain->begin(), _pValueOwnerRemain->end(), std::back_inserter(*pValueOwner));
		_pValueOwnerRemain->clear();	// don't use Clear() to avoid decrementation of reference counter
		while (pValueOwner->size() < _nSize) {
			RefPtr<Value> pValueElem(GetIteratorSrc().NextValue());
			if (!pValueElem) {
				_doneFlag = true;
				if (Error::IsIssued()) return nullptr;
				break;
			}
			pValueOwner->push_back(pValueElem.release());
		}
		if (pValueOwner->size() > _nAdvance) {
			std::copy(pValueOwner->begin() + _nAdvance, pValueOwner->end(), std::back_inserter(*_pValueOwnerRemain));
		_pValueOwnerRemain->IncCntRefOfEach();
		}
	} else {
		while (pValueOwner->size() < _nSize) {
			RefPtr<Value> pValueElem(GetIteratorSrc().NextValue());
			if (!pValueElem) {
				_doneFlag = true;
				if (Error::IsIssued()) return nullptr;
				break;
			}
			pValueOwner->push_back(pValueElem.release());
		}
		// dumb reading
		for (size_t n = _nAdvance - _nSize; n > 0; n--) {
			RefPtr<Value> pValueElem(GetIteratorSrc().NextValue());
			if (!pValueElem) {
				_doneFlag = true;
				if (Error::IsIssued()) return nullptr;
				break;
			}
		}
	}
	if (pValueOwner->empty() || (_neatFlag && pValueOwner->size() < _nSize)) {
		_doneFlag = true;
		return nullptr;
	} else if (_itemAsIterFlag) {
		RefPtr<Iterator> pIterator(new Iterator_Each(pValueOwner.release()));
		return new Value_Iterator(pIterator.release());
	} else {
		return new Value_List(pValueOwner.release());
	}
}

size_t Iterator_Fold::GetLength() const
{
	if (GetIteratorSrc().IsLenUndetermined()) return -1;
	size_t nElems = GetIteratorSrc().GetLength();
	return _neatFlag? nElems / _nSize : (nElems + _nSize - 1) / _nSize;
}

String Iterator_Fold::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Fold:%s", GetIteratorSrc().ToString().c_str());
	return str;
}

//------------------------------------------------------------------------------
// Iterator_Flatten
//------------------------------------------------------------------------------
Iterator_Flatten::Iterator_Flatten(Iterator* pIterator, SearchMode searchMode) :
	_pIteratorCur(pIterator->Reference()), _searchMode(searchMode)
{
	_iteratorDeque.push_back(pIterator);
}

Value* Iterator_Flatten::DoNextValue()
{
	for (;;) {
		RefPtr<Value> pValue(GetIteratorCur().DoNextValue());
		if (pValue) {
			if (!pValue->IsIterable()) return pValue.release();
			RefPtr<Iterator> pIterator(pValue->DoGenIterator());
			if (!pIterator || !pIterator->MustBeFinite()) break;
			_iteratorDeque.push_back(pIterator.Reference());
			if (_searchMode == SearchMode::DepthFirst) _pIteratorCur.reset(pIterator.release());
		} else if (_searchMode == SearchMode::DepthFirst) {
			Iterator::Delete(_iteratorDeque.back());
			_iteratorDeque.pop_back();
			if (_iteratorDeque.empty()) break;
			_pIteratorCur.reset(_iteratorDeque.back()->Reference());
		} else { // _searchMode == SearchMode::BreadthFirst
			Iterator::Delete(_iteratorDeque.front());
			_iteratorDeque.pop_front();
			if (_iteratorDeque.empty()) break;
			_pIteratorCur.reset(_iteratorDeque.front()->Reference());
		}
	}
	return nullptr;
}

String Iterator_Flatten::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "Flatten";
	return rtn;
}

//------------------------------------------------------------------------------
// Iterator_SinceWithFunc
//------------------------------------------------------------------------------
Iterator_SinceWithFunc::Iterator_SinceWithFunc(Processor* pProcessor, Function* pFunction, Iterator* pIteratorSrc, bool includeFirstFlag) :
	_pProcessor(pProcessor), _pFunction(pFunction), _pIteratorSrc(pIteratorSrc),
	_pArgument(new Argument(*pFunction)), _idx(0),
	_includeFirstFlag(includeFirstFlag), _contFlag(true), _triggeredFlag(false)
{
}

Value* Iterator_SinceWithFunc::DoNextValue()
{
	RefPtr<Frame> pFrame(GetFunction().LockFrameOuter());
	if (!pFrame) return nullptr;
	while (_contFlag) {
		RefPtr<Value> pValue(GetIteratorSrc().NextValue());
		if (!pValue) {
			_contFlag = false;
			break;
		}
		if (_triggeredFlag) return pValue.release();
		if (GetArgument().HasArgSlot()) {
			ArgFeeder args(GetArgument());
			if (!args.FeedValue(*pFrame, pValue.Reference())) return Value::nil();
			if (args.IsValid() && !args.FeedValue(*pFrame, new Value_Number(_idx))) return Value::nil();
		}
		_idx++;
		RefPtr<Value> pValueRtn(GetFunction().DoEval(GetProcessor(), GetArgument()));
		if (pValueRtn->GetBool()) {
			_triggeredFlag = true;
			if (_includeFirstFlag) return pValue.release();
		}
	}	
	return nullptr;
}

String Iterator_SinceWithFunc::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("SinceWithFunc");
	return str;
}

//------------------------------------------------------------------------------
// Iterator_SinceWithIter
//------------------------------------------------------------------------------
Iterator_SinceWithIter::Iterator_SinceWithIter(
	Iterator* pIteratorCriteria, Iterator* pIteratorSrc, bool includeFirstFlag) :
	_pIteratorCriteria(pIteratorCriteria), _pIteratorSrc(pIteratorSrc),
	_includeFirstFlag(includeFirstFlag), _contFlag(true), _triggeredFlag(false)
{
}

Value* Iterator_SinceWithIter::DoNextValue()
{
	while (_contFlag) {
		RefPtr<Value> pValue(GetIteratorSrc().NextValue());
		if (!pValue) {
			_contFlag = false;
			break;
		}
		RefPtr<Value> pValueCriteria(GetIteratorCriteria().NextValue());
		if (!pValueCriteria) {
			_contFlag = false;
			break;
		}
		if (_triggeredFlag) return pValue.release();
		if (pValueCriteria->GetBool()) {
			_triggeredFlag = true;
			if (_includeFirstFlag) return pValue.release();
		}
	}	
	return nullptr;
}

String Iterator_SinceWithIter::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("SinceWithIter");
	return str;
}

//------------------------------------------------------------------------------
// Iterator_Permutation
//------------------------------------------------------------------------------
Value* Iterator_Permutation::DoNextValue()
{
	if (_doneFlag) return nullptr;
	RefPtr<Value> pValue(new Value_List(GetValueOwner().Extract<size_t>(_indices)));
	_doneFlag = !std::next_permutation(_indices.begin(), _indices.end());
	return pValue.release();
}

String Iterator_Permutation::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Permutation:n=%zu", GetValueOwner().size());
	return str;
}

//------------------------------------------------------------------------------
// Iterator_PartialPermutation
//------------------------------------------------------------------------------
Value* Iterator_PartialPermutation::DoNextValue()
{
	if (_doneFlag) return nullptr;
	RefPtr<Value> pValue(new Value_List(GetValueOwner().Extract(_indices, _nExtract)));
	_doneFlag = !boost::next_partial_permutation(_indices.begin(), _indices.begin() + _nExtract, _indices.end());
	return pValue.release();
}

String Iterator_PartialPermutation::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("PartialPermutation:n=%zu:r=%zu", GetValueOwner().size(), _nExtract);
	return str;
}

//------------------------------------------------------------------------------
// Iterator_Combination
//------------------------------------------------------------------------------
Value* Iterator_Combination::DoNextValue()
{
	if (_doneFlag) return nullptr;
	RefPtr<Value> pValue(new Value_List(GetValueOwner().Extract(_indices, _nExtract)));
	_doneFlag = !boost::next_combination(_indices.begin(), _indices.begin() + _nExtract, _indices.end());
	return pValue.release();
}

String Iterator_Combination::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Combination:n=%zu:r=%zu", GetValueOwner().size(), _nExtract);
	return str;
}

}
