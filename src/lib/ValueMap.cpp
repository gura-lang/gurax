//==============================================================================
// ValueMap.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ValueMap
//------------------------------------------------------------------------------
void ValueMap::Clear()
{
	for (auto& pair : _map) Value::Delete(pair.second);
	_map.clear();
}

void ValueMap::Assign(const Symbol* pSymbol, Value* pValue)
{
	auto pPair = _map.find(pSymbol);
	if (pPair == _map.end()) {
		_map.emplace(pSymbol, pValue);
	} else {
		Value::Delete(pPair->second);
		pPair->second = pValue;
	}
}

bool ValueMap::ExportTo(Processor& processor, Frame& frameDst, bool overwriteFlag) const
{
	for (auto pair : _map) {
		const Symbol* pSymbol = pair.first;
		const Value* pValue = pair.second;
		if (pSymbol->StartsWith('_')) {
			// nothing to do
		} else if (overwriteFlag || !frameDst.IsAssignedLocal(pSymbol)) {
			frameDst.Assign(pSymbol, pValue->Reference());
		} else {
			Error::Issue(ErrorType::ValueError,
							"can't overwrite the symbol: %s", pSymbol->GetName());
			return false;
		}
	}
	return true;
}

void ValueMap::GatherSymbol(SymbolList& symbolList) const
{
	for (auto pair : _map) {
		const Symbol* pSymbol = pair.first;
		symbolList.push_back(pSymbol);
	}
}

void ValueMap::GatherSymbolIf(SymbolList& symbolList, const Frame::GatherCriteria& gatherCriteria) const
{
	for (auto pair : _map) {
		const Symbol* pSymbol = pair.first;
		const Value* pValue = pair.second;
		//if (pValue->IsInstanceOf(VTYPE_Function)) symbolList.push_back(pSymbol);
		if (gatherCriteria.IsEligible(*pValue)) symbolList.push_back(pSymbol);
	}
}

String ValueMap::ToString(const StringStyle& ss) const
{
	String str;
	SymbolList keys = GetKeys().Sort();
	for (const Symbol* pSymbol : keys) {
		Value* pValue = Lookup(pSymbol);
		str += pSymbol->GetName();
		str += ":";
		str += pValue->GetVTypeCustom().MakeFullName().c_str();
		str += " = ";
		str += pValue->ToString(ss);
		str += "\n";
	}
	return str;
}

}
