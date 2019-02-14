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

bool ArgSlot_Value::IsValid() const
{
	return true;
}

String ArgSlot_Value::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += GetDeclArg().GetSymbol()->GetName();
	rtn += ss.IsCram()? "=>" : " => ";
	rtn += _pValue->ToString(ss);
	return rtn;
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

bool ArgSlot_List::IsValid() const
{
	return true;
}

String ArgSlot_List::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += GetDeclArg().GetSymbol()->GetName();
	rtn += ss.IsCram()? "=>" : " => ";
	rtn += _pValue->GetValueOwner().ToString(ss);
	return rtn;
}

}
