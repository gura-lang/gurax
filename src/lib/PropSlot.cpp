//==============================================================================
// PropSlot.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PropSlot
//------------------------------------------------------------------------------
PropSlot::PropSlot(const Symbol* pSymbol, Flags flags) :
	_seqId(0), _pSymbol(pSymbol), _pVType(&VTYPE_Any), _flags(flags),
	_pHelpHolder(new HelpHolder())
{
}

void PropSlot::DeclareAttrOpt(const Symbol* pSymbol)
{
	if (!_pAttributeOpt) _pAttributeOpt.reset(new AttributeOpt());
	_pAttributeOpt->symbolList.push_back(pSymbol);
	_pAttributeOpt->symbolSet.GetSet().insert(pSymbol);
}

bool PropSlot::CheckValidAttribute(const Attribute& attr) const
{
	const SymbolList& symbols = attr.GetSymbols();
	if (symbols.empty()) return true;
	if (!_pAttributeOpt) {
		Error::Issue(ErrorType::PropertyError, "the property '%s' doesn't accept any attributes",
					 GetSymbol()->GetName());
		return false;
	}
	for (const Symbol* pSymbol : symbols) {
		if (!_pAttributeOpt->symbolSet.IsSet(pSymbol)) {
			Error::Issue(ErrorType::PropertyError, "the property '%s' doesn't accept attribute '%s'",
						 GetSymbol()->GetName(), pSymbol->GetName());
			return false;
		}
	}
	return true;
}

bool PropSlot::SetValue(Value& valueTarget, const Value& value, const Attribute& attr) const
{
	if (value.IsNil() && IsSet(Flag::Nil)) {
		DoSetValue(valueTarget, value, attr);
		return true;
	}
	RefPtr<Value> pValueCasted(GetVType().Cast(value, GetSymbol(), GetFlags()));
	if (!pValueCasted) return false;
	DoSetValue(valueTarget, *pValueCasted, attr);
	return true;
}

String PropSlot::ToString(const StringStyle& ss) const
{
	String str;
	str += GetName();
	if (IsSet(Flag::ListVar)) str += "[]";
	if (IsSet(Flag::Nil)) str += ":nil";
	if (IsSet(Flag::StreamR)) str += ":r";
	if (IsSet(Flag::StreamW)) str += ":w";
	if (IsSet(Flag::OfClass)) str += ":static";
	if (IsSet(Flag::Public)) str += ":public";
	if (IsSet(Flag::Readable)) str += ":R";
	if (IsSet(Flag::Writable)) str += ":W";
	if (_pAttributeOpt) {
		const SymbolList& symbolList = _pAttributeOpt->symbolList;
		if (symbolList.empty()) {
			str += ":[";
			for (auto ppSymbol = symbolList.begin(); ppSymbol != symbolList.end(); ppSymbol++) {
				const Symbol* pSymbol = *ppSymbol;
				if (ppSymbol != symbolList.begin()) str += ",";
				str += pSymbol->GetName();
			}
			str += "]";
		}
	}
	str.Format(" as %s", GetVType().MakeFullName().c_str());
	return str;
}

//------------------------------------------------------------------------------
// PropSlotList
//------------------------------------------------------------------------------
PropSlotList& PropSlotList::SortBySeqId(SortOrder sortOrder)
{
	SortByOrder<PropSlot::LessThan_SeqId, PropSlot::GreaterThan_SeqId>(sortOrder);
	return *this;
}

PropSlotList& PropSlotList::SortBySymbolName(SortOrder sortOrder)
{
	SortByOrder<PropSlot::LessThan_SymbolName, PropSlot::GreaterThan_SymbolName>(sortOrder);
	return *this;
}

String PropSlotList::ToString(const StringStyle& ss) const
{
	return "PropSlotList";
}

//------------------------------------------------------------------------------
// PropSlotOwner
//------------------------------------------------------------------------------
void PropSlotOwner::Clear()
{
	for (PropSlot* pPropSlot : *this) PropSlot::Delete(pPropSlot);
	clear();
}

//------------------------------------------------------------------------------
// PropSlotMap
//------------------------------------------------------------------------------
void PropSlotMap::Clear()
{
	for (auto& pair : _map) PropSlot::Delete(pair.second);
	_map.clear();
}

void PropSlotMap::Assign(PropSlot* pPropSlot)
{
	auto pPair = _map.find(pPropSlot->GetSymbol());
	if (pPair == _map.end()) {
		pPropSlot->SetSeqId(_map.size());
		_map.emplace(pPropSlot->GetSymbol(), pPropSlot);
	} else {
		pPropSlot->SetSeqId(pPair->second->GetSeqId());
		PropSlot::Delete(pPair->second);
		pPair->second = pPropSlot;
	}
}

void PropSlotMap::GatherPropSlot(PropSlotOwner& propSlotOwner) const
{
	for (auto iter : _map) {
		const PropSlot* pPropSlot = iter.second;
		propSlotOwner.push_back(pPropSlot->Reference());
	}
}

void PropSlotMap::GatherPropSlotOfInstance(PropSlotOwner& propSlotOwner) const
{
	for (auto iter : _map) {
		const PropSlot* pPropSlot = iter.second;
		if (!pPropSlot->IsOfClass()) propSlotOwner.push_back(pPropSlot->Reference());
	}
}

void PropSlotMap::GatherSymbol(SymbolList& symbolList) const
{
	for (auto iter : _map) symbolList.push_back(iter.first);
}

String PropSlotMap::ToString(const StringStyle& ss) const
{
	String str;
#if 0
	SymbolList keys = GetKeys().Sort();
	for (const Symbol* pSymbol : keys) {
		PropSlot* pPropSlot = Lookup(pSymbol);
		str += pSymbol->GetName();
		str += ":";
		str += pPropSlot->GetVType().MakeFullName().c_str();
		str += " = ";
		str += pPropSlot->ToString();
		str += "\n";
	}
#endif
	return str;
}

}
