//==============================================================================
// ArgFeeder.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ArgFeeder
//------------------------------------------------------------------------------
bool ArgFeeder::FeedValue(Value* pValue)
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

}
