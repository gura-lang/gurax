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
// ArgSlot_Single
//------------------------------------------------------------------------------
void ArgSlot_Single::FeedValue(RefPtr<Value> pValue)
{
	const VType& vtype = GetDeclArg().GetVType();
	pValue.reset(Value::Cast(vtype, *pValue));
	if (Error::IsIssued()) return;
	_pValue.reset(pValue.release());
}

String ArgSlot_Single::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += GetDeclArg().GetSymbol()->GetName();
	rtn += ss.IsCram()? "=>" : " => ";
	rtn += _pValue->ToString(ss);
	return rtn;
}

//------------------------------------------------------------------------------
// ArgSlot_Multiple
//------------------------------------------------------------------------------
void ArgSlot_Multiple::FeedValue(RefPtr<Value> pValue)
{
	const VType& vtype = GetDeclArg().GetVType();
	pValue.reset(Value::Cast(vtype, *pValue));
	if (Error::IsIssued()) return;
	_pValue->GetValueTypedOwner().Add(pValue.release());
}

String ArgSlot_Multiple::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += GetDeclArg().GetSymbol()->GetName();
	rtn += ss.IsCram()? "=>" : " => ";
	rtn += _pValue->GetValueOwner().ToString(ss);
	return rtn;
}

//------------------------------------------------------------------------------
// ArgSlot_Once
//------------------------------------------------------------------------------
const ArgSlot_Once::Factory ArgSlot_Once::factory;

//------------------------------------------------------------------------------
// ArgSlot_ZeroOrOnce
//------------------------------------------------------------------------------
const ArgSlot_ZeroOrOnce::Factory ArgSlot_ZeroOrOnce::factory;

//------------------------------------------------------------------------------
// ArgSlot_ZeroOrMore
//------------------------------------------------------------------------------
const ArgSlot_ZeroOrMore::Factory ArgSlot_ZeroOrMore::factory;

//------------------------------------------------------------------------------
// ArgSlot_OnceOrMore
//------------------------------------------------------------------------------
const ArgSlot_OnceOrMore::Factory ArgSlot_OnceOrMore::factory;

}
