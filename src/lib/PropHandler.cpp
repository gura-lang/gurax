//==============================================================================
// PropHandler.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PropHandler
//------------------------------------------------------------------------------
PropHandler::PropHandler(const Symbol* pSymbol, Flags flags) :
	_pSymbol(pSymbol), _pVType(&VTYPE_Any), _flags(flags),
	_pHelpProvider(new HelpProvider())
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
		emplace(pPropHandler->GetSymbol(), pPropHandler);
	} else {
		PropHandler::Delete(pPair->second);
		pPair->second = pPropHandler;
	}
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
