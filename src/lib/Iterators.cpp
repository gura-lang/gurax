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
Value* Iterator_ConstN::NextValue()
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
Value* Iterator_Counter::NextValue()
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
// Iterator_ListElem
//------------------------------------------------------------------------------
Value* Iterator_ListElem::NextValue()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (_idx >= valueOwner.size()) return nullptr;
	return valueOwner[_idx++]->Reference();
}

String Iterator_ListElem::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("ListElem:n=%zu", GetValueOwner().size());
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
	_pValue->UpdateIteratorInfo(_flags, _len);
	if (!(_flags & Flag::LenDetermined)) _len = 0;
}

Value* Iterator_UnaryOpImpMap::NextValue()
{
	if (!_pValue->ReadyToPickValue()) return nullptr;
	RefPtr<Value> pValueEach(_pValue->PickValue());
	const VType& vtype = pValueEach->GetVType();
	if (!vtype.IsIdentical(*_pVTypePrev)) {
		if (!(_pOpEntry = _pOperator->LookupEntry(vtype)) &&
			!(_pOpEntry = _pOperator->LookupEntry(VTYPE_Any))) {
			Error::Issue(ErrorType::TypeError, "unsupported %s operation: %s",
						 _pOperator->IsMathUnary()? "math" : "unary", _pOperator->ToString(vtype).c_str());
			return nullptr;
		}
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

Value* Iterator_FunctionImpMap::NextValue()
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
Value* Iterator_Range::NextValue()
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

}
