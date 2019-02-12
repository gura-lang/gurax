//==============================================================================
// ArgSlot.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ArgSlot
//------------------------------------------------------------------------------
ArgSlot* ArgSlot::Find(const Symbol* pSymbol)
{
	ArgSlot* pArgSlot = this;
	for ( ; pArgSlot; pArgSlot = pArgSlot->GetNext()) {
		if (pArgSlot->IsMatched(pSymbol)) return pArgSlot;
	}
	return pArgSlot;
}

//------------------------------------------------------------------------------
// ArgSlot_Value
//------------------------------------------------------------------------------
void ArgSlot_Value::FeedValue(Value* pValue)
{
	_pValue.reset(pValue);
}

//------------------------------------------------------------------------------
// ArgSlot_ValueList
//------------------------------------------------------------------------------
void ArgSlot_ValueList::FeedValue(Value* pValue)
{
	_pValue->GetValueTypedOwner().Add(pValue);
}

}
