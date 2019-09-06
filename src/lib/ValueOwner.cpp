//==============================================================================
// ValueOwner.cpp
//==============================================================================
#include "stdafx.h"
#include "../boost/combination.hpp"

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
// ValueOwner::Iterator_Reverse
//------------------------------------------------------------------------------
Value* ValueOwner::Iterator_Reverse::DoNextValue()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (_idx >= valueOwner.size()) return nullptr;
	return valueOwner[_idx++]->Reference();
}

String ValueOwner::Iterator_Reverse::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#Reverse:n=%zu", GetValueOwner().size());
	return str;
}

//------------------------------------------------------------------------------
// ValueOwner::Iterator_Cycle
//------------------------------------------------------------------------------
Value* ValueOwner::Iterator_Cycle::DoNextValue()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (_idx >= valueOwner.size()) return nullptr;
	return valueOwner[_idx++]->Reference();
}

String ValueOwner::Iterator_Cycle::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#Cycle:n=%zu", GetValueOwner().size());
	return str;
}

//------------------------------------------------------------------------------
// ValueOwner::Iterator_Pingpong
//------------------------------------------------------------------------------
Value* ValueOwner::Iterator_Pingpong::DoNextValue()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (_idx >= valueOwner.size()) return nullptr;
	return valueOwner[_idx++]->Reference();
}

String ValueOwner::Iterator_Pingpong::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#Pingpong:n=%zu", GetValueOwner().size());
	return str;
}

//------------------------------------------------------------------------------
// ValueOwner::Iterator_Fold
//------------------------------------------------------------------------------
Value* ValueOwner::Iterator_Fold::DoNextValue()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (_idx >= valueOwner.size()) return nullptr;
	return valueOwner[_idx++]->Reference();
}

String ValueOwner::Iterator_Fold::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#Fold:n=%zu", GetValueOwner().size());
	return str;
}

//------------------------------------------------------------------------------
// ValueOwner::Iterator_Permutation
//------------------------------------------------------------------------------
Value* ValueOwner::Iterator_Permutation::DoNextValue()
{
	if (_doneFlag) return nullptr;
	RefPtr<Value> pValue(new Value_List(GetValueOwner().Extract<size_t>(_indices)));
	_doneFlag = !std::next_permutation(_indices.begin(), _indices.end());
	return pValue.release();
}

String ValueOwner::Iterator_Permutation::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#Permutation:n=%zu", GetValueOwner().size());
	return str;
}

//------------------------------------------------------------------------------
// ValueOwner::Iterator_PartialPermutation
//------------------------------------------------------------------------------
Value* ValueOwner::Iterator_PartialPermutation::DoNextValue()
{
	if (_doneFlag) return nullptr;
	RefPtr<Value> pValue(new Value_List(GetValueOwner().Extract(_indices, _nExtract)));
	_doneFlag = !boost::next_partial_permutation(_indices.begin(), _indices.begin() + _nExtract, _indices.end());
	return pValue.release();
}

String ValueOwner::Iterator_PartialPermutation::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#PartialPermutation:n=%zu:r=%zu", GetValueOwner().size(), _nExtract);
	return str;
}

//------------------------------------------------------------------------------
// ValueOwner::Iterator_Combination
//------------------------------------------------------------------------------
Value* ValueOwner::Iterator_Combination::DoNextValue()
{
	if (_doneFlag) return nullptr;
	RefPtr<Value> pValue(new Value_List(GetValueOwner().Extract(_indices, _nExtract)));
	_doneFlag = !boost::next_combination(_indices.begin(), _indices.begin() + _nExtract, _indices.end());
	return pValue.release();
}

String ValueOwner::Iterator_Combination::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#Combination:n=%zu:r=%zu", GetValueOwner().size(), _nExtract);
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
