//==============================================================================
// Index.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Index
//------------------------------------------------------------------------------
Value* Index::IndexGet() const
{
	return GetValueCar().DoIndexGet(*this);
}

bool Index::EachIndexGet(const Value& valueIndex, Value** ppValue) const
{
	if (valueIndex.IsInstanceOf(VTYPE_List)) {
		Value* pValue = nullptr;
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		const Value_List& valueIndexEx = dynamic_cast<const Value_List&>(valueIndex);
		for (const Value* pValueIndexEach : valueIndexEx.GetValueOwner()) {
			if (!EachIndexGet(*pValueIndexEach, &pValue)) return false;
			pValueOwner->push_back(pValue->Reference());
		}
		if (GetValueCar().IsTuple()) {
			*ppValue = new Value_Tuple(pValueOwner.release());
		} else {
			*ppValue = new Value_List(pValueOwner.release());
		}
		return true;
	} else if (valueIndex.IsInstanceOf(VTYPE_Iterator)) {
		Value* pValue = nullptr;
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		const Value_Iterator& valueIndexEx = dynamic_cast<const Value_Iterator&>(valueIndex);
		Iterator& iteratorIndex = valueIndexEx.GetIterator();
		for (;;) {
			RefPtr<Value> pValueIndexEach(iteratorIndex.NextValue());
			if (!pValueIndexEach) break;
			if (!EachIndexGet(*pValueIndexEach, &pValue)) return false;
			pValueOwner->push_back(pValue->Reference());
		}
		if (GetValueCar().IsTuple()) {
			*ppValue = new Value_Tuple(pValueOwner.release());
		} else {
			*ppValue = new Value_List(pValueOwner.release());
		}
		return true;
	}
	return GetValueCar().DoSingleIndexGet(valueIndex, ppValue);
}

void Index::IndexSet(RefPtr<Value> pValue)
{
	GetValueCar().DoIndexSet(*this, pValue.release());
}

bool Index::EachIndexSet(const Value& valueIndex, RefPtr<Value> pValue) const
{
	if (valueIndex.IsInstanceOf(VTYPE_List)) {
		const Value_List& valueIndexEx = dynamic_cast<const Value_List&>(valueIndex);
		if (pValue->IsIterable()) {
			RefPtr<Iterator> pIteratorSrc(pValue->GenIterator());
			for (const Value* pValueIndexEach : valueIndexEx.GetValueOwner()) {
				RefPtr<Value> pValueEach(pIteratorSrc->NextValue());
				if (!pValueIndexEach) break;
				if (!EachIndexSet(*pValueIndexEach, pValueEach.release())) return false;
			}
		} else {
			for (const Value* pValueIndexEach : valueIndexEx.GetValueOwner()) {
				if (!EachIndexSet(*pValueIndexEach, pValue->Reference())) return false;
			}
		}
		return true;
	} else if (valueIndex.IsInstanceOf(VTYPE_Iterator)) {
		const Value_Iterator& valueIndexEx = dynamic_cast<const Value_Iterator&>(valueIndex);
		Iterator& iteratorIndex = valueIndexEx.GetIterator();
		if (pValue->IsIterable()) {
			RefPtr<Iterator> pIteratorSrc(pValue->GenIterator());
			if (iteratorIndex.IsInfinite() && pIteratorSrc->IsInfinite()) {
				Error::Issue(ErrorType::IteratorError, "infinite iterator is unacceptable");
				return false;
			}
			for (;;) {
				RefPtr<Value> pValueIndexEach(iteratorIndex.NextValue());
				if (!pValueIndexEach) break;
				RefPtr<Value> pValueEach(pIteratorSrc->NextValue());
				if (!pValueIndexEach) break;
				if (!EachIndexSet(*pValueIndexEach, pValueEach.release())) return false;
			}
		} else {
			if (iteratorIndex.IsInfinite()) {
				Error::Issue(ErrorType::IteratorError, "infinite iterator is unacceptable");
				return false;
			}
			for (;;) {
				RefPtr<Value> pValueIndexEach(iteratorIndex.NextValue());
				if (!pValueIndexEach) break;
				if (!EachIndexSet(*pValueIndexEach, pValue->Reference())) return false;
			}
		}
		return true;
	}
	return GetValueCar().DoSingleIndexSet(valueIndex, pValue.release());
}

Value* Index::IndexOpApply(Value& value, Processor& processor, Operator& op)
{
	const ValueList& valuesIndex = GetValueOwner();
	if (valuesIndex.empty()) {
		Error::Issue(ErrorType::IndexError, "empty-indexing access is not supported");
		return nullptr;
	} else if (valuesIndex.size() == 1) {
		const Value& valueIndex = *valuesIndex.front();
		Value* pValueL = nullptr;
		if (!EachIndexGet(valueIndex, &pValueL)) return Value::nil();
		RefPtr<Value> pValueRtn(op.EvalBinary(processor, *pValueL, value));
		if (pValueRtn->IsUndefined()) return Value::nil();
		EachIndexSet(valueIndex, pValueRtn.Reference());
		return pValueRtn.release();
	} else if (value.IsIterable()) {
		Error::Issue_UnimplementedOperation();
		return Value::nil();
	} else {
		Error::Issue_UnimplementedOperation();
		return Value::nil();
	}
}

String Index::ToString(const StringStyle& ss) const
{
	return String().Format("Index:%s", GetValueCar().ToString(StringStyle(ss).SetQuoteSymbol()).c_str());
}

}
