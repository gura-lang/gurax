//==============================================================================
// ValueOwner.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ValueOwner
//------------------------------------------------------------------------------
void ValueOwner::Clear()
{
	for (Value* pValue : *this) Value::Delete(pValue);
	clear();
}

ValueOwner* ValueOwner::Clone() const
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner(*this));
	pValueOwner->IncCntRefOfEach();
	return pValueOwner.release();
}

ValueOwner* ValueOwner::Extract(size_t n) const
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner(begin(), begin() + n));
	pValueOwner->IncCntRefOfEach();
	return pValueOwner.release();
}

ValueOwner* ValueOwner::CloneDeep() const
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(size());
	for (Value* pValue : *this) {
		Value* pValueCloned = pValue->Clone();
		if (!pValueCloned) return nullptr;
		pValueOwner->push_back(pValueCloned);
	}
	return pValueOwner.release();
}

ValueOwner* ValueOwner::CreateFromIterator(Iterator& iterator, bool skipNilFlag)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	if (skipNilFlag) {
		for (;;) {
			RefPtr<Value> pValue(iterator.NextValue());
			if (!pValue) break;
			if (pValue->IsValid()) pValueOwner->push_back(pValue.release());
		}
	} else {
		for (;;) {
			RefPtr<Value> pValue(iterator.NextValue());
			if (!pValue) break;
			pValueOwner->push_back(pValue.release());
		}
	}
	return pValueOwner.release();
}

ValueOwner* ValueOwner::CreateFromStringList(const StringList& strs)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(strs.size());
	for (const String& str : strs) pValueOwner->push_back(new Value_String(str));
	return pValueOwner.release();
}

void ValueOwner::Set(Int pos, Value* pValue)
{
	auto ppValue = begin() + pos;
	Value::Delete(*ppValue);
	*ppValue = pValue;
}

void ValueOwner::Add(const ValueList& values)
{
	values.IncCntRefOfEach();
	insert(end(), values.begin(), values.end());
}

void ValueOwner::Insert(Int pos, const ValueList& values)
{
	values.IncCntRefOfEach();
	insert(begin() + pos, values.begin(), values.end());
}

Value* ValueOwner::Shift()
{
	if (empty()) return Value::nil();
	RefPtr<Value> pValue(front());
	erase(begin());
	return pValue.release();
}

//------------------------------------------------------------------------------
// ValueOwner::Iterator_Each
//------------------------------------------------------------------------------
Value* ValueOwner::Iterator_Each::DoNextValue()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (_idx >= valueOwner.size()) return nullptr;
	return valueOwner[_idx++]->Reference();
}

String ValueOwner::Iterator_Each::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#Each:begin=%zu:n=%zu", _idxBegin, GetValueOwner().size());
	return str;
}

//------------------------------------------------------------------------------
// ValueStack
//------------------------------------------------------------------------------
void ValueStack::Remove(size_t offset)
{
	auto ppValue = begin() + size() - (offset + 1);
	Value* pValue = *ppValue;
	erase(ppValue);
	Value::Delete(pValue);
}

void ValueStack::Remove(size_t offset, size_t cnt)
{
	auto ppValueBegin = begin() + size() - (offset + cnt);
	auto ppValueEnd = ppValueBegin + cnt;
	for (auto ppValue = ppValueBegin; ppValue != ppValueEnd; ppValue++) {
		Value::Delete(*ppValue);
	}
	erase(ppValueBegin, ppValueEnd);
}

void ValueStack::Shrink(size_t cnt)
{
	if (cnt >= size()) return;
	auto ppValueEnd = rbegin() + size() - cnt;
	for (auto ppValue = rbegin(); ppValue != ppValueEnd; ppValue++) {
		Value::Delete(*ppValue);
	}
	erase(begin() + cnt, end());
}

}
