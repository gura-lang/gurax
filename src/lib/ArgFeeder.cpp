//==============================================================================
// ArgFeeder.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ArgFeeder
//------------------------------------------------------------------------------
bool ArgFeeder::FeedValue(Frame& frame, Value* pValue)
{
	if (!_pArgSlot) {
		Error::Issue(ErrorType::ArgumentError, "too many arguments");
		return false;
	}
	_pArgSlot->FeedValue(_argument, frame, pValue);
	if (Error::IsIssued()) return false;
	_pArgSlot = _pArgSlot->Advance();
	return true;
}

}
