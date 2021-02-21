//==============================================================================
// Index.cpp
//==============================================================================
#include "stdafx.h"

//#define NEWFEATURE

namespace Gurax {

//------------------------------------------------------------------------------
// Index
//------------------------------------------------------------------------------
Value* Index::IndexGet() const
{
#if defined(NEWFEATURE)
	const ValueList& valuesIndex = GetValueOwner();
	if (valuesIndex.empty()) {
		Value* pValue = nullptr;
		if (!GetValueCar().DoEmptyIndexGet2(&pValue)) return Value::nil();
		return pValue;
	} else if (valuesIndex.size() == 1) {
		const Value& valueIndex = *valuesIndex.front();
		Value* pValue = nullptr;
		if (!EachIndexGet(valueIndex, &pValue, false)) return Value::nil();
		return pValue;
	} else {
		RefPtr<ValueOwner> pValuesRtn(new ValueOwner());
		pValuesRtn->reserve(valuesIndex.size());
		for (const Value* pValueIndex : valuesIndex) {
			Value* pValue = nullptr;
			if (!EachIndexGet(*pValueIndex, &pValue, false)) return Value::nil();
			pValuesRtn->push_back(pValue);
		}
		return new Value_List(pValuesRtn.release());
	}
#else
	return GetValueCar().DoIndexGet(*this);
#endif
}

bool Index::EachIndexGet(const Value& valueIndex, Value** ppValue, bool tupleResultFlag) const
{
	if (valueIndex.IsInstanceOf(VTYPE_List)) {
		Value* pValue = nullptr;
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		const Value_List& valueIndexEx = dynamic_cast<const Value_List&>(valueIndex);
		for (const Value* pValueIndexEach : valueIndexEx.GetValueOwner()) {
			if (!EachIndexGet(*pValueIndexEach, &pValue, tupleResultFlag)) return false;
			pValueOwner->push_back(pValue->Reference());
		}
		if (tupleResultFlag) {
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
			if (!EachIndexGet(*pValueIndexEach, &pValue, tupleResultFlag)) return false;
			pValueOwner->push_back(pValue->Reference());
		}
		if (tupleResultFlag) {
			*ppValue = new Value_Tuple(pValueOwner.release());
		} else {
			*ppValue = new Value_List(pValueOwner.release());
		}
		return true;
	}
	return GetValueCar().DoIndexGet2(valueIndex, ppValue);
}

void Index::IndexSet(RefPtr<Value> pValue)
{
#if defined(NEWFEATURE)
	const ValueList& valuesIndex = GetValueOwner();
	if (valuesIndex.empty()) {
		GetValueCar().DoEmptyIndexSet2(pValue.release());
		//Error::Issue(ErrorType::IndexError, "empty-indexing access is not supported");
	} else if (valuesIndex.size() == 1) {
		const Value& valueIndex = *valuesIndex.front();
		EachIndexSet(valueIndex, pValue.release());
	} else if (pValue->IsIterable()) {
		RefPtr<Iterator> pIteratorSrc(pValue->GenIterator());
		for (const Value* pValueIndexEach : valuesIndex) {
			RefPtr<Value> pValueEach(pIteratorSrc->NextValue());
			if (!pValueIndexEach) break;
			if (!EachIndexSet(*pValueIndexEach, pValueEach.release())) return;
		}
	} else {
		for (const Value* pValueIndex : valuesIndex) {
			if (!EachIndexSet(*pValueIndex, pValue->Reference())) return;
		}
	}
#else
	GetValueCar().DoIndexSet(*this, pValue.release());
#endif
}

bool Index::EachIndexSet(const Value& valueIndex, RefPtr<Value> pValue)
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
	return GetValueCar().DoIndexSet2(valueIndex, pValue.release());
}

Value* Index::IndexOpApply(Value& value, Processor& processor, Operator& op)
{
#if 0
	const ValueList& valuesIndex = GetValueOwner();
	if (valuesIndex.empty()) {
		Error::Issue(ErrorType::IndexError, "empty-indexing access is not supported");
		return nullptr;
	} else if (valuesIndex.size() == 1) {
		const Value& valueIndex = *valuesIndex.front();
		Value* pValueL = nullptr;
		if (!EachIndexGet(valueIndex, &pValueL, false)) return Value::nil();
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
#else
	return GetValueCar().DoIndexOpApply(*this, value, processor, op);
#endif
}

String Index::ToString(const StringStyle& ss) const
{
	return String().Format("Index:%s", GetValueCar().ToString(StringStyle(ss).SetQuoteSymbol()).c_str());
}

}
