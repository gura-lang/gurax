//==============================================================================
// ArgAccessor.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ArgAccessor
//------------------------------------------------------------------------------
bool ArgAccessor::FeedValue(Value* pValue)
{
	if (!_pArgSlot) {
		Error::Issue(ErrorType::ArgumentError, "too many arguments");
		return false;
	}
	_pArgSlot->FeedValue(pValue);
	if (Error::IsIssued()) return false;
	_pArgSlot = _pArgSlot->Advance();
	return true;
}

Value* ArgAccessor::GetValue()
{
	if (!_pArgSlot) return nullptr;
	Value* pValue = _pArgSlot->GetValue();
	_pArgSlot = _pArgSlot->GetNext();
	return pValue;
}

}
