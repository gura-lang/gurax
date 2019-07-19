//==============================================================================
// ValueTypedOwner.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ValueTypedOwner
//------------------------------------------------------------------------------
ValueTypedOwner::ValueTypedOwner() :
	_pVTypeOfElems(&VTYPE_Undefined), _pValueOwner(new ValueOwner())
{}

void ValueTypedOwner::Clear()
{
	_pVTypeOfElems = &VTYPE_Undefined;
	_pValueOwner->Clear();
}

void ValueTypedOwner::Append(const ValueTypedOwner& values)
{
	for (const Value* pValue : values.GetValueOwner()) {
		Add(pValue->Reference());
	}
}

void ValueTypedOwner::Append(Iterator& iterator)
{
	for (;;) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		Add(pValue->Reference());
	}
}

void ValueTypedOwner::UpdateVTypeOfElems(VType& vtypeAdded)
{
	if (_pVTypeOfElems->IsIdentical(VTYPE_Undefined)) {
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
