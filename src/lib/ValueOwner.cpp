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

//-----------------------------------------------------------------------------
// Iterator_Fold
//-----------------------------------------------------------------------------
ValueOwner::Iterator_Fold::Iterator_Fold(Iterator* pIteratorSrc, size_t nSize, size_t nAdvance,
							 bool itemAsIterFlag, bool neatFlag) :
	_pIteratorSrc(pIteratorSrc), _nSize(nSize), _nAdvance(nAdvance),
	_itemAsIterFlag(itemAsIterFlag), _neatFlag(neatFlag), _doneFlag(false)
{
	if (_nAdvance < _nSize) {
		_pValueOwnerRemain.reset(new ValueOwner());
		_pValueOwnerRemain->reserve(_nSize - _nAdvance);
	}
}

Value* ValueOwner::Iterator_Fold::DoNextValue()
{
	if (_doneFlag) return nullptr;
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(_nSize);
	if (_nAdvance < _nSize) {
		std::copy(_pValueOwnerRemain->begin(), _pValueOwnerRemain->end(), std::back_inserter(*pValueOwner));
		_pValueOwnerRemain->clear();	// don't use Clear() to avoid decrementation of reference counter
		while (pValueOwner->size() < _nSize) {
			RefPtr<Value> pValueElem(GetIteratorSrc().NextValue());
			if (!pValueElem) {
				_doneFlag = true;
				if (Error::IsIssued()) return nullptr;
				break;
			}
			pValueOwner->push_back(pValueElem.release());
		}
		if (pValueOwner->size() > _nAdvance) {
			std::copy(pValueOwner->begin() + _nAdvance, pValueOwner->end(), std::back_inserter(*_pValueOwnerRemain));
		_pValueOwnerRemain->IncCntRefOfEach();
		}
	} else {
		while (pValueOwner->size() < _nSize) {
			RefPtr<Value> pValueElem(GetIteratorSrc().NextValue());
			if (!pValueElem) {
				_doneFlag = true;
				if (Error::IsIssued()) return nullptr;
				break;
			}
			pValueOwner->push_back(pValueElem.release());
		}
		// dumb reading
		for (size_t n = _nAdvance - _nSize; n > 0; n--) {
			RefPtr<Value> pValueElem(GetIteratorSrc().NextValue());
			if (!pValueElem) {
				_doneFlag = true;
				if (Error::IsIssued()) return nullptr;
				break;
			}
		}
	}
	if (pValueOwner->empty() || (_neatFlag && pValueOwner->size() < _nSize)) {
		_doneFlag = true;
		return nullptr;
	} else if (_itemAsIterFlag) {
		RefPtr<Iterator> pIterator(new Iterator_Each(pValueOwner.release()));
		return new Value_Iterator(pIterator.release());
	} else {
		return new Value_List(pValueOwner.release());
	}
}

size_t ValueOwner::Iterator_Fold::GetLength() const
{
	if (GetIteratorSrc().IsLenUndetermined()) return -1;
	size_t nElems = GetIteratorSrc().GetLength();
	return _neatFlag? nElems / _nSize : (nElems + _nSize - 1) / _nSize;
}

String ValueOwner::Iterator_Fold::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "List#Fold(";
	rtn += GetIteratorSrc().ToString();
	rtn += ")";
	return rtn;
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
