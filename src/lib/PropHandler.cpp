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
	RefPtr<Value> pValueCasted(GetVType().Cast(value, IsSet(Flag::ListVar)));
	if (!pValueCasted) return false;
	DoSetValue(valueTarget, *pValueCasted, attr);
	return true;
}

String PropHandler::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("%s", _pSymbol->GetName());
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
