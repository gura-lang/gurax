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
	_pAttributeOpt->symbolSet.insert(pSymbol);
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
	RefPtr<Value> pValueCasted(GetVType().Cast(value, GetFlags()));
	if (!pValueCasted) return false;
	DoSetValue(valueTarget, *pValueCasted, attr);
	return true;
}

String PropSlot::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("PropSlot:%s", _pSymbol->GetName());
	if (IsSet(Flag::ListVar)) str += "[]";
	str.Format(":%s", GetVType().MakeFullName().c_str());
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
	return str;
}

//------------------------------------------------------------------------------
// PropSlotList
//------------------------------------------------------------------------------
PropSlotList& PropSlotList::SortBySeqId(SortOrder sortOrder)
{
	SortCollectionByOrder<PropSlotList, PropSlot::LessThan_SeqId, PropSlot::GreaterThan_SeqId>
		(*this, sortOrder);
	return *this;
}

PropSlotList& PropSlotList::SortBySymbolName(SortOrder sortOrder)
{
	SortCollectionByOrder<PropSlotList, PropSlot::LessThan_SymbolName, PropSlot::GreaterThan_SymbolName>
		(*this, sortOrder);
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
	for (auto& pair : *this) PropSlot::Delete(pair.second);
	clear();
}

void PropSlotMap::Assign(PropSlot* pPropSlot)
{
	iterator pPair = find(pPropSlot->GetSymbol());
	if (pPair == end()) {
		pPropSlot->SetSeqId(size());
		emplace(pPropSlot->GetSymbol(), pPropSlot);
	} else {
		pPropSlot->SetSeqId(pPair->second->GetSeqId());
		PropSlot::Delete(pPair->second);
		pPair->second = pPropSlot;
	}
}

PropSlotOwner* PropSlotMap::CreatePropSlotOwner() const
{
	RefPtr<PropSlotOwner> pPropSlotOwner(new PropSlotOwner());
	for (auto iter : *this) pPropSlotOwner->push_back(iter.second->Reference());
	return pPropSlotOwner.release();
}

void PropSlotMap::GatherSymbol(SymbolList& symbolList) const
{
	for (auto iter : *this) symbolList.push_back(iter.first);
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
