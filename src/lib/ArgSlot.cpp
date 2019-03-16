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
void ArgSlot_Single::ResetValue()
{
	_pValue.reset(Value::undefined());
}

void ArgSlot_Single::FeedValue(RefPtr<Value> pValue)
{
	const VType& vtype = GetDeclArg().GetVType();
	pValue.reset(vtype.Cast(*pValue));
	if (Error::IsIssued()) return;
	_pValue.reset(pValue.release());
}

String ArgSlot_Single::ToString(const StringStyle& ss) const
{
	String str;
	str += GetDeclArg().GetSymbol()->GetName();
	str += ss.IsCram()? "=>" : " => ";
	str += _pValue->ToString(ss);
	return str;
}

//------------------------------------------------------------------------------
// ArgSlot_Multiple
//------------------------------------------------------------------------------
void ArgSlot_Multiple::ResetValue()
{
	_pValue->GetValueTypedOwner().Clear();
}

void ArgSlot_Multiple::FeedValue(RefPtr<Value> pValue)
{
	const VType& vtype = GetDeclArg().GetVType();
	pValue.reset(vtype.Cast(*pValue));
	if (Error::IsIssued()) return;
	_pValue->GetValueTypedOwner().Add(pValue.release());
}

String ArgSlot_Multiple::ToString(const StringStyle& ss) const
{
	String str;
	str += GetDeclArg().GetSymbol()->GetName();
	str += ss.IsCram()? "=>" : " => ";
	str += _pValue->GetValueOwner().ToString(ss);
	return str;
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

//------------------------------------------------------------------------------
// ArgSlot_Dict
//------------------------------------------------------------------------------
void ArgSlot_Dict::ResetValue()
{
	_pValueDict->Clear();
}

void ArgSlot_Dict::FeedValue(RefPtr<Value> pValue)
{
	_pValueDict->Assign(new Value_Symbol(_pSymbol), pValue.release());
}

String ArgSlot_Dict::ToString(const StringStyle& ss) const
{
	String str;
	return str;
}

}
