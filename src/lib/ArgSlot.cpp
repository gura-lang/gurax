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
void ArgSlot_Value::FeedValue(RefPtr<Value> pValue)
{
	const VType& vtype = GetDeclArg().GetVType();
	pValue.reset(vtype.DoCastFrom(pValue.release()));
	if (Error::IsIssued()) return;
	_pValue.reset(pValue.release());
}

//------------------------------------------------------------------------------
// ArgSlot_List
//------------------------------------------------------------------------------
void ArgSlot_List::FeedValue(RefPtr<Value> pValue)
{
	const VType& vtype = GetDeclArg().GetVType();
	pValue.reset(vtype.DoCastFrom(pValue.release()));
	if (Error::IsIssued()) return;
	_pValue->GetValueTypedOwner().Add(pValue.release());
}

//------------------------------------------------------------------------------
// ArgSlot_Mapping
//------------------------------------------------------------------------------
void ArgSlot_Mapping::FeedValue(RefPtr<Value> pValue)
{
	const VType& vtype = GetDeclArg().GetVType();
	pValue.reset(vtype.DoCastFrom(pValue.release()));
	if (Error::IsIssued()) return;
	_pValue.reset(pValue.release());
}

}
