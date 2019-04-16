//==============================================================================
// ArgPicker.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ArgPicker
//------------------------------------------------------------------------------
Value* ArgPicker::PickValue()
{
	if (!_pArgSlot) return nullptr;
	_pValuePicked.reset(_pArgSlot->PickValue());
	_pArgSlot = _pArgSlot->GetNext();
	return _pValuePicked.get();
}

Stream& ArgPicker::PickStream()
{
	return dynamic_cast<Value_Stream*>(PickValue())->GetStream();
}

Iterator& ArgPicker::PickIterator()
{
	return dynamic_cast<Value_Iterator*>(PickValue())->GetIterator();
}

}
