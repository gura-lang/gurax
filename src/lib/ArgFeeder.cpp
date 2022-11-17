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
	if (Error::IsIssued()) return false;
	if (!_pArgSlot) {
		if (_argument.IsSet(DeclCallable::Flag::CutExtraArgs)) {
			// just ignore extra arguments
			return true;
		} else {
			Error::Issue(ErrorType::ArgumentError, "too many arguments");
			return false;
		}
	}
	_pArgSlot->FeedValue(_argument, _frame, pValue);
	if (Error::IsIssued()) return false;
	_pArgSlot = _pArgSlot->Advance();
	return true;
}

bool ArgFeeder::FeedValues(const ValueList& values)
{
	for (const Value* pValue : values) {
		if (!FeedValue(pValue->Reference())) return false;
	}
	return true;
}

}
