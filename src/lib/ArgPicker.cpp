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
	Value* pValue = _pArgSlot->GetValue();
	_pArgSlot = _pArgSlot->GetNext();
	return pValue;
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
