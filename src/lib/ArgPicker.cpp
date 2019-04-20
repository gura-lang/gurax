//==============================================================================
// ArgPicker.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ArgPicker
//------------------------------------------------------------------------------
Value& ArgPicker::PickValue()
{
	_pValuePicked.reset(_pArgSlot->PickValue());
	_pArgSlot = _pArgSlot->GetNext();
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
