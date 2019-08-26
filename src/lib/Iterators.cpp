//==============================================================================
// Iterators.cpp
//==============================================================================
#include "stdafx.h"

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
Iterator_UnaryOpImpMap::Iterator_UnaryOpImpMap(Processor* pProcessor, const Operator* pOperator, Value* pValue) :
	_pProcessor(pProcessor), _pOperator(pOperator), _pOpEntry(&OpEntry::Empty), _pValue(pValue),
	_pVTypePrev(&VTYPE_Undefined), _flags(Flag::None), _len(0)
{
	_flags = Flag::Finite | Flag::LenDetermined;
	_len = static_cast<size_t>(-1);
	GetValue().UpdateIteratorInfo(_flags, _len);
	if (!(_flags & Flag::LenDetermined)) _len = 0;
}

Value* Iterator_UnaryOpImpMap::DoNextValue()
{
	if (!GetValue().ReadyToPickValue()) return nullptr;
	RefPtr<Value> pValueEach(GetValue().PickValue());
	const VType& vtype = pValueEach->GetVType();
	if (!vtype.IsIdentical(*_pVTypePrev)) {
		if (!(_pOpEntry = _pOperator->FindMatchedEntry(vtype))) return nullptr;
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
Iterator_BinaryOpImpMap::Iterator_BinaryOpImpMap(Processor* pProcessor, const Operator* pOperator,
												 Value* pValueL, Value* pValueR) :
	_pProcessor(pProcessor), _pOperator(pOperator), _pOpEntry(&OpEntry::Empty),
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
	if (!GetValueL().ReadyToPickValue() || !GetValueR().ReadyToPickValue()) return nullptr;
	RefPtr<Value> pValueEachL(GetValueL().PickValue());
	RefPtr<Value> pValueEachR(GetValueR().PickValue());
	const VType& vtypeL = pValueEachL->GetVType();
	const VType& vtypeR = pValueEachR->GetVType();
	if (!vtypeL.IsIdentical(*_pVTypePrevL) || !vtypeR.IsIdentical(*_pVTypePrevR)) {
		if (!(_pOpEntry = _pOperator->FindMatchedEntry(vtypeL, vtypeR))) return nullptr;
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
	if (skipNilFlag) {
		for (;;) {
			if (!GetArgument().ReadyToPickValue()) break;
			RefPtr<Value> pValueRtn(GetFunction().DoEval(GetProcessor(), GetArgument()));
			if (pValueRtn->IsValid()) return pValueRtn.release();
		}
		return nullptr;
	} else {
		if (!GetArgument().ReadyToPickValue()) return nullptr;
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

}
