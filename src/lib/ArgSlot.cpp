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

void ArgSlot_Single::FeedValue(Argument& argument, Frame& frameForVType, RefPtr<Value> pValue)
{
	if (pValue->IsMappable(GetDeclArg(), argument.GetFlags())) {
		pValue->UpdateMapMode(argument);
		_pValue.reset(new Value_ArgMapper(pValue->GenIterator()));
	} else {
		pValue.reset(GetDeclArg().Cast(frameForVType, *pValue));
		if (Error::IsIssued()) return;
		_pValue.reset(pValue.release());
	}
}

String ArgSlot_Single::ToString(const StringStyle& ss) const
{
	return String().Format("%s%s%s", GetDeclArg().GetSymbol()->GetName(),
					ss.IsCram()? "=" : " = ", _pValue->ToString(ss).c_str());
}

//------------------------------------------------------------------------------
// ArgSlot_Multiple
//------------------------------------------------------------------------------
void ArgSlot_Multiple::ResetValue()
{
	GetValue().GetValueTypedOwner().Clear();
}

void ArgSlot_Multiple::FeedValue(Argument& argument, Frame& frame, RefPtr<Value> pValue)
{
	if (pValue->IsMappable(GetDeclArg(), argument.GetFlags())) {
		if (GetValue().IsList()) {
			// Replace List with ArgMapper_Multiple.
			SetValue(new Value_ArgMapper_Multiple(GetValue().GetValueTypedOwner().Reference()));
		}
		pValue->UpdateMapMode(argument);
		GetValue().GetValueTypedOwner().Add(new Value_ArgMapper(pValue->GenIterator()));
	} else {
		pValue.reset(GetDeclArg().Cast(frame, *pValue));
		if (Error::IsIssued()) return;
		GetValue().GetValueTypedOwner().Add(pValue.release());
	}
}

String ArgSlot_Multiple::ToString(const StringStyle& ss) const
{
	return String().Format("%s%s%s", GetDeclArg().GetSymbol()->GetName(),
		ss.IsCram()? "=" : " = ", GetValue().GetValueOwner().
					ToString(StringStyle(ss).SetWithSquare()).c_str());
}

//------------------------------------------------------------------------------
// ArgSlot_Dict
//------------------------------------------------------------------------------
void ArgSlot_Dict::ResetValue()
{
	GetValue().GetValueDict().Clear();
}

void ArgSlot_Dict::FeedValue(Argument& argument, Frame& frame, RefPtr<Value> pValue)
{
	GetValue().GetValueDict().Assign(new Value_Symbol(_pSymbol), pValue.release());
}

String ArgSlot_Dict::ToString(const StringStyle& ss) const
{
	return GetValue().ToString(ss);
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
