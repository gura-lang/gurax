//==============================================================================
// ValueTypedOwner.cpp
//==============================================================================
#include "stdafx.h"
#include "../boost/combination.hpp"

namespace Gurax {

//------------------------------------------------------------------------------
// ValueTypedOwner
//------------------------------------------------------------------------------
ValueTypedOwner::ValueTypedOwner(VType& vtypeOfElems, ValueOwner* pValueOwner) :
	_pVTypeOfElems(pValueOwner->empty()? &VTYPE_Undefined : &vtypeOfElems), _pValueOwner(pValueOwner)
{
}

void ValueTypedOwner::Clear()
{
	ValueOwner& valueOwner = GetValueOwner();
	_pVTypeOfElems = &VTYPE_Undefined;
	valueOwner.Clear();
}

bool ValueTypedOwner::Set(Int pos, Value* pValue)
{
	ValueOwner& valueOwner = GetValueOwner();
	if (!valueOwner.FixPosition(&pos)) return false;
	UpdateVTypeOfElems(*pValue);
	valueOwner.Set(pos, pValue);
	return true;
}

Value* ValueTypedOwner::Get(Int pos) const
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (!valueOwner.FixPosition(&pos)) return nullptr;
	return valueOwner.Get(pos);
}

bool ValueTypedOwner::IndexSet(const Value* pValueIndex, Value* pValue)
{
	ValueOwner& valueOwner = GetValueOwner();
	UpdateVTypeOfElems(*pValue);
	if (pValueIndex->IsInstanceOf(VTYPE_Number)) {
		const Value_Number* pValueIndexEx = dynamic_cast<const Value_Number*>(pValueIndex);
		Int pos = pValueIndexEx->GetNumber<Int>();
		if (pos < 0) pos += valueOwner.size();
		if (0 <= pos && static_cast<size_t>(pos) < valueOwner.size()) {
			valueOwner.Set(pos, pValue);
			return true;
		}
		valueOwner.IssueError_IndexOutOfRange(pos);
	} else if (pValueIndex->IsInstanceOf(VTYPE_Bool)) {
		const Value_Bool* pValueIndexEx = dynamic_cast<const Value_Bool*>(pValueIndex);
		int pos = static_cast<int>(pValueIndexEx->GetBool());
		if (static_cast<size_t>(pos) < valueOwner.size()) {
			valueOwner.Set(pos, pValue);
			return true;
		}
		valueOwner.IssueError_IndexOutOfRange(pValueIndexEx->ToString().c_str());
	} else {
		Error::Issue(ErrorType::IndexError, "number or bool value is expected for list indexing");
	}
	Value::Delete(pValue);
	return false;
}

bool ValueTypedOwner::IndexGet(const Value* pValueIndex, Value** ppValue) const
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (pValueIndex->IsInstanceOf(VTYPE_Number)) {
		const Value_Number* pValueIndexEx = dynamic_cast<const Value_Number*>(pValueIndex);
		Int pos = pValueIndexEx->GetNumber<Int>();
		if (!valueOwner.FixPosition(&pos)) return false;
		*ppValue = valueOwner.Get(pos)->Reference();
		return true;
	} else if (pValueIndex->IsInstanceOf(VTYPE_Bool)) {
		const Value_Bool* pValueIndexEx = dynamic_cast<const Value_Bool*>(pValueIndex);
		int pos = static_cast<int>(pValueIndexEx->GetBool());
		if (!valueOwner.FixPosition(&pos)) return false;
		*ppValue = valueOwner.Get(pos)->Reference();
		return true;
	} else {
		Error::Issue(ErrorType::IndexError, "number or bool value is expected for list indexing");
	}
	return false;
}

void ValueTypedOwner::Add(Value* pValue)
{
	ValueOwner& valueOwner = GetValueOwner();
	UpdateVTypeOfElems(*pValue);
	valueOwner.Add(pValue);
}

void ValueTypedOwner::Add(const ValueList& values)
{
	ValueOwner& valueOwner = GetValueOwner();
	UpdateVTypeOfElems(values.GetVTypeOfElems());
	valueOwner.Add(values);
}
	
