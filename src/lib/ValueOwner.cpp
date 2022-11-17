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

ValueOwner* ValueOwner::Head(size_t n) const
{
	ValueOwner::const_iterator ppValueEnd = (size() <= n)? end() : begin() + n;
	RefPtr<ValueOwner> pValueOwner(new ValueOwner(begin(), ppValueEnd));
	pValueOwner->IncCntRefOfEach();
	return pValueOwner.release();
}

ValueOwner* ValueOwner::Tail(size_t n) const
{
	ValueOwner::const_iterator ppValueBegin = (size() <= n)? begin() : begin() + size() - n;
	RefPtr<ValueOwner> pValueOwner(new ValueOwner(ppValueBegin, end()));
	pValueOwner->IncCntRefOfEach();
	return pValueOwner.release();
}

ValueOwner* ValueOwner::Create(Value* pValue)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(1);
	pValueOwner->push_back(pValue);
	return pValueOwner.release();
}

ValueOwner* ValueOwner::Create(Value* pValue1, Value* pValue2)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(2);
	pValueOwner->push_back(pValue1);
	pValueOwner->push_back(pValue2);
	return pValueOwner.release();
}

ValueOwner* ValueOwner::Create(Value* pValue1, Value* pValue2, Value* pValue3)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(3);
	pValueOwner->push_back(pValue1);
	pValueOwner->push_back(pValue2);
	pValueOwner->push_back(pValue3);
	return pValueOwner.release();
}

ValueOwner* ValueOwner::Create(Value* pValue1, Value* pValue2, Value* pValue3, Value* pValue4)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(4);
	pValueOwner->push_back(pValue1);
	pValueOwner->push_back(pValue2);
	pValueOwner->push_back(pValue3);
	pValueOwner->push_back(pValue4);
	return pValueOwner.release();
}

ValueOwner* ValueOwner::Create(Value* pValue1, Value* pValue2, Value* pValue3, Value* pValue4, Value* pValue5)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(5);
	pValueOwner->push_back(pValue1);
	pValueOwner->push_back(pValue2);
	pValueOwner->push_back(pValue3);
	pValueOwner->push_back(pValue4);
	pValueOwner->push_back(pValue5);
	return pValueOwner.release();
}

ValueOwner* ValueOwner::Create(Value* pValue1, Value* pValue2, Value* pValue3, Value* pValue4, Value* pValue5, Value* pValue6)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(6);
	pValueOwner->push_back(pValue1);
	pValueOwner->push_back(pValue2);
	pValueOwner->push_back(pValue3);
	pValueOwner->push_back(pValue4);
	pValueOwner->push_back(pValue5);
	pValueOwner->push_back(pValue6);
	return pValueOwner.release();
}

ValueOwner* ValueOwner::CreateFromIterator(Iterator& iterator, bool skipNilFlag)
{
	if (!iterator.MustBeFinite()) return nullptr;
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

void ValueOwner::Add(Iterator& iterator)
{
	for (;;) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		push_back(pValue.release());
	}
}

void ValueOwner::AddX(const ValueList& values)
{
	for (const Value* pValue : values) {
		if (pValue->IsValid()) push_back(pValue->Reference());
	}
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
