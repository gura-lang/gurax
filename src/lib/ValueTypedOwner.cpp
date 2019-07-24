//==============================================================================
// ValueTypedOwner.cpp
//==============================================================================
#include "stdafx.h"

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
	_pVTypeOfElems = &VTYPE_Undefined;
	GetValueOwner().Clear();
}

ValueTypedOwner* ValueTypedOwner::CreateFromIterator(Iterator& iterator)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	for (;;) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		pValueOwner->push_back(pValue.release());
	}	
	return new ValueTypedOwner(pValueOwner.release());
}

void ValueTypedOwner::Add(const ValueList& values)
{
	UpdateVTypeOfElems(values.GetVTypeOfElems());
	GetValueOwner().Add(values);
}
	
void ValueTypedOwner::Add(const ValueTypedOwner& values)
{
	UpdateVTypeOfElems(values.GetVTypeOfElems());
	GetValueOwner().Add(values.GetValueOwner());
}

bool ValueTypedOwner::Add(Iterator& iterator)
{
	for (;;) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		Add(pValue->Reference());
	}
	return !Error::IsIssued();
}

void ValueTypedOwner::Append(const ValueList& values)
{
	for (Value* pValue : values) {
		if (pValue->IsType(VTYPE_List)) {
			Add(Value_List::GetValueTypedOwner(*pValue));
		} else if (pValue->IsType(VTYPE_Iterator)) {
			Add(Value_Iterator::GetIterator(*pValue));
		} else {
			Add(pValue->Reference());
		}
	}
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
// ValueTypedOwner::Iterator_Each
//------------------------------------------------------------------------------
Value* ValueTypedOwner::Iterator_Each::DoNextValue()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (_idx >= valueOwner.size()) return nullptr;
	return valueOwner[_idx++]->Reference();
}

String ValueTypedOwner::Iterator_Each::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#Each:n=%zu", GetValueOwner().size());
	return str;
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
	const ValueOwner& valueOwner = GetValueOwner();
	if (_idx >= valueOwner.size()) return nullptr;
	return valueOwner[_idx++]->Reference();
}

String ValueTypedOwner::Iterator_Permutation::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#Permutation:n=%zu", GetValueOwner().size());
	return str;
}

//------------------------------------------------------------------------------
// ValueTypedOwner::Iterator_Combination
//------------------------------------------------------------------------------
Value* ValueTypedOwner::Iterator_Combination::DoNextValue()
{
	const ValueOwner& valueOwner = GetValueOwner();
	if (_idx >= valueOwner.size()) return nullptr;
	return valueOwner[_idx++]->Reference();
}

String ValueTypedOwner::Iterator_Combination::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("List#Combination:n=%zu", GetValueOwner().size());
	return str;
}

}