void ValueTypedOwner::Add(const ValueTypedOwner& values)
{
	ValueOwner& valueOwner = GetValueOwner();
	UpdateVTypeOfElems(values.GetVTypeOfElems());
	valueOwner.Add(values.GetValueOwner());
}

bool ValueTypedOwner::Add(Iterator& iterator)
{
	ValueOwner& valueOwner = GetValueOwner();
	for (;;) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		UpdateVTypeOfElems(*pValue);
		valueOwner.Add(pValue.release());
	}
	return !Error::IsIssued();
}

bool ValueTypedOwner::Append(const ValueList& values)
{
	for (Value* pValue : values) {
		if (pValue->IsType(VTYPE_List)) {
			Add(Value_List::GetValueTypedOwner(*pValue));
		} else if (pValue->IsType(VTYPE_Iterator)) {
			if (!Add(Value_Iterator::GetIterator(*pValue))) return false;
		} else {
			Add(pValue->Reference());
		}
	}
	return true;
}

bool ValueTypedOwner::Insert(Int pos, const ValueList& values)
{
	ValueOwner& valueOwner = GetValueOwner();
	if (!valueOwner.FixPosition(&pos)) return false;
	UpdateVTypeOfElems(values.GetVTypeOfElems());
	valueOwner.Insert(pos, values);
	return true;
}

bool ValueTypedOwner::Insert(Int pos, const ValueTypedOwner& values)
{
	ValueOwner& valueOwner = GetValueOwner();
	if (!valueOwner.FixPosition(&pos)) return false;
	UpdateVTypeOfElems(values.GetVTypeOfElems());
	valueOwner.Add(values.GetValueOwner());
	return true;
}

bool ValueTypedOwner::Insert(Int pos, Iterator& iterator)
{
	ValueOwner& valueOwner = GetValueOwner();
	if (!valueOwner.FixPosition(&pos)) return false;
	for (;;) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		UpdateVTypeOfElems(*pValue);
		valueOwner.Insert(pos, pValue.release());
		pos++;
	}
	return !Error::IsIssued();
}

bool ValueTypedOwner::Erase(Int pos)
{
	ValueOwner& valueOwner = GetValueOwner();
	if (!valueOwner.FixPosition(&pos)) return false;
	ValueOwner::iterator ppValue = valueOwner.begin() + pos;
	Value::Delete(*ppValue);
	valueOwner.erase(ppValue);
	return true;
}

// Elements in posList must be fixed and sorted in a descending order.
bool ValueTypedOwner::Erase(const NumList<Int>& posList)
{
	ValueOwner& valueOwner = GetValueOwner();
	for (Int pos : posList) {
		if (!valueOwner.CheckPosition(pos)) return false;
		ValueOwner::iterator ppValue = valueOwner.begin() + pos;
		Value::Delete(*ppValue);
		valueOwner.erase(ppValue);
	}
	return true;
}

void ValueTypedOwner::UpdateVTypeOfElems(const Value& value)
{
	// Assumes that value is not of Undefined or Any.
	VType& vtypeAdded = value.GetVType();
	if (_pVTypeOfElems->IsIdentical(VTYPE_Undefined)) {
		_pVTypeOfElems = &vtypeAdded;
	} else if (!_pVTypeOfElems->IsIdentical(vtypeAdded)) {
		_pVTypeOfElems = &VTYPE_Any;
	}
}

void ValueTypedOwner::UpdateVTypeOfElems(VType& vtypeAdded)
{
	if (vtypeAdded.IsIdentical(VTYPE_Undefined)) {
		// nothing to do
	} else if (vtypeAdded.IsIdentical(VTYPE_Any)) {
		_pVTypeOfElems = &VTYPE_Any;
	} else if (_pVTypeOfElems->IsIdentical(VTYPE_Undefined)) {
		_pVTypeOfElems = &vtypeAdded;
	} else if (!_pVTypeOfElems->IsIdentical(vtypeAdded)) {
		_pVTypeOfElems = &VTYPE_Any;
	}
}

