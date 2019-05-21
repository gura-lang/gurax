//==============================================================================
// ArgPicker.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ArgPicker
//------------------------------------------------------------------------------
bool ArgPicker::IsValid()
{
	if (IsDefined()) {
		if (PeekValue().IsValid()) return true;
		_pArgSlot = _pArgSlot->GetNext();
		_peekedFlag = false;
	}
	return false;
}

Value& ArgPicker::PeekValue()
{
	if (!_peekedFlag) {
		_pValuePicked.reset(_pArgSlot->PickValue());
		_peekedFlag = true;
	}
	return *_pValuePicked;
}

Value& ArgPicker::PickValue()
{
	if (!_peekedFlag) {
		_pValuePicked.reset(_pArgSlot->PickValue());
	}
	_pArgSlot = _pArgSlot->GetNext();
	_peekedFlag = false;
	return *_pValuePicked;
}

Stream& ArgPicker::PickStream()
{
	return Value_Stream::GetStream(PickValue());
}

Iterator& ArgPicker::PickIterator()
{
	return Value_Iterator::GetIterator(PickValue());
}

}
