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
	if (_pArgSlot) {
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

Function& ArgPicker::PickFunction()
{
	return Pick<Value_Function>().GetFunction();
}

Stream& ArgPicker::PickStream()
{
	return Pick<Value_Stream>().GetStream();
}

Iterator& ArgPicker::PickIterator()
{
	return Pick<Value_Iterator>().GetIterator();
}

}
