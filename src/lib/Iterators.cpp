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
Iterator_FunctionImpMap::Iterator_FunctionImpMap(Processor* pProcessor, Function* pFunction, Argument* pArgument) :
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

Value* Iterator_FunctionImpMap::DoNextValue()
{
	if (!GetArgument().ReadyToPickValue()) return nullptr;
	return GetFunction().DoEval(GetProcessor(), GetArgument());
}

String Iterator_FunctionImpMap::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("FunctionImpMap");
	return str;
}

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
// Iterator_MemberMapToIter
//------------------------------------------------------------------------------
Value* Iterator_MemberMapToIter::DoNextValue()
{
	RefPtr<Value> pValueTargetElem(GetIteratorTarget().NextValue());
	if (!pValueTargetElem) return nullptr;
	Value* pValueProp = pValueTargetElem->DoPropGet(GetSymbol(), GetAttr(), true);
	if (!pValueProp) return nullptr;
	if (pValueProp->IsCallable() && !pValueProp->IsIterable()) {
		return new Value_CallableMember(pValueTargetElem.release(), pValueProp->Reference());
	} else {
		return pValueProp->Reference();
	}
}

String Iterator_MemberMapToIter::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("MemberMapToIter");
	return str;
}

}
