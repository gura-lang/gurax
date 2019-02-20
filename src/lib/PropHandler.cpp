//==============================================================================
// PropHandler.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PropHandler
//------------------------------------------------------------------------------

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
