//==============================================================================
// PropHandler.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PropHandler
//------------------------------------------------------------------------------
PropHandler::PropHandler(const Symbol* pSymbol, Flags flags) :
	_seqId(0), _pSymbol(pSymbol), _pVType(&VTYPE_Any), _flags(flags),
	_pHelpHolder(new HelpHolder())
{
}

bool PropHandler::SetValue(Value& valueTarget, const Value& value, const Attribute& attr) const
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

String PropHandler::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("%s", _pSymbol->GetName());
	if (IsSet(Flag::ListVar)) str += "[]";
	str.Printf(":%s", GetVType().MakeFullName().c_str());
	if (IsSet(Flag::Nil)) str += ":nil";
	if (IsSet(Flag::StreamR)) str += ":r";
	if (IsSet(Flag::StreamW)) str += ":w";
	if (IsSet(Flag::OfClass)) str += ":static";
	if (IsSet(Flag::Public)) str += ":public";
	if (IsSet(Flag::Readable)) str += ":R";
	if (IsSet(Flag::Writable)) str += ":W";
	return str;
}

//------------------------------------------------------------------------------
// PropHandlerList
//------------------------------------------------------------------------------
PropHandlerList& PropHandlerList::SortBySeqId(SortOrder sortOrder)
{
	SortListByOrder<PropHandlerList, PropHandler::LessThan_SeqId, PropHandler::GreaterThan_SeqId>
		(*this, sortOrder);
	return *this;
}

PropHandlerList& PropHandlerList::SortBySymbolName(SortOrder sortOrder)
{
	SortListByOrder<PropHandlerList, PropHandler::LessThan_SymbolName, PropHandler::GreaterThan_SymbolName>
		(*this, sortOrder);
	return *this;
}

String PropHandlerList::ToString(const StringStyle& ss) const
{
	return "PropHandlerList";
}

//------------------------------------------------------------------------------
// PropHandlerOwner
//------------------------------------------------------------------------------
void PropHandlerOwner::Clear()
{
	for (PropHandler* pPropHandler : *this) PropHandler::Delete(pPropHandler);
	clear();
}

//------------------------------------------------------------------------------
// PropHandlerMap
//------------------------------------------------------------------------------
void PropHandlerMap::Clear()
{
	for (auto& pair : *this) PropHandler::Delete(pair.second);
	clear();
}

void PropHandlerMap::Assign(PropHandler* pPropHandler)
{
	iterator pPair = find(pPropHandler->GetSymbol());
	if (pPair == end()) {
		pPropHandler->SetSeqId(size());
		emplace(pPropHandler->GetSymbol(), pPropHandler);
	} else {
		pPropHandler->SetSeqId(pPair->second->GetSeqId());
		PropHandler::Delete(pPair->second);
		pPair->second = pPropHandler;
	}
}

PropHandlerOwner* PropHandlerMap::CreatePropHandlerOwner() const
{
	RefPtr<PropHandlerOwner> pPropHandlerOwner(new PropHandlerOwner());
	for (auto iter : *this) pPropHandlerOwner->push_back(iter.second->Reference());
	return pPropHandlerOwner.release();
}

void PropHandlerMap::GatherSymbol(SymbolList& symbolList) const
{
	for (auto iter : *this) symbolList.push_back(iter.first);
}

String PropHandlerMap::ToString(const StringStyle& ss) const
{
	String str;
#if 0
	SymbolList keys = GetKeys().Sort();
	for (const Symbol* pSymbol : keys) {
		PropHandler* pPropHandler = Lookup(pSymbol);
		str += pSymbol->GetName();
		str += ":";
		str += pPropHandler->GetVType().MakeFullName().c_str();
		str += " = ";
		str += pPropHandler->ToString();
		str += "\n";
	}
#endif
	return str;
}

}
