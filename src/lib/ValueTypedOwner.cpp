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
	ValueOwner& valueOwner = GetValueOwnerToModify();
	_pVTypeOfElems = &VTYPE_Undefined;
	valueOwner.Clear();
}

bool ValueTypedOwner::Set(Int pos, Value* pValue)
{
	ValueOwner& valueOwner = GetValueOwnerToModify();
	if (!valueOwner.FixPosition(&pos, true)) return false;
	UpdateVTypeOfElems(*pValue);
	valueOwner.Set(pos, pValue);
	return true;
}

#if 0
bool ValueTypedOwner::IndexSet(const Value& valueIndex, RefPtr<Value> pValue)
{
	ValueOwner& valueOwner = GetValueOwnerToModify();
	UpdateVTypeOfElems(*pValue);
	if (valueIndex.IsInstanceOf(VTYPE_Number)) {
		const Value_Number& valueIndexEx = dynamic_cast<const Value_Number&>(valueIndex);
		Int pos = valueIndexEx.GetNumber<Int>();
		if (pos < 0) pos += valueOwner.size();
		if (0 <= pos && static_cast<size_t>(pos) < valueOwner.size()) {
			valueOwner.Set(pos, pValue.release());
			return true;
		}
		valueOwner.IssueError_IndexOutOfRange(pos);
	} else if (valueIndex.IsInstanceOf(VTYPE_Bool)) {
		const Value_Bool& valueIndexEx = dynamic_cast<const Value_Bool&>(valueIndex);
		int pos = static_cast<int>(valueIndexEx.GetBool());
		if (static_cast<size_t>(pos) < valueOwner.size()) {
			valueOwner.Set(pos, pValue.release());
			return true;
		}
		valueOwner.IssueError_IndexOutOfRange(valueIndexEx.ToString(StringStyle::Quote_NilVisible).c_str());
	} else if (valueIndex.IsInstanceOf(VTYPE_List)) {
		const Value_List& valueIndexEx = dynamic_cast<const Value_List&>(valueIndex);
		if (pValue->IsIterable()) {
			RefPtr<Iterator> pIteratorSrc(pValue->GenIterator());
			for (const Value* pValueIndexEach : valueIndexEx.GetValueOwner()) {
				RefPtr<Value> pValueEach(pIteratorSrc->NextValue());
				if (!pValueIndexEach) break;
				if (!IndexSet(*pValueIndexEach, pValueEach.release())) return false;
			}
		} else {
			for (const Value* pValueIndexEach : valueIndexEx.GetValueOwner()) {
				if (!IndexSet(*pValueIndexEach, pValue->Reference())) return false;
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
				if (!IndexSet(*pValueIndexEach, pValueEach.release())) return false;
			}
		} else {
			if (iteratorIndex.IsInfinite()) {
				Error::Issue(ErrorType::IteratorError, "infinite iterator is unacceptable");
				return false;
			}
			for (;;) {
				RefPtr<Value> pValueIndexEach(iteratorIndex.NextValue());
				if (!pValueIndexEach) break;
				if (!IndexSet(*pValueIndexEach, pValue->Reference())) return false;
			}
		}
	} else {
		Error::Issue(ErrorType::IndexError, "number or bool value is expected for list indexing");
	}
	return false;
}
#endif

void ValueTypedOwner::Add(Value* pValue)
{
	ValueOwner& valueOwner = GetValueOwnerToModify();
	UpdateVTypeOfElems(*pValue);
	valueOwner.Add(pValue);
}

void ValueTypedOwner::Add(const ValueList& values)
{
	ValueOwner& valueOwner = GetValueOwnerToModify();
	UpdateVTypeOfElems(values.GetVTypeOfElems());
	valueOwner.Add(values);
}
	
void ValueTypedOwner::Add(const ValueTypedOwner& values)
{
	ValueOwner& valueOwner = GetValueOwnerToModify();
	UpdateVTypeOfElems(values.GetVTypeOfElems());
	valueOwner.Add(values.GetValueOwner());
}

bool ValueTypedOwner::Add(Iterator& iterator)
{
	if (!iterator.MustBeFinite()) return false;
	ValueOwner& valueOwner = GetValueOwnerToModify();
	for (;;) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		UpdateVTypeOfElems(*pValue);
		valueOwner.Add(pValue.release());
	}
	return !Error::IsIssued();
}

