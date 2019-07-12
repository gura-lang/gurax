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
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(size());
	for (Value* pValue : *this) pValueOwner->push_back(pValue->Reference());
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

void ValueOwner::Set(size_t pos, Value* pValue)
{
	auto ppValue = begin() + pos;
	Value::Delete(*ppValue);
	*ppValue = pValue;
}

bool ValueOwner::IndexGet(const Value* pValueIndex, Value** ppValue) const
{
	if (pValueIndex->IsInstanceOf(VTYPE_Number)) {
		const Value_Number* pValueIndexEx = dynamic_cast<const Value_Number*>(pValueIndex);
		int idxOrg = pValueIndexEx->GetInt();
		int idx = (idxOrg >= 0)? idxOrg : idxOrg + size();
		if (0 <= idx && static_cast<size_t>(idx) < size()) {
			*ppValue = Get(idx)->Reference();
			return true;
		}
		Error::Issue(ErrorType::IndexError, "index %d is out of range of the list size %zu",
					 idx, size());
	} else if (pValueIndex->IsInstanceOf(VTYPE_Bool)) {
		const Value_Bool* pValueIndexEx = dynamic_cast<const Value_Bool*>(pValueIndex);
		int idx = static_cast<int>(pValueIndexEx->GetBool());
		if (static_cast<size_t>(idx) < size()) {
			*ppValue = Get(idx)->Reference();
			return true;
		}
		Error::Issue(ErrorType::IndexError, "index %s is out of range of the list size %zu",
					 pValueIndexEx->ToString().c_str(), size());
	} else {
		Error::Issue(ErrorType::IndexError, "number or bool value is expected for list indexing");
	}
	return false;
}

bool ValueOwner::IndexSet(const Value* pValueIndex, Value* pValue)
{
	if (pValueIndex->IsInstanceOf(VTYPE_Number)) {
		const Value_Number* pValueIndexEx = dynamic_cast<const Value_Number*>(pValueIndex);
		int idxOrg = pValueIndexEx->GetInt();
		int idx = (idxOrg >= 0)? idxOrg : idxOrg + size();
		if (0 <= idx && static_cast<size_t>(idx) < size()) {
			Set(idx, pValue);
			return true;
		}
		Error::Issue(ErrorType::IndexError, "index %d is out of range of the list size %zu",
					 idx, size());
	} else if (pValueIndex->IsInstanceOf(VTYPE_Bool)) {
		const Value_Bool* pValueIndexEx = dynamic_cast<const Value_Bool*>(pValueIndex);
		int idx = static_cast<int>(pValueIndexEx->GetBool());
		if (static_cast<size_t>(idx) < size()) {
			Set(idx, pValue);
			return true;
		}
		Error::Issue(ErrorType::IndexError, "index %s is out of range of the list size %zu",
					 pValueIndexEx->ToString().c_str(), size());
	} else {
		Error::Issue(ErrorType::IndexError, "number or bool value is expected for list indexing");
	}
	Value::Delete(pValue);
	return false;
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
