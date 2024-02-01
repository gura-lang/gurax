//==============================================================================
// ArgFeeder.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ArgFeeder
//------------------------------------------------------------------------------
bool ArgFeeder::FeedValue(Processor& processor, Value* pValue)
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
	_pArgSlot->FeedValue(processor, _argument, _frame, pValue);
	if (Error::IsIssued()) return false;
	_pArgSlot = _pArgSlot->Advance();
	return true;
}

bool ArgFeeder::FeedValues(Processor& processor, const ValueList& values)
{
	for (const Value* pValue : values) {
		if (!FeedValue(processor, pValue->Reference())) return false;
	}
	return true;
}

}