void ValueTypedOwner::AddX(const ValueList& values)
{
	ValueOwner& valueOwner = GetValueOwnerToModify();
	for (const Value* pValue : values) {
		if (pValue->IsValid()) {
			UpdateVTypeOfElems(*pValue);
			valueOwner.Add(pValue->Reference());
		}
	}
}
	
void ValueTypedOwner::AddX(const ValueTypedOwner& values)
{
	ValueOwner& valueOwner = GetValueOwnerToModify();
	for (const Value* pValue : values.GetValueOwner()) {
		if (pValue->IsValid()) {
			UpdateVTypeOfElems(*pValue);
			valueOwner.Add(pValue->Reference());
		}
	}
}

bool ValueTypedOwner::AddX(Iterator& iterator)
{
	if (!iterator.MustBeFinite()) return false;
	ValueOwner& valueOwner = GetValueOwnerToModify();
	for (;;) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		if (pValue->IsValid()) {
			UpdateVTypeOfElems(*pValue);
			valueOwner.Add(pValue.release());
		}
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
	ValueOwner& valueOwner = GetValueOwnerToModify();
	if (valueOwner.size() == pos) {
		Add(values);
		return true;
	}
	if (!valueOwner.FixPosition(&pos, true)) return false;
	UpdateVTypeOfElems(values.GetVTypeOfElems());
	valueOwner.Insert(pos, values);
	return true;
}

bool ValueTypedOwner::Insert(Int pos, const ValueTypedOwner& values)
{
	ValueOwner& valueOwner = GetValueOwnerToModify();
	if (valueOwner.size() == pos) {
		Add(values);
		return true;
	}
	if (!valueOwner.FixPosition(&pos, true)) return false;
	UpdateVTypeOfElems(values.GetVTypeOfElems());
	valueOwner.Add(values.GetValueOwner());
	return true;
}

bool ValueTypedOwner::Insert(Int pos, Iterator& iterator)
{
	if (!iterator.MustBeFinite()) return false;
	ValueOwner& valueOwner = GetValueOwnerToModify();
	if (valueOwner.size() == pos) return Add(iterator);
	if (!valueOwner.FixPosition(&pos, true)) return false;
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
	ValueOwner& valueOwner = GetValueOwnerToModify();
	if (!valueOwner.FixPosition(&pos, true)) return false;
	ValueOwner::iterator ppValue = valueOwner.begin() + pos;
	Value::Delete(*ppValue);
	valueOwner.erase(ppValue);
	return true;
}

// Elements in posList must be fixed and sorted in a descending order.
bool ValueTypedOwner::Erase(const NumList<Int>& posList)
{
	ValueOwner& valueOwner = GetValueOwnerToModify();
	for (Int pos : posList) {
		if (!valueOwner.CheckPosition(pos, true)) return false;
		ValueOwner::iterator ppValue = valueOwner.begin() + pos;
		Value::Delete(*ppValue);
		valueOwner.erase(ppValue);
	}
	return true;
}

void ValueTypedOwner::UpdateVTypeOfElems(const Value& value)
{
	// Assumes that value is not of Undefined or Any.
	VType& vtypeAdded = value.GetVTypeCustom();
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

VType& ValueTypedOwner::RefreshVTypeOfElems()
{
	if (_pVTypeOfElems->IsIdentical(VTYPE_Any) ||
		_pVTypeOfElems->IsIdentical(VTYPE_Undefined)) {
		const ValueOwner& valueOwner = GetValueOwner();
		auto ppValue = valueOwner.begin();
		if (ppValue != valueOwner.end()) {
			VType* pVType = &(*ppValue)->GetVTypeCustom();
			ppValue++;
			for ( ; ppValue != valueOwner.end(); ppValue++) {
				if (pVType->IsIdentical((*ppValue)->GetVTypeCustom())) {
					pVType = &VTYPE_Any;
					break;
				}
			}
			_pVTypeOfElems = pVType;
		}
	}
	return *_pVTypeOfElems;
}

bool ValueTypedOwner::HasDeterminedVTypeOfElems() const
{
	return !_pVTypeOfElems->IsIdentical(VTYPE_Undefined) && !_pVTypeOfElems->IsIdentical(VTYPE_Any);
}

Iterator* ValueTypedOwner::GenerateIterator() const
{
	return new Iterator_Each(GetValueOwner().Reference());
}

}
