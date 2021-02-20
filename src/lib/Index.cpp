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
#if 0
	const ValueList& valuesIndex = GetValueOwner();
	if (valuesIndex.empty()) {
		//return Clone();
		return Value::nil();
	} else if (valuesIndex.size() == 1) {
		const Value& valueIndex = *valuesIndex.front();
		Value* pValue = nullptr;
		//if (!GetValueTypedOwner().IndexGet(valueIndex, &pValue, false)) return Value::nil();
		return pValue;
	} else {
		RefPtr<ValueOwner> pValuesRtn(new ValueOwner());
		pValuesRtn->reserve(valuesIndex.size());
		for (const Value* pValueIndex : valuesIndex) {
			Value* pValue = nullptr;
			//if (!GetValueTypedOwner().IndexGet(*pValueIndex, &pValue, false)) return Value::nil();
			pValuesRtn->push_back(pValue);
		}
		return new Value_List(pValuesRtn.release());
	}
#else
	return GetValueCar().DoIndexGet(*this);
#endif
}

bool EachIndexGet(const Value& valueIndex, Value** ppValue, bool tupleResultFlag)
{
	size_t posMax = 0;
	if (valueIndex.IsInstanceOf(VTYPE_Number)) {
		const Value_Number& valueIndexEx = dynamic_cast<const Value_Number&>(valueIndex);
		Int pos = valueIndexEx.GetNumber<Int>();
		if (pos < 0) pos += posMax;
		if (0 <= pos && static_cast<size_t>(pos) < posMax) {
			//*ppValue = Get(pos).Reference();
			return true;
		}
		Error::Issue(ErrorType::IndexError,
			"specified position %d exceeds the list's size of %zu", pos, posMax);
	} else if (valueIndex.IsInstanceOf(VTYPE_Bool)) {
		const Value_Bool& valueIndexEx = dynamic_cast<const Value_Bool&>(valueIndex);
		int pos = static_cast<int>(valueIndexEx.GetBool());
		if (pos < 0) pos += posMax;
		if (0 <= pos && static_cast<size_t>(pos) < posMax) {
			//*ppValue = Get(pos).Reference();
			return true;
		}
		Error::Issue(ErrorType::IndexError,
			"specified position %s exceeds the list's size of %zu",
			valueIndexEx.ToString(StringStyle::Quote_NilVisible).c_str(), posMax);
	} else if (valueIndex.IsInstanceOf(VTYPE_List)) {
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
	} else {
		Error::Issue(ErrorType::IndexError, "number or bool value is expected for list indexing");
	}
	return false;
}

void Index::IndexSet(Value* pValue)
{
#if 0
	const ValueList& valuesIndex = GetValueOwner();
	if (valuesIndex.empty()) {
		Error::Issue(ErrorType::IndexError, "empty-indexing access is not supported");
	} else if (valuesIndex.size() == 1) {
		const Value& valueIndex = *valuesIndex.front();
		//GetValueTypedOwner().IndexSet(valueIndex, pValue.release());
	} else if (pValue->IsIterable()) {
		RefPtr<Iterator> pIteratorSrc(pValue->GenIterator());
		for (const Value* pValueIndexEach : valuesIndex) {
			RefPtr<Value> pValueEach(pIteratorSrc->NextValue());
			if (!pValueIndexEach) break;
			//if (!GetValueTypedOwner().IndexSet(*pValueIndexEach, pValueEach.release())) return;
		}
	} else {
		for (const Value* pValueIndex : valuesIndex) {
			//if (!GetValueTypedOwner().IndexSet(*pValueIndex, pValue->Reference())) return;
		}
	}
#else
	GetValueCar().DoIndexSet(*this, pValue);
#endif
}

bool EachIndexSet(const Value& valueIndex, RefPtr<Value> pValue)
{
	size_t posMax = 0;
	if (valueIndex.IsInstanceOf(VTYPE_Number)) {
		const Value_Number& valueIndexEx = dynamic_cast<const Value_Number&>(valueIndex);
		Int pos = valueIndexEx.GetNumber<Int>();
		if (pos < 0) pos += posMax;
		if (0 <= pos && static_cast<size_t>(pos) < posMax) {
			//valueOwner.Set(pos, pValue.release());
			return true;
		}
		Error::Issue(ErrorType::IndexError,
			"specified position %d exceeds the list's size of %zu", pos, posMax);
	} else if (valueIndex.IsInstanceOf(VTYPE_Bool)) {
		const Value_Bool& valueIndexEx = dynamic_cast<const Value_Bool&>(valueIndex);
		int pos = static_cast<int>(valueIndexEx.GetBool());
		if (static_cast<size_t>(pos) < posMax) {
			//valueOwner.Set(pos, pValue.release());
			return true;
		}
		Error::Issue(ErrorType::IndexError,
			"specified position %s exceeds the list's size of %zu",
			valueIndexEx.ToString(StringStyle::Quote_NilVisible).c_str(), posMax);
	} else if (valueIndex.IsInstanceOf(VTYPE_List)) {
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
	} else {
		Error::Issue(ErrorType::IndexError, "number or bool value is expected for list indexing");
	}
	return false;
}

Value* Index::IndexOpApply(Value& value, Processor& processor, Operator& op)
{
	return GetValueCar().DoIndexOpApply(*this, value, processor, op);
}

String Index::ToString(const StringStyle& ss) const
{
	return String().Format("Index:%s", GetValueCar().ToString(StringStyle(ss).SetQuoteSymbol()).c_str());
}

}
