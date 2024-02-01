//==============================================================================
// Index.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Index
//------------------------------------------------------------------------------
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

bool Index::EachIndexSet(Processor& processor, const Value& valueIndex, RefPtr<Value> pValue) const
{
	if (valueIndex.IsInstanceOf(VTYPE_List)) {
		const Value_List& valueIndexEx = dynamic_cast<const Value_List&>(valueIndex);
		if (pValue->IsIterable()) {
			RefPtr<Iterator> pIteratorSrc(pValue->GenIterator());
			for (const Value* pValueIndexEach : valueIndexEx.GetValueOwner()) {
				RefPtr<Value> pValueEach(pIteratorSrc->NextValue());
				if (!pValueIndexEach) break;
				if (!EachIndexSet(processor, *pValueIndexEach, pValueEach.release())) return false;
			}
		} else {
			for (const Value* pValueIndexEach : valueIndexEx.GetValueOwner()) {
				if (!EachIndexSet(processor, *pValueIndexEach, pValue->Reference())) return false;
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
				if (!EachIndexSet(processor, *pValueIndexEach, pValueEach.release())) return false;
			}
		} else {
			if (iteratorIndex.IsInfinite()) {
				Error::Issue(ErrorType::IteratorError, "infinite iterator is unacceptable");
				return false;
			}
			for (;;) {
				RefPtr<Value> pValueIndexEach(iteratorIndex.NextValue());
				if (!pValueIndexEach) break;
				if (!EachIndexSet(processor, *pValueIndexEach, pValue->Reference())) return false;
			}
		}
		return true;
	}
	return GetValueCar().DoSingleIndexSet(processor, valueIndex, pValue.release());
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
		EachIndexSet(processor, valueIndex, pValueRtn.Reference());
		return pValueRtn.release();
	} else if (value.IsIterable()) {
		Error::Issue_UnimplementedOperation();
		return Value::nil();
	} else {
		Error::Issue_UnimplementedOperation();
		return Value::nil();
	}
}

bool Index::GetIndexNumber(const Value& valueIndex, size_t size, size_t* pIdx)
{
	if (valueIndex.IsInstanceOf(VTYPE_Number)) {
		const Value_Number& valueIndexEx = dynamic_cast<const Value_Number&>(valueIndex);
		Int idx = valueIndexEx.GetNumber<Int>();
		if (idx < 0) idx += size;
		if (0 <= idx && static_cast<size_t>(idx) < size) {
			*pIdx = idx;
			return true;
		}
		Error::Issue(ErrorType::IndexError,
			"specified position %d exceeds the size of %zu", idx, size);
	} else if (valueIndex.IsInstanceOf(VTYPE_Bool)) {
		const Value_Bool& valueIndexEx = dynamic_cast<const Value_Bool&>(valueIndex);
		Int idx = static_cast<Int>(valueIndexEx.GetBool());
		if (static_cast<size_t>(idx) < size) {
			*pIdx = idx;
			return true;
		}
		Error::Issue(ErrorType::IndexError,
			"specified position %s exceeds the size of %zu",
			valueIndexEx.ToString(StringStyle::Quote_NilVisible).c_str(), size);
	} else {
		Error::Issue(ErrorType::IndexError,
			"invalid value for indexing");
	}
	return false;
}

String Index::ToString(const StringStyle& ss) const
{
	return String().Format("Index:%s", GetValueCar().ToString(StringStyle(ss).SetQuoteSymbol()).c_str());
}

}
