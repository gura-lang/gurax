//==============================================================================
// ValueDict.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ValueDict
//------------------------------------------------------------------------------
void ValueDict::Clear()
{
	for (auto& pair : *this) {
		Value::Delete(pair.first);
		Value::Delete(pair.second);
	}
	clear();
}

ValueDict* ValueDict::Clone() const
{
	RefPtr<ValueDict> pValueDict(new ValueDict());
	pValueDict->reserve(size());
	for (auto pair : *this) {
		pValueDict->emplace(pair.first->Reference(), pair.second->Reference());
	}
	return pValueDict.release();
}

ValueDict* ValueDict::CloneDeep() const
{
	RefPtr<ValueDict> pValueDict(new ValueDict());
	pValueDict->reserve(size());
	for (auto pair : *this) {
		Value* pValueKeyCloned = pair.first->Clone();
		if (!pValueKeyCloned) return nullptr;
		Value* pValueCloned = pair.second->Clone();
		if (!pValueCloned) return nullptr;
		pValueDict->emplace(pValueKeyCloned, pValueCloned);
	}
	return pValueDict.release();
}

void ValueDict::Assign(Value* pValueKey, Value* pValue)
{
	auto pPair = find(pValueKey);
	if (pPair == end()) {
		emplace(pValueKey, pValue);
	} else {
		Value::Delete(pPair->second);
		pPair->second = pValue;
	}
}

bool ValueDict::Store(const ValueDict& valDict, StoreMode storeMode)
{
	for (auto pairSrc : valDict) {
		const Value *pValueKey = pairSrc.first;
		ValueDict::iterator pPairDst = find(const_cast<Value*>(pValueKey));
		if (pPairDst == end()) {
			insert(ValueDict::value_type(pairSrc.first->Reference(), pairSrc.second->Reference()));
		} else if (storeMode == StoreMode::Overwrite) {
			Value::Delete(pPairDst->second);
			pPairDst->second = pairSrc.second->Reference();
		} else if (storeMode == StoreMode::Timid) {
			// nothing to do
		} else {
			Error::Issue(ErrorType::ValueError, "duplicated key '%s'", pValueKey->ToString().c_str());
			return false;
		}
	}
	return true;
}

bool ValueDict::Store(const Value& valueKey, const Value& value, StoreMode storeMode)
{
	if (!valueKey.IsAsDictKey()) {
		Error::Issue(ErrorType::TypeError, "invalid value type for key");
		return false;
	}
	ValueDict::iterator pPairDst = find(const_cast<Value*>(&valueKey));
	if (pPairDst == end()) {
		insert(ValueDict::value_type(valueKey.Reference(), value.Reference()));
	} else if (storeMode == StoreMode::Overwrite) {
		Value::Delete(pPairDst->second);
		pPairDst->second = value.Reference();
	} else if (storeMode == StoreMode::Timid) {
		// nothing to do
	} else {
		Error::Issue(ErrorType::ValueError, "duplicated key '%s'", valueKey.ToString().c_str());
		return false;
	}
	return true;
}

void ValueDict::Erase(const Value& valueKey)
{
	auto pPair = find(const_cast<Value*>(&valueKey));
	if (pPair == end()) return;
	Value::Delete(pPair->first);
	Value::Delete(pPair->second);
	erase(pPair);
}

String ValueDict::ToString(const StringStyle& ss) const
{
	const char* strPair = ss.IsCram()? "=>" : " => ";
	RefPtr<ValueOwner> pKeys(GetKeys());
	pKeys->Sort();
	String str;
	str += "%{";
	for (auto ppValueKey = pKeys->begin(); ppValueKey != pKeys->end(); ppValueKey++) {
		const Value* pValueKey = *ppValueKey;
		const Value* pValue = Lookup(*pValueKey);
		if (ppValueKey != pKeys->begin()) str += ss.GetComma();
		str += pValueKey->ToString(ss);
		str += strPair;
		str += pValue->ToString(ss);
	}
	str += "}";
	return str;
}

void ValueDict::IssueError_KeyNotFound(const Value& valueKey)
{
	Error::Issue(ErrorType::KeyError, "the dictionary doesn't have a key '%s'", valueKey.ToString().c_str());
}

}