bool ValueTypedOwner::HasDeterminedVTypeOfElems() const
{
	return !_pVTypeOfElems->IsIdentical(VTYPE_Undefined) && !_pVTypeOfElems->IsIdentical(VTYPE_Any);
}

//------------------------------------------------------------------------------
// ValueTypedOwner::Iterator_Reverse
//------------------------------------------------------------------------------
Value* ValueTypedOwner::Iterator_Reverse::DoNextValue()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (_idx >= valueOwner.size()) return nullptr;
	return valueOwner[_idx++]->Reference();
}

String ValueTypedOwner::Iterator_Reverse::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#Reverse:n=%zu", GetValueOwner().size());
	return str;
}

//------------------------------------------------------------------------------
// ValueTypedOwner::Iterator_Cycle
//------------------------------------------------------------------------------
Value* ValueTypedOwner::Iterator_Cycle::DoNextValue()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (_idx >= valueOwner.size()) return nullptr;
	return valueOwner[_idx++]->Reference();
}

String ValueTypedOwner::Iterator_Cycle::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#Cycle:n=%zu", GetValueOwner().size());
	return str;
}

//------------------------------------------------------------------------------
// ValueTypedOwner::Iterator_Pingpong
//------------------------------------------------------------------------------
Value* ValueTypedOwner::Iterator_Pingpong::DoNextValue()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (_idx >= valueOwner.size()) return nullptr;
	return valueOwner[_idx++]->Reference();
}

String ValueTypedOwner::Iterator_Pingpong::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#Pingpong:n=%zu", GetValueOwner().size());
	return str;
}

//------------------------------------------------------------------------------
// ValueTypedOwner::Iterator_Fold
//------------------------------------------------------------------------------
Value* ValueTypedOwner::Iterator_Fold::DoNextValue()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (_idx >= valueOwner.size()) return nullptr;
	return valueOwner[_idx++]->Reference();
}

String ValueTypedOwner::Iterator_Fold::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#Fold:n=%zu", GetValueOwner().size());
	return str;
}

//------------------------------------------------------------------------------
// ValueTypedOwner::Iterator_Permutation
//------------------------------------------------------------------------------
Value* ValueTypedOwner::Iterator_Permutation::DoNextValue()
{
	if (_doneFlag) return nullptr;
	RefPtr<Value> pValue(new Value_List(GetValueTypedOwner().Extract<size_t>(_indices)));
	_doneFlag = !std::next_permutation(_indices.begin(), _indices.end());
	return pValue.release();
}

String ValueTypedOwner::Iterator_Permutation::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#Permutation:n=%zu", GetValueOwner().size());
	return str;
}

//------------------------------------------------------------------------------
// ValueTypedOwner::Iterator_PartialPermutation
//------------------------------------------------------------------------------
Value* ValueTypedOwner::Iterator_PartialPermutation::DoNextValue()
{
	if (_doneFlag) return nullptr;
	RefPtr<Value> pValue(new Value_List(GetValueTypedOwner().Extract(_indices, _nExtract)));
	_doneFlag = !boost::next_partial_permutation(_indices.begin(), _indices.begin() + _nExtract, _indices.end());
	return pValue.release();
}

String ValueTypedOwner::Iterator_PartialPermutation::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#PartialPermutation:n=%zu:r=%zu", GetValueOwner().size(), _nExtract);
	return str;
}

//------------------------------------------------------------------------------
// ValueTypedOwner::Iterator_Combination
//------------------------------------------------------------------------------
Value* ValueTypedOwner::Iterator_Combination::DoNextValue()
{
	if (_doneFlag) return nullptr;
	RefPtr<Value> pValue(new Value_List(GetValueTypedOwner().Extract(_indices, _nExtract)));
	_doneFlag = !boost::next_combination(_indices.begin(), _indices.begin() + _nExtract, _indices.end());
	return pValue.release();
}

String ValueTypedOwner::Iterator_Combination::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#Combination:n=%zu:r=%zu", GetValueOwner().size(), _nExtract);
	return str;
}

}
