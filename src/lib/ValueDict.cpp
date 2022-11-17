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
	for (auto& pair : _map) {
		Value::Delete(pair.first);
		Value::Delete(pair.second);
	}
	_map.clear();
}

ValueDict* ValueDict::Clone() const
{
	RefPtr<ValueDict> pValueDict(new ValueDict());
	pValueDict->_map.reserve(_map.size());
	for (auto pair : _map) {
		//pValueDict->_map.emplace(pair.first->Reference(), pair.second->Reference());
		pValueDict->_map.insert(Map::value_type(pair.first->Reference(), pair.second->Reference()));
	}
	return pValueDict.release();
}

ValueDict* ValueDict::CloneDeep() const
{
	RefPtr<ValueDict> pValueDict(new ValueDict());
	pValueDict->_map.reserve(_map.size());
	for (auto pair : _map) {
		RefPtr<Value> pValueKeyCloned(pair.first->Clone());
		if (!pValueKeyCloned) return nullptr;
		RefPtr<Value> pValueCloned(pair.second->Clone());
		if (!pValueCloned) return nullptr;
		//pValueDict->_map.emplace(pValueKeyCloned.release(), pValueCloned.release());
		pValueDict->_map.insert(Map::value_type(pValueKeyCloned.release(), pValueCloned.release()));
	}
	return pValueDict.release();
}

void ValueDict::Assign(RefPtr<Value> pValueKey, RefPtr<Value> pValue)
{
	auto pPair = _map.find(pValueKey.get());
	if (pPair == _map.end()) {
		//_map.emplace(pValueKey.release(), pValue.release());
		_map.insert(Map::value_type(pValueKey.release(), pValue.release()));
	} else {
		Value::Delete(pPair->second);
		pPair->second = pValue.release();
	}
}

bool ValueDict::Store(const ValueDict& valDict, StoreMode storeMode)
{
	for (auto pairSrc : valDict._map) {
		const Value* pValueKey = pairSrc.first;
		auto pPairDst = _map.find(const_cast<Value*>(pValueKey));
		if (pPairDst == _map.end()) {
			_map.insert(Map::value_type(pairSrc.first->Reference(), pairSrc.second->Reference()));
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
	auto pPairDst = _map.find(const_cast<Value*>(&valueKey));
	if (pPairDst == _map.end()) {
		_map.insert(Map::value_type(valueKey.Reference(), value.Reference()));
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
	auto pPair = _map.find(const_cast<Value*>(&valueKey));
	if (pPair == _map.end()) return;
	Value::Delete(pPair->first);
	Value::Delete(pPair->second);
	_map.erase(pPair);
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
		str += pValueKey->ToString(StringStyle::Quote_NilVisible);
		str += strPair;
		str += pValue->ToString(StringStyle::Quote_NilVisible);
	}
	str += "}";
	return str;
}

void ValueDict::IssueError_KeyNotFound(const Value& valueKey)
{
	Error::Issue(ErrorType::KeyError, "the dictionary doesn't have a key '%s'", valueKey.ToString().c_str());
}

}
